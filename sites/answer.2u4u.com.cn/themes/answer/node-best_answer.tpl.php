<indexAreaStart></indexAreaStart>
<div class="node <?php print $classes; ?>" id="node-<?php print $node->nid; ?>">
  <div class="node-inner">
	
	<?php if (!empty($title)): ?>
		<div class="title_bg"><h1 class="title"><?php print $title; ?></h1></div>
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
	<indexAreaEnd></indexAreaEnd>
	<?php if ($links): ?> 
		  <div class="links clear"> <?php print $links; ?></div>
	<?php endif; ?>
		
  </div> <!-- /node-inner -->
</div> <!-- /node-->

<div class="node_bestanswer">
	<?php print drupal_render($bestanswer); ?>
</div>
