<div class="node <?php print $classes; ?>" id="node-<?php print $node->nid; ?>">
  <div class="node-inner">
   	<indexAreaStart><!--  索引内容 开始 --></indexAreaStart>
    <?php if (!$page): ?>
      <h2 class="title"><?php print $title; ?></h2>
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
<indexAreaEnd><!--  索引内容 结束 --></indexAreaEnd>
    <div class="backfp"><a href="http://2u4u.com.cn">回到首页</a></div>
    <div class="home-shareto">  
                                                <!-- ShareTo Button START -->
                                                <a class="shareto_button" href="http://shareto.com.cn/share.html"><img src="http://video.2u4u.com.cn/sites/video.2u4u.com.cn/themes/video/css/shipin_images/shareto.gif" alt="分享道" style="border:0"/></a>
                                                <script type="text/javascript" src="http://s.shareto.com.cn/js/shareto_button.js"></script>
                                                <!-- ShareTo Button END -->
     
    </div>

    <?php if ($links): ?> 
      <div class="home-links"> <?php print $links; ?></div>
    <?php endif; ?>

  </div> <!-- /node-inner -->
</div> <!-- /node-->
