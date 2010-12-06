
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


namespace IMesh { 
namespace UI { // namespace IMesh::UI

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
END_MESSAGE_MAP()

// CIMeshView 构造/析构

CIMeshView::CIMeshView()
{
	// TODO: 在此处添加构造代码
}

CIMeshView::~CIMeshView()
{
}

BOOL CIMeshView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	m_painter.PreCreateWindow(cs);
	return CView::PreCreateWindow(cs);
}

// CIMeshView 绘制

void CIMeshView::OnDraw(CDC* pCDC/*pDC*/)
{
	CIMeshDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	theApp.GetMainFrame()->AddDebug(_T("OnDraw"));
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



void CIMeshView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CString str;
	str.Format(_T("OnSize %s"), this->GetDocument()->GetTitle());
	theApp.GetMainFrame()->AddDebug(str);
	// TODO: 在此处添加消息处理程序代码
	m_painter.OnSize(nType, cx, cy);
}


void CIMeshView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CView::OnPaint()
	HDC hDC = dc.GetSafeHdc();
	CString str;
	str.Format(_T("OnPaint %s"), this->GetDocument()->GetTitle());
	theApp.GetMainFrame()->AddDebug(str);
	//m_painter.ActivateCurrentContext(hDC);
	m_painter.OnPaint(hDC);
}


int CIMeshView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	theApp.GetMainFrame()->AddDebug(_T("OnCreate"));
	HWND hwnd = GetSafeHwnd();
	HDC hDC = ::GetDC(hwnd);
	return m_painter.OnCreate(hDC);
}



void CIMeshView::OnNcPaint()
{
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CView::OnNcPaint()
	CString str;
	str.Format(_T("OnNcPaint %s"), this->GetDocument()->GetTitle());
	theApp.GetMainFrame()->AddDebug(str);
	m_painter.ActivateCurrentContext();
}


BOOL CIMeshView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

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

}}