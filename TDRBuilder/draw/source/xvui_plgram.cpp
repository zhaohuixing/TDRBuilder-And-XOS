#include "stdafx.h"
#include "xvui_plgram.h"
#include "xvui_uiutils.h"

CVUI_Parallelogram::CVUI_Parallelogram(long	nID, CVUI_GraphManager*	pManager)
	:CVUI_GraphBase(nID, pManager)
{
	m_selBrush.lbColor = XVUI_INTI_ACTIVERGB;
	m_nRaito = XVUI_PLGRAM_RATION;
	m_nOffset = (int)(((double)m_Radius.cy)*m_nRaito);
}

CVUI_Parallelogram::~CVUI_Parallelogram()
{
}

CRect CVUI_Parallelogram::GetBoundaryExt(void)
{
	int nSzie = xvui_ztsize[XVUI_ZOOM_DEFAULT];
	if(0 <= m_nZoom && m_nZoom < XVUI_ZOOMS)
		nSzie = xvui_ztsize[m_nZoom];

	int nSX = 0;
	int nSY = 0;
	
	nSzie += 1;

	if(m_bShadow == true)
	{
		nSX = XVUI_ENODE_SHADOWX;
		nSY = XVUI_ENODE_SHADOWY;
	}

	int nW = max(m_txtRect.Width()/2+1, m_Radius.cx+m_nOffset);
	int nH = max(m_txtRect.Height()/2+1, m_Radius.cy);

	nW += nSzie*2;
	nH += nSzie*2;

	CRect rect(m_ptCenter.x-nW, m_ptCenter.y-nH, 
		       m_ptCenter.x+nW+nSX, m_ptCenter.y+nH+nSY);

	return rect;
}

void CVUI_Parallelogram::DrawNormal(CDC* pDC)
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
	pPts[0].x = m_ptCenter.x-m_Radius.cx+m_nOffset;
	pPts[0].y = m_ptCenter.y-m_Radius.cy;
	pPts[1].x = m_ptCenter.x+m_Radius.cx+m_nOffset;
	pPts[1].y = m_ptCenter.y-m_Radius.cy;
	pPts[2].x = m_ptCenter.x+m_Radius.cx-m_nOffset;
	pPts[2].y = m_ptCenter.y+m_Radius.cy;
	pPts[3].x = m_ptCenter.x-m_Radius.cx-m_nOffset;
	pPts[3].y = m_ptCenter.y+m_Radius.cy;

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

void CVUI_Parallelogram::DrawShadow(CDC* pDC)
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
	pPts[0].x = m_ptCenter.x-m_Radius.cx+m_nOffset+XVUI_ENODE_SHADOWX;
	pPts[0].y = m_ptCenter.y-m_Radius.cy+XVUI_ENODE_SHADOWY;
	pPts[1].x = m_ptCenter.x+m_Radius.cx+m_nOffset+XVUI_ENODE_SHADOWX;
	pPts[1].y = m_ptCenter.y-m_Radius.cy+XVUI_ENODE_SHADOWY;
	pPts[2].x = m_ptCenter.x+m_Radius.cx-m_nOffset+XVUI_ENODE_SHADOWX;
	pPts[2].y = m_ptCenter.y+m_Radius.cy+XVUI_ENODE_SHADOWY;
	pPts[3].x = m_ptCenter.x-m_Radius.cx-m_nOffset+XVUI_ENODE_SHADOWX;
	pPts[3].y = m_ptCenter.y+m_Radius.cy+XVUI_ENODE_SHADOWY;

    // Draw the polygon in DC
	pDC->Polygon(pPts, 4);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pBrush);
	pDC->SetROP2(nOldMode);
}

void CVUI_Parallelogram::DrawSelected(CDC* pDC)
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
	pPts[0].x = m_ptCenter.x-m_Radius.cx+m_nOffset;
	pPts[0].y = m_ptCenter.y-m_Radius.cy;
	pPts[1].x = m_ptCenter.x+m_Radius.cx+m_nOffset;
	pPts[1].y = m_ptCenter.y-m_Radius.cy;
	pPts[2].x = m_ptCenter.x+m_Radius.cx-m_nOffset;
	pPts[2].y = m_ptCenter.y+m_Radius.cy;
	pPts[3].x = m_ptCenter.x-m_Radius.cx-m_nOffset;
	pPts[3].y = m_ptCenter.y+m_Radius.cy;

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

void CVUI_Parallelogram::DrawDebug(CDC* pDC)
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
	pPts[0].x = m_ptCenter.x-m_Radius.cx+m_nOffset;
	pPts[0].y = m_ptCenter.y-m_Radius.cy;
	pPts[1].x = m_ptCenter.x+m_Radius.cx+m_nOffset;
	pPts[1].y = m_ptCenter.y-m_Radius.cy;
	pPts[2].x = m_ptCenter.x+m_Radius.cx-m_nOffset;
	pPts[2].y = m_ptCenter.y+m_Radius.cy;
	pPts[3].x = m_ptCenter.x-m_Radius.cx-m_nOffset;
	pPts[3].y = m_ptCenter.y+m_Radius.cy;

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


bool CVUI_Parallelogram::HitBlock(CPoint pt)
{
	bool bRet = false;

	if(pt == m_ptCenter)
	{
		bRet = true;
		return bRet;
	}

	CPoint pPts[4];
	pPts[0].x = m_ptCenter.x-m_Radius.cx+m_nOffset;
	pPts[0].y = m_ptCenter.y-m_Radius.cy;
	pPts[1].x = m_ptCenter.x+m_Radius.cx+m_nOffset;
	pPts[1].y = m_ptCenter.y-m_Radius.cy;
	pPts[2].x = m_ptCenter.x+m_Radius.cx-m_nOffset;
	pPts[2].y = m_ptCenter.y+m_Radius.cy;
	pPts[3].x = m_ptCenter.x-m_Radius.cx-m_nOffset;
	pPts[3].y = m_ptCenter.y+m_Radius.cy;

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

void CVUI_Parallelogram::ChangeShape(CPoint ptOff)
{
	CVUI_GraphBase::ChangeShape(ptOff);
	m_nOffset = (int)(((double)m_Radius.cy)*m_nRaito);
	if(XVUI_PLGRAM_OFF < m_nOffset)
		m_nOffset = XVUI_PLGRAM_OFF;

	if((int)(((double)m_Radius.cx)*0.5) < m_nOffset)
		m_nOffset = (int)(((double)m_Radius.cx)*0.5);
}

/////////////////////////////////////////////////////////////////////////////
