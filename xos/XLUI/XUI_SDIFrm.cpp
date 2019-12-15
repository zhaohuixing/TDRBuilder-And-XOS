#ifndef _WTL_NO_WTYPES
#define _WTL_NO_WTYPES
#endif

#include "stdafx.h"
#include "resource.h"
#include "xui_form.h"
#include "xui_sdifrm.h"
#include "xui_btn.h"
#include "xui_img.h"
#include "xui_edit.h"
#include "xui_text.h"
#include "xui_msg.h"

#ifdef __USE_WTL__

CXUI_SDIWndFrame::CXUI_SDIWndFrame(CXUI_Form* pFrm)
{
	m_szClass = L"CXUI_SDIWndFrame";
	m_szName = L"";
	m_bLive = false;
	m_pFrmMaster = pFrm;
	DefaultStyle();
}

CXUI_SDIWndFrame::CXUI_SDIWndFrame(std::wstring& szName, CXUI_Form* pFrm)
{
	m_szClass = L"CXUI_SDIWndFrame";
	m_szName = szName;
	m_bLive = false;
	m_pFrmMaster = pFrm;
	DefaultStyle();
}

CXUI_SDIWndFrame::CXUI_SDIWndFrame(const wchar_t* szName, CXUI_Form* pFrm)
{
	m_szClass = L"CXUI_SDIWndFrame";
	m_szName = szName;
	m_bLive = false;
	m_pFrmMaster = pFrm;
	DefaultStyle();
}

CXUI_SDIWndFrame::~CXUI_SDIWndFrame()
{
	m_pFrmMaster = NULL;
}

BOOL CXUI_SDIWndFrame::PreTranslateMessage(MSG* pMsg)
{
	return CFrameWindowImpl<CXUI_SDIWndFrame>::PreTranslateMessage(pMsg);
}


BOOL CXUI_SDIWndFrame::OnIdle()
{
	UIUpdateToolBar();
	return FALSE;
}

bool CXUI_SDIWndFrame::CreateForm(void)
{
	bool bRet = false;

	RECT rect;
	rect.left = m_nLeft;
	rect.right = m_nRight;
	rect.top = m_nTop;
	rect.bottom = m_nBottom;

	HWND hWnd = CreateEx(NULL, ATL::_U_RECT(&rect), m_nStyle, m_nExtStyle, NULL);
	if(hWnd != NULL)
		bRet = true;

	return bRet;
}

LRESULT CXUI_SDIWndFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// create command bar window
	m_bLive = true;

//	HWND hWndCmdBar = m_CmdBar.Create(m_hWnd, rcDefault, NULL, ATL_SIMPLE_CMDBAR_PANE_STYLE);
	// attach menu
//	m_CmdBar.AttachMenu(GetMenu());
	// load command bar images
//	m_CmdBar.LoadImages(IDR_MAINFRAME);
	// remove old menu
	SetMenu(NULL);

	BuildCtrls();

	if(!m_szText.empty())
		SetWindowText(CW2CT(m_szText.c_str()));

//	HWND hWndToolBar = CreateSimpleToolBarCtrl(m_hWnd, IDR_MAINFRAME, FALSE, ATL_SIMPLE_TOOLBAR_PANE_STYLE);

	CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);
//	AddSimpleReBarBand(hWndCmdBar);
//	AddSimpleReBarBand(hWndToolBar, NULL, TRUE);

//	CreateSimpleStatusBar();

	//m_hWndClient = m_view.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);

//	UIAddToolBar(hWndToolBar);
//	UISetCheck(ID_VIEW_TOOLBAR, 1);
//	UISetCheck(ID_VIEW_STATUS_BAR, 1);


	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	return 0;
}

LRESULT CXUI_SDIWndFrame::OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	PostMessage(WM_CLOSE);
	return 0;
}

LRESULT CXUI_SDIWndFrame::OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: add code to initialize document

	return 0;
}

