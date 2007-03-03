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
	class MutationEvent : public Event
	{
	public:

		enum MutationEventChange
		{
			MUTATION_ADDITION = 1,
			MUTATION_MODIFICATION = 2,
			MUTATION_REMOVAL = 3,
		};

		enum MutationEventType
		{
			SUBTREE_MODIFIED = 0,
			NODE_INSERTED = 1,
			NODE_REMOVED = 2,
			NODE_INSERTED_TO_DOCUMENT = 3,
			NODE_REMOVED_FROM_DOCUMENT = 4,
			ATTRIBUTE_MODIFIED = 5,
			CHARACTER_DATA_MODIFIED = 6,
		};

		void initMutationEvent(
			const DOMString* eventTypeArg, 
			bool canBubbleArg, 
			bool cancellableArg, 
			DOMNode *relatedNodeArg, 
			const DOMString* prevValueArg, 
			const DOMString* newValueArg, 
			const DOMString* attrNameArg, 
			unsigned short attrChangeArg);

		void initMutationEvent(
			unsigned int eventTypeIdArg, 
			bool canBubbleArg, 
			bool cancellableArg, 
			DOMNode *relatedNodeArg, 
			const DOMString* prevValueArg, 
			const DOMString* newValueArg, 
			const DOMString* attrNameArg, 
			unsigned short attrChangeArg);

		virtual const EventNames* getEventNames(const DOMString* type);
		virtual const EventNames* getEventNames(unsigned int type);

		DOMNode *relatedNode;
		std::string prevValue; 
		std::string newValue; 
		std::string attrName;
		unsigned short attrChange;
	};
}

#endif 