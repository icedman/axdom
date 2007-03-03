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

#ifndef AX_CHARACTERDATA
#define AX_CHARACTERDATA

#include <dom/domcfg.h>
#include <dom/domnode.h>

namespace Dom
{
	class DOM_CLASS_EXPORT CharacterData : public DOMNode
	{
	public: 
		const DOMString* getData();
		unsigned int getLength();
		const DOMString* substringData(unsigned int offset, unsigned int count);
		void appendData(const DOMString* arg);
		void insertData(unsigned int offset, const DOMString* arg);
		void deleteData(unsigned int offset, unsigned int count);
		void replaceData(unsigned int offset, unsigned int count, const DOMString* arg);
		void setData(const DOMString* data);
	}; 
}

#endif
