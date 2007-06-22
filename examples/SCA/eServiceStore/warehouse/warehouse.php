<html>

  <title>Warehouse Order Processing</title>
  
<body>
<p>
<form method=POST action="warehouse.php">
<input type=submit name="status" value="Refresh Orders"/>
</form> 
</p>
<p>
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
  include_once "display_orders.php";

  echo "<b>Orders to be dispatched:</b><br/><br/>";
  display_orders('NONE');

  echo "<b><br/>Dispatched orders:</b><br/><br/>";
  display_orders('DISPATCHED');
  
?>
</p>
</body>
</html>
