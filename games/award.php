<?php
header("content-type:text/xml");
include 'inc/check_login.php';
game_mysql();
$cmd=$_REQUEST["cmd"];
if($cmd=="list_top"){
	//总分前3位的用户
	echo "<response success='true'>";
	echo "<top1>";
	$sql="select user_id,user_name,sum(score) as score2 from user_games where game='llk' group by user_id order by score2 desc limit 0,3";
	$results=mysql_query($sql);
	while ($row=mysql_fetch_array($results)){
		echo "<item game='llk' user_id='".$row["user_id"]."' user_name='".$row["user_name"]."' score='".$row["score2"]."'/>";
	}
	$sql="select user_id,user_name,sum(score) as score2 from user_games where game='sj' group by user_id order by score2 desc limit 0,3";
	$results=mysql_query($sql);
	while ($row=mysql_fetch_array($results)){
		echo "<item game='sj' user_id='".$row["user_id"]."' user_name='".$row["user_name"]."' score='".$row["score2"]."'/>";
	}
	echo "</top1>";
	//用户自己的得分对比
	echo "<top1self>";
	$sql="select sum(score) as score2,game from user_games where user_id='$user_id' group by game";
	$results=mysql_query($sql);
	while ($row=mysql_fetch_array($results)){
		echo "<item score='".$row["score2"]."' game='".$row["game"]."'/>";
	}
	echo "</top1self>";
	echo "<top2>";
	$sql="select user_id,user_name,level,max(score) as score2 from user_games where game='sj' group by level";
	$results=mysql_query($sql);
	while ($row=mysql_fetch_array($results)){
		echo "<item user_id='".$row["user_id"]."' user_name='".$row["user_name"]."' score='".$row["score2"]."' game='sj' level='".$row["level"]."'/>";
	}
	$sql="select user_id,user_name,level,max(score) as score2 from user_games where game='llk' group by level";
	$results=mysql_query($sql);
	while ($row=mysql_fetch_array($results)){
		echo "<item user_id='".$row["user_id"]."' user_name='".$row["user_name"]."' score='".$row["score2"]."' game='llk' level='".$row["level"]."'/>";
	}
	echo "</top2>";
	echo "<top2self>";
	$sql="select level,max(score) as score2 from user_games where game='sj' and user_id='$user_id' group by level";
	$results=mysql_query($sql);
	while ($row=mysql_fetch_array($results)){
		echo "<item score='".$row["score2"]."' game='sj' level='".$row["level"]."'/>";
	}
	$sql="select level,max(score) as score2 from user_games where game='llk' and user_id='$user_id' group by level";
	$results=mysql_query($sql);
	while ($row=mysql_fetch_array($results)){
		echo "<item score='".$row["score2"]."' game='llk' level='".$row["level"]."'/>";
	}
	echo "</top2self>";
	echo "</response>";
}else if($cmd=="award"){
	//抽奖操作
	if(!isset($_REQUEST["code"])){
		echo("<response succuss='false' msg='请输入验证码！'/>");
	}else{
		$code=$_REQUEST["code"];
		if($code != $_SESSION['SESSION_VALIDATE_CODE'] ){
			echo("<response succuss='false' msg='请输入正确的验证码！'/>");
		}else{
			$_SESSION['SESSION_VALIDATE_CODE']='__%%%%____';
			//判断是否有
			if($award_open){
				$score=0;
				$sql="select max(score) as score2 from user_games where user_id='$user_id'";
				$results=mysql_query($sql);
				while ($row=mysql_fetch_array($results)){
					$score=$row['score2'];
				}
				if($score>=$awards_min_score){
					$seed=rand(0,100);
					if($seed>=40){
						$isGet=FALSE;
						$seed=rand(0,60);
						foreach ($awards_levels as $v){
							if($seed <= ($v["rate"])&&$seed>0){
								//检索该积分段的获奖人数
								$ucount=0;
								$sql="select count(user_id) as ucount from user_awards where send=".($v['score']);
								$results=mysql_query($sql);
								while ($row=mysql_fetch_array($results)){
									$ucount=$row['ucount'];
									break;
								}
								if($ucount>=$v['max']){
									echo "<response succuss='false' msg='谢谢您的参与！'/>";
								}else{
									//先向数据库中插入获奖情况
									$sql="insert into user_awards(user_id,user_name,send,create_time) values('$user_id','$user_name',".($v['score']).",now())";
									mysql_query($sql);
									echo "<response succuss='true' msg='恭喜您获得幸运积分".($v['score'])."'/>";
								}
								$isGet=TRUE;
								break;
							}
						}
						if($isGet==FALSE){
							echo "<response succuss='false' msg='谢谢您的参与！'/>";
						}
					}else{
						echo "<response succuss='false' msg='谢谢您的参与！'/>";
					}
				}else{
					echo "<response succuss='false' msg='请先玩玩游戏再来抽吧！'/>";
				}
			}else{
				echo "<response succuss='false' msg='谢谢您的参与！'/>";
			}
		}
	}
	
}
mysql_close();
?>