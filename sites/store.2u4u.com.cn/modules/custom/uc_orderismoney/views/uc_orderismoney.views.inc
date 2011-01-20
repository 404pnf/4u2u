<?php
// $Id: uc_product.views.inc,v 1.1.2.7 2009/10/20 20:58:06 islandusurper Exp $

/**
 * @file
 * Views 2 hooks and callback registries.
 */

/**
 * Implementation of hook_views_data().
 */
function uc_orderismoney_views_data() {
  $data['uc_orderismoney']['table']['group'] = t('Order ismoney');

  $data['uc_orderismoney']['table']['join']['uc_orders']  = array(
		'left_field' => 'order_id',
		'field' => 'order_id',
  );

  $data['uc_orderismoney']['moneyable'] = array(
    'title' => t('现金定单'),
    'help' => t('定单是否需使用现金购买.'),
    'field' => array(
      'handler' => 'uc_views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    
  );

  return $data;
}

