// Painter.cpp : 实现文件
//

#include "stdafx.h"
#include "IMesh.h"
#include "Painter.h"
#include "Config.h"

namespace IMesh { 
namespace UI { // namespace IMesh::UI


// CPainter
CPainter::CPainter()
{
	m_GLPixelIndex = 0;
	m_hGLContext = NULL;
	m_hDC = NULL;
}

CPainter::~CPainter()
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

void CPainter::PreCreateWindow( CREATESTRUCT& cs )
{
	cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
}


void CPainter::OnSize( UINT nType, int cx, int cy )
{
	ActivateCurrentContext();

	GLsizei width, height;
	GLdouble aspect;
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
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,500.0*aspect,0.0,500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CPainter::OnPaint( HDC hDC )
{
	using namespace Config;
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	{
		glBegin(GL_POLYGON);
		glColor4fv(Colors::RED);
		glVertex2f(100.0f,50.0f);
		glColor4fv(Colors::GREEN);
		glVertex2f(450.0f,400.0f);
		glColor4fv(Colors::BLUE);
		glVertex2f(450.0f,50.0f);
		glEnd();
	}
	glFlush();

	::SwapBuffers(hDC);
}

BOOL CPainter::CreateViewGLContext( HDC hDC )
{
	this->m_hGLContext = wglCreateContext(hDC);
	if(this->m_hGLContext==NULL)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CPainter::SetWindowPixelFormat( HDC hDC )
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

int CPainter::OnCreate( HDC hDC )
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

BOOL CPainter::ActivateCurrentContext()
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