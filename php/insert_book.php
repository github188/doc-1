<html>
  <head>
    <title>Book-O-Rama Book Entry Results</title>
  </head>
  <body>
    <h1>Book-O-Rama BOok Entry Results</h1>
<?php
// create short variable names
$isbn = $_POST['isbn'];
$author = $_POST['author'];
$title = $_POST['title'];
$price = $_POST['price'];

//echo "".$isbn." ".$author." ".$title." ".$price;
if (!$isbn || !$author || !$title || !$price) {
	echo "You have not entered all the required details. <br /".
		"Please go back and try again.";
	exit;
}

if (!get_magic_quotes_gpc()) {
	$isbn = addslashes($isbn);
	$author = addslashes($author);
	$title = addslashes($title);
	$price = doubleval($price);
}

@ $db = new mysqli('localhost', 'lyt', 'lyt', 'books');

if (mysqli_connect_errno()) {
	echo "Error: Could not connect to database. Please try again later.";
	exit;
}

/*$query = "insert into books values
	('".$isbn."', '".$author."', '".$title."', '".$price."')";
//echo "".$query."<br />";
$result = $db->query($query);
*/
$query = "insert into books values(?, ?, ?, ?)";
$stmt = $db->prepare($query);
$stmt->bind_param("sssd", $isbn, $author, $title, $price);
$stmt->execute();
echo $stmt->affected_rows.' book inserted into database.';
$stmt->close();

/*
if ($result) {
	echo $db->affected_rows." book inserted into databases.";
} else {
	echo "An error has occurred .The item was not added.";
}
*/
$db->close();
       ?>
</body>
</html>
