#pragma once


#include "Structures.h"
#include "Camera.h"
#include "MeshLayer.h"
#include "Triangle.h"
#include "Vertex.h"
#include "Edge.h"

namespace IMesh { namespace UI {

class CVisualizer;

class TriangulateEventListener : public IMesh::Interface::EventListener
{
protected:
	typedef IMesh::UI::Models::MeshLayer layer_type;
	typedef vector<triangle* > triangle_list_type;
	typedef vector<point> points_type;

protected:
	IMesh::UI::CVisualizer* m_pVisualizer;
	layer_type* m_pDemoLayer;

public:
	enum ControlSignal {
		Step, Continue, Pause, RunToEnd 
	};
	
	void SetSignal(ControlSignal signal);
	ControlSignal GetSignal();
	void UpdateSignal();
	void DispatchUIMessage();
	bool IsBlocked();
	volatile BOOL m_bExitThread;

protected:
	ControlSignal m_ctrlSignal;
	CCriticalSection m_ctrlCS;
	CSingleLock m_ctrlLock;
	CTime m_lastSignalTime;
	DWORD m_ownerThreadId;

public:
	void SetOwnerThreadId(DWORD ownerThreadId);
	

public:
	void Initialize(IMesh::UI::CVisualizer* pVisualizer, layer_type* pDemoLayer);
	void OnHandle(void* source, const IMesh::Interface::EventArg& eventArgs);

	void OutputEdgeInfo( CString& info, TriangulateEventArg &eventArg, edge &newEdge );

	void OutputCompleteInfo( CString& info, TriangulateEventArg &eventArg );

	void OutputTriangleInfo( CString& info, TriangulateEventArg &eventArg, triangle &newTriangle );


public:
	TriangulateEventListener();
	~TriangulateEventListener();	
};

} } 
