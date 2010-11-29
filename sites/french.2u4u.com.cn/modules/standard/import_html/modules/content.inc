<?php
// $Id: content.inc,v 1.3.4.5 2009/09/09 06:47:22 dman Exp $
/**
 * @file helper to import fields provided by CCK (Content Creation Kit)
 */

/**
 * Try and import any CCK fields into the node in the format expected
 * 
 * Implementation of HOOK_import_html()
 * 
 * @TODO this is probably broken in the upgrade. Revisit.
 * Need to re-aquire the DOM element, nnot just the text string maybe. Maybe
 * should ignore the previous text scan import altogether.
 */
function content_import_html($profile, &$node, $datadoc = NULL) {
  if (function_exists('content_types') && ($content_def = content_types($node->type)) && ! empty($content_def['fields'])) {
    // This content type has fields we may want
    import_html_debug("Scanning import document for CCK fields to import into this $node->type");
  }
  else {
    import_html_debug("Content type {$node->type} has no CCK fields to scan for");
    return; // no valid CCK stuff for me to work on
  }
  
  // Look for ids or classes in the doc matching an expected CCK field name
  foreach ($content_def['fields'] as $field_id => $field_def) {
    
    // allow both fieldname_field and just fieldname.
    $field_short_id = substr($field_id, 6); 

    // We will put them all into an array like CCK expects
    $node->{$field_def['field_name']} = array();

    // A tag may have found itself set on the node object directly -
    // - a dc: meta tag that Drupal doesn't handle natively for example
    // may get picked up in the metas, and therefore the node.
    // If we have a content type with field_dc_location
    // and <meta name="DC:Location" content="Here" />
    // then we get $node->'dc_location'='Here'
    // The following code captures that
    
    // Loop through possible values on the node
    foreach (array($field_id, $field_short_id) as $alt_field_id) {
      if (! empty($node->$alt_field_id)) {
        import_html_debug("Found a value for '%alt_field_id' to save as a CCK field value", array('%alt_field_id' => $alt_field_id), 2);
        // The found value may or may not be an array. Ensure it is, then loop over the list.
        $field_val = is_array($node->$alt_field_id)? $node->$alt_field_id : array($node->$alt_field_id);
        foreach ($field_val as $val) {
          // Create a CCK value entry for this value
          $node->{$field_def['field_name']}[] = array(
            'value' => $val,
            'format' => import_html_get_preferred_filter(), 
          );
        }
      }
    }

    // That's imported the easy ones (meta strings named after field names), 
    // Now do the proper DOM.

    // ...
    // Actually, you knwo what? don't bother.
    // The bits I expect to find were already in the node object as 
    // named attributes. The code aboce should have done them OK.
    // ... I'll look at the DOM method again when I find extra need for it, but for now 
    
    if ($field_def['type'] == 'text') {
      continue;
    }
    
    // TODO support for other CCK field type - other than text!
  }
}

