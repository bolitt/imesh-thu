#include "Event.h"

namespace IMesh { namespace Interface {


Event::Event()
{
}


Event::~Event()
{
}


void Event::Attach( EventListener& listener )
{
	m_listeners.push_back(&listener);
}

void Event::Detach( EventListener& listener )
{
	m_listeners.remove(&listener);
}


void Event::OnRaise( void* source, const EventArg& eventArgs )
{
	for (container_type::iterator it = m_listeners.begin(); it != m_listeners.end(); ++it) {
		container_type::value_type& li = (*it);
		(*li).OnHandle(source, eventArgs);
	}
}


} }

