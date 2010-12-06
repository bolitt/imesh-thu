
// IMeshView.h : CIMeshView ��Ľӿ�
#pragma once

#include "Visualizer.h"

BEGIN_NAMESPACE2(IMesh, UI)

class CIMeshView : public CView
{
protected: // �������л�����
	CIMeshView();
	DECLARE_DYNCREATE(CIMeshView)

// ����
public:
	CIMeshDoc* GetDocument() const;

// ����
public:


// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CIMeshView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

protected:
	CVisualizer m_vis;
	
protected:
	bool m_bLeftButtonDown;
	CPoint m_ptLeftButtonDown;
	CPoint m_ptPrevMouseMove;

public:
	afx_msg void OnNcPaint();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // IMeshView.cpp �еĵ��԰汾
inline CIMeshDoc* CIMeshView::GetDocument() const
   { return reinterpret_cast<CIMeshDoc*>(m_pDocument); }
#endif

END_NAMESPACE2(IMesh, UI)

