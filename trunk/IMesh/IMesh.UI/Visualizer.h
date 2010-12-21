#pragma once

#include "Structures.h"
#include "Camera.h"
#include "Projection.h"
#include "Scene.h"
#include "TriangulateEventListener.h"

namespace IMesh {
namespace UI { // namespace IMesh::UI

// CPainter ÃüÁîÄ¿±ê

class CVisualizer : public CObject
{
public:
	CVisualizer();
	virtual ~CVisualizer();

protected:
	HGLRC m_hGLContext;
	int m_GLPixelIndex;
	HDC m_hDC;

public:
	Camera m_camera;
	Projection m_projection;
	CSize m_canvasSize;

	CloudInit m_cloud;
	TriangulateEventListener m_triangulateEventListener;
	Models::Scene m_scene;

public:
	CWinThread* m_workerThread;
	bool m_isWorkerRunning;
	bool m_isLoaded;
	// for synchronize:
protected:
	CCriticalSection m_renderCriticalSection;

public:
	CSingleLock m_renderLock;
	
protected:
	BOOL CreateViewGLContext(HDC hDC); 
	BOOL SetWindowPixelFormat(HDC hDC);

	void OnView();

public:
	void OnSetup();
	void LoadCloud(char* filepath = NULL);
	void OnTriangulate(TriangulateEventListener::ControlSignal signal);
	void OnTriangulateStep();
	void OnTriangulateDemo();
	void OnTriangulatePause();
	void OnTriangulateToEnd();
public:
	BOOL ActivateCurrentContext();
	void DisactivateCurrentContext();

	int OnCreate(HDC hDC);
	
	
	void PreCreateWindow(CREATESTRUCT& cs);
	void OnSize(UINT nType, int cx, int cy);
	void OnRender();

	


	void OnViewZoom(double delta);
	void OnViewRotate(double deltaX, double deltaY);
	
	PosVec3d CameraToPos();
	PosVec3d CameraFindUp();
	
	void DrawGrid(float size, float step);
	void DrawAxis(float size);
	


};

}}


