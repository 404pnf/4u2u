<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

  <head>
    <title><?php print $head_title; ?></title>
    <?php print $head; ?>
	<link href="http://2u4u.com.cn/sites/2u4u.com.cn/themes/stable/css/common.css" media="all" rel="stylesheet" type="text/css">
    <?php print $styles; ?>
    <!--[if lte IE 6]><style type="text/css" media="all">@import "<?php print $base_path . path_to_theme() ?>/css/ie6.css";</style><![endif]-->
    <!--[if IE 7]><style type="text/css" media="all">@import "<?php print $base_path . path_to_theme() ?>/css/ie7.css";</style><![endif]-->
  </head>

  <body class="<?php print $body_classes; ?>">
    
    <div id="skip"><a href="#content">Skip to Content</a> <a href="#navigation">Skip to Navigation</a></div>  
    <div id="page">

	
    <div id="header">
	<div id="header-middle">
      <div id="logo-title">
	
        <?php if (!empty($logo)): ?>
		  <a href="http://2u4u.com.cn"  title="悠游网" rel="home" id="logo">
            <img src="<?php print $logo; ?>" alt="<?php print $site_name; ?>"/>
          </a>
        <?php endif; ?>

      </div> <!-- /logo-title -->

      <?php if ($header): ?>
        <div id="header-region">
          <?php print $header; ?>
        </div>
      <?php endif; ?>

      <?php print $search_box; ?>
	</div>
	
	
	    <?php if (!empty($primary_links) or !empty($secondary_links)): ?>
          <div id="navigation" class="menu <?php if (!empty($primary_links)) { print "with-main-menu"; } if (!empty($secondary_links)) { print " with-sub-menu"; } ?>">
            <?php if (!empty($primary_links)){ print theme('links', $primary_links, array('id' => 'primary', 'class' => 'links main-menu')); } ?>
            <?php if (!empty($secondary_links)){ print theme('links', $secondary_links, array('id' => 'secondary', 'class' => 'links sub-menu')); } ?>
          </div> <!-- /navigation -->
        <?php endif; ?>
    </div> <!-- /header -->

    <!-- ______________________ MAIN _______________________ -->

    <div id="main" class="clearfix">


    
      <div id="content">
        <div id="content-inner" class="inner column center">
          <?php if ($content_top): ?>
            <div id="content-top">
              <?php print $content_top; ?>
            </div> <!-- /#content-top -->
          <?php endif; ?>
          
          <?php if ($breadcrumb || $title || $mission || $messages || $help || $tabs): ?>
            <div id="content-header">
			
			  <?php if(!empty($node) && $node->type == 'readthink'): ?>
				<?php print $breadcrumb; ?>
			  <?php endif; ?>
<!--
              <?php if(!empty($title)): ?>
                <div class="title_bg"><h1 class="title"><?php print $title; ?></h1></div>
              <?php endif; ?>
