<?php
header("Content-type: text/html; charset=utf-8");
require '../connect.php';
echo 'aaaaaa';
$i = 0;
$j=0;
  $file_r = file_read(); 
  $file_name = explode("~",$file_r);
  
 

  foreach($file_name as $name_new){		

	
		  if(!strstr($name_new,";")){	
			 $series_name = $name_new;	
			 $query = "SELECT `series_id` FROM `disney_series` WHERE `series_name` LIKE '".$series_name."'";

			 $result = mysql_fetch_object(mysql_query($query));
		     $series_id = $result->series_id;
		     
		  }else{
		  	if(strlen($name_new)>4){
		  		
            $book_name = explode(";",$name_new);             
            foreach($book_name as $name){
            if(strlen($name)>4){
               if(strpos($name,"|")){
            		$new_name = explode("|",$name);
					$name_ch = trim($new_name[0]);
				 
				   	$name_en = addslashes(trim($new_name[1]));
				
				    if(strpos($new_name[2],"@")){
					   $book_level = explode("@",$new_name[2]);
					   $level = trim($book_level[1]);	
                       $audio = addslashes(trim($book_level[0]));
                       $img = addslashes(trim($book_level[0]));
					}
            	 }
            	 //数据插入
            	 
            	 $sql = "INSERT INTO `disney_book`(`book_id`,`name_en`,`name_ch`,`level`,`series_name`,`series_id`,`audio`,`image`) VALUES('','$name_en','$name_ch','$level','$series_name',".$series_id.",'$audio','$img')";
                $rs = mysql_query($sql);
            	 if($rs)
            	 	$i++;   
            	 else 
            	    echo $sql."<br>";	    	 
            	 
            	} 
            	 
                 }
		    	}
            }
				
		
	}	
	echo "共导入".$i;
	
function file_read(){

	$path='disney-data.txt';
	$fh = fopen($path, "rb");
	$data = fread($fh, filesize($path));
	fclose($fh);
	return $data;
}
	
	
?>
