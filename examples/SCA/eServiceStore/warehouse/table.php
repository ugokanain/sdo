<?php
/*
+-----------------------------------------------------------------------------+
| (c) Copyright IBM Corporation 2006, 2007                                    |
| All Rights Reserved.                                                        |
+-----------------------------------------------------------------------------+
| Licensed under the Apache License, Version 2.0 (the "License"); you may not |
| use this file except in compliance with the License. You may obtain a copy  |
| of the License at -                                                         |
|                                                                             |
|                   http://www.apache.org/licenses/LICENSE-2.0                |
|                                                                             |
| Unless required by applicable law or agreed to in writing, software         |
| distributed under the License is distributed on an "AS IS" BASIS, WITHOUT   |
| WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.            |
| See the License for the specific language governing  permissions and        |
| limitations under the License.                                              |
+-----------------------------------------------------------------------------+
| Authors: Graham Charters, Matthew Peters                                    |
|                                                                             |
+-----------------------------------------------------------------------------+
$Id$
*/

function table_start() {
	print '<table border="0">';
}

function table_end() {
	print '</table>';
}

function table_row_start() {
	print '<tr>';
}

function table_row_end() {
	print '</tr>';
}

function table_cell($s, $c="#FFFFFF") {
	if (strlen($s) == 0) {
	    print "<td bgcolor=$c>&nbsp;</td>";
	} else {
	    print "<td bgcolor=$c>".$s."</td>";
	}
}

?>
