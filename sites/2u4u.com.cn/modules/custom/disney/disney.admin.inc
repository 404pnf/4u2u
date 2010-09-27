<?php
function disney_series_add_page(){
	
	
	$content =  drupal_get_form('disney_series_add_form');	
	$sql = "SELECT * FROM {disney_series} ORDER BY `series_id` ";	
	$res = db_query($sql);
	$content .= "<ul>";
	while($row = db_fetch_object($res)){		
		if($row->series_name!=''){
			
			$content .= "<li><a href='/disney/series/".$row->series_id."'>".$row->series_name."</a>&nbsp;&nbsp;";
			$content .= "<a href='http://2u4u.com.cn/admin/settings/delete/disney/series/".$row->series_id."'>删除</a></li>";
			
			
		}
	}
	$content .= "</ul>";
	
	return $content;
}


 
 function disney_series_add_form($form_state){

   $form = array();

   $form['disney_series_add']['title'] = array(
      '#title'=>t('请输入新增加的迪士尼英语系列名称'),
      '#type' => 'textfield',
      '#prefix' => '<div id="title">', // This is our wrapper div
      '#suffix' => '</div>',
      );
      
	 $form['disney_series_add']['submit']	= array(
      '#type' => 'submit',
      '#value' => t('提交'),
	   
     );
  
	  return $form;
}



function disney_series_add_form_submit($form,$form_state){
	
	

	if($form_state['values']['title']!=''){
		
		$series_name = '';
		$series_name = $form_state['values']['title'];		
		$sql = "INSERT INTO {disney_series} (`series_id`,`series_name`)
		        SELECT '','%s'
		        FROM {disney_series}
		        WHERE NOT EXISTS (SELECT 1 FROM {disney_series} WHERE `series_name`='%s') LIMIT 1";

		 $rs = db_query($sql,$series_name,$series_name);
		 if($rs)
		     drupal_set_message(t('添加"'.$series_name.'"成功'));
		  else 
		     drupal_set_message(t('添加"'.$series_name.'"失败'),'error');
		       
		// drupal_goto('/admin/settings/add/disney/series');
		
	}
	
	
	
	
}


function disney_series_delete($series_id){

	if($series_id>0){
		
		$sql = "DELETE FROM {disney_series} WHERE `series_id`=%d";
	
		$rs = db_query($sql,$series_id);
		if($rs)
		     drupal_set_message(t('删除成功'));
		 else 
		     drupal_set_message(t('删除失败'),'error');  
		     
		
	 }else{
	
     	drupal_set_message(t('请输入有效id'),'error');  
	
	}
		
	 drupal_goto('http://2u4u.com.cn/admin/settings/add/disney/series');
	
}



 function disney_series_add_form_validate($form,&$form_state){

	if($form_state['values']['title']==''){
	   form_set_error('word',t('请输入名称'));	
	}
 } 
  
