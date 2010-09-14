<?php
include "inc/configs.php";
session_start();
game_mysql();
$is_admin=$_SESSION["is_admin"];
if(!$is_admin){
	header("location:$app_dir/admin_login.php");
	break;
}
?>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<title>管理员工作台</title>
</head>
<body>
<button onclick="window.print();">打印</button>
<div>
<h2>连连看总分前三名的用户</h2>
<table border="1" width="500">
	<tr><th>用户ID</th><th>用户名</th><th>总分</th></tr>
	<?php
	$sql="select user_id,user_name,sum(score) as score2 from user_games where game='llk' group by user_id order by score2 desc limit 0,3";
	$results=mysql_query($sql);
	while ($row=mysql_fetch_array($results)){
		echo "<tr><td>".$row["user_id"]."</td><td>".$row["user_name"]."</td><td>".$row["score2"]."</td></tr>";
	}
	?>
</table>
</div>
<div>
<h2>射击总分前三名的用户</h2>
<table border="1" width="500">
	<tr><th>用户ID</th><th>用户名</th><th>总分</th></tr>
	<?php
	$sql="select user_id,user_name,sum(score) as score2 from user_games where game='sj' group by user_id order by score2 desc limit 0,3";
	$results=mysql_query($sql);
	while ($row=mysql_fetch_array($results)){
		echo "<tr><td>".$row["user_id"]."</td><td>".$row["user_name"]."</td><td>".$row["score2"]."</td></tr>";
	}
	?>
</table>
</div>
<div>
<h2>单关前1名的用户</h2>
<table border="1" width="500">
	<tr><th>用户ID</th><th>用户名</th><th>分数</th><th>游戏</th><th>关</th></tr>
	<?php
	$sql="select user_id,user_name,level,max(score) as score2 from user_games where game='llk' group by level";
	$results=mysql_query($sql);
	while ($row=mysql_fetch_array($results)){
		echo "<tr><td>".$row["user_id"]."</td><td>".$row["user_name"]."</td><td>".$row["score2"]."</td><td>连连看</td><td>".$row["level"]."</td></tr>";
	}
	$sql="select user_id,user_name,level,max(score) as score2 from user_games where game='sj' group by level";
	$results=mysql_query($sql);
	while ($row=mysql_fetch_array($results)){
		echo "<tr><td>".$row["user_id"]."</td><td>".$row["user_name"]."</td><td>".$row["score2"]."</td><td>射击</td><td>".$row["level"]."</td></tr>";
	}
	?>
</table>
</div>
<div>
<h2>幸运奖获得者用户</h2>
<table border="1" width="500">
	<tr><th>用户ID</th><th>用户名</th><th>积分</th><th>抽取时间</th></tr>
	<?php
	$count=0;
	$sql="select user_id,user_name,create_time,send from user_awards order by create_time desc";
	$results=mysql_query($sql);
	while ($row=mysql_fetch_array($results)){
		$count++;
		echo "<tr><td>".$row["user_id"]."</td><td>".$row["user_name"]."</td><td>".$row["send"]."</td><td>".$row["create_time"]."</td></tr>";
	}
	?>
	<tr><td colspan="4">总共 <span style="color:red"><?php echo $count;?></span>人</td></tr>
</table>
</div>
</body>
</html>