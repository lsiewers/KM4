<!doctype html>

<html lang="en">
<head>
    <meta content="text/html;charset=utf-8" http-equiv="Content-Type">
    <meta content="utf-8" http-equiv="encoding">

  <title>CIRCA personal sun</title>
  <meta name="author" content="Luuk Siewers">

</head>

<body>
<h1>Dashboard</h1>

<?php
    include 'connect_db.php';
    session_start();

    if($_SESSION['userId'] == NULL) {
        header("Location: user_form.php?feedback=" . urlencode('Session ended, login and try again please'));
    }

    $query = "SELECT 
                    u.firstName AS firstName,
                    u.id AS userId,
                    d.id AS deviceId,
                    d.strictness AS strictness,
                    d.sunriseTime AS outBedTime,
                    d.sunsetTime AS inBedTime
                FROM c_users u
                LEFT JOIN c_devices d ON (userId='".$_SESSION['userId']."')
                WHERE u.id='" . $_SESSION['userId'] . "' LIMIT 1";
    
    if (!($result = $mysqli->query($query))) {
        showerror($mysqli->errno,$mysqli->error);
    } else {
        $row = $result->fetch_assoc();
        echo "<br> Hello, " . $row['firstName'];
        if($row['deviceId'] == NULL) {
            echo "<br>No device connected to this user";
            include "deviceRegister_form.php";
        } else {
            include "devicePreferences_form.php";
            include "deviceRegister_deregister.php";
            include "user_delete.php";
        }
    }

    // $getUserDevicesQuery = "SELECT * FROM c_devices WHERE userId=" . $_SESSION['userId'] . " LIMIT 1";

    // if (!($result = $mysqli->query($getUserDevicesQuery))) {
    //     showerror($mysqli->errno,$mysqli->error);
    // } else {
    //     $deviceRow = $result->fetch_assoc();
    //     
    // }
?>

<a href="user_logout.php">Log out</a>
</body>
</html>