<?php

function game_mysql(){
		$mysql_server_name="localhost"; //���ݿ����������
		$mysql_username="games"; // �������ݿ��û���
		$mysql_password="c9e7bb63fbfe1267db3975c2dd0c952f"; // �������ݿ�����
		$mysql_database="games"; // ���ݿ������
		
		$conn = @mysql_connect($mysql_server_name, $mysql_username,$mysql_password) 
		 or die("Couldn't select database.");
		 
    $Db = @mysql_select_db($mysql_database)
             or die("Couldn't select database.");
}

function session_mysql(){
		$DB_Server = "localhost";
		$DB_Username = "wzs";
		$DB_Password = "wuzhangshu";
		$DB_DBName = "2u4u";
		$Connect = @mysql_connect($DB_Server, $DB_Username, $DB_Password)
      or die("Couldn't connect.");
      
    $Db = @mysql_select_db($DB_DBName, $Connect)
         or die("Couldn't select database.");

     mysql_query("SET NAMES UTF8");
		
}

?>
