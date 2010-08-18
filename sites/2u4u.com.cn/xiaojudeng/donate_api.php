<?php
header("content-type:text/html;charset:utf-8");
$DB_Server = "localhost";
$DB_Username = "wuzs";
$DB_Password = "wuzhangshu";
$DB_DBName = "2u4u";
$Connect = @mysql_connect($DB_Server, $DB_Username, $DB_Password)
or die("Couldn't connect.");
$Db = @mysql_select_db($DB_DBName, $Connect)
or die("Couldn't select database.");
 mysql_query("SET NAMES UTF8");
 


$sql1 = "SELECT points FROM `userpoints` WHERE uid='726'";

$point = mysql_fetch_array(mysql_query($sql1));

$arr = array();
$arr[] =$point[points];
$arr[] = 'http://2u4u.com.cn/sites/2u4u.com.cn/xiaojudeng/donate_list.php';

$query = "SELECT txn_id,time_stamp,points FROM `userpoints_txn` WHERE uid='726' AND points>0 ORDER BY time_stamp DESC";
$re = mysql_query($query);

while($row = mysql_fetch_array($re)){
	
	$sql = "SELECT ut.uid,us.name FROM `userpoints_txn` ut LEFT JOIN `users` us ON ut.uid=us.uid WHERE ut.txn_id=$row[txn_id]-1";
	$aa = mysql_fetch_array(mysql_query($sql));
    $name = $aa[name];
    
    $ss = $name.","."http://2u4u.com.cn/user/".$aa[uid].",".date("Y-m-d H:i:s",$row[time_stamp]).",".$row[points];
    $arr[] = $ss;
}

	if (function_exists('json_encode')){
		
	  $new_arr = json_encode($arr);
	  
	}else{
	
	 include("JSON.php");
	 $json = new Services_JSON();
	 $new_arr =$json->encode($arr);
	 
  }
	
     echo "var data =".$new_arr;

?>


