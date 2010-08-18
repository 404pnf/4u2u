<?php
/* ****Read me**********************
这是登登录拟页面
***********************************/
session_start();

$_SESSION['is_login']=TRUE;
$_SESSION['user_id']='huangx';
$_SESSION['user_name']='黄馨';
?>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<title>login.success</title>
<link rel="stylesheet" type="text/css" media="screen" href="styles/styles.css" />
</head>
<body bgcolor="#A81F26">
登录成功！
</body>
</html>