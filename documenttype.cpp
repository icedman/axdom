/*
Version: MPL 1.1/GPL 2.0/LGPL 2.1

The contents of this file are subject to the Mozilla Public License Version
1.1 (the "License"); you may not use this file except in compliance with
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

#include <dom/documenttype.h>

namespace Dom
{
	const DOMString* DocumentType::getName()
	{
		return getNodeName();
	}

	NamedNodeMap* DocumentType::getEntities()
	{
		return 0;
	}

	NamedNodeMap* DocumentType::getNotations()
	{
		return 0;
	}

	const DOMString* DocumentType::getPublicId()
	{
		return 0;
	}

	const DOMString* DocumentType::getSystemId()
	{
		return 0;
	}

	const DOMString* DocumentType::getInternalSubset()
	{
		return 0;
	}

	DocumentType::DocumentType()
	{
		nodeType = DOCUMENT_TYPE_NODE;
	}
}

