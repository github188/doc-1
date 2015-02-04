<html>
<head>
<title>Uploading...</title>
</head>
<body>
<h1>Uploading file...<h1>
<?php
if ($_FILES['userfile']['error'] > 0) {
	echo 'Problem:';
	switch ($_FILES['userfile']['error']) {
	case 1: echo 'File exceeded upload_max_filesize';
		break;
	case 2: echo 'File exceeded max_file_size';
		break;
	case 3: echo 'File only partially uploaded';
		break;
	case 4: echo 'No file uploaded';
		break;
	case 6: echo 'Cannot upload file: No temp directory specified';
		break;
	case 7: echo 'Upload failed: Cannot write to disk';
		break;
	}
	exit;
}

if ($_FILES['userfile']['type'] != 'text/plain' && $_FILES['userfile']['type'] != 'text/x-csrc') {
	echo 'Problem: file is no plain text';
	exit;
 }


$upfile = './upload/'.$_FILES['userfile']['name'];
if (is_uploaded_file($_FILES['userfile']['tmp_name'])) {
	if (!move_uploaded_file($_FILES['userfile']['tmp_name'], $upfile)) {
		echo 'Problem: Could not move file to destination directory';
		exit;
	}
} else {
	echo 'Problem: Possible file upload attack Filename: ';
	echo $_FILES['userfile']['name'];
	exit;
}

echo 'File uploaded Successfully<br><br>';

$contents = file_get_contents($upfile);
$contents = strip_tags($contents);
file_put_contents($_FILES['userfile']['name'], $contents);

echo '<p>Preview of uploaded file contents:<br/><hr/>';
echo nl2br($contents);
echo '<br/><hr/>';
?>
</body>
</html>