
<?php
    include 'connect_db.php';

    // Session ID: vgbhbu2t0meogddunc4pq046dd14p9rdupseo9heir1rhppqv620

    if (isset($_GET["session_id"])) { // als sessie id is meegestuurd in URL
        $session_id = htmlspecialchars($_GET["session_id"]); // Sanitizen
        session_id($session_id); // zet sessie id naar id uit URL

        session_start();
        
        if (isset($_SESSION["productId"]) && $_SESSION["productId"]!=0) {
            $celsius = $_GET['celsius'];
            $productId = $_SESSION["productId"];
            
            $query = 
                "INSERT INTO temperatures (id, productId, celsius, dateTime) VALUES (NULL, " . $productId . ", " . $celsius . ", CURRENT_TIME())";
            if (!($result = $mysqli->query($query)))
            showerror($mysqli->errno,$mysqli->error);

            echo $_SESSION["productId"];
        } else {
            echo "Sessie van productID bestaat niet";
        }
    }
        
        
?>