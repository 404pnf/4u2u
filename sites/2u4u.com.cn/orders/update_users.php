<?php

/**
 *   将作文大赛的用户迁移至悠游网数据库中
 */
require 'connect.php';
set_time_limit(0);
//$sql = "SELECT * FROM `users_zuowen` ORDER BY uid ";
$sql = "SELECT * FROM `users_zuowen` ";

$rs = mysql_query($sql);

$user_fields = user_fields();
$i = 0;
while($row = mysql_fetch_assoc($rs)){

  if(!user_exits($row['name'])){
      user_save($user_fields,user_insert($row));

  }else{
  	$user_info = user_insert(user_info_change($row));
  	user_save($user_fields,$user_info);
  }
	$i++;
}
echo $i."个用户";

function user_save($fields,$arr){	
	$query = "	INSERT INTO `users` (".implode(",",$fields).") VALUES (".implode(",",$arr).") ";

	$rs = mysql_query($query);	
	if($rs) 
	    return true;
	 else 
	    return false;
	
}

function user_info_change($arr){
	
	$row = $arr;
	$num = user_exits($arr['name']);
	$row['name'] = $arr['name']."_".$arr['uid']."_zuowen"."_".$num;
	$row['mail'] = $row['name']."@example.com";
	return $row;
	
}

function user_insert($row){	
	
	foreach($row as $key=> $value){
		if(strlen($value)>1)
		     $row[$key] = "'$value'";  
		if($value == '')
		     $row[$key] = "''";      
	}	
	$row['uid'] = "''";   
		return $row;
}


function user_exits($name){
	$sql = "SELECT COUNT(*) num FROM `users` WHERE name='".$name."'";
	$rs = mysql_fetch_object(mysql_query($sql));
	if($rs->num>0)
	    return $rs->num;
	else 
	    return false;	
}




function user_fields(){
    static $fields;
	$result = mysql_query('SELECT * FROM `users` WHERE uid = 1');
    if($field = mysql_fetch_assoc($result)) {
       $fields = array_keys($field);
    }
 return $fields;
}
?>