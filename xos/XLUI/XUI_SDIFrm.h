#ifndef __XUI_SDIFRM_H__
#define __XUI_SDIFRM_H__

//#include "xos_clsobj.h"
#include "xui_ctrlbas.h"
#include "xui_ehandler.h"
#include "xui_msg.h"

class CXUI_Form;

#ifdef __USE_WTL__
#include "resource.h"

class CXUI_SDIWndFrame : public CFrameWindowImpl<CXUI_SDIWndFrame>, public CUpdateUI<CXUI_SDIWndFrame>,
		public CMessageFilter, public CIdleHandler, public CXOS_ClassObject
{
public:
//	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

	CXUI_SDIWndFrame(CXUI_Form* pFrm = NULL);
	CXUI_SDIWndFrame(std::wstring& szName, CXUI_Form* pFrm = NULL);
	CXUI_SDIWndFrame(const wchar_t* szName, CXUI_Form* pFrm = NULL);
	virtual ~CXUI_SDIWndFrame();

	bool IsAlive(void) const {return m_bLive;}

	void SetForm(CXUI_Form* pFrm){m_pFrmMaster = pFrm;}

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXUI_SDIWndFrame");}

	CCommandBarCtrl m_CmdBar;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	virtual bool CreateForm(void);

	BEGIN_UPDATE_UI_MAP(CXUI_SDIWndFrame)
		UPDATE_ELEMENT(ID_VIEW_TOOLBAR, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_STATUS_BAR, UPDUI_MENUPOPUP)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CXUI_SDIWndFrame)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		CHAIN_MSG_MAP(CUpdateUI<CXUI_SDIWndFrame>)
		CHAIN_MSG_MAP(CFrameWindowImpl<CXUI_SDIWndFrame>)

		COMMAND_RANGE_HANDLER(XUI_CTRLID_FIRST, XUI_CTRLID_LAST, OnCmdHandler)
		MESSAGE_RANGE_HANDLER(XUI_M_FIRST, XUI_M_LAST, OnMsgHandler)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
	END_MSG_MAP()


	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnFileNewWindow(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	virtual void OnFinalMessage(HWND hWnd);

	LRESULT OnMsgHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCmdHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);


	void Clean(void);

	virtual void SetCtrlID(long	nCtrlID){m_nCtrlID = nCtrlID;}
	virtual void SetText(std::wstring& szText){m_szText = szText;}
	virtual void SetText(const wchar_t* szText){m_szText = szText;}
	virtual void SetCtrlPos(long nLeft, long nRight, long nTop, long nBottom)
	{m_nLeft = nLeft; m_nRight = nRight; m_nTop = nTop; m_nBottom = nBottom;}
	virtual void SetResID(long nResID){m_nResID = nResID;}
	virtual void SetResURL(std::wstring& szResURL){m_szResURL = szResURL;}
	virtual void SetResURL(const wchar_t* szResURL){m_szResURL = szResURL;}
	virtual void SetStyle(long nStyle){m_nStyle = nStyle;}
	virtual void SetExtStyle(long nExtStyle){m_nExtStyle = nExtStyle;}
	virtual XUI_UITYPE UIType(void) const {return enXUI_FORM;}
	virtual bool SetTraits(const CXUI_FormTrait& ctrlTrait);

	CXUI_SDIWndFrame& operator = (const CXUI_FormTrait& ctrlTrait);	// Assignment

	void DefaultStyle(void);

	void BuildCtrls(void);

private:
/*
	void CreateButton(const CXUI_FormTrait& ctrlTrait);
	void CreateImage(const CXUI_FormTrait& ctrlTrait);
	void CreateEdit(const CXUI_FormTrait& ctrlTrait);
	void CreateText(const CXUI_FormTrait& ctrlTrait);
*/
	void CreateMainMenu(CXUI_MainItem& menuTrait);

public:
	long					m_nCtrlID;
	long					m_nStyle;
	long					m_nExtStyle;
	std::wstring			m_szText;
	long					m_nLeft;
	long					m_nRight;
	long					m_nTop;
	long					m_nBottom;
	std::wstring			m_szResURL;
	long					m_nResID;
	bool					m_bLive;

	bool					m_bCreate;
#ifdef WIN32
	HWND					m_hParent;
#endif

private:

	CXUI_Form*				m_pFrmMaster;

/*
	CXUI_UICtrlTable		m_CtrlTable;

public:
	CXUI_EventHandlerList	m_EventHandlerList;
*/
};
#endif

#endif