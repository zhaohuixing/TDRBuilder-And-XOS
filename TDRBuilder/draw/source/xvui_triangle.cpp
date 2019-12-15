#include "stdafx.h"
#include "xvui_triangle.h"
#include "xvui_uiutils.h"

CVUI_Triangle::CVUI_Triangle(long	nID, CVUI_GraphManager*	pManager)
	:CVUI_GraphBase(nID, pManager)
{
	m_selBrush.lbColor = XVUI_BLOCK_ACTIVERGB;
	m_Radius.cy = XVUI_ENODE_CY;
	m_Radius.cx = m_Radius.cy;
}

CVUI_Triangle::~CVUI_Triangle()
{
}

int CVUI_Triangle::GetLinkCount(void)
{
	return XVUI_TRI_LINKS;
}

CRect CVUI_Triangle::GetBoundaryExt(void)
{
	int nSzie = xvui_ztsize[XVUI_ZOOM_DEFAULT];
	if(0 <= m_nZoom && m_nZoom < XVUI_ZOOMS)
		nSzie = xvui_ztsize[m_nZoom];

	int nSX = 0;
	int nSY = 0;

	nSzie +=1;

	if(m_bShadow == TRUE)
	{
		nSX = XVUI_TRI_SHADOWY*m_Radius.cx*1.8/m_Radius.cy;  
		nSY = XVUI_ENODE_SHADOWY;
	}

	int nW = max(m_txtRect.Width()/2+1, m_Radius.cx);
	int nH = max(m_txtRect.Height()/2+1, m_Radius.cy);

	nW += nSzie*2;
	nH += nSzie*2;

	CRect rect(m_ptCenter.x-nW, m_ptCenter.y-nH, 
		       m_ptCenter.x+nW+nSX, m_ptCenter.y+nH+nSY);

	return rect;
}

	
CPoint CVUI_Triangle::GetLink(int nLink)
{
	CPoint pt(0, 0);
	switch(nLink)
	{
		case 0:
			pt.x = m_ptCenter.x;
			pt.y = m_ptCenter.y - m_Radius.cy;
			break;
		case 1:
			pt.x = m_ptCenter.x + m_Radius.cx;
			pt.y = m_ptCenter.y + m_Radius.cy;
			break;
		case 2:
			pt.x = m_ptCenter.x - m_Radius.cx;
			pt.y = m_ptCenter.y + m_Radius.cy;
			break;
	}

	return pt;
}

HCURSOR CVUI_Triangle::GetLinkCursor(int nLink)
{
	//ASSERT(this);
	ASSERT(this);

	LPCTSTR id;
	switch (nLink)
	{
		case 0:
			id = IDC_SIZENS;
			break;
		case 1:
			id = IDC_SIZENWSE;
			break;
		case 2:
			id = IDC_SIZENESW;
			break;
		default:
			ASSERT(FALSE);
	}

	return AfxGetApp()->LoadStandardCursor(id);
}

void CVUI_Triangle::DrawNormal(CDC* pDC)
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

	CPoint pPts[3];
	pPts[0].x = m_ptCenter.x;
	pPts[0].y = m_ptCenter.y-m_Radius.cy;
	pPts[1].x = m_ptCenter.x+m_Radius.cx;
	pPts[1].y = m_ptCenter.y+m_Radius.cy;
	pPts[2].x = m_ptCenter.x-m_Radius.cx;
	pPts[2].y = m_ptCenter.y+m_Radius.cy;

    // Draw the polygon in DC
	pDC->Polygon(pPts, 3);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);

	double d1 = (double)m_Radius.cx;
	double d2 = (double)(m_Radius.cy*2);
	double d = (double)d2/d1;

    int nw = (int)(((double)m_Radius.cx)*0.25);
    int nh = (int)(((double)nw)*d);

	CBrush brushNo;
	brushNo.CreateSolidBrush(XVUI_BLOCK_NORGB);
	
	CPen penNo;
	penNo.CreatePen(PS_SOLID, 1, XVUI_BLOCK_NORGB);

	pOldBrush = pDC->SelectObject(&brushNo);
	pOldPen = pDC->SelectObject(&penNo);

	CPoint pPts1[3];
	pPts1[0].x = pPts[2].x+nw;
	pPts1[0].y = pPts[2].y;
	pPts1[1].x = pPts1[0].x;
	pPts1[1].y = pPts[2].y-nh;
	pPts1[2] = pPts[2];

	pDC->Polygon(pPts1, 3);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);

	CBrush brushYes;
	brushYes.CreateSolidBrush(XVUI_BLOCK_YESRGB);
	
	CPen penYes;
	penYes.CreatePen(PS_SOLID, 1, XVUI_BLOCK_YESRGB);

	pOldBrush = pDC->SelectObject(&brushYes);
	pOldPen = pDC->SelectObject(&penYes);

	pPts1[0].x = pPts[1].x-nw;
	pPts1[0].y = pPts[1].y;
	pPts1[1].x = pPts1[0].x;
	pPts1[1].y = pPts[1].y-nh;
	pPts1[2] = pPts[1];

	pDC->Polygon(pPts1, 3);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);

	pOldBrush = pDC->SelectObject(&brush);
	pOldPen = pDC->SelectObject(&pen);

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

void CVUI_Triangle::DrawShadow(CDC* pDC)
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

	int nxs = XVUI_TRI_SHADOWY*m_Radius.cx*1.8/m_Radius.cy;  

	CPoint pPts[3];
	pPts[0].x = m_ptCenter.x+nxs;
	pPts[0].y = m_ptCenter.y-m_Radius.cy+XVUI_TRI_SHADOWY;
	pPts[1].x = m_ptCenter.x+m_Radius.cx+nxs;
	pPts[1].y = m_ptCenter.y+m_Radius.cy+XVUI_TRI_SHADOWY;
	pPts[2].x = m_ptCenter.x-m_Radius.cx+nxs;
	pPts[2].y = m_ptCenter.y+m_Radius.cy+XVUI_TRI_SHADOWY;

    // Draw the polygon in DC
	pDC->Polygon(pPts, 3);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pBrush);
	pDC->SetROP2(nOldMode);
}

