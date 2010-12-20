#include "StdAfx.h"
#include "TriangulateEventListener.h"
#include "Visualizer.h"
#include "IAnimation.h"
#include "IMesh.h"

namespace IMesh { namespace UI {

using namespace IMesh::UI::Models;

TriangulateEventListener::TriangulateEventListener(void)
{
	m_ctrlSignal = TriangulateEventListener::Pause;
	m_pCtrlLock = new CSingleLock(&m_ctrlSignalMutex);
}


TriangulateEventListener::~TriangulateEventListener(void)
{
	if (m_pCtrlLock->IsLocked()) {
		m_pCtrlLock->Unlock();
	}
	delete m_pCtrlLock;
	m_pCtrlLock = NULL;
}

void TriangulateEventListener::Initialize( IMesh::UI::CVisualizer* pVisualizer, layer_type* pDemoLayer )
{
	m_pVisualizer = pVisualizer;
	m_pDemoLayer = pDemoLayer;
}

void TriangulateEventListener::OnHandle( void* source, const IMesh::Interface::EventArg& arg )
{
	ASSERT(m_pDemoLayer != NULL);

	TriangulateEventArg& eventArg = (TriangulateEventArg&) arg;
	
	switch(eventArg.m_eventType)
	{
		case TriangulateEventArg::EdgeActivatied:
		{
			if (GetSignal() == TriangulateEventListener::RunToEnd) { break; }

			edge& newEdge = *((edge*) source);
			m_pDemoLayer->ClearCurrentEdge();
			m_pDemoLayer->UpdateCurrentEdge(newEdge, 
											(*eventArg.m_pAllPointList).points);
			m_pDemoLayer->ClearCurrentTriangle();

			/*m_pDemoLayer->UpdateLayer(*eventArg.m_pTriangleList,
									(*eventArg.m_pAllPointList).points);*/
			m_pVisualizer->OnRender();
			break;
		}
		case TriangulateEventArg::SeedTriangleFound:
		{
			if (GetSignal() == TriangulateEventListener::RunToEnd) { break; }

			triangle& newTriangle = *((triangle*) source);
			m_pDemoLayer->ClearCurrentEdge();
			
			m_pDemoLayer->ClearCurrentTriangle();
			m_pDemoLayer->UpdateCurrentTriangle(newTriangle, 
												(*eventArg.m_pAllPointList).points);

			m_pDemoLayer->m_sphere.m_IsVisible = true;
			
			class BallDropAnimation : public Animation
			{
			public:
				CVisualizer* m_pVisualizer;
				MeshLayer* m_pDemoLayer;
				point3D& m_finalCenter;
				float& m_finalRadius;
			public:
				BallDropAnimation(CVisualizer* pVisualizer, 
									MeshLayer* pDemoLayer,
									point3D& center, float& radius) :
										m_pVisualizer(pVisualizer),
										m_pDemoLayer(pDemoLayer),
										m_finalCenter(center),
										m_finalRadius(radius)
				{
					m_fps = 10;
					m_frameNum = 20;
					m_isRepeat = false;
				}
			public:
				void OnAnimationFrame(int i)
				{
					float radius = m_finalRadius * i / m_frameNum;
					m_pDemoLayer->UpdateSpherePos(m_finalCenter, radius);
					m_pVisualizer->OnRender();
				}
			};
			BallDropAnimation animation(m_pVisualizer, m_pDemoLayer, eventArg.m_ballCenter, eventArg.m_ballRadius);
			animation.OnSetup();
			animation.StartAnimation();
			animation.JoinAnimation();
			/*m_pDemoLayer->UpdateLayer(*eventArg.m_pTriangleList,
									(*eventArg.m_pAllPointList).points);*/
			m_pDemoLayer->UpdateSpherePos(eventArg.m_ballCenter, eventArg.m_ballRadius);
			m_pVisualizer->OnRender();
			break;
		}
		case TriangulateEventArg::TriangleCreated:
		{
			if (GetSignal() == TriangulateEventListener::RunToEnd) { break; }
			triangle& newTriangle = *((triangle*) source);
			m_pDemoLayer->ClearCurrentEdge();

			m_pDemoLayer->ClearCurrentTriangle();
			m_pDemoLayer->UpdateCurrentTriangle(newTriangle, 
												(*eventArg.m_pAllPointList).points);

			m_pDemoLayer->m_sphere.m_IsVisible = true;
			m_pDemoLayer->UpdateSpherePos(eventArg.m_ballCenter, eventArg.m_ballRadius);
			
			m_pDemoLayer->UpdateLayer(*eventArg.m_pTriangleList,
				                      (*eventArg.m_pAllPointList).points);
			m_pVisualizer->OnRender();
			break;
		}
		case TriangulateEventArg::Completed:
		{
			m_pDemoLayer->ClearCurrentEdge();
			m_pDemoLayer->ClearCurrentTriangle();

			m_pDemoLayer->m_sphere.m_IsVisible = false;

			m_pDemoLayer->UpdateLayer(*eventArg.m_pTriangleList,
										(*eventArg.m_pAllPointList).points);
			
			m_pVisualizer->OnRender();
			
			CTime currentTime = CTime::GetCurrentTime();
			CTimeSpan duration = currentTime - m_lastSignalTime;
			CString str, str1, str2, str3;
			str1.Format(_T("#Points: %d\r\n"), (*eventArg.m_pAllPointList).points.size());
			str2.Format(_T("#Triangule: %d\r\n"), eventArg.m_pTriangleList->size());
			str3.Format(_T("#Time: %d seconds\r\n"), duration.GetTotalSeconds());
			str = str1 + str2 + str3;
			theApp.GetMainFrame()->AddDebug(str);
			break;
		}

		default:
		{
			new std::exception("Not Support Exception.");
		}
	}

	DWORD millonSecond = 1;
	UpdateSignal();
	do
	{	
		DispatchUIMessage();
		if (IsBlocked()) {
			Sleep(millonSecond);
		}
		else { break; }
		
	} while(true);
}

void TriangulateEventListener::DispatchUIMessage()
{
	BOOL bRet;
	MSG msg;
	if ( (bRet = PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) != 0)
	{ 
		//GetMessage(&msg, NULL, 0, PM_NOREMOVE);
		//TranslateMessage(&msg);
		//DispatchMessage(&msg);
		if ( ! AfxGetApp()->PumpMessage() ) {
			AfxGetApp()->ExitInstance();
		}
	}
}

void TriangulateEventListener::SetSignal( TriangulateEventListener::ControlSignal signal )
{
	m_lastSignalTime = CTime::GetCurrentTime();
	m_pCtrlLock->Lock();
	m_ctrlSignal = signal;
	m_pCtrlLock->Unlock();
}

TriangulateEventListener::ControlSignal TriangulateEventListener::GetSignal()
{
	m_pCtrlLock->Lock();
	TriangulateEventListener::ControlSignal signal = m_ctrlSignal;
	m_pCtrlLock->Unlock();
	return signal;
}

void TriangulateEventListener::UpdateSignal()
{
	m_pCtrlLock->Lock();
	if (m_ctrlSignal == TriangulateEventListener::Step) {
		m_ctrlSignal = TriangulateEventListener::Pause;
	}
	m_pCtrlLock->Unlock();
}

bool TriangulateEventListener::IsBlocked()
{
	return (GetSignal() == TriangulateEventListener::Pause);
}


} }
