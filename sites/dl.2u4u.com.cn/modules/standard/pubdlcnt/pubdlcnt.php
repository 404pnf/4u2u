<?php
// $Id: 

/**
 * @file
 *
 * file download external script
 *
 * @ingroup pubdlcnt
 *
 * Usage:  pubdlcnt.php?file=http://server/path/file.ext
 *
 * Requirement: PHP5 - get_headers() function is used
 *              (The script works fine with PHP4 but better with PHP5)
 *
 * NOTE: we can not use variable_get() function from this external PHP program
 *	     since variable_get() depends on Drupal's internal global variable.
 *       So we need to directly access {variable} table of the Drupal databse 
 *       to obtain some module settings.
 *
 * Copyright 2009 Hideki Ito <hide@pixture.com> Pixture Inc.
 * Distributed under the GPL Licence.
 */

/**
 * Step-1: start Drupal's bootstrap to use drupal database
 *         and includes necessary drupal files
 */

$current_dir = getcwd();

// we need to change the current directory to the (drupal-root) directory
// in order to include some necessary files.
if (file_exists('../../../../includes/bootstrap.inc')) {
  // If this script is in the (drupal-root)/sites/(site)/modules/pubdlcnt directory
  chdir('../../../../'); // go to drupal root
}
else if (file_exists('../../includes/bootstrap.inc')) {
  // If this script is in the (drupal-root)/modules/pubdlcnt directory
  chdir('../../'); // go to drupal root
}
else {
  // Non standard location: you need to edit the line below so that chdir()
  // command change the directory to the drupal root directory of your server
  // using an absolute path.
  // First, please delete the line below and then edit the next line
  print "Error: Public Download Count module failed to work. The file pubdlcnt.php requires manual editing.\n";
  chdir('/absolute-path-to-drupal-root/'); // <---- edit this line!

  if (!file_exits('./includes/bootstrap.inc')) {
    // We can not locate the bootstrap.inc file, let's give up using the
    // script and just fetch the file
    header('Location: ' . $_GET['file']);
    exit;
  }
}
include_once './includes/bootstrap.inc';
// following two lines are needed for check_url() and valid_url() call
include_once './includes/common.inc';
include_once './modules/filter/filter.module';
// start Drupal bootstrap for accessing database
drupal_bootstrap(DRUPAL_BOOTSTRAP_DATABASE);
chdir($current_dir);

/**
 * Step-2: get file query value (URL of the actual file to be downloaded)
 */
$url = check_url($_GET['file']);
$nid = check_url($_GET['nid']);

if (!eregi("^(f|ht)tps?:\/\/.*", $url)) { // check if this is absolute URL 
  // if the URL is relative, then convert it to absolute
  $url = "http://" . $_SERVER['SERVER_NAME'] . $url;
}

/**
 * Step-3: check if the url is valid or not
 */
if (is_valid_file_url($url)) {
  /**
   * Step-4: update counter data (only if the URL is valid and file exists)
   */
  $filename = basename($url);
  pubdlcnt_update_counter($filename, $nid);
}

/**
 * Step-5: redirect to the original URL of the file
 */
header('Location: ' . $url);
exit;

/**
 * Function to check if the specified file URL is valid or not
 */
function is_valid_file_url($url) {
  // replace space characters in the URL with '%20' to support file name
  // with space characters
  $url = preg_replace('/\s/', '%20', $url);

  if (!valid_url($url, true)) {
    return false;
  }
  // URL end with slach (/) and no file name
  if (preg_match('/\/$/', $url)) {
    return false;
  }
  // in case of FTP, we just return TRUE (the file exists)
  if (preg_match('/ftps?:\/\/.*/i', $url)) {
    return true;
  }

  // extract file name and extention
  $filename = basename($url);
  $extension = explode(".", $filename);
  // file name does not have extension
  if (($num = count($extension)) <= 1) {
    return false;
  }
  $ext = $extension[$num - 1];

  // get valid extensions settings from Drupal
  $result = db_query("SELECT value FROM {variable} 
						WHERE name = 'pubdlcnt_valid_extensions'");
  $valid_extensions = unserialize(db_result($result));
  if (!empty($valid_extensions)) {
    // check if the extension is a valid extension or not (case insensitive)
    $s_valid_extensions = strtolower($valid_extensions);
    $s_ext = strtolower($ext);
    $s_valid_ext_array = explode(" ", $s_valid_extensions);
    if (!in_array($s_ext, $s_valid_ext_array)) {
      return false;
    }
  }
  
  if (!url_exists($url)) {
    return false;
  }
  return true; // it seems that the file URL is valid
}

/**
 * Function to check if the specified file URL really exists or not
 */
function url_exists($url) {
  $a_url = parse_url($url);
  if (!isset($a_url['port'])) $a_url['port'] = 80;
  $errno = 0;
  $errstr = '';
  $timeout = 30;
  if (isset($a_url['host']) && $a_url['host'] != gethostbyname($a_url['host'])) {
    $fid = @fsockopen($a_url['host'], $a_url['port'], $errno, $errstr, $timeout);
    if (!$fid) return false;
    $page = isset($a_url['path']) ? $a_url['path'] : '';
    $page .= isset($a_url['query']) ? '?' . $a_url['query'] : '';
    fputs($fid, 'HEAD ' . $page . ' HTTP/1.0' . "\r\n" . 'HOST: ' 
        . $a_url['host'] . "\r\n\r\n");
    $head = fread($fid, 4096);
    $head = substr($head, 0, strpos($head, 'Connection: close'));
    fclose($fid);
    // Here are popular status code back from the server
    //
    // URL exits                  'HTTP/1.1 200 OK'
    // URL exits (but redirected) 'HTTP/1.1 302 Found'
    // URL does not exits         'HTTP/1.1 404 Not Found'
    // Can not access URL         'HTTP/1.1 403 Forbidden'
    // Can not access server      'HTTP/1.1 500 Internal Server Error
    // 
    // So we return true only when status 200 or 302
    if (preg_match('#^HTTP/.*\s+[200|302]+\s#i', $head)) {
      return $pos !== false;
    }
  }
  return false;
}

/**
 * Function to update the data base with new counter value
 */
function pubdlcnt_update_counter($name, $nid) {
  $count = 1;
  $name = db_escape_string($name);	// security purpose

  if (empty($nid)) { // node nid is invalid
    return;
  }
  // today(00:00:00AM) in Unix time
  $today = mktime(0, 0, 0, date("m"), date("d"), date("Y"));
  // convert to datettime format
  $mysqldate = date("Y-m-d H:i:s", $today);

  $result = db_query("SELECT * FROM {pubdlcnt} WHERE name='%s' AND date='%s'", 
                      $name, $mysqldate);
  if ($rec = db_fetch_object($result)) {
    $count = $rec->count + 1;
    // update an existing record
    db_query("UPDATE {pubdlcnt} SET count=%d WHERE name='%s' AND date='%s'", 
			$count, $name, $mysqldate);
  }
  else {
    // insert a new record
    db_query("INSERT INTO {pubdlcnt} (name, nid, date, count) VALUES ('%s', %d, '%s', %d)", 
			$name, $nid, $mysqldate, $count);
  }
}
?>
