<?php
// $Id: fast_gallery.cache.class.php,v 1.11.2.5 2010/03/15 18:38:08 rapsli Exp $ 

/**
 * @file
 * This class provides a very simple cache for the thumbnails, in case
 * Imagecache is not being used (or can't be used).
 *
 * @author Raphael Schär - www.schaerwebdesign.ch
 * @author Nicholas C. Yang - www.nyanginator.com
 */

class FastGalleryCache {
  static private $instance = null;

  /**
   * We are implementing a singleton pattern
   */
  private function __construct() {
  }

  public function getInstance() {
    if (is_null(self :: $instance)) {
      self :: $instance = new self;
    }
    return self :: $instance;
  }

  /**
   * Creates an image resource from a path. Supported filetypes are GIF, 
   * JPEG, and PNG.
   *
   * $param path
   *   Path to the image.
   */
  function imagecreatefromfile($path) {
    if (!file_exists($path)) {
      drupal_set_message(t('There is a problem with creating a thumbnail: Can\'t find file %image. Line %line in %file',
        array('%image' => $path, '%line' => __LINE__, '%file' => __FILE__)), 'error');
        return false;
    }
    $info = getimagesize($path);

    $types = array (
      IMAGETYPE_GIF => 'imagecreatefromgif',
      IMAGETYPE_JPEG => 'imagecreatefromjpeg',
      IMAGETYPE_PNG => 'imagecreatefrompng',
      
    );

    if (!$info || !$types[$info[2]] || !function_exists($types[$info[2]])) {
      return false;
    }

    return $types[$info[2]] ($path);
  }

  /**
   * Creates a thumb and copies it into the same folder with .thumb extension.
   *
   * @param name
   *   Name of the original image.
   * @param width
   *   Desired width of the thumbnail.
   * @param height
   *   Desired height of the thumbnail.
   */
  public function createthumb($name, $width, $height) {
    $name = utf8_decode($name);

    // Return without doing anything if the thumbnail already exists
    if (file_exists($name . '.thumb'))
      return true;

    // We're only supporting JPG, PNG, GIF
    $src_img = $this->imagecreatefromfile($name);
    if ($src_img == FALSE) {
      drupal_set_message('Internal cache failed to create thumbnail: ' . $name);
      return;
    }

    // New dimensions
    $width_orig = imagesx($src_img);
    $height_orig = imagesy($src_img);
    $ratio_orig = $width_orig / $height_orig;

    if ($width / $height > $ratio_orig) {
      $width = $height * $ratio_orig;
    } else {
      $height = $width / $ratio_orig;
    }

    // Resample
    $dst_img = imagecreatetruecolor($width, $height);
    imagecopyresampled($dst_img, $src_img, 0, 0, 0, 0, $width, $height, $width_orig, $height_orig);

    // Save out the thumbnail file as a JPEG
    imagejpeg($dst_img, $name . '.thumb');

    // Some cleanup
    imagedestroy($dst_img);
    imagedestroy($src_img);
  }

  /**
   * Removes all the thumbs.
   *
   * @param path
   *   Path of directory where thumbs are located.
   * @param recursive
   *   Specify whether to recurse through subdirectories.
   */
  public function flushThumbs($path = '', $recursive = TRUE) {
    if ($path == '') {
      $path = variable_get('fast_gallery_path', 'sites/default/files');
    }
    // Get all .thumb files from given path
    $files = glob($path . '*.thumb');

    // Delete the thumbs in this path, skip over directories (arrays)
    if (is_array($files)) {
      foreach ($files as $img) {
        if (!is_array($img))
          unlink($img);
      }
    }

    // Recurse through subdirectories if necessary
    if ($recursive) {
      $dirs = glob($path . '*', GLOB_MARK | GLOB_ONLYDIR);
      foreach ($dirs as $dir) {
        $this->flushThumbs($dir, TRUE);
      }
    }
  }
}