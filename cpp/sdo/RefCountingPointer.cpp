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

#include "RefCountingPointer.h"
#include "DataFactory.h"
#include "DataObject.h"
#include "DataGraph.h"
#include "ChangeSummary.h"
#include "XMLDocument.h"
#include "XSDHelper.h"
#include "XMLHelper.h"

namespace commonj{
	namespace sdo{
		
		// officially, there is nothing here- but if I dont use the overrides in
		// the templates, then they dont get generated.
		void Test ()
		{
			
#ifndef __linux__
			/* 1) construct */
			DataFactoryPtr fptr = DataFactory::getDataFactory();
			
			/* 2) use the & operator= */
			fptr = DataFactory::getDataFactory();
			
			/* 3) copy */
			DataFactoryPtr fptr2 = fptr;
			
			/* 4) use the == and ! */
			if (fptr2 == fptr || !fptr){}
			
			/* 5) Use the T*  and  * */
			DataFactory* dmsf = fptr;
			DataFactory& dmsr = *fptr;
			
			/* 1) construct */
			DataFactoryPtr dfptr(fptr);
			
			/* 3) copy */
			DataFactoryPtr dfptr2 = dfptr;
			
			/* 2) use the & operator= */
			dfptr = dfptr2;
			
			/* 4) use the == and ! */
			if (dfptr2 == dfptr || !dfptr){}
			
			/* 5) Use the T*  and  * */
			DataFactory* ddmsf = dfptr;
			DataFactory& ddmsr = *dfptr;
			
			/* 6) Use the -> */
			DataObjectPtr dptr = dfptr->create("nothing","nowhere"); 
			
			/* and agin to catch the = */
			dptr = fptr->create("nothing","nowhere");
			
			DataObjectPtr dptr2 = dptr;
			
			/* Use the T*  and  * */
			DataObject* dof = dptr;
			DataObject& dor = *dptr;
			
			if (dptr2 == dptr || !dptr){}
			
			
			ChangeSummaryPtr cptr = dptr->getChangeSummary();
			cptr = dptr->getChangeSummary();
			ChangeSummaryPtr cptr2 = cptr;
			
			ChangeSummary* cof = cptr;
			ChangeSummary& cop = *cptr;
			
			
			if (cptr2 == cptr || !cptr){}
			
			cptr->endLogging();
			
			SequencePtr sptr = dptr->getSequence();
			sptr = dptr->getSequence();
			SequencePtr sptr2 = sptr;
			
			Sequence* sof = sptr;
			Sequence& sop = *sptr;
			
			
			if (sptr2 == sptr || !sptr){}
			
			sptr->getBooleanValue(0);
			
			
			// Generate code for XMLDocumentPtr
			XMLDocumentPtr xmldocptr1 = 0;
			XMLDocumentPtr xmldocptr2 = xmldocptr1;
			xmldocptr1 = xmldocptr2;
			if (xmldocptr2 == xmldocptr1 || !xmldocptr1){}
			XMLDocument* xmldocp = xmldocptr1;
			XMLDocument& xmldocref = *xmldocptr2;
			xmldocptr1->getEncoding();

			// Generate code for XSDHelperPtr
			XSDHelperPtr xsdhptr1 = 0;
			XSDHelperPtr xsdhptr2 = xsdhptr1;
			xsdhptr1 = xsdhptr2;
			if (xsdhptr2 == xsdhptr1 || !xsdhptr1){}
			XSDHelper* xsdhp = xsdhptr1;
			XSDHelper& xsdhref = *xsdhptr2;
			xsdhptr1->define("dummy");

			// Generate code for XMLHelperPtr
			XMLHelperPtr xmlhptr1 = 0;
			XMLHelperPtr xmlhptr2 = xmlhptr1;
			xmlhptr1 = xmlhptr2;
			if (xmlhptr2 == xmlhptr1 || !xmlhptr1){}
			XMLHelper* xmlhp = xmlhptr1;
			XMLHelper& xmlhref = *xmlhptr2;
			xmlhptr1->load("dummy");

			// Generate code for DataGraphPtr
			DataGraphPtr dgptr1 = 0;
			DataGraphPtr dgptr2 = dgptr1;
			dgptr1 = dgptr2;
			if (dgptr2 == dgptr1 || !dgptr1){}
			DataGraph* dghp = dgptr1;
			DataGraph& dgref = *dgptr2;
			dgptr1->getRootObject();

#endif
			
		}
	};
};


