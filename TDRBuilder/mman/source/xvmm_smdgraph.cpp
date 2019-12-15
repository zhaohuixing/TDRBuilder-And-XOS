#include "stdafx.h"

#include "xvmm_smdgraph.h"
#include "xvsb_macro.h"
#include "xvui_uidefs.h"

CVMM_SMDGraph::CVMM_SMDGraph(long	nID, CVUI_GraphManager*	pManager) 
	: CVUI_GraphBase(nID, pManager)
{
	m_strName = XVSM_PUSTR_CPU;
	m_puType = enXVSB_PUCOMPLEX;
}

CVMM_SMDGraph::~CVMM_SMDGraph()
{
}

/////////////////////////////////////////////////////////////////////////////
void CVMM_SMDGraph::DrawNormal(CDC* pDC)
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

	CRect rect(m_ptCenter.x-m_Radius.cx, m_ptCenter.y-m_Radius.cy, m_ptCenter.x+m_Radius.cx, m_ptCenter.y+m_Radius.cy);
	pDC->Rectangle(&rect);

	DrawCorner(pDC);

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

void CVMM_SMDGraph::DrawSelected(CDC* pDC)
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

	CRect rect(m_ptCenter.x-m_Radius.cx, m_ptCenter.y-m_Radius.cy, m_ptCenter.x+m_Radius.cx, m_ptCenter.y+m_Radius.cy);
	pDC->Rectangle(&rect);

	DrawCorner(pDC);

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

void CVMM_SMDGraph::DrawDebug(CDC* pDC)
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

	CRect rect(m_ptCenter.x-m_Radius.cx, m_ptCenter.y-m_Radius.cy, m_ptCenter.x+m_Radius.cx, m_ptCenter.y+m_Radius.cy);
	pDC->Rectangle(&rect);

	DrawCorner(pDC);

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

void CVMM_SMDGraph::DrawCorner(CDC* pDC)
{
	CBrush brush(XVUI_BLOCK_CORNERRGB);
	CBrush* pOldBrush;

	pOldBrush = pDC->SelectObject(&brush);


	int x = min(m_Radius.cx, m_Radius.cy); 
	x = x/3;

	CPoint pts[3];
	pts[0].x = m_ptCenter.x-m_Radius.cx+1;
	pts[0].y = m_ptCenter.y-m_Radius.cy+1;
	pts[1].x = pts[0].x + x;
	pts[1].y = pts[0].y;
	pts[2].x = pts[0].x;
	pts[2].y = pts[0].y + x;
	pDC->Polygon(pts, 3);

	pts[0].x = m_ptCenter.x+m_Radius.cx-1;
	pts[0].y = m_ptCenter.y-m_Radius.cy+1;
	pts[1].x = pts[0].x - x;
	pts[1].y = pts[0].y;
	pts[2].x = pts[0].x;
	pts[2].y = pts[0].y + x;
	pDC->Polygon(pts, 3);
	
	pts[0].x = m_ptCenter.x+m_Radius.cx-1;
	pts[0].y = m_ptCenter.y+m_Radius.cy-1;
	pts[1].x = pts[0].x - x;
	pts[1].y = pts[0].y;
	pts[2].x = pts[0].x;
	pts[2].y = pts[0].y - x;
	pDC->Polygon(pts, 3);

	pts[0].x = m_ptCenter.x-m_Radius.cx+1;
	pts[0].y = m_ptCenter.y+m_Radius.cy-1;
	pts[1].x = pts[0].x + x;
	pts[1].y = pts[0].y;
	pts[2].x = pts[0].x;
	pts[2].y = pts[0].y - x;
	pDC->Polygon(pts, 3);

	pDC->SelectObject(pOldBrush);
}

bool CVMM_SMDGraph::GetHeadLinkAccess(int nLink)
{
	bool bRet = false;
	if(nLink == 0 || nLink == 1 || nLink == 2)
		bRet = true;

	return bRet;
}

bool CVMM_SMDGraph::GetTailLinkAccess(int nLink)
{
	bool bRet = false;
	if(nLink == 0 || nLink == 3 || nLink == 2)
		bRet = true;

	return bRet;
}

