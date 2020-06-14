<!doctype html>

<html lang="en">
<head>
    <meta content="text/html;charset=utf-8" http-equiv="Content-Type">
    <meta content="utf-8" http-equiv="encoding">

<link rel="stylesheet" href="https://use.typekit.net/ire0dpa.css">
<link rel="stylesheet" href="css/stylesheet.css"/>
<link rel="icon" type="image/png" href="icons/sun.png" />

  <title>CIRCA personal sun</title>
  <meta name="author" content="Luuk Siewers">

</head>

<body>
<h1>Dashboard</h1>

<?php
    include 'connect_db.php';
    session_start();

    // if session ended, go to login page and try again
    if($_SESSION['userId'] == NULL) {
        header("Location: user_form.php?feedback=" . urlencode('Session ended, login and try again please'));
    }

    // get user and device data
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
        // Give a personal welcome
        echo "<br><strong> Hello, " . $row['firstName'] . "</strong>";
        if($row['deviceId'] == NULL) {
            // Show device register form if there are no devices selected yet
            echo "<br>No device connected to this user";
            include "deviceRegister_form.php";
        } else {
            // Show device data if one is registered
            include "devicePreferences_form.php";
            include "deviceRegister_deregister.php";
            // delete user button (TO DO: should also be available when no devices are registered)
            include "user_delete.php";
        }
    }
?>

<a href="user_logout.php">Log out</a>
</body>
</html>