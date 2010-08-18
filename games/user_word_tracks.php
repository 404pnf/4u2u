<response success="true">
<?php
header("content-type:text/xml;charset=utf-8");
include 'inc/check_login.php';
game_mysql();
$cmd=$_REQUEST["cmd"];
$list_sql="select * from user_words where user_id='$user_id'";
if($cmd=="list"){
	$results=mysql_query($list_sql);
	while ($row=mysql_fetch_array($results)){
		echo "<item word=\"".$row["words"]."\" weight=\"".$row["weight"]."\"/>";
	}
}else if($cmd=="submit"){
	$xml=$_REQUEST["data"];
	$sxe = simplexml_load_string($xml);
	$items=$sxe->item;
	foreach($items as $node) {
		$word=$node["word"];
		$weight=$node["weight"];
		$select_sql="select * from user_words where user_id='$user_id' and words='$word'";
		$results=mysql_query($select_sql);
		$update_sql="insert into user_words(user_id,words,weight) values('$user_id','$word',$weight)";
		if(mysql_num_rows($results)>0){
			$update_sql="update user_words set weight=$weight where user_id='$user_id' and words='$word'";
		}
		mysql_query($update_sql);
	}
	$sql="select count(words) as c from user_words where user_id='$user_id'";
	$results=mysql_query($sql);
	while ($row=mysql_fetch_array($results)){
		echo "<words count=\"".$row["c"]."\"/>";
		break;
	}
}
mysql_close();
?>
</response>