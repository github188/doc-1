<?php
session_start();

echo 'the content of $_SESSION[\'sess_var\'] is '.$_SESSION['sess_var'].'<br />';

unset($_SESSION['sess_var']);

echo 'the content of $_SESSION[\'sess_var\'] is '.$_SESSION['sess_var'].'<br />';

?>
<a href="page3.php">Next page</a>