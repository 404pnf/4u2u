<?php

/**
 * Style plugin to render each item in an ordered or unordered list.
 *
 * @ingroup views_style_plugins
 */
class views_plugin_style_swftools extends views_plugin_style {
  
  /**
   * Set default options
   */
  function option_definition() {
    $options = parent::option_definition();

    // Set all option defaults to SWFTOOLS_UNDEFINED
    $options['profile'] = array('default' => SWFTOOLS_UNDEFINED);
    $options['filepath'] = array('default' => SWFTOOLS_UNDEFINED);
    $options['image'] = array('default' => SWFTOOLS_UNDEFINED);
    $options['title'] = array('default' => SWFTOOLS_UNDEFINED);
    $options['description'] = array('default' => SWFTOOLS_UNDEFINED);
    $options['author'] = array('default' => SWFTOOLS_UNDEFINED);
    $options['date'] = array('default' => SWFTOOLS_UNDEFINED);
    $options['link'] = array('default' => SWFTOOLS_UNDEFINED);
    $options['duration'] = array('default' => SWFTOOLS_UNDEFINED);
    
    return $options;
  }

  /**
   * Render the given style.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Get handlers
    $handlers = $this->view->display_handler->get_handlers('field');
    
    // If there are no handlers then show a message
    if (empty($handlers)) {

      $form['error_markup'] = array(
        '#value' => t('You need at least one field before you can configure your field settings'),
        '#prefix' => '<div class="error form-item description">',
        '#suffix' => '</div>',
      );
    
    }
    else {
    
      $form['intro_markup'] = array(
        '#prefix' => '<div class="description">',
        '#value' => t('You can select the profile that will be used to handle this playlist, and map fields from the query in to the relevant part of the playlist. Note that not all players support all playlist elements. The playlists can be extended even further by modifying or over-riding the %swftools template.', array('%swftools' => 'views-view-swftools.tpl.php')),
        '#suffix' => '</div>',
      );
      
      // Initialise profile options with SWF Tools default
      $options = array(
        SWFTOOLS_UNDEFINED => t('SWF Tools default'),
      );
      
      // Populate with profiles if swftools_profiles is available
      if (function_exists('swftools_profiles_get_profiles')) {
        $profiles = swftools_profiles_get_profiles();
        foreach ($profiles as $key => $info) {
          $options[$key] = $info['name'];
        }
      }
      
      // Add a select list to choose the profile
      $form['profile'] = array(
        '#type' => 'select',
        '#title' => t('Playlist handler'),
        '#description' => t('Select the profile that you want to use to display this playlist. If no profiles have been created then the default SWF Tools file handling setting will be used.'),
        '#options' => $options,
        '#default_value' => $this->options['profile'],
      );
    
      // Initialise an array of fields for the select lists
      $fields = array(
        SWFTOOLS_UNDEFINED => t('None'),
      );
      
      // Add the available fields to the select list, formatted with their short name
      foreach ($this->view->display_handler->get_handlers('field') as $field => $handler) {
        $fields[$field] = $handler->ui_name(TRUE);
      }
           
      $form['start_left'] = array(
        '#value' => '<div class="views-left-50">',
      );
      
      // Files
      $form['filepath'] = array(
        '#type' => 'select',
        '#title' => t('File'),
        '#description' => t('Select the field that will be used to construct the playlist - these are the files that will actually play.'),
        '#options' => $fields,
        '#default_value' => $this->options['filepath'],
      );
      
      // Thumbnails
      $form['image'] = array(
        '#type' => 'select',
        '#title' => t('Thumbnail'),
        '#description' => t('Select the field that will be used to supply thumbnails for each file in the playlist.'),
        '#options' => $fields,
        '#default_value' => $this->options['image'],
      );
      
      // Titles
      $form['title'] = array(
        '#type' => 'select',
        '#title' => t('Title'),
        '#description' => t('Select the field that should be rendered as the title for each file.'),
        '#options' => $fields,
        '#default_value' => $this->options['title'],
      );
      
      // Descriptions
      $form['description'] = array(
        '#type' => 'select',
        '#title' => t('Description'),
        '#description' => t('Select the field that should be rendered as the description for each file.'),
        '#options' => $fields,
        '#default_value' => $this->options['description'],
      );
      
      $form['end_left'] = array(
        '#value' => '</div>',
      );

      $form['start_right'] = array(
        '#value' => '<div class="views-left-40 clear-block">',
      );
      
      // Authors
      $form['author'] = array(
        '#type' => 'select',
        '#title' => t('Author'),
        '#description' => t('Select the field that should be rendered as the author for each file.'),
        '#options' => $fields,
        '#default_value' => $this->options['author'],
      );
      
      // Dates
      $form['date'] = array(
        '#type' => 'select',
        '#title' => t('Date'),
        '#description' => t('Select the field that should be rendered as the date for each file.'),
        '#options' => $fields,
        '#default_value' => $this->options['date'],
      );
      
      // Link
      $form['link'] = array(
        '#type' => 'select',
        '#title' => t('Link'),
        '#description' => t('Select the field that should be rendered as the link for each file.'),
        '#options' => $fields,
        '#default_value' => $this->options['link'],
      );
      
      // Duration
      $form['duration'] = array(
        '#type' => 'select',
        '#title' => t('Duration'),
        '#description' => t('Select the field that should be rendered as the duration for each file.'),
        '#options' => $fields,
        '#default_value' => $this->options['date'],
      );

      $form['end_right'] = array(
        '#value' => '</div>',
      );
    
    }
  }
  
}
