
// IMesh.h : IMesh Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������

#include "MainFrm.h"
// CIMeshApp:
// �йش����ʵ�֣������ IMesh.cpp
//


namespace IMesh { 
namespace UI { // namespace IMesh::UI


class CIMeshApp : public CWinAppEx
{
public:
	CIMeshApp();



// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:
	
	CMainFrame* GetMainFrame();
};

extern CIMeshApp theApp;

}}