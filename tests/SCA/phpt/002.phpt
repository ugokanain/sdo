--TEST--
Call a remote component with a simple scalar type (string)
--SKIPIF--
<?php 
if (!extension_loaded("sdo")) 
    echo "skip sdo not loaded"; 
else if (phpversion('sdo') <= '1.2.2')
    echo "skip test until pecl bug 11388 resolved";
?>
--FILE--
<?php

$HTTP_RAW_POST_DATA = <<<EOF
<?xml version="1.0" encoding="UTF-8"?>
<SOAP-ENV:Envelope xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/" xmlns:ns1="http://Component"><SOAP-ENV:Body><ns1:reverse xmlns="http://Component" xmlns:tns="http://Component" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:type="reverse">
  <in>IBM</in>
</ns1:reverse></SOAP-ENV:Body></SOAP-ENV:Envelope>


EOF;

require "SCA/SCA.php";
$component_file = dirname(__FILE__).'/Component.php';

// make it look to the component as if it is on the receiving end of a SOAP request
$_SERVER['HTTP_HOST'] = 'localhost';
$_SERVER['REQUEST_METHOD'] = 'POST';
$_SERVER['SCRIPT_FILENAME'] = $component_file;
$_SERVER['CONTENT_TYPE'] = 'application/soap+xml';

require_once "$component_file";

?>
--EXPECT--
<?xml version="1.0" encoding="UTF-8"?>
<SOAP-ENV:Envelope xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/" xmlns:ns1="http://Component"><SOAP-ENV:Body><ns1:reverseResponse xmlns="http://Component"><reverseReturn>MBI</reverseReturn></ns1:reverseResponse></SOAP-ENV:Body></SOAP-ENV:Envelope>