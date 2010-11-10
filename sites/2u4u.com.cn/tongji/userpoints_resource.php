<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>用户积分来源分析</title>
</head>
<?php

/*
** 
* modify by @wzs 101109
*/

require 'header.php';
require 'connect.php';

$array = time_limit('time_stamp');

$time_limit = $array['time'];
$string = $array['string'];


$query ="SELECT `description`,sum( `points` ) num 
		FROM `userpoints_txn`
        ";
if($time_limit!='')
  $query .= "WHERE $time_limit";
  
$query = substr($query,0,-4);
$query .= "  AND  `points` >0
		AND `points` <1000  GROUP BY `description` ORDER BY num DESC";
//echo $query;
$result = @mysql_query($query);
$i = 0;
while($row = mysql_fetch_object($result))
{ 
	$total_points += $row->num; 
  	if($i<20){		
		$table.= "<tr><td class='row'>".$row->description."</td>";
		$table.="<td class='row'>".$row->num."</td>";
		$table.= "</tr>";			
	}
    $i++;
}

?>

<div>

<?php echo $string ?> 用户在悠游网获得的总积分是<font color='red' size='10px'><?php echo $total_points ?></font>分。
<h2><p align='center'>用户积分来源</p></h2>
<div align="center">
<table id="mytable" cellspacing="0" >
<th scope="col">积分来源</th>
<th scope="col">积分总计</th>
<?php echo  $table;?>
</table>
</div>
</div>
</html>

