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

// XMLHelperImpl.cpp: implementation of the XMLHelperImpl class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning(disable: 4786)
#include "commonj/sdo/SDOXMLFileWriter.h"   // Include first to avoid libxml compile problems!
#include "commonj/sdo/SDOXMLStreamWriter.h" // Include first to avoid libxml compile problems!
#include "commonj/sdo/SDOXMLBufferWriter.h" // Include first to avoid libxml compile problems!
#include "commonj/sdo/XMLHelperImpl.h"
#include "commonj/sdo/XMLDocumentImpl.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "commonj/sdo/SDOSAX2Parser.h"
#include "commonj/sdo/XSDPropertyInfo.h"
#include "commonj/sdo/XSDTypeInfo.h"
#include "commonj/sdo/SDORuntimeException.h"
#include "commonj/sdo/DataFactoryImpl.h"


namespace commonj
{
	namespace sdo
	{
		
		
		//////////////////////////////////////////////////////////////////////
		// Construction/Destruction
		//////////////////////////////////////////////////////////////////////
		
		XMLHelperImpl::XMLHelperImpl(DataFactoryPtr df)
		{
			dataFactory = (DataFactory*)df;
		}
		
		XMLHelperImpl::~XMLHelperImpl()
		{
			clearErrors();
		}

		DataFactoryPtr XMLHelperImpl::getDataFactory()
		{
			if (!dataFactory) 
			{
				dataFactory = DataFactory::getDataFactory();
			}
			return dataFactory;
		}

		XMLDocumentPtr XMLHelperImpl::createDocument(DataObjectPtr dataObject)
		{
			
			SDOXMLString rootElementName = "";
			SDOXMLString rootElementURI = "";
			if (dataObject)
			{
				// Set the root element name to the name of the containment property
				// or null if there is no container
   				try
				{
					DataObjectPtr cont = dataObject->getContainer();
					if (cont != 0)
					{
						const Property& containmentProp = dataObject->getContainmentProperty();
						rootElementName = containmentProp.getName();
						rootElementURI = cont->getType().getURI();
					}
					else
					{
						DataFactory* df = dataFactory;
						rootElementURI = dataObject->getType().getURI();
						rootElementName = ((DataFactoryImpl*)df)->getRootElementName();
					}
				}
				catch (SDOPropertyNotFoundException&)
				{}
			}

			return new XMLDocumentImpl(dataObject, rootElementURI, rootElementName);
		}

		XMLDocumentPtr XMLHelperImpl::createDocument(
			DataObjectPtr dataObject,
			const char* rootElementURI,
			const char* rootElementName)
		{
			return new XMLDocumentImpl(dataObject, rootElementURI, rootElementName);
		}
		
		XMLDocumentPtr XMLHelperImpl::loadFile(
			const char* xmlFile,
			const char* targetNamespaceURI)
		{
			DataObjectPtr rootDataObject;
			clearErrors();
			SDOSAX2Parser sdoParser(getDataFactory(), targetNamespaceURI, rootDataObject,
				this);
			if (sdoParser.parse(xmlFile) == 0)
			{				
				return createDocument(rootDataObject);
			}
			return 0;
		}

		
		XMLDocumentPtr XMLHelperImpl::load(
			istream& inXml,
			const char* targetNamespaceURI)
		{
			DataObjectPtr rootDataObject;
			SDOSAX2Parser sdoParser(getDataFactory(), targetNamespaceURI, rootDataObject,
				this);
			clearErrors();
			inXml>>sdoParser;
			return createDocument(rootDataObject);
		}
		
		XMLDocumentPtr XMLHelperImpl::load(
			const char* inXml,
			const char* targetNamespaceURI)
		{
			istringstream str(inXml);
            return load(str, targetNamespaceURI);
		}
		
		void XMLHelperImpl::save(XMLDocumentPtr doc, const char* xmlFile)
		{
			SDOXMLFileWriter writer(xmlFile, dataFactory);
			writer.write(doc);
		}
		
		void XMLHelperImpl::save(
			DataObjectPtr dataObject,
			const char* rootElementURI,
			const char* rootElementName,
			const char* xmlFile)
		{
			save(createDocument(dataObject,rootElementURI, rootElementName), xmlFile);
		}
		
		
		// Serializes the datagraph to a stream
		void XMLHelperImpl::save(XMLDocumentPtr doc, ostream& outXml)
		{
			SDOXMLStreamWriter writer(outXml, dataFactory);
			writer.write(doc);				
		}
		void XMLHelperImpl::save(
			DataObjectPtr dataObject,
			const char* rootElementURI,
			const char* rootElementName,
			std::ostream& outXml)
		{
			save(createDocument(dataObject,rootElementURI, rootElementName), outXml);
		}
		
		// Serializes the datagraph to a string
		char* XMLHelperImpl::save(XMLDocumentPtr doc)
		{
			SDOXMLBufferWriter writer(dataFactory);
			writer.write(doc);
			SDOXMLString ret = writer.getBuffer();
			char* retString = new char[strlen(ret) +1];
			strcpy(retString, ret);
			return retString;
		}
		char* XMLHelperImpl::save(
			DataObjectPtr dataObject,
			const char* rootElementURI,
			const char* rootElementName)
		{
			return save(createDocument(dataObject,rootElementURI, rootElementName));
		}

		int XMLHelperImpl::getErrorCount() const
		{
			return parseErrors.size();
		}


		const char* XMLHelperImpl::getErrorMessage(int errnum) const
		{
			if (errnum >= 0 && errnum < parseErrors.size())
			{
				return parseErrors[errnum];
			}
			return 0;
		}

		void XMLHelperImpl::setError(const char* message)
		{
			if (message == 0) return;
			char * m = new char[strlen(message) + 1];
			strcpy(m,message);
			m[strlen(message)] = 0;
			parseErrors.push_back(m);
		}

		void XMLHelperImpl::clearErrors()
		{
			while (!parseErrors.empty()) 
			{
				if (*parseErrors.begin() != 0)
				{
					delete (char*)(*parseErrors.begin());
				}
				parseErrors.erase(parseErrors.begin());
			}
		}
		
	} // End - namespace sdo
} // End - namespace commonj