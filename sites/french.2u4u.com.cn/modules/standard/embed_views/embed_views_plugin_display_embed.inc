<?php
// $Id: embed_views_plugin_display_embed.inc,v 1.1 2009/05/23 14:25:00 grndlvl Exp $
/**
 * @file
 * Contains the embed display plugin.
 */
 
/**
 * A plugin to handle defaults on a view.
 *
 * @ingroup views_display_plugins
 */
class embed_views_plugin_display_embed extends views_plugin_display {
  /**
   * Determine if this display is the 'default' display which contains
   * fallback settings
   */
  function is_default_display() { return FALSE; }
 
  /**
   * The default execute handler fully renders the view.
   *
   * For the simplest use:
   * @code
   *   $output = $view->execute_display('default', $args);
   * @endcode
   *
   * For more complex usages, a view can be partially built:
   * @code
   *   $view->set_arguments($args);
   *   $view->build('default'); // Build the query
   *   $view->execute(); // Run the query
   *   $output = $view->render(); // Render the view
   * @endcode
   *
   * If short circuited at any point, look in $view->build_info for
   * information about the query. After execute, look in $view->result
   * for the array of objects returned from db_query.
   *
   * You can also do:
   * @code
   *   $view->set_arguments($args);
   *   $output = $view->render('default'); // Render the view
   * @endcode
   *
   * This illustrates that render is smart enough to call build and execute
   * if these items have not already been accomplished.
   *
   * Note that execute also must accomplish other tasks, such
   * as setting page titles, breadcrumbs, and generating exposed filter
   * data if necessary.
   */
  function execute() {
    return $this->view->render($this->display->id);
  }
}
