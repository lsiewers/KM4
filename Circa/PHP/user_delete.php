<?php
    echo "
        <form method='POST'> 
            <input type='submit' class='delete' name='deleteAccount' value='Delete your account'/>
            <small>This will also unregister your device and delete it's records. This cannot be undone</small>
        </form><br> 
    ";

    // if delete account button pressed
    if(isset($_POST['deleteAccount'])) { 
        // delete all records attached to device of user
        $deleteRecordsQuery = "DELETE FROM c_bedTimeRecords WHERE deviceId=". $row['deviceId'];
        if ($mysqli->query($deleteRecordsQuery) === TRUE) {
            echo "Records deleted";
            // Reset device data and remove user ID
            $deregisterQuery = "UPDATE c_devices SET userId=NULL, stricness='0.5' WHERE id=". $row['deviceId'];
            echo "<br>";
            if ($mysqli->query($deregisterQuery) === TRUE) {
                echo "Device deregistered";
                // (TO DO: check if any device is registered. If not, just remove account)
                // Delete user account
                $deleteAccountQuery = "DELETE FROM c_users WHERE id=". $row['userId'];
                if ($mysqli->query($deleteAccountQuery) === TRUE) {
                    // Go to login page again
                    header("Location: user_form.php?feedback=" . urlencode("Your account and data has been deleted"));
                } else echo "Error: " . $deleteAccountQuery . "<br>" . $mysqli->error;
            } else echo "Error: " . $deregisterQuery . "<br>" . $mysqli->error;
        } else echo "Error: " . $deleteRecordsQuery . "<br>" . $mysqli->error;
    } 
?>