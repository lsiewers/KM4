<!doctype html>

<html lang="en">
<head>
    <meta content="text/html;charset=utf-8" http-equiv="Content-Type">
    <meta content="utf-8" http-equiv="encoding">

  <title>CIRCA personal sun</title>
  <meta name="author" content="Luuk Siewers">

</head>

<body>
<h1>Register page</h1>

<form action="user_register.php" method="get">
    <input type="email" name="email" autocomplete placeholder="fill in your email" require/><br>
    <input type="password" name="password" placeholder="fill in your password" require/><br><br>
    <input type="firstName" name="firstName" autocomplete placeholder="fill in your first name" require/><br>
    <input type="date" name="birthdate" autocomplete placeholder="fill in your birthday" require/><br>
    <h2>Choose your chronotype</h2>
    <p>Your chronotype tells you what to do when. This helps to find the perfect bedtimes for you.</p>
    <a target="_blank" href="https://www.youtube.com/watch?v=rmbv7yZ2buE">Watch the TED Talk about chonotypes</a><br>
    <small>Don't know what your chronotype is? <a target="_blank" href="https://thepowerofwhenquiz.com/">Take the quiz!</a></small>
    <br><br>
    <select name="chronotype">
        <option value="dolphin">Dolphin</option>
        <option value="bear">Bear</option>
        <option value="lion">Lion</option>
        <option value="wolf">Wolf</option>
    </select> 
    <br>
    <br>
    <input type="submit" value="Register">
</form>

<a href="user_form.php">< back to login</a>
</body>
</html>