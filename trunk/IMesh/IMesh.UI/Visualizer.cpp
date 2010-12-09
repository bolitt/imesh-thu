// Painter.cpp : 实现文件
//

#include "stdafx.h"
#include "IMesh.h"
#include "Visualizer.h"
#include "Config.h"


namespace IMesh { 
namespace UI { // namespace IMesh::UI

	class Helper
	{
	public:
		static PosVec3d Orth2Sphere(const PosVec3d& v) {
			PosVec3d orth;
			return orth;
		}

		static PosVec3d Sphere2Orth(const PosVec3d& v) {
			PosVec3d orth;
			GLdouble smallRadius = v._radius * sin(v._coLatitude);
			orth._x = smallRadius * cos(v._longtitude);
			orth._y = smallRadius * sin(v._longtitude);
			orth._z = v._radius * cos(v._coLatitude);
			return orth;
		}

		static PosVec3d SphereFindTopOrth(const PosVec3d& v) {
			PosVec3d topSphere = v;
			topSphere._coLatitude -= M_PI_2;
			PosVec3d topOrth = Sphere2Orth(topSphere);
			return topOrth;
		}
	};


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


void CVisualizer::InitializeDS()
{
	m_scene.OnSetup();
}


void CVisualizer::OnSize( UINT nType, int cx, int cy )
{
	m_canvasSize.SetSize(cx, cy);
}

Num::GL::Vec3GLdouble CVisualizer::CameraToPos()
{
	PosVec3d& spherePos = m_camera.ToPolarVec3();
	PosVec3d& orthPos = Helper::Sphere2Orth(spherePos);
	return orthPos;
}

Num::GL::Vec3GLdouble CVisualizer::CameraFindUp()
{
	PosVec3d& spherePos = m_camera.ToPolarVec3();
	PosVec3d& orthPos = Helper::SphereFindTopOrth(spherePos);
	return orthPos;
}


void CVisualizer::OnView()
{
}

void GLCheckError()
{
	GLenum error = glGetError();
}

void CVisualizer::OnRender()
{
	using namespace Config;
	
	ActivateCurrentContext();
	{		
		GLsizei width = m_canvasSize.cx;
		GLsizei height = m_canvasSize.cy;
		GLdouble aspect = (height != 0) ? (GLdouble)width / (GLdouble)height : 1;
	
		glViewport(0, 0, width, height);
		//glScissor(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//glOrtho(0, 1, 0, 1, -1, 1);
		m_projection.Reshape((double)width, (double)height);
		glFrustum(m_projection.m_left, m_projection.m_right, 
				 m_projection.m_bottom, m_projection.m_top, 
				 m_projection.m_zNear, m_projection.m_zFar);
		glMatrixMode(GL_MODELVIEW);
	}
	
	{
		glLoadIdentity();
		PosVec3d& orthPos = CameraToPos();
		PosVec3d& upVec = CameraFindUp();
		/*gluLookAt(0, 0, 10, 
				0, 0, -1, 
				0, 1, 0); */
		gluLookAt(orthPos._x, orthPos._y, orthPos._z, 
				0, 0, 0, 
				upVec._x, upVec._y, upVec._z);
	}

	{
		glClear(GL_COLOR_BUFFER_BIT);
		{
			m_scene.OnRender();
		}

		{
			
		}
	}
	
	glFlush();
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
	InitializeDS();
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

void CVisualizer::OnViewZoom( double delta )
{
	Camera::ZoomType z = (delta < 0) ? Camera::CAMERA_ZOOM_IN : Camera::CAMERA_ZOOM_OUT;
	m_camera.Zoom(z);
	OnView();
}

void CVisualizer::OnViewRotate( double deltaX, double deltaY )
{
	using namespace IMesh::UI::Config::Navigation;

	double rotateX = - deltaX / m_canvasSize.cx * DEG_PER_ROTATE_RATE;
	double rotateY = deltaY / m_canvasSize.cy * DEG_PER_ROTATE_RATE;
	m_camera.Rotate(rotateX, rotateY);
	OnView();
}


#pragma endregion Drawer



// CPainter 成员函数

}}