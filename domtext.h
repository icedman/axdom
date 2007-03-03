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

#ifndef AX_DOMTEXT
#define AX_DOMTEXT

#include <dom/domcfg.h>
#include <dom/characterdata.h>

namespace Dom
{
	class DOM_CLASS_EXPORT DOMText : public CharacterData
	{
	public: 
		DOMText* splitText(unsigned int offset) { return 0; }

		DOMText()
		{
			nodeName = "#text";
			nodeType = TEXT_NODE;
		}

		DOMText(const DOMString* data)
		{
			nodeName = "#text";
			nodeValue = (DOMCHAR*)data;
			nodeType = TEXT_NODE;
		}

		DOMText(DOMText *t)
		{
			nodeType = (NodeType)t->getNodeType();
			nodeName = (DOMCHAR*)t->getNodeName();
			nodeValue = (DOMCHAR*)t->getNodeValue();
		}
	}; 
}

#endif
