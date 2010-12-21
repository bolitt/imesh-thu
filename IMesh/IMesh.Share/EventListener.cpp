#include <exception>
#include "EventListener.h"

namespace IMesh { namespace Interface {

EventListener::EventListener()
{
}


EventListener::~EventListener()
{
}

void EventListener::OnHandle(void* source, const EventArg& eventArgs)
{
	throw std::exception("Not Implemented Exception!");
}


} } 
