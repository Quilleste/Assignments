<?php

if (isset($_POST["email"])) { 

	setcookie("usrname", $_POST["email"], time()+3600); 
}

?>