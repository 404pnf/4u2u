<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<link href='table.css' rel='stylesheet' type='text/css' >
<title>大礼包图书库存预警</title>
</head>
<?php


require 'connect.php';

$sql = "SELECT cp.field_product_neirongtiyao_value AS content,n.`title`
		FROM `uc_products` up
		LEFT JOIN `content_type_product` cp ON cp.nid = up.nid
		LEFT JOIN `node` n ON n.nid = up.nid
		WHERE n.status =1
		AND up.sell_price >200
		AND NOT 
		EXISTS (
		SELECT * 
		FROM `content_type_product` 
		WHERE nid = up.nid
		AND vid > cp.vid
		)
		AND cp.field_product_neirongtiyao_value IS NOT NULL 
		GROUP BY cp.nid";


	$re = mysql_query($sql);
	$num = mysql_num_rows($re);
	if($num>0){
	$i = 0;
	$total_mayang = 0;
	$total_points = 0;
	
	$arr = array();
	
	while($row=mysql_fetch_array($re)){
		$title = '';
        $title = $row[title];
		$content_new = '';
   		$content = strip_tags($row[content]);
   		
   		//echo '-------'; 
   		
	   	if(strpos($content,"+")!==false){
	   		   $content = substr($content,1);
               $content =preg_replace("/：.*?\+/s",";",$content); 
               if(strpos($content,"：")){
                   $new_content = explode("：",$content);
                   $content = "1.".$new_content[0].$new_content[1];
               }
            //echo '+++++'.var_export($content,true).'<br/>';    
	   	} 
	    if(strpos($content,"1.")!==false)
                $content =substr(str_replace("1.","; ",$content),1);	

                  
       if(strpos($content,";")){
          $book_list = explode(";",$content);
    
    	//echo var_export($content,true).'<br/>'; 
          
       foreach($book_list as $value){
         //echo $value.'<br/>';
           //$arr[] =  '"'.$value.'';
        	$new_value = '';
        	if(strlen($value)>2){       		
	        	$value = trim($value);	  
	        	
	       		$new_query = "SELECT bi.`name`,bi.`sku`,bk.`now_kc`,`price`,`is_dalibao` FROM 2u4u.`book_info` bi
							  LEFT JOIN 2u4u.`book_kc` bk on bk.sku=bi.sku
							  WHERE bi.`name` LIKE  '".$value."%' AND bk.`now_kc`<10";
				$query = mysql_query($new_query);

			while($new_rs = mysql_fetch_object($query)){	
        
	            if($new_rs->sku>0){
	            	if($new_rs->now_kc<10){
						$op = '<a id="op_'.$new_rs->sku.'" class="op" href="http://2u4u.com.cn/set_dalibao/'.$new_rs->sku.'">';
						if($new_rs->is_dalibao) $op .= "移出礼包";
						else $op .= "移入礼包";
						$op .= '</a>';
						
	            	      $table .= "<tr><td>".$title."</td><td>".$new_rs->name."</td><td>".$new_rs->sku."</td><td>".$new_rs->now_kc."</td><td>".$new_rs->price."</td><td>".$op."</td></tr>";
	            	} 
	           }
	           else{                    		        	
                  $name_sql = '';
 	          	  $search = array( "(", ")", "·",  "）", "（", "《", "》", "--","－","—"); 
                  $new_value = str_replace($search,'|',$value); 
                  if(strpos($new_value,"|")){
			           $arr = explode("|",$new_value);
				       foreach($arr as $book_value){
				          if($book_value!=''){         
				       	      if(strpos("(*)",$book_value))
				       	         $book_value = str_replace("(*)",'',$book_value);				       	      
		                          $name_sql .= "bi.`name` LIKE '%".$book_value."%' AND ";				          
	     			     }
				     }
                   }else{
					
						 $new_value = $value;
						 $name_sql  = " bi.`name` LIKE '".$new_value."%'";
					}	
	
	               if(substr($name_sql,-4)=='AND ')
	                 $name_sql = substr($name_sql,0,-4);     		
	               $new_sql = " SELECT bi.`name`,bi.`sku`,bk.`now_kc`,`price`,`is_dalibao` FROM 2u4u.`book_info` bi
							    LEFT JOIN 2u4u.`book_kc` bk on bk.sku=bi.sku 
	        		            WHERE ".$name_sql."
	        		            AND bk.`now_kc`<10";
	               $result = mysql_query($new_sql);  
	               $res_num = @mysql_num_rows($result);
		           // $new_res = mysql_fetch_object($result); 
		           if($res_num>0) 
		             	while($new_rs = mysql_fetch_object($result))	
		             		if($new_res->now_kc<10&$res_num>0){
		             				$op = '<a id="op_'.$new_res->sku.'" class="op" href="http://2u4u.com.cn/set_dalibao/'.$new_res->sku.'">';
									if($new_res->is_dalibao) $op .= "移出礼包";
									else $op .= "移入礼包";
									$op .= '</a>';
									
								   $table .= "<tr><td>".$title."</td><td>".$new_res->name."</td><td>".$new_res->sku."</td><td>".$new_res->now_kc."</td><td>".$new_rs->price."</td><td>".$op."</td></tr>";
							 }
		           
		            
	             } //------ end else ------
	          }	//------ end while ------

		     } //----- end if ------
         } //----- end foreach ------
 	   }	
 	   
 	   //echo '<br/><br/>';
	 }
	 
	 //echo var_export($arr,true).'<br/>';
}	 
?>	 
<div align="center">
<table id="mytable" cellspacing="0" >
<th scope="col">所属礼包</th>
<th scope="col">图书名</th>
<th scope="col">物料号</th>
<th scope="col">现有库存</th>	
<th scope="col">价格</th>
<th scope="col">移出礼包（移出后，仍需手动修改“礼包站点”的具体书目）</th>
<?php echo $table;?>
</table>
</div>
