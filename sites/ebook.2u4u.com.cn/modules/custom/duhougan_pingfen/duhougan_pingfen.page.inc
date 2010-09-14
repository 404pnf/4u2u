<?php

/**
*读后感评分模块管理员设置页面，主要设置谁可以进行评分
*/
function theme_duhougan_pingfen($node) {
  return drupal_get_form('duhougan_pingfen_rate_form_'.$node->nid, $node);
}

function duhougan_pingfen_rate_form($form_state, $node) {
	$form['#validate'][] = 'duhougan_pingfen_rate_form_validate';
  $form['#submit'][] = 'duhougan_pingfen_rate_form_submit';
	//$form['#id'] = 'duhougan-pingfen-rate-form-'.$node->nid;
  $form['nid'] = array('#type' => 'value', '#value' => $node->nid);

  global $user;
  $score = array();
  $r = 0;
  $score[] = t('Select');

	for($j=100; $j>=50; $j--) {
    $score[$j] = $j;
  }
	
	if(db_result(db_query("SELECT vid FROM {duhougan_pingfen} WHERE vid=%d",$node->vid))){
		$score_id = "have_score";
	}else{
		$score_id = "no_score";
	}

  //$set='rate';
	$set=$node->nid;
  $form[$set] = array(
    '#type'   => 'fieldset',
    '#title'  => t('对此读后感评分'),
    '#value'  => t('<br>分数从50到100分'),
    '#prefix' => '<div id="duhougan_pingfen">',
    '#suffix' => '</div>',
   );

  $form[$set]['score'] = array(
    '#type' => 'select',
    '#title' => t('分数'),
    '#default_value' => $node->duhougan_score,
	'#prefix' => "<div id='".$score_id."'>",
	 '#suffix' => "</div>",
    '#options' => $score,
	 '#required'=> TRUE,
  );
    $form[$set]['vid'] = array(
    '#type' => 'hidden',
	'#value' => $node->vid,
  );

  $form[$set]['submit'] = array(
    '#type'  => 'submit',
		'#id' => 'edit-submit-'. $node->nid,
    '#value' => t('提交'),
  );
	$form[$set]['cancel'] = array(
    '#type'  => 'submit',
		'#id' => 'edit-cancel-'. $node->nid,
    '#value' => t('取消'),
  );

  $form['#attributes'] = array('class' => 'duhougan_pingfen-form');

  return $form;
}

function duhougan_pingfen_rate_form_validate($form, &$form_state){
	if($form_state['values']['op']== $form_state['values']['submit']){
		if(!$form_state["values"]["score"]){
			form_set_error("score","你必须选择一个分数");
		}
	}
	
}

function duhougan_pingfen_rate_form_submit($form, &$form_state){
	global $user;
	if($form_state['values']['op']== $form_state['values']['submit']){
		if($form_state["values"]["score"]){

			if(db_result(db_query("SELECT vid FROM {duhougan_pingfen} WHERE vid=%d",$form_state["values"]["vid"]))){

				db_query("UPDATE {duhougan_pingfen} SET score=%d, timestamp=%d WHERE vid=%d",$form_state["values"]["score"],time(),$form_state["values"]["vid"]); // 判断这个节点是滞已经评分，如果有，更新
			}else{
				db_query("INSERT INTO {duhougan_pingfen} (uid,vid,score,timestamp) VALUES(%d,%d,%d,%d)",$user->uid,$form_state["values"]["vid"],$form_state["values"]["score"],time()); // 插入最新的评分结果
			}
		}
	}	
	if($form_state['values']['op']== $form_state['values']['cancel']){
		db_query('DELETE FROM {duhougan_pingfen} WHERE vid = %d', $form_state["values"]["vid"]);
	}

}