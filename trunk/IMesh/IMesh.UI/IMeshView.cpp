
// IMeshView.cpp : CIMeshView 类的实现
//


#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "IMesh.h"
#endif

#include "IMeshDoc.h"
#include "IMeshView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_NAMESPACE2(IMesh, UI)

	class StringHelper 
	{public:
		static void CStringToMultiByte(char* dst, CString& sourceStr)
		{
			TCHAR*  wstr = sourceStr.GetBuffer();
			int   nLen   =   wcslen(wstr)+1;
			WideCharToMultiByte(CP_ACP, 0, wstr, nLen, dst, 2*nLen, NULL, NULL);
			sourceStr.ReleaseBuffer();
		}
	};


// CIMeshView

IMPLEMENT_DYNCREATE(CIMeshView, CView)

BEGIN_MESSAGE_MAP(CIMeshView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CIMeshView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_NCPAINT()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_Triangulate, &CIMeshView::OnTriangulate)
	ON_COMMAND(ID_FILE_OPEN, &CIMeshView::OnFileOpen)
//	ON_WM_MOUSELEAVE()
ON_WM_NCMOUSELEAVE()
END_MESSAGE_MAP()

// CIMeshView 构造/析构

CIMeshView::CIMeshView()
{
	// TODO: 在此处添加构造代码
	m_bLeftButtonDown = false;
}

CIMeshView::~CIMeshView()
{
	
}

BOOL CIMeshView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	m_vis.PreCreateWindow(cs);
	return CView::PreCreateWindow(cs);
}



// CIMeshView 打印


void CIMeshView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CIMeshView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CIMeshView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CIMeshView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CIMeshView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CIMeshView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CIMeshView 诊断

#ifdef _DEBUG
void CIMeshView::AssertValid() const
{
	CView::AssertValid();
}

void CIMeshView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIMeshDoc* CIMeshView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIMeshDoc)));
	return (CIMeshDoc*)m_pDocument;
}
#endif //_DEBUG


// CIMeshView 消息处理程序


// CIMeshView 绘制

void CIMeshView::OnDraw(CDC* pCDC/*pDC*/)
{
	CIMeshDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	//theApp.GetMainFrame()->AddDebug(_T("OnDraw"));
}

void CIMeshView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	/*CString str;
	str.Format(_T("OnSize %s"), this->GetDocument()->GetTitle());
	theApp.GetMainFrame()->AddDebug(str);*/
	// TODO: 在此处添加消息处理程序代码
	m_vis.OnSize(nType, cx, cy);
}


void CIMeshView::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CView::OnPaint()
	//HDC hDC = dc.GetSafeHdc();
	//CString str;
	//str.Format(_T("OnPaint %s"), this->GetDocument()->GetTitle());
	// theApp.GetMainFrame()->AddDebug(str);
	//m_painter.ActivateCurrentContext(hDC);
	m_vis.OnRender();
}


int CIMeshView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	theApp.GetMainFrame()->AddDebug(_T("OnCreate"));
	HWND hwnd = GetSafeHwnd();
	HDC hDC = ::GetDC(hwnd);
	return m_vis.OnCreate(hDC);
}



void CIMeshView::OnNcPaint()
{
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CView::OnNcPaint()
	//CString str;
	/*str.Format(_T("OnNcPaint %s"), this->GetDocument()->GetTitle());
	theApp.GetMainFrame()->AddDebug(str);*/
	//m_vis.ActivateCurrentContext();
}


BOOL CIMeshView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	double delta = zDelta;

	/*CString str;
	const Camera& c = m_vis.m_camera;
	str.Format(_T("Zoom (%f, %f, %f)"), c.m_angleX, c.m_angleY, c.m_distance);
	theApp.GetMainFrame()->AddDebug(str);*/
	
	m_vis.OnViewZoom(delta);
	this->OnPaint();
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CIMeshView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bLeftButtonDown = true;

	CView::OnLButtonDown(nFlags, point);
}


void CIMeshView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bLeftButtonDown = false;

	CView::OnLButtonUp(nFlags, point);
}

void CIMeshView::OnNcMouseLeave()
{
	// 该功能要求使用 Windows 2000 或更高版本。
	// 符号 _WIN32_WINNT 和 WINVER 必须 >= 0x0500。
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bLeftButtonDown = false;
	CView::OnNcMouseLeave();
}

//void CIMeshView::OnMouseLeave()
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	m_bLeftButtonDown = false;
//	theApp.GetMainFrame()->AddDebug(_T("OnMouseLeave"));
//	CView::OnMouseLeave();
//}


void CIMeshView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	
	if (m_bLeftButtonDown) {
		double dx = point.x - m_ptPrevMouseMove.x;
		double dy = point.y - m_ptPrevMouseMove.y;
		CString str;
		//str.Format(_T("New: (%d, %d)  Old: (%d, %d)"), point.x, point.y, 
		//									m_ptPrevMouseMove.x, m_ptPrevMouseMove.y);
		//const Camera& c = m_vis.m_camera;
		//str.Format(_T("Move (%f, %f, %f)"), c.m_angleX, c.m_angleY, c.m_distance);
		//theApp.GetMainFrame()->AddDebug(str);
		
		m_vis.OnViewRotate(dx, dy);
		this->OnPaint();
	}
	
	m_ptPrevMouseMove = point;
	CView::OnMouseMove(nFlags, point);
}

void CIMeshView::OnTriangulate()
{
	// TODO: 在此添加命令处理程序代码
	//CMainFrame* pMainFrame = static_cast<CMainFrame*>(this->GetActiveWindow());
	//// SDI:
	////   CView* pView = pMainFrame->GetActiveView(); 
	//// MDI:
	//CView* pView = pMainFrame->MDIGetActive()->GetActiveView();
	//CIMeshView* pChildView = static_cast<CIMeshView*>(pView);
	//
	//if (pChildView != NULL)
	//{
	//	theApp.GetMainFrame()->AddDebug(_T("CIMeshView::OnTriangulate()"));
	//}
	//else 
	//{
	//	theApp.GetMainFrame()->AddDebug(_T("CIMeshView::OnTriangulate() Failed"));
	//}
	theApp.GetMainFrame()->AddDebug(_T("CIMeshView::OnTriangulate()"));
	m_vis.OnTriangulate();
	OnPaint();
	theApp.GetMainFrame()->AddDebug(_T("CIMeshView::OnTriangulate() OK"));
}


void CIMeshView::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	theApp.GetMainFrame()->AddDebug(_T("OnFileOpen"));
	CFileDialog openFileDialog(TRUE, _T(".obj"), NULL, 0, 
					_T("Obj Files (*.obj)|*.obj|All Files (*.*)|*.*|"));
	
	if (openFileDialog.DoModal() == IDOK) {
		CString filePathName;
		filePathName = openFileDialog.GetPathName();
		theApp.GetMainFrame()->AddDebug(_T("Open:") + filePathName);
		
		char pFilePath[4096];
		StringHelper::CStringToMultiByte(pFilePath, filePathName);
		
		m_vis.InitializeDS(pFilePath);
		OnPaint();
	}
}

END_NAMESPACE2(IMesh, UI)







