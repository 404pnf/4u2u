<?php
	
require 'connect.php'; 
require 'connect-ebook.php';

$step = $_REQUEST['step'];
if($step=='') $step = 'query';
compare_erp_book_info($step);
 
function compare_erp_book_info($step = 'query'){
	
		$sql_erp = "SELECT `field_erp_wuliaohao_value` sku, `field_erp_shuming_value` name, 	
					`field_erp_dingjia_value` price, `field_erp_jianglijifen_value` points, 
					`field_erp_zhuzuozhe_value` author, `field_erp_shangpindaima_value` isbn, `field_erp_shuhaotiaoma_value` shuhao
				FROM ebook.`content_type_erp`";
		$sql_book_info = "SELECT `sku` , `name` , `price` , `points` , `author` , 
								`isbn` , `shuhao` , `group`
						FROM 2u4u.`book_info`";
		
		$rs_erp = mysql_query($sql_erp);
		$rs_book_info = mysql_query($sql_book_info);
	   
		$num_erp = @mysql_num_rows($rs_erp);
		$num_book_info = @mysql_num_rows($rs_book_info);
		$erp_book_info_differ = abs($num_erp - $num_book_info);
	if($step == 'query'){	
		echo "erp 书目：".$num_erp."， 本地书目：".$num_book_info."， 相差：".$erp_book_info_differ." 本。"."<a class='demo' href='update_erp_book_info.php?step=update'>更新本地书目</a>";
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
					/**/
					$i++;
					
					echo $sql_insert.' sku: '.$sku_erp.'  name: '.$name_erp.'<br>';
				}
			}
			
			echo "插入 ".$i." 条书目。<br>";
		}
		
	}
}

?>
