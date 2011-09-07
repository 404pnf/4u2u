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
		  <a href="http://t.2u4u.com.cn"  title="悠游网" rel="home" id="logo">
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

              <?php if(!empty($title) && $node->type != 'ebook'): ?>
                <div class="title_bg"><h1 class="title"><?php print $title; ?></h1></div>
              <?php endif; ?>

              <?php print $messages; ?>

              <?php print $help; ?> 

              <?php if ($tabs): ?>
                <div class="tabs"><?php print $tabs; ?></div>
              <?php endif; ?>

            </div> <!-- /#content-header -->
          <?php endif; ?>

	  <div id="content-area">

	    <div id="content-area-top"> 
			<div id="zhongdiantuijian" class="clearfix">
				<div class="tuijiantitle">       推荐阅读    </div>
				<div id="huandengpian">	<!-- 幻灯片切换 -->
							  <? print views_embed_view('whx_yuedu', $display_id = 'attachment_11');?>
				</div>
				
				<div id="zhongdian" class="view-whx-yuedu">
							 <? print views_embed_view('whx_yuedu', $display_id = 'attachment_1');?> 
				</div>
		  </div>
     </div>
             
            <?php //print $content; ?>
          </div> <!-- /#content-area -->
    
          <?php print $feed_icons; ?>

         
            <div id="content-bottom">
               <?php $block = module_invoke('sina_open', 'block', 'view', 5); ?>
              <?php print $block['content']; ?> 
              	
              <?php print $content_bottom; ?>
            </div><!-- /#content-bottom -->
          

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
	
	<?php print $scripts; ?>
<script type="text/javascript">
	var staticObj = {};
	staticObj.timer = "";
	staticObj.timer2 = "";
	current = 0;

	var content1=$("#huandengpian .views-row .views-field-field-slideshow-cover-fid"),
		content2=$("#huandengpian .views-row .views-field-title");
		content3=$("#huandengpian .views-row .views-field-body");
			
	function huandengpian_next(type,element_prefix, last) {
		
			current=current+1;
			if(current==last+1) current=1;
			
			$(".views-row").removeClass("on");
            $(element_prefix+current).addClass("on");
			content1.hide();content2.hide();content3.hide();
			$("div.on .views-field-field-slideshow-cover-fid").show();
			$("div.on .views-field-title").show();
			$("div.on .views-field-body").show();
			
		if(type == "mouseover")	{
			clearInterval(staticObj.timer);
			staticObj.timer2 = setTimeout(function(){clearTimeout(staticObj.timer2);},100);
			
			staticObj.timer = setInterval(function(){huandengpian_next('auto','#huandengpian .views-row-',4)}
			,4000);
		} 
		
    };
	
	
	$(function(){
		huandengpian_next('auto','#huandengpian .views-row-',4);current = 1;
	staticObj.timer = setInterval(function(){huandengpian_next('auto','#huandengpian .views-row-',4)}
	,4000);
	
	var h2=$("#huandengpian .views-row");	
	h2.hover(function() {
		current=h2.index(this);
		huandengpian_next('mouseover','#huandengpian .views-row-',4);		
        return false;
    },function() {});  
	
	
	});
</script>
<script type="text/javascript">
var _bdhmProtocol = (("https:" == document.location.protocol) ? " https://" : " http://");
document.write(unescape("%3Cscript src='" + _bdhmProtocol + "hm.baidu.com/h.js%3F116fea821e3bfb6c5a7d4b187a50b502' type='text/javascript'%3E%3C/script%3E"));
</script>	
<SCRIPT type="text/javascript" src="<?php print $base_path.$directory?>/js/jquery-ui.min.js"></SCRIPT>

<script type="text/javascript">
var e_addhover2='.view-whx-yuedu  .view-display-id-attachment_1 .item-list';
var e_hovered2='.view-whx-yuedu  .view-display-id-attachment_1 div.hover ul';
var e_detail_tip2='.view-whx-yuedu  .view-display-id-attachment_1 div.hover .views-row';

function element_add_hover(e_addhover,e_hovered,e_detail_tip){
	$(e_addhover).hover(function(){
		$(this).addClass('hover');
		
		var that = this; 
		var thisX = $('img', that).offset().left;
		var thisY = $('img', that).offset().top;
		var ml = $('img', that).width() + 10;
		
		$('body').append('<div class="detail-tip shadow-right"></div>');
        $('.detail-tip').html($(e_detail_tip).html());
        $('.detail-tip').append('<span class="arrow-left"></span>').css('left', thisX + ml).css('top', thisY); 
	},function(){
		$(this).removeClass('hover');
		$('.detail-tip').remove();
	});
}
$(document).ready(function(){
	element_add_hover(e_addhover2,e_hovered2,e_detail_tip2);
    
	$("div.view-whx-yuedu div.view-display-id-attachment_1").scrollable({
		size: 9,
		vertical:false,
		clickable:false,
		navi:'#navi2',
		items:'.view-content',
		prevPage:'#prev2',//跳转到上一页
		nextPage:'#next2',//跳转到下一页
		hoverClass: 'hover',
		easing:'linear'
	});
});

</script>	

	<?php print $closure; ?>
  </body>
</html>
