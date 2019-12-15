#include "stdafx.h"
#include "xvui_rrect.h"

#define XVUI_RRCORNER		1.2

CVUI_RoundRect::CVUI_RoundRect(long	nID, CVUI_GraphManager*	pManager)
	:CVUI_GraphBase(nID, pManager)
{
	m_selBrush.lbColor = XVUI_CLASS_FILLRGB;
}

CVUI_RoundRect::~CVUI_RoundRect()
{
}

void CVUI_RoundRect::DrawNormal(CDC* pDC)
{
	ASSERT(this);

	CBrush brush;
	if (!brush.CreateBrushIndirect(&m_logBrush))
		return;
	
	CPen pen;
	if (!pen.CreatePen(PS_SOLID, 1, m_clrPen))
		return;

	CBrush* pOldBrush;
	CPen* pOldPen;

	pOldBrush = pDC->SelectObject(&brush);
	pOldPen = pDC->SelectObject(&pen);

	int nx = min(abs(m_Radius.cx), abs(m_Radius.cy));

	CPoint pt((int)((double)nx/XVUI_RRCORNER), (int)((double)nx/XVUI_RRCORNER));
	CRect rect(m_ptCenter.x-m_Radius.cx, m_ptCenter.y-m_Radius.cy, m_ptCenter.x+m_Radius.cx, m_ptCenter.y+m_Radius.cy);
	pDC->RoundRect(&rect, pt);

	LOGFONT lfont;
	m_TextFont.GetLogFont(&lfont);

	//Create the font mapping the zoom change
	lfont.lfHeight = MulDiv(lfont.lfHeight, pDC->GetDeviceCaps(LOGPIXELSY), 72);

    CFont newFont;
	newFont.CreateFontIndirect(&lfont);
	CFont* pFont = (CFont*) pDC->SelectObject(&newFont);

	CRect txtRect(0, 0, 10, 10);

	int nTxtY = pDC->DrawText(m_strName, m_strName.GetLength(), &txtRect, DT_CALCRECT | DT_SINGLELINE | DT_CENTER | DT_NOPREFIX);
	int nOldMode = pDC->SetBkMode(TRANSPARENT);
	CPoint tcpt = txtRect.CenterPoint();
	txtRect.OffsetRect(m_ptCenter.x - tcpt.x, m_ptCenter.y - tcpt.y);
	pDC->DrawText(m_strName, m_strName.GetLength(), &txtRect, DT_SINGLELINE | DT_CENTER | DT_NOPREFIX);
	m_txtRect = txtRect;
	pDC->SetBkMode(nOldMode);

	pDC->SelectObject(pFont);
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}

void CVUI_RoundRect::DrawShadow(CDC* pDC)
{
	ASSERT(this);
	ASSERT(pDC);

	CBrush brush;
	if(!brush.CreateSolidBrush(XVUI_SHADOW_COLOR))
		return;
	brush.UnrealizeObject();
	CBrush* pBrush;
	pBrush = pDC->SelectObject(&brush);

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, XVUI_SHADOW_COLOR);
	CPen* pOldPen;
	pOldPen = pDC->SelectObject(&pen);

	int nOldMode = pDC->SetROP2(R2_MASKPEN);

	int nx = min(abs(m_Radius.cx), abs(m_Radius.cy));

	CPoint pt((int)((double)nx/XVUI_RRCORNER), (int)((double)nx/XVUI_RRCORNER));
	CRect rect(m_ptCenter.x-m_Radius.cx, m_ptCenter.y-m_Radius.cy, m_ptCenter.x+m_Radius.cx, m_ptCenter.y+m_Radius.cy);
	rect.OffsetRect(XVUI_ENODE_SHADOWX, XVUI_ENODE_SHADOWY);
	pDC->RoundRect(&rect, pt);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pBrush);
	pDC->SetROP2(nOldMode);
}

