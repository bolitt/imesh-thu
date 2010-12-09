#pragma once


#include "EventArg.h"


namespace IMesh { namespace Interface {

class EventListener
{
public:
	EventListener(void);
	~EventListener(void);

	virtual void OnHandle(void* source, const EventArg& eventArgs);
};

} }
