<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<link href='table.css' rel='stylesheet' type='text/css' >
<title>邀请注册奖励积分排行</title>
</head>
<?php

require 'connect.php';
$sql = "SELECT `name`,ut.`uid`, count( ut.uid ) num, sum( `points` ) points
FROM `userpoints_txn` ut 
LEFT JOIN `users` u on u.uid=ut.uid
WHERE `description` LIKE '通过邀请用户获取的积分%'
GROUP BY ut.`uid` 
ORDER BY num DESC";

$rs = mysql_query($sql);

while($row = mysql_fetch_object($rs)){
	
	$query = "SELECT sum(c.`points`) total
				FROM `userpoints_txn` c
				WHERE c.`description` LIKE '图书验证码积分充值.奖励推荐' AND uid=".$row->uid;
//echo $query."<br>";
	$result = mysql_fetch_object(mysql_query($query));	
	$points = '';
//var_dump($result->total);
        $points = $row->points + $result->total;	
	$table .= "<tr><td>".$row->name."</td>";  
	$table .= "<td>".$row->num."</td>";  
    $table .= "<td>".$points."</td></tr>";  
	
}

$table .= "</table>";



?>
<table id="mytable" cellspacing="0" >
<th scope="col">用户名</th>
<th scope="col">邀请人数</th>
<th scope="col">获得的奖励积分（含充值奖励）</th>
<?php echo  $table;?>
