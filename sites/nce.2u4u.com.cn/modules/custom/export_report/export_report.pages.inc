<?php
// $Id$
/** 
 * 回调函数
 */
function export_report_download_page(){
	$output = "";
	//$output .=  "123456789";
	$nid = 1;
	$city = '沈阳市';
  //module_load_include('inc', 'webform', 'includes/webform.submissions');
	//$submissions = _export_report_webform_get_submissions(array('nid'=>$nid,'city'=>$city));
	//$submissions = _export_report_webform_get_submissions();
	$node = node_load(1);
	//$cs = webform_component_list($node, 'csv', TRUE);
	//drupal_set_message(print_r($cs));
	$tid = arg(1);
	$key = arg(2);
	if($key != md5($tid.'2u4u')){
		$output .=  t('对不起，您无权查看本页面的内容');
	}else{
	  $term= taxonomy_get_term($tid);
		$city = $term->name;
		_export_report_webform_results_download($node,'excel',array(),$city);
	}

	//$output .=  print_r($submissions);
	return  $output;
}
function export_report_generate_links_page(){
   	$tempstring='';
   	$tempstring.="<div id='matcharea'>";
    $tempstring.="<div id='matcharea-prompt'>各分赛区负责人查看报名人数的链接：</div>";
	$vid=3;
	$taxonomy_tree = taxonomy_get_tree($vid);
    $tempstring.="<ul>";
	
    foreach( $taxonomy_tree as $taxonomy ){
	  $name = $taxonomy->name;
  	  $depth = $taxonomy->depth;
  
      if($depth==0){
        $province = $name;
        if(strpos($province, '0')<=0){
          $tempstring.="<li class='matcharea-province'>";
          $tempstring.=$province;
          $tempstring.="</li>";
  	      $citycount=0;
        }  
      }
     else{
        $city = $name;
        //$url ="apply";
        if(strpos($city, '0')<=0){
          $tempstring.="<li class='matcharea-city'>";
     	  //print( $citycount);
				$base_path = 'http://'.$_SERVER['HTTP_HOST'].base_path();
          $tempstring.= $city . " : " .$base_path. 'report/'.$taxonomy->tid.'/'.md5($taxonomy->tid.'2u4u');
          $tempstring.="</li>";
        }
       }

    }
    $tempstring.="</ul>"; 


  $tempstring.="</div>";
  
  return $tempstring;
}

