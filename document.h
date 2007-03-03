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

#ifndef AX_DOCUMENT
#define AX_DOCUMENT

#include <dom/domcfg.h>
#include <dom/domnode.h>
#include <dom/element.h>
#include <dom/documentfragment.h>
#include <dom/domtext.h>
#include <dom/comment.h>
#include <dom/cdatasection.h>
#include <dom/domimpl.h>
#include <dom/processinginstruction.h>
#include <dom/entityreference.h>
#include <dom/documenttype.h>

namespace Dom
{
	class DOMImplementation;

	class DOM_CLASS_EXPORT Document : public DOMNode
	{
	public: 

		Element* createElement(const DOMString* tagName);
		Attribute* createAttribute(const DOMString* name);
		DocumentFragment* createDocumentFragment();
		DOMText* createTextNode(const DOMString* data);
		Comment* createComment(const DOMString* data);
		CDataSection* createCDATASection(const DOMString* data);
		ProcessingInstruction* createProcessingInstruction(const DOMString* target,
			const DOMString* data);
		EntityReference* createEntityReference(const DOMString* name);
		DocumentType* getDoctype();
		DOMImplementation* getImplementation();
		Element* getDocumentElement();
		NodeList* getElementsByTagName(const DOMString* tagname);
		DOMNode* importNode(DOMNode* importedNode, bool deep);
		Element* createElementNS(const DOMString* namespaceURI,
			const DOMString* qualifiedName);
		Attribute* createAttributeNS(const DOMString* namespaceURI,
			const DOMString* qualifiedName);
		NodeList* getElementsByTagNameNS(const DOMString* namespaceURI,
			const DOMString* localName);
		Element* getElementById(const DOMString* elementId);

		void release();

		Document();
		Document(Document *);

		unsigned int setNodeNameId(const DOMString *tagname, unsigned int);
		unsigned int getNodeNameId(const DOMString *tagname);

	private:
		NodeList* getElementsByTagName(const DOMString* tagname, DOMNode* node, NodeList *bag);
		Element* getElementById(const DOMString* elementId, DOMNode* node);

		NamedNodeMap *nodeTagIds;

		DocumentType docType;
		DOMImplementation domImpl;
	}; 
}

#endif
