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

#ifndef AX_DOMNODE
#define AX_DOMNODE

#include <dom/domcfg.h>
#include <dom/domstring.h>
#include <dom/nodelist.h>
#include <dom/namednodemap.h>
#include <dom/eventtarget.h>
#include <shared/list.h>

#include <string>

namespace Dom
{
	class Document;
	class NodeList;

	class DOM_CLASS_EXPORT DOMNode : public EventTarget
	{
	public: 

		enum NodeType { 
			UNKNOWN_NODE = 0,
			ELEMENT_NODE = 1,
			ATTRIBUTE_NODE = 2,
			TEXT_NODE = 3,
			CDATA_SECTION_NODE = 4,
			ENTITY_REFERENCE_NODE = 5,
			ENTITY_NODE = 6,
			PROCESSING_INSTRUCTION_NODE = 7,
			COMMENT_NODE = 8,
			DOCUMENT_NODE = 9,
			DOCUMENT_TYPE_NODE = 10,
			DOCUMENT_FRAGMENT_NODE = 11,
			NOTATION_NODE = 12,
		};

		const DOMString* getNodeName();
		const DOMString* getNodeValue();
		short getNodeType();
		DOMNode* getParentNode();
		NodeList* getChildNodes();
		DOMNode* getFirstChild();
		DOMNode* getLastChild();
		DOMNode* getPreviousSibling();
		DOMNode* getNextSibling();
		NamedNodeMap* getAttributes();
		Document* getOwnerDocument();
		DOMNode* cloneNode(bool deep);
		DOMNode* insertBefore(DOMNode* newChild, DOMNode* refChild);
		DOMNode* replaceChild(DOMNode* newChild, DOMNode* oldChild);
		DOMNode* removeChild(DOMNode* oldChild);
		DOMNode* appendChild(DOMNode* newChild);
		bool hasChildNodes();
		void setNodeValue(const DOMString *nodeValue);
		void normalize();
		bool isSupported(const DOMString* feature, const DOMString* version);
		const DOMString* getNamespaceURI();
		const DOMString* getPrefix();
		const DOMString* getLocalName();
		void setPrefix(const DOMString* prefix);
		bool hasAttributes();
		virtual void release();

		// implementation
		DOMNode();
		virtual ~DOMNode();
		void setParentNode(DOMNode* node);
		DOMNode* getParentNode(NodeType type);

		void* setData(void *data);
		void* getData() { return nodeData; }

		void setNodeNameId(unsigned int tagId);
		unsigned int getNodeNameId() { return nodeTagId; }
		virtual unsigned int setNodeNameId(const DOMString *tagname, unsigned int) { return 0; }
		virtual unsigned int getNodeNameId(const DOMString *tagname) { return 0; }

	protected:
		std::string nodeName;
		std::string nodeValue;
		DOMNode *parentNode;
		NodeType nodeType;
		unsigned int nodeTagId;
		void *nodeData;

		NodeList childNodes;
		NamedNodeMap attributes;

		friend NodeList;
		friend NamedNodeMap;
		DOMNodeListItem nodeListItem;
	};
}

#endif
