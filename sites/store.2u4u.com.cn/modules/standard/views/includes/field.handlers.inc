<?php
// $Id: field.handlers.inc,v 1.13 2008/06/18 15:25:46 merlinofchaos Exp $
/**
 * @file
 * Views' field handlers.
 */
/**
 * @defgroup views_field_handlers Views' field handlers
 * @{
 * Handlers to tell Views how to build and display fields.
 *
 */

/**
 * Base field handler that has no options and renders an unformatted field.
 *
 * Definition terms:
 * - additional fields: An array of fields that should be added to the query
 *                      for some purpose. The array is in the form of:
 *                      array('identifier' => array('table' => tablename,
 *                      'field' => fieldname); as many fields as are necessary
 *                      may be in this array.
 * - click sortable: If TRUE, this field may be click sorted.
 */
class views_handler_field extends views_handler {
  var $field_alias = 'unknown';

  /**
   * Construct a new field handler.
   */
  function construct() {
    parent::construct();

    $this->additional_fields = array();
    if (!empty($this->definition['additional fields'])) {
      $this->additional_fields = $this->definition['additional fields'];
    }

    if (!isset($this->options['exclude'])) {
      $this->options['exclude'] = '';
    }
  }

  function init(&$view, $options) {
    parent::init($view, $options);

    $this->options += array(
      'exclude' => FALSE,
    );
  }

  /**
   * Called to add the field to a query.
   */
  function query() {
    $this->ensure_my_table();
    // Add the field.
    $this->field_alias = $this->query->add_field($this->table_alias, $this->real_field);

    $this->add_additional_fields();
  }

  /**
   * Add 'additional' fields to the query.
   *
   * @param $fields
   * An array of fields. The key is an identifier used to later find the
   * field alias used. The value is either a string in which case it's
   * assumed to be a field on this handler's table; or it's an array in the
   * form of
   * @code array('table' => $tablename, 'field' => $fieldname) @endcode
   */
  function add_additional_fields($fields = NULL) {
    if (!isset($fields)) {
      // notice check
      if (empty($this->additional_fields)) {
        return;
      }
      $fields = $this->additional_fields;
    }
    if (!empty($fields) && is_array($fields)) {
      foreach ($fields as $identifier => $info) {
        if (is_array($info)) {
          if (isset($info['table'])) {
            $table_alias = $this->query->ensure_table($info['table'], $this->relationship);
          }
          else {
            $table_alias = $this->table_alias;
          }
          $this->aliases[$identifier] = $this->query->add_field($table_alias, $info['field']);
        }
        else {
          $this->aliases[$info] = $this->query->add_field($this->table_alias, $info);
        }
      }
    }
  }

  /**
   * Called to determine what to tell the clicksorter.
   */
  function click_sort($order) {
    $this->query->add_orderby($this->table, $this->field, $order, $this->field_alias);
  }

  /**
   * Determine if this field is click sortable.
   */
  function click_sortable() {
    return !empty($this->definition['click sortable']);
  }

  /**
   * Get this field's label.
   */
  function label() {
    if (!isset($this->options['label'])) {
      return '';
    }
    return $this->options['label'];
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['label'] = array('default' => $this->definition['title'], 'translatable' => TRUE);

    return $options;
  }

  /**
   * Default options form that provides the label widget that all fields
   * should have.
   */
  function options_form(&$form, &$form_state) {
    $form['label'] = array(
      '#type' => 'textfield',
      '#title' => t('Label'),
      '#default_value' => isset($this->options['label']) ? $this->options['label'] : '',
      '#description' => t('The label for this field that will be displayed to end users if the style requires it.'),
    );
    $form['exclude'] = array(
      '#type' => 'checkbox',
      '#title' => t('Exclude from display'),
      '#default_value' => $this->options['exclude'],
      '#description' => t('Check this box to not display this field, but still load it in the view.  Use this option to not show a grouping field in each record, or when doing advanced theming.'),
    );
  }

