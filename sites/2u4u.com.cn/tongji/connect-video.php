<?php
$DB_Server = "localhost";
$DB_Username = "wzs";
$DB_Password = "wuzhangshu";
$DB_DBName = "video";
$Connect = @mysql_connect($DB_Server, $DB_Username, $DB_Password)
or die("Couldn't connect.");
$Db = @mysql_select_db($DB_DBName, $Connect)
or die("Couldn't select database.");
 mysql_query("SET NAMES UTF8");
?>
