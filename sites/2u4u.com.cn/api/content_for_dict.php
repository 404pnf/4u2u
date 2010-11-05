<?php
$type = $_GET['type'];
require 'connect.php';
require 'class.inc';

if($type=='answer'){
	
	$sql = "SELECT n.nid ,td.tid,td.name,n.title,n.created 
			 FROM node n
			 INNER JOIN term_node tn ON n.vid = tn.vid
			 LEFT JOIN term_data td ON tn.tid = td.tid
			 WHERE (n.type in ('best_answer')) AND (n.status <> 0) order by n.created desc limit 7";
	
	$rs = mysql_query($sql);
	while($row = mysql_fetch_object($rs)){
		
		$arr[$row->nid] = array("title"=>$row->title,
								"tid"=>$row->tid,
								"term_name"=>$row->name	
		);
		
	  }
}


if($type=='news'){
	
	$sql = "SELECT `nid`,`title` 
			FROM 2u4u.`node`
			WHERE `status` <> 0 AND `type` ='news'
			ORDER BY `created` DESC LIMIT 5";
	
	$rs = mysql_query($sql);
	while($row = mysql_fetch_object($rs)){
		
		$arr['nodes'][] = array("node"=> array("title"=>"<a href='http://2u4u.com.cn/nid/".$row->nid."'>".$row->title."</a>")
		);
		
	  }
}


if($type=='daily_sentence'){

	$sql = "SELECT n.`nid` , n.`title` , nr.`body` 
			FROM 2u4u.`node` n
			LEFT JOIN 2u4u.`node_revisions` nr ON nr.nid = n.nid
			AND nr.vid = n.vid
			WHERE `status` <>0
			AND `type` = 'dict_daily_sentence'
			ORDER BY `created` DESC  LIMIT 1";
	
	$rs = mysql_query($sql);
	while($row = mysql_fetch_object($rs)){
		
		$arr['nodes'][] = array("node"=> array("title"=>$row->title,
		                                       "body"=>$row->body )
		);
		
	  }





}




echo common::my_json_encode($arr);






?>
