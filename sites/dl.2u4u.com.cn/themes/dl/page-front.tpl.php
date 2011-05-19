<?php
// $Id: page.tpl.php,v 1.1.2.1 2010/06/17 07:54:57 sociotech Exp $
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $language->language; ?>" xml:lang="<?php print $language->language; ?>">

<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>
  <?php print $setting_styles; ?>
  <!--[if IE 8]>
  <?php print $ie8_styles; ?>
  <![endif]-->
  <!--[if IE 7]>
  <?php print $ie7_styles; ?>
  <![endif]-->
  <!--[if lte IE 6]>
  <?php print $ie6_styles; ?>
  <![endif]-->
  <?php print $local_styles; ?>
  <?php print $scripts; ?>
</head>

<body id="fp" class="front grid-type-960 grid-width-12">
  <div id="page" class="page">
    <div id="skip">
      <a href="#main-content-area"><?php print t('Skip to Main Content Area'); ?></a>
    </div>

    <div id="header-group" class="header-group row clearfix <?php print $grid_width; ?>">
      <?php print theme('grid_block', theme('links', $secondary_links), 'secondary-menu'); ?>
      <?php print theme('grid_block', $search_box, 'search-box'); ?>

      <?php if ($logo || $site_name || $site_slogan): ?>
      <div id="header-site-info" class="header-site-info block">
        <div id="header-site-info-inner" class="header-site-info-inner inner">
          <?php if ($logo): ?>
          <div id="logo">
            <a href="<?php print check_url($front_page); ?>" title="<?php print t('Home'); ?>"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /></a>
          </div>
          <?php endif; ?>
          <?php if ($site_name || $site_slogan): ?>
          <div id="site-name-wrapper" class="clearfix">
            <?php if ($site_name): ?>
            <span id="site-name"><a href="<?php print check_url($front_page); ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a></span>
            <?php endif; ?>
            <?php if ($site_slogan): ?>
            <span id="slogan"><?php print $site_slogan; ?></span>
            <?php endif; ?>
          </div><!-- /site-name-wrapper -->
          <?php endif; ?>
        </div><!-- /header-site-info-inner -->
      </div><!-- /header-site-info -->
      <?php endif; ?>

      <?php print $header; ?>
      <?php print theme('grid_block', $primary_links_tree, 'primary-menu'); ?>
    </div><!-- /header-group -->

    <div id="main" class="main row clearfix <?php print $grid_width; ?>">
      <?php if ($sidebar_first): ?>
      <div id="sidebar-first" class="sidebar-first row nested <?php print $sidebar_first_width; ?>">
        <?php print $sidebar_first; ?>
      </div><!-- /sidebar-first -->
      <?php endif; ?>

      <div id="homepage" class="main-group row nested <?php print $main_group_width; ?>">
      	<div id='resources'>	
      	
      	  	
      	  	<!--
      	  	<div id="resources-search">
		     <form id='resources-search-form' method='get' action='/'>
		     	<input type='text' id='search-title' name='search-title'></input>
		     	<button type='submit'>搜索</button>
		     </form>
			</div>
			//-->
      	
      	
      		<div id="sub-category">
			<?php 
			   $upid =$_GET['c'];
			   $title =$_GET['title'];	
			   $views_name = 'zifenlei';
			   $display_id = 'default';
			   $view_args = $upid;
			   print views_embed_view($views_name, $display_id,$view_args); 
			?>
			</div>
			
			
      		<div id="filetype">
			<ul>
			<li><a href='?c=<?php print $upid ?>&filetype=text/plain&title=<?php print $title ?>'>文本</a></li>    
			<li><a href='?c=<?php  print $upid ?>&filetype=stream/mp3&title=<?php print $title ?>'>MP3</a></li>   
			<li><a href='?c=<?php  print $upid ?>&filetype=stream/zip&title=<?php print $title ?>'>RAR</a></li>
			</ul>
			</div>			
			
			
           <div id="resources-list">
			<?php 
			   if(empty($upid))
			     $upid='all';
			   $filetype = $_GET['filetype'];
	  		   $views_name = 'ziyuanjianjie';
			   $display_id = 'page_1';
			   $view_args1 = $upid;
			   $view_args2 = $filetype;	
			  // $view_args3 = $title	;	
			   print views_embed_view($views_name, $display_id,$view_args1,$view_args2); 
			?>
			</div>
			
		</div>	

      </div><!-- /main-group -->
    </div><!-- /main -->

    <?php if ($footer): ?>
    <div id="footer" class="footer row <?php print $grid_width; ?>">
      <?php print $footer; ?>
    </div><!-- /footer -->
    <?php endif; ?>

    <?php if ($footer_message): ?>
    <div id="footer-message" class="footer-message row <?php print $grid_width; ?>">
      <?php print theme('grid_block', $footer_message, 'footer-message-text'); ?>
    </div><!-- /footer-message -->
    <?php endif; ?>
  </div><!-- /page -->
  <?php print $closure; ?>
</body>
</html>
