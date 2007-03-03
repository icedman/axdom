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

#include <dom/event.h>

namespace Dom
{
	void Event::stopPropagation()
	{
		isCancelled = true;
	}

	void Event::preventDefault()
	{
	}

	void Event::initEvent(const DOMString* eventType, bool canBubbleArg, bool cancellableArg)
	{
		type = (DOMCHAR*) eventType;
		bubbles = canBubbleArg;
		cancellable = cancellableArg;
	}
}