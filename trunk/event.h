/*
Version: MPL 1.1/GPL 2.0/LGPL 2.1

The contents of this file are subject to the Mozilla Public License Version
1.1 (the "License"); you may not use this file except compliance with
the License. You may obtaa copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
for the specific language governing rights and limitations under the
License.

Copyright 2007
MarvSanchez
http://code.google.com/u/m4rvin2005/
*/

#ifndef AX_EVENT
#define AX_EVENT

#include <dom/domstring.h>
#include <dom/eventtarget.h>

namespace Dom
{
	class DOM_CLASS_EXPORT Event
	{
	public:

		Event() : isCancelled(0), 
			target(0),
			currentTarget(0)
		{}

		void stopPropagation();
		void preventDefault();
		void initEvent(const DOMString* type, bool canBubbleArg, bool cancellableArg);

		DOMString* getType() { return DOMSTR type.c_str(); }

		std::string type;
		EventTarget *target;
		EventTarget *currentTarget;
		unsigned short eventPhase;
		bool bubbles;
		bool cancellable;
		bool isCancelled;

	};
}

#endif EVENT