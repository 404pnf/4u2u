<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

<head>
<title><?php print $head_title; ?></title>
<!---->
<link href="http://2u4u.com.cn/sites/2u4u.com.cn/themes/stable/css/common.css" media="all" rel="stylesheet" type="text/css">
<link href="<?php print $base_path.$directory?>/js/jplayer200/jplayer.blue.monday.css?" media="all" rel="stylesheet" type="text/css">
<!---->
<link href="<?php print $base_path.$directory?>/mobile/css/mobile.css" media="all" rel="stylesheet" type="text/css">

<script src="<?php print $base_path.$directory?>/js/jquery.min.js" type="text/javascript"></script>
<script src="<?php print $base_path.$directory?>/js/jplayer200/jquery.jplayer.min.js" type="text/javascript"></script>
<!---->
<script src="<?php print $base_path.$directory?>/js/mobile.jplayer.js" type="text/javascript"></script>

<script type="text/javascript">	
	$(function(){
		var pager = $('ul.pager').parent().clone();
		$('.view-smart-mobile').prepend(pager);
		$('li.pager-first a').html('«首页');
		$('li.pager-previous a').html('‹前页');
		$('li.pager-next a').html('后页›');
		$('li.pager-last a').html('末页»');
	
	});
</script>
</head>
<body class="<?php print $body_classes; ?>">
<?php if ($content_top): ?>
	<div id="content-top">
	  <?php print $content_top; ?>
	</div> <!-- /#content-top -->
<?php endif; ?>

<?php print $content; ?>   	 
</body>
</html>