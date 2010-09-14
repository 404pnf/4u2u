<?php include 'inc/check_login.php';?>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<title>2U4U单词大赛</title>
<link rel="stylesheet" type="text/css" media="screen" href="styles/styles.css" />
<style type="text/css">
body{background:url(images/bg.jpg) no-repeat left top;}
</style>
<script language="javascript">AC_FL_RunContent = 0;</script>
<script src="AC_RunActiveContent.js" language="javascript"></script>
</head>
<body bgcolor="#A81F26">
<div id="logo"><img src="images/logo.png"/></div>
<div id="user_info"><?php echo $user_name."(".$user_id.")，欢迎您！";?></div>
<div class="nav">
     <ul>
         <li><a href="words/index.php">单词背诵</a></li>
         <li><a href="llk/index.php">单词连连看游戏</a></li>
         <li><a href="sj/index.php">单词射击游戏</a></li>
         <li><a href="cj/index.php">抽奖</a></li>
         <li><a href="description.html">活动详情</a></li>
     </ul>
     <div class="footer"><span>外语教学与研究出版社版权所有 Copyright © 2008 2U4U.com.cn All Rights Reserved</span></div>
</div>
</body>
</html>