LRESULT CXUI_SDIWndFrame::OnFileNewWindow(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	::PostThreadMessage(_Module.m_dwMainThreadID, WM_USER, 0, 0L);
	return 0;
}

LRESULT CXUI_SDIWndFrame::OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	static BOOL bVisible = TRUE;	// initially visible
	bVisible = !bVisible;
	CReBarCtrl rebar = m_hWndToolBar;
	int nBandIndex = rebar.IdToIndex(ATL_IDW_BAND_FIRST + 1);	// toolbar is 2nd added band
	rebar.ShowBand(nBandIndex, bVisible);
	UISetCheck(ID_VIEW_TOOLBAR, bVisible);
	UpdateLayout();
	return 0;
}

LRESULT CXUI_SDIWndFrame::OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	BOOL bVisible = !::IsWindowVisible(m_hWndStatusBar);
	::ShowWindow(m_hWndStatusBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
	UISetCheck(ID_VIEW_STATUS_BAR, bVisible);
	UpdateLayout();
	return 0;
}

LRESULT CXUI_SDIWndFrame::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
//	CAboutDlg dlg;
//	dlg.DoModal();
	return 0;
}

LRESULT CXUI_SDIWndFrame::OnMsgHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;

	if(m_pFrmMaster)
		return m_pFrmMaster->EventHandler((long)uMsg, (long)wParam, (long)lParam);
	else
		return 0;
}

LRESULT CXUI_SDIWndFrame::OnCmdHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	bHandled = FALSE;

	if(m_pFrmMaster)
		return m_pFrmMaster->EventHandler(WM_COMMAND, WM_COMMAND, wID);
	else
		return 0;
}


void CXUI_SDIWndFrame::OnFinalMessage(HWND hWnd)
{
	// TODO: Add your specialized code here and/or call the base class
	m_bLive = false;

	if(m_pFrmMaster != NULL)
	{
		CXOS_ClassObjTable::iterator iter;

		int nCount = (int)(sizeof(XUI_CtrlClass)/sizeof(wchar_t*));

		for(iter = m_pFrmMaster->m_Property.begin(); iter != m_pFrmMaster->m_Property.end(); ++iter)
		{
			CXOS_ClassObject* pObj = iter->second;
			for(int i = 0; i < nCount; i++)
			{
				if(pObj->GetClassStr() == XUI_CtrlClass[i])
				{
					((CXUI_CtrlBase*)pObj)->DestroyCtrl();
				}
			}
		}
	}

	__super::OnFinalMessage(hWnd);
}

bool CXUI_SDIWndFrame::SetTraits(const CXUI_FormTrait& ctrlTrait)
{
	bool bRet = false;

	if(ctrlTrait.UIType() == UIType())
	{
		m_nCtrlID = ctrlTrait.m_nCtrlID;
		m_nStyle = ctrlTrait.m_nStyle;
		m_nExtStyle = ctrlTrait.m_nExtStyle;
		m_szText = ctrlTrait.m_szText;
		m_nLeft = ctrlTrait.m_nLeft;
		m_nRight = ctrlTrait.m_nRight;
		m_nTop = ctrlTrait.m_nTop;
		m_nBottom = ctrlTrait.m_nBottom;
		m_szResURL = ctrlTrait.m_szResURL;
		m_nResID = ctrlTrait.m_nResID;
		bRet = true;
	}

	return bRet;
}

CXUI_SDIWndFrame& CXUI_SDIWndFrame::operator = (const CXUI_FormTrait& ctrlTrait)
{
	if(ctrlTrait.UIType() == enXUI_FORM)
	{
		m_nCtrlID = ctrlTrait.m_nCtrlID;
		m_nStyle = ctrlTrait.m_nStyle;
		m_nExtStyle = ctrlTrait.m_nExtStyle;
		m_szText = ctrlTrait.m_szText;
		m_nLeft = ctrlTrait.m_nLeft;
		m_nRight = ctrlTrait.m_nRight;
		m_nTop = ctrlTrait.m_nTop;
		m_nBottom = ctrlTrait.m_nBottom;
		m_szResURL = ctrlTrait.m_szResURL;
		m_nResID = ctrlTrait.m_nResID;
	}

	return *this;
}

