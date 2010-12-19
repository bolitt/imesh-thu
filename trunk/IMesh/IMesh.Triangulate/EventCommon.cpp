#include "EventCommon.h"
#include "TriangulationHandler.h"

void TriangulateEventArg::Initialize( event_type eventType,
							edge* pSourceEdge,
							TriangulationHandler* pTriangulationHandler)
{
	m_eventType = eventType;
	m_pEventSource = pSourceEdge;

	_Initialize(pTriangulationHandler);
}

void TriangulateEventArg::Initialize( event_type eventType, triangle* pSourceTriangle, TriangulationHandler* pTriangulationHandler )
{
	m_eventType = eventType;
	m_pEventSource = pSourceTriangle;

	_Initialize(pTriangulationHandler);
}

void TriangulateEventArg::Initialize( event_type eventType, TriangulationHandler* pTriangulationHandler )
{
	m_eventType = eventType;
	m_pEventSource = NULL;
	_Initialize(pTriangulationHandler);
}

void TriangulateEventArg::_Initialize( TriangulationHandler* pTriangulationHandler )
{
	m_pTriangulationHandler = pTriangulationHandler;
	m_pEdgeFront = &pTriangulationHandler->edfr;
	m_pAllPointList = pTriangulationHandler->apl;
	m_pTriangleList = &pTriangulationHandler->triangleList;
	m_pFrontEdgeQueue = &pTriangulationHandler->frontEdgeQueue;
	m_ballRadius = pTriangulationHandler->ballRadius;
	m_ballCenter = pTriangulationHandler->ballCenter;
}
