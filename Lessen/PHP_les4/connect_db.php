<?php
    include db_login.php;

    /* Open a connection */
    $mysqli = new mysqli("$db_host","$db_user","$db_pass","$db_name");

    /* check connection */
    if ($mysqli->connect_errno) {
        echo "Failed to connect to MySQL: (" . $mysqli->connect_errno() . ") " . $mysqli->connect_error();
        exit();
    } 

    // /* check if server is alive */
    // if ($mysqli->ping()) { 
    //     echo "connected!";
    // }

    function showerror($error,$errornr) {
        die("Error (" . $errornr . ") " . $error);
    } 
?> 