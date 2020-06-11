<?php
    include 'connect_db.php';
    include 'checkparam.php';
    session_start();

    $strictness = checkParam('strictness', 100, FILTER_VALIDATE_INT) / 100;

    if($_SESSION['userId'] == NULL) {
        header("Location: user_form.php?feedback=" . urlencode('Session ended, login and try again please') .")");
    }

    echo $setUserQuery = "UPDATE c_devices SET strictness='" . $strictness . "' WHERE userId='" . $_SESSION['userId'] . "'";

    if ($mysqli->query($setUserQuery) === TRUE) {
        // echo "New record created successfully";
        header("Location: user_dashboard.php");
        } else {
        echo "Error: " . $setUserQuery . "<br>" . $mysqli->error;
    }
?>