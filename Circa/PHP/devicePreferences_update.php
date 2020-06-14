<?php
    include 'connect_db.php';
    include 'checkparam.php';
    session_start();

    $strictness = checkParam('strictness', 100, FILTER_VALIDATE_INT) / 100;

    // If session was ended, redirect to login page and try it again
    if($_SESSION['userId'] == NULL) {
        header("Location: user_form.php?feedback=" . urlencode('Session ended, login and try again please') .")");
    }
    
    // Update strictness setting
    echo $setUserQuery = "UPDATE c_devices SET strictness='" . $strictness . "' WHERE userId='" . $_SESSION['userId'] . "'";

    if ($mysqli->query($setUserQuery) === TRUE) {
        // If completed, refresh page to see changes
        header("Refresh:0");
        } else {
        echo "Error: " . $setUserQuery . "<br>" . $mysqli->error;
    }
?>