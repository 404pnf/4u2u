<?php
// $Id: views-view-fields.tpl.php,v 1.6 2008/09/24 22:48:21 merlinofchaos Exp $
/**
 * @file views-view-fields.tpl.php
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - c: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->separator: an optional separator that may appear before a field.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
?>
    
   <div class="smart_left">
                   <div class="smart_first">  <div class="smart_date"><?php print $fields['field_date_value']->content;?></div>
                                              <div class="smart_blog_title"><?php print $fields['title']->content; ?></div>
                   </div>
       <div class="smart_secend"><div class="smart_blog_image"><?php print $fields['field_image_fid']->content;?></div>
                                 <div class="smart_content"><div class="smart_blog_teaser"><?php print $fields['teaser']->content;?></div>
                                                            <div class="anniu"><div class="anniuback">按钮</div></div>  
                                                            <div class="smart_audio_button"><div class="smart_blog_audio"><?php print $fields['field_audio_fid']->content;?></div>                     
                                                                                            <div class="smart_blog_subtitle"><?php print $fields['field_subtitles_value']->content;?></div>
                                                            </div>                        
                                 </div>
       </div>                           
   </div>
   <div class="smart_right"> <?php  print $fields['field_word_value']->content;?></div>
