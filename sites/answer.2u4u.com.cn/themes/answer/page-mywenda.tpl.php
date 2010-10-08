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

    <!-- ______________________ HEADER _______________________ -->
	
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
         <?php if ($content_top): ?>
         <div id="content-top" class="clearfix"> 
			<div id="my-answer">
					<?php Global $user;?>
			<?php if($user->uid):?>
					<?php print '<a href="/mywenda/'.$user->uid.'"> 我的问答</a>'?>
			<?php else:?>
					<a href="/user"> 我的问答</a>
			<?php endif;?>
			</div>
		
			<?php print $content_top; ?>	
			<div> 
			      <div id="my-ask" class="myask">
				<a href="/node/add/best-answer" target="_blank"><img src="/sites/answer.2u4u.com.cn/themes/answer/css/images/wytw.gif"></a>
                              </div>
			      <div id="rule" class="rules"> 
				 >>><a href="/node/63611">问答帮助</a>
                              </div>
			</div>       
		</div> <!-- /#content-top -->
		<?php endif; ?>	 


   
      <div id="content">
        <div id="content-inner" class="inner column center">


          <?php if ($breadcrumb || $title || $mission || $messages || $help || $tabs): ?>
            <div id="content-header">
			
			  <?php if(!empty($node) && $node->type == 'readthink'): ?>
				<?php print $breadcrumb; ?>
			  <?php endif; ?>

              <?php if(!empty($title) && $node->nid != 55446 && $node->type != 'og_group'): ?>
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
				<script type="text/javascript">
				$(function(){
					$('a:[href^=http://test.]').attr('target','_blank');
					$('a:[href^=http://u.]').attr('target','_blank');
					$('a:[href^=http://frenchfriend.]').attr('target','_blank');
					
					$('#primary li.menu-41192 a').addClass('active');
				});
			</script>
         <script type="text/javascript">
var _bdhmProtocol = (("https:" == document.location.protocol) ? " https://" : " http://");
document.write(unescape("%3Cscript src='" + _bdhmProtocol + "hm.baidu.com/h.js%3F3a7af4b2789603cd3a64483ca3d1f193' type='text/javascript'%3E%3C/script%3E"));
</script>
	<SCRIPT type="text/javascript" src="<?php print $base_path.$directory?>/js/jquery-ui.min.js"></SCRIPT>
	<SCRIPT type="text/javascript" src="<?php print $base_path.$directory?>/js/jquery.spasticNav.js"></SCRIPT>
	
	<?php if($closure_region): ?>
		<div id="closure_region">
			<?php print $closure_region; ?>
		</div>
	<?php endif; ?>
	<?php print $closure; ?>
  </body>
</html>
