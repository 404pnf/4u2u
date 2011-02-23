<?php
// $Id: swftools_profiles.admin.inc,v 1.5.2.8 2010/04/07 21:33:36 stuartgreenfield Exp $

/**
 * Presents an overview of defined profiles.
 */
function swftools_profiles_overview() {
  
  // Begin a table  
  $header = array(t('Name'), t('Profile Name'), t('Description'), array('data' => t('Operations'), 'colspan' => '4'));
  $rows = array();

  // Retrieve available profiles from a fresh cache
  foreach(swftools_profiles_get_profiles(TRUE) as $profile) {

    // Begin a row
    $row = array();
    
    // Make sure profile name uses - and not _
    $profile_url_str = str_replace('_', '-', $profile['profile']);
    
    // Build a row
    $row[] = check_plain($profile['name']);
    $row[] = check_plain($profile['profile']);
    $row[] = array('data' => filter_xss_admin($profile['description']), 'class' => 'description');
  
    // Build action links
    $links = array();
    $row[] = l(t('Edit'), 'admin/settings/swftools/profile/' . $profile_url_str);
    $row[] = l(t('Configure'), 'admin/settings/swftools/profile/' . $profile_url_str . '/configure');
    $row[] = l(t('Clone'), 'admin/settings/swftools/profile/'. $profile_url_str . '/clone');
    $row[] = l(t('Delete'), 'admin/settings/swftools/profile/'. $profile_url_str . '/delete');
    
    // Add the row to the table
    $rows[] = $row;
    
  }

  // If no profiles were found give a meaningful message
  if (!$rows) {
    $rows[] = array(
      'data' => array(array('data' => t('No profiles have been created yet.'), 'colspan' => '4', 'class' => 'message')),
    );
  }
  
  // Theme the output
  $output = theme('table', $header, $rows);

  // Append the "Add a new profile" message
  return $output . theme_swftools_profiles_overview_links();
  
}


// TODO: This needs to be registered as a theme
function theme_swftools_profiles_overview_links() {
  return '<div class="swftools-profiles-overview-links">'. l(t('» Add a new profile'), 'admin/settings/swftools/profiles/add') .'</div>';
}


function swftools_profiles_profile_form($form_state, $profile = array(), $clone = FALSE) {

  // See if we are cloning a profile
  if ($clone) {
    $profile['clone'] = $profile['profile'];
    $profile['name'] = $profile['name'] . '_1';
    $profile['profile'] = $profile['profile'] . '_1';
  }
  
  // Initialise array to hold the form
  $form = array();

  // If an empty array was passed establish keys to suppress notice errors
  $profile += array(
    'name' => '',
    'profile' => '',
    'description' => '',
    'multiple' => 0x0002,
    'download_link' => 0,
    'clone' => '',
  );
  
  $form['name'] = array(
    '#title' => t('Display name'),  
    '#type' => 'textfield',
    '#default_value' => $profile['name'],
    '#description' => t('The human-readable name of this profile. This text will be displayed on the profiles listing page and in the CCK formatter list boxes. It is recommended that this name begin with a capital letter and contain only letters, numbers, and <strong>spaces</strong>. This name must be unique.'),
    '#required' => TRUE,
  );
  
  $form['old_name'] = array(
    '#type' => 'value',
    '#value' => $profile['name'],
  );
  
  $form['profile'] = array(
    '#title' => t('Profile name'),
    '#type' => 'textfield',
    '#default_value' => $profile['profile'],
    '#maxlength' => 32,
    '#required' => TRUE,
    '#description' => t('The machine-readable name of this profile. This name will be used by SWF Tools as the input filter <em>profile</em> property. This name must contain only lowercase letters, numbers, and underscores. This name must be unique.'),
  );
  
  $form['old_profile'] = array(
    '#type' => 'value',
    '#value' => $profile['profile'],
  );
  
  $form['description'] = array(
    '#title' => t('Description'),
    '#type' => 'textarea',
    '#default_value' => $profile['description'],
    '#description' => t('A brief description of this profile. This text will be displayed on the profiles listing page.'),
  );
  
  $form['clone'] = array(
    '#type' => 'value',
    '#value' => $profile['clone'],
  );
  
  if (module_exists('content')) {

    $form['multiple'] = array(
      '#type' => 'radios',
      '#title' => t('CCK output'),
      '#default_value' => $profile['multiple'],
      '#options' => array(
        CONTENT_HANDLE_MODULE => t('Playlist'),
        CONTENT_HANDLE_CORE => t('Separate players'),
      ),
      '#description' => t('Specifies whether content that has multiple elements will be rendered as a series of separate players, or assembled in to a playlist.'),
    );
    
    $form['download_link'] = array(
      '#type' => 'radios',
      '#title' => t('Download link'),
      '#default_value' => $profile['download_link'],
      '#options' => array(
        0 => t('Disabled'),
        1 => t('Enabled'),
      ),
      '#description' => t('If this profile is assigned to a CCK FileField or Linkfield then a link to the file can be included to allow users to download it. This setting is only effective when rendering content in to separate players.'),
    );
    
  }
  else {
    $form['multiple'] = array(
      '#type' => 'value',
      '#value' => $profile['multiple'],
    );
    $form['download_link'] = array(
      '#type' => 'value',
      '#value' => $profile['download_link'],    
    );  
  }
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save profile'),
    '#weight' => 9,
  );
  
  if ($profile['profile']) {
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete profile'),
      '#weight' => 45,
    );
  }

  // Return the form
  return $form;

}


