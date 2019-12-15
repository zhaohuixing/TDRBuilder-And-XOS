#ifndef __XUI_BTN_H__
#define __XUI_BTN_H__

#include "xui_ctrlbas.h"
#include "xui_frmtrait.h"
#include "xui_btnctrl.h"

class CXUI_Button :	public CXUI_CtrlBase
{
public:
	CXUI_Button(void);
	CXUI_Button(std::wstring& szName); // Constructor
	CXUI_Button(const wchar_t* szName); // Constructor
	virtual ~CXUI_Button(void);

public:
	virtual bool CreateCtrl(void);

	virtual void SetText(std::wstring& szText);

	virtual void SetText(const wchar_t* szText);

	virtual std::wstring GetText(void);

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXUI_Button");}

	virtual XUI_UITYPE UIType(void) const {return enXUI_BUTTON;}

	virtual void Assign(CXOS_ClassObject* pObj);

public:
	CXUI_Button& operator = (const CXUI_FormTrait& ctrlTrait);	// Assignment

public:

//#ifdef __USE_WTL__
	CXUI_ButtonCtrl			m_Button;
//#endif
};

#endif