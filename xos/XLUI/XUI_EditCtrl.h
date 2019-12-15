#ifndef __XUI_EDITCTRL_H__
#define __XUI_EDITCTRL_H__

#include <string>

#ifdef __USE_WTL__

#include <atlctrls.h>
#include <atlgdi.h>
#include <atlcrack.h>
#include <atlmisc.h>
#endif

#ifdef __USE_WTL__
class CXUI_EditCtrl : public CWindowImpl<CXUI_EditCtrl, CEdit, CControlWinTraits> 
#else
class CXUI_EditCtrl
#endif
{
public:
	CXUI_EditCtrl();

#ifdef __USE_WTL__

	DECLARE_WND_SUPERCLASS(_T("CXUI_EditCtrl"), CEdit::GetWndClassName())

	typedef CWindowImpl<CXUI_EditCtrl, CEdit, CControlWinTraits> thisClass;
	BEGIN_MSG_MAP_EX(thisClass)
    END_MSG_MAP()

private:
#endif
};

#endif