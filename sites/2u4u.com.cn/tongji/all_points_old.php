<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>充值积分统计</title>
</head>
<?php

/*
** 统计用户充值的次数和充值的总积分 wzs 09/09/09
* 
* modify by @wzs 100312
*/

require 'header.php';
require 'connect.php';

$array = time_limit('time');

$time_limit = $array['time'];
/*
$begin = mktime(0,0,0,11,1,2009);
$end = strtotime("today");
$time_limit = " time<".$begin." and ";
//$time_limit = " time>".$begin." and time<".$end." and ";
*/
$string = $array['string'];

$sqlx ="SELECT COUNT(*) as num FROM `topup` ";
if($time_limit!='')
   $sqlx .= "WHERE $time_limit";
$sqlx = substr($sqlx,0,-4);
$co = mysql_fetch_array(mysql_query($sqlx));
$times = $co[num];


$sql = "SELECT emno,count(emno) as num FROM `topup` ";
//$time_limit = " time<1268755200-86400*7 ";
if($time_limit!='')
  $sql .= "WHERE $time_limit";

$sql = substr($sql,0,-4);
$sql .= " GROUP BY emno ORDER BY num desc ";
//echo $sql;
$result = @mysql_query($sql);
echo $sql;
$books_num = mysql_num_rows($result);

$allponits = 0;
$i = 0;
while($row = mysql_fetch_array($result))
{ 
    
	$query = "SELECT field_erp_shuming_value as name ,field_erp_dingjia_value as price,field_erp_jianglijifen_value as jifen FROM `content_type_erp` WHERE field_erp_wuliaohao_value=".$row[emno];
//echo $query."<br>";
$res = @mysql_query($query);
	
    $count = mysql_num_rows($res);     
	if($count>0){	
      $arr = mysql_fetch_array($res);
	  $allpoints += $arr['price']*$row['num'];
	  $all_jifen += $arr['jifen']*$row['num'];
    }else{
         continue;
    }
    
	if($i<10){
		if(strlen($arr['name'])>2)
		   $info['name'][] = $arr['name'];
		else 
		   $info['name'][] =$row[emno];
		$info['num'][] = $row['num'];	
		$info['price'][] = $arr['price'];
		$info['jifen'][] = $arr['jifen'];			
	}
    $i++;
}
//var_dump($info);
for($j=0;$j<10;$j++){
	$table.= "<tr><td class='row'>".$info['name'][$j]."</td>";
	$table.="<td class='row'>".$info['num'][$j]."</td>";
	$table.="<td class='row'>".$info['price'][$j]."</td>";
	$table.="<td class='row'>".$info['jifen'][$j]."</td>";
	$table.= "</tr>";	
}
//var_dump($table);
?>

<div>

<?php echo $string ?> 用户在悠游网一共进行了<font color='red' size='10px'><?php echo $times ?></font>次充值。
充值的总码洋是<font color='red' size='10px'><?php echo $allpoints ?></font>元。充值的总积分是<font color='red' size='10px'><?php echo $all_jifen ?></font>分。充值的图书品种共<font color='red' size='10px'><?php echo $books_num?></font>种。<br>
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
