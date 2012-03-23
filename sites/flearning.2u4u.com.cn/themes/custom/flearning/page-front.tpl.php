<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

  <head>
    <title><?php print $head_title; ?></title>
    <?php print $head; ?>

	<meta name="viewport" content="width=device-width;"/>

	<link href="<?php print $base_path.$directory?>/css/common.css" media="all" rel="stylesheet" type="text/css">
	
	<link href="<?php print $base_path.$directory?>/css/mfront.css" media="all" rel="stylesheet" type="text/css">

	<SCRIPT type="text/javascript" src="<?php print $base_path.$directory?>/js/jquery.js"></SCRIPT>
	<script language="javascript" type="text/javascript" src="<?php print $base_path.$directory?>/js/txgenerictools.js" ></script>
	<SCRIPT type="text/javascript" src="<?php print $base_path.$directory?>/js/jquery.m2u4u.common.js"></SCRIPT>
	
  </head>

  <body class="<?php print $body_classes; ?>">

    <div id="main">
    
	  	<div class="toolbar">
			<span  id="paihang" class="button common_btn over_button">排行</span>
			
			<span id="shoucang" class="button common_btn over_button">收藏</span> 
			
			<span class="button title_btn"> <a href="/"><img src="<?php print $base_path.$directory?>/css/images/fltrp.png" /> 精华版</a></span>
			
			<span id="info" class="button common_btn info_btn over_button"> <img src="<?php print $base_path.$directory?>/css/images/info.png" /> </span> 
			
			<span id="lishi" class="button common_btn over_button">历史</span>
			
			<span id="yanzheng" class="button common_btn over_button">验证</span>
			
		  </div>
	
	
      <div id="page">
        <div id="page-inner" class="inner column center">
		
		
			<!--内容-->
			<div id= "page_content" >
			
				
				<? print views_embed_view('mobile', $display_id = 'tuijian');?>	
				
				<div class="fenglei">
					<table>
						<tr>
							<td>
								<div class="term_image">
									<a href="search/term?tid=四级"><img src="<?php print $base_path.$directory?>/css/images/siji.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=四级">四级</a>
								</div>
								<div class="term_description">
									英语四级考试资源
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=六级"><img src="<?php print $base_path.$directory?>/css/images/liuji.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=六级">六级</a>
								</div>
								<div class="term_description">
									英语六级考试资源
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=考试"><img src="<?php print $base_path.$directory?>/css/images/kaoshi.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=考试">考试</a>
								</div>
								<div class="term_description">
									各种考试资源
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=egs"><img src="<?php print $base_path.$directory?>/css/images/egs.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=egs">EGS 测试</a>
								</div>
								<div class="term_description">
									考试测试、专向练习
								</div>
								
							</td>
						</tr>
						
						<tr>
							<td>
								<div class="term_image">
									<a href="search/term?tid=四级"><img src="<?php print $base_path.$directory?>/css/images/siji.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=四级">四级</a>
								</div>
								<div class="term_description">
									英语四级考试资源
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=六级"><img src="<?php print $base_path.$directory?>/css/images/liuji.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=六级">六级</a>
								</div>
								<div class="term_description">
									英语六级考试资源
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=考试"><img src="<?php print $base_path.$directory?>/css/images/kaoshi.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=考试">考试</a>
								</div>
								<div class="term_description">
									各种考试资源
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=egs"><img src="<?php print $base_path.$directory?>/css/images/egs.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=egs">EGS 测试</a>
								</div>
								<div class="term_description">
									考试测试、专向练习
								</div>
								
							</td>
						</tr>
						
						<tr>
							<td>
								<div class="term_image">
									<a href="search/term?tid=四级"><img src="<?php print $base_path.$directory?>/css/images/siji.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=四级">四级</a>
								</div>
								<div class="term_description">
									英语四级考试资源
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=六级"><img src="<?php print $base_path.$directory?>/css/images/liuji.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=六级">六级</a>
								</div>
								<div class="term_description">
									英语六级考试资源
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=考试"><img src="<?php print $base_path.$directory?>/css/images/kaoshi.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=考试">考试</a>
								</div>
								<div class="term_description">
									各种考试资源
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=egs"><img src="<?php print $base_path.$directory?>/css/images/egs.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=egs">EGS 测试</a>
								</div>
								<div class="term_description">
									英语水平测试、考试测试、专向练习
								</div>
								
							</td>
						</tr>
						
						<tr>
							<td>
								<div class="term_image">
									<a href="search/term?tid=四级"><img src="<?php print $base_path.$directory?>/css/images/siji.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=四级">四级</a>
								</div>
								<div class="term_description">
									英语四级考试资源
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=六级"><img src="<?php print $base_path.$directory?>/css/images/liuji.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=六级">六级</a>
								</div>
								<div class="term_description">
									英语六级考试资源
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=考试"><img src="<?php print $base_path.$directory?>/css/images/kaoshi.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=考试">考试</a>
								</div>
								<div class="term_description">
									各种考试资源
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=egs"><img src="<?php print $base_path.$directory?>/css/images/egs.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=egs">EGS 测试</a>
								</div>
								<div class="term_description">
									英语水平测试、考试测试、专向练习
								</div>
								
							</td>
						</tr>
						
						<tr>
							<td>
								<div class="term_image">
									<a href="search/term?tid=四级"><img src="<?php print $base_path.$directory?>/css/images/siji.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=四级">四级</a>
								</div>
								<div class="term_description">
									英语四级考试资源
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=六级"><img src="<?php print $base_path.$directory?>/css/images/liuji.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=六级">六级</a>
								</div>
								<div class="term_description">
									英语六级考试资源
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=考试"><img src="<?php print $base_path.$directory?>/css/images/kaoshi.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=考试">考试</a>
								</div>
								<div class="term_description">
									各种考试资源
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=egs"><img src="<?php print $base_path.$directory?>/css/images/egs.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=egs">EGS 测试</a>
								</div>
								<div class="term_description">
									英语水平测试、考试测试、专向练习
								</div>
								
							</td>
						</tr>
						
						
					
					
					</table>
					
				</div>
				
				
				
				
				
			</div>		
		 </div> <!-- /page-inner -->
	  </div> <!-- /page -->
	  
	  <div class="footbar">
		<?php print $footer_block; ?>
		<div id="advanced_search"><a class="button common_btn" href="#">高级检索</a></div>
        
	  </div>
	 
	 
