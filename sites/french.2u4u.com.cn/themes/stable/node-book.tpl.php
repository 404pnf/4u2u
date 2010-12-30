<div class="node <?php print $classes; ?>" id="node-<?php print $node->nid; ?>">
  <div class="node-inner">

    <?php if (!$page): ?>
      <h2 class="title"><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
    <?php endif; ?>
	
	<?php if(strlen($node->field_zuozhe[0]['view'])>2): ?>		  
		<div class="field_zuozhe"> 
			<span class="field_content"><?php print $node->content['field_zuozhe']['#children']?></span>
		</div>
	<?php  endif ?>
	
    <?php if ($submitted): ?>
      <span class="submitted clear"><?php print $submitted; ?></span>
    <?php endif; ?>	
	
	<?php if ($terms): ?>
       <div class="taxonomy clear"><span class="field_label">标签：</span><?php print $terms; ?></div>
    <?php endif;?>

	

    <div class="content clear">
      <?php if(strlen($node->content['body']['#value'])>2):?>		  
		<div class="field_body"> 
			<span class="field_content"><?php print $node->content['body']['#value']; ?></span>
		</div>
	  <?php endif ?>
    </div>

    
    <?php if ($links): ?> 
      <div class="links clear"> <?php print $links; ?></div>
    <?php endif; ?>

  </div> <!-- /node-inner -->
</div> <!-- /node-->
