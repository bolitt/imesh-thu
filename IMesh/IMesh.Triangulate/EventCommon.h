#pragma once

#include "predefs.h"

#include "../IMesh.Share/Event.h"
#include "../IMesh.Share/EventArg.h"
#include "../IMesh.Share/EventListener.h"

#ifdef _DEBUG
  #pragma comment(lib, "../Debug/IMesh.Norm.lib")
  #pragma comment(lib, "../Debug/IMesh.Share.lib")
#else
  #pragma comment(lib, "../Release/IMesh.Norm.lib")
  #pragma comment(lib, "../Release/IMesh.Share.lib")
#endif

class TriangulationHandler;

class TriangulateEvent : public IMesh::Interface::Event
{
};

class TriangulateEventArg : public IMesh::Interface::EventArg
{
public:
	enum EventType {
		EdgeActivatied,    // 增加算法过程中的事件
		TriangleCreated,
		SeedTriangleFound,
		Completed
	};
	typedef EventType event_type;

public:
	EventType			  m_eventType;
	void*                 m_pEventSource;

	TriangulationHandler* m_pTriangulationHandler;

	// for outer use
	all_point_list*       m_pAllPointList;
	vector<triangle *>*   m_pTriangleList;
	edgefront*            m_pEdgeFront;
	deque<edge *>*        m_pFrontEdgeQueue;
	float                 m_ballRadius;
	point3D				  m_ballCenter;

protected:
	void _Initialize(TriangulationHandler* pTriangulationHandler);

public:
	void Initialize(event_type eventType,
					edge* pSourceEdge,
					TriangulationHandler* pTriangulationHandler);
	void Initialize(event_type eventType,
					triangle* pSourceTriangle,
					TriangulationHandler* pTriangulationHandler);
	void Initialize(event_type eventType,
					TriangulationHandler* pTriangulationHandler);
};

