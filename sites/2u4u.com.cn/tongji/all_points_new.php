<?php

/*
** 统计用户充值的次数和充值的总积分 wzs 09/09/09
*/
header("Content-type:text/html;charset:utf-8");
require 'connect.php';
 
$ops = addslashes(trim($_GET[op]));

$end = strtotime("today");
$sqlx ="SELECT COUNT(*) as num FROM `topup` ";
if($ops == 'new'){
 $sqlx .= " WHERE time>=$end-86400*7 AND time<$end ";
}

$co = mysql_fetch_array(mysql_query($sqlx));
$times = $co[num];


$sql = "SELECT emno,count(emno) as num FROM `topup` ";
//$time_limit = " where  time<1268755200-86400*7";
//$sql .=$time_limit;
if($_GET['op']=='new'){
   	  $sql .= " WHERE time>=$end-86400*7 AND time<$end ";
   }
  $sql .= " GROUP BY emno ORDER BY num desc ";
  
 $result = @mysql_query($sql,$Connect) or die(mysql_error());

$books_num = mysql_num_rows($result);

$allponits = 0;
$i = 0;
while($row = mysql_fetch_array($result))
{ 
    
	$query = "SELECT field_erp_shuming_value as name ,field_erp_dingjia_value as price FROM `content_type_erp` WHERE field_erp_wuliaohao_value=".$row[emno];
		
	$res = @mysql_query($query) or die(mysql_error());
	

	
    $count = mysql_num_rows($res);     
	if($count>0){	
      $arr = mysql_fetch_array($res);
	  $allpoints += $arr['price']*$row['num'];
    }else{
         continue;
    }
    
	if($i<10){
		if(strlen($arr['name'])>2)
		   $info['name'][] = $arr['name'];
		else 
		   $info['name'][] =$row[emno];
		$info['num'][] = $row['num'];		
	}
    $i++;
}
if($ops=='new'){
   $new_word = "在过去的一周里，";
 }else{
   $date = date("Y-m-d",$end);
   $new_word = "截至 ".$date;
 }
?>

<div>

<?php echo $new_word ?> 用户在悠游网一共进行了<font color='red' size='10px'><?php echo $times ?></font>次充值,
充值的总码洋是<font color='red' size='10px'><?php echo $allpoints ?></font>元,充值的图书品种共<font color='red' size='10px'><?php echo $books_num?></font>种。<br>


<h2><p align='center'>充值前10名的图书</p></h2>
<table height=45 cellSpacing=0 borderColorDark=#ffffff width="50%"  
bgColor=#ffffff borderColorLight=#c0c0c0 border=1 align='center' >
<?php 
  for($j=0;$j<10;$j++){
?>
 <tr><td><?php echo $info['name'][$j] ?></td><td><?php echo $info['num'][$j] ?></td></tr>
<?php 
   }
?>
</table>
</div>
