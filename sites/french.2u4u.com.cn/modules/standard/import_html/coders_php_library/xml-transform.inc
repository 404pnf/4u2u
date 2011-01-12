<?php
// $Id: xml-transform.inc,v 1.33.2.6 2009/07/01 02:40:56 dman Exp $
/**
 * @file
 * Utility for formatting XML files using XSL. 
 *
 * A bunch of stubs compliant with the different XML implimentations in PHP
 * versions 4 & 5. It's pretty rag-tag as different functions were added in
 * different illogical ways over time. Should probably be split off into two
 * discreet libraries for the versions.
 * 
 * And bog off Drupal code conventions! I'm using the DOM, mixed camelCase is
 * correct.
 * 
 * @package coders
 * @author Dan Morrison http://coders.co.nz/
 */

/*
 * For debug routines, parameter passing and some output formatting
 */
if (defined("DEBUGLEVEL")) {
  module_load_include('inc', 'xml-transform', 'debug');
}
// and may conditionally call file-routines and tidy-functions.inc
// but only when this library is actually used.
//  module_load_include('inc', 'xml-transform', 'ile-routines');

/**
 * Load whichever XML support is available
 */
function init_xsl() {
  // Just loading this lib means we really want to have XML
  // OK, support both old & new PHP library ways of doing things ...
  if (!extension_loaded('xsl') && !extension_loaded('xslt')) {
    debug("Need to try and dynamically load XSL extension. Please do this properly on the server to avoid this message.");
    if (!@dl('xslt.so')&&!@dl('php_xslt.dll')&&!@dl('php_xsl.dll')) {
      trigger_error("No XSL library support at all on this server!" , E_USER_ERROR );
      return FALSE;
    }
    debug("Ready to use XSL on the server", 2);
  }
  return TRUE;
}


/**
 * Try to load an xml doc from file, 
 *
 * Running tidy over the source first to override most parsing 
 * problems before they happen.
 * @parameter string Source filepath or URL
 * @parameter $do_tidy bool Whether to pre-process with HTMLTidy before parsing - ONLY do this with suspect HTML inout, not other XML sources.
 * @returns xmldoc
 */
