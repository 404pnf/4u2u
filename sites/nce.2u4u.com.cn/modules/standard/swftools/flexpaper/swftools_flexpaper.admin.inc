<?php
// $Id: swftools_flexpaper.admin.inc,v 1.1.2.2 2010/04/05 08:48:38 stuartgreenfield Exp $

function swftools_flexpaper_admin_form() {
  
  // Initialise array
  $form = array();

  // Fetch the form by using the profile definition
  $form = swftools_flexpaper_profile_form();

  // We will have a spare #submit after fetching the form
  unset($form['swftools_flexpaper']['#submit']);
  
  // Add custom form handler to flush cache upon submit
  $form['#submit'][] = 'swftools_admin_settings_submit';
  
  // Return finished form
  return system_settings_form($form);

}


/**
 * Submit handler to filter out form settings that are either empty strings or 'default', and to handler fit behavior.
 */
function swftools_flexpaper_admin_form_submit($form, &$form_state) {

  // We convert FitBehavior to the appropriate FlexPaper parameter
  switch ($form_state['values']['swftools_flexpaper']['FitBehavior']) {
    case 'page':
      $form_state['values']['swftools_flexpaper']['FitPageOnLoad'] = 'true';
      break;
    case 'width':
      $form_state['values']['swftools_flexpaper']['FitWidthOnLoad'] = 'true';
  }
  
  // We don't want to store FitBehavior
  $form_state['values']['swftools_flexpaper']['FitBehavior'] = '';
  
  // Keep only those items that actually have a value
  $filtered_settings = array_diff($form_state['values']['swftools_flexpaper'], array('', 'default'));
  
  // Replace full suite of values with the reduced set we created
  $form_state['values']['swftools_flexpaper'] = $filtered_settings;
  
}


/**
 * Returns a form definition for use by the profile system.
 *
 * @return
 *   A form definition array
 */
function swftools_flexpaper_profile_form($profile = '') {

  /**
   * Retrieve profile settings, if they have been created.
   * If there is no profile then the global defaults will be used, which might be
   * those from the module defaults, or those from the primary settings page.
   * This seems like a logical behavior to have!
   */
  $saved_settings = _swftools_flexpaper_settings($profile, SWFTOOLS_FULL_SETTINGS);
  
  // Convert fit settings to FitBehavior for common radio option
  if ($saved_settings['FitPageOnLoad'] == 'true') {
    $saved_settings['FitBehavior'] = 'page';
  }
  else if ($saved_settings['FitWidthOnLoad'] == 'true') {
    $saved_settings['FitBehavior'] = 'width';
  }
  else {
    $saved_settings['FitBehavior'] = 'default';    
  }
  
  // Initialise array
  $form = array();
  
  $form['swftools_flexpaper']['height'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['height'],
    '#title' => t('Height'),
    '#description' => t('The height of the player in pixels.'),
    '#size' => 8,
  );
  
  $form['swftools_flexpaper']['width'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['width'],
    '#title' => t('Width'),
    '#description' => t('The width of the player in pixels.'),
    '#size' => 8,
  );
  
  $form['swftools_flexpaper']['Scale'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['Scale'],
    '#title' => t('Scale'),
    '#description' => t('The initial zoom factor that should be used. Should be a number above 0 (1=100%)'),
    '#size' => 8,
  );
  
  $form['swftools_flexpaper']['ZoomTransition'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['ZoomTransition'],
    '#title' => t('Zoom transition'),
    '#description' => t('The zoom transition that should be used when zooming in FlexPaper. It uses the same Transition modes as the Tweener. The default value is easeOut. Some examples: easenone, easeout, linear, easeoutquad.'),
    '#size' => 8,
  );
  
  $form['swftools_flexpaper']['ZoomTime'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['ZoomTime'],
    '#title' => t('Zoom time'),
    '#description' => t('The time it should take for the zoom to reach the new zoom factor. Should be 0 or greater.'),
    '#size' => 8,
  );
  
  $form['swftools_flexpaper']['ZoomInterval'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['ZoomInterval'],
    '#title' => t('Zoom interval'),
    '#description' => t('The interval which the zoom slider should be using. Basically how big the "step" should be between each zoom factor. The default value is 0.1. Should be a positive number.'),
    '#size' => 8,
  );

  $form['swftools_flexpaper']['FitBehavior'] = array(
    '#type' => 'radios',
    '#options' => array(
      'default' => t('Use scale setting'),
      'page' => t('Fit page to viewer'),
      'width' => t('Fit width to viewer'),
    ),
    '#default_value' => $saved_settings['FitBehavior'],
    '#title' => t('Document size on loading'),
    '#description' => t('When the document loads it can be shown at the scale specified above, scaled so the whole page fits in the viewer, or scaled so the document width fills the viewer.'),
    '#size' => 8,
  );
  
  $form['swftools_flexpaper']['PrintEnabled'] = array(
    '#type' => 'radios',
    '#options' => array(
      'true'  => t('Enabled'),
      'false' => t('Disabled'),
    ),
    '#default_value' => $saved_settings['PrintEnabled'],
    '#title' => t('Printing'),
    '#description' => t('Disables or enables print for the document. Please note that this in no way sufficient by itself to protect your intellectual property. It is merely a way of disabling the functionality for the average user and is in no way any final digital rights management or copyright protection.'),
    '#size' => 8,
  );
  
  $form['swftools_flexpaper']['FullScreenAsMaxWindow'] = array(
    '#type' => 'radios',
    '#options' => array(
      'true'  => t('Enabled'),
      'false' => t('Disabled'),
    ),
    '#default_value' => $saved_settings['FullScreenAsMaxWindow'],
    '#title' => t('Full screen as maximised window'),
    '#description' => t('This setting is disabled because it does not work correctly under Drupal.'),
    '#disabled' => TRUE,
    '#size' => 8,
  );
  
  $form['swftools_flexpaper']['localeChain'] = array(
    '#type' => 'select',
    '#options' => array(
      'default'  => t('English (US)'),
      'fr_FR' => t('French'),
      'zh_CN' => t('Chinese (simple)'),
      'es_ES' => t('Spanish'),
      'pt_BR' => t('Brazilian Portugese'),
      'ru_RU' => t('Russian'),
      'fi_FN' => t('Finnish (fi)'),
      'de_DE' => t('German'),
      'nl_NL' => t('Netherlands'),
      'tr_TR' => t('Turkish'),
      'se_SE' => t('Swedish'),
      'pt_PT' => t('Portugese'),
      'el_EL' => t('Greek'),
      'da_DN' => t('Danish'),
      'cz_CS' => t('Czech'),
      'it_IT' => t('Italian'),
      'pl_PL' => t('Polish'),
      'pv_FN' => t('Finnish (pv)'),
      'hu_HU' => t('Hungarian'),
    ),
    '#default_value' => $saved_settings['localeChain'],
    '#title' => t('Language'),
    '#description' => t('Sets the locale (language) to use.'),
  );
  
  // Initialise tree as we want to store arrays
  $form['swftools_flexpaper']['#tree'] = TRUE;

  // Add custom form handler to accommodate fit behavior and to strip blanks / defaults
  $form['#submit'][] = 'swftools_flexpaper_admin_form_submit';
    
  // Return finished form
  return $form;

}
