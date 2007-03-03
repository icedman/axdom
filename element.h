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

#ifndef AX_ELEMENT
#define AX_ELEMENT

#include <dom/domcfg.h>
#include <dom/domnode.h>
#include <dom/attribute.h>
#include <dom/nodelist.h>
#include <dom/namednodemap.h>

namespace Dom
{
	class Attribute;

	class DOM_CLASS_EXPORT Element : public DOMNode
	{
	public: 
	
		const DOMString* getTagName();
		const DOMString* getAttribute(const DOMString* name);
		Attribute* getAttributeNode(const DOMString* name);
		NodeList* getElementsByTagName(const DOMString* name);
		void setAttribute(const DOMString* name, const DOMString* value);
		Attribute* setAttributeNode(Attribute *newAttr);
		Attribute* removeAttributeNode(Attribute* oldAttr);
		void removeAttribute(const DOMString* name);
		const DOMString* getAttributeNS(const DOMString* namespaceURI,
			const DOMString* localName);
		void setAttributeNS(const DOMString* namespaceURI,
			const DOMString* qualifiedName,
			const DOMString* value);
		void removeAttributeNS(const DOMString* namespaceURI,
			const DOMString* localName);
		Attribute* getAttributeNodeNS(const DOMString* namespaceURI,
			const DOMString* localName);
		Attribute* setAttributeNodeNS(Attribute* newAttr);
		NodeList* getElementsByTagNameNS(const DOMString* namespaceURI,
			const DOMString* localName);
		bool hasAttribute(const DOMString* name);
		bool hasAttributeNS(const DOMString* namespaceURI,
			const DOMString* localName);

		// implementation
		Element();
		Element(const DOMString* tagName);
		Element(Element *);
	}; 
}

#endif
