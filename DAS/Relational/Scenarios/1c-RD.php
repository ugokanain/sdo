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

require_once 'SDO/DAS/Relational.php';
require_once 'company_metadata.inc.php';


/*************************************************************************************
* Use SDO to retrieve then delete row of the company table.
*
* See companydb_mysql.sql and companydb_db2.sql for examples of defining the database 
*************************************************************************************/

/*************************************************************************************
 * Get and initialise a DAS with the metadata
*************************************************************************************/
try {
	$das = new SDO_DAS_Relational ($database_metadata,'company',$SDO_reference_metadata);
} catch (SDO_DAS_Relational_Exception $e) {
	echo "SDO_DAS_Relational_Exception raised when trying to create the DAS.";
	echo "Probably something wrong with the metadata.";
	echo "\n".$e->getMessage();
	exit();
}

/*************************************************************************************
* Find the company or companies and delete
*************************************************************************************/
$dbh = new PDO(PDO_DSN,DATABASE_USER,DATABASE_PASSWORD);
try {
	$root = $das->executeQuery($dbh,
	"select name, id from company where name='Acme'",
	array('company.name', 'company.id', 'company.employee_of_the_month'));
} catch (SDO_DAS_Relational_Exception $e) {
	echo "SDO_DAS_Relational_Exception raised when trying to retrieve data from the database.";
	echo "Probably something wrong with the SQL query.";
	echo "\n".$e->getMessage();
	exit();
}
foreach($root['company'] as $acme) {
	echo "Looked for Acme and found company with name = " . $acme->name . " and id " . $acme->id . "\n";
}

unset($root['company']);

$dbh = new PDO(PDO_DSN,DATABASE_USER,DATABASE_PASSWORD);
try {
	$das -> applyChanges($dbh, $root);
} catch (SDO_DAS_Relational_Exception $e) {
	echo "\nSDO_DAS_Relational_Exception raised when trying to apply changes.";
	echo "\nProbably something wrong with the data graph.";
	echo "\n".$e->getMessage();
	exit();
}
echo "Deleted all companies called Acme\n";

?>
