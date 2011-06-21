<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

  <head>
    <title>21st | 悠游网 最权威的多语种学习网站</title>
    <?php print $head; ?>
    
	<link href="<?php print $base_path . path_to_theme() ?>/js/coin-slider/coin-slider-styles.css" media="all" rel="stylesheet" type="text/css">
	  
    <?php print $styles; ?>
    
    <link type="text/css" rel="stylesheet" media="all" href="/sites/2u4u.com.cn/themes/stable/css/21st.css" />

    <!--[if lte IE 6]><style type="text/css" media="all">@import "<?php print $base_path . path_to_theme() ?>/css/ie6.css";</style><![endif]-->
    <!--[if IE 7]><style type="text/css" media="all">@import "<?php print $base_path . path_to_theme() ?>/css/ie7.css";</style><![endif]-->
	
	<?php print $scripts; ?>
	<SCRIPT type="text/javascript" src="<?php print $base_path . path_to_theme()?>/js/coin-slider/coin-slider.js"></SCRIPT>

  <body class="<?php print $body_classes; ?>">
    
    <div id="skip"><a href="#content">Skip to Content</a> <a href="#navigation">Skip to Navigation</a></div>  
    <div id="page">

	
<!-- 21sst使用的header，删除了默认的header和primary links的输出 -->
<div id="header_title"> 
    <style type="text/css"> 
.top-text{
        margin: 0px;
        font:"宋体";
        font-size:12px;
        color: #000;
}
.head-text {
        font-family: "宋体";
        font-size: 12px;
        line-height: 16px;
        color: #000;
 
}
.top-text a{color:#000;}
.top-text a:link{color:#000;}
.top-text a:visited {color:#000;}
.top-text a:hover{color:#FFFF00;}
.top-text a:active{color:#000;}
 
body {
	background-color: #F5F5F5;
}
</style> 
</head> 
<center> 
<div style="width:960px;"> 
<table width="960" border="0" align="center" cellpadding="0" cellspacing="0" style="width:960px;"> 
  <tr> 
    <td width="142" height="45" bgcolor="#ff7f07" style="width:142px;"><a href="http://2u4u.com.cn/" target="_blank"><img src="http://cdn1.2u4u.com.cn/duhougan/images/images_02.gif" width="142" height="41" border="0" /></a></td> 
    <td width="818" bgcolor="#ff7f07" style="width:818px;"><div align="center" class="top-text">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<a href="http://ebook.2u4u.com.cn" target="_blank">电子图书馆</a><span class="head-text">|</span> 
<a href="http://2u4u.com.cn/chongzhi" target="_blank">积分充值</a><span class="head-text">|</span> 
<a href="http://shop.2u4u.com.cn/libao" target="_blank">积分换礼</a><span class="head-text">|</span> 
<a href="http://quiz.2u4u.com.cn" target="_blank">测试中心</a><span class="head-text">|</span> 
<a href="http://video.2u4u.com.cn" target="_blank">多媒体课堂</a><span class="head-text">|</span> 
<a href="http://test.2u4u.com.cn/online/" target="_blank">在线词典</a><span class="head-text">|</span> 
<a href="http://2u4u.com.cn/wenda" target="_blank">有问有答</a><span class="head-text">|</span></div></td> 
</tr> 
</table></div></center>
<div style="width:960px;margin:auto"><a href="http://www.i21st.cn/" target="_blank"><img src="http://2u4u.com.cn/sites/2u4u.com.cn/themes/stable/css/images/banner_21st.gif"></a></div> 
 </div> 

    <!-- ______________________ MAIN _______________________ -->

    <div id="main" class="clearfix">
    
      <div id="content">
        <div id="content-inner" class="inner column center">

            </div> <!-- /#content-header -->

          <div id="content-area">

	<div id="left_21st">
		<div class="21st" id="zhichang">
                <a href="http://www.i21st.cn/job/" target="_blank"><h2>职场直通车</h2></a>
                <?php print views_embed_view('21st_page', $display_id = 'block_1');?>
                </div>

		<div class="21st" id="AD1">
                <?php print views_embed_view('21st_page', $display_id = 'block_8');?>
                </div>


		<div class="21st" id="translate">
                <a href="http://www.i21st.cn/translate/" target="_blank"><h2>热点翻译</h2></a>
                <?php print views_embed_view('21st_page', $display_id = 'block_2');?>
                </div>

	</div>


	 <div id="middle_21st">

		<div class="21st" id="focus">
                <?php print views_embed_view('21st_page', $display_id = 'block_3');?>
        </div>
		
		<script>
			$(document).ready(function() {
			
				$('#coin-slider').coinslider({ navigation: true,hoverPause: true,hoverPause: true,width: 200, height: 210,effect: 'straight'});
			
			});
		</script>



		<div class="21st" id="englishlearning">
                <h2>英语学习</h2>
                <?php print views_embed_view('21st_page', $display_id = 'block_5');?>
                </div>

		 <div class="21st" id="englishquiz">
                <h2>英语考试</h2>
                <?php print views_embed_view('21st_page', $display_id = 'block_6');?>
                </div>

	</div> 


	<div id="right_21st">
		
		<div class="21st" id="RSS">
				<h2>订阅更精彩</h2>
			<?php $block = module_invoke('block', 'block', 'view', 83); 
			print $block['content'];
			?>
		</div>
	<!--
		<div class="21st" id="newspaper">
                <?php print views_embed_view('21st_page', $display_id = 'block_10');?>
                </div>
	-->		
		<div class="21st" id="baowanglianxian">
                <h2>报网连线</h2>
                <?php print views_embed_view('21st_page', $display_id = 'block_7');?>
                </div>
		
		<div class="21st" id="AD2">
                <?php print views_embed_view('21st_page', $display_id = 'block_9');?>
                </div>



	</div>
		
			
		
		
          </div>
        </div> <!-- /content-inner /content -->

        <?php if ($right): ?>
          <div id="sidebar-second" class="column sidebar second">
            <div id="sidebar-second-inner" class="inner">
              <?php print $right; ?>
            </div>
          </div>
        <?php endif; ?> <!-- /sidebar-second -->

      </div> <!-- /main -->

      <!-- ______________________ FOOTER _______________________ -->

      <?php if(!empty($footer_message) || !empty($footer_block)): ?>
        <div id="footer">
          <?php print $footer_message; ?>
          <?php print $footer_block; ?>
        </div> <!-- /footer -->
      <?php endif; ?>

    </div> <!-- /page -->
	
	
	<script type="text/javascript">
var _bdhmProtocol = (("https:" == document.location.protocol) ? " https://" : " http://");
document.write(unescape("%3Cscript src='" + _bdhmProtocol + "hm.baidu.com/h.js%3F116fea821e3bfb6c5a7d4b187a50b502' type='text/javascript'%3E%3C/script%3E"));
</script>
        <SCRIPT type="text/javascript" src="<?php print $base_path.$directory?>/js/jquery-ui.min.js"></SCRIPT>
	<SCRIPT type="text/javascript" src="<?php print $base_path.$directory?>/js/jquery.spasticNav.js"></SCRIPT>
	
	<?php if($closure_region): ?>
		<div id="closure_region">
			<?php print $closure_region; ?>
			<script type="text/javascript">
				$(function(){$('a:[href^=http][href*=2u4u.com.cn]').attr('target','_blank');});
			</script>
		</div>
	<?php endif; ?>
	<?php print $closure; ?>
  </body>
</html>
