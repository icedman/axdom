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

#include "domparser.h"
#include "xmlparser.h"

namespace Dom
{
	Parser::Parser()
	{
		root = 0;
		internalParser = 0;
	}

	Parser::~Parser()
	{
	}

	bool Parser::initialize(Document *rootDoc)
	{
		if (internalParser)
			shutdown();

		root = rootDoc;
		internalParser = (void*)new XmlParser();
		XmlParser *p = (XmlParser*)internalParser;
		p->initialize(root);
		return true;
	}

	void Parser::shutdown()
	{
		if (internalParser)
		{
			XmlParser *p = (XmlParser*)internalParser;
			p->parse("\n\n", 2, true); // finalize
			p->shutdown();
			delete p;
			internalParser = 0;
		}
	}

	bool Parser::parse(const char* data, unsigned int length)
	{
		if (!internalParser)
			return false;

		XmlParser *p = (XmlParser*)internalParser;
		return p->parse(data, length, false);
	}
}