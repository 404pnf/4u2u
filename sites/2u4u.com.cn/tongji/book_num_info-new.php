<?php
require 'connect.php';

 
//header("Content-type:application/vnd.ms-excel;charset:utf-8"); 
//header("Content-Disposition:filename=book_num_info.xls"); 
//header("Pragma: no-cache");
//header("Expires: 0");

if($_GET['t']=='week'|empty($_GET['t'])){
     $filename = "book_num_info_7days";
     $time_limit =" where tp.time>unix_timestamp(now())-86400*7 ";
}
if($_GET['t']=='all'){
	 $filename = "book_num_info_all";
	 $time_limit = '';
}
if($_GET['info']=='new'){
	 $time_limit = '';
	 $limit = "LIMIT 300";
}


//$sql = "SELECT emno,count(emno) as num FROM `topup` GROUP BY emno ORDER BY num desc ";

$sql = "SELECT tp.`emno`,count(emno) as num ,bi.`name`,bi.`price`,bi.`points`   
        FROM `topup` tp LEFT JOIN `book_info` bi ON bi.sku = tp.emno $time_limit GROUP BY emno ORDER BY num desc ";

$result = @mysql_query($sql);

header("Content-type:application/vnd.ms-excel;charset:utf-8"); 
header("Content-Disposition:filename=$filename.xls"); 
header("Pragma: no-cache");
header("Expires: 0");


$table .= ' <TABLE height=45 cellSpacing=0 borderColorDark=#ffffff width="100%"  
bgColor=#ffffff borderColorLight=#c0c0c0 border=1> 
   <tbody>
         <td align="center" >分类</td>
          <td align="center" >书名</td>
	 <td align="center" >价格</td>
	 <td align="center" >物料号</td>	
	 <td align="center" >次数</td>	
</tr>'; 

while($row = mysql_fetch_array($result))
{ 

	$query = "SELECT nid FROM ebook.`content_type_erp` WHERE field_erp_wuliaohao_value=".$row[emno];
	$res = @mysql_query($query) or die(mysql_error());
    $count = mysql_num_rows($res);
	if($count>0){	
      $arr = mysql_fetch_array($res);

      $sqlx = "SELECT td.name FROM ebook.`term_data` td LEFT JOIN ebook.`term_node` tn ON td.tid= tn.tid WHERE tn.nid=".$arr['nid'];
 $term_name = mysql_fetch_array(mysql_query($sqlx));
      $fenlei = $term_name['name'];
	  $name = $row['name'];
	  $price = $row['price'];
    }else{
          $fenlei = '';
	  $name = '';
          $price = '';
    }
$table .='<tr>
<td align="center" >'.$fenlei.'</td>
<td align="center" >'.$name.'</td>
	      <td align="center" >'.$price.'</td>
	 <td align="center" >'.$row[emno].'</td>	
	 <td align="center" >'.$row[num].'</td></tr>'; 
} 
$table .=" </TBODY> </TABLE>"; 
echo $table;

?>
