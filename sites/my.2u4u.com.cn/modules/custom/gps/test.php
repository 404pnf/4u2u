<?
include_once "IXR_Library.inc.php";
   
    $client = new IXR_Client('http://2u4u.com.cn/xmlrpc.php');
    if(!$client->query( 'vgame_set_award','guanliyuan',1)){
        die('An error occurred - '.$client->getErrorCode().":".$client->getErrorMessage());
    }else 
    	echo 'ok';
    

?>
