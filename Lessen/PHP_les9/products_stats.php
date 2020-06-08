<?php 
    include 'connect_db.php';

    $getProductsQuery = "SELECT * FROM products";

    // check for errors in insert query
    if (!($getProductsResults = $mysqli->query($getProductsQuery))) {
        showerror($mysqli->errno,$mysqli->error);
    } else {
        $product = $getProductsResults->fetch_assoc();
        do {
            $getTemperatureDataQuery = "SELECT COUNT(celsius) as measuresLength, AVG(celsius) as averageTemperature FROM temperatures WHERE productId = " . $product["id"];
            if (!($getTemperatureDataResults = $mysqli->query($getTemperatureDataQuery))) {
                showerror($mysqli->errno,$mysqli->error);
            } else {
                $temperatureData = $getTemperatureDataResults->fetch_assoc();
                echo $product["id"] . ": <br> - total measurements: " . $temperatureData["measuresLength"] . "<br> - average temp: " . $temperatureData["averageTemperature"] . "<br><br>";
            }
        } while ($product = $getProductsResults->fetch_assoc());

        
    }
?>