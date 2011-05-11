<?php
error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE); 

require 'connect.php';

global $discuz_url;
$discuz_url = "http://u.2u4u.com.cn/";
$time = strtotime("today");
$sql = "SELECT blogid,uid,username,subject 
	       FROM `uchome_blog` 
	       WHERE dateline>$time-86400*7 GROUP BY uid ORDER BY hot DESC,viewnum DESC 
	       LIMIT 4";		    
$rs =  mysql_query($sql);
$fic = fopen("export.xml","w");    
/*fwrite($fic, '<?xml version="1.0"encoding="ISO-8859-1"?>');
fwrite($fic, '<!-- DB to XML -->');*/
fwrite($fic, '<xml>');

DEFINE('UC_API',"http://u.2u4u.com.cn/ucenter");
    while($row = mysql_fetch_object($rs)){
	fwrite($fic, "<node>");      
    	$photo = '';
    	$photo = ckavatar($row->uid) ? avatar($row->uid, 'small',true) : UC_API.'/images/noavatar_small.gif';
	fwrite($fic,'<avatar>'.$photo.'</avatar>');
	fwrite($fic,'<id>'.$row->username.'</id>');
	fwrite($fic,'<title>'.$row->subject.'</title>');
	fwrite($fic,'<url>'.$discuz_url."home/space.php?uid=".$row->uid.'</url>');
      	fwrite($fic,'</node>');
    }
fwrite($fic,'</xml>');     
fclose($fic);  	 	    


function avatar($uid, $size='small', $returnsrc = FALSE) {
	
	$size = in_array($size, array('big', 'middle', 'small')) ? $size : 'small';
	$avatarfile = avatar_file($uid, $size);
	return $returnsrc ? UC_API.'/data/avatar/'.$avatarfile : '<img src="'.UC_API.'/data/avatar/'.$avatarfile.'" onerror="this.onerror=null;this.src=\''.UC_API.'/images/noavatar_'.$size.'.gif\'">';
}

function avatar_file($uid, $size) {
	global $_SGLOBAL, $_SCONFIG;

	$type = empty($_SCONFIG['avatarreal'])?'virtual':'real';
	$var = "avatarfile_{$uid}_{$size}_{$type}";
	if(empty($_SGLOBAL[$var])) {
		$uid = abs(intval($uid));
		$uid = sprintf("%09d", $uid);
		$dir1 = substr($uid, 0, 3);
		$dir2 = substr($uid, 3, 2);
		$dir3 = substr($uid, 5, 2);
		$typeadd = $type == 'real' ? '_real' : '';
		$_SGLOBAL[$var] = $dir1.'/'.$dir2.'/'.$dir3.'/'.substr($uid, -2).$typeadd."_avatar_$size.jpg";
	}
	return $_SGLOBAL[$var];
}

function ckavatar($uid) {
	    $_SCONFIG['uc_dir'] = '/home/apache/data/html/ucenter/ucenter';
		$file = $_SCONFIG['uc_dir'].'./data/avatar/'.avatar_file($uid, 'middle');
		return file_exists($file)?1:0;
	
}
?>
