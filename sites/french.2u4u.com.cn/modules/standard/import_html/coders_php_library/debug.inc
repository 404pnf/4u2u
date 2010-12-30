<?php
// $Id: debug.inc,v 1.17.2.9 2009/10/06 13:57:15 dman Exp $
/**
 * @file
 * Small library of diagnostic feedback stuff.
 *
 * Maybe should be tracing to a file instead but...
 * Set DEBUGLEVEL > 0 to see what's going on
 * Set DEBUGSYSLOG to send messages to syslog also
 * Set DEBUGBACKTRACE for performance and callstack logging
 *
 * @package coders
 * @author Dan Morrison http://coders.co.nz/
 */

/**
 * Wrapper to watchdog
 * 
 * WATCHDOG_DEBUG level alerts are discared unless debug_level is set
 */
function import_html_debug($message, $variables = array(), $severity = WATCHDOG_DEBUG) {
  $debuglevel = import_html_variable('debug_level');
  if (empty($debuglevel) && ($severity >= WATCHDOG_DEBUG)) return;
  if (! is_array($variables)) {
    trigger_error("Incorrect code call to import_html_debug ($message)");
  }
  
  watchdog('Import HTML', $message, $variables, $severity);
}

function import_html_debug_code($message, $data = array(), $severity = WATCHDOG_DEBUG) {
  $printed_value = "<textarea rows=20 style=\"width: 100%;\">\n ". print_r($data, 1) ." </textarea>";
  import_html_debug($message . $printed_value, $variables = array(), $severity);
}

/*
 * This is (obviously) a debug-only library
 * and use of it should eventually be removed
 * BUT during development this library might 
 * be called upon more than once, from different locations even.
 * Do our own require_once - type check.
 */
if (! function_exists('debug')) { 

  define('DEBUGBACKTRACE', 0);


  /**
   * Display a feedback message
   * If DEBUGLEVEL is set, and is greater than or equal to the threshold level of this
   * message, display it. If the threshold is greater, display nothing.
   * <pre>debug("Beginning user submission process",1)</pre>
   * <pre>debug("Checking configuration files exist",2)</pre>
   * <pre>debug("Making database lookup '$request'",3)</pre>
   *
   * if global DEBUGBACKTRACE is set, additional backtrace and timer detail 
   * is also displayed.
   *
   * ... would return varying levels of detail depending on the value of DEBUGLEVEL
   * @param string $message The message to display
   * @param int    $level The amount of detail to show - 1 is basic, 2 identifies most function calls, 3 is verbose.
   * @global DEBUGLEVEL
   */
  function debug($message, $level = 0) {
    $debuglevel = import_html_variable('debug_level');
    if (! is_string($message)) return debug_pre($message, $level);
    if ( ($level) && ($level > $debuglevel) ) return; 
    drupal_set_message($message . (DEBUGBACKTRACE ? debug_get_trace() : '') );
  }


  /**
   * Dump an object or code listing in viewable raw format
   */
  function debug_pre($message, $level=0) {
    $debuglevel = import_html_variable('debug_level');
    if ( ($level) && ($level > $debuglevel) ) return; 
    debug("<pre>". htmlspecialchars(print_r($message, 1)) ."</pre>".  debug_get_trace(), $level);
  }
  
  function debug_get_microtime() { 
    list($usec, $sec) = explode(" ", microtime()); 
    return ((float)$usec + (float)$sec); 
  } 

}
