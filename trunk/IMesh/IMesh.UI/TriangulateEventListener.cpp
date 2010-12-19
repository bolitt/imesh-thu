#include "StdAfx.h"
#include "TriangulateEventListener.h"
#include "Visualizer.h"
#include "IAnimation.h"

namespace IMesh { namespace UI {

using namespace IMesh::UI::Models;

TriangulateEventListener::TriangulateEventListener(void)
{
	m_ctrlSignal = TriangulateEventListener::Pause;
}


TriangulateEventListener::~TriangulateEventListener(void)
{
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
			/*m_pDemoLayer->UpdateLayer(*eventArg.m_pTriangleList,
									(*eventArg.m_pAllPointList).points);*/
			m_pDemoLayer->UpdateSpherePos(eventArg.m_ballCenter, eventArg.m_ballRadius);
			m_pVisualizer->OnRender();
			break;
		}
		case TriangulateEventArg::TriangleCreated:
		{
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
		Sleep(millonSecond);
	} while(IsBlocked());
}

void TriangulateEventListener::DispatchUIMessage()
{
	BOOL bRet;
	MSG msg;
	if ( (bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{ 
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void TriangulateEventListener::SetSignal( TriangulateEventListener::ControlSignal signal )
{
	CSingleLock lock(&m_ctrlSignalMutex);
	lock.Lock();
	m_ctrlSignal = signal;
	lock.Unlock();
}

TriangulateEventListener::ControlSignal TriangulateEventListener::GetSignal()
{
	TriangulateEventListener::ControlSignal signal;
	CSingleLock lock(&m_ctrlSignalMutex);
	lock.Lock();
	signal = m_ctrlSignal;
	lock.Unlock();
	return signal;
}

void TriangulateEventListener::UpdateSignal()
{
	CSingleLock lock(&m_ctrlSignalMutex);
	lock.Lock();
	if (m_ctrlSignal == TriangulateEventListener::Step) {
		m_ctrlSignal = TriangulateEventListener::Pause;
	}
	lock.Unlock();
}

bool TriangulateEventListener::IsBlocked()
{
	TriangulateEventListener::ControlSignal signal = GetSignal();
	return (signal == TriangulateEventListener::Pause);
}


} }
