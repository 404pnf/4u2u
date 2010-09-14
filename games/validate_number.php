<?php
header("Content-Type:image/png");
session_start();
srand((double)microtime()*1000000);
$im = imagecreate(62,20);
$black = ImageColorAllocate($im, 0,0,0);
$white = ImageColorAllocate($im, 255,255,255);

$gray = ImageColorAllocate($im, 200,200,200);
imagefill($im,68,30,$gray);
while(($authnum=rand()%100000)<10000);
imagestring($im, 5, 10, 3, $authnum, $white);
for($i=0;$i<200;$i++){
	$randcolor = ImageColorallocate($im,rand(0,255),rand(0,255),rand(0,255));
	imagesetpixel($im, rand()%70 , rand()%30 , $randcolor);
}
ImagePNG($im);
ImageDestroy($im);
$_SESSION['SESSION_VALIDATE_CODE'] = $authnum.'';?>