<?php
/* ****Read me**********************
在这里返回用户登录信息
***********************************/
include 'inc/check_login.php';
$login_result="false";
if($is_login){
	$login_result="true";
}
header("Content-Type:text/xml");
echo("<response success='$login_result'><userid>$user_id</userid><username>$user_name</username></response>");
?>
