#ifndef __XUI_TIMER_H__
#define __XUI_TIMER_H__

#include "xui_ctrlbas.h"
#include "xui_frmtrait.h"

class CXUI_Timer :	public CXUI_CtrlBase
{
public:
	CXUI_Timer(void);
	CXUI_Timer(std::wstring& szName); // Constructor
	CXUI_Timer(const wchar_t* szName); // Constructor
	virtual ~CXUI_Timer(void);

public:
	virtual bool CreateCtrl(void);

	virtual void DestroyCtrl(void);

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXUI_Timer");}

	virtual XUI_UITYPE UIType(void) const {return enXUI_TIMER;}

	virtual void Assign(CXOS_ClassObject* pObj);

public:
	CXUI_Timer& operator = (const CXUI_FormTrait& ctrlTrait);	// Assignment
};

#endif