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
code.google.com/p/ashlar
*/

#include <dom/domimpl.h>
#include <dom/domstring.h>
#include <dom/document.h>
#include <dom/element.h>
#include <dom/attribute.h>
#include <dom/domparser.h>
#include <dom/domwriter.h>
#include <dom/eventtarget.h>
#include <dom/mutationevent.h>
#include <dom/event.h>
#include <stdio.h>

#include <windows.h>

void Dump(Dom::DOMNode *node);
void DumpNodeList(Dom::NodeList *nl);

void DumpNodeList(Dom::NodeList *nl)
{
	for(int i = 0; i<nl->getLength(); i++)
	{
		Dom::DOMNode *n = nl->item(i);
		Dump(n);
	}
}

void Dump(Dom::DOMNode *node)
{
	if (!node)
		return;

	int level = 0;
	Dom::DOMNode *n = node->getParentNode();
	while(n)
	{
		n = n->getParentNode();
		level++;
	}

	for(int i = 0; i<level; i++) printf(" ");
	printf("%s [%d]", node->getNodeName(), node->getNodeType());
	if (node->getAttributes()->getLength())
	{
		n = node->getAttributes()->item(0);
		printf(" > ");
		while(n)
		{
			printf("%s = %s; ", n->getNodeName(), n->getNodeValue());
			n = n->getNextSibling();
		}
	}

	if (1 && strlen((char*)node->getNodeValue()))
	{
		printf("\n");
		for(int i = 0; i<level; i++) printf(" ");
		printf(">%s<", node->getNodeValue());
	}
	printf("\n");

	DumpNodeList(node->getChildNodes());
}

class MyListener : public Dom::EventListener
{
public:
	void handleEvent(Dom::Event* evt)
	{
		Dom::MutationEvent *me = (Dom::MutationEvent*)evt;
		printf("%s\n", (Dom::DOMCHAR*) me->getType());
	}
};

int main()
{
	Dom::DOMImplementation domimpl;
	if (!domimpl.hasFeature(DOMSTR "core", DOMSTR "2"))
	{
		return 0;
	}

	Dom::Document *doc = new Dom::Document();
	Dom::EventTarget *et;

	MyListener my;

	doc->addEventListener(DOMSTR "nodeInserted", &my, true);
	doc->addEventListener(DOMSTR "nodeRemoved", &my, true);
	doc->addEventListener(DOMSTR "attributeModified", &my, true);

	Dom::Parser parser;

	DWORD tm = timeGetTime();
	parser.initialize(doc);

	FILE *fp = fopen("test.xul", "r");
	if (!fp)
		return false;

	while(!feof(fp))
	{
		char buffer[1024];
		unsigned short len = fread(buffer, 1, 1024, fp);
		parser.parse(buffer, len);
	}

	fclose(fp);

	parser.shutdown();

	doc->normalize();

	Dom::Writer writer;
	writer.write("c:\\temp.xul", doc);

	printf(">");
	for(int i=0;i<0;i++)
	{
		Dom::NodeList *nl = doc->getElementsByTagName(DOMSTR "button");
		if (nl->getLength())
		{
			/*
			Dom::DOMNode *n = nl->item(0);
			n->getParentNode()->removeChild(n);
			n->release();
			*/
		}
		//printf("%d\n", nl->getLength());
		nl->release();
	}

	//Dump(doc);
	doc->release();

	printf("%d\n", timeGetTime() - tm);

	return 0;
}
