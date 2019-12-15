#ifndef _WTL_NO_WTYPES
#define _WTL_NO_WTYPES
#endif

#include "stdafx.h"
#include "resource.h"
#include "xui_shfrm.h"
#include "xui_shfrmctrl.h"

#ifdef __USE_WTL__

CXUI_SHFrameCtrl::CXUI_SHFrameCtrl(CXUI_SHForm* pFrm)
{
	m_szClass = L"CXUI_SHFrameCtrl";
	m_szName = L"";
	m_bLive = false;
	m_pFrmMaster = pFrm;
}

CXUI_SHFrameCtrl::CXUI_SHFrameCtrl(std::wstring& szName, CXUI_SHForm* pFrm)
{
	m_szClass = L"CXUI_SHFrameCtrl";
	m_szName = szName;
	m_bLive = false;
	m_pFrmMaster = pFrm;
}

CXUI_SHFrameCtrl::CXUI_SHFrameCtrl(const wchar_t* szName, CXUI_SHForm* pFrm)
{
	m_szClass = L"CXUI_SHFrameCtrl";
	m_szName = szName;
	m_bLive = false;
	m_pFrmMaster = pFrm;
}

CXUI_SHFrameCtrl::~CXUI_SHFrameCtrl()
{
	m_pFrmMaster = NULL;
}

BOOL CXUI_SHFrameCtrl::PreTranslateMessage(MSG* pMsg)
{
	return CFrameWindowImpl<CXUI_SHFrameCtrl>::PreTranslateMessage(pMsg);
}


BOOL CXUI_SHFrameCtrl::OnIdle()
{
	UIUpdateToolBar();
	return FALSE;
}

bool CXUI_SHFrameCtrl::CreateForm(void)
{
	bool bRet = false;

	RECT rect;
	rect.left = 0;
	rect.right = 640;
	rect.top = 0;
	rect.bottom = 480;

	long nStyle = WS_OVERLAPPEDWINDOW | WS_BORDER | WS_THICKFRAME;
	long nExtStyle = WS_EX_OVERLAPPEDWINDOW | WS_EX_STATICEDGE;

	HWND hWnd = CreateEx(NULL, ATL::_U_RECT(&rect), nStyle, nExtStyle, NULL);
	if(hWnd != NULL)
		bRet = true;

	return bRet;
}

LRESULT CXUI_SHFrameCtrl::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// create command bar window
	m_bLive = true;

	SetMenu(NULL);

	SetWindowText(_T("System Shell Process"));

	CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);


	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	SendMessage(XUI_SHCMDRUN);

	return 0;
}

void CXUI_SHFrameCtrl::OnFinalMessage(HWND hWnd)
{
	// TODO: Add your specialized code here and/or call the base class
	m_bLive = false;

	__super::OnFinalMessage(hWnd);
}

LRESULT CXUI_SHFrameCtrl::OnRunSHCmd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
//	if(m_pFrmMaster)
//	{
//		m_pFrmMaster->RunCommand();
//	}
	return 1L;
}


#endif