-->
              <?php print $messages; ?>

              <?php print $help; ?> 

              <?php if ($tabs): ?>
                <div class="tabs"><?php print $tabs; ?></div>
              <?php endif; ?>

            </div> <!-- /#content-header -->
          <?php endif; ?>

          <div id="content-area">
        
	   
            <div class="personal">
                <?php
                   $personal = module_invoke('my2u4u','block','view','6');
                   PRINT($personal['content']);
                 ?>

            </div>
            <?php 
                global $user;
                if ($user->uid>0){
              	    $content = file_get_contents('http://u.2u4u.com.cn/home/space.php?do=home&view=all&out=true'); print $content;}
		else print "您还没有登录";
             ?>


          </div> <!-- /#content-area -->




          <?php print $feed_icons; ?>

          <?php if ($content_bottom): ?>
            <div id="content-bottom">
              <?php print $content_bottom; ?>
            </div><!-- /#content-bottom -->
          <?php endif; ?>

          </div>
        </div> <!-- /content-inner /content -->
		<?php if ($left): ?>
          <div id="sidebar-first" class="column sidebar first">
            <div id="sidebar-first-inner" class="inner">
              <?php print $left; ?>
            </div>
          </div>
        <?php endif; ?> <!-- /sidebar-first -->
        <?php if ($right): ?> 
          <div id="sidebar-second" class="column sidebar second">
            <div id="sidebar-second-inner" class="inner">
              <?php //print $right; ?> 
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
	
	<?php print $scripts; ?>
			<script type="text/javascript">
				$(function(){
					$('a:[href^=http://test.]').attr('target','_blank');
					$('a:[href^=http://u.]').attr('target','_blank');
					$('a:[href^=http://frenchfriend.]').attr('target','_blank');
					
					$('#primary li.menu-174 a').addClass('active');
				});
			</script>
			
	<script type="text/javascript">
		$(function(){
		
			//$('.feed a:[href^=space.php]').each(function(i){
			$('.feed a[href*=.php?]').not('[href^=http://]').each(function(i){
				//alert($(this).attr('href'));
				var uchome_href = 'http://u.2u4u.com.cn/home/'+$(this).attr('href');
				$(this).attr('href',uchome_href);
			});//用户名的链接
			
			$('.feed img[src*=image]').not('[src*=http://u.2u4u.com.cn]').each(function(i){
				var uchome_src = 'http://u.2u4u.com.cn/home/'+$(this).attr('src');
				$(this).attr('src',uchome_src);
			});//调用的图片img的链接src
			
			$('.feed a[id^=feedcomment_a_op]').each(function(i){
				var uchome_href = $(this).parent().find(".feed_content .detail a").attr('href');
				$(this).attr('href',uchome_href);
			});//评论链接
			
			$('.feed a[id^=do_a_op_]').each(function(i){
				//$(this).next().wrap('<div />').attr('style','display:none');
				$(this).attr('style','display:none');
				
			});//回复链接隐藏
			
			$('a#a_feed_more').attr('href','http://u.2u4u.com.cn/home/');//查看更多动态链接到全站动态
			
		});
         function feed_more_show(feedid) {
      
             var showid = '#feed_more_'+feedid;
             var opid = '#feed_a_more_'+feedid;
             
 		 $(opid).removeAttr("onclick");
 		 
	     $(showid).attr({style:"display:block"});
	     $(showid).addClass('sub_doing');
	     $(opid).removeClass('close_class');
		 $(opid).addClass('show_class');
		
	     $(opid).html('<< 收起列表');
	     $(opid+".show_class").click(function(event) {
	     	if(this.className == "show_class")
		     	feed_more_close(feedid);
		     
		     //alert(this.className);
	     });
	     return false;
	 }
         
     function feed_more_close(feedid) {
     	
	     var showid = '#feed_more_'+feedid;
	     var opid = '#feed_a_more_'+feedid;
			       
		$(opid).removeAttr("onclick");
				          
	     $(showid).attr({style:"display:none"});
	     $(showid).removeClass('sub_doing');
	     $(opid).removeClass('show_class');
		 $(opid).addClass('close_class');
		 
	     $(opid).html('>> 更多动态');
	      $(opid+".close_class").click(function(event) {
	     	if(this.className == "close_class")
	            feed_more_show(feedid);
	             return false;
   	      });
   	      
   	      return false;
   }
   function feedcomment_get(feedid) {
   		//http://u.2u4u.com.cn/home/space.php?uid=78293&do=blog&id=43829
	}
</script>
	<script type="text/javascript">
var _bdhmProtocol = (("https:" == document.location.protocol) ? " https://" : " http://");
document.write(unescape("%3Cscript src='" + _bdhmProtocol + "hm.baidu.com/h.js%3F116fea821e3bfb6c5a7d4b187a50b502' type='text/javascript'%3E%3C/script%3E"));
</script>
        <SCRIPT type="text/javascript" src="<?php print $base_path.$directory?>/js/jquery-ui.min.js"></SCRIPT>
	<SCRIPT type="text/javascript" src="<?php print $base_path.$directory?>/js/jquery.spasticNav.js"></SCRIPT>
	<script type="text/javascript">
			$('#primary').spasticNav();
		</script>
	<?php if($closure_region): ?>
		
		<div id="closure_region">
			<?php print $closure_region; ?>
			
		</div>
	<?php endif; ?>
	<?php print $closure; ?>
  </body>
</html>
