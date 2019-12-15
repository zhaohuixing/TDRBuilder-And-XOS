#include "stdafx.h"
#include "xvmm_clslink.h"
#include "xvmm_clsman.h"
#include "xvsb_macro.h"

CVMM_ClassLinker::CVMM_ClassLinker(int nID, CVUI_GraphManager* pManager)
	: CVMM_ModuleLinker(nID, pManager)
{
	m_puType = enXVSB_LINK;
}

CVMM_ClassLinker::CVMM_ClassLinker(const CPoint pts[], int nCount, int nID, CVUI_GraphManager* pManager)
	: CVMM_ModuleLinker(pts, nCount, nID, pManager)
{
	m_puType = enXVSB_LINK;
}

CVMM_ClassLinker::CVMM_ClassLinker(int nID, int nShape, CVUI_GraphManager* pManager)
	: CVMM_ModuleLinker(nID, nShape, pManager)
{
	m_puType = enXVSB_LINK;
}

CVMM_ClassLinker::~CVMM_ClassLinker()
{
}

void CVMM_ClassLinker::DrawNormal(CDC* pDC)
{
	CBrush brush(XVUI_CLSLINK_COLOR);
	
	CBrush lnkBrush(XVUI_LINK_CONNECTRGB);

    CBrush* pOldBrush = (CBrush*) pDC->SelectObject(&brush);
	CPen pen (PS_SOLID, 1, m_clrPen);
    CPen* pOldPen = (CPen*) pDC->SelectObject(&pen);

	pDC->MoveTo((CPoint)m_PolyLine[0]);
	int i;
	for(i = 1; i < (int)m_PolyLine.size(); i++)
	{
		if(!IsHorzLine(i-1))
		{
			pDC->LineTo((CPoint)m_PolyLine[i]);
		}
		else
		{
			DrawLineSegment(pDC, m_PolyLine[i-1], m_PolyLine[i]);
		}
	}

	// Draw the arrow in the head
	bool bHorz = (m_PolyLine[0].y == m_PolyLine[1].y);
	CPoint pts[3];
	pts[0] = (CPoint)m_PolyLine[0];
	if(bHorz) //
	{
		if(m_PolyLine[0].x <= m_PolyLine[1].x) // <- direction
		{
			pts[1].x = pts[0].x + XVUI_ARROW_CX;
			pts[1].y = pts[0].y - XVUI_ARROW_CY;
			pts[2].x = pts[0].x + XVUI_ARROW_CX;
			pts[2].y = pts[0].y + XVUI_ARROW_CY;
		}
		else //-> direction
		{
			pts[1].x = pts[0].x - XVUI_ARROW_CX;
			pts[1].y = pts[0].y - XVUI_ARROW_CY;
			pts[2].x = pts[0].x - XVUI_ARROW_CX;
			pts[2].y = pts[0].y + XVUI_ARROW_CY;
		}
	}
	else
	{
		if(m_PolyLine[0].y <= m_PolyLine[1].y) // Upper
		{
			pts[1].x = pts[0].x + XVUI_ARROW_CY;
			pts[1].y = pts[0].y + XVUI_ARROW_CX;
			pts[2].x = pts[0].x - XVUI_ARROW_CY;
			pts[2].y = pts[0].y + XVUI_ARROW_CX;
		}
		else
		{
			pts[1].x = pts[0].x + XVUI_ARROW_CY;
			pts[1].y = pts[0].y - XVUI_ARROW_CX;
			pts[2].x = pts[0].x - XVUI_ARROW_CY;
			pts[2].y = pts[0].y - XVUI_ARROW_CX;
		}
	}
    // Draw the polygon in DC
	if(m_bHeadLink)
		pDC->SelectObject(&lnkBrush);
	pDC->Polygon(pts, 3);

	if(m_bTailLink)
	{
		int nLast = (int)m_PolyLine.size()-1;
		bHorz = (m_PolyLine[nLast].y == m_PolyLine[nLast-1].y);
		CPoint ptend[4];
		
		if(bHorz) //
		{
			if(m_PolyLine[nLast].x <= m_PolyLine[nLast-1].x) // <- direction
			{
				ptend[0].x = m_PolyLine[nLast].x;
				ptend[0].y = m_PolyLine[nLast].y-2;
				ptend[1].x = ptend[0].x + 4;
				ptend[1].y = ptend[0].y;
				ptend[2].x = ptend[1].x;
				ptend[2].y = ptend[1].y+4;
				ptend[3].x = ptend[0].x;
				ptend[3].y = ptend[2].y;
			}
			else //-> direction
			{
				ptend[0].x = m_PolyLine[nLast].x;
				ptend[0].y = m_PolyLine[nLast].y-2;
				ptend[1].x = ptend[0].x - 4;
				ptend[1].y = ptend[0].y;
				ptend[2].x = ptend[1].x;
				ptend[2].y = ptend[1].y+4;
				ptend[3].x = ptend[0].x;
				ptend[3].y = ptend[2].y;
			}
		}
		else
		{
			if(m_PolyLine[0].y <= m_PolyLine[1].y) // Upper
			{
				ptend[0].x = m_PolyLine[nLast].x-2;
				ptend[0].y = m_PolyLine[nLast].y;
				ptend[1].x = ptend[0].x + 4;
				ptend[1].y = ptend[0].y;
				ptend[2].x = ptend[1].x;
				ptend[2].y = ptend[1].y-4;
				ptend[3].x = ptend[0].x;
				ptend[3].y = ptend[2].y;
			}
			else
			{
				ptend[0].x = m_PolyLine[nLast].x-2;
				ptend[0].y = m_PolyLine[nLast].y;
				ptend[1].x = ptend[0].x + 4;
				ptend[1].y = ptend[0].y;
				ptend[2].x = ptend[1].x;
				ptend[2].y = ptend[1].y+4;
				ptend[3].x = ptend[0].x;
				ptend[3].y = ptend[2].y;
			}
		}
		pDC->SelectObject(&lnkBrush);
		pDC->Polygon(ptend, 4);
	}

    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);
}

void CVMM_ClassLinker::ValidateLinkage(int nOldHead, int nOldTail)
{
	if(m_Manager == NULL)
		return;

	if(nOldHead == m_nHeadLink && nOldTail == m_nTailLink)
		return;

	((CVMM_ClassManager*)m_Manager)->ChangeLinkage(nOldHead, nOldTail, m_nHeadLink, m_nTailLink);
}

