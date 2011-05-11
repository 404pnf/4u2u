#!/bin/php
<?php

$timeunit = $argv[1];
$limit = 0;
if($timeunit == "-d"){
  $limit = time() - $argv[2]*3600*24;
}
if($timeunit == "-h"){
  $limit = time() - $argv[2]*3600;
}

$output = $argv[3];
if($output == '-o'){
   if ($handle = opendir('.')) {
    echo "Directory handle: $handle\n";
    echo "Files:\n";

    while (false !== ($nidfile = readdir($handle))) {
       if(is_dir($nidfile)&& is_numeric($nidfile)){
	  $modtime = filemtime($nidfile);

  	  $size = filesize($nidfile);
	  
	  if($modtime > $limit){
	    echo $nidfile."|".$modtime."|".$limit."\n";
	    $output = $argv[4];	
	    shell_exec("mkdir $output/$nidfile");
	    shell_exec("cp Yuedu.swf $output/$nidfile/");
	    shell_exec("cp template.tpl $output/$nidfile/index.html");
	$ifname = "$output/$nidfile/index.html";
            $fhandle = fopen($ifname,"r");
            $content = fread($fhandle,filesize($ifname));
                $directory = opendir($nidfile);
//while($item = readdir($directory)){
//if(($item != ".") && ($item != "..")){
//$files[] = $item;
//}
//}
$count= array();
exec("ls ". $nidfile."| wc -l",$count);
            $content = str_replace("215", $count[0], $content);
 $content = str_replace("111", $nidfile, $content);

            $fhandle = fopen($ifname,"w");
            fwrite($fhandle,$content);
            fclose($fhandle);    
	copyto($nidfile,"$output/$nidfile/assets");
	    
	  }
	}
    }

    

    closedir($handle);
  }

}

function copyto($from,$to){
  shell_exec("cp $from $to -r");

}





?>
