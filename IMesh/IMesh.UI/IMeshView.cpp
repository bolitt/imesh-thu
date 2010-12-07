
// IMeshView.cpp : CIMeshView ���ʵ��
//


#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "IMesh.h"
#endif

#include "IMeshDoc.h"
#include "IMeshView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_NAMESPACE2(IMesh, UI)

// CIMeshView

IMPLEMENT_DYNCREATE(CIMeshView, CView)

BEGIN_MESSAGE_MAP(CIMeshView, CView)
	// ��׼��ӡ����
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
END_MESSAGE_MAP()

// CIMeshView ����/����

CIMeshView::CIMeshView()
{
	// TODO: �ڴ˴���ӹ������
	m_bLeftButtonDown = false;
}

CIMeshView::~CIMeshView()
{
	
}

BOOL CIMeshView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	m_vis.PreCreateWindow(cs);
	return CView::PreCreateWindow(cs);
}



// CIMeshView ��ӡ


void CIMeshView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CIMeshView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CIMeshView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CIMeshView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CIMeshView ���

#ifdef _DEBUG
void CIMeshView::AssertValid() const
{
	CView::AssertValid();
}

void CIMeshView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIMeshDoc* CIMeshView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIMeshDoc)));
	return (CIMeshDoc*)m_pDocument;
}
#endif //_DEBUG


// CIMeshView ��Ϣ�������


// CIMeshView ����

void CIMeshView::OnDraw(CDC* pCDC/*pDC*/)
{
	CIMeshDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	//theApp.GetMainFrame()->AddDebug(_T("OnDraw"));
}

void CIMeshView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	/*CString str;
	str.Format(_T("OnSize %s"), this->GetDocument()->GetTitle());
	theApp.GetMainFrame()->AddDebug(str);*/
	// TODO: �ڴ˴������Ϣ����������
	m_vis.OnSize(nType, cx, cy);
}


void CIMeshView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CView::OnPaint()
	HDC hDC = dc.GetSafeHdc();
	CString str;
	/*str.Format(_T("OnPaint %s"), this->GetDocument()->GetTitle());
	theApp.GetMainFrame()->AddDebug(str);*/
	//m_painter.ActivateCurrentContext(hDC);
	m_vis.OnRender();

	::SwapBuffers(hDC);
}


int CIMeshView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	theApp.GetMainFrame()->AddDebug(_T("OnCreate"));
	HWND hwnd = GetSafeHwnd();
	HDC hDC = ::GetDC(hwnd);
	return m_vis.OnCreate(hDC);
}



void CIMeshView::OnNcPaint()
{
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CView::OnNcPaint()
	//CString str;
	/*str.Format(_T("OnNcPaint %s"), this->GetDocument()->GetTitle());
	theApp.GetMainFrame()->AddDebug(str);*/
	//m_vis.ActivateCurrentContext();
}


BOOL CIMeshView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bLeftButtonDown = true;

	CView::OnLButtonDown(nFlags, point);
}


void CIMeshView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bLeftButtonDown = false;

	CView::OnLButtonUp(nFlags, point);
}

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


END_NAMESPACE2(IMesh, UI)
