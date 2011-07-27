
<?php
/*
	header("expires:mon,26jul199705:00:00gmt"); //用于清楚缓存
	header("cache-control:no-cache,must-revalidate"); //用于清楚缓存
	header("pragma:no-cache");
*/	
 require 'connect.php'; 
  
function get_kc($sku){
	
	$client = new SoapClient("http://nps.fltrp.com/webs/getkc/getkc.cfc?wsdl");
	return $client->getkc($sku); 
}  

$num_rs = 0;
$num_sku = 0;

 if(isset($_REQUEST['num'])&&empty($_REQUEST['sku'])){
 	
   $sql = "SELECT bk.last_kc,bk.now_kc,bk.changed,bi.sku,bi.name name,bi.price price,is_dalibao FROM  `book_kc` bk  LEFT JOIN `book_info` bi ON bi.sku = bk.sku ";
 
   $num = empty($_REQUEST['num'])?1:$_REQUEST['num'];           
   switch($num){
  	case 1:
  		 $limit = " bk.`now_kc`<20 ";
         break;
    case 2:
  		 $limit = " bk.`now_kc` between 20 and 50 ";
         break;
    case 3:
  		 $limit = " bk.`now_kc` between 50 and 100";
         break;
     case 4:
  		 $limit = " bk.`now_kc`>100 ";
         break;     
       
   }
   
   if($limit!='')
          $sql .=" WHERE ".$limit." AND `is_dalibao`=1  ORDER BY bk.`now_kc` DESC";

	$rs = mysql_query($sql);
   // $num_rs = mysql_num_rows($rs);
	$num_rs = @mysql_num_rows($rs);
	//echo $sql;
}    
  
   if(!empty($_REQUEST['sku'])){
   		//$sql_sku = "Select * from book_kc ";
   
   	   $sql_sku = "SELECT bk.last_kc,bk.now_kc,bk.changed,bi.sku,bi.name name,bi.price price,bk.is_dalibao FROM `book_info` bi LEFT JOIN `book_kc` bk ON bi.sku = bk.sku ";
   	   $sku = (int)$_REQUEST['sku'];
   	   $sql_sku .= " WHERE bi.sku = ".$sku;
   	   
   	   $rs_sku = mysql_query($sql_sku);
   	   $num_sku = mysql_num_rows($rs_sku);
    }
    
    

      
       if($num_rs>0||$num_sku>0){
			$table  ="<h2><p align='center'>大礼包图书库存</p></h2>
						<div align='center'>
						<table id='mytable' cellspacing='0' >
						<th scope='col'>书名</th>
						<th scope='col'>价格</th>
						<th scope='col'>物料号</th>
						<th scope='col'>库存</th>
						<th scope='col'>更新时间</th>
						<th scope='col'>移出/移入 礼包</th>
						</tr>";
			if($num_sku>0) $res = $rs_sku;
			else $res = $rs;
		 
         while($row = mysql_fetch_object($res)){    	
	    	$table.= "<tr><td class='row'>".$row->name."</td>";
		    $table.="<td class='row'>".$row->price."</td>";
		    $table.="<td class='row'>".$row->sku."</td>";
	    	
	    	$op = '<a id="op_'.$row->sku.'" class="op" href="http://2u4u.com.cn/set_dalibao/'.$row->sku.'">';
	    	if($row->is_dalibao) $op .= "移出礼包";
	    	else $op .= "移入礼包";
	    	$op .= '</a>';
	    	// whx here
	    	
	        if($row->changed>86400){
	            $now_kc = $row->now_kc;
	            $changed = date("Y-m-d",$row->changed);
	        }
	         /*else{
	        	$now_kc = get_kc($row->sku);
	        	$changed = "添加到礼包（添加后，仍需在礼包站点，手动设置礼包内容）";
	        }
	        */	
             
            else{ 
	            $now_kc = file_get_contents('http://2u4u.com.cn/erp_kc?sku='.$row->sku);
	            $changed = date("Y-m-d",time());

	            if($now_kc>0){
	               $query = "INSERT INTO `book_kc` (`sku`,`last_kc`,`now_kc`,`time`,`is_dalibao`)
	                VALUES ($row->sku,$now_kc,$now_kc,$changed,0)";
	              mysql_query($query);
	         	} 

	        }    
             
	        if($row->now_kc!=$row->last_kc) 
	    	    $table.="<td class='row'><font color=red>".(int)$now_kc."</font></td>";
	    	else 
	    	    $table.="<td class='row'>".(int)$now_kc."</td>";
	    	    
	    	$table.="<td class='row'>".$changed."</td>";
	    	$table.="<td class='row'>".$op."</td>";
	    	
	    	
	    	$table.= "</tr>";
           }            
          $table.= "</table>";
          echo  $table;
       }else{       	 
       	   echo "暂时还不能查询本书的库存";
       }
 	
?>
