<?php
	include_once 'includes/bootstrap.inc';
	drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
	global $user;
	
	if($user->uid != 1){
		print('only admin user can view this page.<br/>');
		exit();
	}
	$result = db_query("select nid from node where type in ('page','news', 'dict_daily_sentence', 'xgn_menu', '')");
	$file = fopen("/var/www/html/new/".$_SERVER['HTTP_HOST'],"w");

	while($obj = db_fetch_object($result)){
	  $nid = $obj ->nid;
	  $url = 'http://'.$_SERVER['HTTP_HOST'].'/node/'.$nid.'/';
	  $url = '<a href = "'.$url.'">'.$url."</a>"."\r\n";
	  echo fwrite($file,$url);
	}
	fclose($file);
	print('success!');
