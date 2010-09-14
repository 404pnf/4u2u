<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<link href='table.css' rel='stylesheet' type='text/css' >
<title>每月网站新增注册人数</title>
</head>

<?php
require 'connect.php';
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
$table .= "</table>";
?>
<table id="mytable" cellspacing="0" >
<th scope="col">时间</th>
<th scope="col">新增注册数</th>
<?php echo  $table;?>
