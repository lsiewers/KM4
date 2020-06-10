<?php
    echo "
        <form method='POST'> 
            <input type='submit' name='deregisterDeviceBtn' value='Deregister device and delete its records'/>
            <small>This cannot be undone</small>
        </form><br> 
    ";

    if(isset($_POST['deregisterDeviceBtn'])) { 
        $deleteRecordsQuery = "DELETE FROM c_bedTimeRecords WHERE deviceId=". $row['deviceId'];
        if ($mysqli->query($deleteRecordsQuery) === TRUE) {
            echo "Records deleted";
            $deregisterQuery = "UPDATE c_devices SET userId=NULL, strictness='0.5' WHERE id=". $row['deviceId'];
            echo "<br>";
            if ($mysqli->query($deregisterQuery) === TRUE) {
                echo "Device deregistered";
                header("Location: user_dashboard.php"); // refresh page
            } else {
                echo "Error: " . $deregisterQuery . "<br>" . $mysqli->error;
            }
        } else {
            echo "Error: " . $deregisterQuery . "<br>" . $mysqli->error;
        }
    } 
?>