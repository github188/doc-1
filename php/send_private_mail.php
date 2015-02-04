<?php
$from = $_POST['from'];
$title = $_POST['title'];
$body = $_POST['body'];
$to_email = 'li_yunteng@163.com';

// Tell gpg where to find the key ring
// putenv('GNUPGHOME=/tmp/.gnupg');

// create a unique file name
//$infile = tempnam('', 'pgp');
//$outfile = $infile.'.asc';

// write the user's text to the file
//$fp = fopen($infile, 'w');
//fwrite($fp, $body);
//fclose(fp);

// set up our command
// $command = "/usr/bin/gpg -a \\
// 		--recipient 'li yunteng <liyt@jwele.com.cn>' \\
// 		--encrypt -o $outfile $infile";
// execute our gpg command
// system($command, $result);

// delete the unencrypted temp file
//unlink($infile);

// if ($result == 0) {
// 	$fp = fopen($infile, 'r');
// 	if ((!$fp) || (filesize($infile) == 0)) {
// 		$result = -1;
// 	} else {
// 		// read the encrypted file
// 		$contents = fread($fp, filesize($infile));

// 		// delete the encrypted temp file
// 		unlink($infile);

// 		mail($to_email, $title, $content, "From:".$from."\n");
// 		echo '<h1>Message Sent</h1>';
// 		echo '<p>Your message was encrypted and sent.</p>';
// 		echo '<p>Thank you.</p>';

// 	}
// }

mail($to_email, $title, $body, "From:".$from."\n");

// if ($result != 0) {
// 	echo '<h1>Error:</h1>';
// 	echo '<p>Your message could not be encrypted.</p>';
// 	echo '<p>It has not ben sent.</p>';
// 	echo '<p>Sorry.</p>';
// }
?>