  /**
   * Provide extra data to the administration form
   */
  function admin_summary() {
    return $this->label();
  }

  /**
   * Run before any fields are rendered.
   *
   * This gives the handlers some time to set up before any handler has
   * been rendered.
   *
   * @param $values
   *   An array of all objects returned from the query.
   */
  function pre_render($values) { }

  /**
   * Render the field.
   *
   * @param $values
   *   The values retrieved from the database.
   */
  function render($values) {
    $value = $values->{$this->field_alias};
    return check_plain($value);
  }

  /**
   * Call out to the theme() function, which probably just calls render() but
   * allows sites to override output fairly easily.
   */
  function theme($values) {
    return theme($this->theme_functions(), $this->view, $this, $values);
  }

  function theme_functions() {
    $themes = array();
    $hook = 'views_view_field';

    $display = $this->view->display[$this->view->current_display];

    if (!empty($display)) {
      $themes[] = $hook . '__' . $this->view->name  . '__' . $display->id . '__' . $this->options['id'];
      $themes[] = $hook . '__' . $this->view->name  . '__' . $display->id;
      $themes[] = $hook . '__' . $display->id . '__' . $this->options['id'];
      $themes[] = $hook . '__' . $display->id;
      if ($display->id != $display->display_plugin) {
        $themes[] = $hook . '__' . $this->view->name  . '__' . $display->display_plugin . '__' . $this->options['id'];
        $themes[] = $hook . '__' . $this->view->name  . '__' . $display->display_plugin;
        $themes[] = $hook . '__' . $display->display_plugin . '__' . $this->options['id'];
        $themes[] = $hook . '__' . $display->display_plugin;
      }
    }
    $themes[] = $hook . '__' . $this->view->name . '__' . $this->options['id'];
    $themes[] = $hook;

    return $themes;
  }
}

/**
 * A special handler to take the place of missing or broken handlers.
 */
class views_handler_field_broken extends views_handler_field {
  function ui_name() {
    return t('Broken/missing handler');
  }

  function ensure_my_table() { /* No table to ensure! */ }
  function query() { /* No query to run */ }
  function options_form(&$form, &$form_state) {
    $form['markup'] = array(
      '#prefix' => '<div class="form-item description">',
      '#value' => t('The handler for this item is broken or missing and cannot be used. If a module provided the handler and was disabled, re-enabling the module may restore it. Otherwise, you should probably delete this item.'),
    );
  }

  /**
   * Determine if the handler is considered 'broken'
   */
  function broken() { return TRUE; }
}


/**
 * A handler to provide proper displays for dates.
 */
class views_handler_field_date extends views_handler_field {
  function option_definition() {
    $options = parent::option_definition();

    $options['date_format'] = array('default' => 'small');
    $options['custom_date_format'] = array('default' => '');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $time = time();

    $form['date_format'] = array(
      '#type' => 'select',
      '#title' => t('Date format'),
      '#options' => array(
        'small' => format_date($time, 'small'),
        'medium' => format_date($time, 'medium'),
        'large' => format_date($time, 'large'),
        'custom' => t('Custom'),
        'time ago' => t('Time ago'),
      ),
      '#default_value' => isset($this->options['date_format']) ? $this->options['date_format'] : 'small',
    );
    $form['custom_date_format'] = array(
      '#type' => 'textfield',
      '#title' => t('Custom date format'),
      '#description' => t('If "Custom", see <a href="http://us.php.net/manual/en/function.date.php">the PHP docs</a> for date formats. If "Time ago" this is the the number of different units to display, which defaults to two.'),
      '#default_value' => isset($this->options['custom_date_format']) ? $this->options['custom_date_format'] : '',
      '#process' => array('views_process_dependency'),
      '#dependency' => array('edit-options-date-format' => array('custom', 'time ago')),
    );
  }

