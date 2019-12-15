#ifndef __XUI_TEXT_H__
#define __XUI_TEXT_H__

#include "xui_ctrlbas.h"
#include "xui_frmtrait.h"
#include "xui_textctrl.h"

class CXUI_Text :	public CXUI_CtrlBase
{
public:
	CXUI_Text(void);
	CXUI_Text(std::wstring& szName); // Constructor
	CXUI_Text(const wchar_t* szName); // Constructor
	virtual ~CXUI_Text(void);

public:
	virtual bool CreateCtrl(void);

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXUI_Text");}

	virtual XUI_UITYPE UIType(void) const {return enXUI_TEXT;}

	virtual void SetText(std::wstring& szText);

	virtual void SetText(const wchar_t* szText);

	virtual std::wstring GetText(void);

	virtual void Assign(CXOS_ClassObject* pObj);

public:
	CXUI_Text& operator = (const CXUI_FormTrait& ctrlTrait);	// Assignment

public:
	CXUI_TextCtrl			m_Text;
};

#endif