function parse_in_xml_file($xmlfile, $do_tidy = 0) {
  module_load_include('inc', 'import_html', 'coders_php_library/file-routines');

  if (! file_exists($xmlfile)) {
    trigger_error("File '$xmlfile' not found, cannot load XML source.", E_USER_WARNING);
    return FALSE;
  }

  // Almost no content out there can be trusted to be valid :-(
  // I guess I'll tidy it myself before I attempt to parse it.
  if ($do_tidy) {
    module_load_include('inc', 'import_html', 'coders_php_library/tidy-functions');
    if (! extension_loaded( "tidy" ) ) {
      import_html_debug("Doing tidy via commandline");
      // No tidy module available. 
      // Old-school tidy must be run directly on the file, so do this first
      $xmlsource = xml_tidy_file($xmlfile);
    } 
    else {
      import_html_debug("Doing tidy on string from file $xmlfile using extension");
      $xmlsource = file_get_contents($xmlfile);
      $xmlsource = xml_tidy_string( $xmlsource );
    }

    // Also Need to remove any php tags that may have had (they look like XML processing instructions)
    $xmlsource = tidy_strip_php($xmlsource);
    
    #import_html_debug_code("File loaded, tidied, stripped ?php tags", $xmlsource);
    if (function_exists('import_html_variable') && import_html_variable('debug_level')) {
      file_put_contents($xmlfile .'.tidied.html', $xmlsource);
    }
  }
  else {
    $xmlsource = file_get_contents($xmlfile);
  }

  // non-utf8 characters are still let through as 'valid' but actually fail later in parsing.
  if (function_exists('charset_decode_utf_8')) { 
    $data = charset_decode_utf_8($xmlsource);
  }


  if (! trim($xmlsource)) { 
    trigger_error("Failed to parse contents of '$xmlfile' ", E_USER_WARNING);
    return;
  }
  else { 
    import_html_debug("Retrieved source of '%xmlfile' OK, it's %length characters", array('%xmlfile' => $xmlfile, '%length' => strlen($xmlsource)), WATCHDOG_DEBUG);
  }
  #import_html_debug_code("After loading XML text", $xmlsource);

  // If we force the source into the strict namespace, the XSL transformations 
  // (also in that namespace) SHOULD not litter the output with unwanted xmlns tags. 
  // so lets try and ensure the document knows that it's the right ns
  // $namespaceuri = "http://www.w3.org/TR/REC-html40";
  $namespaceuri = "http://www.w3.org/1999/xhtml"; // All XSL output should be this also, ok?

  if ( extension_loaded( "dom" )) {
    ///////////
    // PHP 5 //
    $xmldoc = new domdocument; // DOM PHP5 version
    debug("Using PHP5 DOM extension to process XML", 4);
 
    if (! $xmldoc->loadxml($xmlsource) ) {
      // Only complain if it was tidied and still failed. We expect failures on untidy input
      if ($do_tidy) {
        trigger_error("Failed to parse in xml source. [$xmlfile]", E_USER_WARNING);
        import_html_debug_code("Failed to parse XML input, even after tidying! Error XML source:", $xmlsource);
      }
      else {
        import_html_debug_code("Failed to parse XML input, but that's OK, we can try to tidy it next. Error XML source:", $xmlsource);
      }
      import_html_debug("Had XML trouble with the document '$xmlfile' ", array(), WATCHDOG_ERROR);

      return FALSE;
    }

    // Some files need to know where they came from (XSL includes)
    $xmldoc->documenturi = $xmlfile;
    
    // How to add namespaces in PHP5?

    #import_html_debug_code("XML source $xmlfile successfully loaded as an XML doc.", $xmldoc->savexml());
    return $xmldoc;
  } 
  else {
    trigger_error("No known DOM XML support on this server at all - can't really do anything! We need to enable php module dom or domxml to parse web pages nicely");
    return FALSE;
  }
}

function debug_xml_source($text) {
    return "<textarea rows='40' cols='80' wrap='none'>$text</textarea>" ;
}


/**
 * Version-safe string->xmldoc parser.
 * Convert a String to a DOM, via PHP4 or 5.
 * @parameter xmlsource $string Source XML
 * @parameter $do_tidy bool ONLY run HTMLTidy on HTML input, not once you already have XML source,
 * @returns xmldoc, or NULL if parse failed
 */
function parse_in_xml_string($xmlsource, $do_tidy = 0) {
  if ($do_tidy) {
    module_load_include('inc', 'xml-transform', 'idy-functions');
    $xmlsource = xml_tidy_string($xmlsource);
  }
  
  // Entities get resolved down into bytecode every time I run a XSL process. 
  // Plump them back up into numerics again.
  // Or headaches ensue. Again.
  $xmlsource = charset_decode_utf_8($xmlsource);

  init_xsl();
  if ( extension_loaded( "dom" )) {
    ///////////
    // PHP 5 //
    $xmldoc = new domdocument;
    if ($xmldoc->loadXML($xmlsource)) {
      return $xmldoc;
    }
    return NULL;
    trigger_error('Problem parsing XML String'); 
  } 
  else {
    trigger_error("No known DOM XML support on this server at all - can't really do anything! We need to enable php module dom or domxml to parse web pages nicely");
    return FALSE;
  }
}


/**
 * Do the actual conversion between XML+XSL
 *
 * Input and output are full DOM objects in PHP5
 * We return the result STRING, as that's what 
 * the process gives us :-/ 
 * Need to parse it back in again for pipelining.
 *
 * Painfully, the entire library support changed between PHP4 & 5.
 * We need to see if it's the "xsl" or the "xslt" library that's in use!
 *
 * @param domdocument or string $xmldoc 
 * @param domdocument or string $xsldoc . If it uses includes, the xsl must have
 * had its documenturi set correctly prior to this, but it can be set in the
 * parameters also. This may be mandatory for php4?
 * @param array $parameters To be passed into the xslt_process()
 * @returns string The result.
 */
