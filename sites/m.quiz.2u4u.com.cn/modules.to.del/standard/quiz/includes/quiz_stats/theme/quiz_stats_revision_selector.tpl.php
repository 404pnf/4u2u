<?php 
// $Id: quiz_stats_revision_selector.tpl.php,v 1.1.2.3 2010/02/23 13:41:21 falcon Exp $
print '<p>' . $content['explanation'] . '</p>' . "\n";
print '<p>';
$counter = 1;
foreach ($content['links'] as $key => $value) {
  print ' | '. l(t('revision !num', array('!num' => $counter++)), $value);
}
print ' |</p>';
?>