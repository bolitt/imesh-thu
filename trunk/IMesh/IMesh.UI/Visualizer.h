#pragma once

#include "vec.h"
#include "Camera.h"
#include "Projection.h"
#include "Scene.h"

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

public:
	Models::Scene m_scene;

public:
	GLUquadric* m_quadric;

protected:
	BOOL CreateViewGLContext(HDC hDC); 
	BOOL SetWindowPixelFormat(HDC hDC);

	void OnView();

public:
	BOOL ActivateCurrentContext();
	int OnCreate(HDC hDC);
	void InitializeDS();
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


