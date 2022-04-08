<?php
$fname =  $_POST['fname'];
$lname = $_POST['lname'];

if( ( $fname != null ) and ( $lname != null ) )
{
  setcookie( "fname", $fname, time() + 36000 );
  setcookie( "lname", $lname, time() + 36000 );
}

echo "post fname ".$_POST['fname']."<BR>";
echo "post lname ". $_POST['lname']."<BR>";
echo "cookie ". $_COOKIE['fname']."<BR>";
echo "cookie ". $_COOKIE['lname']."<BR>";
?>

<html>
<head>
<title>Untitled Document</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</head>

<body>

<form method="post" action="hidden.php">
<p>First Name: <input type="text" maxlength="40" name="fname" id="fname" value="<?php if(isset($_COOKIE['fname'])){echo $_COOKIE['fname'];} else {echo "";} ?>"/></p>
<p>Last Name: <input type="text" maxlength="40" name="lname" id="lname" value="<?php if(isset($_COOKIE['lname'])){echo $_COOKIE['lname'];} else {echo "";} ?>"/></p

<input type="submit" name="submit" value="Send">
<p><input id="btn" type="submit" value="Send"/></p>
</form>
</body>
</html>