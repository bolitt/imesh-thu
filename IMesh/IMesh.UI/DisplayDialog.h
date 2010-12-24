#pragma once

#include "resource.h"

#include "Visualizer.h"

BEGIN_NAMESPACE2(IMesh, UI)
// CDisplayDialog 对话框

class CDisplayDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CDisplayDialog)

public:
	CDisplayDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDisplayDialog();
	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_DISPLAY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL m_bEnabledSurface;
	BOOL m_bEnabledMesh;
	BOOL m_bEnabledNormal;
	BOOL m_bEnabledSiftPoints;

public:
	CVisualizer* m_pVis;

public:
	void UpdateDisplay();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

public:
	afx_msg void OnBnClickedCheckDisplaySurface();
	afx_msg void OnBnClickedCheckDisplayMesh();
	afx_msg void OnBnClickedCheckDisplayNormal();
};

END_NAMESPACE2(IMesh, UI)

