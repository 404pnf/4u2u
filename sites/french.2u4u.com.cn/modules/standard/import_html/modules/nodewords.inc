<?php
// $Id: nodewords.inc,v 1.1.4.1 2009/03/14 13:41:17 dman Exp $
/**
 * @file helper to import fields provided by nodewords module (meta tags)
 */

/** 
 * Adds nodewords support.
 * cast keywords into the format that nodewords expects
 * 
 * Implementation  of HOOK_import_html()
 */
function nodewords_import_html($profile, &$node, $datadoc = NULL) {
  if ($node->keywords && ! $node->nodewords['keywords']) {
    $node->nodewords['keywords'] = $node->keywords;
  }
}