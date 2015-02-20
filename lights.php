<?php
session_start();
if (!isset($_SESSION['session']))
{
	header('Location: login.php');
	die();
}
?>
<html>

<h2>Room 410's Lights</h2>


<?php
error_reporting(E_ALL);

/* Get the port for the WWW service. */
$service_port = 4444;

/* Get the IP address for the target host. */
$address = gethostbyname('b.benthepro.me');

/* Create a TCP/IP socket. */
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket === false) {
    echo "socket_create() failed: reason: " . socket_strerror(socket_last_error()) . "\n";
} else {
}

$result = socket_connect($socket, $address, $service_port);
if ($result === false) {
    echo "socket_connect() to $address:$service_port failed.\nReason: ($result) " . socket_strerror(socket_last_error($socket)) . "\n";
} else {
}


$in = "led=?\r\n";
socket_write($socket, $in, strlen($in));
$out = '';
$out = socket_read($socket, 2048);
//echo $out;
$ledstate = $out;

if (isset($_POST['ledOn'])){
if ($ledstate == 1)
{
  $in = "led=13L";
} else {
  $in = "led=13H";
}
socket_write($socket, $in, strlen($in));
$out = '';
$out = socket_read($socket, 2048);
//echo $out;
$ledstate = $out;
}

socket_close($socket);
?>

<form action="lights.php" method="POST">
<INPUT TYPE = "Submit" NAME = "ledOn" VALUE = "<?php if($ledstate==0){echo "Turn Lights Off";}else{echo "Turn Lights On";}?>">
</form>

</html>
