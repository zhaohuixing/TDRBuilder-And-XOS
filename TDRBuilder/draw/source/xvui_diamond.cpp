#include "stdafx.h"
#include "xvui_diamond.h"
#include "xvui_uiutils.h"

CVUI_Diamond::CVUI_Diamond(long	nID, CVUI_GraphManager*	pManager)
	:CVUI_GraphBase(nID, pManager)
{
	m_selBrush.lbColor = XVUI_BLOCK_ACTIVERGB;
}

CVUI_Diamond::~CVUI_Diamond()
{
}

void CVUI_Diamond::DrawNormal(CDC* pDC)
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

	CPoint pPts[4];
	pPts[0].x = m_ptCenter.x;
	pPts[0].y = m_ptCenter.y-m_Radius.cy;
	pPts[1].x = m_ptCenter.x+m_Radius.cx;
	pPts[1].y = m_ptCenter.y;
	pPts[2].x = m_ptCenter.x;
	pPts[2].y = m_ptCenter.y+m_Radius.cy;
	pPts[3].x = m_ptCenter.x-m_Radius.cx;
	pPts[3].y = m_ptCenter.y;

    // Draw the polygon in DC
	pDC->Polygon(pPts, 4);

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

void CVUI_Diamond::DrawShadow(CDC* pDC)
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

	CPoint pPts[4];
	pPts[0].x = m_ptCenter.x+XVUI_ENODE_SHADOWX;
	pPts[0].y = m_ptCenter.y-m_Radius.cy+XVUI_ENODE_SHADOWY;
	pPts[1].x = m_ptCenter.x+m_Radius.cx+XVUI_ENODE_SHADOWX;
	pPts[1].y = m_ptCenter.y+XVUI_ENODE_SHADOWY;
	pPts[2].x = m_ptCenter.x+XVUI_ENODE_SHADOWX;
	pPts[2].y = m_ptCenter.y+m_Radius.cy+XVUI_ENODE_SHADOWY;
	pPts[3].x = m_ptCenter.x-m_Radius.cx+XVUI_ENODE_SHADOWX;
	pPts[3].y = m_ptCenter.y+XVUI_ENODE_SHADOWY;

    // Draw the polygon in DC
	pDC->Polygon(pPts, 4);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pBrush);
	pDC->SetROP2(nOldMode);
}

void CVUI_Diamond::DrawSelected(CDC* pDC)
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

	CPoint pPts[4];
	pPts[0].x = m_ptCenter.x;
	pPts[0].y = m_ptCenter.y-m_Radius.cy;
	pPts[1].x = m_ptCenter.x+m_Radius.cx;
	pPts[1].y = m_ptCenter.y;
	pPts[2].x = m_ptCenter.x;
	pPts[2].y = m_ptCenter.y+m_Radius.cy;
	pPts[3].x = m_ptCenter.x-m_Radius.cx;
	pPts[3].y = m_ptCenter.y;

    // Draw the polygon in DC
	pDC->Polygon(pPts, 4);

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

void CVUI_Diamond::DrawDebug(CDC* pDC)
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

	CPoint pPts[4];
	pPts[0].x = m_ptCenter.x;
	pPts[0].y = m_ptCenter.y-m_Radius.cy;
	pPts[1].x = m_ptCenter.x+m_Radius.cx;
	pPts[1].y = m_ptCenter.y;
	pPts[2].x = m_ptCenter.x;
	pPts[2].y = m_ptCenter.y+m_Radius.cy;
	pPts[3].x = m_ptCenter.x-m_Radius.cx;
	pPts[3].y = m_ptCenter.y;

    // Draw the polygon in DC
	pDC->Polygon(pPts, 4);

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

bool CVUI_Diamond::HitBlock(CPoint pt)
{
	bool bRet = false;

	if(pt == m_ptCenter || (pt.y == m_ptCenter.y && m_ptCenter.x-m_Radius.cx <= pt.x && pt.x <= m_ptCenter.x+m_Radius.cx))
	{
		bRet = true;
		return bRet;
	}


	CPoint pPts[4];
	pPts[0].x = m_ptCenter.x;
	pPts[0].y = m_ptCenter.y-m_Radius.cy;
	pPts[1].x = m_ptCenter.x+m_Radius.cx;
	pPts[1].y = m_ptCenter.y;
	pPts[2].x = m_ptCenter.x;
	pPts[2].y = m_ptCenter.y+m_Radius.cy;
	pPts[3].x = m_ptCenter.x-m_Radius.cx;
	pPts[3].y = m_ptCenter.y;

	CVUI_HitUtility hittest;

	if(hittest.PtInPloy(pPts, 4, pt))
	{
		bRet = true;
	}
	else
	{
		bRet = false;
	}

	return bRet;
}


/////////////////////////////////////////////////////////////////////////////
