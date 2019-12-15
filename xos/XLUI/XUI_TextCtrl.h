#ifndef __XUI_TEXTCTRL_H__
#define __XUI_TEXTCTRL_H__

#include <string>

#ifdef __USE_WTL__

#include <atlctrls.h>
#include <atlgdi.h>
#include <atlcrack.h>
#include <atlmisc.h>
#endif

#ifdef __USE_WTL__
class CXUI_TextCtrl : public CWindowImpl<CXUI_TextCtrl, CStatic, CControlWinTraits> 
#else
class CXUI_TextCtrl
#endif
{
public:
	CXUI_TextCtrl();

#ifdef __USE_WTL__

	DECLARE_WND_SUPERCLASS(_T("CXUI_TextCtrl"), CEdit::GetWndClassName())

	typedef CWindowImpl<CXUI_TextCtrl, CStatic, CControlWinTraits> thisClass;
	BEGIN_MSG_MAP_EX(thisClass)
    END_MSG_MAP()

#endif
private:
	std::wstring	m_szText;
};

#endif