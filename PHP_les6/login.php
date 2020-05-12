
<?php
    include 'connect_db.php';
    session_start();
    echo "<br> <small>Session ID: " . session_id() . "</small><br>";

    $password = checkParam("password", 30); // number between 0 - 30
    $productId = checkParam("id", 999); // number between 0 - 999

    function checkParam($name, $range) {
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

    $_SESSION["productId"] = $productId;

    $query = "SELECT * FROM products WHERE id=" . $_SESSION["productId"] . " AND password='" . $password . "'";

    // check for errors in insert query
    if (!($result = $mysqli->query($query))) {
        showerror($mysqli->errno,$mysqli->error);
    } else {
        echo "<br> Logged in! <br><br>";

        // show all temperatures of product 
        $query = "SELECT * FROM temperatures WHERE productId=" . $_SESSION["productId"];
        // check for errors in insert query
        if (!($result = $mysqli->query($query))) {
            showerror($mysqli->errno,$mysqli->error);
        } else {
            $row = $result->fetch_assoc();
            do {
                echo "<li>" . $row["celsius"] . "&#8451; <small>at " . $row["dateTime"] . "</small></li>";
            } while ($row = $result->fetch_assoc());
        }
    }
?>