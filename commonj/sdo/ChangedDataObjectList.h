#ifndef _CHANGEDDATAOBJECTLIST_H_
#define _CHANGEDDATAOBJECTLIST_H_

#include "commonj/sdo/RefCountingPointer.h"
/* 
+----------------------------------------------------------------------+
| (c) Copyright IBM Corporation 2005.                                  | 
| All Rights Reserved.                                                 |
+----------------------------------------------------------------------+ 
|                                                                      | 
| Licensed under the Apache License, Version 2.0 (the "License"); you  | 
| may not use this file except in compliance with the License. You may | 
| obtain a copy of the License at                                      | 
|  http://www.apache.org/licenses/LICENSE-2.0                          |
|                                                                      | 
| Unless required by applicable law or agreed to in writing, software  | 
| distributed under the License is distributed on an "AS IS" BASIS,    | 
| WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or      | 
| implied. See the License for the specific language governing         | 
| permissions and limitations under the License.                       | 
+----------------------------------------------------------------------+ 
| Author: Ed Slattery                                                  | 
+----------------------------------------------------------------------+ 

*/
/* $Id$ */

#include <vector>
namespace commonj{
namespace sdo{

class DataObject;


class ChangedDataObjectList
{

public:
	enum ChangeType
	{
		Undefined,
		Create,
		Change,
		Delete
	};


	virtual SDO_API DataObjectPtr operator[] (int pos) = 0;

	virtual SDO_API const DataObjectPtr operator[] (int pos) const = 0;

	virtual SDO_API int size () const = 0;

    virtual SDO_API ChangeType getType(unsigned int index) = 0;


};
};
};
#endif

