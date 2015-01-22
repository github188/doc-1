<html>
<head>
<title>Bob's Auto Parts - Order Results</title>
</head>
<body>
	<h1>Bob's Auto Parts</h1>
<h2>Order Results</h2>
<?php
echo "<p>Order processed at";
echo date('H:i, jS F Y');
echo "</p>";

$tireqty = $_POST['tireqty'];
$oilqty = $_POST['oilqty'];
$sparkqty = $_POST['sparkqty'];
echo "<p>Your order is as follows: </p>";
echo $tireqty. ' tires <br />';
echo $oilqty. ' bottles of oil <br />';
echo $sparkqty. ' spark plugs <br /><br/>';
$totalqty = 0;
$totalamount = 0.00;
define('TIREPRICE', 200);
define('OILPRICE', 10);
define('SPARKPRICE', 4);
$totalqty = $tireqty + $oilqty + $sparkqty;
echo "Items ordered: ".$totalqty."<br />";
$totalamount= $tireqty * TIREPRICE
        + $oilqty * OILPRICE
	+ $sparkqty * SPARKPRICE;
echo "Subtotal: $".number_format($totalamount, 2)."<br />";
$taxrate = 0.10;
$totalamount = $totalamount * (1+$taxrate);
echo "Total including tax: $".number_format($totalamount,2)."<br />";
echo gettype($taxrate).'<br />';
echo 'isset($tireqty):'.isset($tireqty).'<br />';
echo 'isset($nothere):'.isset($nothere).'<br />';
echo 'empty($tireqty):'.empty($tireqty).'<br />';
echo 'empty($nothere):'.empty($nothere).'<br />';
$find = $_POST['find'];
switch($find) {
case "a" :
	echo '<p>Regular</p>';
	break;
case "b":
	echo "<p>Customer by TV</p>";
	break;
case "c":
	echo "<p>phone directory</p>";
	break;
case "d":
	echo "<p>word of mouth</p>";
	break;
default:
	echo "<p>we don't know how this customer found us</p>";
	break;
}
?>
</body>
</html>
