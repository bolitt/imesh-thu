
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CIMeshView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_NCMOUSELEAVE()
	ON_WM_NCPAINT()
	ON_WM_PAINT()
	ON_COMMAND(ID_FILE_OPEN, &CIMeshView::OnFileOpen)
	ON_COMMAND(ID_TRIANGULATE, &CIMeshView::OnTriangulate)
	ON_COMMAND(ID_TRIANGULATE_STEP, &CIMeshView::OnTriangulateStep)
	ON_COMMAND(ID_TRIANGULATE_DEMO, &CIMeshView::OnTriangulateDemo)
	ON_COMMAND(ID_TRIANGULATE_PAUSE, &CIMeshView::OnTriangulatePause)
	ON_COMMAND(ID_TRIANGULATE_TO_END, &CIMeshView::OnTriangulateToEnd)
	ON_COMMAND(ID_SETTING_DIALOG_OPEN, &CIMeshView::OnSettingDialogOpen)
END_MESSAGE_MAP()

// CIMeshView ����/����

CIMeshView::CIMeshView()
{
	// TODO: �ڴ˴���ӹ������
	m_bLeftButtonDown = false;
	m_pSettingDialog = NULL;
}

CIMeshView::~CIMeshView()
{
	if (m_pSettingDialog != NULL) {
		m_pSettingDialog->DestroyWindow();
		m_pSettingDialog = NULL;
	}
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
}

void CIMeshView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	m_vis.OnSize(nType, cx, cy);
}


int CIMeshView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	theApp.GetMainFrame()->AddDebug(_T("Created New Demo Scene"));
	theApp.GetMainFrame()->AddDebug(_T("++ Please Load Model First! ++"));
	HWND hwnd = GetSafeHwnd();
	HDC hDC = ::GetDC(hwnd);
	return m_vis.OnCreate(hDC);
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
	m_vis.OnRender();
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CIMeshView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bLeftButtonDown = true;

#ifndef SHARED_HANDLERS
	HMENU hmenu = theApp.GetContextMenuManager()->GetMenuById(IDR_POPUP_EDIT);
	DestroyMenu(hmenu);
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
	
	
	CView::OnLButtonDown(nFlags, point);
}


void CIMeshView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bLeftButtonDown = false;

	CView::OnLButtonUp(nFlags, point);
}

void CIMeshView::OnNcMouseLeave()
{
	// �ù���Ҫ��ʹ�� Windows 2000 ����߰汾��
	// ���� _WIN32_WINNT �� WINVER ���� >= 0x0500��
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bLeftButtonDown = false;
	CView::OnNcMouseLeave();
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
		m_vis.OnRender();
	}
	
	m_ptPrevMouseMove = point;
	CView::OnMouseMove(nFlags, point);
}


void CIMeshView::OnFileOpen()
{
	// TODO: �ڴ���������������
	CFileDialog openFileDialog(TRUE, _T(".obj"), NULL, 0, 
					_T("Obj Files (*.obj)|*.obj|All Files (*.*)|*.*|"));
	
	if (openFileDialog.DoModal() == IDOK) {
		CString filePathName;
		filePathName = openFileDialog.GetPathName();
		theApp.GetMainFrame()->AddDebug(_T("Open Model:") + filePathName);
		
		char pFilePath[4096];
		StringHelper::CStringToMultiByte(pFilePath, filePathName);
		
		m_vis.LoadCloud(pFilePath);
		m_vis.OnRender();
	}
}


void CIMeshView::OnTriangulate()
{
	// TODO: �ڴ���������������
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
	OnTriangulateDemo();
}

void CIMeshView::OnTriangulateStep()
{
	theApp.GetMainFrame()->AddDebug(_T("Step"));
	m_vis.OnTriangulateStep();
}

void CIMeshView::OnTriangulateDemo()
{
	theApp.GetMainFrame()->AddDebug(_T("Run: Demo"));
	m_vis.OnTriangulateDemo();
}

void CIMeshView::OnTriangulatePause()
{
	theApp.GetMainFrame()->AddDebug(_T("Pause"));
	m_vis.OnTriangulatePause();
}

void CIMeshView::OnTriangulateToEnd()
{
	theApp.GetMainFrame()->AddDebug(_T("Run: To End"));
	m_vis.OnTriangulateToEnd();
}


void CIMeshView::OnNcPaint()
{
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CView::OnNcPaint()
}


void CIMeshView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CView::OnPaint()
	m_vis.OnRender();
}

void CIMeshView::OnSettingDialogOpen()
{
	if (m_pSettingDialog == NULL) {
		m_pSettingDialog = new CDisplayDialog();
		m_pSettingDialog->m_pVis = &m_vis;
		m_pSettingDialog->Create(IDD_DISPLAY_DIALOG, this);
		m_pSettingDialog->ShowWindow(SW_SHOW);
		m_pSettingDialog->BringWindowToTop();
	} else {
		m_pSettingDialog->ShowWindow(SW_SHOW);
		m_pSettingDialog->BringWindowToTop();
		m_pSettingDialog->SetFocus();
	}
}


END_NAMESPACE2(IMesh, UI)
