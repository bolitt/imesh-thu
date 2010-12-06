// Painter.cpp : 实现文件
//

#include "stdafx.h"
#include "IMesh.h"
#include "Visualizer.h"
#include "Config.h"

// use M_PI
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#include <cmath>
#endif


namespace IMesh { 
namespace UI { // namespace IMesh::UI


// CPainter
CVisualizer::CVisualizer()
{
	m_GLPixelIndex = 0;
	m_hGLContext = NULL;
	m_hDC = NULL;
}

CVisualizer::~CVisualizer()
{
	// TODO: Add your message handler code here
	if(wglGetCurrentContext()!=NULL)
	{
		wglMakeCurrent(NULL,NULL);
	}
	if(this->m_hGLContext!=NULL)
	{
		wglDeleteContext(this->m_hGLContext);
		this->m_hGLContext = NULL;
	}
	//SAFE_DELETE(m_hDC);
}


#pragma region Drawer

void CVisualizer::PreCreateWindow( CREATESTRUCT& cs )
{
	cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
}


void CVisualizer::OnSize( UINT nType, int cx, int cy )
{
	ActivateCurrentContext();

	GLsizei width, height;
	GLdouble aspect, fovy, zNear, zFar;
	width = cx;
	height = cy;
	if(cy==0)
	{
		aspect = (GLdouble)cx;
	}
	else
	{
		aspect = (GLdouble)cx / (GLdouble)cy;
	}
	fovy = 90;
	zNear = -50;
	zFar = -1000;
	
	OnView();
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1, 0, 1, -1, 1);
	//gluPerspective(fovy, aspect, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	
}

void CVisualizer::OnView()
{
	gluLookAt(0, 0, 100, 
				0, 0, -1, 
				0, 1, 0);
}

void CVisualizer::OnPaint( HDC hDC )
{
	using namespace Config;
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	{
		glBegin(GL_POLYGON);
		glColor4fv(Colors::RED);
		glVertex3f(0.5f, 0.2f, 0.0f);
		glColor4fv(Colors::GREEN);
		glVertex3f(0.6f, 0.4f, 0.0f);
		glColor4fv(Colors::BLUE);
		glVertex3f(0.6f, 0.2f, 0.0f);
		glEnd();
	}
	glFlush();

	::SwapBuffers(hDC);
}

BOOL CVisualizer::CreateViewGLContext( HDC hDC )
{
	this->m_hGLContext = wglCreateContext(hDC);
	if(this->m_hGLContext==NULL)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CVisualizer::SetWindowPixelFormat( HDC hDC )
{
	//定义窗口的像素格式
	PIXELFORMATDESCRIPTOR pixelDesc=
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|
		PFD_DOUBLEBUFFER|PFD_SUPPORT_GDI,
		PFD_TYPE_RGBA,
		24,
		0,0,0,0,0,0,
		0,
		0,
		0,
		0,0,0,0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};

	this->m_GLPixelIndex = ChoosePixelFormat(hDC, &pixelDesc);
	if(this->m_GLPixelIndex==0)
	{
		this->m_GLPixelIndex = 1;
		if(DescribePixelFormat(hDC,this->m_GLPixelIndex, sizeof(PIXELFORMATDESCRIPTOR),&pixelDesc)==0)
		{
			return FALSE;
		}
	}

	if(SetPixelFormat(hDC,this->m_GLPixelIndex,&pixelDesc)==FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

int CVisualizer::OnCreate( HDC hDC )
{
	if(this->SetWindowPixelFormat(hDC) == FALSE)
	{
		return -1;
	}
	if(this->CreateViewGLContext(hDC) == FALSE)
	{
		return -1;
	}
	m_hDC = hDC;
	if(this->ActivateCurrentContext() == FALSE) {
		return -1;
	}
	return 0;
}

BOOL CVisualizer::ActivateCurrentContext()
{
	if (wglGetCurrentContext() != this->m_hGLContext) {
		if(wglMakeCurrent(m_hDC, this->m_hGLContext)==FALSE)
		{
			return FALSE;
		}
	} else {
		
	}
	
	return TRUE;
}


#pragma endregion Drawer



// CPainter 成员函数

}}