/**
 * Returns a settings form for configuring a specific player within a given profile.
 * 
 * @param $form_state
 *   The current form state.
 * @param $profile
 *   An array of profile settings loaded from the {swftools_profile} table.
 * @param $settings
 *   The name of the variable that stores the settings in a non-profiled context, e.g. swftools_wpaudio.
 * @param $module
 *   The module that provides the settings form.
 * @param $file
 *   The file that contains the settings form.
 * @param $function
 *   The name of the function that will return the settings form.
 * @return
 *   A form definition array to render the settings form.
 */
function swftools_profiles_configure_settings($form_state, $profile, $settings, $module, $file, $function) {
  
  // Load support file if required
  if ($module && $file) {
    require_once(drupal_get_path('module', $module) . '/' . $file);
  }
  
  // Get the form definition
  $form = $function($profile['profile']);

  // Add profile and settings tracking variables  
  $form['profile'] = array(
    '#type' => 'value',
    '#value' => $profile['profile'],
  );
 
  // See if this form is linked to global settings by checking if the profile variable for the first setting is not set
  if ($settings && variable_get(swftools_profiles_variable_name($settings[0], $profile['profile']), SWFTOOLS_UNDEFINED) == SWFTOOLS_UNDEFINED) {
    $form['mirror'] = array(
      '#type' => 'markup',
      '#value' => t('<p>The settings on this page are mirroring the SWF Tools global defaults.</p>'),
      '#weight' => -10,
    );
  }
    
  // Return the resulting form
  return swftools_profiles_configure_settings_form($form);
  
}


/**
 * Adds submit and reset buttons to the settings configuration form.
 *
 * @param $form
 *   An associative array containing the structure of the form.
 * @return
 *   The form structure.
 */
function swftools_profiles_configure_settings_form($form) {
  $form['buttons']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration') );
  $form['buttons']['reset'] = array('#type' => 'submit', '#value' => t('Reset to defaults') );

  if (!empty($_POST) && form_get_errors()) {
    drupal_set_message(t('The settings have not been saved because of the errors.'), 'error');
  }
  $form['#submit'][] = 'swftools_profiles_configure_settings_form_submit';
  $form['#submit'][] = 'swftools_admin_settings_submit';
  $form['#theme'] = 'system_settings_form';
  return $form;
}


/**
 * Executes the settings profile configuration submit.
 * 
 * See system_settings_form_submit() in system.module to see where this came from.
 */
function swftools_profiles_configure_settings_form_submit($form, &$form_state) {
  
  // Record the operation being performed, the profile and the settings
  $op = isset($form_state['values']['op']) ? $form_state['values']['op'] : '';
  $profile = $form_state['values']['profile'];
  
  // Exclude unnecessary elements.
  unset($form_state['values']['submit'], $form_state['values']['reset'], $form_state['values']['form_id'], $form_state['values']['op'], $form_state['values']['form_token'], $form_state['values']['form_build_id'], $form_state['values']['profile']);  
  
  // Iterate over remaining variables, storing them in the profile
  foreach ($form_state['values'] as $variable => $value) {
    if ($op == t('Reset to defaults')) {
      variable_del(swftools_profiles_variable_name($variable, $profile));
    }
    else {
      variable_set(swftools_profiles_variable_name($variable, $profile), $value);
    }
  }
  
  // Output a confirmation message
  if ($op == t('Reset to defaults')) {
    drupal_set_message(t('The configuration options have been reset to their default values.'));
  }
  else {
    drupal_set_message(t('The configuration options have been saved.'));
  }
  
}


