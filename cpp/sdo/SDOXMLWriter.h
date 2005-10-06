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
| Author: Pete Robbins                                                 | 
+----------------------------------------------------------------------+ 

*/
/* $Id$ */

#ifndef _SDOXMLWRITER_H_
#define _SDOXMLWRITER_H_

#pragma warning(disable: 4786)
#include <libxml/xmlwriter.h>
#include "XMLDocument.h"
#include "SDOXMLString.h"
#include "SchemaInfo.h"
#include "DataFactory.h"
#include "XSDPropertyInfo.h"
#include <stack>
#include "SAX2Namespaces.h"

namespace commonj
{
	namespace sdo
	{
			
		class SDOXMLWriter
		{
			
		public:
			
			SDOXMLWriter(DataFactoryPtr dataFactory = NULL);
			
			virtual ~SDOXMLWriter();
			
			int write(XMLDocumentPtr doc);

		protected:
			void setWriter(xmlTextWriterPtr textWriter);
			void freeWriter();
			
		private:
			xmlTextWriterPtr writer;

			void handleChangeSummaryAttributes(
				ChangeSummaryPtr cs,
				DataObjectPtr doB);

			void handleChangeSummaryElements(
				ChangeSummaryPtr cs, 
				DataObjectPtr dob);

			void handleChangeSummaryDeletedObject(
				const char* name, 
				ChangeSummaryPtr cs, 
				DataObjectPtr dob);

			void handleSummaryChange(
				const SDOXMLString& elementName, 
			    ChangeSummaryPtr cs, 
				DataObjectPtr dob);

			void handleChangeSummary(
				const SDOXMLString& elementName,
			    ChangeSummaryPtr cs);


			int writeDO(
				DataObjectPtr dataObject,
				const SDOXMLString& elementURI,
				const SDOXMLString& elementName,
				bool writeXSIType = false);

			SchemaInfo* schemaInfo;
			DataFactoryPtr	dataFactory;

			XSDPropertyInfo* getPropertyInfo(const Type& type, const Property& property);
			
			std::stack<SDOXMLString>	namespaceUriStack;

			SAX2Namespaces namespaces;
			

			void writeReference(
				DataObjectPtr dataObject, 
				const Property& property,
				bool isElement,
				DataObjectPtr refferedToObject = 0);

		};
	} // End - namespace sdo
} // End - namespace commonj


#endif //_SDOXMLWRITER_H_