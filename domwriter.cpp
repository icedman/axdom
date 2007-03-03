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

#include "domwriter.h"
#include <stdio.h>

namespace Dom
{
	void WriteString(FILE *fp, const DOMCHAR *str);
	void Write(FILE *fp, DOMNode *node);
	void WriteElement(FILE *fp, Element *node);
	void WriteNodeList(FILE *fp, NodeList *nl);
	void WriteIndent(FILE *fp, DOMNode *node);
	void WriteNodeValue(FILE *fp, DOMNode *node);

	void WriteString(FILE *fp, const DOMCHAR *str)
	{
		fwrite(str, strlen(str), 1, fp);
	}

	void WriteIndent(FILE *fp, DOMNode *node)
	{
		int level = 0;
		while(node->getParentNode())
		{
			node = node->getParentNode();
			if (node->getParentNode())
				WriteString(fp, "\t");
		}
	}

	void WriteNodeValue(FILE *fp, DOMNode *node)
	{
		if (strlen((DOMCHAR*)node->getNodeValue()))
		{
			WriteString(fp, (DOMCHAR*)node->getNodeValue());
		}
	}

	void WriteElement(FILE *fp, Element *node)
	{
		WriteString(fp, "<");
		WriteString(fp, (DOMCHAR*)node->getNodeName());
		if (node->hasAttributes())
		{
			DOMNode *attr = node->getAttributes()->getFirstChild();
			while(attr)
			{
				WriteString(fp, " ");
				WriteString(fp, (DOMCHAR*)attr->getNodeName());
				WriteString(fp, "=\"");
				WriteString(fp, (DOMCHAR*)attr->getNodeValue());
				WriteString(fp, "\"");
				attr = attr->getNextSibling();
			}
		}

		if (node->hasChildNodes())
		{
			WriteString(fp, ">");

			DOMNode *n = node->getFirstChild();
			int c = 0;
			while(n)
			{
				c += (n->getNodeType() == DOMNode::ELEMENT_NODE) ? 1 : 0;
				n = n->getNextSibling();
			}

			if (c)
				WriteString(fp, "\n");

		} else {
			WriteString(fp, "/>\n");
			return;
		}

		WriteNodeList(fp, node->getChildNodes());

		WriteString(fp, "</");
		WriteString(fp, (DOMCHAR*)node->getNodeName());
		WriteString(fp, ">\n");
	}

	void WriteNodeList(FILE *fp, NodeList *nl)
	{
		DOMNode *n = nl->getFirstChild();
		while(n)
		{
			Write(fp, n);
			n = n->getNextSibling();
		}
	}

	void Write(FILE *fp, DOMNode *node)
	{
		if (!node)
			return;

		switch(node->getNodeType())
		{
		case DOMNode::ELEMENT_NODE:
			{
				WriteElement(fp, (Element*)node);
				break;
			}
		case DOMNode::COMMENT_NODE:
			{
				WriteString(fp, "<!--");
				WriteNodeValue(fp, node);
				WriteString(fp, "-->\n");
				break;
			}
		case DOMNode::TEXT_NODE:
			{
				WriteNodeValue(fp, node);
				break;
			}
		case DOMNode::CDATA_SECTION_NODE:
			{
				WriteString(fp, "\n<![CDATA[");
				WriteNodeValue(fp, node);
				WriteString(fp, "]]>\n");
				break;
			}
		default:
			WriteNodeList(fp, node->getChildNodes());
			break;
		}		
	}

	bool Writer::write(const char* filename, Document* doc)
	{
		FILE *fp = fopen(filename, "w");
		if (!fp)
			return false;

		Write(fp, doc);


		fclose(fp);
		return true;
	}
}