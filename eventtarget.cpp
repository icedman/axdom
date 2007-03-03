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

#include <dom/domnode.h>
#include <dom/eventtarget.h>
#include <dom/event.h>

namespace Dom
{
	EventListenerItem::EventListenerItem(const DOMString* type, EventListener *listener)
	{
		eventType = (DOMCHAR*) type;
		SetData(listener);
	}

	EventTarget::EventTarget()
	{
	}

	EventTarget::~EventTarget()
	{
		freeListeners();
	}

	void EventTarget::addEventListener(const DOMString* type, EventListener* listener, bool useCapture)
	{
		EventListenerItem *li = findEventListener(type, listener);
		if (!li)
		{
			li = new EventListenerItem(type, listener);
			listeners.Push(li);
		}
	}

	void EventTarget::removeEventListener(const DOMString* type, EventListener* listener, bool useCapture)
	{
		EventListenerItem *li = findEventListener(type, listener);
		if (li)
		{
			listeners.Remove(li);
			delete li;
		}
	}

	bool EventTarget::dispatchEvent(Event* evt)
	{
		EventListenerItem *li = listeners.GetFirst();
		while(li)
		{
			EventListener *eventListener = (EventListener*)li->GetData();
			if (stricmp((DOMCHAR*)li->eventType.c_str(), (DOMCHAR*) evt->getType()) == 0)
			{
				eventListener->handleEvent(evt);
				if (evt->isCancelled)
					return true;
			}
			li = li->GetNext();
		}

		if (evt->bubbles)
		{
			DOMNode *node = static_cast<DOMNode*>(this); 
			EventTarget *parent = (EventTarget*)node->getParentNode();
			if (parent)
			{
				parent->dispatchEvent(evt);
			}
		}
		return true;
	}

	EventListenerItem* EventTarget::findEventListener(const DOMString* type, EventListener* listener)
	{
		EventListenerItem *li = listeners.GetFirst();
		while(li)
		{
			EventListener *eventListener = (EventListener*)li->GetData();
			if (eventListener == listener)
			{
				if (stricmp((DOMCHAR*)li->eventType.c_str(), (DOMCHAR*)type) == 0)
					return li;
			}
			li = li->GetNext();
		}
		return 0;
	}

	void EventTarget::freeListeners()
	{
		EventListenerItem *li = 0;
		while(li = listeners.GetFirst())
		{
			listeners.Remove(li);
			delete li;
		}
	}
}
