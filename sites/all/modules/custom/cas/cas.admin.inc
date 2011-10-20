<?php

/**
 * @file
 * CAS module settings UI.
 */

/**
 * Provides settings pages.
 */
function cas_admin_settings() {

  $form['library'] = array(
    '#type' => 'fieldset',
    '#title' => t('Library (phpCAS)'),
    '#collapsible' => TRUE,
  );

   // If Libraries API is not installed, display path settings.
    $form['library']['cas_library_dir'] = array(
      '#type' => 'textfield',
      '#title' => t('Library directory'),
      '#default_value' => variable_get('cas_library_dir', 'CAS'),
      '#description' => t('Specify the path to the directory the CAS.php file resides in. Leave blank to load cas from your phpinclude path.'),
      '#after_build' => array('cas_library_version_check'),
    );

  $form['login'] = array(
    '#type' => 'fieldset',
    '#title' => t('Login form'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['login']['cas_login_invite'] = array(
    '#type' => 'textfield',
    '#title' => t('CAS Login invitation'),
    '#default_value' => variable_get('cas_login_invite', CAS_LOGIN_INVITE_DEFAULT),
    '#description' => t('Message users will see to invite them to log in with CAS credentials.'),
  );

  $form['login']['cas_login_message'] = array(
    '#type' => 'textfield',
    '#title' => t('Successful login message'),
    '#default_value' => variable_get('cas_login_message', 'Logged in via sso as %cas_username.'),
    '#description' => t('Message displayed when a user logs in successfully. <em>%cas_username</em> will be replaced with the user\'s name.'),
  );
  $form['pages'] = array(
    '#type' => 'fieldset',
    '#title' => t('Redirection'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['pages']['cas_check_first'] = array(
    '#type' => 'checkbox',
    '#title' => t('Check with the CAS server to see if the user is already logged in?'),
    '#default_value' => variable_get('cas_check_first', 0),
    '#description' => t('This implements the <a href="@cas-gateway">Gateway feature</a> of the CAS Protocol. The check is only performed the first time a user visits your site, so that the local drupal logout is still useful for site admins.', array('@cas-gateway' => 'https://wiki.jasig.org/display/CAS/gateway')),
  );

  $form['pages']['cas_access'] = array(
    '#type' => 'radios',
    '#title' => t('Require CAS login for'),
    '#default_value' => variable_get('cas_access', 0),
    '#options' => array(t('specific pages'), t('all pages except specific pages')),
  );

  $form['pages']['cas_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Specific pages'),
    '#default_value' => variable_get('cas_pages', ''),
    '#cols' => 40,
    '#rows' => 5,
    '#description' => t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are '<em>blog</em>' for the blog page and '<em>blog/*</em>' for every personal blog. '<em>&lt;front&gt;</em>' is the front page."),
  );

  $form['pages']['cas_exclude'] = array(
    '#type' => 'textarea',
    '#title' => t('Excluded Pages'),
    '#default_value' => variable_get('cas_exclude', CAS_EXCLUDE),
    '#cols' => 40,
    '#rows' => 5,
    '#description' => t("Indicates which pages will be ignored (no login checks). Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are '<em>blog</em>' for the blog page and '<em>blog/*</em>' for every personal blog. '<em>&lt;front&gt;</em>' is the front page."),
  );

  $form['misc'] = array(
    '#type' => 'fieldset',
    '#title' => t('Login/Logout Destinations'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  // Settings for redirection upon first login
  $form['misc']['cas_first_login_destination'] = array(
    '#type' => 'textfield',
    '#title' => t('Initial login destination'),
    '#default_value' => variable_get('cas_first_login_destination', ''),
    '#size' => 40,
    '#maxlength' => 255,
    '#description' => t("Drupal path or URL. Enter a destination if you want the user to be redirected to this page on their first CAS login. An example path is <em>blog</em> for the blog page, <em>&lt;front&gt;</em> for the front page, or <em>user</em> for the user's page."),
  );

  // Setting for page to return to after a CAS logout
  $form['misc']['cas_logout_destination'] = array(
    '#type' => 'textfield',
    '#title' => t('Logout destination'),
    '#default_value' => variable_get('cas_logout_destination', ''),
    '#size' => 40,
    '#maxlength' => 255,
    '#description' => t("Drupal path or URL. Enter a destination if you want a user to be directed to this page after logging out of CAS, or leave blank to direct users back to the previous page. An example path is <em>blog</em> for the blog page or <em>&lt;front&gt;</em> for the front page."),
  );

   $form['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Miscellaneous & Experimental Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['advanced']['cas_debugfile'] = array(
    '#type' => 'textfield',
    '#title' => t('CAS debugging output filename'),
    '#default_value' => variable_get('cas_debugfile', ''),
    '#maxlength' => 255,
    '#description' => t("Leave empty if you don't want debugging output."),
  );

  return system_settings_form($form);
}

/**
 * Checks that the library is installed in the location specified by loading the
 * class and extracting the version.
 *
 * @param $element
 *   The form element containing the "library" fieldset.
 * @param $form_state
 *   An array containing the form's state information.
 *
 * @return
 *   The modified form element containing the "library" fieldset.
 */
function cas_library_version_check($element, &$form_state) {
  //$path = module_exists('libraries') ? NULL : $element['#value'];
  $path = $element['#value'];
  // Suppress errors if phpCAS cannot be loaded.
  if ($version = @cas_phpcas_load($path)) {
    $element['#suffix'] = '<div class="ok messages">' . t('phpCAS version %version successfully loaded.', array('%version' => $version)) . '</div>';
  }
  else {
    $element['#suffix'] = '<div class="error messages">' . t('The phpCAS library was not found or could not be loaded.') . '</div>';
  }
  return $element;
}
