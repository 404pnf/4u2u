<?php
// $Id: uc_product.views.inc,v 1.1.2.7 2009/10/20 20:58:06 islandusurper Exp $

/**
 * @file
 * Views 2 hooks and callback registries.
 */

/**
 * Implementation of hook_views_data().
 */
function uc_ismoney_views_data() {
  $data['uc_ismoney']['table']['group'] = t('Product');

  $data['uc_ismoney']['table']['join'] = array(
    'node' => array(
      'left_field' => 'vid',
      'field' => 'vid',
    ),
    'node_revisions' => array(
      'left_field' => 'vid',
      'field' => 'vid',
    ),
  );

  $data['uc_ismoney']['moneyable'] = array(
    'title' => t('现金商品'),
    'help' => t('商品是否需使用现金购买.'),
    'field' => array(
      'handler' => 'views_handler_field_node',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    
  );

  return $data;
}

