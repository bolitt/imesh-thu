// Painter.cpp : 实现文件
//

#include "stdafx.h"
#include "IMesh.h"
#include "Visualizer.h"
#include "PositionHelper.h"
#include "Config.h"


namespace IMesh {
namespace UI { // namespace IMesh::UI


// CPainter
CVisualizer::CVisualizer() : m_renderLock(&m_renderCriticalSection)
{
	m_GLPixelIndex = 0;
	m_hGLContext = NULL;
	m_hDC = NULL;
	m_workerThread = NULL;
	m_isLoaded = false;
	m_isWorkerRunning = false;
}

CVisualizer::~CVisualizer()
{
	// TODO: Add your message handler code here
	DisactivateCurrentContext();
	if(this->m_hGLContext!=NULL)
	{
		wglDeleteContext(this->m_hGLContext);
		this->m_hGLContext = NULL;
	}
	
	if (m_workerThread != NULL)
	{
		m_workerThread->SuspendThread();
		m_workerThread->ExitInstance();
		//m_workerThread->Delete();
		m_workerThread = NULL;
	}
	if (m_renderLock.IsLocked()) 
	{
		m_renderLock.Unlock();
	}
}


#pragma region Drawer

void CVisualizer::PreCreateWindow( CREATESTRUCT& cs )
{
	cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
}

void CVisualizer::OnSetup()
{
	m_scene.OnSetup();

	m_triangulateEventListener.Initialize(this, &m_scene.m_meshLayer);
	// for test:
	/*InitializeDS();
	OnTriangulate();*/
}

void CVisualizer::LoadCloud(char* filepath /* =NULL */)
{
	if (m_isLoaded) {
		theApp.GetMainFrame()->AddDebug(_T("已经导入！"));
		theApp.GetMainFrame()->AddDebug(_T("如需导入新模型，请先新建页面"));
		MessageBeep(MB_ICONERROR);
		return;
	}

	if (filepath == NULL) {
		m_cloud.Initialize();
	}
	else {
		m_cloud.Initialize(filepath);
	}

	// attach event
	m_scene.m_adjuster.Initialize(m_cloud.GetLowestDim(), m_cloud.GetHighestDim());
	m_scene.m_cloudLayer.SetLayer(m_cloud);

	class WorkerThread : public CWinThread
	{
	public:
		CloudInit& m_cloud;
		TriangulateEventListener& m_listener;
		WorkerThread(CloudInit& cloud, 
					TriangulateEventListener& listener) 
						: m_cloud(cloud), m_listener(listener)
		{
			m_bAutoDelete = TRUE;
		}

		~WorkerThread() 
		{
		}
	public:
		BOOL InitInstance()
		{
			m_cloud.m_triangleHandler.m_event.Attach(m_listener);
			return CWinThread::InitInstance();
		}
		int ExitInstance()
		{
			m_listener.m_bExitThread = TRUE;
			m_cloud.m_triangleHandler.m_event.Detach(m_listener);
			return CWinThread::ExitInstance();
		}
		int Run()
		{
			m_listener.SetOwnerThreadId(this->m_nThreadID);
			m_cloud.RunTriangulate();
			return 0;
		}
	};

	m_workerThread = new WorkerThread(m_cloud, m_triangulateEventListener);
	BOOL isCreated = m_workerThread->CreateThread(CREATE_SUSPENDED);
	
	if (isCreated)
	{
		m_workerThread->InitInstance();
	}
	m_isLoaded = true;
}


void CVisualizer::OnSize( UINT nType, int cx, int cy )
{
	m_canvasSize.SetSize(cx, cy);
}

Num::GL::Vec3GLdouble CVisualizer::CameraToPos()
{
	PosVec3d& spherePos = m_camera.ToPolarVec3();
	PosVec3d& orthPos = PositionHelper::Sphere2Orth(spherePos);
	return orthPos;
}

Num::GL::Vec3GLdouble CVisualizer::CameraFindUp()
{
	PosVec3d& spherePos = m_camera.ToPolarVec3();
	PosVec3d& orthPos = PositionHelper::SphereFindTopOrth(spherePos);
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

	m_renderLock.Lock();

	ActivateCurrentContext();
	{
		GLsizei width = m_canvasSize.cx;
		GLsizei height = m_canvasSize.cy;
		//if (width == 0 || height == 0) { m_renderLock.Unlock(); return; } // to avoid zero-size assertion
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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		{
			m_scene.OnRender();
		}
	}
	
	glFlush();

	::SwapBuffers(m_hDC);

	DisactivateCurrentContext();
	m_renderLock.Unlock();
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
	/*PIXELFORMATDESCRIPTOR x = {

		BYTE  iLayerType;
		BYTE  bReserved;
		DWORD dwLayerMask;
		DWORD dwVisibleMask;
		DWORD dwDamageMask;
	} */

	//定义窗口的像素格式
	PIXELFORMATDESCRIPTOR dsp =
	{
		dsp.nSize = sizeof(PIXELFORMATDESCRIPTOR),
		dsp.nVersion = 1,
		dsp.dwFlags = PFD_DRAW_TO_WINDOW |PFD_SUPPORT_OPENGL |
						PFD_DOUBLEBUFFER //|PFD_SUPPORT_GDI
						,
		dsp.iPixelType = PFD_TYPE_RGBA,
		dsp.cColorBits = 24,
		dsp.cRedBits=0, dsp.cRedShift=0,
		dsp.cGreenBits=0, dsp.cGreenShift=0,
		dsp.cBlueBits=0, dsp.cBlueShift=0,
		dsp.cAlphaBits=0, dsp.cAlphaShift=0,
		dsp.cAccumBits=0,
		dsp.cAccumRedBits=0, dsp.cAccumGreenBits=0, dsp.cAccumBlueBits=0, dsp.cAccumAlphaBits=0,
		dsp.cDepthBits=32,
		dsp.cStencilBits=0,
		dsp.cAuxBuffers=0,
		dsp.iLayerType=PFD_MAIN_PLANE,
		dsp.bReserved=0,
		dsp.dwLayerMask=0, dsp.dwVisibleMask=0, dsp.dwDamageMask=0
	};

	this->m_GLPixelIndex = ChoosePixelFormat(hDC, &dsp);
	if(this->m_GLPixelIndex==0)
	{
		this->m_GLPixelIndex = 1;
		if(DescribePixelFormat(hDC,this->m_GLPixelIndex, sizeof(PIXELFORMATDESCRIPTOR),&dsp)==0)
		{
			return FALSE;
		}
	}

	if(SetPixelFormat(hDC,this->m_GLPixelIndex,&dsp)==FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

int CVisualizer::OnCreate( HDC hDC )
{
	m_hDC = hDC;

	if(this->SetWindowPixelFormat(m_hDC) == FALSE)
	{
		return -1;
	}
	if(this->CreateViewGLContext(m_hDC) == FALSE)
	{
		return -1;
	}
	if(this->ActivateCurrentContext() == FALSE) {
		return -1;
	}
	

	OnSetup();
	return 0;
}


void CVisualizer::DisactivateCurrentContext()
{
	if(wglGetCurrentContext()!=NULL)
	{
		wglMakeCurrent(NULL,NULL);
	}
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
}

void CVisualizer::OnViewRotate( double deltaX, double deltaY )
{
	using namespace IMesh::UI::Config::Navigation;

	double rotateX = - deltaX / m_canvasSize.cx * DEG_PER_ROTATE_RATE;
	double rotateY = deltaY / m_canvasSize.cy * DEG_PER_ROTATE_RATE;
	m_camera.Rotate(rotateX, rotateY);
}

void CVisualizer::OnTriangulate(TriangulateEventListener::ControlSignal signal)
{
	if (!m_isLoaded) {
		//CView* pView = theApp.GetMainFrame()->MDIGetActive()->GetActiveView();
		//HWND h = (pView != NULL) ? pView->GetSafeHwnd() : NULL;
		//MessageBox(NULL, _T("请先导入模型"), _T("操作错误"), MB_ICONERROR | MB_OK);
		theApp.GetMainFrame()->AddDebug(_T("请先导入点云模型"));
		MessageBeep(MB_ICONERROR);
		return;
	}

	m_triangulateEventListener.SetSignal(signal);
	if (!m_isWorkerRunning) {
		m_isWorkerRunning = true;
		m_workerThread->Run();
		//m_cloudEngine.RunTriangulate();
	}
}

void CVisualizer::OnTriangulateStep()
{
	OnTriangulate(TriangulateEventListener::Step);
}

void CVisualizer::OnTriangulateDemo()
{
	OnTriangulate(TriangulateEventListener::Continue);
}

void CVisualizer::OnTriangulatePause()
{
	OnTriangulate(TriangulateEventListener::Pause);
}

void CVisualizer::OnTriangulateToEnd()
{
	OnTriangulate(TriangulateEventListener::RunToEnd);
}


#pragma endregion Drawer



// CPainter 成员函数

}}