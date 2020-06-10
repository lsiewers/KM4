<?php
    include '../connect_db.php';
    include '../checkparam.php';

    $deviceId = checkParam('deviceId', 999, FILTER_VALIDATE_INT);
    $data = json_decode(checkParam('data', 999, false), true);

    $setDataQuery = "INSERT INTO c_bedTimeRecords (id, deviceId, inBedRecord, outBedRecord, InBedRecommended, OutBedRecommended) 
        VALUES (NULL," . $deviceId . ",'" . $data['inBedTimeRecord'] . "','" . $data['outBedTimeRecord'] . "','" . $data['inBedTimeRecommended'] . "','" . $data['outBedTimeRecommended'] . "')";

    // success callback, so ESP32 knows
    if ($mysqli->query($setDataQuery) === TRUE) {
        // echo $data['inBedTimeRecord']
        echo "true";
    } else {
        echo "Error: " . $setDataQuery . "<br>" . $mysqli->error;
    }
?>