<?php
// $Id$
/**
 * Table builder for user downloads
 */
function uc_filedownload_user_downloads($account) {
  // Create a header and the pager it belongs to.
  $header = array(
    array('data' => t('Purchased'  ), 'field' => 'u.granted', 'sort' => 'desc'),
		array('data' => t('产品名称'), 'field' => 'n.title'),
    array('data' => t('Filename'   ), 'field' => 'f.filename'),
    array('data' => t('Description'), 'field' => 'p.description'),
		//可能暂时不显示下载次数和IP地址限制，暂时不删除
    array('data' => t('Downloads'  ), 'field' => 'u.accessed'),
    array('data' => t('Addresses'  )),
  );

  drupal_set_title(t('File downloads'));

  $files = array();

  $result = pager_query(
    "SELECT u.granted, f.filename, u.accessed, u.addresses, p.description, u.file_key, f.fid, u.download_limit, u.address_limit, u.expiration, n.nid, n.title FROM {uc_file_users} as u ".
    "LEFT JOIN {uc_files} as f ON u.fid = f.fid ".
		"LEFT JOIN {uc_product_features} upf ON u.pfid = upf.pfid ".
		"LEFT JOIN {node} n ON n.nid = upf.nid ".
    "LEFT JOIN {uc_file_products} as p ON p.pfid = u.pfid WHERE u.uid = %d".
    tablesort_sql($header),
    UC_FILE_PAGER_SIZE,
    0,
    "SELECT COUNT(*) FROM {uc_file_users} WHERE uid = %d",
    $account->uid
  );

  $row = 0;
  while ($file = db_fetch_object($result)) {

    $download_limit = $file->download_limit;

    // Set the JS behavior when this link gets clicked.
    $onclick = array(
      'attributes' => array(
        'onclick' => 'uc_file_update_download('. $row .', '. $file->accessed .', '. ((empty($download_limit)) ? -1 : $download_limit) .');', 'id' => 'link-'. $row
      ),
    );

    // Expiration set to 'never'
    if ($file->expiration == FALSE) {
      $file_link = l(basename($file->filename), 'download/'. $file->fid .'/'. $file->file_key, $onclick);
    }

    // Expired.
    elseif (time() > $file->expiration) {
      $file_link = basename($file->filename);
    }

    // Able to be downloaded.
    else {
      $file_link = l(basename($file->filename), 'download/'. $file->fid .'/'. $file->file_key, $onclick) .' ('. t('expires on @date', array('@date' => format_date($file->expiration, 'custom', variable_get('uc_date_format_default', 'm/d/Y')))) .')';
    }

    $files[] = array(
      'granted' => $file->granted,
      'link' => $file_link,
      'description' => $file->description,
      'accessed' => $file->accessed,
      'download_limit' => $file->download_limit,
      'addresses' => $file->address,
      'address_limit' => $file->address_limit,
			'address_limit' => $file->address_limit,
			'nid' => $file->nid,
			'title' => $file->title,
    );
    $row++;
  }

  return theme('uc_filedownload_user_downloads', $header, $files);
}

function theme_uc_filedownload_user_downloads($header, $files) {
	$output ='Success';
  $rows = array();
  $row = 0;
  foreach ($files as $file) {
    $rows[] = array(
      array('data' => format_date($file['granted'], 'custom', variable_get('uc_date_format_default', 'm/d/Y')), 'class' => 'date-row', 'id' => 'date-'. $row),
      //array('data' => l($file['title'],'dlnode/'.$file['nid']), 'class' => 'node-title-row', 'id' => 'node-title-'. $row),
			array('data' => l($file['title'],'dlnode/'.$file['nid'],array('attributes'=>array('target'=>'_blank'),)), 'class' => 'node-title-row', 'id' => 'node-title-'. $row),
			array('data' => $file['link'], 'class' => 'filename-row', 'id' => 'filename-'. $row),
      array('data' => $file['description'], 'class' => 'description-row', 'id' => 'description-'. $row),
      array('data' => $file['accessed'] .'/'. ($file['download_limit'] ? $file['download_limit'] : t('Unlimited')), 'class' => 'download-row', 'id' => 'download-'. $row),
      array('data' => count(unserialize($file['addresses'])) .'/'. ($file['address_limit'] ? $file['address_limit'] : t('Unlimited')), 'class' => 'addresses-row', 'id' => 'addresses-'. $row),
    );
    $row++;
  }
  if (empty($rows)) {
    $rows[] = array(array('data' => t('No downloads found'), 'colspan' => 6));
  }

  $output .= theme('table', $header, $rows);
  $output .= theme('pager', NULL, UC_FILE_PAGER_SIZE, 0);
  $output .= '<div class="form-item"><p class="description">'.
  t('Once your download is finished, you must refresh the page to download again. (Provided you have permission)') .
  '<br />'. t('Downloads will not be counted until the file is finished transferring, even though the number may increment when you click.') .
  '<br /><b>'. t('Do not use any download acceleration feature to download the file, or you may lock yourself out of the download.') .'</b>'.
  '</p></div>';
  return $output;
}
