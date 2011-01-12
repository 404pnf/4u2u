<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
  <head>
    
    <title><?php print $head_title; ?></title>
<meta name="viewport" content="width=device-width,minimum-scale=1.0,maximum-scale=1.0" />
    <link type="text/css" rel="stylesheet" media="all" href="/<?php print drupal_get_path(theme, taiyanghua) ?>/less/taiyanghua.less" />     
    <script src="/sites/2u4u.com.cn/themes/stable/js/jquery-1.4.2.js" type="text/javascript"></script>
    <!--[if !IE]>
	<link rel="stylesheet" href="iphone-only.css" type="text/css" media="only screen and (max-device-width: 480px)" />
    <![endif]-->	
<script type="text/javascript">
	$(function(){
		
		$('.view-whx-quiz .views-row').hover(function(){
			$(this).addClass('hover');
		},function(){
			$(this).removeClass('hover');
		});
		$('.view-whx-quiz .views-row').click(function(){
			var href = $(this).find('.views-field-title a').attr('href');
	//		alert(href);
			window.location.href=href;
		});
	});
</script>
</head>

    <div id="page">

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

              <?php print $breadcrumb; ?>

              <?php if ($title): ?>
                <h1 class="title"><?php print $title; ?></h1>
              <?php endif; ?>


              <?php print $messages; ?>

              <?php print $help; ?> 

              <!-- <?php if ($tabs): ?>
                <div class="tabs"><?php print $tabs; ?></div>
              <?php endif; ?> -->

            </div> <!-- /#content-header -->
          <?php endif; ?>

          <div id="content-area">
            <?php print $content; ?>
          </div> <!-- /#content-area -->

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
        <?php endif; ?> 

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
    <?php print $closure; ?>
  </body>
</html>
