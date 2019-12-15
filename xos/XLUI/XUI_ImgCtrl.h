#ifndef __XUI_IMGCTRL_H__
#define __XUI_IMGCTRL_H__

#include <string>

#ifdef __USE_WTL__

#include <atlctrls.h>
#include <atlgdi.h>
#include <atlcrack.h>
#include <atlmisc.h>
#include <atlimage.h>
#endif

#ifdef __USE_WTL__
//class CXUI_ImageCtrl : public CWindowImpl<CXUI_ImageCtrl, CWindow>, public COwnerDraw<CXUI_ImageCtrl>
class CXUI_ImageCtrl : public CWindowImpl<CXUI_ImageCtrl, CStatic, CControlWinTraits>, 
					   public COwnerDraw<CXUI_ImageCtrl>
#else
class CXUI_ImageCtrl
#endif
{
public:
	CXUI_ImageCtrl();
	~CXUI_ImageCtrl();

	void CleanImage(void)
	{
#ifdef __USE_WTL__
		if(m_Picture){(m_Picture)->Release();(m_Picture) = NULL;}
#endif
	}

	void SetStretch(bool bTrue){m_bStretch = bTrue;}

	bool LoadImage(std::wstring szImage);
	bool LoadImage(const wchar_t* szImage);


#ifdef __USE_WTL__

	DECLARE_WND_SUPERCLASS(_T("CXUI_ImageCtrl"), CStatic::GetWndClassName())

    BEGIN_MSG_MAP(CXUI_ImageCtrl)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		CHAIN_MSG_MAP_ALT(COwnerDraw<CXUI_ImageCtrl>, 1)
        DEFAULT_REFLECTION_HANDLER()
    END_MSG_MAP()

/*
	typedef CWindowImpl<CXUI_ImageCtrl, CStatic, CControlWinTraits>  thisClass;

	BEGIN_MSG_MAP_EX(thisClass)
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_KILLFOCUS(OnKillFocus)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONUP(OnLButtonUp)
	END_MSG_MAP()
*/
    void DrawItem(LPDRAWITEMSTRUCT lpdis);

	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);


/*
	HWND Create(HWND hWndParent, ATL::_U_RECT rect = NULL, LPCTSTR szWindowName = NULL,
			DWORD dwStyle = 0, DWORD dwExStyle = 0,
			ATL::_U_MENUorID MenuOrID = 0U, LPVOID lpCreateParam = NULL)
	{
		//return CWindow::Create(GetWndClassName(), hWndParent, rect.m_lpRect, szWindowName, dwStyle, dwExStyle, MenuOrID.m_hMenu, lpCreateParam);
		return CWindow::Create(_T("IMAGE"), hWndParent, rect.m_lpRect, szWindowName, dwStyle, dwExStyle, MenuOrID.m_hMenu, lpCreateParam);
	}
*/

private:
	COLORREF GetCtrlBkClr(void);

	BOOL DrawImage(CDC* pDC, CPoint  ptCenter, CRect rectImage);

private:
	LPPICTURE	  m_Picture;
#endif

	bool          m_bStretch;
};

#endif