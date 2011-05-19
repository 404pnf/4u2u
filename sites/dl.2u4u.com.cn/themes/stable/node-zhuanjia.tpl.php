<div class="node <?php print $classes; ?>" id="node-<?php print $node->nid; ?>">
  <div class="node-inner">

    <?php if (!$page): ?>
      <h2 class="title"><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
    <?php endif; ?>

    <?php print $picture; ?>

    <?php if ($submitted): ?>
      <span class="submitted clear"><?php print $submitted; ?></span>
    <?php endif; ?>
	<?php if ($terms): ?>
       <div class="taxonomy clear"><?php print $terms; ?></div>
    <?php endif;?>

    <div class="content clear">
      <?php print $content; ?>
    </div>
    <div class="backfp"><a href="http://quiz.2u4u.com.cn">回到首页</a></div>
      <div class="home-shareto">
                                                  <!-- ShareTo Button START -->
           <a class="shareto_button" href="http://shareto.com.cn/share.html"><img src="http://video.2u4u.com.cn/site    s/video.2u4u.com.cn/themes/video/css/shipin_images/shareto.gif" alt="分享到" style="border:0"/></a>
                                                  <script type="text/javascript" src="http://s.shareto.com.cn/js/shareto_button.js"></script>
                                                  <!-- ShareTo Button END -->
      </div>

    
    <?php if ($links): ?> 
      <div class="links clear"> <?php print $links; ?></div>
    <?php endif; ?>

  </div> <!-- /node-inner -->
</div> <!-- /node-->
