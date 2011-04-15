<?php
// $Id: FGImage.class.php,v 1.6.2.9 2010/07/29 19:42:36 rapsli Exp $

/**
 *
 * @author rschaer
 *
 */


class FGImage {
  //$fid
  public $path, $name, $folder, $parent, $fid, $isDir, $filetype, $created, $iptc;

  /**
   * Constructor
   * @param $path
   *  The path to the image
   * @param $options
   *  an assoziative array containing some options. The following options are possible:
   *    - dir: can be true or false. If set to true the image behaves as a dir! Default is set to false
   */
  public function __construct($path, $options = array()) {
    $this->setPath($path);
    // Split up the Image Path, so we can work on it
    $arPath = explode('/', $path);
    if ($arPath[count($arPath)-1] == '') {
      unset($arPath[count($arPath)-1]);
      $options['dir'] = TRUE;
    }

    $this->setName($arPath);

    if (isset($options['dir'])) {
      $this->setIsDir($options['dir']);
    }
    else {
      $this->setIsDir(FALSE);
      $this->setFileType($arPath[count($arPath) - 1]);
    }

    $this->setFolder($arPath);
    $this->setParent($arPath);
    $this->setCreationTimestamp();

    // reading exif data and storing the them into the image
    if (function_exists('exif_read_data')) {
      if (file_get_mimetype($this->getPath()) == 'image/jpeg') {
        $this->iptc = $this->readIPTCTags($this->getPath(), array('object_name', 'title'));
      }
    }
  }

  /**
   * Render the html for displaying the image
   * @return string html
   */
  public function renderHtml() {
    $path = $this->getPath();
    if ($this->isDir) { //incase a dir we return a special image
      $folder_image = $this->getPath() . '/folder.jpg';
      if (file_exists($folder_image)) {
        return $this->renderThumb($folder_image);
      }
      else {
        $path = drupal_get_path('module', 'fast_gallery') . '/images/folder.png';
        return $this->renderThumb($path);
      }
      
      //return theme('image', array('path' => $path, 'title' => t('folder')));
    }
    else if($this->getFileType() == 'pdf') {
      $path = drupal_get_path('module', 'fast_gallery') . '/images/doc.screenshot.jpg';
      return $this->renderThumb($path);
    }
    else {
      return $this->renderThumb($path);
    }
  }

  /**
   * Render an image either using the internal cache or the drupal provided image
   * @param string $path
   * @return html
   */
  private function renderThumb($path) {
    if (module_exists('imagecache')) {

      if (variable_get('fast_gallery_ic_thumb', '') == '') {
        drupal_set_message(t('You haven\'t assigned any Imagecache preset!'), 'error');
      }
      return theme('imagecache', variable_get('fast_gallery_ic_thumb', ''), $path);
    }
    else {
      $cache = fast_gallery_get_cache();
      $cache->createthumb($path, 150, 100);
      return theme('image', $path . '.thumb', $this->getName(), $this->getName());
    }
  }

  public function createArrayVersion() {
    $image = array(
      'path' => $this->getPath(),
      'name' => $this->getName(),
      'folder' => $this->getFolder(),
      'filetyp' => $this->getFileType(),
      'created' => $this->getCreationTimestamp(),
      'title' => $this->getTitle(),
    );
    return $image;
  }
  /**
   * Given a path and index n, removes n number of elements from the end of
   * the path (delimited by '/').
   *
   * @param path_ar
   *   Path.
   * @param n
   *   Number of elements to remove from end of the path.
   */
  private function substractFromPath($path_ar, $n) {
    $path_ar = array_slice($path_ar, 0, - $n);
    return implode('/', $path_ar);
  }

  /**
   * Write IPTC Tags to a given file.
   *
   * Code looseley based on example from http://www.php.net/manual/en/function.iptcembed.php
   *
   * @param string $file - path to file
   * @return success: true, failure: false
   *
   */
  private function writeIPTCTags($file) {
    if (!function_exists('iptcembed'))
      return false;

    $iptc_new = '';
    $machinekey = array_flip($this->getHumanReadableIPTCkey());

    foreach ($this->iptc as $key => $val) {
      $len = strlen($val);
      $tag = substr($machinekey[$key], 2);
      $iptc_new .= chr(0x1c).chr(2).chr($tag) . (
	$len < 0x8000 ?
	chr($len>>8).chr(($len)&0xff) :
	chr(0x80).chr(0x04).chr(($len>>24)&0xff).chr(($len>>16)&0xff).chr(($len>>8)&0xff).chr(($len)&0xff) ) . $val;
    }

    $content = iptcembed($iptc_new, $file, 0);
    if (!($fp = fopen($file, "w"))) {
      return false;
    }
    if (!fwrite($fp, $content)) {
      fclose($fp);
      return false;
    }
    fclose($fp);
    return true;
  }

  /**
   * Read IPTC Tags from a given file. You can select which IPTC Key to read
   * 
   * @param string $file - path to file
   * @return Ambigous <string, multitype:, unknown>
   */
  private function readIPTCTags($file) {
    $humanReadableKey = $this->getHumanReadableIPTCkey();
    $size = GetImageSize ($file, $infoImage);
    $iptc = empty($infoImage["APP13"]) ? array() : iptcparse($infoImage["APP13"]);
    $arSmallIPTC = array();
    if (is_array($iptc)) {
      foreach ($iptc as $key => $value) {
        $resultTag = "";
        foreach ($value as $innerkey => $innervalue) {
          if (($innerkey+1) != count($value)) {
            $resultTag .= $innervalue . ", ";
          }
          else {
            $resultTag .= $innervalue;
          }
        }
        $arSmallIPTC[$humanReadableKey[$key]] = $resultTag;
      }
    }
    return $arSmallIPTC;
  }

