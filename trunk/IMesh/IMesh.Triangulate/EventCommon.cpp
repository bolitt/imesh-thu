#include "EventCommon.h"


void EdgeEventArg::Initialize( event_type eventType,
							edge* pSourceEdge, edgefront* pEdgeFront, 
							all_point_list* pAllPointList, 
							vector<triangle *>* pTriangleList, deque<edge *>* pFrontEdgeQueue )
{
	m_eventType = eventType;
	m_pSourceEdge = pSourceEdge;
	m_pEdgeFront = pEdgeFront;
	m_pAllPointList = pAllPointList;
	m_pTriangleList = pTriangleList;
	m_pFrontEdgeQueue = pFrontEdgeQueue;
}