void CXUI_SDIWndFrame::DefaultStyle(void)
{
//	m_nCtrlID = IDR_MAINFRAME;
	m_nStyle = WS_OVERLAPPEDWINDOW | WS_BORDER | WS_THICKFRAME;
	m_nExtStyle = WS_EX_OVERLAPPEDWINDOW | WS_EX_STATICEDGE;
	m_szText = L"The XML System UI Service";
	m_nLeft = 0;
	m_nRight = 640;
	m_nTop = 0;
	m_nBottom = 480;
	m_szResURL = L"";
//	m_nResID = IDR_MAINFRAME;
}

void CXUI_SDIWndFrame::BuildCtrls(void)
{
	if(m_pFrmMaster == NULL)// || m_pFrmMaster->m_UITraitMap.size() == 0)
		return;

	if(m_pFrmMaster->m_MMeunTrait != NULL && 0 < m_pFrmMaster->m_MMeunTrait->GetMenuColumnCount())
		CreateMainMenu(*(m_pFrmMaster->m_MMeunTrait));


	CXOS_ClassObjTable::iterator iter;

	int nCount = (int)(sizeof(XUI_CtrlClass)/sizeof(wchar_t*));

	for(iter = m_pFrmMaster->m_Property.begin(); iter != m_pFrmMaster->m_Property.end(); ++iter)
	{
		CXOS_ClassObject* pObj = iter->second;
		for(int i = 0; i < nCount; i++)
		{
			if(pObj->GetClassStr() == XUI_CtrlClass[i])
			{
				((CXUI_CtrlBase*)pObj)->SetParent(m_hWnd);
				((CXUI_CtrlBase*)pObj)->CreateCtrl();
			}
		}
	}
}


void CXUI_SDIWndFrame::CreateMainMenu(CXUI_MainItem& menuTrait)
{
	MENUITEMINFO mItemInfo;

	CMenu MMenu;
	MMenu.CreateMenu();

	for(int i = 0; i < menuTrait.GetMenuColumnCount(); ++i)
	{
		memset(&mItemInfo, 0, sizeof(mItemInfo));
		CXUI_PopupMenu* pSubMenu = menuTrait.GetMenuColumn(i);
		if(pSubMenu)
		{
			CMenu SubMenu;
			SubMenu.CreateMenu();
			for(int j = 0; j < pSubMenu->GetMenuItemCount(); ++j)
			{
				CXUI_MenuItem* pMItem =	pSubMenu->GetMenuItem(j);
				if(pMItem)
				{
					SubMenu.AppendMenu(MF_STRING, pMItem->m_nCtrlID, CW2CT(pMItem->m_szText.c_str()));
				}
			}

			mItemInfo.fMask = MIIM_STATE|MIIM_TYPE|MIIM_ID|MIIM_SUBMENU;
			mItemInfo.fType = MFT_STRING;
			mItemInfo.fState = MFS_ENABLED;
			mItemInfo.wID = pSubMenu->m_nCtrlID;
			mItemInfo.hSubMenu = SubMenu.m_hMenu;
			mItemInfo.dwTypeData = CW2CT(pSubMenu->m_szMenuText.c_str());
			mItemInfo.cch = _tcsclen(CW2CT(pSubMenu->m_szMenuText.c_str()));
			mItemInfo.cbSize = sizeof(mItemInfo);

			MMenu.InsertMenuItem(i, TRUE, &mItemInfo); 
		}
	}

	SetMenu((HMENU)MMenu);
};

LRESULT CXUI_SDIWndFrame::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;

	if(m_pFrmMaster)
		return m_pFrmMaster->EventHandler((long)WM_TIMER, 0, (long)wParam);
	else
		return 0;
}

#endif
