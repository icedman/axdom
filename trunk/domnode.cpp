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

#include <dom/domnode.h>
#include <dom/document.h>
#include <dom/characterdata.h>
#include "mutationevent.h"

namespace Dom
{
	const DOMString* DOMNode::getNodeName()
	{
		return (const DOMString*)nodeName.c_str();
	}

	const DOMString* DOMNode::getNodeValue()
	{
		return (const DOMString*)nodeValue.c_str();
	}

	short DOMNode::getNodeType()
	{
		return nodeType;
	}

	DOMNode* DOMNode::getParentNode()
	{
		return parentNode;
	}

	NodeList* DOMNode::getChildNodes()
	{
		return &childNodes;
	}

	DOMNode* DOMNode::getFirstChild()
	{
		return childNodes.getFirstChild();
	}

	DOMNode* DOMNode::getLastChild()
	{
		return childNodes.getLastChild();
	}

	DOMNode* DOMNode::getPreviousSibling()
	{
		DOMNodeListItem *li = nodeListItem.GetPrevious();
		if (li)
			return li->GetData();
		return 0;
	}

	DOMNode* DOMNode::getNextSibling()
	{
		DOMNodeListItem *li = nodeListItem.GetNext();
		if (li)
			return li->GetData();
		return 0;
	}

	NamedNodeMap* DOMNode::getAttributes()
	{
		return &attributes;
	}

	Document* DOMNode::getOwnerDocument()
	{
		if (getNodeType() == DOCUMENT_NODE)
			return (Document*)this;

		if (getParentNode())
		{
			return getParentNode()->getOwnerDocument();
		}
		return 0;
	}

	DOMNode* DOMNode::cloneNode(bool deep)
	{
		DOMNode *clone = 0;

		switch(getNodeType())
		{
		case UNKNOWN_NODE:
			break;
		case ELEMENT_NODE:
			{
				clone = new Element((Element*)this);
				break;
			}
		case ATTRIBUTE_NODE:
			{
				clone = new Attribute((Attribute*)this);
				break;
			}
		case TEXT_NODE:
			{
				clone = new DOMText((DOMText*)this);
				break;
			}
		case CDATA_SECTION_NODE:
			break;
		case ENTITY_REFERENCE_NODE:
			break;
		case ENTITY_NODE:
			break;
		case PROCESSING_INSTRUCTION_NODE:
			break;
		case COMMENT_NODE:
			{
				clone = new Comment((Comment*)this);
				break;
			}
		case DOCUMENT_NODE:
			{
				clone = new Document();
				break;
			}
		case DOCUMENT_TYPE_NODE:
			break;
		case DOCUMENT_FRAGMENT_NODE:
			break;
		case NOTATION_NODE:
			break;
		}

		if (!clone)
			return 0;

		if (hasAttributes())
		{
			NamedNodeMap *cloneAttribs = clone->getAttributes();
			DOMNode *attr = (Attribute*)attributes.getFirstChild();
			while(attr)
			{
				DOMNode *cloneAttr= attr->cloneNode(false);
				if (cloneAttr)
					cloneAttribs->setNamedItem(cloneAttr);
				attr = attr->getNextSibling();
			}
		}

		if (deep)
		{
			DOMNode *child = getFirstChild();
			while(child)
			{
				DOMNode *cloneChild = child->cloneNode(deep);
				if (cloneChild)
					clone->appendChild(cloneChild);
				child = child->getNextSibling();
			}
		}
		return clone;
	}

	DOMNode* DOMNode::insertBefore(DOMNode* newChild, DOMNode* refChild)
	{
		if (!refChild)
			return 0;

		if (childNodes.insertBefore(newChild, refChild))
		{
			if (1)
			{
				MutationEvent me;
				me.initMutationEvent(DOMSTR "nodeInserted", true, true, this, DOMSTR"", newChild->getNodeName(),newChild->getNodeValue(), MUTATION_ADDITION);
				me.target = this;
				dispatchEvent(&me);
			}
			return newChild;
		}

		return 0;
	}

	DOMNode* DOMNode::replaceChild(DOMNode* newChild, DOMNode* oldChild)
	{
		if (insertBefore(newChild, oldChild))
		{
			return removeChild(oldChild);
		}
		return oldChild;
	}

