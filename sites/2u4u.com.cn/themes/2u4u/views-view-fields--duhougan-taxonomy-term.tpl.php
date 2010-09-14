<?php

// $Id: views-view-fields.tpl.php,v 1.6 2008/09/24 22:48:21 merlinofchaos Exp $

/**

 * @file views-view-fields.tpl.php

 * Default simple view template to all the fields as a row.

 *

 * - $view: The view in use.

 * - $fields: an array of $field objects. Each one contains:

 *   - $field->content: The output of the field.

 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.

 *   - $field->class: The safe class id to use.

 *   - $field->handler: The Views field handler object controlling this field. Do not use

 *     var_export to dump this object, as it can't handle the recursion.

 *   - $field->inline: Whether or not the field should be inline.

 *   - $field->inline_html: either div or span based on the above flag.

 *   - $field->separator: an optional separator that may appear before a field.

 * - $row: The raw result object from the query, with all data it fetched.

 *

 * @ingroup views_templates

 */

?>

<?php foreach ($fields as $id => $field): ?>

  <?php if (!empty($field->separator)): ?>

    <?php print $field->separator; ?>

  <?php endif; ?>



  <<?php print $field->inline_html;?> class="views-field-<?php print $field->class; ?>">

    <?php if ($field->label): ?>

      <label class="views-label-<?php print $field->class; ?>">

        <?php print $field->label; ?>:

      </label>

    <?php endif; ?>

      <?php

      // $field->element_type is either SPAN or DIV depending upon whether or not

      // the field is a 'block' element type or 'inline' element type.

      ?>

      <<?php print $field->element_type; ?> class="field-content"><?php print $field->content; ?></<?php print $field->element_type; ?>>

  </<?php print $field->inline_html;?>>

<?php endforeach; ?>





<?php





$node = node_load($row->nid);



 $type = array(9011,9012,9013,9014,9015,9017,9018,9019,9020,9021);



	 $is_duhougan = FALSE;



	foreach($node->taxonomy as $value){



		if(in_array($value->tid,$type)){

			$is_duhougan = TRUE;

		}



	}



	

	global $user;



	$compele_profiel = db_result(db_query("SELECT nid FROM {node} WHERE uid=%d AND type='%s'",$user->uid,'profile'));



	if(user_is_anonymous() && $is_duhougan){



		$output = l(t("参加读后感大赛，请先登录"),'user/login',array('html' => true, 'query' => 'destination=node/'.$node->nid) );



	}



	if(!$compele_profiel && user_is_logged_in() && $is_duhougan){



	//	$output = l(t("参加读后感大赛，请先完善您的资料"),'user/'.$user->uid.'/profile/profile',array('html' => true, 'query' => 'destination=node/add/readthink/'.$node->nid) );



		$output = "<a href=".base_path()."user/".$user->uid."/profile/profile?destination=node/add/readthink?destination=duhougan_confirm/".$node->nid."&edit[parent]=".$node->nid.">参加读后感大赛，请先完善您的资料</a>";



	}



	if($compele_profiel && user_is_logged_in() && $is_duhougan){



		$output = l(t("参加读后感大赛"),'node/add/readthink',array('html' => true, 'query' => 'destination=duhougan_confirm/'.$node->nid.'&edit[parent]='.$node->nid) );

	}



	print $output;





	?>
