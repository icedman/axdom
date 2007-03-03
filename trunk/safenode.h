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

#ifndef AX_SAFENODE
#define AX_SAFENODE

#include <dom/domnode.h>

namespace Dom
{
	//! Safe DOM node query class
	class DOM_CLASS_EXPORT SafeNode
	{
	public:
		SafeNode();
		SafeNode(DOMNode *e);
		~SafeNode();

		bool attach(DOMNode *e);
		bool attach(NodeList *n);

		void detach();
		void detachNodes();

		//! Calls NodeList->Item()
		SafeNode* item(int index);
		//! Calls NodeList->Length();
		int getLength() { if (nodes) return nodes->getLength(); return 0; }
		//! Finds a child element. Call GetDOMNodesByTagName()
		SafeNode* getElement(const DOMString *tagName);
		//! Finds an attribute of an element
		SafeNode* getAttribute(const DOMString *name);
		//! Finds an attribute of an element or and child element of the same name
		SafeNode* getValue(const DOMString *name);
		//! Gets the nodeName of a resulting query
		const DOMString* getNodeName();
		//! Gets the nodeValue of a resulting query
		const DOMString* getNodeValue(const DOMString *defaultValue = 0);
		//! Gets the integer value of a resulting query
		int getNodeValueInt(int defaultValue);
		//! Gets the DOMNode of a resulting query
		DOMNode* getNode();

		SafeNode* getElement(const char *tagName) { return getElement(DOMSTR tagName); }
		SafeNode* getAttribute(const char *name) { return getAttribute(DOMSTR name); }
		SafeNode* getValue(const char *name) { return getValue(DOMSTR name); }

	private:
		SafeNode *explorer;
		DOMNode *element;
		NodeList *nodes;

	};

}

#endif