<?php
header("Content-Type: image/png");
$inputText = $_POST["res"];
$length = strlen(utf8_decode($inputText));
$im = @imagecreate(200, 200)
    or die("Невозможно создать поток изображения");
$background_color = imagecolorallocate($im, 0, 0, 0);
$text_color = imagecolorallocate($im, 233, 14, 91);
$sizeText = 60;
if($length <= 6) {
	
} else {
	$calc = $length - 6;
	$sizeText -= $calc*2.5;
}
imagettftext ($im, $sizeText, -45 , 10 , 25 , $text_color, "ANTQUAI.ttf", $inputText);
imagepng($im);
imagepng($im, "test.png");
imagedestroy($im);
?>