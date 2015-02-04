<?php
$height = 500;
$width = 500;
$im = imagecreatetruecolor($width, $height);
$white = imagecolorallocate($im, 255, 255, 255);
$blue = imagecolorallocate($im, 0, 0, 64);

imagefill($im, 0, 0, $blue);
imageline($im, 0, 0, $width, $height, $white);
imagestring($im, 4, 50, 150, 'test', $white);

Header('Content-type: image/jpeg');
imagejpeg($im);

//imagedestory($im);
?>
