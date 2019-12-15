#include "stdafx.h"
#include "xvmm_mlinker.h"
#include "xvmm_mman.h"
#include "xvsb_macro.h"

CVMM_ModuleLinker::CVMM_ModuleLinker(int nID, CVUI_GraphManager* pManager)
	: CVUI_PolyLine(nID, pManager)
{
	m_bHeadLink = false;
	m_bTailLink = false;
	m_bGhostHeadLink = false;
	m_bGhostTailLink = false;

	m_rectGHLink.SetRect(0, 0, 1, 1);
	m_rectGTLink.SetRect(0, 0, 1, 1);
	m_nHeadLink = XVSM_PU_ERROR;	
	m_nTailLink = XVSM_PU_ERROR;	
	m_puType = enXVSB_LINK;
	m_bTail2Logic = false;
	m_bTail2LogicYes = false;
}

CVMM_ModuleLinker::CVMM_ModuleLinker(const CPoint pts[], int nCount, int nID, CVUI_GraphManager* pManager)
	: CVUI_PolyLine(pts, nCount, nID, pManager)
{
	m_bHeadLink = false;
	m_bTailLink = false;
	m_bGhostHeadLink = false;
	m_bGhostTailLink = false;

	m_rectGHLink.SetRect(0, 0, 1, 1);
	m_rectGTLink.SetRect(0, 0, 1, 1);
	m_nHeadLink = XVSM_PU_ERROR;	
	m_nTailLink = XVSM_PU_ERROR;	
	m_puType = enXVSB_LINK;
	m_bTail2Logic = false;
	m_bTail2LogicYes = false;
}

CVMM_ModuleLinker::CVMM_ModuleLinker(int nID, int nShape, CVUI_GraphManager* pManager)
	: CVUI_PolyLine(nID, nShape, pManager)
{
	m_bHeadLink = false;
	m_bTailLink = false;
	m_bGhostHeadLink = false;
	m_bGhostTailLink = false;

	m_rectGHLink.SetRect(0, 0, 1, 1);
	m_rectGTLink.SetRect(0, 0, 1, 1);
	m_nHeadLink = XVSM_PU_ERROR;	
	m_nTailLink = XVSM_PU_ERROR;	
	m_puType = enXVSB_LINK;
	m_bTail2Logic = false;
	m_bTail2LogicYes = false;
}

CVMM_ModuleLinker::~CVMM_ModuleLinker()
{
}

void CVMM_ModuleLinker::DrawNormal(CDC* pDC)
{
	CBrush brush(m_clrPen);
	
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
//		bHorz = (m_PolyLine[nLast].y == m_PolyLine[nLast-1].y);
		CPoint ptend[4];
	
/*
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
*/
		ptend[0].x = m_PolyLine[nLast].x-2;
		ptend[0].y = m_PolyLine[nLast].y-2;
		ptend[1].x = ptend[0].x + 4;
		ptend[1].y = ptend[0].y;
		ptend[2].x = ptend[1].x;
		ptend[2].y = ptend[1].y+4;
		ptend[3].x = ptend[0].x;
		ptend[3].y = ptend[2].y;
		pDC->SelectObject(&lnkBrush);
		pDC->Polygon(ptend, 4);
	}

    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);
}

void CVMM_ModuleLinker::DrawSelected(CDC* pDC)
{
	CBrush brush(m_selBrush.lbColor);

	CBrush lnkBrush(XVUI_LINK_CONNECTRGB);

    CBrush* pOldBrush = (CBrush*) pDC->SelectObject(&brush);
	CPen pen (PS_SOLID, 1, m_selBrush.lbColor);
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
//		bHorz = (m_PolyLine[nLast].y == m_PolyLine[nLast-1].y);
		CPoint ptend[4];

/*
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
*/
		ptend[0].x = m_PolyLine[nLast].x-2;
		ptend[0].y = m_PolyLine[nLast].y-2;
		ptend[1].x = ptend[0].x + 4;
		ptend[1].y = ptend[0].y;
		ptend[2].x = ptend[1].x;
		ptend[2].y = ptend[1].y+4;
		ptend[3].x = ptend[0].x;
		ptend[3].y = ptend[2].y;

		pDC->SelectObject(&lnkBrush);
		pDC->Polygon(ptend, 4);
	}

    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);

	if(m_bDrawTrack == true)
	{
		DrawGhost(pDC);
	}
}

