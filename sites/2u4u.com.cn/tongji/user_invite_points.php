<?php

require 'connect.php';
$sql = "SELECT `name`,ut.`uid`, count( ut.uid ) num, sum( `points` ) points
FROM `userpoints_txn` ut 
LEFT JOIN `users` u on u.uid=ut.uid
WHERE `description` LIKE '通过邀请用户获取的积分%'
GROUP BY ut.`uid` 
ORDER BY num DESC";

$rs = mysql_query($sql);
$i = 1;
while($row = mysql_fetch_object($rs)){
	
	$table .= "<li><div class='t1'>".$i."</div>";  
	$table .= "<div class='t2'>".$row->name."</div>";  
    $table .= "<div class='t3'>".$row->num."</div></li>";  
    $i++;
	
}

echo $table;
?>
