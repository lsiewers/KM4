<?php
    include '../connect_db.php';
    include '../checkparam.php';

    $deviceId = checkParam('deviceId', 999, FILTER_VALIDATE_INT);

    // Test URL = circa/esp32/get-recommended.php?deviceId=1

    // Calculate a recommended time based on:
        // - total average of your records for personalization
        // - this week's average of your records for consistency
        // - your chronotype's recommended time for optimization
        // - strictness for preferences

    // DISCLAIMERS:
        // - It's only for going to bed in the evening and out of bed in the morning once
        // - All evening records must be before 23:59:59 (11:59:59PM), because the average is only based on the day itself


    // SELECT
            // - overall average in bed records
            // - overall average out bed records
            // - overall average in bed records of last week only
            // - overall average out bed records of last week only
            // - recommended in bed time according to user's chronotype
            // - recommended out bed time according to user's chronotype
            // - users' strictness setting
    $recordsQuery = "SELECT 
                        SEC_TO_TIME(AVG(TIME_TO_SEC(r.inBedRecord))) AS totalInBedAvg,
                        SEC_TO_TIME(AVG(TIME_TO_SEC(r.outBedRecord))) AS totalOutBedAvg,
                        (SELECT SEC_TO_TIME(AVG(TIME_TO_SEC(inBedRecord))) 
                            FROM c_bedTimeRecords c 
                            WHERE deviceId='".$deviceId."' 
                            AND outBedRecord >=DATE_ADD(CURDATE(), INTERVAL -7 DAY) 
                            AND outBedRecord <=CURDATE()) AS weekInBedAvg, 
                        (SELECT SEC_TO_TIME(AVG(TIME_TO_SEC(outBedRecord))) 
                            FROM c_bedTimeRecords c 
                            WHERE deviceId='".$deviceId."'
                            AND outBedRecord >=DATE_ADD(CURDATE(), INTERVAL -7 DAY) 
                            AND outBedRecord <=CURDATE()) AS weekOutBedAvg, 
                        chr.inBedTime AS chronoInBedTime, 
                        chr.outBedTime AS chronoOutBedTime,
                        d.strictness AS strictness
                    FROM c_devices d 
                    LEFT JOIN c_bedTimeRecords r ON (r.deviceId = d.id) 
                    LEFT JOIN c_users u ON (deviceId = d.id) 
                    LEFT JOIN c_chronotypes chr ON (u.chronotype = chr.name) 
                    WHERE d.id='".$deviceId."'";

    if (!($result = $mysqli->query($recordsQuery)))
        showerror($mysqli->errno,$recordsQuery->error);
    
    $row = $result->fetch_assoc();

    // show json
    // do {
    //     echo "<br>";
    //     echo json_encode($row);
    // } while ($row = $result->fetch_assoc())
    // echo "chronotype in bed time = " . strval($row['chronoInBedTime']) . " <br>";
    // echo "average overall in bed time = " . strval($row['totalInBedAvg']) . " <br>";
    // echo "average in bed time last week = " . strval($row['weekInBedAvg']) . " <br><br>";
    // echo "strictness = " . strval($row['strictness']) . " <br>";
    // algorithm($row['totalInBedAvg'], $row['weekInBedAvg'], $row['chronoInBedTime'], $row['strictness']);
    // echo "<br>";
    // echo "strictness = " . (string)(1-$row['strictness']) . " <br>";
    // algorithm($row['totalInBedAvg'], $row['weekInBedAvg'], $row['chronoInBedTime'], (1 - $row['strictness']));
    $calculatedCount = 0;

    if (!isset($obj)) $obj = new stdClass();

    $inBedTimeRecommended = algorithm($row['totalInBedAvg'], $row['weekInBedAvg'], $row['chronoInBedTime'], $row['strictness'], "inBedTimeRecommended", $obj);
    $outBedTimeRecommended = algorithm($row['totalOutBedAvg'], $row['weekOutBedAvg'], $row['chronoOutBedTime'], $row['strictness'], "outBedTimeRecommended", $obj);

    // send json obj to ESP32
    echo $json = json_encode($obj);

    function algorithm($avgTime, $avgWeekTime, $chronoTime, $strictness, $jsonKeyVal, $jsonObj) {
        global $calculatedCount;
        /// average time * strictness + chronotype time * inversed strictness
        $strictnessSum = strtotime($avgTime) * (1 - $strictness) + strtotime($chronoTime) * $strictness;
        // echo "strictness sum outcome = " . strftime('%H:%M:%M', $strictnessSum) . "<br>";
        $consistencyWeight = 0.5;
        $consistencySum = strtotime($avgWeekTime) * $consistencyWeight + $strictnessSum * (1-$consistencyWeight);
        // human-readable output
        // echo "strictness and consistency sum outcome = " . strftime('%H:%M:%M', $consistencySum) . "<br>";
        $jsonObj->$jsonKeyVal = strftime('%H:%M:%M', $consistencySum); // output in timeString
        // $jsonObj->$jsonKeyVal = $consistencySum; // output in seconds
        $calculatedCount += 1;
    }
    
    // update times in db
    if($calculatedCount == 2) {
        $arr = json_decode($json, true);
        $setRecommendedQuery = "UPDATE c_devices SET sunriseTime='" . $arr["outBedTimeRecommended"] . "', sunsetTime='" . $arr["inBedTimeRecommended"] . "' WHERE id='" . $deviceId . "'";
        // if ($mysqli->query($setRecommendedQuery) === TRUE) {
        //     echo "New record created successfully";
        // } else {
        //     echo "Error: " . $setRecommendedQuery . "<br>" . $mysqli->error;
        // }
    }
?>