<?php

header("Content-type: text/html; charset=utf-8");
include('db.php');


$order=$_POST['order'];
$sap=$_POST['sap'];
$current_date=date('Y-m-d');
$query="INSERT INTO `sap`.`orders` (`order`, `sap`, `created`)
        VALUES ('".$order."', '".$sap."', '".$current_date."')";
$result=mysql_query($query);

if(!$result)
{
 
 echo "<script>alert('录入失败,请检查是否重复录入!');history.back();</script>";
}else{
  echo "<script>alert('录入成功！');history.back();</script>";
}

?>
