<?php
// $Id: core.inc,v 1.1.2.14 2009/10/06 14:09:02 dman Exp $
/**
 * @file
 * Basic per-module functionality used by import_html.
 *
 * Each available module MAY implement a hook_import_html() function to add or
 * manipulate its own data as the node gets saved.
 *
 * This set defines the known core module attributes that can be added to a node
 * when importing. It sets the node (content & title) values, the menu and path
 * values, and possibly some taxonomy tags.
 *
 * Each of these (pretty integral) attributes is set in a modular way as an
 * example for extensions, and to keep the central import_html codebase lighter.
 *
 *
 * @ingroup import_html Import HTML
 * @author Dan Morrison http://coders.co.nz/
 */


/**************************************************
 * NODE
 **************************************************/

/**
 * Implementation of hook_import_html
 *
 * Add appropriate normal node attributes - title, body and teaser
 * - to the node
 */
function node_import_html($profile, &$node, $datadoc = NULL) {
  // Setting a few basics will just avoid 'undefined' complaints when previewing
  $node->nid = isset($node->nid) ? $node->nid : 0;
  $node->sticky = isset($node->sticky) ? $node->sticky : FALSE;


  //
  //  Title
  // Note, internally the title should always be plaintext, encoded characters and no newlines
  // A meta 'title' may have been set,
  // but I'll use the real visible one by preference.
  $h1 = xml_get_element_content($datadoc, 'h1');
  if ($h1) {
    $node->title = $h1;
  }
  else {
    $title_elem = xml_get_element_content($datadoc, 'title');
    if ($title_elem) {
      $node->title = $title_elem;
    }
  }

  //
  // BODY is the thing with id=content or whatever is set in the prefs
  //
  import_html_debug_code('XML DOM being scanned for XPATH data extraction to find the body content', xml_tostring($datadoc));
  $content_element = xml_getelementbyid($datadoc, 'content');

  if (!$content_element) {
    import_html_debug("Failed to find a body, anything with id='content' in this page", array(), WATCHDOG_NOTICE);
    // TODO some cck may be valid without a 'content' body?
  }

  if ($content_element) {
    $node->body = trim(xml_tostring($content_element, TRUE));
    // The XSL may give us further hints about how it found this body data
    $precision = xml_getattribute($content_element, 'precision');
    if ($precision != NULL) {
      $node->import_html_precision = $precision;
      $explanation = xml_getattribute($content_element, 'title');
      import_html_debug(
        "I'm %precision % confident that we found the right body element. !explanation",
        array('%precision' => 100*$precision, '!explanation' => $explanation),
        WATCHDOG_INFO
      );
    }
  }

  // It's possible that our input was content-encoded (if it came from RSS or the old import-xml node)
  // If so, the entities should be unwrapped.
  // Other (HTML) imports should not require this
  // @TODO when was $node->content_encoded being flagged?
  $node->body = (isset($node->content_encoded)) ? html_entity_decode($node->body):$node->body;

  //
  //  Teaser
  //
  $teaser = xml_textcontent( xml_getelementbyid($datadoc, 'teaser') );
  $description = xml_textcontent( xml_getelementbyid($datadoc, 'description') );
  if (!$teaser) $teaser = $description ;
  if ($teaser) {
    // We have an explicit, exclusive teaser.
    // This should be handled by NOT joining it with the body.
    $node->teaser_include = FALSE;
    $node->teaser = $teaser;
  }

  // Make up and refine our own teaser
  // TODO work on this a bit more - it's not always what we want
  /*
  // No custom teaser found, but
  // Imported HTML is highly likely to contain formatting that
  // will ruin teasers. Do our own cut-down version that assumes
  // FILTERED HTML
  if (!$teaser) {
    $teaser = filter_filter('process', 0, 1, node_teaser($node->body));
    if ($teaser) $node->teaser = $teaser;
  }

  // Note that if setting our own explicit teaser (and overriding the default process)
  // we must also set the 'do not show in body' flag or we will be creating repetition
  // as the edit form glues it back together.
  */

}


/**************************************************
 * USER
 **************************************************/

/**
 * Implementation of hook_import_html
 *
 * Add appropriate user identification to the new node.
 */
function user_import_html($profile, &$node, $datadoc = NULL) {
  global $user;
  $node->uid = $user->uid;
  $node->name = $profile['import_user'];
  if ($import_user = user_load(array('name' => $node->name))) {
    $node->uid = $import_user->uid;
  }
}


/**************************************************
 * MENU
 **************************************************/

