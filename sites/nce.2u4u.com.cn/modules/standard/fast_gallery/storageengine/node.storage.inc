<?php
// $Id: node.storage.inc,v 1.3.2.2 2010/03/15 18:38:08 rapsli Exp $

/**
 * @file
 * This is the dummy implementation of Istorage for implementing a node storage
 */

include_once('Istorage.php');

/**
 * This function MUST be implemented!!!
 * @return Istorage
 */
function fast_gallery_get_storage() {
  return new DefaultStorage();
}


class NodeStorage implements Istorage {
  /**
   * Return all images that are stored on a given path
   * 
   * @param $path String
   * @return array - an array of FGImages
   */
  public function getImages($path) {
    
  }
  
  /**
   * 
   * @param array $arImages
   *  an array of FGImages
   *  
   */
  public function storeImages($arImages) {
    
  }
  
  
  /**
   * removing all files from the storage
   */
  public function clearDb() {
    
  }
  
  
  /**
   * Incase a file is being deleted from the file system
   * we need to ensure that we deleted it from the db aswell
   * so that db and filesystem stays synced
   */
  public function removeDeletedFiles() {
    
  }

  /**
   * Fetch a random image from the storage, which will then be displayed in
   * a block
   * @return FGImage
   */
  public function getRandomImage() {
    
  }
}