/**
 * Validates the profile form before submission.
 */
function swftools_profiles_profile_form_validate($form, &$form_state) {

  $profile = array();
  
  $profile['profile'] = trim($form_state['values']['profile']);
  $profile['name'] = trim($form_state['values']['name']);

  // Work out what the profile was before the user submitted this form
  $old_profile = trim($form_state['values']['old_profile']);
  $old_name = trim($form_state['values']['old_name']);

  // Get the list of existing profiles
  $profiles = swftools_profiles_get_profiles();

  // Also need the list of names
  $names = array();
  foreach ($profiles as $info) {
    $names[] = $info['name'];
  }
  
  if (isset($profiles[$profile['profile']]) && $profile['profile'] != $old_profile) {
    form_set_error('profile', t('The machine-readable name %profile is already taken.', array('%profile' => $profile['profile'])));
  }

  if (!preg_match('!^[a-z0-9_]+$!', $profile['profile'])) {
    form_set_error('profile', t('The machine-readable name must contain only lowercase letters, numbers, and underscores.'));
  }

  if (in_array($profile['name'], $names) && $profile['name'] != $old_name) {
    form_set_error('name', t('The human-readable name %name is already taken.', array('%name' => $profile['name'])));
  }

}


/**
 * Implementation of hook_form_submit().
 */
function swftools_profiles_profile_form_submit($form, &$form_state) {

  // Register the operation being performed
  $op = isset($form_state['values']['op']) ? $form_state['values']['op'] : '';

  // Initialise an array for convenience
  $profile = $form_state['values'];
  $profile['profile'] = trim($profile['profile']);
  $profile['name'] = trim($profile['name']);
  $profile['old_profile'] = trim($profile['old_profile']);  
  $profile['clone'] = trim($profile['clone']);  

  // If the profile is to be deleted handover to deletion function
  if ($op == t('Delete profile')) {
    $form_state['redirect'] = 'admin/settings/swftools/profile/' . str_replace('_', '-', $profile['old_profile']) . '/delete'; 
    return;
  }

  // Execute the save
  $status = swftools_profiles_profile_save($profile);

  // Capture the profile name
  $t_args = array('%name' => $profile['name']);
  
  // Generate a message
  if ($status == SAVED_UPDATED) {
    drupal_set_message(t('The profile %name has been updated.', $t_args));
    
    // Update any existing settings to the new profile name
    foreach (swftools_profiles_settings() as $setting) {
      if (($settings = variable_get(swftools_profiles_variable_name($setting,$profile['old_profile']), SWFTOOLS_UNDEFINED)) != SWFTOOLS_UNDEFINED) {
        variable_set(swftools_profiles_variable_name($setting, $profile['profile']), $settings);
        variable_del(swftools_profiles_variable_name($setting, $profile['old_profile']));
      }
    }
    
  }
  elseif ($status == SAVED_NEW) {
    drupal_set_message(t('The profile %name has been added.', $t_args));
    watchdog('swftools', 'Added profile %name.', $t_args, WATCHDOG_NOTICE, l(t('view'), 'admin/settings/swftools/profiles/list'));
  }
  
  // If we are cloning a profile, copy settings for each configured player
  if ($profile['clone']) {
    
    // Clone any settings that already exist
    foreach (swftools_profiles_settings() as $setting) {
      if (($settings = variable_get(swftools_profiles_variable_name($setting, $profile['clone']), SWFTOOLS_UNDEFINED)) != SWFTOOLS_UNDEFINED) {
        variable_set(swftools_profiles_variable_name($setting, $profile['profile']), $settings);
      }
    }

  }
  
  // Redirect to profile listing page
  $form_state['redirect'] = 'admin/settings/swftools/profiles';
  
  // Rebuild profiles cache
  swftools_profiles_get_profiles(TRUE);
  
  // Rebuild theme registry
  drupal_rebuild_theme_registry();
  
  // Finished
  return;

}


