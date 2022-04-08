<?php
	if(is_file("result.txt")) {
		$handle = fopen("result.txt", "r");
		if($handle) {
			$arr = array();
			while (($buffer = fgets($handle)) !== false) {
				$arr[] = $buffer;
			}
			fclose($handle);
			$msg = "";
			foreach($arr as $val) {
				$msg .= $val;
			}
			echo $msg;
		} else echo "File exists, but can't be opened!";
	} else echo "File does not exist!";
?>