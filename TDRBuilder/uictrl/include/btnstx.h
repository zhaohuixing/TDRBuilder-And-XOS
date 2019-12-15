#ifndef __BUTTONSTEX_H__
#define __BUTTONSTEX_H__

#pragma once
#include "btnst.h"

class CButtonSTEx : public CButtonST
{
public:
	CButtonSTEx(void);
	virtual ~CButtonSTEx(void);

public:
	void ShowArrow(BOOL bShow){m_bShowArrow = bShow;}
	DWORD SetIconEx(int nIconIn, int nIconOut = NULL);

    //{{AFX_VIRTUAL(CButtonSTEx)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

private:
	BOOL			m_bShowArrow;
	STRUCT_ICONS	m_icoArrow;

	void FreeArrowIcon(BOOL bCheckForNULL = TRUE);
	void DrawTheArrow(CDC* pDC, RECT* rpItem, CRect* rpCaption, BOOL bIsPressed, BOOL bIsDisabled);
};

#endif