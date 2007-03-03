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

#include <dom/document.h>
#include <dom/element.h>
#include <dom/attribute.h>

namespace Dom
{

	Element* Document::createElement(const DOMString* tagName)
	{
		return (Element*)new Element(tagName);
	}

	Attribute* Document::createAttribute(const DOMString* name)
	{
		return (Attribute*)new Attribute(name, DOMSTR"");
	}

	DocumentFragment* Document::createDocumentFragment()
	{
		return (DocumentFragment*)new DocumentFragment();
	}

	DOMText* Document::createTextNode(const DOMString* data)
	{
		return (DOMText*)new DOMText(data);
	}

	Comment* Document::createComment(const DOMString* data)
	{
		return (Comment*)new Comment(data);
	}

	CDataSection* Document::createCDATASection(const DOMString* data)
	{
		return (CDataSection*)new CDataSection(data);
	}

	ProcessingInstruction* Document::createProcessingInstruction(const DOMString* target,
		const DOMString* data)
	{
		return (ProcessingInstruction*)new ProcessingInstruction(target, data);
	}

	EntityReference* Document::createEntityReference(const DOMString* name)
	{
		return (EntityReference*)new EntityReference(name);
	}

	DocumentType* Document::getDoctype()
	{
		return &docType;
	}

	DOMImplementation* Document::getImplementation()
	{
		return &domImpl;
	}

	Element* Document::getDocumentElement()
	{
		return (Element*)new Document();
	}

	NodeList* Document::getElementsByTagName(const DOMString* tagName)
	{
		return getElementsByTagName(tagName, this, 0);
	}

	DOMNode* Document::importNode(DOMNode* importedNode, bool deep)
	{
		return 0;
	}

	Element* Document::createElementNS(const DOMString* namespaceURI,
		const DOMString* qualifiedName)
	{
		return 0;
	}

	Attribute* Document::createAttributeNS(const DOMString* namespaceURI,
		const DOMString* qualifiedName)
	{
		return 0;
	}

	NodeList* Document::getElementsByTagNameNS(const DOMString* namespaceURI,
		const DOMString* localName)
	{
		return 0;
	}

	Element* Document::getElementById(const DOMString* elementId)
	{
		return getElementById(elementId, this);
	}

	Document::Document()
	{
		nodeType = DOCUMENT_NODE;
		nodeName = "#document";
		nodeTagIds = 0;
	}

	Document::Document(Document *d)
	{
		nodeType = (NodeType)d->getNodeType();
		nodeName = (DOMCHAR*)d->getNodeName();
		nodeTagIds = 0;
	}


	NodeList* Document::getElementsByTagName(const DOMString* tagName, DOMNode* node, NodeList *bag)
	{
		if (!bag)
			bag = new NodeList();

		DOMNode *e = node->getFirstChild();
		while(e)
		{
			if (stricmp((DOMCHAR*)e->getNodeName(), (DOMCHAR*)tagName) == 0)
			{
				bag->appendLocalChild(e);
			}

			getElementsByTagName(tagName, e, bag);
			e = e->getNextSibling();
		}

		return bag;
	}

	Element* Document::getElementById(const DOMString* elementId, DOMNode* node)
	{
		DOMNode *e = node->getFirstChild();
		while(e)
		{
			// read dom 2 specs about ID
			Attribute *attr = (Attribute*)e->getAttributes()->getNamedItem(DOMSTR "id");
			if (attr)
			{
				if (stricmp((DOMCHAR*)attr->getValue(), (DOMCHAR*)elementId) == 0)
				{
					return (Element*)e;
				}
			}

			Element *el = getElementById(elementId, e);
			if (el)
				return el;

			e = e->getNextSibling();
		}

		return 0;
	}

	void Document::release()
	{
		if (nodeTagIds)
		{
			nodeTagIds->release();
			nodeTagIds = 0;
		}
		DOMNode::release();
	}

	unsigned int Document::setNodeNameId(const DOMString *tagName, unsigned int id)
	{
		if (!nodeTagIds)
		{
			nodeTagIds = new NamedNodeMap();
		}

		unsigned int oldId = getNodeNameId(tagName);
		if (oldId)
			return oldId;

		Attribute *attr = new Attribute(tagName, DOMSTR "");
		attr->setData((void*)id);
		nodeTagIds->appendLocalChild(attr);
		return id;
	}

	unsigned int Document::getNodeNameId(const DOMString *tagName)
	{
		if (!nodeTagIds)
			return 0;

		DOMNode *node = nodeTagIds->getNamedItem(tagName);
		if (node)
			return (unsigned int)node->getData();

		return 0;
	}
}
