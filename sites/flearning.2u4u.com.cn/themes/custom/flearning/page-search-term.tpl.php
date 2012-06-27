<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

  <head>
    <title><?php print $head_title; ?></title>
    <?php print $head; ?>

	<meta name="viewport" content="width=device-width;"/>

	<link href="<?php print $base_path.$directory?>/css/common.css" media="all" rel="stylesheet" type="text/css">
	
	<link href="<?php print $base_path.$directory?>/css/mobile.css" media="all" rel="stylesheet" type="text/css">
	
	<link href="<?php print $base_path.$directory?>/css/shipin_mobile.css" media="all" rel="stylesheet" type="text/css">
	
	<SCRIPT type="text/javascript" src="<?php print $base_path.$directory?>/js/jquery.js"></SCRIPT>
	<script language="javascript" type="text/javascript" src="<?php print $base_path.$directory?>/js/txgenerictools.js" ></script>
	<SCRIPT type="text/javascript" src="<?php print $base_path.$directory?>/js/jquery.flearning.common.js"></SCRIPT>

  </head>

  <body class="<?php print $body_classes; ?>">

    <div id="main">
    	
	
	
      <div id="page">
        <div id="page-inner" class="inner column center">
			<div id= "page_content" >
				<?
				
				global $user;
				if($user->uid>0)//验证用户访问的内容
					print views_embed_view('search', $display_id = 'search_yanzheng');
				else//未验证用户访问的内容
					print views_embed_view('search', $display_id = 'search_page');

				
				?>
				
			</div>		
		 </div> <!-- /page-inner -->
	  </div> <!-- /page -->
	  
	  
	 
	  
	  
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


  </body>
</html>
