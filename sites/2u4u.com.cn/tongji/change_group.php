<?php
require 'connect.php';
$sql = "SELECT nid FROM `node_access` WHERE realm LIKE 'og_subscriber' ORDER BY nid DESC";
$result = mysql_query($sql);
$i = 0;
while($row = mysql_fetch_object($result)){

	$query = "SELECT nid FROM `node_access` WHERE nid =".$row->nid." AND realm LIKE 'og_public'";
	
	$re = mysql_query($query);
	
	if(mysql_num_rows($re)>0){
       continue;
	}else{
		$new_sql = "INSERT INTO `node_access`(nid,realm,grant_view) VALUES (".$row->nid.",'og_public','1') ";
	
		$res = mysql_query($new_sql);

		if($res)
		  $i++;		
	}
}
echo "共增加".$i."个";


?>