	DOMNode* DOMNode::removeChild(DOMNode* oldChild)
	{
		if (childNodes.removeChild(oldChild))
		{
			if (1)
			{
				MutationEvent me;
				me.initMutationEvent(DOMSTR "nodeRemoved", true, true, this, DOMSTR"", oldChild->getNodeName(), oldChild->getNodeValue(), MUTATION_REMOVAL);
				me.target = this;
				dispatchEvent(&me);
			}
			return oldChild;
		}
		return 0;
	}

	DOMNode* DOMNode::appendChild(DOMNode* newChild)
	{
		if (newChild->getParentNode())
		{
			newChild->getParentNode()->removeChild(newChild);
		}

		if (childNodes.appendChild(newChild))
		{
			if (1)
			{
				MutationEvent me;
				me.initMutationEvent(DOMSTR "nodeInserted", true, true, this, DOMSTR"", newChild->getNodeName(),newChild->getNodeValue(), MUTATION_ADDITION);
				me.target = this;
				dispatchEvent(&me);
			}
			return newChild;
		}
		return 0;
	}

	bool DOMNode::hasChildNodes()
	{
		return (childNodes.getLength() > 0);
	}

	void DOMNode::setNodeValue(const DOMString *nodeValue)
	{
		this->nodeValue = (DOMCHAR*)nodeValue;
	}

	void DOMNode::normalize()
	{
		DOMNode *n = getFirstChild();
		while(n)
		{
			if (n->getNodeType() == TEXT_NODE)
			{
				if (IsWhiteSpace(DOMSTR n->getNodeValue()))
				{
					childNodes.removeChild(n);
					n->release();
					n = getFirstChild();
					continue;
				}

				DOMNode *prev = n->getPreviousSibling();
				if (prev)
				{
					if (prev->getNodeType() == TEXT_NODE)
					{
						CharacterData *tn = (CharacterData*)prev;
						tn->appendData(DOMSTR "\n");
						tn->appendData(n->getNodeValue());
						childNodes.removeChild(n);
						n->release();
						n = prev;
						continue;
					}
				}
			}

			n = n->getNextSibling();
		}

		n = getFirstChild();
		while(n)
		{
			n->normalize();
			n = n->getNextSibling();
		}
	}

	bool DOMNode::isSupported(const DOMString* feature, const DOMString* version)
	{
		return true;
	}

	const DOMString* DOMNode::getNamespaceURI()
	{
		return 0;
	}

	const DOMString* DOMNode::getPrefix()
	{
		return 0;
	}

	const DOMString* DOMNode::getLocalName()
	{
		return 0;
	}

	void DOMNode::setPrefix(const DOMString* prefix)
	{
	}

	bool DOMNode::hasAttributes()
	{
		return (attributes.getLength() > 0);
	}

	void DOMNode::release()
	{
		if (getParentNode())
			return;

		// attributes
		DOMNode *attr = 0;
		while(attr = attributes.item(0))
		{
			attributes.removeChild(attr);
			attr->release();
		}

		// childnodes
		DOMNode *child = 0;
		while(child = getFirstChild())
		{
			removeChild(child);
			child->release();
		}

		delete this;
	}

	// implementation
	DOMNode::DOMNode()
	{
		nodeType = DOMNode::UNKNOWN_NODE;
		nodeTagId = 0;
		nodeData = 0;
		parentNode = 0;
		childNodes.ownerNode = this;
		attributes.ownerNode = this;
		nodeListItem.SetData(this);
	}

	DOMNode::~DOMNode()
	{
		//printf(">released\n");
	}

	void* DOMNode::setData(void *data)
	{
		nodeData = data;
		return nodeData;
	}

	void DOMNode::setNodeNameId(unsigned int tagId)
	{
		nodeTagId = tagId;
	}

	void DOMNode::setParentNode(DOMNode* node)
	{
		parentNode = node;
	}

	DOMNode* DOMNode::getParentNode(NodeType type)
	{
		DOMNode *n = getParentNode();
		if (!n)
			return 0;

		while(n)
		{
			if (n->getNodeType() == type || type == UNKNOWN_NODE)
				return n;
			n = n->getParentNode();
		}

		return 0;
	}

}