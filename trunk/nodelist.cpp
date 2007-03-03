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

#include <dom/nodelist.h>
#include <dom/domnode.h>

namespace Dom
{
	DOMNode* NodeList::item(unsigned int index)
	{	
		return (DOMNode*)nodeList.GetDataAt(index);
	}

	unsigned int NodeList::getLength()
	{
		return nodeList.Size();
	}

	NodeList::NodeList()
	{
		transient = false;
		ownerNode = 0;
	}

	NodeList::~NodeList()
	{}

	DOMNode* NodeList::getFirstChild()
	{
		DOMNodeListItem *li = nodeList.GetFirst();
		if (li)
			return li->GetData();
		return 0;
	}

	DOMNode* NodeList::getLastChild()
	{
		DOMNodeListItem *li = nodeList.GetLast();
		if (li)
			return li->GetData();
		return 0;
	}

	DOMNode* NodeList::insertBefore(DOMNode* newChild, DOMNode* refChild)
	{
		if (!newChild || !refChild || transient)
			return 0;
		if (nodeList.InsertBefore(&newChild->nodeListItem, &refChild->nodeListItem))
		{
			newChild->setParentNode(ownerNode);
			return newChild;
		}
		return 0;
	}

	DOMNode* NodeList::removeChild(DOMNode* oldChild)
	{
		if (!oldChild || transient)
			return 0;
		if (nodeList.Remove(&oldChild->nodeListItem))
		{
			oldChild->setParentNode(0);
			return oldChild;
		}
		return 0;
	}

	DOMNode* NodeList::appendChild(DOMNode* newChild)
	{
		if (!newChild || transient)
			return 0;
		if (nodeList.Push(&newChild->nodeListItem))
		{
			newChild->setParentNode(ownerNode);
			return newChild;
		}
		return 0;
	}

	DOMNode* NodeList::appendLocalChild(DOMNode* newChild)
	{
		if (!newChild)
			return 0;
		if (!transient && getLength())
			return 0;

		transient = true;
		DOMNodeListItem *newLi = new DOMNodeListItem();
		newLi->SetData(newChild);
		if (nodeList.Push(newLi))
			return newChild;
		delete newLi;

		return 0;
	}

	void NodeList::release()
	{		
		if (transient)
		{
			DOMNodeListItem *li = 0;
			while(li = nodeList.GetFirst())
			{
				nodeList.Remove(li);
				delete li;
			}
		}
		delete this;
	}
}
