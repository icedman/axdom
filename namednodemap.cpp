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

#include <dom/namednodemap.h>
#include <dom/nodelist.h>
#include <dom/domnode.h>

namespace Dom
{
	DOMNode* NamedNodeMap::setNamedItem(DOMNode* arg)
	{
		DOMNode *n = (DOMNode*)removeNamedItem(arg->getNodeName());
		if (n)
			n->release();

		if (appendChild(arg))
			return arg;
		return 0;
	}

	DOMNode* NamedNodeMap::getNamedItem(const DOMString* name)
	{
		DOMNode *n = getFirstChild();
		while(n)
		{
			if (stricmp((DOMCHAR*)n->getNodeName(), (DOMCHAR*)name) == 0)
			{
				return n;
			}
			n = n->getNextSibling();
		}
		return 0;
	}

	DOMNode* NamedNodeMap::removeNamedItem(const DOMString* name)
	{
		DOMNode *n = getNamedItem(name);
		if (n)
		{
			return removeChild(n);
		}
		return 0;
	}

	DOMNode* NamedNodeMap::getNamedItemNS(const DOMString* namespaceURI, const DOMString* localName)
	{
		return 0;
	}

	DOMNode* NamedNodeMap::setNamedItemNS(DOMNode* arg)
	{
		return 0;
	}

	DOMNode* NamedNodeMap::removeNamedItemNS(const DOMString* namespaceURI, const DOMString* localName)
	{
		return 0;
	}

}
