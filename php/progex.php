<?php
phpinfo();
echo "URL: ".getenv('HTTP_REFERER').'<br />';
chdir("./upload/");

echo '<pre>';

exec('ls -al', $result);
foreach ($result as $line)
	echo "$line\n";
echo '</pre>';
echo '<br><hr><br>';

echo '<pre>';
passthru('ls -al');
echo '</pre>';
echo '<br><hr><br>';

echo '<pre>';
$result = system('ls -al');

echo '</pre>';
echo '<br><hr><br>';

echo '<pre>';
$result = `ls -al`;
echo $result;
echo '</pre>';

?>
