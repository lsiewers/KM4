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
<?php
    include 'connect_db.php';
    include 'checkparam.php';

    $password = checkParam("password", 75, false); // number between 0 - 30
    $email = checkParam("email", 99, FILTER_VALIDATE_EMAIL); // number between 0 - 999
    $birthdate = date("Y-m-d H:i:s", strtotime($_GET['birthdate'])); // birthday before today
    $chronotype = checkParam("chronotype", 75, false);
    $firstName = checkParam("firstName", 75, false);

    $query = "SELECT * FROM c_users WHERE email='" . $email . "'";

    // check for errors in insert query
    if (!($result = $mysqli->query($query))) {
        echo showerror($mysqli->errno,$mysqli->error);
    } else {
        if($result->fetch_assoc() == NULL) {
            // if user doesn't exist yet, add it with form information
            echo $setUserQuery = "INSERT INTO c_users (id, firstName, birthdate, email, password, chronotype) VALUES (NULL, '" . $firstName . "', '" . $birthdate . "', '" . $email . "', '" . $password . "', '" . $chronotype . "')";

            if ($mysqli->query($setUserQuery) === TRUE) {
                echo "New record created successfully";
                if($_SESSION['userId'] == NULL) {
                    // if succeeded, go back to login page
                    header("Location: user_form.php?feedback=" . urlencode('Register completed! Now you can log in with your new account.') .")");
                }
              } else {
                echo "Error: " . $setUserQuery . "<br>" . $mysqli->error;
            }
        //         header('Location: user_account.php');
        } else {
            // account already exists based on email
            echo "An account with this email exists already!";
        }
    }
?>
</body>
</html>