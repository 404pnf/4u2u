<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

  <head>
    <title><?php print $head_title; ?></title>
    <?php print $head; ?>

	<meta name="viewport" content="width=device-width;"/>

	<link href="<?php print $base_path.$directory?>/css/common.css" media="all" rel="stylesheet" type="text/css">
	
	<link href="<?php print $base_path.$directory?>/css/mobile.css" media="all" rel="stylesheet" type="text/css">

	<SCRIPT type="text/javascript" src="<?php print $base_path.$directory?>/js/jquery.js"></SCRIPT>
	<script language="javascript" type="text/javascript" src="<?php print $base_path.$directory?>/js/txgenerictools.js" ></script>
	<SCRIPT type="text/javascript" src="<?php print $base_path.$directory?>/js/jquery.flearning.common.js"></SCRIPT>
	
  </head>

  <body class="<?php print $body_classes; ?>">

    <div id="main">
    	<!--
		<div class="toolbar">
			<span class="button touched_btn"><a href="/paihang">排行</a></span>
			<span class="button common_btn"><a href="/shoucang">收藏</a></span> <span class="button title_btn"> <a href="/"><img src="<?php print $base_path.$directory?>/css/images/fltrp.png" /> 精华版</a></span>
			<span class="button common_btn info_btn"> <img src="<?php print $base_path.$directory?>/css/images/info.png" /> </span> 
			<span class="button common_btn"><a href="/lishi">历史</a></span>
			<span class="button touched_btn"><a href="/denglu">验证</a></span>
			
		</div>
		-->
      <div id="page">
        <div id="page-inner" class="inner column center">
		<!--
			<div id="page_title">
			
			</div>
		-->
			<!--内容-->
			<div id= "page_content" >
				<?php print $content; ?>
			</div>	
			
		 </div> <!-- /page-inner -->
	  </div> <!-- /page -->
	  
	  
	  <!--
	  <div class="footbar">
		<?php //print $footer_block; ?>
		<div id="advanced_search"><a class="button common_btn" href="/advanced/search">高级检索</a></div>
        
	  </div>
	  -->
	  
	  
<!-- toolbar 中显示与隐藏的内容 -->
<div id="over_content" >

	<div id="over_paihang" class="overlayer">
		<div class="arrow">
			
		</div>
		
		<div class="content">
			<div class="content-inner">
				<? print views_embed_view('paihangbang', $display_id = 'paihang_page');?>
			</div>
		</div>
	</div>
	
	<div id="over_shoucang" class="overlayer">
		<div class="arrow">
			
		</div>
		
		<div class="content">
			<div class="content-inner">
				<? print views_embed_view('flag_bookmarks_lishi', $display_id = 'shoucang_page');?>
			</div>
		</div>
	</div>
	
	<div id="over_info" class="overlayer">
		<div class="arrow">
			
		</div>
		
		<div class="content">
			<div class="content-inner">
				<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;本版是外研社iLearning外语自主学习资源库的移动学习客户端，iLearning以全球化的国际视野，与国际顶尖合作伙伴共同打造非母语环境下的外语学习解决方案。资源整合了国内外知名媒体（BBC、VOA、ITN
CHINADAILY等），顶尖教育出版机构（剑桥、牛津、培生、麦克米伦等）的优质专业内容，为广大学习者构建了一个自主学习的多媒体、多语种、多终端外语学习平台。</p>

			</div>
		</div>
	</div>
	
	<div id="over_lishi" class="overlayer">
		<div class="arrow">
			
		</div>
		
		<div class="content">
			<div class="content-inner">
				<? print views_embed_view('flag_bookmarks_lishi', $display_id = 'lishi_page');?>
			
			</div>
		</div>
	</div>
	
	
	<div id="over_yanzheng" class="overlayer">
		<div class="arrow">
			
		</div>
		
		<div class="content">
			<div class="content-inner">
				<?php 
					$block = module_invoke("iLearning_serial","block", "view",0);
		
					print $block["content"]; 
				?>
			
			</div>
		</div>
	</div>
	
</div>
<!--  end toolbar 中显示与隐藏的内容 -->	 
	 
	</div> <!-- /main -->


<script type="text/javascript">
/*
$(function(){
	var params ={"btnLeft" : "600", "btnwidth" : "60","btnstatus":"","machineID":"7ccc31e0ddd2a215938c0f8fbc223056"};//btnLeft:按钮位置，距离左侧边距绝对位置，btnwidth：按钮宽度大小，btnstatus：按钮状态，""或者"normal"表示未点击的按钮，"touched"或其他值表示已经点击过，再次点击，则收回正在显示的内容。
	performRequest( 'paihang', params);
});*/
</script>
	
<script type="text/javascript">
var _bdhmProtocol = (("https:" == document.location.protocol) ? " https://" : " http://");
document.write(unescape("%3Cscript src='" + _bdhmProtocol + "hm.baidu.com/h.js%3F116fea821e3bfb6c5a7d4b187a50b502' type='text/javascript'%3E%3C/script%3E"));
</script>

  </body>
</html>