void CVMM_ModuleLinker::DrawGhost(CDC* pDC)
{
	if(!IsSelected())
		return;
	
	int nMode = pDC->SetROP2(R2_COPYPEN);
	CBrush brush(XVUI_TRACKER_RGB);
    CBrush* pOldBrush = (CBrush*) pDC->SelectObject(&brush);
	CPen pen (PS_DASH, 0, XVUI_TRACKER_RGB);
    CPen* pOldPen = (CPen*) pDC->SelectObject(&pen);

	pDC->MoveTo((CPoint)m_TrackLine[0]);
	int i;
	for(i = 1; i < (int)m_TrackLine.size(); i++)
	{
		pDC->LineTo(m_TrackLine[i]);
	}

	// Draw the arrow in the head
	bool bHorz = (m_TrackLine[0].y == m_TrackLine[1].y);
	CPoint pts[3];
	pts[0] = (CPoint)m_TrackLine[0];
	if(bHorz) //
	{
		if(m_TrackLine[0].x <= m_TrackLine[1].x) // <- direction
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
		if(m_TrackLine[0].y <= m_TrackLine[1].y) // Upper
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
    pDC->SelectObject(pOldPen);
	CPen penArrow(PS_SOLID, 0, XVUI_TRACKER_RGB);
    pOldPen = (CPen*) pDC->SelectObject(&penArrow);

	pDC->Polygon(pts, 3);

	if(m_bGhostHeadLink == true || m_bGhostTailLink == true)
	{
		pDC->SelectObject(pOldPen);
		CPen penBlock(PS_SOLID, 0, RGB(0, 0, 0));
		pOldPen = (CPen*) pDC->SelectObject(&penBlock);

		pDC->SelectObject(pOldBrush);
		CBrush lnkBrush(XVUI_LINK_CONNECTRGB);
		pOldBrush = (CBrush*)pDC->SelectObject(&lnkBrush);

		if(m_bGhostHeadLink == true)
			pDC->Rectangle(&m_rectGHLink);

		if(m_bGhostTailLink == true)
			pDC->Rectangle(&m_rectGTLink);
	}

    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);
	pDC->SetROP2(nMode);
}

void CVMM_ModuleLinker::MoveCenter(CPoint ptOff)
{
	CVUI_PolyLine::MoveCenter(ptOff);
	UpdateLinkage();
}

void CVMM_ModuleLinker::ChangeShape(CPoint ptOff)
{
	CVUI_PolyLine::ChangeShape(ptOff);
	UpdateLinkage();
}

void CVMM_ModuleLinker::UpdateLinkage(void)
{
	int nOldHead, nOldTail;
	nOldHead = m_nHeadLink; 
	nOldTail = m_nTailLink;
	m_bTail2Logic = false;
	m_bTail2LogicYes = false;

    UpdateHeadLink();
    UpdateTailLink();
    
	if(m_bDrawTrack == false)
	{
		ValidateLinkage(nOldHead, nOldTail);
	}
}

void CVMM_ModuleLinker::UpdateHeadLink(void)
{
	if(m_Manager == NULL)
		return;

	if(m_bDrawTrack == true)
	{
		UpdateGhostHeadLink();
	}
	else
	{
		UpdateRealHeadLink();
	}
}

void CVMM_ModuleLinker::UpdateTailLink(void)
{
	if(m_Manager == NULL)
		return;

	if(m_bDrawTrack == true)
	{
		UpdateGhostTailLink();
	}
	else
	{
		UpdateRealTailLink();
	}
}
    
void CVMM_ModuleLinker::ValidateLinkage(int nOldHead, int nOldTail)
{
	if(m_Manager == NULL)
		return;

	if(nOldHead == m_nHeadLink && nOldTail == m_nTailLink)
		return;

	if(m_bTail2Logic == false)
	{
		((CVMM_ModuleManager*)m_Manager)->ChangeLinkage(nOldHead, nOldTail, m_nHeadLink, m_nTailLink);
	}
	else
	{
		if(m_bTail2LogicYes == true)
		{
			((CVMM_ModuleManager*)m_Manager)->ChangeLogicYesLinkage(nOldHead, nOldTail, m_nHeadLink, m_nTailLink);
		}
		else
		{
			((CVMM_ModuleManager*)m_Manager)->ChangeLogicNoLinkage(nOldHead, nOldTail, m_nHeadLink, m_nTailLink);
		}
	}
	
}

void CVMM_ModuleLinker::UpdateGhostHeadLink(void)
{
	if(m_bDrawTrack == false || m_Manager == NULL)
		return;

	CPoint pt = m_TrackLine[0];
	int nCount;
	int nIndex;
	CRect rect;

	CVUI_GraphMap::reverse_iterator riter;
	for(riter = m_Manager->m_GraphMap.rbegin(); riter != m_Manager->m_GraphMap.rend(); ++riter)
	{
		if(riter->first <= XVSM_PU_LINK_FIRST)
			break;
        
        nCount = riter->second->GetLinkCount();
		for(nIndex = 0; nIndex < nCount; nIndex++)
		{
			rect = riter->second->GetLinkRect(nIndex);
			if(rect.PtInRect(pt))
			{
				if(riter->second->GetHeadLinkAccess(nIndex))
				{
					m_bGhostHeadLink = true;
					m_rectGHLink = rect;
					return;
				}
			}
		}
	}

	m_bGhostHeadLink = false;
}

