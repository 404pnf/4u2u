<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>电子图书馆积分统计</title>
</head>
<?php

/*
** 统计用户充值的次数和充值的总积分 wzs 09/09/09
* 
* modify by @wzs 100312
*/

require 'header.php';
require 'connect.php';

$array = time_limit('tp.time');

$time_limit = $array['time'];
$string = $array['string'];


$query = "SELECT SUM(points) total_points,SUM(price) total_price FROM `topup` tp " ;
if($time_limit!='')
  $query .= "WHERE $time_limit";
$query = substr($query,0,-4);
$res = mysql_fetch_object(mysql_query($query));
$total_points = $res->total_points;
$total_price = $res->total_price;

$sql = "SELECT tp.`emno`,count(tp.`emno`) as num ,bi.`name`,bi.`price`,bi.`points`   
        FROM `topup` tp LEFT JOIN `book_info` bi ON bi.sku = tp.emno ";

if($time_limit!='')
  $sql .= "WHERE $time_limit";
$sql = substr($sql,0,-4);
$sql .= " GROUP BY tp.emno ORDER BY num desc ";
$result = @mysql_query($sql);
$i = 0;
while($row = mysql_fetch_array($result))
{ 
	$total_times += $row[num]; 
  	if($i<10){		
		$name =strlen($row['name'])>2?$row['name']:$row[emno];
		$table.= "<tr><td class='row'>".$name."</td>";
		$table.="<td class='row'>".$row['num']."</td>";
		$table.="<td class='row'>".$row['price']."</td>";
		$table.="<td class='row'>".$row['points']."</td>";
		$table.= "</tr>";			
	}
    $i++;
}

?>

<div>

<?php echo $string ?> 用户在悠游网一共进行了<font color='red' size='10px'><?php echo $total_times ?></font>次充值。
充值的总码洋是<font color='red' size='10px'><?php echo $total_price ?></font>元。充值的总积分是<font color='red' size='10px'><?php echo $total_points ?></font>分。充值的图书品种共<font color='red' size='10px'><?php echo $i?></font>种。<br>
<h2><p align='center'>充值前10名的图书</p></h2>
<div align="center">
<table id="mytable" cellspacing="0" >
<th scope="col">图书名称</th>
<th scope="col">充值次数</th>
<th scope="col">定价</th>
<th scope="col">积分</th>
<?php echo  $table;?>
</table>
</div>
