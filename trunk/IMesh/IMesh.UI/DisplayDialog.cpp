// DisplayDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "DisplayDialog.h"
#include "afxdialogex.h"


BEGIN_NAMESPACE2(IMesh, UI)
// CDisplayDialog 对话框

IMPLEMENT_DYNAMIC(CDisplayDialog, CDialogEx)

CDisplayDialog::CDisplayDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDisplayDialog::IDD, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

	m_bEnabledSurface = TRUE;
	m_bEnabledMesh = TRUE;
	m_bEnabledNormal = TRUE;

	m_pVis = NULL;
}

CDisplayDialog::~CDisplayDialog()
{
}

void CDisplayDialog::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CDisplayDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_DISPLAY_SURFACE, m_bEnabledSurface);
	DDX_Check(pDX, IDC_CHECK_DISPLAY_MESH, m_bEnabledMesh);
	DDX_Check(pDX, IDC_CHECK_DISPLAY_NORMAL, m_bEnabledNormal);
	UpdateDisplay();
}


BEGIN_MESSAGE_MAP(CDisplayDialog, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK_DISPLAY_SURFACE, &CDisplayDialog::OnBnClickedCheckDisplaySurface)
	ON_BN_CLICKED(IDC_CHECK_DISPLAY_MESH, &CDisplayDialog::OnBnClickedCheckDisplayMesh)
	ON_BN_CLICKED(IDC_CHECK_DISPLAY_NORMAL, &CDisplayDialog::OnBnClickedCheckDisplayNormal)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDisplayDialog, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IDisplayDialog 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {FE0BDB17-34F7-4D66-AEE3-6A5D8DDF7209}
static const IID IID_IDisplayDialog =
{ 0xFE0BDB17, 0x34F7, 0x4D66, { 0xAE, 0xE3, 0x6A, 0x5D, 0x8D, 0xDF, 0x72, 0x9 } };

BEGIN_INTERFACE_MAP(CDisplayDialog, CDialogEx)
	INTERFACE_PART(CDisplayDialog, IID_IDisplayDialog, Dispatch)
END_INTERFACE_MAP()

void CDisplayDialog::UpdateDisplay()
{
	if (m_pVis != NULL) {
		Models::Scene& scene = m_pVis->m_scene;
		scene.m_cloudLayer.m_normalsLayer.m_IsVisible = m_bEnabledNormal == TRUE ? true : false;
		scene.m_meshLayer.m_edgesLayer.m_IsVisible = m_bEnabledMesh == TRUE ? true : false;
		scene.m_meshLayer.m_trianglesLayer.m_IsVisible = m_bEnabledSurface == TRUE ? true : false;
		m_pVis->OnRender();
	}
}

// CDisplayDialog 消息处理程序


void CDisplayDialog::OnBnClickedCheckDisplaySurface()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDisplayDialog::OnBnClickedCheckDisplayMesh()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDisplayDialog::OnBnClickedCheckDisplayNormal()
{
	// TODO: 在此添加控件通知处理程序代码
}

END_NAMESPACE2(IMesh, UI)
