--TEST--
qrencode() function
--SKIPIF--
<?php 

if(!extension_loaded('qrencode')) die('skip');

 ?>
--FILE--
<?php
echo 'OK'; // no test case for this function yet
?>
--EXPECT--
OK