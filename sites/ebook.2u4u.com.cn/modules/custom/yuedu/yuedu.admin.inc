<?php
function convert_pdf(&$node) {
	global $user;
  $numberOfFiles = count($node->field_yuedu_pdf);
  if ($numberOfFiles > 1) {
    $swfDir = file_directory_path() . '/pdf/swf/' . $node->nid;
    if (! is_dir($swfDir)) {
      foreach ($node->field_yuedu_pdf as $file) {
        $filesAbsolutePath .= ' ' . $file ['filepath'];
      }
      $firstFileName = $node->field_yuedu_pdf [0] ['filepath'];
      $newFileName = str_replace(".pdf", "-combine.pdf", $firstFileName);
      $command = "gs -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=$newFileName  " . $filesAbsolutePath;
      shell_exec($command);
      $node->field_yuedu_pdf [0] ['filepath'] = $newFileName;
      
    //drupal_set_message ($command );
    }
  }
  $file = $node->field_yuedu_pdf [0];
  $path_parts = pathinfo($file ['filepath']);
  $filename = $path_parts ['filename'];
  $fileext = $path_parts ['extension'];
  $swfDir = file_directory_path() . '/pdf/swf/' . $node->nid;
  if (! is_dir($swfDir)) {
    mkdir($swfDir);
    $dest = $file ['filepath'];
    $path_parts = pathinfo($dest);

    $out = exec("/usr/local/bin/pdf2swf $dest -o $swfDir/%.ds >> /tmp/output");
    # bxy: need more sophisticated cmd option
    # i complile everything from source and copy fonts/character collection
    # from a ubutntu to here, /usr/share/fonts /usr/share/xpdf /etc/xpdf/
    # /home/myapp/swftools/bin/pdf2swf $f -o tmp/$f.%.swf -s languagedir=/home/myapp/xpdf/etc/
    # /home/myapp/swftools/bin/pdf2swf $dest -o $swfDir/%.ds -s languagedir=/home/myapp/xpdf/etc/ >>/tmp/output
    #$out = exec("/home/myapp/swftools/bin/pdf2swf $dest -o $swfDir/%.ds -s languagedir=/home/myapp/xpdf/etc/ >>/tmp/outpu");
  }
  
  $domain = $_SERVER ['SERVER_NAME'];
  $swfUrl = "http://$domain/sites/$domain/files/Yuedu.swf";
  $number = count(scandir($swfDir)) - 2;
  $contentUrl = "http://$domain/yuedu/doc/" . $node->nid . '/';
  $node->field_yuedu_player [0] ['value'] = swf($swfUrl, array (
    'params' => array (
    'height' => '700', 'width' => '100%', 'wmode' => 'window', 'allowscriptaccess' => 'samedomain', 'wmode' => 'transparent' 
  ), 'flashvars' => array (
    'num' => $number - 1, 'url' => $contentUrl, 'name' => $path_parts ['filename'], 'nid' => $node->nid 
  ) 
  ));
  
  $preview =(int)$number*0.4;
  if($preview <= 20){
  	$preview = 20;
  }
  $node->field_yuedu_preview[0]['value'] = $preview;
  $cover = $node->field_yuedu_cover;
  if (! isset($cover [0]->data)) {
    //drupal_set_message('hi');
    $path_parts = pathinfo($file ['filename']);
    $sku = $node->field_yuedu_sku[0]['value'];
    if($sku =='')
    {
	$sku = 'cover';
    }
    $coverDir= file_directory_path() . '/pdf/swf/cover';
    shell_exec("/usr/local/bin/swfrender $swfDir/1.ds -o $coverDir/$sku.jpg");
    $filepath = "$coverDir/$sku.jpg";
    if (file_exists($filepath)) {
      $field = field_file_save_file($filepath, array (), file_directory_path());
      $node->field_yuedu_cover = array (
        0 => $field 
      );
    }
  }
}


