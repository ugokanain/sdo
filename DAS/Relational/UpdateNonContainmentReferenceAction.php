<?
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

require_once 'SDO/DAS/Relational/DataObjectHelper.php';

class SDO_DAS_Relational_UpdateNonContainmentReferenceAction extends SDO_DAS_Relational_Action {
	
	/**
	* execute self
	*/
	private $from_who;
	private $property_name;
	private $who_to;
	
	public function __construct($object_model, $from_who, $property_name, $who_to) 
	{
		// TODO this looks a bit odd - yet can;t call parent constructor as no $do		
		$this->object_model = $object_model;
		$this->from_who = $from_who;
		$this->property_name = $property_name;
		$this->who_to = $who_to;
	}
	
	public function execute($dbh) 
	{	
		$pk_from 	= SDO_DAS_Relational_DataObjectHelper::getPrimaryKeyFromDataObject($this->object_model,$this->from_who);
		$pk_to 		= SDO_DAS_Relational_DataObjectHelper::getPrimaryKeyFromDataObject($this->object_model,$this->who_to);
		$type_name 	= SDO_DAS_Relational_DataObjectHelper::getApplicationType($this->from_who);
		$str 	=  "UPDATE $type_name set $this->property_name = " ;
		$str 	.= '"' . $pk_to . '"' ;
		$str 	.= ' where ';
		$name_of_the_pk_column = $this->object_model->getPropertyRepresentingPrimaryKeyFromType($type_name);
		$str 	.= $name_of_the_pk_column . '=' . $pk_from;
		$this->executeStatement($dbh,$str);
	}
	
	public function toString() 
	{
		return '[UpdateNonContainmentReference: ' . $this->type_name . ': ' . $this->property_name . ']';
	}
}

?>