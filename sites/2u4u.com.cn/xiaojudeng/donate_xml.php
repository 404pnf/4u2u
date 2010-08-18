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

echo '<?xml version="1.0" encoding="UTF-8" ?>';
echo '<xml>';

while($row = mysql_fetch_array($re)){
	
	$sql = "SELECT ut.uid,us.name FROM `userpoints_txn` ut LEFT JOIN `users` us ON ut.uid=us.uid WHERE ut.txn_id=$row[txn_id]-1";
	
	$aa = mysql_fetch_array(mysql_query($sql));

    $name = $aa[name];

    echo "<item>";	
    echo "<name>$name</name>";
	echo "<link>http://2u4u.com.cn/user/$aa[uid]</link>";
	echo "<time>".date("Y-m-d H:i:s",$row[time_stamp])."</time>";
	echo "<points>".$row[points]."</points>";
	echo "</item>";	

}
echo "</xml>";
?>