void CVUI_RoundRect::DrawSelected(CDC* pDC)
{
	ASSERT(this);

	CBrush brush;
	if (!brush.CreateBrushIndirect(&m_selBrush))
		return;
	
	CPen pen;
	if (!pen.CreatePen(PS_SOLID, 1, m_clrPen))
		return;

	CBrush* pOldBrush;
	CPen* pOldPen;

	pOldBrush = pDC->SelectObject(&brush);
	pOldPen = pDC->SelectObject(&pen);

	int nx = min(abs(m_Radius.cx), abs(m_Radius.cy));

	CPoint pt((int)((double)nx/XVUI_RRCORNER), (int)((double)nx/XVUI_RRCORNER));
	CRect rect(m_ptCenter.x-m_Radius.cx, m_ptCenter.y-m_Radius.cy, m_ptCenter.x+m_Radius.cx, m_ptCenter.y+m_Radius.cy);
	pDC->RoundRect(&rect, pt);

	LOGFONT lfont;
	m_TextFont.GetLogFont(&lfont);

	//Create the font mapping the zoom change
	lfont.lfHeight = MulDiv(lfont.lfHeight, pDC->GetDeviceCaps(LOGPIXELSY), 72);

    CFont newFont;
	newFont.CreateFontIndirect(&lfont);
	CFont* pFont = (CFont*) pDC->SelectObject(&newFont);

	CRect txtRect(0, 0, 10, 10);

	int nTxtY = pDC->DrawText(m_strName, m_strName.GetLength(), &txtRect, DT_CALCRECT | DT_SINGLELINE | DT_CENTER | DT_NOPREFIX);
	int nOldMode = pDC->SetBkMode(TRANSPARENT);
	CPoint tcpt = txtRect.CenterPoint();
	txtRect.OffsetRect(m_ptCenter.x - tcpt.x, m_ptCenter.y - tcpt.y);
	pDC->DrawText(m_strName, m_strName.GetLength(), &txtRect, DT_SINGLELINE | DT_CENTER | DT_NOPREFIX);
	m_txtRect = txtRect;
	pDC->SetBkMode(nOldMode);

	pDC->SelectObject(pFont);
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}

void CVUI_RoundRect::DrawDebug(CDC* pDC)
{
	ASSERT(this);

	CBrush brush;
	if (!brush.CreateBrushIndirect(&m_debugBrush))
		return;
	
	CPen pen;
	if (!pen.CreatePen(PS_SOLID, 1, m_clrPen))
		return;

	CBrush* pOldBrush;
	CPen* pOldPen;

	pOldBrush = pDC->SelectObject(&brush);
	pOldPen = pDC->SelectObject(&pen);

	int nx = min(abs(m_Radius.cx), abs(m_Radius.cy));

	CPoint pt((int)((double)nx/XVUI_RRCORNER), (int)((double)nx/XVUI_RRCORNER));
	CRect rect(m_ptCenter.x-m_Radius.cx, m_ptCenter.y-m_Radius.cy, m_ptCenter.x+m_Radius.cx, m_ptCenter.y+m_Radius.cy);
	pDC->RoundRect(&rect, pt);

	LOGFONT lfont;
	m_TextFont.GetLogFont(&lfont);

	//Create the font mapping the zoom change
	lfont.lfHeight = MulDiv(lfont.lfHeight, pDC->GetDeviceCaps(LOGPIXELSY), 72);

    CFont newFont;
	newFont.CreateFontIndirect(&lfont);
	CFont* pFont = (CFont*) pDC->SelectObject(&newFont);

	CRect txtRect(0, 0, 10, 10);

	int nTxtY = pDC->DrawText(m_strName, m_strName.GetLength(), &txtRect, DT_CALCRECT | DT_SINGLELINE | DT_CENTER | DT_NOPREFIX);
	int nOldMode = pDC->SetBkMode(TRANSPARENT);
	CPoint tcpt = txtRect.CenterPoint();
	txtRect.OffsetRect(m_ptCenter.x - tcpt.x, m_ptCenter.y - tcpt.y);
	pDC->DrawText(m_strName, m_strName.GetLength(), &txtRect, DT_SINGLELINE | DT_CENTER | DT_NOPREFIX);
	m_txtRect = txtRect;
	pDC->SetBkMode(nOldMode);

	pDC->SelectObject(pFont);
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}

/////////////////////////////////////////////////////////////////////////////
