/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 *   
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/* $Rev: 241789 $ $Date: 2007-08-25 00:50:26 +0930 (Sat, 25 Aug 2007) $ */

#ifndef _XMLDocumentImpl_H_
#define _XMLDocumentImpl_H_

#include "commonj/sdo/disable_warn.h"

#include "commonj/sdo/XMLDocument.h"
#include "commonj/sdo/DataObject.h"
#include "commonj/sdo/SDOXMLString.h"
#include "commonj/sdo/SDOString.h"


namespace commonj
{
    namespace sdo
    {
        
/**  XMLDocumentImpl place for holding a graph
 *
 * The XMLDocumentImpl class implements the abstract XMLDocument.
 * Provides a place to hold a loaded
 * graph of data. The root element name is maintained here so that
 * the graph can be serialized to the same name later.
 */
        
        class XMLDocumentImpl : public XMLDocument
        {
            
        public:
            XMLDocumentImpl();
            
            XMLDocumentImpl(
                DataObjectPtr dataObject);

            XMLDocumentImpl(
                DataObjectPtr dataObject,
                const char* rootElementURI,
                const char* rootElementName);

            virtual ~XMLDocumentImpl();
            
            virtual DataObjectPtr getRootDataObject() const {return dataObject;}
            virtual const char* getRootElementURI() const {return rootElementURI;}
			virtual const char* getRootElementName() const {return rootElementName;}
            virtual const char* getEncoding() const {return encoding;}
            virtual void setEncoding(const char* enc);
            virtual void setEncoding(const SDOString& enc);

            virtual bool getXMLDeclaration() const {return xmlDeclaration;}
            virtual void setXMLDeclaration(bool xmlDecl);

            virtual const char* getXMLVersion() const {return xmlVersion;}
            virtual void setXMLVersion(const char* xmlVer);
            virtual void setXMLVersion(const SDOString& xmlVer);

            virtual const char* getSchemaLocation() const {return schemaLocation;}
            virtual void setSchemaLocation(const char* schemaLoc);
            virtual void setSchemaLocation(const SDOString& schemaLoc);

            virtual const char* getNoNamespaceSchemaLocation() const { return noNamespaceSchemaLocation;}
            virtual void setNoNamespaceSchemaLocation(const char* noNamespaceSchemaLoc);
            virtual void setNoNamespaceSchemaLocation(const SDOString& noNamespaceSchemaLoc);
            
            
            friend std::istream& operator>>(std::istream& input, XMLDocumentImpl& doc);
        private:
            DataObjectPtr   dataObject;
            SDOXMLString    rootElementURI;
            SDOXMLString    rootElementName;
            SDOXMLString    encoding;
            bool            xmlDeclaration;
            SDOXMLString    xmlVersion;
            SDOXMLString    schemaLocation;
            SDOXMLString    noNamespaceSchemaLocation;

            
        };
    } // End - namespace sdo
} // End - namespace commonj


#endif //_XMLDocumentImpl_H_
