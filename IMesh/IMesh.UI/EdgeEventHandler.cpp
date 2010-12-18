#include "StdAfx.h"
#include "EdgeEventHandler.h"
#include "Visualizer.h"

namespace IMesh { namespace UI {

using namespace IMesh::UI::Models;

EdgeEventListener::EdgeEventListener(void)
{
}


EdgeEventListener::~EdgeEventListener(void)
{
}

void EdgeEventListener::Initialize( IMesh::UI::CVisualizer* pVisualizer, layer_type* pDemoLayer )
{
	m_pVisualizer = pVisualizer;
	m_pDemoLayer = pDemoLayer;
}

void EdgeEventListener::OnHandle( void* source, const IMesh::Interface::EventArg& arg )
{
	edge& newEdge = *((edge*) source);
	EdgeEventArg& edgeEventArg = (EdgeEventArg&) arg;

	switch(edgeEventArg.m_eventType)
	{
		case EdgeEventArg::Activatied: 
		{
			UpdateLayer(newEdge, edgeEventArg);
			break;
		}
		
		default:
		{
			new std::exception("Not Support Exception.");
		}
	}

	BOOL bRet;
	MSG msg;
	if ( (bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{ 
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	/*DWORD millonSecond = 100;
	
	while(true) 
	{
		Sleep(millonSecond);
	} */
}


void EdgeEventListener::UpdateLayer( edge& newEdge, EdgeEventArg& edgeEventArg )
{
	/*CSingleLock lock;
	CSemaphore semaphore;*/
	
	if (m_pDemoLayer != NULL) 
	{
		triangle_list_type& triangles = *(edgeEventArg.m_pTriangleList);
		points_type& points = edgeEventArg.m_pAllPointList->points;
		m_pDemoLayer->UpdateLayer(triangles, points);
	}

	m_pVisualizer->OnRender();
}

} }