  function render($values) {
    $value = $values->{$this->field_alias};
    $format = $this->options['date_format'];
    if ($format == 'custom' || $format == 'time ago') {
      $custom_format = $this->options['custom_date_format'];
    }

    switch ($format) {
      case 'time ago':
        return $value ? t('%time ago', array('%time' => format_interval(time() - $value, is_numeric($custom_format) ? $custom_format : 2))) : theme('views_nodate');
      case 'custom':
        return $value ? format_date($value, $format, $custom_format) : theme('views_nodate');
      default:
        return $value ? format_date($value, $format) : theme('views_nodate');
    }
  }
}

/**
 * A handler to provide proper displays for dates.
 *
 * Allows for display of true/false, yes/no, on/off.
 */
class views_handler_field_boolean extends views_handler_field {
  function option_definition() {
    $options = parent::option_definition();

    $options['type'] = array('default' => 'yes-no');
    $options['not'] = array('definition bool' => 'reverse');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['type'] = array(
      '#type' => 'select',
      '#title' => t('Output format'),
      '#options' => array(
        'yes-no' => t('Yes/No'),
        'true-false' => t('True/False'),
        'on-off' => t('On/Off'),
      ),
      '#default_value' => $this->options['type'],
    );
    $form['not'] = array(
      '#type' => 'checkbox',
      '#title' => t('Reverse'),
      '#description' => t('If checked, true will be displayed as false.'),
      '#default_value' => $this->options['not'],
    );
  }

  function render($values) {
    $value = $values->{$this->field_alias};
    if (!empty($this->options['not'])) {
      $value = !$value;
    }

    switch ($this->options['type']) {
      case 'yes-no':
      default:
        return $value ? t('Yes') : t('No');
      case 'true-false':
        return $value ? t('True') : t('False');
      case 'on-off':
        return $value ? t('On') : t('Off');
    }
  }
}

/**
 * A handler to run a field through check_markup, using a companion
 * format field.
 *
 * - format: (REQUIRED) The field in this table used to control the format
 *           such as the 'format' field in the node, which goes with the
 *           'body' field.
 */
class views_handler_field_markup extends views_handler_field {
  /**
   * Constructor; calls to base object constructor.
   */
  function construct() {
    parent::construct();

    $this->format = $this->definition['format'];

    $this->additional_fields = array();
    if (!is_numeric($this->format)) {
      $this->additional_fields['format'] = $this->format;
    }
  }

  function render($values) {
    $value = $values->{$this->field_alias};
    $format = is_numeric($this->format) ? $this->format : $values->{$this->aliases['format']};
    return check_markup($value, $format, FALSE);
  }
}

/**
 * A handler to run a field through simple XSS filtering
 */
class views_handler_field_xss extends views_handler_field {
  function render($values) {
    $value = $values->{$this->field_alias};
    return filter_xss($value);
  }
}

/**
 * Field handler to provide simple renderer that turns a URL into a clickable link.
 */
class views_handler_field_url extends views_handler_field {
  function option_definition() {
    $options = parent::option_definition();

    $options['display_as_link'] = array('default' => TRUE);

    return $options;
  }

