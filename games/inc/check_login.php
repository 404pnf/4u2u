<?php
@session_start();

include 'configs.php';
$is_login=$_SESSION['is_login'];
$sid = $_GET['sid'];


if(!$is_login&&$sid!=''){

session_mysql();
 
$sql = "SELECT u.uid,u.name FROM `users` u INNER JOIN `sessions` s ON u.uid = s.uid WHERE s.sid = '$sid'";

$rs = mysql_fetch_object(mysql_query($sql));

if($rs && $rs->uid>0){
	$_SESSION['user_id']=$rs->uid;
	$_SESSION['user_name']=$rs->name;
	$_SESSION['is_login'] = true;

}else
	 header("location:http://2u4u.com.cn/game/link");
}

if(!$is_login&&$sid==''){	
	 header("location:http://2u4u.com.cn/game/link");

}
	
$user_id=$_SESSION['user_id'];
$user_name=$_SESSION['user_name'];
$is_login=$_SESSION['is_login'];

?>