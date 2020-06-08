<meta content="text/html;charset=utf-8" http-equiv="Content-Type">
<meta content="utf-8" http-equiv="encoding">

<h1>Account page</h1>

<?php
    include 'connect_db.php';
    session_start();

    if($_SESSION['userId'] == NULL) {
        header("Location: user_form.php?feedback=" . urlencode('Session ended, login and try again please'));
    }

    $getUserQuery = "SELECT * FROM c_users WHERE id=" . $_SESSION['userId'] . " LIMIT 1";
    
    if (!($result = $mysqli->query($getUserQuery))) {
        showerror($mysqli->errno,$mysqli->error);
    } else {
        $userRow = $result->fetch_assoc();
        echo "<br> Hello, " . $userRow['firstName'];
    }

    $getUserDevicesQuery = "SELECT * FROM c_devices WHERE userId=" . $_SESSION['userId'] . " LIMIT 1";

    if (!($result = $mysqli->query($getUserDevicesQuery))) {
        showerror($mysqli->errno,$mysqli->error);
    } else {
        $deviceRow = $result->fetch_assoc();
        if($deviceRow == NULL) {
            echo "<br>No device connected to this user";
            include "deviceRegister_form.php";
        } else {
            include "devicePreferences_form.php";
        }
    }
?>

<a href="user_logout.php">Log out</a>