<!-- toolbar 中显示与隐藏的内容 -->
<div id="over_content" >

	<div id="over_paihang" class="overlayer">
		<div class="arrow">
			
		</div>
		
		<div class="content">
			<div class="content-inner">
				<? print views_embed_view('paihang', $display_id = 'paihang_page');?>
			</div>
		</div>
	</div>
	
	<div id="over_shoucang" class="overlayer">
		<div class="arrow">
			
		</div>
		
		<div class="content">
			<div class="content-inner">
				<? print views_embed_view('flag_bookmarks', $display_id = 'shoucang_page');?>
			</div>
		</div>
	</div>
	
	<div id="over_info" class="overlayer">
		<div class="arrow">
			
		</div>
		
		<div class="content">
			<div class="content-inner">
				更多内容，请关注*****
			</div>
		</div>
	</div>
	
	<div id="over_lishi" class="overlayer">
		<div class="arrow">
			
		</div>
		
		<div class="content">
			<div class="content-inner">
				历史记录
			
			</div>
		</div>
	</div>
	
	
	<div id="over_yanzheng" class="overlayer">
		<div class="arrow">
			
		</div>
		
		<div class="content">
			<div class="content-inner">
				验证
			
			</div>
		</div>
	</div>
	
</div>
<!--  end toolbar 中显示与隐藏的内容 -->	 
	 
	</div> <!-- /main -->


<script type="text/javascript">
	$(function(){
		$('.over_button').click(function(){
			var that = this;
			var position = $(this).position();
			
			var nowleft = position.left;
			var nowright = position.right;
			var thatwidth = $(that).outerWidth();
			
			var contentId = $('#over_'+that.id);
			/**/
	//alert();
	
			var contentW = contentId.outerWidth();
			
			var arrowleft = thatwidth/2-8;

			$('#over_'+that.id+' .arrow').css({'left':arrowleft+'px'});

			if(nowleft+contentW>768){
				contentId.css({'right':'20px'});
				
			}
			else
				contentId.css({'left':nowleft+'px'});
	/**/				
			if($(this).hasClass('touched_btn')){
				$('.touched_btn').removeClass('touched_btn');
				
				$('.overlayer').hide('fast');
			}
			else{
				$('.touched_btn').removeClass('touched_btn');
				
				$('.overlayer').hide('fast');
				
				$(this).addClass('touched_btn');
				$('#over_'+that.id).toggle('slow');
			}
		});
	});

</script>
	
<script type="text/javascript">
var _bdhmProtocol = (("https:" == document.location.protocol) ? " https://" : " http://");
document.write(unescape("%3Cscript src='" + _bdhmProtocol + "hm.baidu.com/h.js%3F116fea821e3bfb6c5a7d4b187a50b502' type='text/javascript'%3E%3C/script%3E"));
</script>

  </body>
</html>
