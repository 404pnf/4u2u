<?php

function get_book_kc(){
	set_time_limit(0);
        $query = "SELECT MAX(`changed`) time FROM {book_kc} WHERE is_dalibao=1";
	$update_time = db_fetch_object(db_query($query));
	$span = time()-$update_time->time;
	if($span>86400){
		$sql = "SELECT `sku`,`last_kc`,`now_kc`,`changed` FROM `book_kc` ";
		$rs = db_query($sql);
		$i = 0;
		while($row = db_fetch_object($rs)){
		  if(time()-$row->changed>86400){
			 $kc = get_kc($row->sku);
			  if($kc!=$row->now_kc){
				$query = "UPDATE `book_kc` SET `last_kc`=`now_kc`,`now_kc` = %d ,`changed` =%d WHERE sku=%d ";
				db_query($query,$kc,time(),$row->sku);
				$i++;			  
		    }   
		 }  
	    } 
	    echo "<h2 align='center'>更新了".$i."条记录</h2>";
}else  
    echo "<h2 align='center'>今天已经进行过更新！</h2>";
}

function get_erp_kc(){
	$emno = (int)$_GET['sku'];
	$kc = get_kc($emno);
	echo $kc;
	if($kc>=0){
	    $sql = "INSERT INTO {book_kc}(`sku`,`last_kc`,`now_kc`,`changed`) VALUES (%d,%d,%d,%d) ";
	    db_query($sql,$emno,$kc,$kc,time());
	}
}



function get_kc($emno){
	
	$client = new SoapClient("http://nps.fltrp.com/webs/getkc/getkc.cfc?wsdl");
	return $client->getkc($emno); 
}
