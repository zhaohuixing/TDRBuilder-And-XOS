#ifndef __XUI_SHFRMCTRL_H__
#define __XUI_SHFRMCTRL_H__

#include "xui_ctrlbas.h"

class CXUI_SHForm;

#ifdef __USE_WTL__
#include "resource.h"


#define XUI_SHCMDRUN		WM_USER+1

class CXUI_SHFrameCtrl : public CFrameWindowImpl<CXUI_SHFrameCtrl>, public CUpdateUI<CXUI_SHFrameCtrl>,
		public CMessageFilter, public CIdleHandler, public CXOS_ClassObject
{
public:
//	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

	CXUI_SHFrameCtrl(CXUI_SHForm* pFrm = NULL);
	CXUI_SHFrameCtrl(std::wstring& szName, CXUI_SHForm* pFrm = NULL);
	CXUI_SHFrameCtrl(const wchar_t* szName, CXUI_SHForm* pFrm = NULL);
	virtual ~CXUI_SHFrameCtrl();

	bool IsAlive(void) const {return m_bLive;}

	void SetForm(CXUI_SHForm* pFrm){m_pFrmMaster = pFrm;}

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXUI_SHFrameCtrl");}

	CCommandBarCtrl m_CmdBar;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	virtual bool CreateForm(void);

	BEGIN_UPDATE_UI_MAP(CXUI_SHFrameCtrl)
		UPDATE_ELEMENT(ID_VIEW_TOOLBAR, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_STATUS_BAR, UPDUI_MENUPOPUP)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CXUI_SHFrameCtrl)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(XUI_SHCMDRUN, OnRunSHCmd)
		CHAIN_MSG_MAP(CUpdateUI<CXUI_SHFrameCtrl>)
		CHAIN_MSG_MAP(CFrameWindowImpl<CXUI_SHFrameCtrl>)
	END_MSG_MAP()


	virtual void OnFinalMessage(HWND hWnd);

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnRunSHCmd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	bool					m_bLive;

	bool					m_bCreate;
#ifdef WIN32
	HWND					m_hParent;
#endif

private:

	CXUI_SHForm*				m_pFrmMaster;

};
#endif

#endif