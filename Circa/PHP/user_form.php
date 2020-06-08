<h1>Login page</h1>
<!-- https://home.hku.nl/~ton.markus/kern_iad/index.php?les=6&content=7 -->
<form action="user_login.php" method="get">
    <input type="email" name="email" placeholder="fill in your email" require/><br>
    <input type="password" name="password" placeholder="fill in your password" require/><br>
    <input type="submit" value="Submit">
</form>

<?php
    include 'checkparam.php';

    echo urldecode(checkParam("feedback", 100, false, false, false)); 
?>

<p>Not registered yet?</p>
<a href="user_registerForm.php">Register</a>