  /**
   * Just some little helper function to get the iptc fields
   * @return array
   *
   */
  private function getHumanReadableIPTCkey() {
    return array(
      "2#202" => "object_data_preview_data",
      "2#201" => "object_data_preview_file_format_version",
      "2#200" => "object_data_preview_file_format",
      "2#154" => "audio_outcue",
      "2#153" => "audio_duration",
      "2#152" => "audio_sampling_resolution",
      "2#151" => "audio_sampling_rate",
      "2#150" => "audio_type",
      "2#135" => "language_identifier",
      "2#131" => "image_orientation",
      "2#130" => "image_type",
      "2#125" => "rasterized_caption",    
      "2#122" => "writer",
      "2#120" => "caption",
      "2#118" => "contact",
      "2#116" => "copyright_notice",
      "2#115" => "source",
      "2#110" => "credit",
      "2#105" => "headline",
      "2#103" => "original_transmission_reference",
      "2#101" => "country_name",
      "2#100" => "country_code",
      "2#095" => "state",
      "2#092" => "sublocation",
      "2#090" => "city",
      "2#085" => "by_line_title",
      "2#080" => "by_line",
      "2#075" => "object_cycle",
      "2#070" => "program_version",
      "2#065" => "originating_program",
      "2#063" => "digital_creation_time",
      "2#062" => "digital_creation_date",   
      "2#060" => "creation_time",
      "2#055" => "creation_date",
      "2#050" => "reference_number",
      "2#047" => "reference_date",
      "2#045" => "reference_service",
      "2#042" => "action_advised",
      "2#040" => "special_instruction",
      "2#038" => "expiration_time",
      "2#037" => "expiration_date",
      "2#035" => "release_time",
      "2#030" => "release_date",
      "2#027" => "content_location_name",
      "2#026" => "content_location_code",
      "2#025" => "keywords",
      "2#022" => "fixture_identifier",
      "2#020" => "supplemental_category", 
      "2#015" => "category",
      "2#010" => "subject_reference", 
      "2#010" => "urgency",
      "2#008" => "editorial_update",
      "2#007" => "edit_status",
      "2#005" => "object_name",
      "2#004" => "object_attribute_reference",
      "2#003" => "object_type_reference",
      "2#000" => "record_version"
      );
  }

  // All the accessor mehtods
  // -------------------------

  public function setCreationTimestamp($timestamp = 0) {
    if ($timestamp == 0) {
      if (!file_exists($this->getPath())) {
        drupal_set_message(t('The file %file doesn\'t exist. Line %line in %file',
        array('%line' => __LINE__, '%file' => __FILE__, '%file' => $this->getPath())), 'error');
        return false;
      }
      $this->created = filectime($this->getPath());
    }
    else {
      $this->created = $timestamp;
    }
  }

  public function getCreationTimestamp() {
    return $this->created;
  }

  public function setIsDir($isDir) {
    if ($isDir) {
      $this->isDir = TRUE;
    }
    else {
      $this->isDir = FALSE;
    }
  }

  public function isDir() {
    return $this->isDir;
  }

  public function getFid() {
    return $this->fid;
  }

  public function setFid($fid) {
    $this->fid = $fid;
  }

  public function getFolder() {
    return $this->folder;
  }

  public function setFolder($arPath) {
    if (!$this->isDir()) {
      $this->folder = $this->substractFromPath($arPath, 1);
    }
    else {
      $this->folder = implode("/", $arPath);
    }
  }

  public function getParent() {
    return $this->parent;
  }

  public function setParent($arPath) {
    if ($this->isDir()) {
      $this->parent = $this->substractFromPath($arPath, 1);
    }
    else {
      $this->parent = $this->substractFromPath($arPath, 2);
    }
  }
  /**
   * Getter method
   * @return string $path
   */
  public function getPath() {
    return $this->path;
  }

  /**
   * Setter method
   * @param $path string
   */
  public function setPath($path) {
    $this->path = $path;
  }

  /**
   * Getter method
   * @return string $path
   */
  public function getName() {
    return $this->name;
  }

  /**
   * Setter method
   * @param $name string
   */
  public function setName($arPath) {
    if (!$this->isDir()) {
      $this->name = $arPath[count($arPath)-1];
    }
  }

  /**
   * setter method
   * @param $path - the path of the file
   */
  public function setFileType($path) {
    $ending = explode(".", $path);
    $ending = $ending[count($ending) - 1];
    $this->filetype = $ending;
  }

  /**
   * getter method
   * @return string
   */
  public function getFileType() {
    return $this->filetype;
  }

  public function getIptc($key='') {
    if ($key == '<none>') { //incase display None
      return '';
    }
    if ($key != '') {
      if ($this->{iptc}[$key] == ''){ //incase there are no IPTC
					$nam=$this->getName();
					$pos=strrpos($nam, '.');
					return $pos>0?substr($nam, 0, $pos):$nam;
      }
      else { //incase there are filenames
        return $this->{iptc}[$key];
      }
    }
    return $this->iptc;
  }

  public function setIptc($key, $value) {
    $this->iptc[$key] = $value;
    return $this->writeIPTCTags($this->getPath());
  }

}