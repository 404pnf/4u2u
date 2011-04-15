<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>用户注册数统计</title>
</head>
<?php
/**
 *   用户注册数统计（月份、人次）
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
$table = "<br>";
/*
$now = mktime(0, 0 , 0,date("m"),1,date("Y")); 
for($i=0;$i<12;$i++){
	$end = $now-$i*30*86400;
	$start = $now-($i+1)*30*86400;
	$time_limit = "`created`>".$start." AND `created`<".$end; 
    $sql = "SELECT count(uid) total  FROM `users` u WHERE ".$time_limit;
    $rs = mysql_query($sql);
    $row = mysql_fetch_object($rs);
    $table .= "<tr><td>".date("Y-m",$start)."</td>";  
    $table .= "<td>".$row->total."</td></tr>";  
    
    
}
*/
$now = mktime(0, 0 , 0,date("m"),1,date("Y")); 
for($i=0;$i<12;$i++){
	
	$end = $now-$i*30*86400;
	$start = $now-($i+1)*30*86400;
	
	if(date("m")>i) {
		$end = mktime(0, 0 , 0,date("m")-$i	,1,date("Y"));
	}
	if(date("m")>i+1) {
		$start = mktime(0, 0 , 0,date("m")-($i+1)	,1,date("Y"));
	}
	
	if(date("m")<=i) {
		$end = mktime(0, 0 , 0,date("m")+12-$i	,1,date("Y")-1);
	}
	if(date("m")<=i+1) {
		$start = mktime(0, 0 , 0,date("m")+12-($i+1)	,1,date("Y")-1);
	}
	
	$time_limit = "`created`>".$start." AND `created`<".$end; 
    $sql = "SELECT count(uid) total  FROM `users` u WHERE ".$time_limit;
    $rs = mysql_query($sql);
    $row = mysql_fetch_object($rs);
    $table .= "<tr><td>".date("Y-m",$start)."</td>";  
    $table .= "<td>".$row->total."</td></tr>";  
    
    
}

$table .= "</table>";
?>
<table id="mytable" cellspacing="0" >
<th scope="col">时间</th>
<th scope="col">新增注册数</th>
<?php echo  $table;?>


</html>
