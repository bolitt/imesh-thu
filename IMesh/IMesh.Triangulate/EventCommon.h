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

class EdgeEvent : public IMesh::Interface::Event
{
};

class EdgeEventArg : public IMesh::Interface::EventArg
{
public:
	enum EventType {
		Activatied,    // 增加算法过程中的事件
	};
	typedef EventType event_type;

public:
	EventType			  m_eventType;

	edge*                 m_pSourceEdge;
	all_point_list*       m_pAllPointList;
	vector<triangle *>*   m_pTriangleList;
	edgefront*            m_pEdgeFront;
	deque<edge *>*        m_pFrontEdgeQueue;

public:
	void Initialize(event_type eventType,
					edge* pSourceEdge,
					edgefront* pEdgeFront, 
					all_point_list* pAllPointList,
					vector<triangle *>* pTriangleList, 
					deque<edge *>* pFrontEdgeQueue);
};

