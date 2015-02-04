<html>
  <head>
    <title>File Details</title>
  </head>
  <body>
<?php
$current_dir = "./upload/";
$file = $current_dir.basename($_REQUEST['file']);

echo "<h1>Detail of file: ".$file."</h1>";
echo '<h2>File data</h2>';
echo 'File last accessed: '.date('j F Y H:i', fileatime($file)).'<br>';
echo 'File last modified: '.date('j F Y H:i', filemtime($file)).'<br>';


//$user = posix_getpwuid(fileowner($file));
//echo "user: ".$user['name'];
//echo 'File owner: '.$user['name'].'<br>';

//$group = posix_getpwgid(filegroup($file));
//echo 'File group: '.$group['name'].'<br>';

echo 'File permissions: '.decoct(fileperms($file)).'<br>';

echo 'File type: '.filetype($file).'<br>';

echo 'File size: '.filesize($file).' bytes<br>';

echo '<h2>File tests</h2>';

echo 'is_dir: '.((is_dir($file)) ? 'true' : 'false').'<br>';
echo 'is_executeble: '.(is_executable($file) ? 'true' : 'false').'<br>';
echo 'is_file: '.(is_file($file) ? 'true' : 'false').'<br>';
echo 'is_link: '.(is_link($file) ? 'true' : 'false').'<br>';
echo 'is_readable: '.(is_readable($file) ? 'true' : 'false').'<br>';
echo 'is_writable: '.(is_writable($file) ? 'true' : 'false').'<br>';

?>
</body>
</html>
