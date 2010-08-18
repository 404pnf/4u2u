<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>">

<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>
<?php $node_url=drupal_get_path_alias($_GET['q']);?>
<?php $pos=strpos($node_url,'dalibao');?>
<?php if($pos!== false ): ?>
<LINK href="/misc/dalibao.css" type="text/css" rel="stylesheet">
<?php endif;?>
  <?php print $scripts; ?>
</head>
<body class="<?php print $body_classes; ?>">

  <div id="page"><div id="page-inner">

    <a name="top" id="navigation-top"></a>
    <?php if ($primary_links || $secondary_links || $navbar): ?>
      <div id="skip-to-nav"><a href="#navigation"><?php print t('Skip to Navigation'); ?></a></div>
    <?php endif; ?>

    <div id="header"><div id="header-inner" class="clear-block">

      <?php if ($logo || $site_name || $site_slogan): ?>
        <div id="logo-title">

          <?php if ($logo): ?>
            <div id="logo"><a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" id="logo-image" /></a></div>
          <?php endif; ?>

          <?php if ($site_name): ?>
            <?php if ($title): ?>
              <div id="site-name"><strong>
                <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">
                <?php print $site_name; ?>
                </a>
              </strong></div>
            <?php else: ?>
              <h1 id="site-name">
                <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">
                <?php print $site_name; ?>
                </a>
              </h1>
            <?php endif; ?>
          <?php endif; ?>

          <?php if ($site_slogan): ?>
            <div id="site-slogan"><?php print $site_slogan; ?></div>
          <?php endif; ?>

        </div> <!-- /#logo-title -->
      <?php endif; ?>

      <?php if ($header): ?>
        <div id="header-blocks" class="region region-header">
          <?php print $header; ?>
        </div> <!-- /#header-blocks -->
      <?php endif; ?>

    </div></div> <!-- /#header-inner, /#header -->

	 <?php if ($search_box || $primary_links || $secondary_links || $navbar): ?>
        <div id="navbar" class="clearfix"><div id="navbar-inner" class="clear-block region region-navbar">

          <a name="navigation" id="navigation"></a>


          <?php if ($primary_links): ?>
            <div id="primary">
              <div id="primary_menu">
                <?php print theme('links', $primary_links); ?>
                <?php if ($search_box && !$is_front): ?>
	            <div id="search-box">
	              <?php print $search_box; ?>
	            </div> <!-- /#search-box -->
	          <?php endif; ?>
              </div>
            </div> <!-- /#primary -->
          <?php endif; ?>

          <?php if ($secondary_links): ?>
            <div id="secondary">
              <?php print theme('links', $secondary_links); ?>
            </div> <!-- /#secondary -->
          <?php endif; ?>

          <?php print $navbar; ?>

        </div></div> <!-- /#navbar-inner, /#navbar -->
      <?php endif; ?>


    <div id="main"><div id="main-inner" class="clear-block<?php if ($search_box || $primary_links || $secondary_links || $navbar) { print ' with-navbar'; } ?>">

    <?php if ($content_header): ?>
      <div id="content_header" class="clear-block "><div id="content_header-inner">
        <?php print $content_header; ?>
      </div></div> <!-- /#content_header-inner, /#content_header -->
    <?php endif; ?>

      <div id="content" class="<?php if ($content_header) { print 'with-content_header'; } ?>"><div id="content-inner">

        <?php if ($mission): ?>
          <div id="mission"><?php print $mission; ?></div>
        <?php endif; ?>

        <?php if ($content_top): ?>
          <div id="content-top" class="region region-content_top">
            <?php print $content_top; ?>
          </div> <!-- /#content-top -->
        <?php endif; ?>

        <?php if ($breadcrumb || $title || $tabs || $help || $messages): ?>
          <div id="content-header">
			<?php if ($breadcrumb && !$is_front):?>
				<?php $node=node_load(arg(1));if($nodt->type == 'readthink'): ?>
				<div class="breadcrumb">  <?php print $breadcrumb; ?> </div>
				<?php endif; ?>
			<?php endif; ?>
          <?php if ($title && !$is_front  && $node->type != 'tu2shu1chan3pin3' && $node->type != 'panel' && $node->type != 'best_answer' && $node->type != 'og_group' && $node->nid != 22022 &&$node->nid != 55446 && $node->nid != 10395 && $node->nid != 50487&& $node->nid != 50521): ?>
 <h1 class="title"> <span class="title-left"></span><span class="title-content"><?php print $title; ?></span><span class="title-right"></span></h1>
             <?php endif; ?>
            <?php print $messages; ?>
            <?php if ($tabs): ?>
              <div class="tabs"><?php print $tabs; ?></div>
            <?php endif; ?>
            <?php print $help; ?>
          </div> <!-- /#content-header -->
        <?php endif; ?>
	
	<?php if ($node->nid != 50487 && $node->nid != 50521): ?>	<!-- yuedulibrary && quizceter  not show "content area"-->
        	<div id="content-area">
         		 <?php print $content; ?>
       	 </div>
	<?php endif; ?>

        <?php if ($feed_icons): ?>
          <div class="feed-icons"><?php print $feed_icons; ?></div>
        <?php endif; ?>

        
        <div id="content-bottom" class="region region-content_bottom">
          <?php if ($content_bottom): ?>
            <?php print $content_bottom; ?>
          <?php endif; ?>
        </div> <!-- /#content-bottom -->
        

      </div></div> <!-- /#content-inner, /#content -->

      <?php if ($left): ?>
        <div id="sidebar-left" class="<?php if ($content_header) { print 'with-content_header'; } ?>"><div id="sidebar-left-inner" class="region region-left">
          <?php print $left; ?>
        </div></div> <!-- /#sidebar-left-inner, /#sidebar-left -->
      <?php endif; ?>

      <?php if ($right): ?>
        <div id="sidebar-right" class="<?php if ($content_header) { print 'with-content_header'; } ?>"><div id="sidebar-right-inner" class="region region-right">
          <?php print $right; ?>
        </div></div> <!-- /#sidebar-right-inner, /#sidebar-right -->
      <?php endif; ?>

    </div></div> <!-- /#main-inner, /#main -->

    <?php if ($footer || $footer_message): ?>
      <div id="footer"><div id="footer-inner" class="region region-footer">

        <?php if ($footer_message): ?>
          <div id="footer-message"><?php print $footer_message; ?></div>
        <?php endif; ?>

        <?php print $footer; ?>

      </div></div> <!-- /#footer-inner, /#footer -->
    <?php endif; ?>

  </div></div> <!-- /#page-inner, /#page -->

  <?php if ($closure_region): ?>
    <div id="closure-blocks" class="region region-closure"><?php print $closure_region; ?></div>
  <?php endif; ?>
 <script type="text/javascript">
var _bdhmProtocol = (("https:" == document.location.protocol) ? " https://" : " http://");
document.write(unescape("%3Cscript src='" + _bdhmProtocol + "hm.baidu.com/h.js%3F3a7af4b2789603cd3a64483ca3d1f193' type='text/javascript'%3E%3C/script%3E"));
</script> 
  <?php print $closure; ?>

	<div class="clearfix"></div>
</body>
</html>
