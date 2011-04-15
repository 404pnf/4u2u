<?php

class FGApi {
  static private $instance = null;

  /**
   * We are implementing a singleton pattern
   */
  private function __construct() {
  }

  /**
   * 
   * @return FGApi
   */
  public function getInstance() {
    if (is_null(self :: $instance)) {
      self :: $instance = new self;
    }
    return self :: $instance;
  }
  
  /**
   * filtering the params and checking if they are complete
   * @param array $params
   * @return array
   *  - status -> boolean if need params are available
   *  - params
   */
  public function transformParams($params) {
    $checkedParams = array();
    foreach ($params as $key => $item) {
      $checkedParams[$key] = check_plain($item);
    }
    if (!isset($checkedParams['type'])) {
      $checkedParams['type'] = 'html';
    }
    if (!isset($checkedParams['path'])) {
      return array('status' => FALSE, 'params' => $checkedParams);
    }
    if (!isset($checkedParams['gallery'])) {
      return array('status' => FALSE, 'params' => $checkedParams);
    }
    
    return array('status' => TRUE, 'params' => $checkedParams);
  }
  
  /**
   * the path alias needs to be transformed so it can be
   * matched onto the internal path to find the pictures
   * @param array $params
   * @return string
   */
  public function createFgGalleryPath($params) {
    $settings = variable_get('fg_galleries');

      $ar_base_path = explode('/', $params['gallery']);

      //remove slashed that are too much
      if ($ar_base_path[count($ar_base_path)-1] == '') {
        unset($ar_base_path[count($ar_base_path)-1]);
      }
      if ($ar_base_path[0] == '') {
        unset($ar_base_path[0]);
      }
      $gallery = implode('/', $ar_base_path) . '/';


      $path = $settings[$gallery]['fg_path'] . $params['path'];

      $current_path_alias = $params['path'];
      $start = strlen($settings[$gallery]['fg_alias']);
      $path_new = substr($current_path_alias, ++$start);
      $path_new  = $settings[$gallery]['fg_path'] . $path_new;
      
      return $path_new;
  }
  /**
   * The main function for converting to an XML document.
   * Pass in a multi dimensional array and this recrusively loops through and builds up an XML document.
   *
   * @param array $data
   * @param string $rootNodeName - what you want the root node to be - defaultsto data.
   * @param SimpleXMLElement $xml - should only be used recursively
   * @return string XML
   */
  public function toXml($data, $rootNodeName = 'data', $xml=null)
  {
    if(empty($data)){
      return false;
    }
    // turn off compatibility mode as simple xml throws a wobbly if you don't.
    if (ini_get('zend.ze1_compatibility_mode') == 1)
    {
      ini_set ('zend.ze1_compatibility_mode', 0);
    }

    if ($xml == null)
    {
      $xml = simplexml_load_string("<?xml version='1.0' encoding='utf-8'?><$rootNodeName />");
    }

    // loop through the data passed in.
    foreach($data as $key => $value)
    {
      // no numeric keys in our xml please!
      if (is_numeric($key))
      {
        // make string key...
        $key = "unknownNode_". (string) $key;
      }

      // replace anything not alpha numeric
      $key = preg_replace('/[^a-z]/i', '', $key);

      // if there is another array found recrusively call this function
      if (is_array($value))
      {
        $node = $xml->addChild($key);
        // recrusive call.
        ArrayToXML::toXml($value, $rootNodeName, $node);
      }
      else
      {
        // add single node.
        $value = htmlentities($value);
        $xml->addChild($key,$value);
      }

    }
    // pass back as string. or simple xml object if you want!
    return $xml->asXML();
  }
}
