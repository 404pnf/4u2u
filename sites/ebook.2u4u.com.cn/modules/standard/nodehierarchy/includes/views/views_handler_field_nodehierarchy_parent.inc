<?php
// $Id: views_handler_field_nodehierarchy_parent.inc,v 1.1.2.1 2008/09/29 02:19:05 ronan Exp $

/**
 * Field handler to allow linking to a comment
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_nodehierarchy_parent extends views_handler_field {
  /**
   * Override init function to provide generic option to link to comment.
   */
  function init(&$view, &$data) {
    parent::init($view, $data);
    if (isset($data['link_to_parent']) && $view->base_table != 'node') {
      // @todo: This can't be right, it'll totally fail with relationships.
      $this->additional_fields[] = 'nid';
      $this->nid_field = 'node_nid';
    }
    else {
      $this->nid_field = 'parent';
    }
  }

  function options(&$options) {
    parent::options($options);
    $options['link_to_parent'] = TRUE;
    $options['display_as'] = 'title';
  }

  /**
   * Provide link-to-comment option.
   */
  function options_form(&$form, &$form_state) {
    $form['display_as'] = array(
      '#title' => t('Display this field as'),
      '#type' => 'select',
      '#options' => array('title' => t('Node Parent Title'), 'nid' => t('Node Parent ID')),
      '#default_value' => $this->options['display_as'],
    );
    $form['link_to_parent'] = array(
      '#title' => t('Link this field to the parent node'),
      '#type' => 'checkbox',
      '#default_value' => $this->options['link_to_parent'],
    );
  }

  function render_parent($data, $values) {
    $out = "";
    if (@$this->options['display_as'] === 'nid') {
      $out = $data;
    }
    else {
      $parent = node_load($data);
      $out = $parent->title;
    }
    if (!empty($this->options['link_to_parent'])) {
      return l($out, "node/". $data );
    }
    else {
      return $out;
    }
  }

  function render($values) {
    return $this->render_parent(check_plain($values->{$this->field_alias}), $values);
  }
}