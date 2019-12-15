#ifndef __XUI_BTNCTRL_H__
#define __XUI_BTNCTRL_H__

#ifdef __USE_WTL__
#include <atlctrls.h>
#include <atlgdi.h>
#include <atlcrack.h>
#include <atlmisc.h>
#endif

#ifdef __USE_WTL__
class CXUI_ButtonCtrl : public CWindowImpl<CXUI_ButtonCtrl, CButton, CControlWinTraits>
#else
class CXUI_ButtonCtrl
#endif
{
public:
	CXUI_ButtonCtrl(){};
#ifdef __USE_WTL__
  
	DECLARE_WND_SUPERCLASS(_T("CXUI_ButtonCtrl"), CButton::GetWndClassName())

	typedef CWindowImpl<CXUI_ButtonCtrl, CButton, CControlWinTraits>  thisClass;

	BEGIN_MSG_MAP_EX(thisClass)
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_KILLFOCUS(OnKillFocus)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONUP(OnLButtonUp)
	END_MSG_MAP()


	LRESULT OnBtnClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnMouseMove(UINT fwKeys, CPoint pt);
	LRESULT OnKillFocus(HWND hWnd);
	LRESULT OnLButtonDown(UINT nFlags, CPoint pt);
	LRESULT OnLButtonUp(UINT nFlags, CPoint pt);

#endif
};

#endif