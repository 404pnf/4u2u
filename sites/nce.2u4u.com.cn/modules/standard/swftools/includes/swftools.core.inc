<?php 
// $Id: swftools.core.inc,v 1.1.2.2 2010/04/08 23:46:02 stuartgreenfield Exp $

/**
 * SWF Tools core functions.
 * 
 * These functions are needed by both the API and the full SWF Tools module,
 * so they have been separated in to this include file. This is the 'minimum'
 * set of functions and allows us to:
 * 
 * - Retrieve a list of embedding methods from enabled modules
 * - Report the direct embedding method as available
 * - Theme content using the swftools_direct embedding method
 * - Theme elements of #type => 'swftools'
 * - Return constants defining the library, alternate content,
 *   and the default for adding JavaScript to all pages.
 */


/**
 * JavaScript will be added to all pages when they are served, even if SWF Tools isn't called directly.
 */
define('SWFTOOLS_ALWAYS_ADD_JS', 0x0001);

/**
 * The path to the libraries directory containing supporting players and scripts.
 */
define('SWFTOOLS_LIBRARIES', 'sites/all/libraries/');

/**
 * The default alternate markup string that is displayed if the embedding process fails.
 */
define('SWFTOOLS_DEFAULT_HTML_ALT', '<p>' . t('You are missing some Flash content that should appear here! Perhaps your browser cannot display it, or maybe it did not initialize correctly.') . '</p>');

/**
 * JavaScript will be added inline with the page markup.
 */
define('SWFTOOLS_JAVASCRIPT_INLINE', 0x0001);

/**
 * JavaScript will be added to the page header.
 */
define('SWFTOOLS_JAVASCRIPT_HEADER', 0x0002);


/**
 * Implementation of hook_swftools_embed().
 * 
 * Returns the markup for the page, using compliant HTML.
 */
function theme_swftools_direct($file, $options) {
  
  // Strip out unset values, e.g. bgcolor
  $options['params'] = array_filter($options['params']);
  
  // Build parameters string
  $params = '';
  foreach ($options['params'] as $key => $value) {
    $params .= '<param name="' . rawurlencode($key) . '" value="' . rawurlencode($value) . '" />';
  }
  
  // Attach flashvars parameter, if flashvars are present
  $params .= $options['flashvars'] ? '<param name="flashvars" value="' . drupal_query_string_encode($options['flashvars']) . '" />' : '';

  // Construct embedding markup
  $html  = '<object id="' . $options['othervars']['id'] . '" name="' . $options['othervars']['id'] . '" classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" width="' . $options['othervars']['width'] . '" height="' . $options['othervars']['height'] . '">';
  $html .= '<param name="movie" value="' . $file . '" />';
  $html .= $params;
  $html .= '<!--[if gte IE 7]>-->';
  $html .= '<object name="' . $options['othervars']['id'] . '" type="application/x-shockwave-flash" data="' . $file . '" width="' . $options['othervars']['width'] . '" height="' . $options['othervars']['height'] . '">';
  $html .= $params;
  $html .= '<!--<![endif]-->';
  $html .=  $options['othervars']['html_alt'];
  $html .= '<!--[if gte IE 7]>-->';
  $html .= '</object>';
  $html .= '<!--<![endif]-->';
  $html .= '</object>';
  
  // Return the result
  return $html;

}


/**
 * Collects information from all modules about the players and embedding methods available.
 * 
 * @param $action
 *   Optional parameter to retrieve data only about a specific method.
 * @param $reset
 *   Optional parameter which if TRUE will reset the method cache and rebuild it.
 * @return
 *   An array of data describing the available methods.
 */
function swftools_get_methods($action = NULL, $reset = FALSE) {
  
  // Cache methods array as it may be called several times
  static $methods;

  // If user has requested the cache to be reset then reset it
  if ($reset || !isset($methods)) {
    if (!$reset && ($cached = cache_get('swftools:methods'))) {
      $methods = $cached->data;
    }
    else {
      $methods = array();
      foreach (module_implements('swftools_methods') as $module) {
        $function = $module . '_swftools_methods';
        if (function_exists($function)) {
          $implements = $function();
          foreach ($implements as $method_type => $method) {
            foreach ($method as $method_name => $method_details) {
              $method_details += array(
                'name'     => $method_name,
                'module'   => '',
                'title'    => '',
                'download' => '',
                'library'  => '',
              );
              if ($method_type == 'swftools_embed_method') {
                $method_details += array(
                  'theme' => $method_name,     
                );
              } 
              else {
                $method_details += array(
                  'version'  => 7,
                  'profile'  => array(),
                );
              }             
              $methods[$method_type][$method_name] = $method_details;
            }
          }
        }
      }
      cache_set('swftools:methods', $methods);
    }
  }
  
  // In case no module is presenting a method for the required action the following line avoids a notice error
  if ($action) {
    $methods += array(
      $action => NULL,
    );
  }
  
  // Return results - either for the specific action, or the whole array
  return $action ? $methods[$action] : $methods;

}


/**
 * Flushes all caches when new settings are stored.
 * 
 * This function is called by player and embedding modules as a
 * submit handler to ensure all cached content is purged. 
 */
function swftools_admin_settings_submit($form, &$form_state) {
  
  // Flush all caches so new players appear
  drupal_flush_all_caches();
    
}


/**
 * Themes an swftools element by passing it on to the appropriate theme function.
 * 
 * If the incoming element is not an array someone is calling to place a simple
 * swf on the page and they're using the API, so hand it to theme_swftools_api()
 * 
 * If the incoming element is an array, and SWF Tools main module is present then
 * hand the element to swf() as it provides more power, such as auto-detection of
 * sizes and automatic rendering of media in to players.
 * 
 * If the incoming element is an array, and SWF Tools main module is not avaiable
 * then assume we have a simple swf, so call theme_swftools_api() with just
 * $element['#value']
 * 
 * @param $element
 *   An element array.
 * @return
 *   Markup to render the object.
 */
function theme_swftools($element, $options = array()) {

  // If the incoming element is a Forms API element remap it  
  if (is_array($element) && isset($element['#value'])) {
    $options = array(
      'params' => $element['#params'],
      'othervars' => $element['#othervars'],
      'flashvars' => $element['#flashvars'],
      'methods' => $element['#methods'],
    );
    $element = $element['#value'];
  }
  
  // Is the full version of SWF Tools installed?
  if (defined('SWFTOOLS_INSTALLED')) {

    // Hand over to swf() and return the result
    return $element ? swf($element, $options) : '';
    
  }
  
  // Hand over to theme_swftools_api and return the result
  return $element ? theme('swftools_api', $element, $options) : '';

}


/**
 * Implementation of hook_swftools_methods().
 * 
 * Note that we use a trick here as this method is always available.
 * We implement system_swftools_methods() as we know the system module
 * will always be present so we can be sure this gets reported.
 */
function system_swftools_methods() {
  
  $methods['swftools_embed_method']['swftools_direct'] = array(
    'module'       => 'swftools',
    'title'        => t('Direct embedding'),
  );

  return $methods;

}
