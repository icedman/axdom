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

#include <dom/attribute.h>

namespace Dom
{

	const DOMString* Attribute::getName()
	{
		return DOMNode::getNodeName();
	}

	bool Attribute::getSpecified()
	{
		return false;
	}

	const DOMString* Attribute::getValue()
	{
		return DOMNode::getNodeValue();
	}

	void Attribute::setValue(const DOMString* value)
	{
		return DOMNode::setNodeValue(value);
	}

	Element* Attribute::getOwnerElement()
	{
		return (Element*)getParentNode();
	}

	Attribute::Attribute()
	{
		nodeType = DOMNode::ATTRIBUTE_NODE;
	}

	Attribute::Attribute(const DOMString* name, const DOMString* value)
	{
		nodeType = DOMNode::ATTRIBUTE_NODE;
		nodeName = (DOMCHAR*)name;
		nodeValue = (DOMCHAR*)value;
	}

	Attribute::Attribute(Attribute *a)
	{
		nodeType = (NodeType)a->getNodeType();
		nodeName = (DOMCHAR*)a->getNodeName();
		nodeValue = (DOMCHAR*)a->getNodeValue();
	}
}