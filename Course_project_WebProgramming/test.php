<form method="post" action="test_2.php">
<?
$count = 5; 
$html_msg;
	for($i = 0; $i < ($count-2); $i++) {
		$html_msg .= '<input type="checkbox" name="vals[]" value="val' . ($i+1) . '">';
		$html_msg .= '<label for="val' . ($i+1) . '"> Graph for val' . ($i+1) . '</label><br>';
	}
	$html_msg .= "</p>";
	echo $html_msg;
?>
<p><input value="btn" id="submit_btn" type="submit"/></p>
</form> 