function yuedu_import() {
//			    	$node = node_load(32859);
//	
//   foreach ($node->taxonomy as $vid => $nodeTerm) {
//			   		 $term = getOrCreateTermFromString($nodeTerm->name);
//	}
  $newBooks = yuedu_get_new_books();
  $header = array (
    'SKU', 'Title' 
  );
  foreach ($newBooks as $newBook) {
    $newBooksString .= $newBook ['sku'] . ',';
  }
  $newBooksString = trim($newBooksString, ',');
  $renderedTable = theme_table($header, $newBooks);
  $renderedForm = drupal_get_form('yuedu_import_form', $newBooksString);
  
  return $renderedTable . $renderedForm;

}

function yuedu_import_form(&$form_state, $booksToImport) {
  $form = array ();
  $form ['import'] = array (
    '#type' => 'fieldset', '#title' => t('Import') 
  );
  // add a file upload file
  $form ['import'] ['num'] = array (
    '#type' => 'textfield', '#title' => 'Items', '#description' => t('Number of items to import') 
  );
  // add a submit button
  $form ['import'] ['submit'] = array (
    '#type' => 'submit', '#value' => 'Submit' 
  );
  $form ['newBooks'] = array (
    '#type' => 'hidden', '#value' => $booksToImport 
  );
  return $form;
}

function yuedu_import_form_submit($form, &$form_state) {
  $values = $form_state ['values'];
  $newBooks = explode(',', $values ['newBooks']);
  $num = $values ['num'];
  //pop
  if ($num > 0 && $num < count($newBooks)) {
  	array_splice($newBooks, $num);
  }
   yuedu_create_node_from_sku_array($newBooks);

}

function yuedu_get_new_books() {
  $newBooks = array ();
  $dirname = "/var/www/html/2u4u/sites/ebook.2u4u.com.cn/files/pdf/";
	if (is_dir($dirname)) $dir_handle = opendir($dirname);
	  while ($file = readdir($dir_handle)) {
	    	$fileparts = explode('.',$file);
	    	if($fileparts[count($fileparts)-1]=='pdf'){
	    	$sql = "select * from {content_type_erp} where field_erp_wuliaohao_value =%d";
	      $result = db_fetch_object(db_query(db_rewrite_sql($sql), $fileparts[0]));
		if($result != null){
			$newBook = array ();
	        $newBook ['sku'] = $fileparts[0];
	        $newBook ['title'] =$result->field_erp_shuming_value;
	        array_push($newBooks, $newBook);
		}
	    	}
	    }
	  
  

  return $newBooks;
}

//function yuedu_get_book_info_by_sku_array($skuArray) {
//  $objWorksheet = yuedu_get_booklist_worksheet();
//  $highestRow = $objWorksheet->getHighestRow();
//  
//  $bookInfoArrayArray = array ();
//  
//  foreach ($skuArray as $sku) {
//    $bookInfoArray = array ();
//    for ($row = 2; $row <= $highestRow; ++ $row) {
//      $skuInList = $objWorksheet->getCellByColumnAndRow(0, $row)->getValue();
//      if ($skuInList == $sku) {
//        $bookInfoArray ['sku'] = $skuInList;
//        $bookInfoArray ['title'] = $objWorksheet->getCellByColumnAndRow(1, $row)->getValue();
//        $bookInfoArray ['summary'] = $objWorksheet->getCellByColumnAndRow(10, $row)->getValue();
//        $bookInfoArray ['author'] = $objWorksheet->getCellByColumnAndRow(13, $row)->getValue();
//        $bookInfoArray ['isbn'] = $objWorksheet->getCellByColumnAndRow(14, $row)->getValue();
//        for($i = 5;$i<=8;$i++){
//		$tag = $objWorksheet->getCellByColumnAndRow($i, $row)->getValue();
//		if($tag != ''){
//			$tags .= $tag.',';
//		}
//	}
//	$bookInfoArray ['tags'] = $tags;
//        array_push($bookInfoArrayArray, $bookInfoArray);
//      }
//    }
//  }
//  return $bookInfoArrayArray;
//}
/*
function yuedu_get_booklist_worksheet() {
  $modulePath = drupal_get_path('module', 'yuedu');
  $bookListPath = '/var/www/html/2u4u/sites/ebook.2u4u.com.cn/files/pdf/booklist.xlsx';
  include_once "$modulePath/Classes/PHPExcel.php";
  include_once "$modulePath/Classes/PHPExcel/IOFactory.php";
  $objReader = PHPExcel_IOFactory::createReader('Excel2007');
  $objReader->setReadDataOnly(true);
  $objPHPExcel = $objReader->load($bookListPath);
  $objWorksheet = $objPHPExcel->getActiveSheet();
  return $objWorksheet;
}
*/

