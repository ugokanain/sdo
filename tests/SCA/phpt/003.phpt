--TEST--
Call a remote component with a structured type
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
<SOAP-ENV:Envelope xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/" xmlns:ns1="http://Component"><SOAP-ENV:Body><ns1:add xmlns="http://Component" xmlns:tns="http://Component" xmlns:tns2="http://www.test.com/info" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:type="add">
  <tns2:person>
    <tns2:name>
      <first>William</first>
      <last>Shakespeare</last>
    </tns2:name>
    <tns2:address>
      <street>456 Evergreen</street>
      <city>Austin</city>
      <state>TX</state>
    </tns2:address>
  </tns2:person>
  <tns2:phone>
    <type>home</type>
    <number>123-456</number>
  </tns2:phone>
</ns1:add></SOAP-ENV:Body></SOAP-ENV:Envelope>


EOF;

require "SCA/SCA.php";
$component_file = dirname(__FILE__).'/Component.php';

// make it look to the component as if it is on the receiving end of a SOAP request
$_SERVER['HTTP_HOST'] = 'localhost';
$_SERVER['REQUEST_METHOD'] = 'POST';
$_SERVER['SCRIPT_FILENAME'] = $component_file;
$_SERVER['CONTENT_TYPE'] = 'application/soap+xml';

include "$component_file";

?>
--EXPECT--
<?xml version="1.0" encoding="UTF-8"?>
<SOAP-ENV:Envelope xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/" xmlns:ns1="http://Component"><SOAP-ENV:Body><ns1:addResponse xmlns="http://Component"><addReturn><name><first>William</first><last>Shakespeare</last></name><phone><type>home</type><number>123-456</number></phone><address><street>456 Evergreen</street><city>Austin</city><state>TX</state></address></addReturn></ns1:addResponse></SOAP-ENV:Body></SOAP-ENV:Envelope>