<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>多媒体课堂积分统计</title>
</head>
<?php
/**
 *   统计多媒体课堂的积分购买数据（消费总积分、视频名称、文章Id、价格、次数）
 *   by @wzs 100311
 */

require 'header.php';
require 'connect-video.php';

$array = time_limit('st.time');
$time_limit = $array['time'];

//$time_limit = " st.time>1257004800 and st.time<1271952000 and ";

$string = $array['string'];

$sql = "SELECT nd.title, cs.field_shipin_points_value points,st.nid, count( st.nid ) num
FROM `node` nd
LEFT JOIN `shipin_transaction` st ON nd.nid = st.nid
LEFT JOIN `content_type_shipin` cs ON cs.nid = st.nid
WHERE $time_limit st.nid >0
AND cs.field_shipin_points_value >0 
GROUP BY st.nid
ORDER BY num DESC ";

$rs = mysql_query($sql);
$i = 0;
$j = 0;

while($row = mysql_fetch_object($rs)){
//	$total += $row->points*$row->num;
	$table.= "<tr><td class='row'>".$row->title."</td>";
	$table.="<td class='row'>".$row->nid."</td>";
	$table.= "<td class='row'>".$row->num."</td>";
	$table.= "<td class='row'>".$row->points."</td>";
	$table.= "</tr>";
	//$j +=$row->num;
	$i++;
}

$query = "SELECT SUM(st.points) as total,count(*) as num FROM `shipin_transaction` st WHERE $time_limit st.`uid`>0 AND st.`points` >0 ";
$result = mysql_fetch_object(mysql_query($query));
$total = $result->total;
$buy_num = $result->num;

echo $string." 用户在多媒体频道消费的积分为<font size=12 color=red>".$total."</font>分，购买了<font size=12 color=red>".$buy_num."</font>次，涉及的视频共<font size=12 color=red>".$i."</font>个。<br>";
?>
<div align="center">
<table id="mytable" cellspacing="0" >
<th scope="col">视频名称</th>
<th scope="col">文章id</th>
<th scope="col">购买次数</th>
<th scope="col">价格</th></tr>
<?php echo  $table;?>
</table>
</div>
