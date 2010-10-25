<?php

/*
 * **  打印出最近一段时间的网站订单。 by wzs 090913
 * **  时间格式有两种：一是到本周一网站所有的订单（已排除前期的订单）；另一种是上一周的网站订单（周一至周日）
 * */

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
	while($row=mysql_fetch_array($re)){
		$title = '';
        $title = $row[title];
		$content_new = '';
   		$content = strip_tags($row[content]);
	   	if(strpos($content,"+")!==false){
	   		   $content = substr($content,1);
               $content =preg_replace("/：.*?\+/s",";",$content); 
               if(strpos($content,"：")){
                   $new_content = explode("：",$content);
                   $content = $new_content[0].";";
               }
	   		} 
	    if(strpos($content,"1.")!==false)
                $content =substr(str_replace("1.","; ",$content),1);	

                  
       if(strpos($content,";")){
          $book_list = explode(";",$content);
    
          
          foreach($book_list as $value){
          
        	$new_value = '';
        	if(strlen($value)>2){       		
	        	$value = trim($value);	        		       
	       		$new_query = "SELECT bi.`name`,bi.`sku`,bk.`now_kc` FROM 2u4u.`book_info` bi
							  LEFT JOIN 2u4u.`book_kc` bk on bk.sku=bi.sku
							  WHERE bi.`name` LIKE  '".$value."%' AND bk.`now_kc`<10";
	            $new_rs = mysql_fetch_object(mysql_query($new_query));
	            if($new_rs->sku>0){
	            	if($new_rs->now_kc<10){
	            	      $table .= "<tr><td>".$title."</td><td>".$new_rs->name."</td><td>".$new_rs->sku."</td><td>".$new_rs->now_kc."</td>";
	            	} 
	           }else{                    		        	
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
	                 $new_sql = " SELECT bi.`name`,bi.`sku`,bk.`now_kc` FROM 2u4u.`book_info` bi
							        LEFT JOIN 2u4u.`book_kc` bk on bk.sku=bi.sku 
	        		                WHERE ".$name_sql."
	        		                AND bk.`now_kc`<10";
	                 $result = mysql_query($new_sql);  
	                 $res_num = @mysql_num_rows($result);
		             $new_res = mysql_fetch_object($result); 
		             
		             if($new_res->now_kc<10&$res_num>0){
	        	           $table .= "<tr><td>".$title."</td><td>".$new_res->name."</td><td>".$new_res->sku."</td><td>".$new_res->now_kc."</td></tr>";
		             }
		            
	             }
		     }
         } 
 	   }	
	 }
	 	
	$table1 = ' <TABLE height=60 cellSpacing=0 borderColorDark=#ffffff width="100%"  
	bgColor=#ffffff borderColorLight=#c0c0c0 border=1> 
	   <tbody>
	    <strong>大礼包图书库存预警</strong>
		<tr>
		 <td align="center" >所属礼包</td>	
		 <td align="center" >图书名</td>
		 <td align="center" >物料号</td>
		 <td align="center" >现有库存</td>	
		
	</tr>'; 
	
	echo $table1.$table;
}	 
	 

