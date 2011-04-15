<?php
// $Id: fast_gallery.class.php,v 1.33.2.7 2010/07/23 17:30:48 rapsli Exp $ 

/**
 * @file
 * This is a helper class, the actual controller. It is the actual controller
 * of the application being the connection between the drupal API and the
 * storage engine.
 *
 * It's doing the most basic stuff that are the same overall the storage engines
 *
 * @author Raphael Sch�r - www.schaerwebdesign.ch
 */

include_once('FGImage.class.php');

/**
 * The Fast Gallery Controller class
 */
class FastGallery {
  private static $instance = null;

  /**
   * We are implementing a singleton pattern
   */
  private function __construct() {
  }

  /**
   *
   * @return FastGallery
   */
  public function getInstance() {
    if (is_null(self :: $instance)) {
      self :: $instance = new self;
    }
    return self :: $instance;
  }

  /**
   * Get a random image from any gallery
   * @return FGImage
   */
  public function getRandomImage() {
    $storage = $this->getStorageEngine();
    return $storage->getRandomImage();
  }

  /**
   * Checks for gallery additions/deletions only. Leaves existing files alone.
   */
  public function rescanGallery() {
    $arGalleries = variable_get('fg_galleries', array());
    $storage = $this->getStorageEngine();

    foreach ($arGalleries as $gallery) {
      $path = utf8_decode($gallery['fg_path']);
      if (!is_dir($path)) {
        watchdog('fast_gallery', 'No gallery path specified! Do it at !link', array('!link' => l('admin/settings/fast_gallery', 'admin/config/fast_gallery')));
      }
      // Get current file list hierarchy
      $files = $this->exploreDir($path, TRUE);

      // Process the files
      $FgImgContainer = array();
      $this->processFiles($files, $FgImgContainer);

      $storage->storeImages($FgImgContainer);
    }
    $storage->removeDeletedFiles();
    fast_gallery_flush_caches();
  }

  /**
   * Return the storage engine. We first find out which storage engine is
   * used, then we load specified file and then we call the function that
   * needs to be in the storage engine file "fast_gallery_get_storage,
   * which then returns the correct storage engine
   * @return Istorage
   */
  public function getStorageEngine() {
    $storage_engine_info = variable_get('fg_storage_engine', array());

    //we fetch the file with the storage engine
    include_once($storage_engine_info['path'] . '/' . $storage_engine_info['file']);
    return fast_gallery_get_storage();//and call the function to return it.

  }

  /**
   * Process the images (which are right now only a path) and
   * make nice FGImages out of them so that they can be
   * passed to the storage engine
   *
   * @param ar_files
   *   Array of files, as returned by exploreDir()
   * @param fGImagesContainer
   *   Array that collects the created FGImages objects
   */
  private function processFiles($ar_files, &$fGImagesContainer) {
    foreach ($ar_files as $key => $value) {
      // If we found a folder, recurse through it
      if (is_array($value)) {
        $this->processFiles($value, $fGImagesContainer);
      }
      else {
    // Handle files with special characters.
        $value_slash = str_replace('\\', '/', utf8_encode($value));
        $fGImagesContainer[] = new FGImage($value_slash);
    }

      //we don't care about empty arrays
      if (is_array($value) && count($value) < 1) {
        continue;
  }
    }
    //return $fgImagesContainer;
  }

  /**
   * clearing the db -> removing all entries from the db
   *
   */
  public function clearDb() {
    $storage = $this->getStorageEngine();
    $storage->clearDb();
    fast_gallery_flush_caches();
  }


  /**
   * Get all images in given directory.
   *
   * @param path
   *   Absolute path of the directory
   * @param recursive
   *   Specify whether to recurse through subdirectories.
   * @return
   *   Array of arrays of image files. Each array element corresponds to
   *   an image type. If recursive is on, returns an array tree hierarchy.
   */
  private function exploreDir($path = '', $recursive = FALSE) {
    $fg_galleries = variable_get('fg_storage_engine', array());

    // get all the files that are supported by the gallery
    // or take some default values
    $exts = $fg_galleries['supported_files'];

    if (count($exts) < 1) {
      $exts = array (
          'jpg',
          'jpeg',
          'png',
          'gif',
          'bmp',
    /*'flv',
     'mov',
     'wmv',
     'asx',
     'swf',
     'pdf',*/
      );
    }
    // Get all image files of each file type
    $files = array ();
    foreach ($exts as $ext) {

      $pattern = sql_regcase($path . '*.' . $ext);
      $f = glob($pattern);
      if (count($f) > 0 && $f != '') {
        $files[] = $f;
      }
    }

    // Recurse through subdirectories if necessary
    if ($recursive) {
      $dirs = glob($path . '*', GLOB_MARK | GLOB_ONLYDIR);
      if (is_array($dirs)) {
        foreach ($dirs as $dir) {
          if ($dir != '') {
            $files[] = $dir;
          }
          $files[] = $this->exploreDir($dir, TRUE);
        }
      }
    }
    return $files;
  }

  /**
   * Building the array for the breadcrumbs
   * @return array
   *  and array containing breadcrumb items
   */
  public function buildBreadCrumbs() {
    $bc = array();
    $path = '';
    
    $args = arg();
    $settings = variable_get('fg_galleries', array());
    
    foreach ($settings as $gallery) {
      if ($gallery['fg_alias'] == $args[0]) {
        unset($args[0]);
        array_unshift($args, $gallery['fg_title']);
        $alias_first = $gallery['fg_alias'];
      }
    }
    
    foreach ($args as $key => $item) {
      if ($key == 0) {
        $path .= $alias_first . '/';
      }
      else {
        $path .= $item . '/';
      }
      $bc[] = l($item, $path);
    }
    return $bc;
  }

}