<?php
// $Id: views-view-swftools.tpl.php,v 1.1.2.4 2010/04/14 23:29:54 stuartgreenfield Exp $

/**
 * We do this iteration in here because we want the user to be able to modify this
 * template easily. The code below builds a playlist ready to go SWF Tools. We
 * don't do it in template_preprocess_views_view_swftools() because if the you are
 * supplying arbitrary data to pass on to a playlist then we don't want to have to
 * iterate again. Note that the code below includes a call to a function that will
 * automatically take care of assigning the fileurl, the image thumbnail and a 
 * title if these are set on the options form.
 * 
 * You can then add additional data to the playlist array as you wish, picking up
 * other fields that have been fetched out of views. For example, you can fetch
 * the node body and attach it on an element called 'description' and then that
 * can be used by TiltViewer to populate the reverse of the images.
 */

// Get the fields we are using
$keys = array_keys($view->field);

// Initialise a playlist ready for SWF Tools
$files = array();

//  Iterate over each row of the results - this is a clever bit of processing to match files with their thumbnails
foreach ($rows as $key => $row) {

  // Reset the work array
  $work = array();
    
  // Render each field in this row using the assigned handler
  foreach ($keys as $id) {
    $work[$id] = $view->field[$id]->theme($row);
  }

  // We need to use delta and delta_1 to manage the case of multiple CCK content, but we set a dummy value in
  // case the user didn't add the fields
  $work += array(
    'delta' => '',
    'delta_1' => '',
  );
  
  /**
   * We need to work out if we should output this or not, and eliminate duplicates when handling content
   * types that have multiple files with multiple thumbnails in the same node.
   * 
   * There are three conditions that result in output:
   * 1) If the delta variables are not set then we always output (since they are both empty strings and satisfy condition 3)
   * 2) If the image path is empty then we always output because there is no thumbnail
   * 3) If the delta on the file is the same as the delta on the thumbnail then output
   */
//  if (!(isset($work['delta']) && isset($work['delta_1'])) || empty($work[$options['image']]) || ($work['delta'] == $work['delta_1'])) {
  if (empty($work[$options['image']]) || ($work['delta'] == $work['delta_1'])) {
    
    // This function will add the basic playlist elements of filepath, image and title directly to $files
    swftools_views_add_playlist_element($files, $key, $options, $work);
    
    /**
     * If you want to add arbitrary data to the playlist then you can do so here
     * Add your additional elements to $files[$key]['myKey'] = myValue
     * Rendered fields are available in $work[$id] where $id is the field name.
     * 
     * For example, to attach the node body to an element called 'description'
     * ready for TiltViewer to use you would write:
     * 
     * $files[$key]['description'] = $work['body'];
     * 
     */
    
  }
  
}

// Call swf to output the result
print swf($files, $swftools['options']);

?>
