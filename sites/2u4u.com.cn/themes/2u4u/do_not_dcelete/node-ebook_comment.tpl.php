<?php
/**
 * For comments as nodes to work, we need to know in advance what node types
 * will be used as comments and theme them differently. In particular, pay
 * attention to the way the title is output. This tpl.php assumes a content
 * type called "comment".
 */
 ?>
<div class="ebook-comment comment comment-published comment-container clearfix">
<div class="comment-inner">
<div class="comment-corner-tl corners-4x4 ctl"></div>
<div class="comment-corner-tr corners-4x4 ctr"></div>
<div class="comment-corner-links-bl corners-4x4 cbl"></div>
<div class="comment-corner-links-br corners-4x4 cbr"></div>
<div class="comment-bubble"></div>



<div id="node-<?php print $node->nid; ?>" class="node<?php if ($sticky) { print ' sticky'; } ?><?php if (!$status) { print ' node-unpublished'; } ?>">
<div class="comment-user-picture"><?php print $picture ?></div>

  <?php if ($submitted): ?>
   <div class="comment-meta clearfix">
<div class="submitted"><?php print t('!date — !username', array('!username' => theme('username', $node), '!date' => format_date($node->created))); ?></div>
</div>
  <?php endif; ?>

  <div class="content">
<div class="content"><?php print $content ?></div>
  </div>

    <?php if ($links): ?>
      <div class="links clear-block"><?php print $links; ?></div>
    <?php endif; ?>
  </div>

</div>
</div>
