#pragma once


namespace IMesh { 
namespace UI { // namespace IMesh::UI

// CPainter ÃüÁîÄ¿±ê

class CPainter : public CObject
{
public:
	CPainter();
	virtual ~CPainter();

protected:
	HGLRC m_hGLContext;
	int m_GLPixelIndex;
	HDC m_hDC;

protected:
	BOOL CreateViewGLContext(HDC hDC); 
	BOOL SetWindowPixelFormat(HDC hDC);

public:
	BOOL ActivateCurrentContext();
	int OnCreate(HDC hDC);
	void PreCreateWindow(CREATESTRUCT& cs);
	void OnSize(UINT nType, int cx, int cy);
	void OnPaint(HDC hDC);

};

}}


