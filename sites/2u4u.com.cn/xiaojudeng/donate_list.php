<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="zh-hans" lang="zh-hans" dir="ltr">

<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  <title>捐赠积分用户列表 | 悠游</title>
  <link type="text/css" rel="stylesheet" media="all" href="/sites/2u4u.com.cn/files/css/donate.css" />
</head>
<?php
$DB_Server = "localhost";
$DB_Username = "wuzs";
$DB_Password = "wuzhangshu";
$DB_DBName = "2u4u";
$Connect = @mysql_connect($DB_Server, $DB_Username, $DB_Password)
or die("Couldn't connect.");
$Db = @mysql_select_db($DB_DBName, $Connect)
or die("Couldn't select database.");
 mysql_query("SET NAMES UTF8");

 
$query = "SELECT txn_id,time_stamp,points FROM `userpoints_txn` WHERE uid='726' AND points>0 ORDER BY time_stamp DESC";
$re = mysql_query($query);

echo '<div id="donate_list">';
echo '<ul id="donate_title">感谢以下用户参加单词大赛，给百度小桔灯帐号捐赠积分</ul>';

    echo "<ul id='donate_ul'>";
    echo "<li id='donate_li'>用户名</li>";
	echo "<li id='donate_li'>捐赠积分</li>";
    echo "</ul>";
    
   $name = array();
   $points = array();
   $uid = array();
   
while($row = mysql_fetch_array($re)){
	
	$sql = "SELECT ut.uid,us.name FROM `userpoints_txn` ut LEFT JOIN `users` us ON ut.uid=us.uid WHERE ut.txn_id=$row[txn_id]-1";
	
	$aa = mysql_fetch_array(mysql_query($sql));


 if(in_array($aa[uid],$uid)){
 	
  $points[$aa[uid]] += $row[points];


}else{
	$name[$aa[uid]] = $aa[name];
  $points[$aa[uid]] = $row[points];
  $uid[] = $aa[uid];
	}
  
  }

foreach($uid as $value){
	
	  echo "<ul id='donate_ul'>";
    echo "<li id='donate_li'><a href='http://2u4u.com.cn/user/$value'>$name[$value]</a></li>";
	  echo "<li id='donate_li'>".$points[$value]."</li>";
    echo "</ul>";
	
	}


echo "</div>";
?>
