<!doctype html>

<html lang="en">
<head>
    <meta content="text/html;charset=utf-8" http-equiv="Content-Type">
    <meta content="utf-8" http-equiv="encoding">

  <title>CIRCA personal sun</title>
  <meta name="author" content="Luuk Siewers">

</head>

<body>
    <?php
        include 'connect_db.php';
        include 'checkparam.php';
        session_start();

        $password = checkParam("password", 30, false); // number between 0 - 30
        $email = checkParam("email", 99, FILTER_VALIDATE_EMAIL); // number between 0 - 999

        echo $query = "SELECT * FROM c_users WHERE email='" . $email . "' AND password='" . $password . "' LIMIT 1";

        // check for errors in insert query
        if (!($result = $mysqli->query($query))) {
            showerror($mysqli->errno,$mysqli->error);
        } else {
            $row = $result->fetch_assoc();
            $_SESSION["userId"]= $row["id"];
            echo "<br> Logged in! <br><br>" .  $_SESSION["userId"] . " " . $row["id"];
            if($_SESSION["userId"] != NULL) {
                header('Location: user_dashboard.php');
            } else {
                echo "Your account doesn't exist";
            }
        }
    ?>
</body>
</html>