  /**
   * Provide link to the page being visited.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['display_as_link'] = array(
      '#title' => t('Display as link'),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['display_as_link']),
    );
  }

  function render($values) {
    $value = $values->{$this->field_alias};
    if (!empty($this->options['display_as_link'])) {
      return l(check_plain($value), $value, array('html' => TRUE));
    }
    else {
      return $value;
    }
  }
}

/**
 * Field handler to provide a list of items.
 *
 * The items are expected to be loaded by a child object during pre_render,
 * and 'my field' is expected to be the pointer to the items in the list.
 *
 * Items to render should be in a list in $this->items
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_prerender_list extends views_handler_field {
  function option_definition() {
    $options = parent::option_definition();

    $options['type'] = array('default' => 'separator');
    $options['separator'] = array('default' => ', ');
    $options['empty'] = array('default' => '', 'translatable' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['type'] = array(
      '#type' => 'radios',
      '#title' => t('Display type'),
      '#options' => array(
        'ul' => t('Unordered list'),
        'ol' => t('Ordered list'),
        'separator' => t('Simple separator'),
      ),
      '#default_value' => $this->options['type'],
    );

    $form['separator'] = array(
      '#type' => 'textfield',
      '#title' => t('Separator'),
      '#default_value' => $this->options['separator'],
      '#process' => array('views_process_dependency'),
      '#dependency' => array('radio:options[type]' => array('separator')),
    );

    $form['empty'] = array(
      '#type' => 'textfield',
      '#title' => t('Empty list text'),
      '#default_value' => $this->options['empty'],
      '#description' => t('If the list is empty, you may enter text here that will be displayed.'),
    );
  }

  function render($values) {
    $field = $values->{$this->field_alias};
    if (!empty($this->items[$field])) {
      if ($this->options['type'] == 'separator') {
        return implode(check_plain($this->options['separator']), $this->items[$field]);
      }
      else {
        return theme('item_list', $this->items[$field], NULL, $this->options['type']);
      }
    }
    else if (!empty($this->options['empty'])) {
      return $this->options['empty'];
    }
  }
}

/**
 * Render a numeric value as a size.
 */
class views_handler_field_file_size extends views_handler_field {
  function render($values) {
    return format_size($values->{$this->field_alias});
  }
}

/**
 * Render a field as a numeric value
 *
 * Definition terms:
 * - float: If true this field contains a decimal value. If unset this field
 *          will be assumed to be integer.
 * -
 */
class views_handler_field_numeric extends views_handler_field {
  function option_definition() {
    $options = parent::option_definition();

    $options['set_precision'] = array('default' => FALSE);
    $options['precision'] = array('default' => 0);
    $options['decimal'] = array('default' => '.', 'translatable' => TRUE);
    $options['separator'] = array('default' => ',', 'translatable' => TRUE);
    $options['prefix'] = array('default' => '', 'translatable' => TRUE);
    $options['suffix'] = array('default' => '', 'translatable' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    if (!empty($this->definition['float'])) {
      $form['set_precision'] = array(
        '#type' => 'checkbox',
        '#title' => t('Round'),
        '#description' => t('If checked, the number will be rounded.'),
        '#default_value' => $this->options['set_precision'],
      );
      $form['precision'] = array(
        '#type' => 'textfield',
        '#title' => t('Precision'),
        '#default_value' => $this->options['precision'],
        '#description' => t('Specify how many digits to print after the decimal point.'),
        '#process' => array('views_process_dependency'),
        '#dependency' => array('edit-options-set-precision' => array(TRUE)),
        '#size' => 2,
      );
      $form['decimal'] = array(
        '#type' => 'textfield',
        '#title' => t('Decimal point'),
        '#default_value' => $this->options['decimal'],
        '#description' => t('What single character to use as a decimal point.'),
        '#size' => 2,
      );
    }
    $form['separator'] = array(
      '#type' => 'textfield',
      '#title' => t('Thousands separator'),
      '#default_value' => $this->options['separator'],
      '#description' => t('What single character to use as the thousands separator.'),
      '#size' => 2,
    );
    $form['prefix'] = array(
      '#type' => 'textfield',
      '#title' => t('Prefix'),
      '#default_value' => $this->options['prefix'],
      '#description' => t('Text to put before the number, such as currency symbol.'),
    );
    $form['suffix'] = array(
      '#type' => 'textfield',
      '#title' => t('Suffix'),
      '#default_value' => $this->options['suffix'],
      '#description' => t('Text to put after the number, such as currency symbol.'),
    );
  }

  function render($values) {
    $value = $values->{$this->field_alias};
    if (!empty($this->options['set_precision'])) {
      $value = number_format($value, $this->options['precision'], $this->options['decimal'], $this->options['separator']);
    }
    else {
      $remainder = abs($value) - intval(abs($value));
      $value = number_format($value, 0, '', $this->options['separator']);
      if ($remainder) {
        $value .= $this->options['decimal'] . $remainder;
      }
    }
    return check_plain($this->options['prefix'] . $value . $this->options['suffix']);
  }
}

/**
 * @}
 */

