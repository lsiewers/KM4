<br>
<p>
    You can change the strictness of your perfect rhythm. <br>
    <small>Your bedtimes are depended on your chronotype and your recorded bedtimes</small>
    <small>If the strictness is high, your recommended bedtime will be more influenced by your chronotype</small><br>
    <small>If the strictness is low, your recommended bedtime will be more influenced by your average bedtime</small>
</p>

<form action="devicePreferences_update.php">
    <h3><label for="strictness">strictness</label></h3>
    <?= $row['strictness'] ?>
    <input name="strictness" type="range" value="<?= $row['strictness'] * 100 ?>" min="0" max="100"><br>
    <input type="submit" value="update">
</form>

<h3>Upcoming recommended bedtimes</h3>
<pre><?php 
    if($row["inBedTime"] == NULL) 
        echo "Get your device running first to get your recommended time";
    else 
        echo "In bed time (sunset): ". $row["inBedTime"] . "<br>Out bed time (sunrise):" .  $row["outBedTime"]; 
    ?>
</pre>

<h2>Records</h2>
<ul class="records">
<?php 
    
    $recordsQuery = "SELECT *
                    FROM c_bedTimeRecords
                    WHERE deviceId='" . $row['deviceId'] . "' 
                    ORDER BY outBedRecord DESC
                    LIMIT 25";

    if (!($result = $mysqli->query($recordsQuery)))
        showerror($mysqli->errno,$mysqli->error);

    $record = $result->fetch_assoc();

    if($record["inBedRecord"] == 0) {
        echo "no records yet";
    } else {
        do {
            echo "<li>"
                    .strftime("%A %d %B", strtotime($record["inBedRecord"])).
                    "
                    <ul>
                        <li><small>Went to bed at</small> <strong>".strftime("%H:%M:%S", strtotime($record["inBedRecord"]))."</strong>, ".showDiff($record["inBedRecord"],$record["inBedRecommended"])."</li>
                        <li><small>Went out of bed at</small> <strong>".strftime("%H:%M:%S", strtotime($record["outBedRecord"]))."</strong>, ".showDiff($record["outBedRecord"],$record["outBedRecommended"])."</li>
                    </ul> 
                    <form method='POST'> 
                        <input type='text' name='id' value='" . $record['id'] ."' hidden />
                        <input type='submit' name='deleteRecordBtn' value='Delete Record'/> 
                    </form> 
                </li>";
        } while ($record = $result->fetch_assoc());
    }


    if(isset($_POST['deleteRecordBtn'])) { 
        $deleteQuery = "DELETE FROM c_bedTimeRecords WHERE id=" . $_POST['id'];
        echo "<br>";
        if ($mysqli->query($deleteQuery) === TRUE) {
            echo "Record deleted";
        } else {
            echo "Error: " . $deleteQuery . "<br>" . $mysqli->error;
        }
    } 

    function showDiff($record, $recommended) {
        $diff = strtotime($record) - strtotime($recommended);
        $hours;
        $minutes;
        $seconds;
        $sortDiff;
        if ($diff < 0) {
            $hours = strftime("%H" ,($diff*-1));
            $minutes = strftime("%M" ,($diff*-1));
            $seconds = strftime("%S" ,($diff*-1));
            $sortDiff = "earlier";
        } else {
            $hours = strftime("%H" ,($diff));
            $minutes = strftime("%M" ,($diff));
            $seconds = strftime("%S" ,($diff));
            $sortDiff = "later";
        }
        if($hours > 0) $hours = (string)$hours . " hours ";
        else $hours = "";
        if($minutes > 0) $minutes = (string)$minutes . " min. ";
        else $minutes = "";
        if($seconds > 0) $seconds = (string)$seconds . " sec. ";
        else $seconds = "";
        return "<small class='".$sortDiff."'>" . $hours . $minutes . $seconds . " " . $sortDiff . " than recommended</small>";
    }
?>
</ul>

<style>
 .later { color: orange; }
 .earlier { color: turquoise; }
</style>