/**
 * Saves a profile to the database.
 *
 * @param $profile
 *   The profile to save, as an array.
 * @return
 *   Status flag indicating outcome of the operation.
 */
function swftools_profiles_profile_save($profile) {

  // Set flag to show if this is an existing profile
  $is_existing = FALSE;
  
  // Set the name of the existing profile
  $existing_profile = !empty($profile['old_profile']) ? $profile['old_profile'] : $profile['profile'];

  // See if this profile is in the database
  $is_existing = db_result(db_query("SELECT COUNT(*) FROM {swftools_profiles} WHERE profile = '%s'", $existing_profile));

  // If the profile exists, update it, otherwise insert it
  if ($is_existing) {
    db_query("UPDATE {swftools_profiles} SET profile = '%s', name = '%s', description = '%s', multiple = %d, download_link = %d WHERE profile = '%s'", $profile['profile'], $profile['name'], $profile['description'], $profile['multiple'], $profile['download_link'], $existing_profile);
    return SAVED_UPDATED;
  }
  else {
    db_query("INSERT INTO {swftools_profiles} (profile, name, description, multiple, download_link) VALUES ('%s', '%s', '%s', %d, %d)", $profile['profile'], $profile['name'], $profile['description'], $profile['multiple'], $profile['download_link']);
    return SAVED_NEW;
  }
}


/**
 * Menu callback to delete a profile.
 */
function swftools_profiles_delete_confirm(&$form_state, $profile) {
  
  // Store the profile
  $form['profile'] = array(
    '#type' => 'value',
    '#value' => $profile['profile'],
  );
  
  // Store the name
  $form['name'] = array(
    '#type' => 'value',
    '#value' => $profile['name'],
  );

  // Define message and caption
  $message = t('Are you sure you want to delete the profile %profile?', array('%profile' => $profile['name']));
  $caption = '';
  
  // TODO: Warn if content is using this profile
  
//  $num_nodes = db_result(db_query("SELECT COUNT(*) FROM {node} WHERE type = '%s'", $type->type));
//  if ($num_nodes) {
//    $caption .= '<p>'. format_plural($num_nodes, '<strong>Warning:</strong> there is currently 1 %type post on your site. It may not be able to be displayed or edited correctly, once you have removed this content type.', '<strong>Warning:</strong> there are currently @count %type posts on your site. They may not be able to be displayed or edited correctly, once you have removed this content type.', array('%type' => $type->name)) .'</p>';
//  }

  $caption .= '<p>'. t('This action cannot be undone.') .'</p>';

  // Return a confirmation form
  return confirm_form($form, $message, 'admin/settings/swftools/profiles', $caption, t('Delete'));

}


/**
 * Processes profile deletion.
 */
function swftools_profiles_delete_confirm_submit($form, &$form_state) {
  
  // TODO: When we delete a profile we should account for profiles that might be using it
  
  // Delete any settings associated with this profile
  foreach (swftools_profiles_settings() as $setting) {
    if (($settings = variable_get(swftools_profiles_variable_name($setting, $form_state['values']['profile']), SWFTOOLS_UNDEFINED)) != SWFTOOLS_UNDEFINED) {
      variable_del(swftools_profiles_variable_name($setting, $form_state['values']['profile']));
    }
  }

  // Execute the delete
  db_query("DELETE FROM {swftools_profiles} WHERE profile = '%s'", $form_state['values']['profile']);
  
  // Generate a message
  $t_args = array('%name' => $form_state['values']['name']);
  drupal_set_message(t('The profile %name has been deleted.', $t_args));
  watchdog('swftools', 'Deleted profile %name.', $t_args, WATCHDOG_NOTICE);

  // Redirect back to profile list
  $form_state['redirect'] = 'admin/settings/swftools/profiles';
  
  // Done
  return;
}


/**
 * Returns an array of variable names available for association with profiles.
 */
function swftools_profiles_settings() {
  
  // Get SWF Tools methods
  $methods = swftools_get_methods();
  
  // Initialise an array for the results with the file handling settings
  $settings['swftools_handlers'] = 'swftools_handlers';
    
  // Build an array of other profile settings
  foreach ($methods as $handlers) {
    foreach ($handlers as $handler) {
      if (isset($handler['profile']['settings'])) {
        foreach ($handler['profile']['settings'] as $setting) {
          $settings[$setting] = $setting;
        }
      }
    }
  }
  
  // Return the results
  return $settings;  
  
}
