<?php
include "inc/configs.php";
/* ****Read me**********************
这是登登录拟页面
***********************************/
session_start();
$msg="";
if(isset($_REQUEST["user_id"])&&isset($_REQUEST["password"])&&isset($_REQUEST["code"])){
	$uid=$_REQUEST["user_id"];
	$password=$_REQUEST["password"];
	$code=$_REQUEST["code"];
	if($code != $_SESSION['SESSION_VALIDATE_CODE'] ){
		$msg="验证码错误！";
	}else{
		$_SESSION['SESSION_VALIDATE_CODE']='__%%%%____';
		if($uid==$admin_id&&$password==$admin_password){
			$_SESSION['is_login']=TRUE;
			$_SESSION['user_id']=$admin_id;
			$_SESSION['user_name']='管理员';
			$_SESSION['is_admin']=TRUE;
			header("location:$app_dir/admin.php");
		}
	}
}
?>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<title>login.success</title>
</head>
<body>
<form action="admin_login.php" method="post">
	<ul style="list-style:none;">
	<li>
	<label>用户名:</label><input name="user_id"/>
	</li>
	<li>
	<label>密&nbsp;&nbsp;&nbsp;&nbsp;码:</label><input type="password" name="password"/>
	</li>
	<li>
	<label>验证码:</label><input name="code"/>
	</li>
	<li>
	<img src="validate_number.php"/>
	</li>
	<li>
	<button type="submit">登录</button>
	</li>
	<li>
	<span style="color:red"><?php echo $msg;?></span>
	</li>
</form>
</body>
</html>