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

#include "mutationevent.h"

namespace Dom
{

	void MutationEvent::initMutationEvent(
		const DOMString* eventTypeArg, 
			bool canBubbleArg, 
			bool cancellableArg, 
			DOMNode *relatedNodeArg, 
			const DOMString* prevValueArg, 
			const DOMString* newValueArg, 
			const DOMString* attrNameArg, 
			unsigned short attrChangeArg)
	{
		type = (DOMCHAR*) eventTypeArg;
		bubbles = canBubbleArg;
		cancellable = cancellableArg;
		relatedNode = relatedNodeArg;
		prevValue = (DOMCHAR*) prevValueArg;
		newValue = (DOMCHAR*) newValueArg;
		attrName = (DOMCHAR*) attrNameArg;
		attrChange = attrChangeArg;
	}

}