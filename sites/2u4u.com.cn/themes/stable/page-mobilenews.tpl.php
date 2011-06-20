<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

<head>
<title><?php print $head_title; ?></title>
<link href="<?php print $base_path.$directory?>/css/mobile.css" media="all" rel="stylesheet" type="text/css">
</head>
<body>
			<!--热点推荐-->
		<div class="mobile_content">
			<div class="recommend"><a href="/rediantuijian" target="_blank">热点推荐</a></div> 
			<div id= "rediantuijian" class="clearfix recommend-bg">
				<div class="redian_new">
					<? print views_embed_view('mobie_content', $display_id = 'attachment_1');?>				
				</div>	
				<? print views_embed_view('mobie_content', $display_id = 'page_1');?>				
			
			</div>
		</div>
       	 
</body>
</html>