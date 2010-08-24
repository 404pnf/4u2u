<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>图书充值次数查询</title>
</head>
<?php
require 'header.php';
require 'connect.php'; 
$array = time_limit('tp.time');
$time_limit = $array['time'];
$string = $array['string'];

$new_string = str_replace(" 至 ","--",substr($string,3));
//	$sql = "SELECT emno,count(emno) as num FROM `topup` WHERE time>UNIX_TIMESTAMP(now())-86400*30 GROUP BY emno ORDER BY num desc ";
    $sql ="SELECT tp.`emno`,count(emno) as num ,bi.`name`,bi.`price`,bi.`points`   
        FROM `topup` tp LEFT JOIN `book_info` bi ON bi.sku = tp.emno ";
	if($time_limit!='')
	  $sql .= "WHERE $time_limit";
	$sql = substr($sql,0,-4);
	$sql .= " GROUP BY tp.emno ORDER BY num desc ";     
        
	$result = @mysql_query($sql);


	while($row = mysql_fetch_array($result))
	{ 
		$name =strlen($row['name'])>2?$row['name']:$row[emno];
		$table.= "<tr><td class='row'>".$name."</td>";
		$table.="<td class='row'>".$row['num']."</td>";
		$table.="<td class='row'>".$row['price']."</td>";
		$table.="<td class='row'>".$row['points']."</td>";
		$table.= "</tr>";			
	} 

?>
<h2><p align='center'>外研社图书充值排行(<?php echo $new_string; ?>)</p></h2>
<div align="center">
<table id="mytable" cellspacing="0" >
<th scope="col">图书名称</th>
<th scope="col">充值次数</th>
<th scope="col">定价</th>
<th scope="col">积分</th>
<?php echo  $table;?>
</table>
</div>
</html>