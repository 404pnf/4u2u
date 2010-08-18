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
require 'connect.php';

$array = time_limit('uo.created');


$time_limit = $array['time'];
/*
$begin = mktime(0,0,0,11,1,2009);
$end = strtotime("today");
$time_limit = "uo.created>".$begin." and uo.created<".$end." and ";
*/

$string = $array['string'];
 

$sql = "SELECT up.* FROM `uc_order_products` up LEFT JOIN `uc_orders` uo ON up.order_id=uo.order_id WHERE $time_limit  uo.order_status IN ('payment_received','completed') AND up.price >500 AND uo.order_id>56 AND uo.uid>1";
//echo $sql;
$rs = mysql_query($sql);
$i = 0;
while($row = mysql_fetch_object($rs)){
	
		$total += $row->qty*$row->price;
		$i++;

	$new_sql = "SELECT cp.`field_product_mayang_value` mayang FROM `content_type_product` cp WHERE cp.nid=$row->nid AND field_product_mayang_value>0 ORDER BY cp.vid DESC LIMIT 1";

	$res = @mysql_fetch_object(mysql_query($new_sql));


    if($res->mayang>0)
            $mayang += $row->qty*$res->mayang;
}

?>

<div>

<?php echo $string ?> 用户在悠游网一共兑换了<font color='red' size='10px'><?php echo $i ?></font>个礼包,
消费积分<font color='red' size='10px'><?php echo $total ?></font>点,兑换码洋<font color='red' size='10px'><?php echo $mayang ?></font>元。

<?php 

$query = "SELECT up.title, up.nid,count( up.nid ) AS num
FROM `uc_order_products` up LEFT JOIN `uc_orders` uo
ON up.order_id=uo.order_id WHERE $time_limit uo.order_status IN ('payment_received','completed') AND up.price >500 AND uo.order_id>56 AND uo.uid>1
GROUP BY nid
ORDER BY num DESC ";
//echo $query;
$result = mysql_query($query);

while($arr = mysql_fetch_object($result)){
 	$table.= "<tr><td class='row'>".$arr->title."</td>";
	$table.="<td class='row'>".$arr->nid."</td>";
	$table.= "<td class='row'>".$arr->num."</td>";
	$table.= "</tr>";

} 
?>
<h2><p align='center'>大礼包兑换排行</p></h2>
<div align="center">
<table id="mytable" cellspacing="0" >
<th scope="col">大礼包名称</th>
<th scope="col">id号</th>
<th scope="col">购买次数</th>
</tr>
<?php echo  $table;?>
</table>

</div>

