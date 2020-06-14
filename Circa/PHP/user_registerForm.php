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
<h1>Register page</h1>
<!-- register form -->
<form action="user_register.php" method="get">
    <label for="email">Email</label><br>
    <input type="email" name="email" autocomplete placeholder="fill in your email" require/><br>
    <label for="password">Password</label><br>
    <input type="password" name="password" placeholder="fill in your password" require/><br><br>
    <label for="firstname">Your firstname</label><br>
    <input type="text" name="firstName" autocomplete placeholder="fill in your first name" require/><br>
    <label for="birthday">Your birthday</label><br>
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
    <div class="select-arrow">
        <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 306 306"><path d="M94.35 0l-35.7 35.7L175.95 153 58.65 270.3l35.7 35.7 153-153z"/></svg>
    </div>
    <br>
    <br>
    <input type="submit" value="Register">
</form>
<br>
<!-- Back to login page -->
<small><a href="user_form.php">< back to login</a></small>
</body>
</html>