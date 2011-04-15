<?php
// $Id: Istorage.php,v 1.5.2.3 2010/05/03 06:01:27 rapsli Exp $

Interface Istorage {
  
  /**
   * Return all images that are stored on a given path
   * 
   * @param $path String
   * @param $options array
   * @return array - an array of FGImages
   */
  public function getImages($path, $options=array());
  
  /**
   * 
   * @param array $arImages
   *  an array of FGImages
   *  
   */
  public function storeImages($arImages);
  
  
  /**
   * removing all files from the storage
   */
  public function clearDb();
  
  
  /**
   * Incase a file is being deleted from the file system
   * we need to ensure that we deleted it from the db aswell
   * so that db and filesystem stays synced
   */
  public function removeDeletedFiles();

  /**
   * Fetch a random image from the storage, which will then be displayed in
   * a block
   * @return FGImage
   */
  public function getRandomImage();
  
}