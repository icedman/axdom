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

#include "xmlparser.h"
#include <stdio.h>

namespace Dom
{

	// Parser handlers. pass on to userData
	static void XMLCALL StartElementHandler(void *userData, const XML_Char *name, const XML_Char **attr)
	{
		XmlParser *p = (XmlParser*)userData;
		p->onStartElement(name, attr);
	}

	static void XMLCALL EndElementHandler(void *userData, const XML_Char *name)
	{
		XmlParser *p = (XmlParser*)userData;
		p->onEndElement(name);
	}

	static void XMLCALL StartCDataSectionHandler(void *userData)
	{
		XmlParser *p = (XmlParser*)userData;
		p->onStartCDataSection();
	}

	static void XMLCALL EndCDataSectionHandler(void *userData)
	{
		XmlParser *p = (XmlParser*)userData;
		p->onEndCDataSection();
	}

	static void XMLCALL CharacterDataHandler(void *userData, const XML_Char *data, int len)
	{
		XmlParser *p = (XmlParser*)userData;
		p->onCharacterData(data, len);
	}

	static void XMLCALL CommentHandler(void *userData, const XML_Char *comment)
	{
		XmlParser *p = (XmlParser*)userData;
		p->onComment(comment);
	}

	static void XMLCALL DefaultHandler(void *userData, const XML_Char *data, int len)
	{
		XmlParser *p = (XmlParser*)userData;
		p->onDefault(data, len);
	}

	static void XMLCALL XmlDeclHandler(void *userData, const XML_Char *version, const XML_Char *encoding, int standalone)
	{
		XmlParser *p = (XmlParser*)userData;
		p->onXmlDecl(version, encoding, standalone);
	}

	// XmlParser
	XmlParser::XmlParser()
	{
		parser = 0;
		node = 0;
	}

	XmlParser::~XmlParser()
	{
		if (parser)
			shutdown();
	}

	bool XmlParser::initialize(Document *rootDoc)
	{
		if (parser)
		{
			XML_ParserReset(parser, 0);
			return true;
		}

		root = rootDoc;
		node = root;
		parser = XML_ParserCreate(0);

		// element
		XML_SetElementHandler(parser, StartElementHandler, EndElementHandler);
		// cdata
		XML_SetCdataSectionHandler(parser, StartCDataSectionHandler, EndCDataSectionHandler);
		XML_SetCharacterDataHandler(parser, CharacterDataHandler);
		// comment
		XML_SetCommentHandler(parser, CommentHandler);
		// default
		XML_SetDefaultHandler(parser, DefaultHandler);
		XML_SetXmlDeclHandler(parser, XmlDeclHandler);

		XML_SetUserData(parser, (void*)this);
		return true;
	}

	void XmlParser::shutdown()
	{
		if (parser)
		{
			XML_ParserFree(parser);
			parser = 0;
		}
	}

	bool XmlParser::parse(const char* data, int len, int isFinal)
	{
		XML_Parse(parser, data, len, isFinal);
		return true;
	}

	void XmlParser::onStartElement(const XML_Char *name, const XML_Char **attr)
	{
		DOMNode *parent = getCurrentNode();
		Element *element = root->createElement(DOMSTR name);
		if (!element)
			return;

		node = element;
		parent->appendChild(element);

		// add attributes
		for (int i = 0; attr[i]; i += 2)
		{
			element->setAttribute(DOMSTR attr[i], DOMSTR attr[i+1]);
		}
	}

	void XmlParser::onEndElement(const XML_Char *name)
	{
		DOMNode *n = getCurrentNode();
		if (IsWhiteSpace(DOMSTR n->getNodeValue()))
			n->setNodeValue(DOMSTR "");

		if (node)
			node = node->getParentNode();
	}

	void XmlParser::onStartCDataSection()
	{
		DOMNode *parent = getCurrentNode();
		CDataSection *cdatasection = root->createCDATASection(DOMSTR"");
		if (!cdatasection)
			return;

		node = cdatasection;
		parent->appendChild(cdatasection);
	}

	void XmlParser::onEndCDataSection()
	{
		onEndElement(0);
	}

	void XmlParser::onCharacterData(const XML_Char *data, int len)
	{
		if (!len)
			return;

		DOMNode *current = getCurrentNode();
		std::string sdata(data, len);

		switch(current->getNodeType())
		{
		case DOMNode::CDATA_SECTION_NODE:
			{
				CharacterData *cdata = (CharacterData*)current;
				cdata->appendData(DOMSTR sdata.c_str());
				break;
			}
		case DOMNode::TEXT_NODE:
			{
				CharacterData *cdata = (CharacterData*)current;
				cdata->appendData(DOMSTR sdata.c_str());
				break;
			}
		default:
			{
				if (IsWhiteSpace(DOMSTR sdata.c_str()))
					return;

				DOMText *text = root->createTextNode(DOMSTR sdata.c_str());
				current->appendChild(text);
				break;
			}
		}
	}

	void XmlParser::onComment(const XML_Char *cmnt)
	{
		DOMNode *parent = getCurrentNode();
		Comment *comment = root->createComment(DOMSTR cmnt);
		if (!comment)
			return;

		root->appendChild(comment);
	}

	void XmlParser::onDefault(const XML_Char *data, int len)
	{}

	void XmlParser::onXmlDecl(const XML_Char *version, const XML_Char *encoding, int standalone)
	{}
}