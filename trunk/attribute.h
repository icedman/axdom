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

#ifndef AX_ATTRIBUTE
#define AX_ATTRIBUTE

#include <dom/domcfg.h>
#include <dom/domnode.h>
#include <dom/element.h>

namespace Dom
{
	class Element;

	class DOM_CLASS_EXPORT Attribute : public DOMNode
	{
	public: 

		// Attribute
		const DOMString* getName();
		bool getSpecified();
		const DOMString* getValue();
		void setValue(const DOMString* value);
		Element* getOwnerElement();

		// implementation
		Attribute();
		Attribute(Attribute *);
		Attribute(const DOMString* name, const DOMString* value);
	}; 
}

#endif
