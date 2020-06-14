<?php
    // Remove device buttton
    echo "
        <form method='POST'> 
            <input type='submit' class='delete' name='deregisterDeviceBtn' value='Deregister device and delete its records'/>
            <small>This cannot be undone</small>
        </form>
    ";

    // If remove device button pressed
    if(isset($_POST['deregisterDeviceBtn'])) { 
        // Delete all records of that device
        $deleteRecordsQuery = "DELETE FROM c_bedTimeRecords WHERE deviceId=". $row['deviceId'];
        if ($mysqli->query($deleteRecordsQuery) === TRUE) {
            echo "Records deleted";
            // Reset all settings of device and remove user ID
            $deregisterQuery = "UPDATE c_devices SET userId=NULL, strictness='0.5' WHERE id=". $row['deviceId'];
            echo "<br>";
            if ($mysqli->query($deregisterQuery) === TRUE) {
                echo "Device deregistered";
                header("Refresh:0"); // refresh page
            } else {
                echo "Error: " . $deregisterQuery . "<br>" . $mysqli->error;
            }
        } else {
            echo "Error: " . $deregisterQuery . "<br>" . $mysqli->error;
        }
    } 
?>