#ifndef __XUI_EDIT_H__
#define __XUI_EDIT_H__

#include "xui_ctrlbas.h"
#include "xui_frmtrait.h"
#include "xui_editctrl.h"

class CXUI_Edit :	public CXUI_CtrlBase
{
public:
	CXUI_Edit(void);
	CXUI_Edit(std::wstring& szName); // Constructor
	CXUI_Edit(const wchar_t* szName); // Constructor
	virtual ~CXUI_Edit(void);

public:
	virtual bool CreateCtrl(void);

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXUI_Edit");}

	virtual XUI_UITYPE UIType(void) const {return enXUI_EDIT;}

	virtual void SetText(std::wstring& szText);

	virtual void SetText(const wchar_t* szText);

	virtual std::wstring GetText(void);

	virtual void Assign(CXOS_ClassObject* pObj);

public:
	CXUI_Edit& operator = (const CXUI_FormTrait& ctrlTrait);	// Assignment

public:

	CXUI_EditCtrl			m_Edit;
};

#endif