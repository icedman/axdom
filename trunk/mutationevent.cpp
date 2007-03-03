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

#include <dom/mutationevent.h>
#include "eventgroup.h"

namespace Dom
{
	const EventNames mutationEventNames[] = {
		{ MUTATION_EVENTS, MutationEvent::SUBTREE_MODIFIED,
		"subtreeModified",
		"onSubtreeModified" },
		{ MUTATION_EVENTS, MutationEvent::NODE_INSERTED,
		"nodeInserted",
		"onNodeInserted" },
		{ MUTATION_EVENTS, MutationEvent::NODE_REMOVED,
		"nodeRemoved",	"onNodeRemoved" },
		{ MUTATION_EVENTS, MutationEvent::NODE_INSERTED_TO_DOCUMENT,
		"nodeRnsertedToDocument",
		"onNodeRnsertedToDocument" },
		{ MUTATION_EVENTS, MutationEvent::NODE_REMOVED_FROM_DOCUMENT,
		"nodeRemovedFromDocument",
		"onNodeRemovedFromDocument" },
		{ MUTATION_EVENTS, MutationEvent::ATTRIBUTE_MODIFIED,
		"attributeModified",
		"onAttributeModified" },
		{ MUTATION_EVENTS, MutationEvent::CHARACTER_DATA_MODIFIED,
		"characterDataModified",
		"onCharacterDataModified" },
		0
	};

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

	void MutationEvent::initMutationEvent(
		unsigned int eventTypeIdArg, 
		bool canBubbleArg, 
		bool cancellableArg, 
		DOMNode *relatedNodeArg, 
		const DOMString* prevValueArg, 
		const DOMString* newValueArg, 
		const DOMString* attrNameArg, 
		unsigned short attrChangeArg)
	{
		eventTypeId = eventTypeIdArg;
		eventGroupId = MUTATION_EVENTS;
		bubbles = canBubbleArg;
		cancellable = cancellableArg;
		relatedNode = relatedNodeArg;
		prevValue = (DOMCHAR*) prevValueArg;
		newValue = (DOMCHAR*) newValueArg;
		attrName = (DOMCHAR*) attrNameArg;
		attrChange = attrChangeArg;

		const EventNames *names = getEventNames(eventTypeId);
		if (names)
			type = names->name;
	}

	const EventNames* MutationEvent::getEventNames(const DOMString* type)
	{
		for(int i=0; mutationEventNames[i].groupId; i++)
		{
			if (stricmp((DOMCHAR*) type, (DOMCHAR*) mutationEventNames[i].name) == 0)
				return &mutationEventNames[i];
		}
		return 0;
	}

	const EventNames* MutationEvent::getEventNames(unsigned int type)
	{
		for(int i=0; mutationEventNames[i].groupId; i++)
		{
			if (type == mutationEventNames[i].typeId)
				return &mutationEventNames[i];
		}
		return 0;
	}
}