/**
 * Menu can't do anything useful in this new-node phase, BUT it can reserve
 * its namespace. Miscellaneous class HTML import may create an attribute called
 * 'menu'. That would be bad.
 */
function menu_import_html($profile, &$node, $datadoc = NULL) {
  unset($node->menu);
}

  //
  // This is currently a freaking mess. I don't know what the menu router is trying to do these days.
  //

/**
 * Set alias and navigation for the given node
 * Helper for import_html_import_files()
 */
function menu_import_html_after_save($profile, &$node, $datadoc = NULL) {
  $normal_path = "node/{$node->nid}";

  // Create Menu item for this new item
  if ($profile['create_menus']) {
    $node->label = import_html_guess_label($node->title, $node->path);

    if (!empty($node->menu)) {
      $menu = $node->menu;
      // a placeholder or previous menu item existed and was found when the node was loaded.
      import_html_debug("We will re-use the existing menu item, and keep its place in the sitemap");
    }
    else {
      // Check if a placeholder menu for the alias exists.
      // This can happen if the child items were created earlier and required a placeholder
      // Try both canonic and aliased paths
      if ( ! $menu = menu_get_item_by_path($normal_path) ) {
        $menu = menu_get_item_by_path($node->path);
      }
    }
    // $menu is a menu_link array

    if (! empty($menu)) {
      // Found a pre-existing menu, update it
      import_html_debug("Discovered that a placeholder menu item for %path already exists. Filling that one out with the full details now", array('%path' => $node->path));
      #dpm($menu);
    }
    else {
      // New menu item
      $parent_menu = import_html_create_menu_path(dirname($node->path), $profile);
      #dpm(array('After creating the menu path, the parent menu is' => $parent_menu));

      if (empty($parent_menu)) {
        trigger_error("Code should not get here - failed to build menu - no parent menu returned to hang this node off.", E_USER_ERROR);
        return;
      }
      // New menu item
      $menu = array(
        'link_title' => $node->label,
        'link_path'  => $normal_path,
        'parent'     => $parent_menu['menu_name'] .':'. $parent_menu['mlid'],
        'menu_name'  => $parent_menu['menu_name'],
        'plid'       => $parent_menu['mlid'],
      );
    }

    $node->menu = $menu;
    # dpm(array("about to save menu link " => $menu));
    menu_link_save($node->menu);
  }
}


/**
 * Given a traditional URL path, return the parent menu item
 *
 * A helper function to menu_import_html_after_save()
 *
 * This is a recursive function that slices the given
 * (alias) path up until it finds a menu item it recognises.
 * Once found, it comes back down again building a path
 * until we end up with the new parent menu id.
 *
 * If you are creating menu items that do not yet have a parent - the parent
 * menu link cannot go anywhere useful.
 * I'd like to have it fall back to system_admin_menu_block_page by default, but
 * can't see how to make that happen on the fly.
 *
 * @param $path
 *   the  path (aliased URL) we intend to construct
 * @param $title
 *   optional    Display title of the menu item at that path point, otherwist
 * it'll use the last fragment of the path as a display title
 * @return a menu object, the bottom-most, the one we asked for.
 * FALSE if it hit
 * the top unexpectedly
 *
 * @return a menu_link definition ARRAY
 *
 **/
