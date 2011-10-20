<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

  <head>
    <title><?php print $head_title; ?></title>
    <?php print $head; ?>
	
	<meta name="viewport" content="width=device-width;"/>
	
	<link href="/sites/2u4u.com.cn/themes/stable/mobile/css/common.css" media="all" rel="stylesheet" type="text/css">
	<link href="<?php print $base_path.$directory?>/mobile/css/mobile.css" media="all" rel="stylesheet" type="text/css">
	
	<SCRIPT type="text/javascript" src="/sites/2u4u.com.cn/themes/stable/mobile/js/jquery.js"></SCRIPT>
	<script src="/sites/ebook.2u4u.com.cn/themes/ebook/js/jquery.tools.min.js" type="text/javascript"></script>
	
	<?php $clienttype = $_REQUEST['clienttype']; echo '<script> var clienttype = "'. $clienttype.'"; </script>';?>
	<SCRIPT type="text/javascript" src="/sites/2u4u.com.cn/themes/stable/mobile/js/jquery.m2u4u.common.js"></SCRIPT>
	
  </head>

  <body class="<?php print $body_classes; ?>">

    <div id="main" class="clearfix">
    <!--	<div class="toolbar">
			
			<? print views_embed_view('mobile_fp', $display_id = 'attachment_11');?>
			
		</div>
	-->		
	  <div class="topterm">
		<a id="prev" class=""></a><!--向前滚动的按钮-->
		<div class="termcover">
			<div class="termcontent">
				<div class="list"><a href="/mobile/yuedu/2012">儿童英语</a><br/><a href="/mobile/yuedu/2013">中小学英语</a></div>
				<div class="list"><a href="/mobile/yuedu/2015">大学英语教程</a><br/><a href="/mobile/yuedu/9307">英汉对照读物</a></div>
				<div class="list"><a href="/mobile/yuedu/9308">简易英语读物</a><br/><a href="/mobile/yuedu/9309">大众英语读物</a></div>
				<div class="list"><a href="/mobile/yuedu/9310">精选英文原著</a><br/><a href="/mobile/yuedu/2018">英语考试用书</a></div>
				<div class="list"><a href="/mobile/yuedu/2019">英语学术文集</a><br/><a href="/mobile/yuedu/2023">英语专项训练</a></div>
				<div class="list"><a href="/mobile/yuedu/8680">实用英语</a><br/><a href="/mobile/yuedu/11123">其他语种电子书</a></div>
			</div>
		</div>
		<a id="next" class=""></a><!--向后滚动的按钮 -->
     </div>
     
     <div id="content">
        <div id="content-inner" class="inner column center">
        	
			
			<?php print $content; ?>
		</div> 
	  </div> 	
	</div> <!-- /main -->

	
<script type="text/javascript">
$(function(){

	if(clienttype == 'iphone'){
		$(".termcover").scrollable({
			size: 2,
			vertical:false,
			clickable:false,
			//navi:'#navi2',
			items:'.termcontent',
			prevPage:'#prev',//跳转到上一页
			nextPage:'#next',//跳转到下一页
			hoverClass: 'hover',
			easing:'linear'
		}); 
	}
	else{
		$(".termcover").scrollable({
			size: 3,
			vertical:false,
			clickable:false,
			//navi:'#navi2',
			items:'.termcontent',
			prevPage:'#prev',//跳转到上一页
			nextPage:'#next',//跳转到下一页
			hoverClass: 'hover',
			easing:'linear'
		}); 
	}
});

var _bdhmProtocol = (("https:" == document.location.protocol) ? " https://" : " http://");
document.write(unescape("%3Cscript src='" + _bdhmProtocol + "hm.baidu.com/h.js%3F116fea821e3bfb6c5a7d4b187a50b502' type='text/javascript'%3E%3C/script%3E"));
</script>

	
	<?php //print $closure; ?>
  </body>
</html>
