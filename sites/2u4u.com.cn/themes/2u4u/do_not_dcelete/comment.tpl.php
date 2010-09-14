<div class="comment-blog comment comment-published comment-container clearfix">
<div class="comment-inner">
<div class="comment-corner-tl corners-4x4 ctl"></div>
<div class="comment-corner-tr corners-4x4 ctr"></div>
<div class="comment-corner-links-bl corners-4x4 cbl"></div>
<div class="comment-corner-links-br corners-4x4 cbr"></div>
<div class="comment-bubble"></div>


<div class="comment-user-picture"><?php if ($picture) print $picture; ?>
</div>

<div class="comment-meta clearfix">
<div class="submitted"><?php print $submitted; ?></div>
</div>

<?php if ($title): ?>
<h2 class="comment-title"><?php print $title; ?></h2>
<?php endif; ?>

<div class="content"><?php print $content; ?></div>

</div>
</div>
