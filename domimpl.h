/*
Version: MPL 1.1/GPL 2.0/LGPL 2.1

The contents of this file are subject to the Mozilla Public License Version
1.1 (the "License")=0; you may not use this file except in compliance with
the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
for the specific language governing rights and limitations under the
License.

Copyright 2007
Marvin Sanchez
http://code.google.com/u/m4rvin2005/
*/

#ifndef AX_DOMIMPLEMENTATION
#define AX_DOMIMPLEMENTATION

#include <dom/domcfg.h>
#include <dom/domstring.h>
#include <dom/documenttype.h>

namespace Dom
{
	class DOM_CLASS_EXPORT DOMImplementation
	{	
	public:
		bool hasFeature(const DOMString* feature, const DOMString* version);
		/*
		DocumentType* createDocumentType(const DOMString* qualifiedName,
		const DOMString* publicId,
		const DOMString* systemId);
		Document* createDocument(const DOMString* namespaceURI,
		const DOMString* qualifiedName,
		DocumentType* doctype);
		*/

		DOMImplementation();
	}; 

}
#endif
