<?php
/* 
+----------------------------------------------------------------------+
| (c) Copyright IBM Corporation 2005.                                  |
| All Rights Reserved.                                                 |
+----------------------------------------------------------------------+
|                                                                      |
| Licensed under the Apache License, Version 2.0 (the "License"); you  |
| may not use this file except in compliance with the License. You may |
| obtain a copy of the License at                                      |
| http://www.apache.org/licenses/LICENSE-2.0                           |
|                                                                      |
| Unless required by applicable law or agreed to in writing, software  |
| distributed under the License is distributed on an "AS IS" BASIS,    |
| WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or      |
| implied. See the License for the specific language governing         |
| permissions and limitations under the License.                       |
+----------------------------------------------------------------------+
| Author: Matthew Peters                                               |
+----------------------------------------------------------------------+

*/


/***********************************************************************
 * You need to fix up and enable three defines below. 
 * Enter meaningful values, then remove the  
 * echos **AND THE ASSERT**!!! 
 **********************************************************************/
echo "\n";
echo "\n";
echo "\n";
echo "          ***********************************************************\n";
echo "          ***********************************************************\n";
echo "          ***********************************************************\n";
echo "\n";
echo "          You need to supply a PDO data source name, a database username,";
echo "          and a password in SDO/DAS/Relational/Scenarios/company_metadata.inc.php\n";
echo "\n";
echo "          ***********************************************************\n";
echo "          ***********************************************************\n";
echo "          ***********************************************************\n";
echo "\n";
echo "\n";
echo "\n";

assert(false); // remove this once you have meaningful defines 

// this one works with MySQL
//define ('PDO_DSN','mysql:dbname=companydb;host=localhost');
//define('DATABASE_USER','YOUR USERID - root, maybe?');
//define ('DATABASE_PASSWORD','YOUR PASSWORD HERE');

// this one works with IBM DB2
//define ('PDO_DSN','odbc:company');
//define('DATABASE_USER','YOUR USERID');
//define ('DATABASE_PASSWORD','YOUR PASSWORD HERE');


/*****************************************************************
* METADATA DEFINING THE DATABASE
* See companydb_mysql.sql for how the database might be defined to MySQL
* See companydb_db2.sql for how the database might be defined to DB2
******************************************************************/

$company_table = array (
	'name' => 'company',
	'columns' => array('id', 'name',  'employee_of_the_month'),
	'PK' => 'id',
	'FK' => array (
		'from' => 'employee_of_the_month',
		'to' => 'employee',
		),
	);
$department_table = array (
	'name' => 'department', 
	'columns' => array('id', 'name', 'location' , 'number', 'co_id'),
	'PK' => 'id',
	'FK' => array (
		'from' => 'co_id',
		'to' => 'company',
		)
	);
$employee_table = array (
	'name' => 'employee',
	'columns' => array('id', 'name', 'SN', 'manager', 'dept_id'),
	'PK' => 'id',
	'FK' => array (
		'from' => 'dept_id',
		'to' => 'department',
		)
	);
$database_metadata = array($company_table, $department_table, $employee_table);

/*******************************************************************
* METADATA DEFINING SDO CONTAINMENT REFERENCES
*******************************************************************/
$department_reference = array( 'parent' => 'company', 'child' => 'department');
$employee_reference = array( 'parent' => 'department', 'child' => 'employee');

$SDO_reference_metadata = array($department_reference, $employee_reference);


?>
