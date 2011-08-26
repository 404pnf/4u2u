<?php
// $Id: box.tpl.php,v 1.3 2007/12/16 21:01:45 goba Exp $

/**
 * @file tuijian-node.tpl.php
 *
 * Theme implementation to display 推荐此书的粉丝以及推荐评论框.
 *
 * Available variables:
 * - $content: content.
 *
 * @see template_preprocess()
 */
?>


<?php print $content ?>
<div id="sayToFriBox" class="sayToFri normal">
							
	<div id="sayto" class="title"></div>
	<textarea id="sayContent" class="textarea" cols="" rows=""></textarea>

	<div calss="wordleft-tip">还可以输入 <span class="charsLeft">140</span> 字</div>
	
	<a class="right nextBtn" href="javascript:void(0);" id="saveAndSend">完成并发送</a>
</div>

<script>
$(function () {

	$('#friendList .sayto a').click(function(){
		//alert($(this).attr('alt'));
		if($(this).parent().parent('.fans-row').hasClass('selected')){
			$(this).parent().parent('.fans-row').removeClass('selected');
			sayto_user = $(this).attr('alt');
			sayto_users = $('#sayto').text();
			
			var regSign = new  RegExp('@'+sayto_user+'@');
			var regSign2 = new  RegExp('@'+sayto_user+'$');
			
			sayto_users = sayto_users.replace(regSign.exec(sayto_users),'@').replace(regSign2.exec(sayto_users),'');
			
			$('#sayto').text(sayto_users);
			
		}
		else{
			$(this).parent().parent('.fans-row').addClass('selected');
			$('#sayto').append('@'+$(this).attr('alt'));
		}
		
		
		if($('#sayto').text()!='')
			$('#sayToFriBox').removeClass('normal').removeClass('focus').addClass('focus');
		else
			$('#sayToFriBox').removeClass('normal').removeClass('focus').addClass('normal');
	});
	
	
		
	var max=$("#sayToFriBox .charsLeft").text();
	
	$('textarea#sayContent').keyup(function() {
		var text=$(this).val();
		var counter=text.length;
		$("#sayToFriBox .charsLeft").text(max-counter);
		
		$('#sayToFriBox').removeClass('normal').removeClass('focus').addClass('focus');
		
	}); 
	
	
	
	$('#saveAndSend').click(function(){
		comment = $('#sayto').text()+' '+$('#sayContent').val();
		
		$('#edit-comment').val(comment);
		
		$('#edit-submit').click();
		
	});
	
	
	$('li a.tuijian_function').click(function(){
		url = 'http://t.2u4u.com.cn/'+$(this).attr('alt');
		
		$.ajax({
			url: url,
			dataType: 'html',
			//data: data,
			timeout:200000,// 设置请求超时时间（毫秒）。 
			//context:$('.tuijian_content'),
			beforeSend: function( xhr ) {
				$('.tuijian_content').html('<img src="/sites/t.2u4u.com.cn/themes/ebook/css/images/loading.gif"/>');

			},
			error: function (XMLHttpRequest, textStatus, errorThrown) {// 请求失败时调用函数。  
				$('.tuijian_content').html(" 请求超时! textStatus: " + textStatus + ', errorThrown: ' + errorThrown);
			 }, 
			success: function(resp) 
			{  //请求成功后回调函数。
			

				try
				{
				
					$('.tuijian_content').html(resp);
				
				}
				catch (err)
				{
					$('.tuijian_content').append('服务器交互失败，请重试'+err);
				}
				
			}	
		});
			
		
	});
});

</script>