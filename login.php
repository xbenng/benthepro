<?php
session_start();
if(isset($_SESSION['session']))
{
	header('Location: lights.php');
	die();
}
if(isset($_POST['submit']))
{
	if($_POST['password'] == 'passworod')
	{
	$_SESSION['session'] = TRUE;
	header('Location: lights.php');
	die();
	}
}
?>
<form action="login.php" method="post">
	<input type="password" name="password">
	<input type="submit" name="submit" value="login">
</form>