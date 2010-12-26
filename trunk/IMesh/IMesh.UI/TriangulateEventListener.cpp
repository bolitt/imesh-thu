#include "StdAfx.h"
#include "TriangulateEventListener.h"
#include "Visualizer.h"
#include "IAnimation.h"
#include "IMesh.h"

namespace IMesh { namespace UI {

using namespace IMesh::UI::Models;

TriangulateEventListener::TriangulateEventListener(void) : m_ctrlLock(&m_ctrlCS)
{
	m_ctrlSignal = TriangulateEventListener::Pause;
	m_bExitThread = FALSE;
	m_ownerThreadId = -1;
}


TriangulateEventListener::~TriangulateEventListener(void)
{
	SetSignal(TriangulateEventListener::Pause);
	if (m_ctrlLock.IsLocked()) {
		m_ctrlLock.Unlock();
	}
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

			if (GetSignal() == TriangulateEventListener::Step) {
				CString info = _T("@ Activate Edge:");
				OutputEdgeInfo(info, eventArg, newEdge);
			}
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
			
			class BallAnimation : public Animation
			{
			public:
				CVisualizer* m_pVisualizer;
				MeshLayer* m_pDemoLayer;
				point3D& m_finalCenter;
				float& m_finalRadius;
			public:
				BallAnimation(CVisualizer* pVisualizer, 
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
			BallAnimation animation(m_pVisualizer, m_pDemoLayer, eventArg.m_ballCenter, eventArg.m_ballRadius);
			animation.OnSetup();
			animation.StartAnimation();
			animation.JoinAnimation();
			/*m_pDemoLayer->UpdateLayer(*eventArg.m_pTriangleList,
									(*eventArg.m_pAllPointList).points);*/
			m_pDemoLayer->UpdateSpherePos(eventArg.m_ballCenter, eventArg.m_ballRadius);
			m_pVisualizer->OnRender();


			if (GetSignal() == TriangulateEventListener::Step) {
				CString info = _T("@ Found Seed Triangle");
				OutputTriangleInfo(info, eventArg, newTriangle);
			}
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

			if (GetSignal() == TriangulateEventListener::Step) {
				CString info = _T("@ Created Triangle:");
				OutputTriangleInfo(info, eventArg, newTriangle);
			}
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
			
			{
				CString info = _T("@ Completed Ball Pivot:");
				OutputCompleteInfo(info, eventArg);

			}
			break;
		}

		default:
		{
			new std::exception("Not Support Exception.");
		}
	}

	UpdateSignal();
	do
	{
		if (m_bExitThread == TRUE) 
		{
			DWORD curThreadId = GetCurrentThreadId();
			if (curThreadId == m_ownerThreadId)
			{
				ExitThread(-1);
			}
		}

		DispatchUIMessage();
		if (IsBlocked()) {
			Sleep(0);
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
	m_ctrlSignalTimer.Start();
	m_ctrlLock.Lock();
	m_ctrlSignal = signal;
	m_ctrlLock.Unlock();
}

TriangulateEventListener::ControlSignal TriangulateEventListener::GetSignal()
{
	m_ctrlLock.Lock();
	TriangulateEventListener::ControlSignal signal = m_ctrlSignal;
	m_ctrlLock.Unlock();
	return signal;
}

void TriangulateEventListener::UpdateSignal()
{
	m_ctrlLock.Lock();
	if (m_ctrlSignal == TriangulateEventListener::Step) {
		m_ctrlSignal = TriangulateEventListener::Pause;
	}
	m_ctrlLock.Unlock();
}

bool TriangulateEventListener::IsBlocked()
{
	return (GetSignal() == TriangulateEventListener::Pause);
}

void TriangulateEventListener::OutputTriangleInfo( CString& info, TriangulateEventArg &eventArg, triangle &newTriangle )
{
	vector<point>& points = (*eventArg.m_pAllPointList).points;
	ModelViewAdjuster& adjuster = m_pVisualizer->m_scene.m_adjuster;
	point& p0 = points[newTriangle.idx_i];
	Num::Vec3f& pp0 = adjuster.Adjust((float)p0.position.x, (float)p0.position.y, (float)p0.position.z);
	point& p1 = points[newTriangle.idx_j];
	Num::Vec3f& pp1 = adjuster.Adjust((float)p1.position.x, (float)p1.position.y, (float)p1.position.z);
	point& p2 = points[newTriangle.idx_k];
	Num::Vec3f& pp2 = adjuster.Adjust((float)p2.position.x, (float)p2.position.y, (float)p2.position.z);
	CString str, str1, str2, str3, str4;
	str1.Format(info);
	str2.Format(_T("  > P[%d]:(%.4f, %.4f, %.4f)"), newTriangle.idx_i, pp0._x, pp0._y, pp0._z);
	str3.Format(_T("  > P[%d]:(%.4f, %.4f, %.4f)"), newTriangle.idx_j, pp1._x, pp1._y, pp1._z);
	str4.Format(_T("  > P[%d]:(%.4f, %.4f, %.4f)"), newTriangle.idx_k, pp2._x, pp2._y, pp2._z);
	theApp.GetMainFrame()->AddDebug(str1);
	theApp.GetMainFrame()->AddDebug(str2);
	theApp.GetMainFrame()->AddDebug(str3);
	theApp.GetMainFrame()->AddDebug(str4);
}


void TriangulateEventListener::OutputEdgeInfo(CString& info, TriangulateEventArg &eventArg, edge &newEdge )
{
	vector<point>& points = (*eventArg.m_pAllPointList).points;
	ModelViewAdjuster& adjuster = m_pVisualizer->m_scene.m_adjuster;
	point& p0 = points[newEdge.idx_i];
	Num::Vec3f& pp0 = adjuster.Adjust((float)p0.position.x, (float)p0.position.y, (float)p0.position.z);
	point& p1 = points[newEdge.idx_j];
	Num::Vec3f& pp1 = adjuster.Adjust((float)p1.position.x, (float)p1.position.y, (float)p1.position.z);
	CString str, str1, str2, str3;
	str1.Format(info);
	str2.Format(_T("  > P[%d]:(%.4f, %.4f, %.4f)"), newEdge.idx_i, pp0._x, pp0._y, pp0._z);
	str3.Format(_T("  > P[%d]:(%.4f, %.4f, %.4f)"), newEdge.idx_j, pp1._x, pp1._y, pp1._z);
	theApp.GetMainFrame()->AddDebug(str1);
	theApp.GetMainFrame()->AddDebug(str2);
	theApp.GetMainFrame()->AddDebug(str3);
}


void TriangulateEventListener::OutputCompleteInfo(CString& info, TriangulateEventArg &eventArg )
{
	CString str1, str2, str3, str4;
	m_ctrlSignalTimer.Pause();
	double millisenconds = m_ctrlSignalTimer.GetTotalMilliSeconds();
	str1.Format(info);
	str2.Format(_T("  > #Points: %d"), (*eventArg.m_pAllPointList).points.size());
	str3.Format(_T("  > #Triangule: %d"), eventArg.m_pTriangleList->size());
	str4.Format(_T("  > Time: %.5lf seconds"), millisenconds / 1000.0);
	theApp.GetMainFrame()->AddDebug(str1);
	theApp.GetMainFrame()->AddDebug(str2);
	theApp.GetMainFrame()->AddDebug(str3);
	theApp.GetMainFrame()->AddDebug(str4);
}

void TriangulateEventListener::SetOwnerThreadId( DWORD ownerThreadId )
{
	m_ownerThreadId = ownerThreadId;
}

} }
