<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

  <head>
    <title><?php print $head_title; ?></title>
    <?php print $head; ?>
    <?php print $styles; ?>
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
                <div class="title_bg"><h1 class="title"><?php print $title; ?></h1></div>
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
			    <div class="dlsearch1">
                    <?php print $download_search; ?>
                </div>
            <?php print $content; ?> 

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
	
	<?php print $scripts; ?>

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
	<SCRIPT>
// perform JavaScript after the document is scriptable.
$(function() {
	
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
});

</SCRIPT>	

	<?php print $closure; ?>
  </body>
</html>
