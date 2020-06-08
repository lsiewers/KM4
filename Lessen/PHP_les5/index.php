<!-- <h1>Users</h1> -->

<?php 
    include 'connect_db.php';

    // real stuff
    $celsius = checkParam("celsius", 30); // number between 0 - 30
    $productId = checkParam("productId", 999); // number between 0 - 999

    function checkParam($name, $range) {
        if (!isset($_GET[$name]) || empty($_GET[$name])) {
            echo "param value $name is empty";
            exit(); 
        } else if (!filter_var($_GET[$name], FILTER_VALIDATE_INT)) {
            echo "param value $name is not an integet";
            exit(); 
        } else if ($_GET[$name] > $range) { 
            echo "param value $name is out of range";
            exit(); 
        } else {
            return $_GET[$name];
        }
    }

    // insert query
    echo "<br> SUCCESS <br>";
    echo $query = 
        "INSERT INTO temperatures (id, productId, celsius, dateTime) VALUES (NULL, " . $productId . ", " . $celsius . ", CURRENT_TIME())";

    // check for errors in insert query
    if (!($result = $mysqli->query($query)))
    showerror($mysqli->errno,$mysqli->error);

    // display results of select query
    // $row = $result->fetch_assoc();

    // do {
    // echo "name: " . $row["firstName"] . " " . $row["lastName"] . " <small>(a.k.a. " . $row["nickName"] . ")</small>" . "<br>" . "email: " . $row["email"] . "<br><br>";
    // } while ($row = $result->fetch_assoc());
?>

