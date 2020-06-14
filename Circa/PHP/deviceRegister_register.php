<?php
    include 'connect_db.php';
    include 'checkparam.php';
    session_start();

    $deviceId = checkParam("deviceId", 999, FILTER_VALIDATE_INT);

    // if session ended, go back to login page and try again
    if($_SESSION['userId'] == NULL) {
        header("Location: user_form.php?feedback=" . urlencode('Session ended, login and try again please') .")");
    }
    
    // Set this user's ID to device ID which is selected
    // (TO DO: user should fill in a token or password attached to the device too)
    echo $setDeviceQuery = "UPDATE c_devices SET userId='" . $_SESSION['userId'] . "' WHERE id='" . $deviceId . "'";

    if ($mysqli->query($setDeviceQuery) === TRUE) {
        echo "New record created successfully";
        header("Refresh:0"); // refresh page
    } else {
        echo "Error: " . $setDeviceQuery . "<br>" . $mysqli->error;
    }
?>