function xmldoc_plus_xsldoc($xmldoc, $xsldoc, $parameters) {
  // OK, support both old & new PHP library ways of doing things ...
  init_xsl();

  if (empty($parameters['xsl_path'])) {
    trigger_error("xmldoc_plus_xsldoc was called without the xsl_path parameter set. This makes it hard to do relative XSL includes.", E_USER_NOTICE);
  }

  if (extension_loaded("xsl")) {
    //////////
    // PHP5 //
    import_html_debug("Doing XSL using PHP5 xsl module. XSL base should be %xsl_path ", array('%xsl_path' => $parameters['xsl_path']), WATCHDOG_DEBUG);
    $xsltproc = new XSLTProcessor;

    if ( $parameters['xsl_path']) $xsldoc->documenturi = $parameters['xsl_path'];
   
    $xsltproc->importStyleSheet($xsldoc); // attach the xsl rules
    // Set parameters when defined
    if ($parameters) {
       foreach ($parameters as $param => $value) {
         $xsltproc->setParameter("", $param, $value);
       }
    }
    $out = $xsltproc->transformtoxml($xmldoc);
    // I just CAN'T trust XML not to have squashed the entities into bytecodes.
    // Expand them before returning or I can never trust that my result here is actually valid to put in anywhere else again.
    return charset_decode_utf_8($out);
  }
}

function xslt_error_handler($handler, $errno, $level, $info) {
  // for now, let's just see the arguments
  debug_pre(func_get_args());
}

/**
 * A version safe way to make an XML doc from a filename
 */
function load_xml_from_file($xmlfile) {
  $xmldoc = new domdocument('1.0');
  return 
    is_callable(array($xmldoc, "load")) 
    ? $xmldoc->load($xmlfile) // PHP5
    : $xmldoc = domxml_open_file($xmlfile) //PHP4
  ;
}

/**
 * PHP directives can make it through and validate OK,
 * but confuse the hell out of the XML DOM it would seem
 * I'll have to discard them here.
 */
function tidy_strip_php($source) {
  return preg_replace('/<\?.*?\?>/sS', "", $source, -1);
}


/**
 * Returns the XML as a string from a document object.
 * Due to total differences between 4&5, this func combines
 *     dump_mem() with savexml()
 * @param $xmlnode to be dumped
 * @param $innerXML BOOL discard the wrapper element, only return the contents
 */
function xml_toString($xmlnode, $innerxml = FALSE) {
  if (!$xmlnode) return '';
  if (!is_object($xmlnode)) {
    import_html_debug_code("Problem extracting string from what should have been a DOM node. ", $xmlnode, WATCHDOG_ERROR); 
    return '';
  }
  if (extension_loaded("xsl")) {
    # debug("Dumping XML to string using PHP5 xsl module", 4);
    $xmldoc = ($xmlnode->ownerDocument) ? $xmlnode->ownerDocument : $xmlnode;
    $out = '';
    if ($innerxml) {
      foreach ($xmlnode->childNodes as $child) {
        $out .= $xmldoc->savexml($child);
      }
      // I just CAN'T trust XML not to have squashed the entities into bytecodes.
      // Expand them before returning or I can never trust that my result here is actually valid to put in anywhere else again.
      return charset_decode_utf_8($out);
    }
    return charset_decode_utf_8($xmldoc->savexml($xmlnode));
  }
  if (extension_loaded("xslt")) {
    # debug("Dumping XML to string using PHP4 xslt module", 4);
    $xmldoc = ($xmlnode->owner_document()) ? $xmlnode->owner_document() : $xmlnode;
    return ($xmlnode->node_type() == XML_DOCUMENT_NODE ) ? $xmldoc->dump_mem(TRUE) : xml_dump_child_nodes($xmlnode);
  }
}

