<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>电子图书馆积分统计</title>
</head>
<?php

/*
** 统计大礼包的兑换次数、兑换的总积分和总码洋   wzs 09/12/15
*/
require 'header.php';
require 'connect-shop.php';

$array = time_limit('uo.created');

$time_limit = $array['time'];
$string = $array['string'];



$query = "SELECT sum(up.qty*up.cost) mayang,sum(up.qty*up.price)  points
FROM `uc_order_products` up 
LEFT JOIN `uc_orders` uo ON up.order_id=uo.order_id 
WHERE $time_limit uo.order_status IN ('payment_received','completed') 
AND up.price >500 AND uo.order_id>56 AND uo.uid>1";
$total = mysql_fetch_object(mysql_query($query));

$mayang_all = round($total->mayang,2);
$points_all = round($total->points,2);

$sql = "SELECT up.nid,up.title,count( up.nid ) AS num,up.qty,up.price FROM `uc_order_products` up LEFT JOIN `uc_orders` uo ON up.order_id=uo.order_id WHERE $time_limit uo.order_status IN ('payment_received','completed') AND up.price >500 AND uo.order_id>56 AND uo.uid>1 GROUP BY nid
ORDER BY num DESC ";


$rs = mysql_query($sql);
$i = 0;
while($row = mysql_fetch_object($rs)){

	$times +=$row->num; 
	$table.= "<tr><td class='row'>".$row->title."</td>";
	$table.="<td class='row'>".$row->nid."</td>";
	$table.= "<td class='row'>".$row->num."</td>";
	$table.= "</tr>";
}

?>

<?php echo $string ?> 用户在悠游网一共兑换了<font color='red' size='10px'><?php echo $times ?></font>个礼包。
消费的积分<font color='red' size='10px'><?php echo $points_all ?></font>点。
兑换的码洋<font color='red' size='10px'><?php echo $mayang_all ?></font>元
<h2><p align='center'>大礼包兑换排行</p></h2>
<div align="center">
<table id="mytable" cellspacing="0" >
<th scope="col">大礼包名称</th>
<th scope="col">id号</th>
<th scope="col">购买次数</th>
<?php echo  $table;?>
</table>
</div>
</html>
