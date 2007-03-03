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

#ifndef AX_NODELIST
#define AX_NODELIST

#include <dom/domcfg.h>
#include <shared/list.h>

namespace Dom
{
	class DOMNode;
	class DOMNodeListItem : public Shared::Node<DOMNodeListItem, DOMNode> {};
	class DOMNodeList : public Shared::List<DOMNodeListItem, DOMNode> {};

	class DOM_CLASS_EXPORT NodeList
	{
	public: 
		virtual DOMNode* item(unsigned int index);
		virtual unsigned int getLength();

		NodeList();
		~NodeList();
		DOMNode *getFirstChild();
		DOMNode *getLastChild();

		DOMNode* appendLocalChild(DOMNode* newChild);

		void release();

	protected:
		friend DOMNode;
		DOMNode* ownerNode;
		DOMNode* insertBefore(DOMNode* newChild, DOMNode* refChild);
		DOMNode* removeChild(DOMNode* oldChild);
		DOMNode* appendChild(DOMNode* newChild);
		DOMNodeList nodeList;

	private:
		bool transient;
	}; 
}

#endif