function xml_dump_child_nodes($node) {
   $owner_document = $node->owner_document();
   $children = $node->child_nodes();
   $total_children = count($children);
   for ($i = 0; $i < $total_children; $i++) {
     $cur_child_node = $children[$i];
     $output .= $owner_document->dump_node($cur_child_node);
   }
   return $output;
}

/**
 * Tedious PHP version-safe method
 * Optionally just return the first one.
 * Encapsulated here so I don't have to think about nodelist item(0) vs array[0]
 */
function xml_getElementsByTagName($xmldoc, $tagname, $just_one=FALSE) {
  $func = (extension_loaded('xsl'))?'getElementsByTagName':'get_elements_by_tagname';
  $result = $xmldoc->$func($tagname);
  if ($just_one) { 
    foreach ($result as $element) return $element; 
  }
  return $result;
}

/**
 * Tedious PHP version-safe method
 * Adapted to try an attribute search as well, if xml:id is not working.
 * A document id element is not neccesarily the XML DOM ID handle, unless 
 * some special hoops are jumped through. 
 * Works when handed either a node or the whole document
 */
function xml_getElementById($xmlnode, $id) {
  $xmldoc = xml_getOwnerDocument($xmlnode);
  
  $element = (extension_loaded('xsl'))
    ? $xmldoc->getElementById($id) 
    : $xmldoc->get_element_by_id($id);

  if ($element)
    return $element;

  debug("lookup for xml:ID $id failed, doing query instead", 4);
  // For occult reasons, http://blog.bitflux.ch/wiki/GetElementById_Pitfalls 
  // the above may fail when the below may work : (100+ times slower)
  // http://php5.bitflux.org/xmlonspeed/slide_20.php

  if (extension_loaded('xsl')) { // PHP5
    $xp = new DomXPath($xmldoc);
    $res = $xp->query(".//*[@id = '$id']", $xmlnode);
    return $res->item(0);
  }
}  

/**
 * Version-safe, and allows a document's owner to be itself, to be nice.
 */
function xml_getOwnerDocument($xmlnode) {
  return (extension_loaded('xsl')) ? 
    ( ($xmlnode->nodeType == XML_DOCUMENT_NODE ) ? $xmlnode : $xmlnode->ownerDocument) 
    : $xmlnode->owner_document(); // ...don't ask.
}

function xml_query($xmlnode, $query) {
  if (extension_loaded('xsl')) { // PHP5
    $xp = new DomXPath(xml_getOwnerDocument($xmlnode));
    return $xp->query($query, $xmlnode);
  }
}

/**
 * PHP version-safe implimentation of element->toString;
 */
function xml_textContent($xmlnode) {
  if (!is_object($xmlnode)) {
    debug("Null node to get XML text from. Returning empty string.", 5);
    return '';
  }
  $text = (extension_loaded('xsl')) ? $xmlnode->textContent : $xmlnode->get_content();
  // I just CAN'T trust XML not to have squashed the entities into bytecodes.
  // Expand them before returning or I can never trust that my result here is actually valid to put in anywhere else again.
  return charset_decode_utf_8($text);
}

/**
 * Tedious PHP version-safe method
 */
function xml_getAttribute($xmlnode, $attname) {
  if (!is_object($xmlnode)) {
    debug("Invalid Parameter, null node", 1);
    return '';
  }
  $func = (extension_loaded('xsl')) ? 'getAttribute' : 'get_attribute';
  return $xmlnode->$func($attname);
}




/**
 * Find element by tagname, return its content.
 */
function xml_get_element_content($xmldoc, $tagname) {
  $tags = $xmldoc->getElementsByTagName($tagname);
  foreach ($tags as $tag) {
    return xml_textContent($tag);
  }
  // Note this just breaks the loop on the first item. 
  // foreach just happens to work.
  debug("No $tagname tag in parsed data");
}
