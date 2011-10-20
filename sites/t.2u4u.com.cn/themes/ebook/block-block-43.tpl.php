<div id="block-<?php print $block->module .'-'. $block->delta ?>" >
  <div class="block-inner">

    <?php if (!empty($block->subject)): ?>
      <div class="block-title-bg"><h3 class="title block-title"><?php print $block->subject; ?></h3></div>
    <?php endif; ?>

    <div class="content">
      <?php print $block->content; ?>
    </div>

    <?php print $edit_links; ?>

  </div> <!-- /block-inner -->
</div> <!-- /block -->