function _export_report_webform_results_download($node, $format = 'excel', $options = array(), $city = "") {
  module_load_include('inc', 'webform', 'includes/webform.export');
  module_load_include('inc', 'webform', 'includes/webform.components');

  $submission_information = array(
    'serial' => t('Serial'),
    'sid' => t('SID'),
    'time' => t('Time'),
    'draft' => t('Draft'),
    'ip_address' => t('IP Address'),
    'uid' => t('UID'),
    'username' => t('Username'),
  );

  $submission_information += webform_component_list($node, 'csv', TRUE);
  if (empty($options)) {
    $options = array(
      'delimiter' => variable_get('webform_csv_delimiter', '\t'),
      'components' => array_keys($submission_information),
      'select_display' => 'value',
      'select_format' => 'separate',
    );
  }
  

  // Open a new Webform exporter object.
  $exporter = webform_export_create_handler($format, $options);

  $file_name = tempnam(variable_get('file_directory_temp', file_directory_temp()), 'webform');
  $handle = @fopen($file_name, 'w'); // The @ suppresses errors.
  $exporter->bof($handle);

  // Fill in the header for the submission information (if any).
  $header[2] = $header[1] = $header[0] = count($submission_information) ? array_fill(0, count($submission_information), '') : array();
  if (count($submission_information)) {
    $header[0][0] = $node->title;
    $header[1][0] = t('Submission Details');
    foreach (array_values($submission_information) as $column => $label) {
      $header[2][$column] = $label;
    }
  }

  // Compile header information for components.
  foreach ($options['components'] as $cid) {
    if (isset($node->webform['components'][$cid])) {
      $component = $node->webform['components'][$cid];

      // Let each component determine its headers.
      if (webform_component_feature($component['type'], 'csv')) {
        $component_header = (array) webform_component_invoke($component['type'], 'csv_headers', $component, $options);
        $header[0] = array_merge($header[0], (array) $component_header[0]);
        $header[1] = array_merge($header[1], (array) $component_header[1]);
        //$header[2] = array_merge($header[2], (array) $component_header[2]);
      }
    }
  }

  // Add headers to the file.
  foreach ($header as $row) {
    $exporter->add_row($handle, $row);
  }

  // Get all the submissions for the node.
  //$submissions = webform_get_submissions($node->nid);
	$submissions = _export_report_webform_get_submissions($city);

  // Generate a row for each submission.
  $row_count = 0;
  foreach ($submissions as $sid => $submission) {
    $row_count++;

    $row = array();
    if (isset($submission_information['serial'])) {
      $row[] = $row_count;
    }
    if (isset($submission_information['sid'])) {
      $row[] = $sid;
    }
    if (isset($submission_information['time'])) {
      $row[] = format_date($submission->submitted, 'small');
    }
    if (isset($submission_information['draft'])) {
      $row[] = $submission->is_draft;
    }
    if (isset($submission_information['ip_address'])) {
      $row[] =  $submission->remote_addr;
    }
    if (isset($submission_information['uid'])) {
      $row[] = $submission->uid;
    }
    if (isset($submission_information['username'])) {
      $row[] = $submission->name;
    }

    foreach ($options['components'] as $cid) {
      if (isset($node->webform['components'][$cid])) {
        $component = $node->webform['components'][$cid];
        // Let each component add its data.
        $raw_data = isset($submission->data[$cid]['value']) ? $submission->data[$cid]['value'] : NULL;
        if (webform_component_feature($component['type'], 'csv')) {
          $data = webform_component_invoke($component['type'], 'csv_data', $component, $options, $raw_data);
          if (is_array($data)) {
            $row = array_merge($row, array_values($data));
          }
          else {
            $row[] = empty($data) ? '' : $data;
          }
        }
      }
    }

    // Write data from submissions.
    $data = $exporter->add_row($handle, $row);
  }

  // Add the closing bytes.
  $exporter->eof($handle);

  // Close the file.
  @fclose($handle);

  $export_name = _webform_safe_name($node->title);
  $exporter->set_headers($export_name);
  @readfile($file_name);  // The @ makes it silent.
  @unlink($file_name);  // Clean up, the @ makes it silent.
  exit();
}
/**
 * Return all the submissions for a particular node.
 *
 * @param $filters
 *   An array of filters to apply to this query. Usually in the format
 *   array('nid' => $nid, 'uid' => $uid). A single integer may also be passed
 *   in, which will be equivalent to specifying a $nid filter.
 * @param $header
 *   If the results of this fetch will be used in a sortable
 *   table, pass the array header of the table.
 * @param $pager_count
 *   Optional. The number of submissions to include in the results.
 */
function _export_report_webform_get_submissions($city) {
  $submissions = array();
		
	$pager_query = "SELECT s.sid FROM {webform_submissions} s LEFT JOIN {webform_submitted_data} sd ON sd.sid = s.sid  WHERE s.nid = 1 AND sd.cid = 11 AND sd.data = '%s' " ;

	//$pager_query .= ' ORDER BY s.sid ASC';

	$result = db_query($pager_query, $city);


	$sids = array();
	while ($row = db_fetch_object($result)) {
		$sids[] = $row->sid;
		$submissions[$row->sid] = FALSE;
	}
  //drupal_set_message(print_r($sids));
	//drupal_set_message('sids123456');
  // If there are no submissions being retrieved, return an empty array.
  if (empty($sids)) {
    return $submissions;
  }

  // Query the required submission data.
  $query = 'SELECT s.*, sd.cid, sd.no, sd.data, u.name, u.mail, u.status ' .
           'FROM {webform_submissions} s ' .
           'LEFT JOIN {webform_submitted_data} sd ON sd.sid = s.sid ' .
           'LEFT JOIN {users} u ON u.uid = s.uid ' .
           'WHERE s.sid IN (' . db_placeholders($sids) . ') ' .
           'ORDER BY sd.sid ASC, sd.cid ASC, sd.no ASC';

  $result = db_query($query, $sids);
  //drupal_set_message('sids123456789');
  // Convert the queried rows into submissions.
  $previous = array();
  while ($row = db_fetch_object($result)) {
    if ($row->sid != $previous) {
      $submissions[$row->sid] = new stdClass();
      $submissions[$row->sid]->sid = $row->sid;
      $submissions[$row->sid]->nid = $row->nid;
      $submissions[$row->sid]->submitted = $row->submitted;
      $submissions[$row->sid]->remote_addr = $row->remote_addr;
      $submissions[$row->sid]->uid = $row->uid;
      $submissions[$row->sid]->name = $row->name;
      $submissions[$row->sid]->is_draft = $row->is_draft;
    }
    $submissions[$row->sid]->data[$row->cid]['value'][$row->no] = $row->data;
    $previous = $row->sid;
  }

  foreach (module_implements('webform_submission_load') as $module) {
    $function = $module . '_webform_submission_load';
    $function($submissions);
  }

  return $submissions;
}