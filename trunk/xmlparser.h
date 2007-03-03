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

#ifndef EXPATPARSER
#define EXPATPARSER

#include <dom/domstring.h>
#include <dom/document.h>
#include <expat/expat.h>

namespace Dom
{
	//! An Xml parser wrapped around expat

	class XmlParser
	{
	public:
		XmlParser();
		~XmlParser();

		bool initialize(Document *root);
		void shutdown();
		bool parse(const char* data, int len, int isFinal);

		void onStartElement(const XML_Char *name, const XML_Char **attr);
		void onEndElement(const XML_Char *name);
		void onStartCDataSection();
		void onEndCDataSection();
		void onCharacterData(const XML_Char *data, int len);
		void onComment(const XML_Char *comment);
		void onDefault(const XML_Char *data, int len);
		void onXmlDecl(const XML_Char *version, const XML_Char *encoding, int standalone);

		DOMNode *getCurrentNode() { if (!node) node = root; return node; }

	public:
		Document *root;
		DOMNode  *node;
		XML_Parser parser;
	};

}

#endif