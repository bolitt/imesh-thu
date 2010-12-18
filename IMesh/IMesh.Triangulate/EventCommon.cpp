#include "EventCommon.h"
#include "TriangulationHandler.h"

void EdgeEventArg::Initialize( event_type eventType,
							edge* pSourceEdge,
							TriangulationHandler* pTriangulationHandler)
{
	m_eventType = eventType;
	m_pSourceEdge = pSourceEdge;
	m_pTriangulationHandler = pTriangulationHandler;
	m_pEdgeFront = &pTriangulationHandler->edfr;
	m_pAllPointList = pTriangulationHandler->apl;
	m_pTriangleList = &pTriangulationHandler->triangleList;
	m_pFrontEdgeQueue = &pTriangulationHandler->frontEdgeQueue;
}