void CVUI_Triangle::DrawSelected(CDC* pDC)
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

	CPoint pPts[3];
	pPts[0].x = m_ptCenter.x;
	pPts[0].y = m_ptCenter.y-m_Radius.cy;
	pPts[1].x = m_ptCenter.x+m_Radius.cx;
	pPts[1].y = m_ptCenter.y+m_Radius.cy;
	pPts[2].x = m_ptCenter.x-m_Radius.cx;
	pPts[2].y = m_ptCenter.y+m_Radius.cy;

    // Draw the polygon in DC
	pDC->Polygon(pPts, 3);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);

	double d1 = (double)m_Radius.cx;
	double d2 = (double)(m_Radius.cy*2);
	double d = (double)d2/d1;

    int nw = (int)(((double)m_Radius.cx)*0.25);
    int nh = (int)(((double)nw)*d);

	CBrush brushNo;
	brushNo.CreateSolidBrush(XVUI_BLOCK_NORGB);
	
	CPen penNo;
	penNo.CreatePen(PS_SOLID, 1, XVUI_BLOCK_NORGB);

	pOldBrush = pDC->SelectObject(&brushNo);
	pOldPen = pDC->SelectObject(&penNo);

	CPoint pPts1[3];
	pPts1[0].x = pPts[2].x+nw;
	pPts1[0].y = pPts[2].y;
	pPts1[1].x = pPts1[0].x;
	pPts1[1].y = pPts[2].y-nh;
	pPts1[2] = pPts[2];

	pDC->Polygon(pPts1, 3);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);

	CBrush brushYes;
	brushYes.CreateSolidBrush(XVUI_BLOCK_YESRGB);
	
	CPen penYes;
	penYes.CreatePen(PS_SOLID, 1, XVUI_BLOCK_YESRGB);

	pOldBrush = pDC->SelectObject(&brushYes);
	pOldPen = pDC->SelectObject(&penYes);

	pPts1[0].x = pPts[1].x-nw;
	pPts1[0].y = pPts[1].y;
	pPts1[1].x = pPts1[0].x;
	pPts1[1].y = pPts[1].y-nh;
	pPts1[2] = pPts[1];

	pDC->Polygon(pPts1, 3);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);

	pOldBrush = pDC->SelectObject(&brush);
	pOldPen = pDC->SelectObject(&pen);

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

void CVUI_Triangle::DrawDebug(CDC* pDC)
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

	CPoint pPts[3];
	pPts[0].x = m_ptCenter.x;
	pPts[0].y = m_ptCenter.y-m_Radius.cy;
	pPts[1].x = m_ptCenter.x+m_Radius.cx;
	pPts[1].y = m_ptCenter.y+m_Radius.cy;
	pPts[2].x = m_ptCenter.x-m_Radius.cx;
	pPts[2].y = m_ptCenter.y+m_Radius.cy;

    // Draw the polygon in DC
	pDC->Polygon(pPts, 3);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);

	double d1 = (double)m_Radius.cx;
	double d2 = (double)(m_Radius.cy*2);
	double d = (double)d2/d1;

    int nw = (int)(((double)m_Radius.cx)*0.25);
    int nh = (int)(((double)nw)*d);

	CBrush brushNo;
	brushNo.CreateSolidBrush(XVUI_BLOCK_NORGB);
	
	CPen penNo;
	penNo.CreatePen(PS_SOLID, 1, XVUI_BLOCK_NORGB);

	pOldBrush = pDC->SelectObject(&brushNo);
	pOldPen = pDC->SelectObject(&penNo);

	CPoint pPts1[3];
	pPts1[0].x = pPts[2].x+nw;
	pPts1[0].y = pPts[2].y;
	pPts1[1].x = pPts1[0].x;
	pPts1[1].y = pPts[2].y-nh;
	pPts1[2] = pPts[2];

	pDC->Polygon(pPts1, 3);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);

	CBrush brushYes;
	brushYes.CreateSolidBrush(XVUI_BLOCK_YESRGB);
	
	CPen penYes;
	penYes.CreatePen(PS_SOLID, 1, XVUI_BLOCK_YESRGB);

	pOldBrush = pDC->SelectObject(&brushYes);
	pOldPen = pDC->SelectObject(&penYes);

	pPts1[0].x = pPts[1].x-nw;
	pPts1[0].y = pPts[1].y;
	pPts1[1].x = pPts1[0].x;
	pPts1[1].y = pPts[1].y-nh;
	pPts1[2] = pPts[1];

	pDC->Polygon(pPts1, 3);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);

	pOldBrush = pDC->SelectObject(&brush);
	pOldPen = pDC->SelectObject(&pen);

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

bool CVUI_Triangle::HitBlock(CPoint pt)
{
	bool bRet = false;

	if(pt == m_ptCenter)
	{
		bRet = true;
		return bRet;
	}

	CPoint pPts[3];
	pPts[0].x = m_ptCenter.x;
	pPts[0].y = m_ptCenter.y-m_Radius.cy;
	pPts[1].x = m_ptCenter.x+m_Radius.cx;
	pPts[1].y = m_ptCenter.y+m_Radius.cy;
	pPts[2].x = m_ptCenter.x-m_Radius.cx;
	pPts[2].y = m_ptCenter.y+m_Radius.cy;


	CVUI_HitUtility hittest;

	if(hittest.PtInPloy(pPts, 3, pt))
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
