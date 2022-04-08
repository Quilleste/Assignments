<?php
//from 6 to 30 symbols, can't end or befin with "."
//regex - ^([A-z0-9]\.?){5,29}[A-z0-9]{1}@otp\.khpi\.ua$
if (isset($_POST["email"])) { 
    $toCheck = $_POST["email"];
	echo "Email input is correct!"; 
    if(preg_match("~^([A-z0-9]\.?){5,29}[A-z0-9]{1}@otp\.khpi\.ua$~", $toCheck)) {	
		echo json_encode(array('stat' => "Email input is correct!")); 
	} else echo json_encode(array('stat' => "Email is incorrect! Please, recheck it and try again.")); 
} else echo json_encode(array('stat' => "Email field can't be empty."));

?>