function import_html_create_menu_path($path, $profile = array()) {

  list($menu_name, $plid) = explode(':', $profile['menu_parent_id'], 2);
  $root_parent = array('mlid' => $plid, 'menu_name' => $menu_name);

  if ((!module_exists('menu')) || (!module_exists('path'))) {
    // It's possible without path.module - but we can't structure them with what we know;
    return $root_parent;
  }

  import_html_debug("Looking for a menu item matching path '$path' ");

  // Check parent exists
  if ($menu_link_item = menu_get_item_by_path($path)) {
    import_html_debug("Found the menu item for '$path'." . $menu_link_item['mlid']);
    return $menu_link_item;
  }

  import_html_debug("Failed to find a menu item for the URL '$path'. Making it now.");

  $p_path = dirname($path); // parent path

  if ($p_path == dirname($p_path)) {
    import_html_debug("
        Hit topmost menu path '$p_path', this is either caused by creating a new menu tree
        from the bottom up and we just reached the top,
        or a recursion error (illegal paths).
    ", array(), WATCHDOG_INFO);

    $parent = $root_parent;
  }
  else {
    if (! $parent = menu_get_item_by_path($p_path)) {
      // Parent not found. Need to make it up.
      // Recurse...
      $parent = import_html_create_menu_path($p_path, $profile);
      // ... and welcome back again!
      // That will have climbed up and come back down. with its nearest new ancestor
    }
  }
  // and attach self to it

  if (!$parent) {
    import_html_debug("Failed to regressively build menu for '$path'. This should not happen. Dunno why we are here.", array(), WATCHDOG_ERROR);
    trigger_error("This code should never run. Something must be wrong in the input", E_USER_ERROR);
    return FALSE;
  }

  if ($path == '.') {
    return $root_parent;
  }

  import_html_debug("Creating a placeholder menu item for $path. Parent was found to be item {$parent['mlid']}", array(), WATCHDOG_INFO);
  $menu_link_item = import_html_create_placeholder_menu_item($path, $profile, $parent);

  if (empty($menu_link_item)) {
    trigger_error("Failed to create placeholder menu item ($path, $parent) ", E_USER_ERROR);
    return NULL;
  }

  import_html_debug("New Menu Item '". $menu_link_item['title'] ."' id is :". $menu_link_item['mlid']);
  return $menu_link_item;
}

/**
 * Create a dummy node to represent a menu container.
 *
 * This appears to be the only sane way to build a site from the bottom up.
 * I can, If I try, create menu trees that do not link to nodes ... but most
 * users will not be able to remove, over-write or edit them using the tools
 * they are used to.
 *
 * Instead, just make empty shells on-the-fly. You can kill them via content
 * management and things will bubble up and Drupal will not have a hernia.
 *
 * @param $parent is a parent link item array, containing (at least) a mlid and
 * menu_name
 */
function import_html_create_placeholder_menu_item($path, $profile, $parent_menu) {
  $node = (object) array(
    'type'    => $profile['content_type'],
    'title'   => t('PLACEHOLDER - ') . import_html_guess_label('', $path),
    'path'    => $path,
    'status'  => $profile['import_status'],
    'promote' => FALSE,
    'body' => t("
      Placeholder page.
      Created by import_html.
      This is required to keep the menu in place during imports.
      Feel free to delete it!
    "),
  );
  user_import_html($profile, $node);
  import_html_debug("Inserting placeholder Node !node_link to keep the menu in shape", array('!node_link' => l($node->path, $node->path)), WATCHDOG_NOTICE);
  node_save($node);

  if (! $node->nid) {
    trigger_error("Failed to create placeholder node to hold the menus together. Not fatal, but some sections under $path will be unstructured", E_USER_WARNING);
    return NULL;
  }

  // Now make the menu for this dummy node
  $menu = array(
    'parent'     => $parent_menu['menu_name'] .':'. $parent_menu['mlid'],
    'menu_name'  => $parent_menu['menu_name'],
    'plid'       => $parent_menu['mlid'],
    'link_title' => import_html_guess_label('', $path),
    'link_path'  => 'node/'. $node->nid,
  );

  $mlid = menu_link_save($menu);

  if (! $mlid) {
    trigger_error("Failed to create placeholder menu link item. Not fatal, but some sections under $path will be unstructured", E_USER_WARNING);
    return NULL;
  }

  $new_menu = menu_link_load($mlid);
  return $new_menu;
}



/**
 * Return a menu item matching a given path or alias.
 * The alias for the requested path will be tried automatically.
 *
 * @return a menu link ARRAY. NULL if no valid menu item was found.
 */
function menu_get_item_by_path($path) {
  // Caching works against me when adding lots of aliases in one go.
  // Cannot trust get_alias etc
  // Wipe it :(
  drupal_lookup_path('wipe'); // This is not working?

  // Use DB to fetch all aliases
  $aliases = array($path);
  $placeholders = array(' link_path = "%s" ');
  $result = db_query("SELECT src FROM {url_alias} WHERE dst = '%s'", $path);
  while ($row = db_fetch_array($result)) {
    $aliases[] = $row['src'];
    $placeholders [] = ' link_path = "%s" ';
  }

  // It's bad mojo to mess with the DB directly, but menu doesn't provide a lookup API.
  // Or a way to avoid caching. Do it by hand if I need a newly added menu
  $row = db_fetch_array(db_query('SELECT * FROM {menu_links} WHERE link_path <> "" AND ('. join($placeholders, 'OR') .') ', $aliases ));
  if ($row) {
    // If I don't unserialize this, it gets flattened later
    $row['options'] = unserialize($row['options']);
    return $row;
  }
  import_html_debug("menu_get_item_by_path() failed. Failed to find a menu item called either '". join($aliases, ', ') ."' ");
  return NULL;

}



/**************************************************
 * PATH
 **************************************************/

/**
 * Path does not actually add the alias here - that is taken care ov naturally
 * during node_save.
 * BUT path.module is just not quick enough - it doesn't recognise newly added
 * items, so sometimes find itself making a dozen aliases of the same thing at
 * onec. Forec a path flush every round.
 */
function path_import_html($profile, &$node, $datadoc = NULL) {
  drupal_lookup_path('wipe');

  // Path requires the nodes language to be set. Don't know why it's a PATH job, but
  // that's the module that complains about undefined property if it isn't
  $node->language = isset($node->language) ? $node->language : '';


}


/**
 * Add path alias support to the import_html process
 *
 * Needed to be run after save as we need to know the nid
 *
 * Adds an old-style (legacy) alias to the node path if required.
 */
function path_import_html_after_save($profile, &$node, $datadoc = NULL) {
  #dpm(array('INVOKED path_import_html_after_save for '. $node->path));
  if ($profile['legacy_aliases'] && ($node->old_path != $node->path)) {
    import_html_debug("Setting up URL ALIASES for this item now. Directing {$node->old_path} to go to the system path ". drupal_get_normal_path($node->path), array(), WATCHDOG_DEBUG);

    $normal_path = "node/{$node->nid}";

    if ($normal_path == $node->path) {
      import_html_debug(
        "Failed to resolve %node_path into a system path. Cannot create alias at this time.",
        array('%node_path' => $node->path),
        WATCHDOG_NOTICE
      );
    }
    else {
      // path_set_alias is WRONG when it looks for existing items
      // drupal_lookup_path('wipe'); // DOES NOT WORK - to it ourselves.
      if (! db_result(db_query("SELECT count(*) FROM {url_alias} WHERE dst = '%s' ", $node->old_path))) {
        path_set_alias($normal_path, $node->old_path);
      }
      import_html_debug(
        "This document (known internally as '%normal_path' )
          should now be accessible via aliases as both
          '!main_alias' and '!legacy_alias' ",
        array(
          '%normal_path' => $normal_path,
          '!main_alias' => l($node->path, $node->path),
          '!legacy_alias' => l($node->old_path, $node->old_path)
        ),
        WATCHDOG_NOTICE
      );
    }
  }

}

/**************************************************
 * TAXONOMY
 **************************************************/

/**
 * Absorbs elements in the import document we recognise as being (probably)
 * taxonomy terms.
 *
 *
 * Any link rel="tag" is a start. The plaintext content of such a tag is
 * searched for as a term.
 *
 * both <a href rel='tag' > and <link rel="tag"> are good for me.
 *
 * @TODO this still needs to be expanded with real-world cases
 */
function taxonomy_import_html($profile, &$node, $datadoc = NULL) {
  $node->taxonomy = (! empty($node->taxonomy) && is_array($node->taxonomy)) ? $node->taxonomy : array();

  $active_vocabs = taxonomy_get_vocabularies($node->type);
  if (!$active_vocabs) return;

  $freetag_vocab = $profile['freetag_vocab'];

  if ($freetag_vocab && !empty($node->keywords)) {
    $node->taxonomy['tags'][$freetag_vocab] = $node->keywords;
  }
  //TODO support dc:subject also


  // Scan to see if any allow freetagging. After that it's guesswork which one to target. The one with the lowest number;
  $prime_vocab = 0;
  foreach ($active_vocabs as $vocabulary) {
    if ($vocabulary->tags) {
      $prime_vocabulary = $vocabulary;
      break;
    }
  }

  // Translate links with rel=tag into taxonomy terms
  // TODO review and rewrite with some more control form the profile settings.
  // Need to try on some actual use-cases that INCLUDE this info in the first case.
  $relationships = xml_query($datadoc, './/*[@rel]');
  foreach ($relationships as $link) {
    if (empty($link)) continue;
    $reltype = xml_getattribute($link, 'rel');
    // rels can be multiple - like classes. Split on space
    $reltypes = explode(' ', xml_getAttribute($link, 'rel'));
    $rellink = xml_getattribute($link, 'href');
    $label = trim(xml_textcontent($link));
    // Microformats may put their value into a 'title' attribute instead
    if (empty($label)) {
      $label = xml_getAttribute($link, 'title');
    }

    if (!empty($label)) {
      foreach ($reltypes as $reltype) {
        if ($reltype == 'tag') {
          // Some of this magic should probably shift into absorb_metas()
          // Still thinking of the best way to encode tags into the raw HTML

          if (strstr($label, ":")) {
            // allow an extended format for this value
            // to support freetext vocab additions
            // <a rel='tag'>Author:Joe Brown</a> will create a term in the 'Author' vocab called "Joe Brown".
            debug("Splitting rel link '$label' up to make it a vocab term entry", 2);
            $vocab_term = split(":", $label);
            $vocab = $vocab_term[0];
            $label = $vocab_term[1];
            $vocabulary = taxonomy_get_vocabulary_by_name($vocab);
            if ($vocabulary) {
              $node->taxonomy['tags'][$vocabulary->vid] .= ",". $label;
            }
          }

          // Match against existing terms
          $terms = taxonomy_get_term_by_name($label);
          // Allow an optional 'S' on the end of terms when looking for a match. Just to be flexible.
          $terms = array_merge($terms, taxonomy_get_term_by_name($label ."s"));

          if (!is_array($node->taxonomy)) {
            $node->taxonomy = array();
          }
          if ($terms) {
            foreach ($terms as $term) {
              // If we did successfully identify the vocab earlier, filter on that. Otherwise let anything go
              if ($vocabulary && ($term->vid != $vocabulary->vid)) continue;
              $node->taxonomy[$term->tid] = $term;
            }
          }
          else {
            // Couldn't retrieve it, can we add freetags?
            @$node->taxonomy['tags'][$prime_vocabulary->vid] .= ",". $label;
          }

        } // is a 'tag'
        import_html_absorb_properties($node, $reltype, $label);
      }  // inner rel tag type
    } // has value
  } // each rel

  // Tag this new content if the profile has a global tag set
  // May have been set during the form process.
  //
  // Note that if the global tag is from a freetaging vocab, we insert it as a string
  // but if it was from a select category, we insert it by ID.

  $cats = $profile['import_category'];
  if (is_array($cats)) {
    foreach ($cats as $term_id) {
      if ($term = taxonomy_get_term($term_id)) {
        // Be careful not to add terms that are invalid or recently deleted

        // $node->taxonomy contains either strings or IDs.
        // Figure it out and insert into the object accordingly
        // Mixing ids and strings confuses taxonomy submit otherwise
        $term_vocab = taxonomy_vocabulary_load($term->vid);
        if ($term_vocab->tags) {
          @$node->taxonomy['tags'][$term_vocab->vid] .= ', '. $term->name;
        }
        else {
          $node->taxonomy[$term_id] = $term;
        }
      }
      else {
        drupal_set_message("Tried to add the term $cat_id to the node - but it seems to be invalid. Maybe it was deleted. Check the import profile.", 'warning');
      }
    }
  }

}

/**
 * Implimentation of hook_import_html_node_merge()
 *
 * HOOK_import_html_node_merge gets called after a new node has been created,
 * and is being used to update a pre-existing one.
 *
 * A per-module way of blending new values over old ones - conflict resolution
 * and checking for duplicates.
 *
 * If the values are done with, unset them from the $old node so they don't get
 * inadvertantly copied by the bulk operation that follows.
 *
 * Taxonomy needs this because: If I am MERGING with a pre-existing node that
 * already has terms (such as when doing a re-import) then the node taxonomy
 * already has a bunch of identified terms that are likely to be duplicates. I
 * don't want to discard them (they may have been updated in the meantime) but
 * leaving the node with them set, and ALSO adding the freetagging list will
 * cause duplicate complaints. I need to investigate the existing terms and
 * remove them individually. Easiest way is to convert them into a flat list so
 * they get re-saved.
 *
 * taxonomy_preview_terms() didn't look like it will help.
 *
 * taxonomy_form_alter() seems to have the same problem. And solves it sorta.
 *
 * But not good enough for us without rewriting $node->taxonomy totally
 *
 * Taxonomy doesn't mind duplicates in the freetag string, so we will pull the
 * known terms out, just add them to the freetag string, and discard the oldies.
 *
 * It operates on both old and new by reference.
 */
function taxonomy_import_html_node_merge(&$old_node, &$new_node, $profile = array()) {
  foreach ($old_node->taxonomy as $tid => $term) {
    if (is_object($term)) {
      $term_vocab = taxonomy_vocabulary_load($term->vid);
      if ($term_vocab->tags) {
        unset($old_node->taxonomy[$tid]);
        if (! isset($new_node->taxonomy['tags'])) {
          $new_node->taxonomy['tags'] = array();
        }
        if (! isset($new_node->taxonomy['tags'][$term->vid])) {
          $new_node->taxonomy['tags'][$term->vid] = '';
        }
        $new_node->taxonomy['tags'][$term->vid] .= ', '. $term->name;
      }
    }
  }
}


function taxonomy_get_vocabulary_by_name($name) {
  $vs = taxonomy_get_vocabularies();
  foreach ($vs as $voc) {
    if ($voc->name == $name) return $voc;
  }
}
