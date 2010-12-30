<?php
// $Id: import_html_modules.inc,v 1.11.4.3 2009/10/06 14:09:02 dman Exp $
/**
 * @file
 * Additional per-module functionality used by import_html.
 *
 * Each available module MAY impliment a hook_import_html() function to add or manipulate
 * its own data as the node gets saved.
 *
 * @ingroup import_html Import HTML
 * @author Dan Morrison http://coders.co.nz/
 */

/**
 * hook_import_html - prototype function hook
 *
 * invoke this when creating a node out of nothing
 *
 * @param $profile array of settings for the import_html process
 * @param $node node object with lots of extra data added to it, only some of which we want to save.
 * @param $datadoc XML doc of the 'simple' node source that we may investigate for extra info if the cooked node object is not good enough
 */
function hook_import_html($profile, &$node, $datadoc = NULL) {

}
/**
 * hook_import_html_after_save - prototype function hook
 *
 * Some functions (alias) can only operate when the nid is already known.
 * Invoke this when the node has been created
 *
 * @param $profile array of settings for the import_html process
 * @param $node node object with lots of extra data added to it, only some of which we want to save.
 * @param $datadoc XML doc of the 'simple' node source that we may investigate for extra info if the cooked node object is not good enough
 */
function hook_import_html_after_save($profile, &$node, $datadoc = NULL) {

}


