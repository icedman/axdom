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

#include <dom/domimpl.h>
#include <dom/document.h>

namespace Dom
{

	bool DOMImplementation::hasFeature(const DOMString* feature,
		const DOMString* version)
	{
		if (!feature)
			return false;

		double ver = 0;
		if (version)
			ver = atof((DOMCHAR*)version);

		// implements dom core 2
		if (stricmp((DOMCHAR*)feature, "core") == 0)
		{
			if (ver <= 2)
				return true;
		}

		// implements dom event model 2
		if (stricmp((DOMCHAR*)feature, "events") == 0)
		{
			if (ver <= 2)
				return true;
		}

		return false;
	}

	/*
	DocumentType* DOMImplementation::createDocumentType(const DOMString* qualifiedName,
	const DOMString* publicId,
	const DOMString* systemId);

	Document* DOMImplementation::createDocument(const DOMString* namespaceURI,
	const DOMString* qualifiedName,
	DocumentType* doctype)
	{
	}
	*/

}
