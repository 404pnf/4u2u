<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>日语mp3的积分统计</title>
</head>
<?php

/*
** 统计日语mp3下载次数    wzs 09/12/17
* 
*   加上时间的限制，统计每周的记录  wzs 10/03/01
*/

require 'header.php';
require 'connect-shop.php';

$array = time_limit('uo.created');
$time_limit = $array['time'];
$string = $array['string'];

$query = "SELECT sum(up.price*up.qty) as points
FROM `uc_order_products` up
LEFT JOIN `uc_orders` uo ON up.order_id = uo.order_id
LEFT JOIN `term_node` tn ON tn.nid = up.nid
WHERE  $time_limit tn.tid = 1974
AND uo.order_status
IN (
'payment_received', 'completed'
)
AND uo.uid >1";

$total = mysql_fetch_object(mysql_query($query));

$all_points = round($total->points,2);

$sql = "SELECT up.title,up.price,count( up.nid ) AS num
FROM `uc_order_products` up
LEFT JOIN `uc_orders` uo ON up.order_id = uo.order_id
LEFT JOIN `term_node` tn ON tn.nid = up.nid
WHERE  $time_limit tn.tid = 1974
AND uo.order_status
IN (
'payment_received', 'completed'
)
AND uo.uid >1
GROUP BY up.nid
ORDER BY num DESC";
$rs = mysql_query($sql);
$i = 0;
$j = 0;
//echo $sql;
while($row = mysql_fetch_object($rs)){
	
		$table.= "<tr><td class='row'>".$row->title."</td>";
		$table.="<td class='row'>".(int)$row->price."</td>";
		$table.= "<td class='row'>".$row->num."</td>";
		$table.= "</tr>";
		$i +=$row->num;
		$j++;
 }
?>
<?php echo $string;?>日语mp3一共下载了<font color='red' size='10px'><?php echo $i ?></font>次，
用户花费的积分<font color='red' size='10px'><?php echo $all_points ?></font>点。
涉及的mp3种类<font color='red' size='10px'><?php echo $j ?></font>个。
<h2><p align='center'>日语mp3下载排行</p></h2>
<div align="center">
<table id="mytable" cellspacing="0" >
<th scope="col">书名</th>
<th scope="col">价格</th>
<th scope="col">购买次数</th></tr>
<?php echo  $table;?>
</table>
</div>
