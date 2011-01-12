<?php foreach ($fields as $id => $field): ?>

  <<?php print $field->inline_html;?> class="<?php print $field->class; ?>">
    <?php if ($field->label): ?>
      <label class="<?php print $field->class; ?>">
        <?php print $field->label; ?>:
      </label>
    <?php endif; ?>


   <?php print $field->content; ?>

  </<?php print $field->inline_html;?>>
<?php endforeach; ?>
