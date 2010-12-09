#pragma once

#include <iostream>
#include "Event.h"

using namespace std;

namespace IMesh { namespace Interface { namespace Test{

class EventSourceClass {
public:
	Event EdgeEvent;
	Event VertexEvent;
public:
	char* ToString() { return "EventSourceClass"; }
};

class Tester 
{
public:
	static void Run()
	{
		class EdgeEventListener : EventListener
		{
		public:
			int m_num;

		public:
			void OnHandle(void* source, const EventArg& eventArgs) {
				EventSourceClass& sourceInstance = *((EventSourceClass *) source);
				cout << "EdgeEventListener[id=" << m_num << "] source:"<< sourceInstance.ToString() << endl;
			}
		};
		class VertexEventListener : EventListener
		{
		public:
			int m_num;
		public:
			void OnHandle(void* source, const EventArg& eventArgs) {
				EventSourceClass& sourceInstance = *((EventSourceClass *) source);
				cout << "VertexEventListener[id=" << m_num << "] source:"<< sourceInstance.ToString() << endl;
			}
		};
		
		EventSourceClass eventSource;

		EdgeEventListener aLi; aLi.m_num = 1;
		VertexEventListener bLi; bLi.m_num = 2;
		VertexEventListener cLi; cLi.m_num = 3;

		eventSource.EdgeEvent.Attach((EventListener &)aLi);
		eventSource.VertexEvent.Attach((EventListener &)bLi);
		eventSource.VertexEvent.Attach((EventListener &)cLi);
		cout << "Attached Listeners! " << endl;
		cout << "EdgeEvent: OnRaise" << endl;
		eventSource.EdgeEvent.OnNotify(&eventSource, EventArg());
		cout << "VertexEvent: OnNotify" << endl;
		eventSource.VertexEvent.OnNotify(&eventSource, EventArg());
		cout << "Detached bLi " << endl;
		eventSource.VertexEvent.Detach((EventListener &)bLi);
		cout << "VertexEvent: OnNotify" << endl;
		eventSource.VertexEvent.OnNotify(&eventSource, EventArg());
	}
	

	
};

} } }
