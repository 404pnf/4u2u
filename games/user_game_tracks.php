<response success="true">
<?php
header("content-type:text/xml");
include 'inc/check_login.php';
game_mysql();
$cmd=$_REQUEST["cmd"];
if($cmd=="list_top"){
	$sql="select user_id,user_name,sum(score) as score2 from user_games where game='".$_REQUEST["game"]."' group by user_id order by score2 desc limit 0,8";
	$results=mysql_query($sql);
	while ($row=mysql_fetch_array($results)){
		echo "<item user_id='".$row["user_id"]."' user_name='".$row["user_name"]."' score='".$row["score2"]."'/>";
	}
}else if($cmd=="list_level_score"){
	$game=$_REQUEST["game"];
	$level=$_REQUEST["level"];
	$sql="select * from user_games where user_id='$user_id' and game='$game' and level=$level";
	$results=mysql_query($sql);
	$levelScore=-1;
	if(mysql_num_rows($results)>0){
		while ($row=mysql_fetch_array($results)){
			$levelScore=$row["score"];
			break;
		}
	}
	$sql="select sum(score) as score2 from user_games where user_id='$user_id' and game='$game'";
	$results2=mysql_query($sql);
	$row2=mysql_fetch_array($results2);
	
	echo "<result success='true' score='".$levelScore."' total='".$row2["score2"]."'/>";
}else if($cmd=="submit"){
	/*从客户端读入xml的str*/
	$game=$_REQUEST["game"];
	$level=$_REQUEST["level"];
	$score=$_REQUEST["score"];
	$sel_sql="select * from user_games where user_id='$user_id' and game='$game' and level=$level";
	$results=mysql_query($sel_sql);
	$update_sql="insert into user_games(user_id,user_name,game,level,score) values('$user_id','$user_name','$game','$level',$score)";
	if(mysql_num_rows($results)>0){
		$update_sql="update user_games set score=$score where user_id='$user_id' and game='$game' and level=$level";
	}
	mysql_query($update_sql);
}
mysql_close();
?>
</response>