void CVMM_ModuleLinker::UpdateRealHeadLink(void)
{
	if(m_bDrawTrack == true || m_Manager == NULL)
		return;

	CPoint pt = (CPoint)m_PolyLine[0];
	CPoint pt1, ptoff;
	int nCount;
	int nIndex;
	CRect rect;
	int nLinkID = GetID();

	CVUI_GraphMap::reverse_iterator riter;
	for(riter = m_Manager->m_GraphMap.rbegin(); riter != m_Manager->m_GraphMap.rend(); ++riter)
	{
		if(riter->first <= XVSM_PU_LINK_FIRST)
			break;

        nCount = riter->second->GetLinkCount();
		for(nIndex = 0; nIndex < nCount; nIndex++)
		{
			rect = riter->second->GetLinkRect(nIndex);
			if(rect.PtInRect(pt))
			{
				if(riter->second->GetHeadLinkAccess(nIndex))
				{
					if(m_Manager->CanSetHeadLink(nLinkID, riter->first))
					{
						pt1 = riter->second->GetLink(nIndex); 
						ptoff = pt1 - pt;
						MoveHead(ptoff);
						m_bHeadLink = true;
						m_nHeadLink = riter->first;
						return;
					}
				}
			}
		}
	}
	m_nHeadLink = XVSM_PU_ERROR;	
	m_bHeadLink = false;
}

void CVMM_ModuleLinker::UpdateGhostTailLink(void)
{
	if(m_bDrawTrack == false || m_Manager == NULL)
		return;

	int nLast = (int)m_TrackLine.size()-1;
	CPoint pt = m_TrackLine[nLast];
	int nCount;
	int nIndex;
	CRect rect;

	CVUI_GraphMap::reverse_iterator riter;
	for(riter = m_Manager->m_GraphMap.rbegin(); riter != m_Manager->m_GraphMap.rend(); ++riter)
	{
		if(riter->first <= XVSM_PU_LINK_FIRST)
			break;

        nCount = riter->second->GetLinkCount();
		for(nIndex = 0; nIndex < nCount; nIndex++)
		{
			rect = riter->second->GetLinkRect(nIndex);
			if(rect.PtInRect(pt))
			{
				if(riter->second->GetTailLinkAccess(nIndex))
				{
					m_bGhostTailLink = true;
					m_rectGTLink = rect;
					return;
				}
			}
		}
	}
	m_bGhostTailLink = false;
}

void CVMM_ModuleLinker::UpdateRealTailLink(void)
{
	if(m_bDrawTrack == true || m_Manager == NULL)
		return;

	int nLast = (int)m_PolyLine.size()-1;
	CPoint pt = (CPoint)m_PolyLine[nLast];
	CPoint pt1, ptoff;
	int nCount;
	int nIndex;
	CRect rect;
	int nLinkID = GetID();

	m_bTail2Logic = false;
	m_bTail2LogicYes = false;

	CVUI_GraphMap::reverse_iterator riter;
	for(riter = m_Manager->m_GraphMap.rbegin(); riter != m_Manager->m_GraphMap.rend(); ++riter)
	{
		if(riter->first <= XVSM_PU_LINK_FIRST)
			break;

        nCount = riter->second->GetLinkCount();
		for(nIndex = 0; nIndex < nCount; nIndex++)
		{
			rect = riter->second->GetLinkRect(nIndex);
			if(rect.PtInRect(pt))
			{
				if(riter->second->GetTailLinkAccess(nIndex))
				{
					if(m_Manager->CanSetTailLink(nLinkID, riter->first))
					{
						pt1 = riter->second->GetLink(nIndex); 
						ptoff = pt1 - pt;
						MoveTail(ptoff);
						m_bTailLink = true;
						m_nTailLink = riter->first;	
						if(riter->second->GetType() == enXVSB_PULOGIC)
						{
							m_bTail2Logic = true;
							if(nIndex == 1)
								m_bTail2LogicYes = true;
						}
						return;
					}
				}
			}
		}
	}
	m_nTailLink = XVSM_PU_ERROR;	
	m_bTailLink = false;
}

bool CVMM_ModuleLinker::IsHeadMovable(void)
{
	bool bRet = (m_bHeadLink == false);
	return bRet;
}

bool CVMM_ModuleLinker::IsTailMovable(void)
{
	bool bRet = (m_bTailLink == false);
	return bRet;
}
