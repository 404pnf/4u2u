<?php

function get_book_kc(){

	
	set_time_limit(0);
    $query = "SELECT MAX(`changed`) time FROM {book_kc} WHERE is_dalibao=1";
	$update_time = db_fetch_object(db_query($query));
	$span = time()-$update_time->time;
	//if($span>86400){
	if($span>=0){
		$sql = "SELECT `sku`,`last_kc`,`now_kc`,`changed` FROM `book_kc` where  is_dalibao=1";
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

/*
function insert_book_kc_base_erp($sku){

	$kc = get_kc($sku);
	if($kc>=0){
	    $sql = "INSERT INTO {book_kc}(`sku`,`last_kc`,`now_kc`,`changed`) VALUES (%d,%d,%d,%d) ";
	    db_query($sql,$emno,$kc,$kc,time());
	}
	return $kc;
}
*/



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


function set_book_kc_is_dalibao($sku){
	$sql_query = "SELECT is_dalibao FROM {book_kc} WHERE `sku` = %d ";
	$rs = db_query($sql_query,$sku);
	
	if($row = db_fetch_object($rs)){
		if($row-> is_dalibao){
			$sql = "UPDATE {book_kc} SET is_dalibao=0 WHERE `sku` = %d ";
			$output = "移入礼包";
		}
		else{
			$sql = "UPDATE {book_kc} SET is_dalibao=1 WHERE `sku` = %d ";
			$output = "移出礼包";
		}
		db_query($sql,$sku);
		echo $output;
	}
	
}



//$step = $_REQUEST['step'];
//if($step=='') $step = 'query';
//compare_erp_book_info($step);
 
function compare_erp_book_info($step = 'query'){
	
		$sql_erp = "SELECT `field_erp_wuliaohao_value` sku, `field_erp_shuming_value` name, 	
					`field_erp_dingjia_value` price, `field_erp_jianglijifen_value` points, 
					`field_erp_zhuzuozhe_value` author, `field_erp_shangpindaima_value` isbn, `field_erp_shuhaotiaoma_value` shuhao
				FROM ebook.`content_type_erp` ORDER BY sku";
		$sql_book_info = "SELECT `sku` , `name` , `price` , `points` , `author` , 
								`isbn` , `shuhao` , `group`
						FROM 2u4u.`book_info`";
		
		$rs_erp = mysql_query($sql_erp);
		$rs_book_info = mysql_query($sql_book_info);
	   
		$num_erp = @mysql_num_rows($rs_erp);
		$num_book_info = @mysql_num_rows($rs_book_info);
		$erp_book_info_differ = abs($num_erp - $num_book_info);
	if($step == 'query'){	
		echo "erp 书目：".$num_erp."， 本地书目：".$num_book_info."， 相差：".$erp_book_info_differ." 本。（参考项，erp 书目 sku 有部分重复）"."<a class='demo' href='/update_book_info/update'>确认更新</a>";
	}
	else
	if($step == 'update'){
		
		$book_info_sku_arr = array();
		if($num_erp > $num_book_info){
			while($row_book_info = mysql_fetch_object($rs_book_info)){    
				$book_info_sku_arr[] = (int)$row_book_info->sku;
				
			}
			
			$i = 0;
			
			while($row_erp = mysql_fetch_object($rs_erp)){    
				$sku_erp = (int)$row_erp->sku;
				$name_erp = $row_erp->name;
				$price_erp = $row_erp->price;
				$points_erp = $row_erp->points;
				$author_erp = $row_erp->author;
				$isbn_erp = $row_erp->isbn;
				$shuhao_erp = $row_erp->shuhao;
				
				if(!in_array($sku_erp,$book_info_sku_arr,true)){
					$sql_insert = "INSERT INTO 2u4u.`book_info`(`sku` , `name` , `price` , `points` , `author` , `isbn` , `shuhao` , `group`) VALUES(".$sku_erp.",'".$name_erp."', ".$price_erp.", ".$points_erp.", '".$author_erp."','".$isbn_erp."','".$shuhao_erp."', 0)";
					
					mysql_query($sql_insert);
					
					$i++;
					
					echo ' sku: '.$sku_erp.'  name: '.$name_erp.'<br>';
				}
				
			}
			
			echo "插入 ".$i." 条书目。<br>";
		}
		
	}
}


