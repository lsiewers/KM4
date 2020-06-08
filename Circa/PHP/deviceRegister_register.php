<meta content="text/html;charset=utf-8" http-equiv="Content-Type">
<meta content="utf-8" http-equiv="encoding">

<?php
    include 'connect_db.php';
    include 'checkparam.php';
    session_start();

    $deviceId = checkParam("deviceId", 999, FILTER_VALIDATE_INT);

    if($_SESSION['userId'] == NULL) {
        header("Location: user_form.php?feedback=" . urlencode('Session ended, login and try again please') .")");
    }

    echo $setDeviceQuery = "UPDATE c_devices SET userId='" . $_SESSION['userId'] . "' WHERE id='" . $deviceId . "'";

    if ($mysqli->query($setDeviceQuery) === TRUE) {
        echo "New record created successfully";
        header("Location: user_dashboard.php");
    } else {
        echo "Error: " . $setDeviceQuery . "<br>" . $mysqli->error;
    }
?>