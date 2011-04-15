<?php
// $Id: default.storage.inc,v 1.9.2.9 2010/07/29 19:42:36 rapsli Exp $

/**
 * @file
 * This is the default storage engine. It's storing the files found in the
 * directory in it's on db structure.
 */

include_once('Istorage.php');

/**
 * This function MUST be implemented!!!
 * @return Istorage
 */
function fast_gallery_get_storage() {
  return new DefaultStorage();
}

/**
 * This is the default storage engine for fast gallery. It is mainly
 * responsible for providing images and storing images. The default
 * engine uses a very simple concept of just storing them in a seperate
 * table in the db.
 * The default engine is supposed to be easy to use, fast and stable.
 */
class DefaultStorage implements Istorage {


  /**
   * Returning a random image. This could be used for providing a block
   *
   * @param string $gallery
   *  the alias of a gallery to choose the image from
   * @return FGImage
   */
  public function getRandomImage() {
    $result = db_query("SELECT folder, filename FROM {fast_gallery_file} as f,
      {fast_gallery_hierarchy} AS h 
      WHERE f.foid = h.foid 
      ORDER BY RAND() LIMIT 0,1");

    while ($image = db_fetch_object($result)) {
      return new FGImage($image->folder .'/'. $image->filename);
    }
    return new FGImage('');
  }

  /**
   * Return all images that are stored on a given path
   *
   * @param $path String
   * @param $options array
   * @return array - an array of FGImages
   */
  public function getImages($path, $options=array()) {
    //incase we have a / at the end -> remove it.
    $arTmp = explode("/", $path);
    if ($arTmp[sizeof($arTmp)-1] == '') {
      array_pop($arTmp);
    }
    $folder = implode("/", $arTmp);
    $return = array();

    $foid = $this->getFoid($folder);
    
    //incase we want to display the subfolder first
    if (variable_get('fg_folder_first', FALSE) && $_GET['page'] < '1') {
      $return = array_merge($return, $this->getFolders($foid));
    }

    $sort_order = variable_get('fg_sort_order', 'filename');
    $sort_direction = variable_get('fg_sort_direction', 'asc');

    //fetch images
    $result = pager_query("SELECT filename, folder, fgf.foid FROM {fast_gallery_file} as fgf, {fast_gallery_hierarchy} as fgh
                     WHERE fgf.foid = fgh.foid 
                     AND fgh.folder = '%s' 
                     ORDER BY $sort_order $sort_direction", variable_get('fg_pager_amount', 20), 0, NULL, $folder);

    while ($item = db_fetch_array($result)) {
      if (file_exists($item['folder'] .'/'. $item['filename'])) { //we also have folders stored in that list of files, let's not display them
        $return[] = new FGImage($item['folder'] .'/'. $item['filename']);
      }
    }

    //incase we display the subfolders last
    if (!variable_get('fg_folder_first', FALSE)  && $_GET['page'] < '1')  {
      $return = array_merge($return, $this->getFolders($foid));
    }
    return $return;
  }

  private function getFoid($folder) {
    $foid = db_result(db_query("SELECT foid FROM {fast_gallery_hierarchy}
                          WHERE folder='%s' 
                          ORDER BY folder", array($folder)));
    return $foid;
  }

  /**
   * Get the subfolders of a given folder
   * @param int $foid
   * @return array
   */
  private function getFolders($foid) {
    $sort_order = variable_get('fg_sort_order', 'filename');
    $sort_direction = variable_get('fg_sort_direction', 'asc');

    switch ($sort_order) {
      default:
        $sort_order = 'folder';
        break;
    }

    $folders = array();
    $result = db_query("SELECT fgh.foid, fgh.folder FROM {fast_gallery_hierarchy} fgh
                     WHERE fgh.pid = %d 
                     ORDER BY $sort_order $sort_direction", array($foid));
    while ($folder = db_fetch_array($result)) {
      /*
       * $folder2 = db_fetch_array(db_query("SELECT * FROM {fast_gallery_file} 
                     WHERE foid=%d AND filename IN ('folder.JPG') LIMIT 0,1", $folder['foid']));
      if (!empty($folder2['filename'])) {
        $path = $folder['folder'] . '/' . $folder2['filename'];
        $folders[] = new FGImage($path, array('dir' => TRUE));
      }
       */
      $folders[] = new FGImage($folder['folder'], array('dir' => TRUE));
    }
    return $folders;
  }

  /**
   * implementing the interface. Passing an array of
   * FGImages and save them into the db
   * @param array $arImages
   *  an array of FGImages
   *
   */
  public function storeImages($arImages) {
    global $user;
    static $first_run = TRUE;
    static $runid;
    static $folders = array();
    $runid = variable_get('fast_gallery_runid', 0);

    //TODO: This makes the APP slow -> Rebuilding the whole
    // Gallery every time!
    if ($first_run) {
      cache_clear_all(NULL, 'cache_fast_gallery');
      $first_run = FALSE;
      variable_set('fast_gallery_runid', ++$runid);

      db_query("TRUNCATE {fast_gallery_file}");
      db_query("TRUNCATE {fast_gallery_hierarchy}");

      $folders[$arImages[0]->getFolder()] = $this->storeHierarchy($arImages[0]);

    }
    foreach ($arImages as $image) {
      /*if ($image->isDir()) {
        continue;
      }*/

      if (!array_key_exists($image->folder, $folders)) {
        $foid = $this->storeHierarchy($image);
        $folders[$image->getFolder()] = $foid;
      }

      $foid = $folders[$image->getFolder()];

      $update = db_result(db_query("SELECT foid FROM {fast_gallery_file} WHERE foid=%d AND filename='%s'",
      array($foid, $image->getName())));

      $dbObject = array(
        'foid' => $foid,
        'filename' => $image->getName(),
        'runid' => $runid,
        'filecreated' => $image->getCreationTimestamp()
      );
      if ($update) {
        drupal_write_record('fast_gallery_file', $dbObject, array('foid', 'filename'));
      }
      else {
        drupal_write_record('fast_gallery_file', $dbObject);
      }

    }
    cache_clear_all('*', 'cache_fast_gallery');
  }

  /**
   * (non-PHPdoc)
   * @see sites/all/modules/fast_gallery/storageengine/Istorage#clearDb()
   */
  public function clearDb() {
    db_query("TRUNCATE TABLE fast_gallery_hierarchy");
    db_query("TRUNCATE TABLE fast_gallery_file");
    cache_clear_all(NULL, 'cache_fast_gallery');
  }

  /**
   * (non-PHPdoc)
   * @see sites/all/modules/fast_gallery/storageengine/Istorage#removeDeletedFiles()
   */
  public function removeDeletedFiles() {
    db_query("DELETE FROM {fast_gallery_file} WHERE runid < %d", array(variable_get('fast_gallery_runid', 0)));
  }

  /**
   * In order to retrieve the hierarchy we need to store this information
   * in a special table
   * @param FGImage $image
   * @return unknown_type
   */
  private function storeHierarchy($image) {
    static $folders = array();

    //a little cache to reduce load on db -> we only have to run this for one image per folder
    if (!in_array($image->getFolder(), $folders)) {
      $folder = db_result(db_query("SELECT folder AS c FROM {fast_gallery_hierarchy}
              WHERE folder = '%s'", array($image->getFolder())));

      if (!$folder) { //incase we don't have this folder in our db
        $dbObject['folder'] = $image->getFolder();
        $dbObject['pid'] = db_result(db_query("SELECT foid FROM {fast_gallery_hierarchy}
                            WHERE folder = '%s'", array($image->getParent())));
        if (!$dbObject['pid']) {
          $dbObject['pid'] = 0;
        }
        drupal_write_record('fast_gallery_hierarchy', $dbObject);

        //TODO: needs to be checked!!! needs to return the foid, so that we can make
        //the correct entry into fast_gallery
        $foid = db_result(db_query("SELECT MAX(foid) FROM {fast_gallery_hierarchy}"));
        $folders[$foid] = $image->getFolder();
        return $foid;
      }
    }
    $ar = array_flip($folders);
    return $ar[$image->getFolder()];
  }



}