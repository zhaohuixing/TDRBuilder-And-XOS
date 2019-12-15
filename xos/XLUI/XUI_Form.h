#ifndef __XUI_FORM_H__
#define __XUI_FORM_H__

#include "xos_clsbase.h"
#include "xui_sdifrm.h"
#include "xui_frmtrait.h"


class CXUI_Form : public CXOS_ClassObject
{
public:
	CXUI_Form(void);
	CXUI_Form(std::wstring& szName);
	CXUI_Form(const wchar_t* szName);
	virtual ~CXUI_Form(void);

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXUI_Form");}

	void Clean(void);

	void AttachFrame(void);

	bool AddUITrait(const CXUI_FormTrait& uiTrait);

	void AttachMMenu(CXUI_MainItem*	pMMTrait);

	bool AddEventHandler(CXUI_EventHandler*	pEvent);

	long EventHandler(long nMsg, long nActID, long nCtrlID);

	CXUI_CtrlBase* GetFormCtrl(long nCtrlID);

	CXUI_CtrlBase* GetFormCtrl(std::wstring& szCtrlName);

	CXUI_CtrlBase* GetFormCtrl(const wchar_t* szCtrlName);

	bool CheckCtrlExiting(const CXUI_FormTrait& ctrlTrait);

	CXUI_EventHandler* QueryEventHandler(long nEventID, long nActID, long nCtrlID);


public:
	virtual void SetTitle(std::wstring& szText);

	virtual void SetTitle(const wchar_t* szText);

	virtual std::wstring GetTitle(void);

	virtual void Assign(CXOS_ClassObject* pObj);

public:
	virtual void SetOwnership(void);

private:
	void CreateButton(const CXUI_FormTrait& ctrlTrait);
	void CreateImage(const CXUI_FormTrait& ctrlTrait);
	void CreateEdit(const CXUI_FormTrait& ctrlTrait);
	void CreateText(const CXUI_FormTrait& ctrlTrait);
	void CreateTimer(const CXUI_FormTrait& ctrlTrait);

public:
	
//	CXUI_UITraitTable		m_UITraitMap;

	CXUI_MainItem*			m_MMeunTrait;

//	CXUI_UICtrlTable		m_CtrlTable;

//	CXUI_EventHandlerList	m_EventHandlerList;

	long					m_nCurCtrlID;

	long					GetAvailableID(void) const {return m_nCurCtrlID;}

	void					IncrementCurrentID(void){m_nCurCtrlID++;}

#ifdef __USE_WTL__
	CXUI_SDIWndFrame		m_SDIFrame;
#endif
};

#endif