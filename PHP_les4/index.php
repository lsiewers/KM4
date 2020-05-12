<h1>Users</h1>

<?php 
    include 'connect_db.php';
    
    $query = "SELECT * FROM users";

    if (!($result = $mysqli->query($query)))
    showerror($mysqli->errno,$mysqli->error);

    $row = $result->fetch_assoc();

    do {
    echo "name: " . $row["firstName"] . " " . $row["lastName"] . " <small>(a.k.a. " . $row["nickName"] . ")</small>" . "<br>" . "email: " . $row["email"] . "<br><br>";
    } while ($row = $result->fetch_assoc());
?>

