<?php
// $Id: emimage.inc,v 1.1.2.1 2009/10/09 15:43:35 robrechtj Exp $

/**
 * @file
 * Support file for the CCK Embedded Image module.
 */

/**
 * Implementation of hook_node_import_fields().
 */
function emimage_node_import_fields($type) {
  $fields = array();

  foreach (node_import_cck_fields($type, 'emimage') as $fieldname => $fieldinfo) {
    foreach ($fieldinfo['columns'] as $colname => $colinfo) {
      $cck_fieldname = node_import_cck_name($fieldname, $colname);

      $fields[$cck_fieldname] = node_import_cck_field_defaults($fieldinfo);
      switch ($colname) {
        case 'embed':
          $fields[$cck_fieldname]['title'] = $fieldinfo['widget']['label'];
          break;

        default:
          // as in the node editing form, we only set the embed field, and the
          // rest happens automatically
          unset($fields[$cck_fieldname]);
          break;
      }
    }
  }

  return $fields;
}