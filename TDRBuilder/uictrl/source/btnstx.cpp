#include "stdafx.h"
#include "btnstx.h"
#include "resource.h"

CButtonSTEx::CButtonSTEx(void)
	:CButtonST()
{
	m_bShowArrow = FALSE;
	FreeArrowIcon(FALSE);
}

CButtonSTEx::~CButtonSTEx(void)
{
	FreeArrowIcon();
}

DWORD CButtonSTEx::SetIconEx(int nIconIn, int nIconOut)
{
	FreeArrowIcon();

	HINSTANCE	hInstResource	= NULL;

	// Find correct resource handle
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(IDI_ARROW), RT_GROUP_ICON);

	// Set icon when the mouse is IN the button
	m_icoArrow.hIcon = (HICON)::LoadImage(hInstResource, MAKEINTRESOURCE(IDI_ARROW), IMAGE_ICON, 0, 0, 0);

  	// Set icon when the mouse is OUT the button
	ICONINFO	ii;

	// Get icon dimension
	::ZeroMemory(&ii, sizeof(ICONINFO));
	BOOL bRetValue = ::GetIconInfo(m_icoArrow.hIcon, &ii);
	if (bRetValue == FALSE)
	{
		m_icoArrow.dwWidth	= 16;
		m_icoArrow.dwHeight	= 16;
	} // if
	else
	{
		m_icoArrow.dwWidth	= (DWORD)(ii.xHotspot * 2);
		m_icoArrow.dwHeight	= (DWORD)(ii.yHotspot * 2);
		::DeleteObject(ii.hbmMask);
		::DeleteObject(ii.hbmColor);
	}
	return CButtonSTEx::SetIcon(nIconIn, 0, 0, nIconOut, 0, 0);
}

void CButtonSTEx::FreeArrowIcon(BOOL bCheckForNULL)
{
	if(bCheckForNULL)
	{
		if(m_icoArrow.hIcon)
			::DestroyIcon(m_icoArrow.hIcon);
	}
	::ZeroMemory(&m_icoArrow, sizeof(m_icoArrow));
}

void CButtonSTEx::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	CDC*	pDC = CDC::FromHandle(lpDIS->hDC);

	// Checkbox?
	if (m_bIsCheckBox)
	{
		m_bIsPressed  =  (lpDIS->itemState & ODS_SELECTED) || (m_nCheck != 0);
	} // if
	else	// Normal button OR other button style ...
	{
		m_bIsPressed = (lpDIS->itemState & ODS_SELECTED);

		// If there is a menu and it's displayed, draw the button as pressed
		if (
#ifdef	BTNST_USE_BCMENU
			m_menuPopup.m_hMenu 
#else
			m_hMenu 
#endif
			&& m_bMenuDisplayed)	m_bIsPressed = TRUE;
	} // else

	m_bIsFocused  = (lpDIS->itemState & ODS_FOCUS);
	m_bIsDisabled = (lpDIS->itemState & ODS_DISABLED);

	CRect itemRect = lpDIS->rcItem;

	pDC->SetBkMode(TRANSPARENT);

	// Prepare draw... paint button background

	// Draw transparent?
	if (m_bDrawTransparent)
		PaintBk(pDC);
	else
		OnDrawBackground(pDC, &itemRect);

	// Draw button border
	OnDrawBorder(pDC, &itemRect);

	// Read the button's title
	CString sTitle;
	GetWindowText(sTitle);

	CRect captionRect = lpDIS->rcItem;

	// Draw the icon
	if (m_csIcons[0].hIcon)
	{
		DrawTheIcon(pDC, !sTitle.IsEmpty(), &lpDIS->rcItem, &captionRect, m_bIsPressed, m_bIsDisabled);
	} // if

	if (m_csBitmaps[0].hBitmap)
	{
		pDC->SetBkColor(RGB(255,255,255));
		DrawTheBitmap(pDC, !sTitle.IsEmpty(), &lpDIS->rcItem, &captionRect, m_bIsPressed, m_bIsDisabled);
	} // if

	CRect rtCap(captionRect);
	if(m_bShowArrow && m_icoArrow.hIcon)
	{
		rtCap.right -= m_icoArrow.dwWidth;
	}
	// Write the button title (if any)
	if (sTitle.IsEmpty() == FALSE)
	{
		//DrawTheText(pDC, (LPCTSTR)sTitle, &lpDIS->rcItem, &captionRect, m_bIsPressed, m_bIsDisabled);
		DrawTheText(pDC, (LPCTSTR)sTitle, &lpDIS->rcItem, &rtCap, m_bIsPressed, m_bIsDisabled);
	} // if

	if(m_bShowArrow && m_icoArrow.hIcon)
	{
		DrawTheArrow(pDC, &lpDIS->rcItem, &captionRect, m_bIsPressed, m_bIsDisabled);
	}

	if (m_bIsFlat == FALSE || (m_bIsFlat && m_bDrawFlatFocus))
	{
		// Draw the focus rect
		if (m_bIsFocused)
		{
			CRect focusRect = itemRect;
			focusRect.DeflateRect(3, 3);
			pDC->DrawFocusRect(&focusRect);
		} // if
	} // if
}

void CButtonSTEx::DrawTheArrow(CDC* pDC, RECT* rpItem, CRect* rpCaption, BOOL bIsPressed, BOOL bIsDisabled)
{
	BYTE		byIndex		= 0;

	// Select the icon to use
	CRect	rImage;
	PrepareImageRect(TRUE, rpItem, rpCaption, bIsPressed, m_icoArrow.dwWidth, m_icoArrow.dwHeight, &rImage);

	int nWidth = rpItem->right - rpItem->left;
	rImage.OffsetRect(nWidth-m_icoArrow.dwWidth-2, 0);
	// Ole'!
	pDC->DrawState(	rImage.TopLeft(),
					rImage.Size(), 
					m_icoArrow.hIcon,
					(bIsDisabled ? DSS_DISABLED : DSS_NORMAL), 
					(CBrush*)NULL);
}

