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

#include <dom/safenode.h>
#include <dom/document.h>
#include <dom/element.h>

namespace Dom
{
	SafeNode::SafeNode()
	{
		element = 0;
		explorer = 0;
		nodes = 0;
	}

	SafeNode::SafeNode(DOMNode *e)
	{
		element = e;
		explorer = 0;
		nodes = 0;
	}

	SafeNode::~SafeNode()
	{
		detach();
		detachNodes();
	}

	bool SafeNode::attach(DOMNode *e)
	{
		detach();
		detachNodes();
		element = e;
		return true;
	}

	bool SafeNode::attach(NodeList *n)
	{
		detach();
		detachNodes();
		nodes = n;
		return true;
	}

	void SafeNode::detach()
	{
		if (explorer)
		{
			delete explorer;
			explorer = 0;
		}
	}

	void SafeNode::detachNodes()
	{
		if (nodes)
		{
			nodes->release();
			nodes = 0;
		}
	}

	SafeNode* SafeNode::item(int index)
	{
		detach();
		explorer = new SafeNode();
		if (nodes)
		{
			if (nodes->getLength() > index)
				explorer->attach((DOMNode*)nodes->item(index));
		}
		return explorer;
	}

	SafeNode* SafeNode::getElement(const DOMString *tagName)
	{
		detach();
		explorer = new SafeNode();
		if (!element && nodes)
		{
			if (nodes->getLength())
				element = (DOMNode*)nodes->item(0);
		}
		if (element)
		{
			NodeList *n = 0;
			if (element->getNodeType() == DOMNode::DOCUMENT_NODE)
			{
				n = ((Document*)element)->getElementsByTagName(tagName);
			} else if (element->getNodeType() == DOMNode::ELEMENT_NODE) {
				n = ((Element*)element)->getElementsByTagName(tagName);
			}
			explorer->attach(n);
		}
		return explorer;
	}

	SafeNode* SafeNode::getAttribute(const DOMString *name)
	{
		detach();
		explorer = new SafeNode();
		if (!element && nodes)
		{
			if (nodes->getLength())
				element = (DOMNode*)nodes->item(0);
		}
		if (element)
		{
			explorer->attach(((Element*)element)->getAttributeNode(name));
		}
		return explorer;
	}

	SafeNode* SafeNode::getValue(const DOMString *name)
	{
		SafeNode* snode = getAttribute(name);
		if (snode->getNodeValue())
			return snode;

		snode = getElement(name);
		if (snode->item(0)->getNodeValue())
		{
			return snode;
		}

		detach();
		explorer = new SafeNode();
		return explorer;
	}

	DOMNode* SafeNode::getNode()
	{
		if (element)
			return element; 
		if (nodes)
		{
			if (nodes->getLength())
				return (DOMNode*)nodes->item(0);
		}
		return 0;
	}

	const DOMString* SafeNode::getNodeName()
	{
		if (element)
			return (const DOMString*) element->getNodeName();

		if (nodes)
		{
			if (nodes->getLength())
				return nodes->item(0)->getNodeName();
		}

		return 0;
	}

	const DOMString* SafeNode::getNodeValue(const DOMString *defaultValue)
	{
		if (element)
			return (const DOMString*) element->getNodeValue();

		if (nodes)
		{
			if (nodes->getLength())
				return nodes->item(0)->getNodeValue();
		}

		return defaultValue;
	}

	int SafeNode::getNodeValueInt(int defaultValue)
	{
		const DOMString* val = getNodeValue();
		if (!val)
			return defaultValue;
		return atoi((DOMCHAR*) val);
	}
}