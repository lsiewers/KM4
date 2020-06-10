<?php
    echo "
        <form method='POST'> 
            <input type='submit' name='deleteAccount' value='Delete your account'/>
            <small>This will also unregister your device and delete it's records. This cannot be undone</small>
        </form><br> 
    ";

    if(isset($_POST['deleteAccount'])) { 
        $deleteRecordsQuery = "DELETE FROM c_bedTimeRecords WHERE deviceId=". $row['deviceId'];
        if ($mysqli->query($deleteRecordsQuery) === TRUE) {
            echo "Records deleted";
            $deregisterQuery = "UPDATE c_devices SET userId=NULL WHERE id=". $row['deviceId'];
            echo "<br>";
            if ($mysqli->query($deregisterQuery) === TRUE) {
                echo "Device deregistered";
                $deleteAccountQuery = "DELETE FROM c_users WHERE id=". $row['userId'];
                if ($mysqli->query($deleteAccountQuery) === TRUE) {
                    header("Location: user_form.php?feedback=" . urlencode("Your account and data has been deleted"));
                } else echo "Error: " . $deleteAccountQuery . "<br>" . $mysqli->error;
            } else echo "Error: " . $deregisterQuery . "<br>" . $mysqli->error;
        } else echo "Error: " . $deleteRecordsQuery . "<br>" . $mysqli->error;
    } 
?>