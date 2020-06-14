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
        session_start();

        $password = checkParam("password", 30, false); // string between 0 - 30
        $email = checkParam("email", 99, FILTER_VALIDATE_EMAIL); // string between 0 - 999

        // If not all fields are filled (should work with input:require only)
        if($password == NULL || $email == NULL) {
            header('Location: user_form.php?feedback=' . urlencode("Make sure to fill both fields"));
        }

        // Select user with login credentials
        echo $query = "SELECT * FROM c_users WHERE email='" . $email . "' AND password='" . $password . "' LIMIT 1";

        // check for errors in insert query
        if (!($result = $mysqli->query($query))) {
            showerror($mysqli->errno,$mysqli->error);
        } else {
            $row = $result->fetch_assoc();
            if($row["id"] != NULL) {
                // If user exists with these credentials
                $_SESSION["userId"]= $row["id"];
                header('Location: user_dashboard.php');
            } else {
                // If user doesn't exists with these credentials
                header('Location: user_form.php?feedback=' . urlencode("Whoops, are you sure your email/password are right?"));
            }
        }
    ?>
</body>
</html>