function yuedu_create_node_from_sku_array($skuArray) {
  global $user;
  foreach ($skuArray as $sku) {
  	
  	 $dirname = "/var/www/html/2u4u/sites/ebook.2u4u.com.cn/files/pdf/";
	if (is_dir($dirname)) $dir_handle = opendir($dirname);
	  while ($filename = readdir($dir_handle)) {
	    if ($filename != "." && $filename != "..") {
	    	$fileparts = explode('.',$filename);
	    	if($fileparts[count($fileparts)-1]=='pdf' && $fileparts[0]==$sku){
			    $file_drupal_path = file_directory_path() . "/pdf/$filename";
			    $file = new stdClass();
			    $file->filename = basename($file_drupal_path);
			    $file->filepath = $file_drupal_path;
			    $file->filesize = filesize($file_drupal_path);
			    $file->uid = $user->uid;
			    $file->status = FILE_STATUS_PERMANENT;
			    $file->timestamp = time();
			    drupal_write_record('files', $file);
			    $file->fid = db_result(db_query("SELECT fid FROM {files} WHERE filepath = '%s'", $file->filepath));
			    
			    $sql = "select * from {content_type_erp} where field_erp_wuliaohao_value =%d";
	      		$erp = db_fetch_object(db_query(db_rewrite_sql($sql), $fileparts[0]));
	
			    
			    
			    $node = new stdClass();
			    $node->type = 'ebook';
			    $node->status = 1;
			    $node->uid = $user->uid;
			    $node->title = $erp->field_erp_shuming_value;
			    $node->field_yuedu_author [0] ['value'] = $erp->field_erp_zhuzuozhe_value;
			    $node->field_yuedu_summary [0] ['value'] = $erp->field_erp_neirongtiyao_value;
			    $node->field_yuedu_sku [0] ['value'] = $sku;
			    $node->field_yuedu_isbn [0] ['value'] = $erp->field_erp_shuhaotiaoma_value;
			    $node->field_yuedu_pricebypoints[0]['value'] = $erp->field_erp_dingjia_value;
//			    $node->field_yuedu_preview[0]['value'] = 10;
			    
			    $erpNode = node_load($erp->nid);
			    foreach ($erpNode->taxonomy as $vid => $nodeTerm) {
			   		 $term = getOrCreateTermFromString($nodeTerm->name);
			    }
			    $node->taxonomy[$term->vid][$term->tid] = $term->tid;
			    
			    $node->field_yuedu_pdf = array (
			      array (
			      'fid' => $file->fid, 'title' => basename($file->filename), 'filename' => $file->filename, 'filepath' => $file->filepath, 'filesize' => $file->filesize, 'mimetype' => $mime, 'description' => basename($file->filename), 'list' => 1 
			    ) 
			    );

			    $node->created = time();
			    $node->changed = $node->created;
			    $node->promote = 1;
			    $node->sticky = 0;
			    $node->format = 1;

			    node_save($node);
convert_pdf($node);
node_save($node);
//			    drupal_set_message($dirname.$file);
			    unlink($dirname.$filename);
	    	}
	    }
	}
  }
}

function getOrCreateTermFromString($termName)
{
	$terms = taxonomy_get_term_by_name($termName);
	if(count($terms)>1){
		foreach($terms as $term){
			if($term->vid == 19)
				return $term;
		}
	}
	 $autoterm = array(
     'name' => $termName,  // or whatever you want the auto-term to be named
     'parent' => 0,
     'vid' => 19,
    );
     taxonomy_save_term($autoterm);
	return getOrCreateTermFromString($termName);
	
}
