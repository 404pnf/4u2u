<?php
    require 'connect.php'; 
    
    $sql = "SELECT bk.*,bi.name name
       FROM `book_kc` bk LEFT JOIN `book_info` bi ON 
        bi.sku = bk.sku WHERE bk.`last_kc`<>bk.`now_kc` AND `is_dalibao`=1 ORDER BY bk.`now_kc` ";

    $rs = mysql_query($sql);
    while($row = mysql_fetch_object($rs)){
    	
    	$op = '<a id="op_'.$row->sku.'" class="op" href="http://2u4u.com.cn/set_dalibao/'.$row->sku.'">移出礼包</a>';
    	
    	
    	$table.= "<tr><td class='row'>".$row->name."</td>";
    	$table.="<td class='row'>".$row->sku."</td>";
    	$table.="<td class='row'>".$row->last_kc."</td>";
    	$table.="<td class='row'><font color=red>".$row->now_kc."</font></td>";
    	$table.="<td class='row'>".date("Y-m-d",$row->changed)."</td>";
    	$table.="<td class='row'>".$op."</td>";
    	$table.= "</tr>";
       }
 
?>

<html>
<head>

<script src="jquery-1.3.1.min.js" type="text/javascript"></script>
<script src="jquery.form.js" type="text/javascript"></script>
<script src="jquery.ajaxContent.pack.js" type="text/javascript"></script>

<script type="text/javascript">
/*
window.setTimeout(function(){	
	alert('123');



//$(".op").click(function () { 
//$("div").each(function (index, domEle) {  
	$('.op').each(function(){
		id = this.id;
		//alert(this.id);
		 
		$('#'+id).ajaxContent({
			event:'click', 
			loaderType:'img',
			loadingMsg:'<img src="ajax-loader.gif">',
			target:'#'+id
		});	
	});
//});

},3000);
*/
</script>

</head>



<body onload="alert('huan yin')">
<h2><p align='center'>大礼包图书库存变动情况</p></h2>
<div align="center">
<table id="mytable" cellspacing="0" >
<th scope="col">书名</th>
<th scope="col">物料号</th>
<th scope="col">上次库存</th>
<th scope="col">本次库存</th>
<th scope="col">更新时间</th>
<th scope="col">移出礼包（移出后，仍需手动修改“礼包站点”的具体书目）</th>
</tr>
<?php echo  $table;?>
</table>
</div>
</html>
