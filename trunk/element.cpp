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

#include <dom/element.h>
#include "mutationevent.h"
#include <dom/attribute.h>

namespace Dom
{
	const DOMString* Element::getTagName()
	{
		return DOMNode::getNodeName();
	}

	const DOMString* Element::getAttribute(const DOMString* name)
	{
		Attribute *attr = (Attribute*)attributes.getNamedItem(name);
		if (attr)
			return attr->getValue();
		return 0;
	}

	Attribute* Element::getAttributeNode(const DOMString* name)
	{
		return (Attribute*)attributes.getNamedItem(name);
	}

	NodeList* Element::getElementsByTagName(const DOMString* tagName)
	{
		NodeList *bag = new NodeList();
		DOMNode *e = getFirstChild();
		while(e)
		{
			if (stricmp((char*)e->getNodeName(), (char*)tagName) == 0)
			{
				bag->appendLocalChild(e);
			}
			e = e->getNextSibling();
		}
		return bag;
	}

	void Element::setAttribute(const DOMString* name, const DOMString* value)
	{
		Attribute *attr = new Attribute(name, value);
		setAttributeNode(attr);
	}

	Attribute* Element::setAttributeNode(Attribute *newAttr)
	{
		unsigned short mod = MUTATION_ADDITION;

		std::string prev;
		Attribute *attr = (Attribute*)getAttributeNode(newAttr->getNodeName());
		if (attr)
		{
			mod = MUTATION_MODIFICATION;
			prev = (DOMCHAR*) attr->getNodeValue();
		}

		// if node->nodeValue == null (removal)

		if (1)
		{
			MutationEvent me;
			me.initMutationEvent(DOMSTR "attributeModified", true, true, this, DOMSTR prev.c_str(), newAttr->getNodeValue(), newAttr->getNodeName(), mod);
			dispatchEvent(&me);
		}

		return (Attribute*)attributes.setNamedItem(newAttr);
	}

	Attribute* Element::removeAttributeNode(Attribute* oldAttr)
	{
		Attribute *attr = (Attribute*)attributes.removeNamedItem(oldAttr->getName());
		if (attr == oldAttr)
			return oldAttr;
		return 0;
	}

	void Element::removeAttribute(const DOMString* name)
	{
		Attribute *attr = (Attribute*)attributes.removeNamedItem(name);
	}

	const DOMString* Element::getAttributeNS(const DOMString* namespaceURI,
		const DOMString* localName)
	{
		return 0;
	}

	void Element::setAttributeNS(const DOMString* namespaceURI,
		const DOMString* qualifiedName,
		const DOMString* value)
	{
	}

	void Element::removeAttributeNS(const DOMString* namespaceURI,
		const DOMString* localName)
	{
	}

	Attribute* Element::getAttributeNodeNS(const DOMString* namespaceURI,
		const DOMString* localName)
	{
		return 0;
	}

	Attribute* Element::setAttributeNodeNS(Attribute* newAttr)
	{
		return 0;
	}

	NodeList* Element::getElementsByTagNameNS(const DOMString* namespaceURI,
		const DOMString* localName)
	{
		return 0;
	}

	bool Element::hasAttribute(const DOMString* name)
	{
		return (getAttributeNode(name)!=0);
	}

	bool Element::hasAttributeNS(const DOMString* namespaceURI,
		const DOMString* localName)
	{
		return 0;
	}

	Element::Element()
	{
		nodeType = DOMNode::ELEMENT_NODE;
	}

	Element::Element(const DOMString* tagName)
	{
		nodeType = DOMNode::ELEMENT_NODE;
		nodeName = (DOMCHAR*)tagName;
	}

	Element::Element(Element *e)
	{
		nodeType = (NodeType)e->getNodeType();
		nodeName = (DOMCHAR*)e->getNodeName();
		nodeValue = (DOMCHAR*)e->getNodeValue();
	}
}
