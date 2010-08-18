<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

  <head>
    <title><?php print $head_title; ?></title>
    <?php print $head; ?>
    <?php print $styles; ?>
	
	<?php print $scripts; ?>
	<SCRIPT type="text/javascript" src="<?php print $base_path.$directory?>/js/jquery-ui.min.js"></SCRIPT>
	<SCRIPT type="text/javascript" src="<?php print $base_path.$directory?>/js/jquery.spasticNav.js"></SCRIPT>
	
    <!--[if lte IE 6]><style type="text/css" media="all">@import "<?php print $base_path . path_to_theme() ?>/css/ie6.css";</style><![endif]-->
    <!--[if IE 7]><style type="text/css" media="all">@import "<?php print $base_path . path_to_theme() ?>/css/ie7.css";</style><![endif]-->
  </head>

  <body class="<?php print $body_classes; ?>">
    
    <div id="skip"><a href="#content">Skip to Content</a> <a href="#navigation">Skip to Navigation</a></div>  
    <div id="page">

    <!-- ______________________ HEADER _______________________ -->
	
<!-- whx 修改logo的alt以及rel-->
    <div id="header">
	<div id="header-middle">
      <div id="logo-title">
	
        <?php if (!empty($logo)): ?>
		  <a href="<?php print $front_page; ?>" title="<?php print $site_name; ?>" rel="home" id="logo">
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
			
			  <?php $node=node_load(arg(1));if($nodt->type == 'readthink'): ?>
				<?php print $breadcrumb; ?>
			  <?php endif; ?>

              <?php if ($title): ?>
                <h1 class="title"><?php print $title; ?></h1>
              <?php endif; ?>

              <?php if ($mission): ?>
                <div id="mission"><?php print $mission; ?></div>
              <?php endif; ?>

              <?php print $messages; ?>

              <?php print $help; ?> 

              <?php if ($tabs): ?>
                <div class="tabs"><?php print $tabs; ?></div>
              <?php endif; ?>

            </div> <!-- /#content-header -->
          <?php endif; ?>

          <div id="content-area">
                    <div id="mobile_dl" class="dlmain">
                      <div id="mobile_title" class="dltitle">
                        <div class="dlname">
                          手机资源下载
                        </div>
                      </div>
					 <div id="learning_dl_content" class="dl_content">
                      <div class="dlsearch1">
                        <?php print $download_search; ?>
                      </div>
                      <div class="dlsearch2">
                        <div id="tab_area1" class="dlcontent tab_area" >
                          <ul id="dl-tabs0" class="dl-tabs">
							<!--<div class="tab_label">价格区间：</div>-->
                            <li id="tab1" class="tabs active">
                              <a href="/dlprice/2" target="_blank">5元专区</a>
                            </li>
                            <li id="tab2" class="tabs">
                              <a href="/dlprice/3" target="_blank">10元专区</a>
                            </li>
                            <li id="tab3" class="tabs">
                              <a href="/dlprice/0" target="_blank">免费资源</a>
                            </li>
                          </ul>
                          <div id="dl-panes0" class="dl-panes clear">
							<div id="pane_tab1" class="pane">
                              <? print views_embed_view('product_dl', $display_id = 'attachment_1');?>
							  
								<div id="mobile1_gundong" class="gundong">
									<span> 	5元区其他下载	</span>
									<a id="next1" ></a><!--向后滚动的按钮 因为float是right，所以next与prev调换位置-->
									<div class="navi"></div><!-- navigator 确定每个页面的圆圈-->
									<a id="prev1"></a><!--向前滚动的按钮-->
								<? print views_embed_view('product_dl', $display_id = 'attachment_5');?>
								</div>

                            </div>
                            <div id="pane_tab2" class="pane">
                              <? print views_embed_view('product_dl', $display_id = 'attachment_2');?>
							  
								<div id="mobile2_gundong" class="gundong">
									<span> 	10元区其他下载	</span>
									<a id="next2" ></a><!--向后滚动的按钮 因为float是right，所以next与prev调换位置-->
									<div class="navi"></div><!-- navigator 确定每个页面的圆圈-->
									<a id="prev2"></a><!--向前滚动的按钮-->
								<? print views_embed_view('product_dl', $display_id = 'attachment_6');?>
								</div>
							</div>
							<div id="pane_tab3" class="pane">
                              <? print views_embed_view('product_dl', $display_id = 'attachment_3');?>
							  
								<div id="mobile3_gundong" class="gundong">
									<span> 	免费资源其他下载	</span>
									<a id="next3" ></a><!--向后滚动的按钮 因为float是right，所以next与prev调换位置-->
									<div class="navi"></div><!-- navigator 确定每个页面的圆圈-->
									<a id="prev3"></a><!--向前滚动的按钮-->
									<? print views_embed_view('product_dl', $display_id = 'attachment_7');?>
								</div>
                            </div>
                          </div>
                        </div>
						</div>
                      </div>
                    </div><!--手机资源下载 结束-->

                    <div id="learning_dl" class="dlmain">
                      <div id="learning_title" class="dltitle">
                        <div class="dlname">
                          学习机资源免费下载
                        </div>
                      </div>
					  <div id="learning_dl_content" class="dl_content">
                      <div class="jianjie">
						<? print views_embed_view('product_dl', $display_id = 'attachment_4');?>
                      </div>
                      <div class="dlsearch2">
                        <div class="dl_next_title">
                          按积分查找
                        </div>
						
						<div id="tab_area2" class="dlcontent tab_area" >
                          <ul id="dl-tabs0" class="dl-tabs">
                            <li id="tab4" class="tabs active">
                              <a href="/learningfreedl/9991" target="_blank">新标准一起</a>
                            </li>
                            <li id="tab5" class="tabs">
                              <a href="/learningfreedl/9992" target="_blank">新标准三起</a>
                            </li>
                            <li id="tab6" class="tabs">
                              <a href="/learningfreedl/9993" target="_blank">新标准初中</a>
                            </li>
							<li id="tab7" class="tabs">
                              <a href="/learningfreedl/9994" target="_blank">新标准高中</a>
                            </li>
                          </ul>
                          <div id="dl-panes0" class="dl-panes clear">
							<div id="pane_tab4" class="pane">
                              <div id="learning1_gundong" class="gundong">
									<a id="next4" ></a><!--向后滚动的按钮 因为float是right，所以next与prev调换位置-->
									<div class="navi"></div><!-- navigator 确定每个页面的圆圈-->
									<a id="prev4"></a><!--向前滚动的按钮-->
								<? print views_embed_view('product_dl', $display_id = 'attachment_8');?>
							   </div>	
                            </div>
                            <div id="pane_tab5" class="pane">
								<div id="learning2_gundong" class="gundong">
									<a id="next5" ></a><!--向后滚动的按钮 因为float是right，所以next与prev调换位置-->
									<div class="navi"></div><!-- navigator 确定每个页面的圆圈-->
									<a id="prev5"></a><!--向前滚动的按钮-->
								<? print views_embed_view('product_dl', $display_id = 'attachment_9');?>
								</div>
							</div>
							<div id="pane_tab6" class="pane">
                              <div id="learning3_gundong" class="gundong">
									<a id="next6" ></a><!--向后滚动的按钮 因为float是right，所以next与prev调换位置-->
									<div class="navi"></div><!-- navigator 确定每个页面的圆圈-->
									<a id="prev6"></a><!--向前滚动的按钮-->
								<? print views_embed_view('product_dl', $display_id = 'attachment_10');?>
							   </div>	
                            </div>
                            <div id="pane_tab7" class="pane">
								<div id="learning4_gundong" class="gundong">
									<a id="next7" ></a><!--向后滚动的按钮 因为float是right，所以next与prev调换位置-->
									<div class="navi"></div><!-- navigator 确定每个页面的圆圈-->
									<a id="prev7"></a><!--向前滚动的按钮-->
								<? print views_embed_view('product_dl', $display_id = 'attachment_11');?>
								</div>
							</div>
                          </div>
                        </div>
                      </div>
					 </div>
                    </div><!--学习机资源下载 结束-->
            </div> <!-- /#content-area -->

          <?php print $feed_icons; ?>

          <?php if ($content_bottom): ?>
            <div id="content-bottom">
              <?php print $content_bottom; ?>
            </div><!-- /#content-bottom -->
          <?php endif; ?>

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
	  

	
	<?php if($closure_region): ?>
		<div id="closure_region">
			<?php print $closure_region; ?>
		</div>
	<?php endif; ?>

