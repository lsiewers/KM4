
<?php
    include 'connect_db.php';
    session_start();
    echo "<br> <small>Session ID: " . session_id() . "</small><br>";

    $password = checkParam("password", 30, FILTER_VALIDATE_INT); // number between 0 - 30
    $email = checkParam("email", 99, FILTER_VALIDATE_EMAIL); // number between 0 - 999

    function checkParam($name, $range, $filterType) {
        // if (filter_var($_GET[]))
        if (!isset($_GET[$name]) || empty($_GET[$name])) {
            echo "param value $name is empty";
            exit(); 
        // } else if (!filter_var($_GET[$name], FILTER_VALIDATE_INT)) {
            // echo "param value $name is not an integet";
            // exit(); 
        } else if ($_GET[$name] > $range) { 
            echo "param value $name is out of range";
            exit(); 
        } else {
            return $_GET[$name];
        }
    }

    echo $query = "SELECT * FROM users WHERE email='" . $email . "' AND password='" . $password . "'";

    // check for errors in insert query
    if (!($result = $mysqli->query($query))) {
        showerror($mysqli->errno,$mysqli->error);
    } else {
        $row = $result->fetch_assoc();
        $_SESSION["userId"]= $row["id"];
        echo "<br> Logged in! <br><br>" .  $_SESSION["userId"] . " " . $row["id"];
        if($_SESSION["userId"] != NULL) {
            header('Location: user_dashboard.php');
        }
    }
?>