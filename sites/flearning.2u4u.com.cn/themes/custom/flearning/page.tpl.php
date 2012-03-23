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
	<SCRIPT type="text/javascript" src="<?php print $base_path.$directory?>/js/jquery.m2u4u.common.js"></SCRIPT>
	
  </head>

  <body class="<?php print $body_classes; ?>">

    <div id="main">
    
		<div class="toolbar">
			<span class="button touched_btn"><a href="/paihang">排行</a></span>
			<span class="button common_btn"><a href="/shoucang">收藏</a></span> <span class="button title_btn"> <a href="/"><img src="<?php print $base_path.$directory?>/css/images/fltrp.png" /> 精华版</a></span>
			<span class="button common_btn info_btn"> <img src="<?php print $base_path.$directory?>/css/images/info.png" /> </span> 
			<span class="button common_btn"><a href="/lishi">历史</a></span>
			<span class="button touched_btn"><a href="/denglu">验证</a></span>
			
		  </div>
	
      <div id="page">
        <div id="page-inner" class="inner column center">
		
			<div id="page_title">
					页面标题栏
				<? //print views_embed_view('mobile_fp', $display_id = 'attachment_11');?>
			
			</div>
		
			<!--内容-->
			<div id= "page_content" >
				<?php print $content; ?>
			</div>		
		 </div> <!-- /page-inner -->
	  </div> <!-- /page -->
	  
	  <div class="footbar">
		<?php print $footer_block; ?>
		<div id="advanced_search"><a class="button common_btn" href="#">高级检索</a></div>
        
	  </div>
	  
	  
	  
	</div> <!-- /main -->

	
<script type="text/javascript">
var _bdhmProtocol = (("https:" == document.location.protocol) ? " https://" : " http://");
document.write(unescape("%3Cscript src='" + _bdhmProtocol + "hm.baidu.com/h.js%3F116fea821e3bfb6c5a7d4b187a50b502' type='text/javascript'%3E%3C/script%3E"));
</script>

  </body>
</html>