<script type="text/javascript">
	function tabs_hover(tab_area) {
        var hl=$(tab_area+" li.tabs"),content=$(tab_area+" .pane");
		//alert(tab_area);
        hl.mouseover(function() {
			
            $(tab_area+" .dl-tabs li.tabs").removeClass("active");
            $(this).addClass("active");
            content.hide();
            $(tab_area+" #pane_"+this.id).show();
			//alert(tab_area+" #pane_"+this.id);
            return false;
            });
        $(hl[0]).addClass("active");
	} 
	$(tabs_hover("#tab_area1"));
	$(tabs_hover("#tab_area2"));
</script>
<SCRIPT>
// perform JavaScript after the document is scriptable.
$(function() {
	// setup ul.tabs to work as tabs for each div directly under div.panes
	//$("ul.dl-tabs").tabs("dl-pane > div");
	
	$("div.view-display-id-attachment_5").scrollable({
		size: 5,
		vertical:false,
		clickable:false,
		navi:'.navi',
		items:'.view-content',
		prevPage:'#prev1',//跳转到上一页
		nextPage:'#next1',//跳转到下一页
		//hoverClass: 'hover',
		easing:'linear'
	});
	$("div.view-display-id-attachment_6").scrollable({
		size: 5,
		vertical:false,
		clickable:false,
		navi:'.navi',
		items:'.view-content',
		prevPage:'#prev2',//跳转到上一页
		nextPage:'#next2',//跳转到下一页
		//hoverClass: 'hover',
		easing:'linear'
	});
	$("div.view-display-id-attachment_7").scrollable({
		size: 5,
		vertical:false,
		clickable:false,
		navi:'.navi',
		items:'.view-content',
		prevPage:'#prev3',//跳转到上一页
		nextPage:'#next3',//跳转到下一页
		//hoverClass: 'hover',
		easing:'linear'
	});
	$("div.view-display-id-attachment_8").scrollable({
		size: 5,
		vertical:false,
		clickable:false,
		navi:'.navi',
		items:'.view-content',
		prevPage:'#prev4',//跳转到上一页
		nextPage:'#next4',//跳转到下一页
		//hoverClass: 'hover',
		easing:'linear'
	});
	$("div.view-display-id-attachment_9").scrollable({
		size: 5,
		vertical:false,
		clickable:false,
		navi:'.navi',
		items:'.view-content',
		prevPage:'#prev5',//跳转到上一页
		nextPage:'#next5',//跳转到下一页
		//hoverClass: 'hover',
		easing:'linear'
	});
	$("div.view-display-id-attachment_10").scrollable({
		size: 5,
		vertical:false,
		clickable:false,
		navi:'.navi',
		items:'.view-content',
		prevPage:'#prev6',//跳转到上一页
		nextPage:'#next6',//跳转到下一页
		//hoverClass: 'hover',
		easing:'linear'
	});
	$("div.view-display-id-attachment_11").scrollable({
		size: 5,
		vertical:false,
		clickable:false,
		navi:'.navi',
		items:'.view-content',
		prevPage:'#prev7',//跳转到上一页
		nextPage:'#next7',//跳转到下一页
		//hoverClass: 'hover',
		easing:'linear'
	});
});

</SCRIPT>	
<?php print $closure; ?>
  </body>
</html>
