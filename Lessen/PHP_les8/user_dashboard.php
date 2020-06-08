<?php 
    include 'connect_db.php';
    
    session_start();
    
    $query = "SELECT u.nickname as userName, p.location as productId FROM users u LEFT JOIN products p ON (p.userId = u.id) WHERE u.id =" . $_SESSION["userId"];

    if (!($result = $mysqli->query($query)))
    showerror($mysqli->errno,$mysqli->error);

    $row = $result->fetch_assoc();

    do {
    echo $row["userName"] . " has a lovely product in the " . $row["productId"] . "<br>";
    } while ($row = $result->fetch_assoc());
?>

