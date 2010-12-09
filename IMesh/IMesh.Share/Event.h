#pragma once

#include <list>
#include "EventArg.h"
#include "EventListener.h"

namespace IMesh { namespace Interface {

class Event
{
protected: 
	typedef std::list<EventListener *> container_type;

protected:
	container_type m_listeners;

public:
	Event(void);
	~Event(void);

	virtual void Attach(EventListener& listener);
	virtual void Detach(EventListener& listener);
	virtual void OnRaise(void* source, const EventArg& eventArgs);
};

} }
