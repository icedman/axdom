/*
Version: MPL 1.1/GPL 2.0/LGPL 2.1

The contents of this file are subject to the Mozilla Public License Version
1.1 (the "License"); you may not use this file except compliance with
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

#ifndef AX_MUTATIONEVENT
#define AX_MUTATIONEVENT	

#include <dom/event.h>
#include <dom/domnode.h>

namespace Dom
{
	const unsigned short MUTATION_ADDITION = 1;
	const unsigned short MUTATION_MODIFICATION = 2;
	const unsigned short MUTATION_REMOVAL = 3;

	const unsigned short SUBTREE_MODIFIED = 0;
	const unsigned short NODE_INSERTED		= 1;
	const unsigned short NODE_REMOVED		= 2;
	const unsigned short NODE_INSERTED_TO_DOCUMENT = 3;
	const unsigned short NODE_REMOVED_FROM_DOCUMENT = 4;
	const unsigned short ATTRIBUTE_MODIFIED = 5;
	const unsigned short CHARACTER_DATA_MODIFIED = 6;

	class MutationEvent : public Event
	{
	public:

		void initMutationEvent(
			const DOMString* eventTypeArg, 
			bool canBubbleArg, 
			bool cancellableArg, 
			DOMNode *relatedNodeArg, 
			const DOMString* prevValueArg, 
			const DOMString* newValueArg, 
			const DOMString* attrNameArg, 
			unsigned short attrChangeArg);

		DOMNode *relatedNode;
		std::string prevValue; 
		std::string newValue; 
		std::string attrName;
		unsigned short attrChange;
	};
}

#endif 