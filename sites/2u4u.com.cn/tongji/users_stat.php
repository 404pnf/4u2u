<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>用户注册数统计</title>
</head>
<?php
/**
 *   统计电子图书馆的积分购买数据（消费总积分、图书名称、物料号、价格、次数）
 *   by @wzs 100310
 */

require 'header.php';
require 'connect.php';

$array = time_limit('u.created');
$time_limit = $array['time'];
$string = $array['string'];
$time_limit = substr($time_limit,0,-4);
$sql = "SELECT count(uid) total  FROM `users` u WHERE ".$time_limit;
$rs = mysql_query($sql);
$row = mysql_fetch_object($rs);

echo $string." 悠游网注册用户为<font size=12 color=red>".$row->total."</font><br>";
?>

</html>