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

echo "executing scenario one-company-create/retrieve/update\n";

require_once 'SDO/DAS/Relational.php';
require_once 'company_metadata.inc.php';


/*************************************************************************************
 * Use SDO to perform create, retrieve and update operations on a row of the company table.
 * 
 * See companydb_mysql.sql and companydb_db2.sql for examples of defining the database 
 *************************************************************************************/

/*************************************************************************************
 * Empty out the company table
 *************************************************************************************/
$dbh = new PDO(PDO_DSN,DATABASE_USER,DATABASE_PASSWORD);
$count = $dbh->exec('DELETE FROM company;');

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
 * Create the root data object then a single company object underneath it. 
 * Set the company name to 'Acme'.
 *************************************************************************************/
$root 		= $das  -> createRootDataObject();
$company 	= $root -> createDataObject('company');
$company -> name = "Acme";
writeBack($das,$company);
echo "Created a company with name Acme and wrote it to the database\n";

/*************************************************************************************
 * Find it again (with its autogenerated id this time).
 * Now update it and write it back again.
 *************************************************************************************/
$company2 = findCompany($das,'Acme');
echo "Looked for Acme and found company with name = " . $company2->name . " and id " . $company2->id . "\n";
$company2->name = 'MegaCorp';
writeBack($das,$company2);
echo "Wrote back Acme with name changed to MegaCorp\n";

/*************************************************************************************
 * Find it again under its new name.
 *************************************************************************************/
$company3 = findCompany($das,'Megacorp');
echo "Looked for MegaCorp and found company with name = " . $company3->name . " and id " . $company3->id . "\n";


/*************************************************************************************
 * Function to issue executeQuery() to the DAS
 *
 * We could reuse a connection but in this case we get a new one to illustrate the
 * disconnected nature of the data graph.
 * 
 * Since we want to put a variable into the SQL, use the prepared statement interface
 * and a placeholder to ensure invalid SQL cannot be injected, regardless of what is 
 * passed in $name. 
 * 
 * After getting the root object we get and return the first company object underneath it.
 *************************************************************************************/
function findCompany($das,$name) {
	$dbh = new PDO(PDO_DSN,DATABASE_USER,DATABASE_PASSWORD);
	try {
		$pdo_stmt = $dbh->prepare('select name, id from company where name=?');
		$root = $das->executePreparedQuery($dbh, $pdo_stmt ,array($name), array('company.name', 'company.id'));
	} catch (SDO_DAS_Relational_Exception $e) {
		echo "SDO_DAS_Relational_Exception raised when trying to retrieve data from the database.";
		echo "Probably something wrong with the SQL query.";
		echo "\n".$e->getMessage();
		exit();
	}
	return $root['company'][0];
}

/*************************************************************************************
 * Function to issue applyChanges() to the DAS.
 *
 * We could reuse a connection but in this case we get a new one to illustrate the
 * disconnected nature of the data graph.
 *************************************************************************************/
function writeBack($das, $data_object) {
	$dbh = new PDO(PDO_DSN,DATABASE_USER,DATABASE_PASSWORD);
	try {
		$das -> applyChanges($dbh, $data_object);
	} catch (SDO_DAS_Relational_Exception $e) {
		echo "\nSDO_DAS_Relational__Exception raised when trying to apply changes.";
		echo "\nProbably something wrong with the data graph.";
		echo "\n".$e->getMessage();
		exit();
	}
}



?>
