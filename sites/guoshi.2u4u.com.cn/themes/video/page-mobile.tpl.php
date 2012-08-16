<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

<head>
<title><?php print $head_title; ?></title>
<meta name="viewport" content="width=device-width;"/>
<!--
<link href="http://2u4u.com.cn/sites/2u4u.com.cn/themes/stable/css/common.css" media="all" rel="stylesheet" type="text/css">-->
<link href="/sites/2u4u.com.cn/themes/stable/mobile/css/common.css" media="all" rel="stylesheet" type="text/css">
	
<link href="<?php print $base_path.$directory?>/js/jplayer200/jplayer.blue.monday.css?" media="all" rel="stylesheet" type="text/css">

<link href="<?php print $base_path.$directory?>/mobile/css/mobile.css" media="all" rel="stylesheet" type="text/css">

<!--
<script src="<?php print $base_path.$directory?>/js/jquery.min.js" type="text/javascript"></script>
-->
	<SCRIPT type="text/javascript" src="/sites/2u4u.com.cn/themes/stable/mobile/js/jquery.js"></SCRIPT>
	
	<script src="/sites/ebook.2u4u.com.cn/themes/ebook/js/jquery.tools.min.js" type="text/javascript"></script>
	
<script src="<?php print $base_path.$directory?>/js/jplayer200/jquery.jplayer.min.js" type="text/javascript"></script>
<!---->
<script src="<?php print $base_path.$directory?>/js/mobile.jplayer.js" type="text/javascript"></script>

	<?php $clienttype = $_REQUEST['clienttype']; echo '<script> var clienttype = "'. $clienttype.'"; </script>';?>
	
<script type="text/javascript">	
	$(function(){
		
		$('li.pager-previous a').html('');
		
		$('li.pager-next a').html('');
		
	});
</script>
</head>
<body class="<?php print $body_classes; ?>">
<div id="main"> 
	<?php if ($content_top): ?>
		<div id="content-top">
		  <?php print $content_top; ?>
		  <a id="prev" class=""></a><!--向前滚动的按钮-->
		  <div class="nextbg"><a id="next" class=""></a></div><!--向后滚动的按钮 -->
		</div> <!-- /#content-top -->
	<?php endif; ?>
	
	<?php print $content; ?>   	 
</div>
<script type="text/javascript">
	$(function(){

		if(clienttype == 'iphone'){
			$("#quicktabs-2").scrollable({
				size: 4,
				vertical:false,
				clickable:false,
				//navi:'#navi2',
				items:'ul.quicktabs_tabs',
				prevPage:'#prev',//跳转到上一页
				nextPage:'#next',//跳转到下一页
				hoverClass: 'hover',
				easing:'linear'
			}); 
		}
		else{
			$("#quicktabs-2").scrollable({
				size: 8,
				vertical:false,
				clickable:false,
				//navi:'#navi2',
				items:'ul.quicktabs_tabs',
				prevPage:'#prev',//跳转到上一页
				nextPage:'#next',//跳转到下一页
				hoverClass: 'hover',
				easing:'linear'
			}); 
		}		
	});
</script>
</body>
</html>