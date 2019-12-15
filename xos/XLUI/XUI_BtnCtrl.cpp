#ifdef WIN32
#include "stdafx.h"
#endif

#include "xui_btnctrl.h"
#include "xui_msg.h"

#ifdef __USE_WTL__

LRESULT CXUI_ButtonCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	CWindow pWnd;		// Active window
	CWindow pParent;	// Window that owns the button

	DefWindowProc();
	
	// If the mouse enter the button with the left button pressed then do nothing
	if((nFlags & MK_LBUTTON) != 0) 
	{ 
		return 0; 
	}

	CPoint p2 = point;
	ClientToScreen(&p2);
	CWindow wndUnderMouse = ::WindowFromPoint(p2);
	pParent = GetParent();

	if((::GetCapture() != m_hWnd) && pParent.IsWindow() && wndUnderMouse && (wndUnderMouse.m_hWnd == m_hWnd)) 
	{
		SetCapture();
		Invalidate();
	}
	else
	{
		if(wndUnderMouse && (wndUnderMouse.m_hWnd != m_hWnd))
		{
			if(!(nFlags & MK_LBUTTON))
			{
				ReleaseCapture();
			}
		}
	}
	
	return 0;
}

LRESULT CXUI_ButtonCtrl::OnKillFocus(HWND hWnd)
{
	DefWindowProc();

	if(::GetCapture() == m_hWnd)
		ReleaseCapture();

	Invalidate();
	return 0;
}

LRESULT CXUI_ButtonCtrl::OnLButtonDown(UINT nFlags, CPoint pt)
{
	DefWindowProc();

	CPoint p2 = pt;
	ClientToScreen(&p2);
	CWindow wndUnderMouse = ::WindowFromPoint(p2);
	if(wndUnderMouse && (wndUnderMouse.m_hWnd == m_hWnd))
	{
		SetCapture();
		Invalidate();
	}

	return 0;
}

LRESULT CXUI_ButtonCtrl::OnLButtonUp(UINT nFlags, CPoint pt)
{
	DefWindowProc();
	
	CPoint p2 = pt;
	ClientToScreen(&p2);
	CWindow wndUnderMouse = ::WindowFromPoint(p2);

	if(::GetCapture() == m_hWnd)
	{
		ReleaseCapture();
	}

	Invalidate();

	if(wndUnderMouse && (wndUnderMouse.m_hWnd == m_hWnd))
	{
		UINT nMsg = XUI_M_CLICK;
		UINT nCtrlID = GetDlgCtrlID();
		HWND hParent = GetParent();

		::SendMessage(hParent, nMsg, nMsg, nCtrlID); 
	}
	else
	{
		::SetFocus(NULL);
	}

	return 0;
}

#endif