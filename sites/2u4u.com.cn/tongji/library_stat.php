<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>电子图书馆积分统计</title>
</head>
<?php
/**
 *   统计电子图书馆的积分购买数据（消费总积分、图书名称、物料号、价格、次数）
 *   by @wzs 100310
 */

require 'header.php';
require 'connect-ebook.php';

$array = time_limit('yt.time');
$time_limit = $array['time'];
//$time_limit = " yt.time>1257004800 and yt.time<1271952000 and ";
$string = $array['string'];

$sql = "SELECT nd.title, ce.field_yuedu_pricebypoints_value points,yt.nid,yt.sku, count( yt.nid ) num
FROM `node` nd
LEFT JOIN `yuedu_transaction` yt ON nd.nid = yt.nid
LEFT JOIN `content_type_ebook` ce ON yt.nid = ce.nid
WHERE $time_limit yt.sku >0
AND ce.field_yuedu_pricebypoints_value >0 
GROUP BY yt.nid
ORDER BY num DESC ";

$rs = mysql_query($sql);
$i = 0;
$j = 0;

while($row = mysql_fetch_object($rs)){
//	$total += $row->points*$row->num;
	$table.= "<tr><td class='row'>".$row->title."</td>";
	$table.="<td class='row'>".$row->nid."</td>";
	$table.="<td class='row'>".$row->sku."</td>";
	$table.= "<td class='row'>".$row->num."</td>";
	$table.= "<td class='row'>".$row->points."</td>";
	$table.= "</tr>";
	$j +=$row->num;
	$i++;
}

$query = "SELECT SUM(yt.points) as total FROM `yuedu_transaction` yt  WHERE $time_limit yt.`sku`>0 AND yt.`points` >0  ";
$result = mysql_fetch_object(mysql_query($query));
$total = $result->total;

echo $string." 用户在电子图书馆消费的积分为<font size=12 color=red>".$total."</font>分，购买了<font size=12 color=red>".$j."</font>次涉及的图书共<font size=12 color=red>".$i."</font>种。<br>";
?>
<div align="center">
<table id="mytable" cellspacing="0" >
<th scope="col">书名</th>
<th scope="col">文章id</th>
<th scope="col">物料号</th>
<th scope="col">购买次数</th>
<th scope="col">价格</th></tr>
<?php echo  $table;?>
</table>
</div>
</html>
