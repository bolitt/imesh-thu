#pragma once


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
	
	GLdouble m_Longtitude; // x on sphere
	GLdouble m_Latitude;   // y on sphere
	GLdouble m_Height;     // z on sphere


protected:
	BOOL CreateViewGLContext(HDC hDC); 
	BOOL SetWindowPixelFormat(HDC hDC);

public:
	BOOL ActivateCurrentContext();
	int OnCreate(HDC hDC);
	void PreCreateWindow(CREATESTRUCT& cs);
	void OnSize(UINT nType, int cx, int cy);
	void OnPaint(HDC hDC);
	void OnView();
};

}}


