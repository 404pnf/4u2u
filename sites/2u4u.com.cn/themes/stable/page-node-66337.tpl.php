<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

  <head>
    <title><?php print $head_title; ?></title>
    <?php print $head; ?>

	<meta name="viewport" content="width=device-width;"/>
	
	<link href="<?php print $base_path.$directory?>/mobile/css/common.css" media="all" rel="stylesheet" type="text/css">
	
	<link href="<?php print $base_path.$directory?>/mobile/css/mfront.css" media="all" rel="stylesheet" type="text/css">

	<SCRIPT type="text/javascript" src="<?php print $base_path.$directory?>/mobile/js/jquery.js"></SCRIPT>
	<script language="javascript" type="text/javascript" src="<?php print $base_path.$directory?>/mobile/js/txgenerictools.js" ></script>
	<?php $clienttype = $_REQUEST['clienttype']; echo '<script> var clienttype = "'. $clienttype.'"; </script>';?>
	<SCRIPT type="text/javascript" src="<?php print $base_path.$directory?>/mobile/js/jquery.m2u4u.common.js"></SCRIPT>
	
  </head>

  <body class="<?php print $body_classes; ?>">
  <?php ?>
    <div id="main">
	  <div class="toolbar">
		
		<? print views_embed_view('mobile_fp', $display_id = 'attachment_11');?>
		
	  </div>
		
      <div id="content">
        <div id="content-inner" class="inner column center">
		
		
		<!--幻灯片-->
		<div id= "huandengpian" >
			<? print views_embed_view('mobile_fp', $display_id = 'attachment_10');?>	
		</div>		
		
		<!--热点推荐-->
		<div id= "rediantuijian" class="recommend-bg">
			<? print views_embed_view('mobile_fp', $display_id = 'page_2');?>				
		
		</div>
		
	  </div> 	
	</div> <!-- /main -->

	
<script type="text/javascript">
var _bdhmProtocol = (("https:" == document.location.protocol) ? " https://" : " http://");
document.write(unescape("%3Cscript src='" + _bdhmProtocol + "hm.baidu.com/h.js%3F116fea821e3bfb6c5a7d4b187a50b502' type='text/javascript'%3E%3C/script%3E"));
</script>

  </body>
</html>
