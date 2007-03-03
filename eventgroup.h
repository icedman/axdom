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

#ifndef AX_EVENTGROUP
#define AX_EVENTGROUP

namespace Dom
{
	enum EventGroupId
	{
		UNKNOWN_EVENTS = 0,
		MUTATION_EVENTS = 1,
		UI_EVENTS = 10,
		MOUSE_EVENTS = 11,
	};

	typedef struct EventNames
	{
		unsigned int groupId;
		unsigned int typeId;
		char name[32];
		char method[32];
	} EventNames;
}

#endif