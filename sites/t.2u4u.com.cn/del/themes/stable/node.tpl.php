<div class="node <?php print $classes; ?>" id="node-<?php print $node->nid; ?>">
  <div class="node-inner">
<?php 
	$node_url=drupal_get_path_alias($_GET['q']);
	$pos=strpos($node_url,'user');
?>
    <?php if (!$page && $pos !== 0): ?>
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

    
    <?php if ($links): ?> 
      <div class="links clear"> <?php print $links; ?></div>
    <?php endif; ?>

  </div> <!-- /node-inner -->
</div> <!-- /node-->
