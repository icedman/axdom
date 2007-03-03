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

#ifndef AX_EVENTTARGET
#define AX_EVENTTARGET

#include <dom/domstring.h>
#include <dom/eventtarget.h>
#include <shared/list.h>

#include <string>

namespace Dom
{
	class Event;

	class DOM_CLASS_EXPORT EventListener
	{
	public:
		virtual void handleEvent(Event* evt) { return; }
	};

	class EventListenerItem : public Shared::Node<EventListenerItem, EventListener>
	{
	public:
		EventListenerItem(const DOMString* type, EventListener *listener);
		std::string eventType;

		unsigned int eventGroupId;
		unsigned int eventTypeId;
	};

	class EventListenerList : public Shared::List<EventListenerItem, EventListener> {};

	// useCapture is not implemented
	class DOM_CLASS_EXPORT EventTarget 
	{
	public:
		void addEventListener(const DOMString* type, EventListener* listener, bool useCapture);
		void removeEventListener(const DOMString* type, EventListener* listener, bool useCapture);
		bool dispatchEvent(Event* evt);

		// implementation
		EventTarget();
		~EventTarget();

		void freeListeners();

	private:
		EventListenerItem* findEventListener(const DOMString* type, EventListener* listener);
		EventListenerList listeners;
	};
}

#endif