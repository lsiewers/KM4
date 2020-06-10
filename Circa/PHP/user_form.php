<!doctype html>

<html lang="en">
<head>
    <meta content="text/html;charset=utf-8" http-equiv="Content-Type">
    <meta content="utf-8" http-equiv="encoding">

  <title>CIRCA personal sun</title>
  <meta name="author" content="Luuk Siewers">

</head>

<body>
<h1>Login page</h1>
<!-- https://home.hku.nl/~ton.markus/kern_iad/index.php?les=6&content=7 -->
<form action="user_login.php" method="get">
    <input type="email" name="email" placeholder="fill in your email" required/><br>
    <input type="password" name="password" placeholder="fill in your password" required/><br>
    <input type="submit" value="Login">
</form>

<?php
    include 'checkparam.php';
    echo urldecode(checkParam("feedback", 100, false, false, false)); 
?>

<p>Not registered yet?</p>
<a href="user_registerForm.php">Register</a>
</body>
</html>