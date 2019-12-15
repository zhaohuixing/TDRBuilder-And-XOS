#ifndef __XUI_SHFORM_H__
#define __XUI_SHFORM_H__

#include "xos_clsbase.h"
#include "xui_shfrmctrl.h"
#include "xui_frmtrait.h"


class CXUI_SHForm : public CXOS_ClassObject
{
public:
	CXUI_SHForm(void);
	CXUI_SHForm(std::wstring& szName);
	CXUI_SHForm(const wchar_t* szName);
	virtual ~CXUI_SHForm(void);

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXUI_SHForm");}

public:
	void AttachFrame(void);

	virtual void SetOwnership(void);

	bool AddShellCommand(CXOS_Method*	pFn);

	void RunCommand(void);

private:

public:
	
#ifdef __USE_WTL__
	CXUI_SHFrameCtrl		m_SHFrame;
#endif
};

#endif