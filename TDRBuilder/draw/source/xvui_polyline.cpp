#include "stdafx.h"
#include "xvui_graphman.h"
#include "xvui_polyline.h"
#include <algorithm>
#include <functional>
#include "xvsb_macro.h"
#include "xvui_uiutils.h"
#include "xvui_uidefs.h"

CVUI_PolyLine::CVUI_PolyLine(int nID, CVUI_GraphManager*	pManager)
	:CVUI_GraphBase(nID, pManager)
{
	m_PolyLine.clear();
	m_selBrush.lbColor = XVUI_LINE_ACTIVERGB;
	m_PolyLine.push_back(CVUI_LinkPoint(XVUI_ENODE_CX*2, XVUI_ENODE_CY));
	m_PolyLine.push_back(CVUI_LinkPoint(XVUI_ENODE_CX, XVUI_ENODE_CY));
	m_PolyLine.push_back(CVUI_LinkPoint(XVUI_ENODE_CX, XVUI_ENODE_CY*2));
	m_bDrawTrack = false;
	m_bMoveHeadTail = false;
	m_hOldCursor = NULL;
}

CVUI_PolyLine::CVUI_PolyLine(const CPoint pts[], int nCount, int nID, CVUI_GraphManager* pManager)
	:CVUI_GraphBase(nID, pManager)
{
	m_PolyLine.clear();
	m_selBrush.lbColor = XVUI_LINE_ACTIVERGB;
	m_bMoveHeadTail = false;
	m_hOldCursor = NULL;

	if(nCount < 2)
	{
		m_PolyLine.push_back(CVUI_LinkPoint(XVUI_ENODE_CX*2, XVUI_ENODE_CY));
		m_PolyLine.push_back(CVUI_LinkPoint(XVUI_ENODE_CX, XVUI_ENODE_CY));
	}
	else
	{
		for(int i = 0; i < nCount; i++)
		{
			m_PolyLine.push_back(pts[i]);
		}
		StraightLine();
		RemoveOverlay();
	}
	m_bDrawTrack = false;
}

CVUI_PolyLine::CVUI_PolyLine(int nID, int nShape, CVUI_GraphManager* pManager)
	:CVUI_GraphBase(nID, pManager)
{
	m_PolyLine.clear();
	m_selBrush.lbColor = XVUI_LINE_ACTIVERGB;
	m_bMoveHeadTail = false;
	m_hOldCursor = NULL;

	if(nShape == 2) //<-
	{
		m_PolyLine.push_back(CVUI_LinkPoint(0, 0));
		m_PolyLine.push_back(CVUI_LinkPoint(XVUI_ENODE_CY, 0));
	}
	else if(nShape == 3) //|
	{
		m_PolyLine.push_back(CVUI_LinkPoint(0, 0));
		m_PolyLine.push_back(CVUI_LinkPoint(0, XVUI_ENODE_CY));
	}
	else if(nShape == 4) //->
	{
		m_PolyLine.push_back(CVUI_LinkPoint(XVUI_ENODE_CY, 0));
		m_PolyLine.push_back(CVUI_LinkPoint(0, 0));
	}
	else if(nShape == 5) //|
	{
		m_PolyLine.push_back(CVUI_LinkPoint(XVUI_ENODE_CY, XVUI_ENODE_CY));
		m_PolyLine.push_back(CVUI_LinkPoint(0, XVUI_ENODE_CY));
		m_PolyLine.push_back(CVUI_LinkPoint(0, 0));
		m_PolyLine.push_back(CVUI_LinkPoint(XVUI_ENODE_CY, 0));
	}
	else if(nShape == 6) //|
	{
		m_PolyLine.push_back(CVUI_LinkPoint(0, XVUI_ENODE_CY));
		m_PolyLine.push_back(CVUI_LinkPoint(XVUI_ENODE_CY, XVUI_ENODE_CY));
		m_PolyLine.push_back(CVUI_LinkPoint(XVUI_ENODE_CY, 0));
		m_PolyLine.push_back(CVUI_LinkPoint(0, 0));
	}
	else if(nShape == 7) //|
	{
		m_PolyLine.push_back(CVUI_LinkPoint(XVUI_ENODE_CY, 0));
		m_PolyLine.push_back(CVUI_LinkPoint(0, 0));
		m_PolyLine.push_back(CVUI_LinkPoint(0, XVUI_ENODE_CY));
		m_PolyLine.push_back(CVUI_LinkPoint(XVUI_ENODE_CY, XVUI_ENODE_CY));
	}
	else if(nShape == 8) //|
	{
		m_PolyLine.push_back(CVUI_LinkPoint(0, 0));
		m_PolyLine.push_back(CVUI_LinkPoint(XVUI_ENODE_CY, 0));
		m_PolyLine.push_back(CVUI_LinkPoint(XVUI_ENODE_CY, XVUI_ENODE_CY));
		m_PolyLine.push_back(CVUI_LinkPoint(0, XVUI_ENODE_CY));
	}
	else if(nShape == 9) //|
	{
		m_PolyLine.push_back(CVUI_LinkPoint(XVUI_ENODE_CY, 0));
		m_PolyLine.push_back(CVUI_LinkPoint(XVUI_ENODE_CY, XVUI_ENODE_CY));
		m_PolyLine.push_back(CVUI_LinkPoint(0, XVUI_ENODE_CY));
		m_PolyLine.push_back(CVUI_LinkPoint(0, XVUI_ENODE_CY*2));
	}
	else if(nShape == 10) //|
	{
		m_PolyLine.push_back(CVUI_LinkPoint(0, 0));
		m_PolyLine.push_back(CVUI_LinkPoint(0, XVUI_ENODE_CY));
		m_PolyLine.push_back(CVUI_LinkPoint(XVUI_ENODE_CY, XVUI_ENODE_CY));
		m_PolyLine.push_back(CVUI_LinkPoint(XVUI_ENODE_CY, XVUI_ENODE_CY*2));
	}
	else
	{
		m_PolyLine.push_back(CVUI_LinkPoint(0, XVUI_ENODE_CY));
		m_PolyLine.push_back(CVUI_LinkPoint(0, 0));
	}

	m_bDrawTrack = false;
}

CVUI_PolyLine::~CVUI_PolyLine()
{
	m_PolyLine.clear();
	m_selBrush.lbColor = XVUI_LINE_ACTIVERGB;
	m_bDrawTrack = false;
}

bool CVUI_PolyLine::HitTest(CPoint point, int& nHandle)
{
	bool bRet = false;
	nHandle = -1;

	if(IsSelected())
	{
		bRet = HitHandleTest(point, nHandle);
		if(bRet)
			return bRet;
	}
	else
	{
		bRet = HitHeadTailTest(point, nHandle);
		if(bRet)
			return bRet;
	}

	if(HitBlock(point))
	{
		bRet = true;
		return bRet;
	}

	return bRet;
}

bool CVUI_PolyLine::HitHeadTailTest(CPoint point, int& nHandle)
{
	bool bRet = false;
	nHandle = -1;

	int nHandleCount = GetHandleCount();
	CRect rect;

	rect = GetHandleRectExt(0);
	if(rect.PtInRect(point))
	{
		bRet = true;
		nHandle = 0;
		return bRet;
	}

	int nX, nY;
	rect = GetHandleRect(nHandleCount-1);
	nX = rect.Width()/2;
	nY = rect.Height()/2;
	rect.InflateRect(nX, nY);
	if(rect.PtInRect(point))
	{
		bRet = true;
		nHandle = nHandleCount-1;
		return bRet;
	}

	return bRet;
}

bool CVUI_PolyLine::IsHeadHandle(int nHandle)
{
	bool bRet = false;

	bRet = (nHandle == 0);

	return bRet;
}

bool CVUI_PolyLine::IsTailHandle(int nHandle)
{
	bool bRet = false;
	int nHandleCount = GetHandleCount();

	bRet = (nHandle == nHandleCount-1);

	return bRet;
}


bool CVUI_PolyLine::HitHandleTest(CPoint point, int& nHandle)
{
	bool bRet = false;
	nHandle = -1;

	int nHandleCount = GetHandleCount();
	CRect rect;

	rect = GetHandleRectExt(0);
	if(rect.PtInRect(point))
	{
		bRet = true;
		nHandle = 0;
		return bRet;
	}

	int nX, nY;

	for (int i = 1; i < nHandleCount; i++)
	{
		rect = GetHandleRect(i);
		nX = rect.Width()/2;
		nY = rect.Height()/2;
		rect.InflateRect(nX, nY);
		if(rect.PtInRect(point))
		{
			bRet = true;
			nHandle = i;
			return bRet;
		}
	}
	return bRet;
}

bool CVUI_PolyLine::HitBlock(CPoint point)
{
	bool bRet = false;
	CRect rect;

	int nSzie = xvui_ztsize[XVUI_ZOOM_DEFAULT];
	if(0 <= m_nZoom && m_nZoom < XVUI_ZOOMS)
		nSzie = xvui_ztsize[m_nZoom];

	rect = GetHandleRectExt(0);
	if(rect.PtInRect(point))
	{
		bRet = true;
		return bRet;
	}

	int nLines = GetLineCount();

	for (int i = 0; i < nLines; i++)
	{
		if(IsHorzLine(i))
		{
			rect.left = min(m_PolyLine[i].x, m_PolyLine[i+1].x);
			rect.right = max(m_PolyLine[i].x, m_PolyLine[i+1].x);
			rect.top = m_PolyLine[i].y-nSzie;
			rect.bottom = m_PolyLine[i].y+nSzie;
		}
		else
		{
			rect.top = min(m_PolyLine[i].y, m_PolyLine[i+1].y);
			rect.bottom = max(m_PolyLine[i].y, m_PolyLine[i+1].y);
			rect.left = m_PolyLine[i].x-nSzie;
			rect.right = m_PolyLine[i].x+nSzie;
		}
		if(rect.PtInRect(point))
		{
			bRet = true;
			return bRet;
		}
	}
	return bRet;
}

int CVUI_PolyLine::GetLineCount(void)
{
	int nLines = (int)m_PolyLine.size()-1;

	return nLines;
}

int CVUI_PolyLine::GetPointCount(void)
{
	int nPoints = (int)m_PolyLine.size();

	return nPoints;
}

int CVUI_PolyLine::GetHandleCount(void)
{
	int nLines = GetLineCount();
	int nHandles = 2*nLines+1;

	return nHandles;
}
	
CPoint CVUI_PolyLine::GetHandle(int nHandle)
{
	CPoint pt(0, 0);
	int nCount = GetHandleCount();
	if(nHandle < 0 || nCount <= nHandle)
		return pt;

	if(nHandle == 0)
		return (CPoint)m_PolyLine[nHandle];

	if(nHandle == nCount-1)
	{
		pt = (CPoint)m_PolyLine[GetPointCount()-1];
		return pt;
	}

	int nLine = GetHandleLineIndex(nHandle);
	bool bMiddle = (nHandle%2 == 1);
	if(bMiddle)
	{
		if(IsHorzLine(nLine))
		{
			pt.y = m_PolyLine[nLine].y;
			pt.x = (m_PolyLine[nLine].x+m_PolyLine[nLine+1].x)/2;
		}
		else
		{
			pt.x = m_PolyLine[nLine].x;
			pt.y = (m_PolyLine[nLine].y+m_PolyLine[nLine+1].y)/2;
		}
	}
	else
	{
		pt = m_PolyLine[nLine];
	}

	return pt;
}
	
CPoint CVUI_PolyLine::GetHeadPoint(void)
{
	return (CPoint)m_PolyLine[0];
}

CPoint CVUI_PolyLine::GetTailPoint(void)
{
	return (CPoint)m_PolyLine[GetPointCount()-1];
}

CRect CVUI_PolyLine::GetHandleRect(int nHandle)
{
	bool bRet = false;

	CRect rect(0, 0, 1, 1);
	int nCount = GetHandleCount();

	bRet = (0 <= nHandle || nHandle < nCount);
	ASSERT(bRet);
	
	if(!bRet)
		return rect; 

	int nSzie = xvui_ztsize[XVUI_ZOOM_DEFAULT];
	if(0 <= m_nZoom && m_nZoom < XVUI_ZOOMS)
		nSzie = xvui_ztsize[m_nZoom];

	CPoint pt = GetHandle(nHandle);

	rect.left = pt.x - nSzie;
	rect.top = pt.y - nSzie;
	rect.right = pt.x + nSzie;
	rect.bottom = pt.y + nSzie;

	return rect;
}

CRect CVUI_PolyLine::GetHandleRectExt(int nHandle)
{
	bool bRet = false;

	CRect rect(0, 0, 1, 1);

	int nCount = GetHandleCount();
	bRet = (0 <= nHandle || nHandle < nCount);
	ASSERT(bRet);
	
	if(!bRet)
		return rect; 

	if(nHandle == 0)
	{
		bool bHorz = (m_PolyLine[0].y == m_PolyLine[1].y);
		if(bHorz) //
		{
			if(m_PolyLine[0].x <= m_PolyLine[1].x) // <- direction
			{
				rect.left = m_PolyLine[0].x;
				rect.right = m_PolyLine[0].x + XVUI_ARROW_CX;
				rect.top = m_PolyLine[0].y - XVUI_ARROW_CY;
				rect.bottom = m_PolyLine[0].y + XVUI_ARROW_CY;
			}
			else //-> direction
			{
				rect.left = m_PolyLine[0].x - XVUI_ARROW_CX;
				rect.right = m_PolyLine[0].x;
				rect.top = m_PolyLine[0].y - XVUI_ARROW_CY;
				rect.bottom = m_PolyLine[0].y + XVUI_ARROW_CY;
			}
		}
		else
		{
			if(m_PolyLine[0].y <= m_PolyLine[1].y) // Upper
			{
				rect.left = m_PolyLine[0].x - XVUI_ARROW_CY;
				rect.right = m_PolyLine[0].x + XVUI_ARROW_CY;
				rect.top = m_PolyLine[0].y;
				rect.bottom = m_PolyLine[0].y + XVUI_ARROW_CX;
			}
			else
			{
				rect.left = m_PolyLine[0].x - XVUI_ARROW_CY;
				rect.right = m_PolyLine[0].x + XVUI_ARROW_CY;
				rect.top = m_PolyLine[0].y - XVUI_ARROW_CX;
				rect.bottom = m_PolyLine[0].y;
			}
		}

		return rect;
	}

	rect = GetHandleRect(nHandle);

	return rect;
}

int CVUI_PolyLine::GetHandleLineIndex(int nHandleID)
{
	int nLine = nHandleID/2;
	if(GetLineCount() <= nLine)
	{
		nLine = GetLineCount()-1;
	}

	return nLine;
}

int CVUI_PolyLine::GetHandlePointIndex(int nHandleID)
{
	int nPoint = -1;
	if(!IsMiddleHandle(nHandleID))
	{
		nPoint = nHandleID/2;
	}
	return nPoint;
}

HCURSOR CVUI_PolyLine::GetHandleCursor(int nHandle)
{
	ASSERT(this);

	LPCTSTR id;

	bool bMiddle = (nHandle%2 == 1);

	if(bMiddle)
	{
		int nLine = GetHandleLineIndex(nHandle);
		if(IsHorzLine(nLine))
		{
			id = IDC_SIZENS;
		}
		else
		{
			id = IDC_SIZEWE;
		}
	}
	else
	{
		id = IDC_SIZEALL;
		int nCount = GetHandleCount();
		if((nHandle == 0 || nHandle == nCount-1) && m_bDrawTrack == true) 
		{
			id = IDC_CROSS;
		}
	}

	return AfxGetApp()->LoadStandardCursor(id);

}

bool CVUI_PolyLine::IsHorzLine(int nIndx)
{
	bool bRet = (0 <= nIndx && nIndx < GetLineCount());

	ASSERT(bRet);
	if(!bRet)
		return bRet;

    bRet = (m_PolyLine[nIndx].y == m_PolyLine[nIndx+1].y || m_PolyLine[nIndx].x == m_PolyLine[nIndx+1].x);   
	ASSERT(bRet);
	if(!bRet)
		return bRet;

	bRet = (m_PolyLine[nIndx].y == m_PolyLine[nIndx+1].y);

	return bRet;
}

bool CVUI_PolyLine::IsWestEastLine(int nIndx)
{
	bool bRet = (0 <= nIndx && nIndx < GetLineCount());

	ASSERT(bRet);
	if(!bRet)
		return bRet;

	bRet = (m_PolyLine[nIndx+1].x < m_PolyLine[nIndx].x);

	return bRet;
}

bool CVUI_PolyLine::DisplayCursor(CPoint point)
{
	bool bRet = false;
	int nHandle = -1;
	HCURSOR hCursor = NULL;

	if(IsSelected())
	{
		bRet = HitHandleTest(point, nHandle);
		if(bRet)
		{

			hCursor = GetHandleCursor(nHandle);
			::SetCursor(hCursor);
			bRet = true;
			return bRet;
		}
	}
	if(HitBlock(point))
	{
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
		bRet = true;
		return bRet;
	}

	return bRet;

}

void CVUI_PolyLine::DrawTracker(CDC* pDC)
{
	if(!IsSelected())
		return;
	
	int nHandleCount = GetHandleCount();

	CBrush brush;
	if(!brush.CreateSolidBrush(XVUI_TRACKER_RGB))
		return;			

	CBrush* pOldB;
	pOldB = pDC->SelectObject(&brush);

	CPen penOne;
	penOne.CreatePen(PS_SOLID, 0, XVUI_BLOCK_LINERGB);

	CPen penLight;
	penLight.CreatePen(PS_SOLID, 0, XVUI_TRACKER_LIGHT);

	CPen penDark;
	penDark.CreatePen(PS_SOLID, 0, XVUI_TRACKER_DARK);

	CPen penGreen;
	penGreen.CreatePen(PS_DOT, 0, XVUI_TRACKER_RGB);
	CPen* pOldP;
	CRect rect;
	int nSzie = xvui_ztsize[XVUI_ZOOM_DEFAULT];
	if(0 <= m_nZoom && m_nZoom < XVUI_ZOOMS)
		nSzie = xvui_ztsize[m_nZoom];

	int nMode = pDC->SetROP2(R2_COPYPEN);
	CPoint pPts[4];

	for (int nHandle = 0; nHandle < nHandleCount; nHandle++)
	{
		pOldP = pDC->SelectObject(&penGreen);
		CPoint handle = GetHandle(nHandle);
		CPoint handle2 = GetHandle(nHandle%(nHandleCount-1)+1);
		
		if(nHandle != nHandleCount-1)
		{
			pDC->MoveTo(handle);
			pDC->LineTo(handle2);
		}
		pDC->SelectObject(pOldP);

		if(IsMiddleHandle(nHandle))
		{
			rect.left = handle.x - nSzie;
			rect.top = handle.y - nSzie;
			rect.right = handle.x + nSzie;
			rect.bottom = handle.y + nSzie;
			pOldP = pDC->SelectObject(&penLight);
			pDC->Rectangle(&rect);
			pDC->MoveTo(rect.left, rect.top);
			pDC->LineTo(rect.right, rect.bottom);
			pDC->MoveTo(rect.right, rect.top);
			pDC->LineTo(rect.left, rect.bottom);
		}
		else
		{
			if(nHandle != 0 && nHandle != nHandleCount-1)
			{
				pPts[0].x = handle.x - nSzie; 
				pPts[0].y = handle.y;
				pPts[1].x = handle.x;
				pPts[1].y = handle.y - nSzie; 
				pPts[2].x = handle.x + nSzie; 
				pPts[2].y = handle.y;
				pPts[3].x = handle.x;
				pPts[3].y = handle.y + nSzie; 
				pOldP = pDC->SelectObject(&penOne);
				pDC->Polygon(pPts, 4);
			}
			else
			{
				if(nHandle == 0)
				{
					rect.left = handle.x - nSzie;
					rect.top = handle.y - nSzie;
					rect.right = handle.x + nSzie;
					rect.bottom = handle.y + nSzie;
					pOldP = pDC->SelectObject(&penOne);
					pDC->Rectangle(&rect);
					pDC->SelectObject(pOldP);
					pOldP = pDC->SelectObject(&penDark);
					pDC->MoveTo(handle.x - nSzie, handle.y);
					pDC->LineTo(handle.x + nSzie, handle.y);
					pDC->MoveTo(handle.x, handle.y - nSzie);
					pDC->LineTo(handle.x, handle.y + nSzie);
				}
				else
				{
					rect.left = handle.x - nSzie;
					rect.top = handle.y - nSzie;
					rect.right = handle.x + nSzie;
					rect.bottom = handle.y + nSzie;
					pOldP = pDC->SelectObject(&penOne);
					pDC->Rectangle(&rect);
					pDC->SelectObject(pOldP);
					pOldP = pDC->SelectObject(&penDark);
					pDC->MoveTo(rect.left, rect.top);
					pDC->LineTo(rect.right, rect.bottom);
					pDC->MoveTo(rect.right, rect.top);
					pDC->LineTo(rect.left, rect.bottom);
				}
			}
		}

		pDC->SelectObject(pOldP);
	}
	pDC->SetROP2(nMode);
	pDC->SelectObject(pOldB);
}

void CVUI_PolyLine::DrawNormal(CDC* pDC)
{
	CBrush brush(m_clrPen);
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
	pDC->Polygon(pts, 3);
    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);
}

void CVUI_PolyLine::DrawShadow(CDC* pDC)
{
	return;
}

void CVUI_PolyLine::DrawSelected(CDC* pDC)
{
	CBrush brush(m_selBrush.lbColor);
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
	pDC->Polygon(pts, 3);
    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);

	if(m_bDrawTrack == true)
	{
		DrawGhost(pDC);
	}
}

void CVUI_PolyLine::DrawGhost(CDC* pDC)
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
    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);
	pDC->SetROP2(nMode);
}

void CVUI_PolyLine::DrawDebug(CDC* pDC)
{
	DrawNormal(pDC);
}

void CVUI_PolyLine::DrawLinkers(CDC* pDC)
{
	return;
}

bool CVUI_PolyLine::IsMiddleHandle(int nHandle)
{
	bool bRet = (nHandle%2 == 1);

	return bRet;
}

CRect CVUI_PolyLine::GetBoundaryExt(void)
{
	int nCount = GetPointCount();
	int nMinX, nMinY, nMaxX, nMaxY, i;

	nMinX = nMinY = nMaxX = nMaxY = 0;
	if(m_bDrawTrack == false)
	{
		for(i = 0; i < nCount; i++)
		{
			nMinX = min(m_PolyLine[i].x, nMinX);
			nMinY = min(m_PolyLine[i].y, nMinY);
			nMaxX = max(m_PolyLine[i].x, nMaxX);
			nMaxY = max(m_PolyLine[i].y, nMaxY);
		}
	}
	else
	{
		for(i = 0; i < (int)m_TrackLine.size(); i++)
		{
			nMinX = min(m_TrackLine[i].x, nMinX);
			nMinY = min(m_TrackLine[i].y, nMinY);
			nMaxX = max(m_TrackLine[i].x, nMaxX);
			nMaxY = max(m_TrackLine[i].y, nMaxY);
		}
	}

	CRect rect(nMinX, nMinY, nMaxX, nMaxY);

	int nSize = xvui_ztsize[XVUI_ZOOM_DEFAULT];
	if(0 <= m_nZoom && m_nZoom < XVUI_ZOOMS)
		nSize = xvui_ztsize[m_nZoom];

	nSize += 1;

	nSize = max(nSize, XVUI_ARROW_CX);
	nSize *= 2;

	rect.InflateRect(nSize, nSize);	

	return rect;
}

void CVUI_PolyLine::MoveCenter(CPoint ptOff)
{
	if(m_bDrawTrack == false)
	{
		int nX, nY;

		nX = ptOff.x;
		nY = ptOff.y;

		int nCount = GetPointCount();
		int i;

		for(i = 0; i < nCount; i++)
		{
			if((m_PolyLine[i].x+nX) <= 0)
			{
				nX = -m_PolyLine[i].x;
			}
			else if(XVUI_GRIDSIZE <=(m_PolyLine[i].x+nX))
			{
				nX = XVUI_GRIDSIZE-m_PolyLine[i].x;
			}

			if((m_PolyLine[i].y+nY) <= 0)
			{
				nY = -m_PolyLine[i].y;
			}
			else if(XVUI_GRIDSIZE <=(m_PolyLine[i].y+nY))
			{
				nY = XVUI_GRIDSIZE-m_PolyLine[i].y;
			}
		}

		for(i = 0; i < nCount; i++)
		{
			//m_PolyLine[i].CleanList();
			m_PolyLine[i].Offset(nX, nY);
		}
	}
	else
	{
		MoveGhostCenter(ptOff);
	}
}

bool CVUI_PolyLine::OnLMouseBtnDblClick(CPoint point, int& nID)
{
	m_bDrawTrack = false;
	m_ptRealTrack = point;
	return CVUI_GraphBase::OnLMouseBtnDblClick(point, nID);
}

bool CVUI_PolyLine::OnLMouseBtnDown(CPoint point)
{
	m_ptRealTrack = point;
	int nCount = GetPointCount();
	m_TrackLine.clear();
	for(int i = 0; i < nCount; i++)
	{
		m_TrackLine.push_back((CPoint)m_PolyLine[i]);
	}

	int nHandle = 0;
	if(HitHeadTailTest(point, nHandle))	
	{
		m_bMoveHeadTail = true;
		m_hOldCursor = ::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
	}
	else
	{
		m_bMoveHeadTail = false;
	}


	return CVUI_GraphBase::OnLMouseBtnDown(point);
}

bool CVUI_PolyLine::OnMouseMove(CPoint point)
{
	m_bDrawTrack = true;
	return CVUI_GraphBase::OnMouseMove(point);
}

bool CVUI_PolyLine::OnLMouseBtnUp(CPoint point)
{
	bool bRet = true;
	m_bDrawTrack = false;
	m_ptLastHit = m_ptRealTrack;
	
	if(m_bMoveHeadTail == true)
	{
		m_hOldCursor = ::SetCursor(m_hOldCursor);
		m_bMoveHeadTail = false;
	}

	if(m_nMouseState == enMOUSE_LMOVE)
	{
		CRect rect1;
		CRect rect2;
		CRect rect;
		CPoint ptOff;
		rect1 = GetBoundaryExt();
		ptOff = point - m_ptLastHit;
		m_ptLastHit = point;
		if(m_nMouseDrag == -1)
		{
			MoveCenter(ptOff);
		}
		else
		{
			ChangeShape(ptOff);
		}
		AdjustPloyLine();
		rect2 = GetBoundaryExt();
		rect = CVUI_MaxRect::GetBoundary(rect1, rect2);
		bRet = true;
		if(m_Manager)
			m_Manager->InvalidateRect(&rect);
	}

	m_nMouseDrag = -1;
	m_nMouseState = enMOUSE_NONE;
	return bRet;
}

bool CVUI_PolyLine::AdjustPloyLine(void)
{
	bool bRet = true;
	bool bRet1 = true;
	bool bRet2 = true;
	bool bRet3 = true;

	bRet1 = StraightLine();
	bRet2 = RemoveOverlay();
	bRet2 = UpdateIntersection();

	bRet = (bRet1 && bRet2 && bRet3);
	return bRet;
}

bool CVUI_PolyLine::RemoveOverlay(void)
{
	bool bRet = true;

	int i1, i2, i3;
	for(i1 = 0; i1 < GetPointCount();)
	{
		i2 = i1+1;
		if(GetPointCount()-1 <= i2)
			break;
		i3 = i2+1;
		if(GetPointCount()-1 < i3)
			break;

		if((m_PolyLine[i1].x == m_PolyLine[i2].x && m_PolyLine[i2].x == m_PolyLine[i3].x)||
		   (m_PolyLine[i1].y == m_PolyLine[i2].y && m_PolyLine[i2].y == m_PolyLine[i3].y))
		{
			CVUI_LPointArray::iterator iter = m_PolyLine.begin() + (CVUI_LPointArray ::difference_type)i2;
			if(iter != m_PolyLine.end())
			{
				m_PolyLine.erase(iter);
				i1 = i1;
				continue;
			}
			else
			{
				i1++;
			}
		}
		else
		{
			i1++;
		}
	}

	return bRet;
}

bool CVUI_PolyLine::UpdateIntersection(void)
{
	bool bRet = true;

	if(m_Manager == NULL)
		return bRet;

	m_Manager->ResetPolyLinePoints();

	return bRet;
}

bool CVUI_PolyLine::StraightLine(void)
{
	bool bRet = true;
	bool bHorz;
	int nX, nY;

    //Check first line 
    if(m_PolyLine[0].x != m_PolyLine[1].x && m_PolyLine[0].y != m_PolyLine[1].y) //A declining line
	{
		bHorz = (abs(m_PolyLine[0].y-m_PolyLine[1].y) <= abs(m_PolyLine[0].x-m_PolyLine[1].x));
		if(bHorz)
		{
			nX = m_PolyLine[1].x; 
			nY = m_PolyLine[0].y;
		}
		else
		{
			nX = m_PolyLine[0].x; 
			nY = m_PolyLine[1].y;
		}
		m_PolyLine.insert(m_PolyLine.begin()+1, CVUI_LinkPoint(nX, nY));
	}

	//Check the rest of lines
    for(int i = 1; i < GetLineCount(); i++)
	{
		if(m_PolyLine[i].x != m_PolyLine[i+1].x && m_PolyLine[i].y != m_PolyLine[i+1].y)
		{
			if(IsHorzLine(i-1))
			{
				m_PolyLine[i].x = m_PolyLine[i+1].x;
			}
			else
			{
				m_PolyLine[i].y = m_PolyLine[i+1].y;
			}
		}
	}

	return bRet;
}

bool CVUI_PolyLine::IsHeadMovable(void)
{
	bool bRet = true;

	return bRet;
}

bool CVUI_PolyLine::IsTailMovable(void)
{
	bool bRet = true;

	return bRet;
}

void CVUI_PolyLine::ChangeShape(CPoint ptOff)
{
	int nCount = GetPointCount();
//	int i;
/*
	for(i = 0; i < nCount; i++)
	{
		m_PolyLine[i].CleanList();
	}
*/
	if(m_nMouseDrag == 0)
	{
		if(m_bDrawTrack == false)
			MoveHead(ptOff);
		else
			MoveGhostHead(ptOff);
	}
	else if(m_nMouseDrag == GetHandleCount()-1)
	{
		if(m_bDrawTrack == false)
			MoveTail(ptOff);
		else
			MoveGhostTail(ptOff);
	}
	else
	{
		if(m_bDrawTrack == false)
			MoveActiveHandle(ptOff);
		else
			MoveGhostActiveHandle(ptOff);
	}
}

void CVUI_PolyLine::MoveHead(CPoint ptOff)
{
	int nX, nY;

	nX = ptOff.x;
	nY = ptOff.y;

    if((m_PolyLine[0].x+nX) <= 0)
	{
		nX = -m_PolyLine[0].x;
	}
	else if(XVUI_GRIDSIZE <=(m_PolyLine[0].x+nX))
	{
		nX = XVUI_GRIDSIZE-m_PolyLine[0].x;
	}

	if((m_PolyLine[0].y+nY) <= 0)
	{
		nY = -m_PolyLine[0].y;
	}
	else if(XVUI_GRIDSIZE <=(m_PolyLine[0].y+nY))
	{
		nY = XVUI_GRIDSIZE-m_PolyLine[0].y;
	}

	if(GetLineCount() <= 1)
	{
		if(IsTailMovable())
		{
			if(IsHorzLine(0))
			{
				m_PolyLine[0].Offset(nX, nY);
				m_PolyLine[1].Offset(0, nY);
			}
			else
			{
				m_PolyLine[0].Offset(nX, nY);
				m_PolyLine[1].Offset(nX, 0);
			}
		}
		else
		{
			HeadOffset(nX, nY);
		}
	}
	else
	{
		if(IsHorzLine(0))
		{
			m_PolyLine[0].Offset(nX, nY);
			m_PolyLine[1].Offset(0, nY);
		}
		else
		{
			m_PolyLine[0].Offset(nX, nY);
			m_PolyLine[1].Offset(nX, 0);
		}
	}
}

void CVUI_PolyLine::MoveTail(CPoint ptOff)
{
	int nX, nY;

	nX = ptOff.x;
	nY = ptOff.y;

	int i = GetPointCount()-1;
	int iLine = GetLineCount()-1;

    if((m_PolyLine[i].x+nX) <= 0)
	{
		nX = -m_PolyLine[i].x;
	}
	else if(XVUI_GRIDSIZE <=(m_PolyLine[i].x+nX))
	{
		nX = XVUI_GRIDSIZE-m_PolyLine[i].x;
	}

	if((m_PolyLine[i].y+nY) <= 0)
	{
		nY = -m_PolyLine[i].y;
	}
	else if(XVUI_GRIDSIZE <=(m_PolyLine[i].y+nY))
	{
		nY = XVUI_GRIDSIZE-m_PolyLine[i].y;
	}

	if(GetLineCount() <= 1)
	{
		if(IsHeadMovable())
		{
			if(IsHorzLine(0))
			{
				m_PolyLine[1].Offset(nX, nY);
				m_PolyLine[0].Offset(0, nY);
			}
			else
			{
				m_PolyLine[1].Offset(nX, nY);
				m_PolyLine[0].Offset(nX, 0);
			}
		}
		else
		{
			TailOffset(nX, nY);
		}
	}
	else
	{
		if(IsHorzLine(iLine))
		{
			m_PolyLine[i].Offset(nX, nY);
			m_PolyLine[i-1].Offset(0, nY);
		}
		else
		{
			m_PolyLine[i].Offset(nX, nY);
			m_PolyLine[i-1].Offset(nX, 0);
		}
	}
}

void CVUI_PolyLine::MoveActiveHandle(CPoint ptOff)
{
	int nX, nY;

	nX = ptOff.x;
	nY = ptOff.y;

	bool bHorz1, bHorz2;

	int nPoint = GetHandlePointIndex(m_nMouseDrag);
	int nLine = GetHandleLineIndex(m_nMouseDrag);
	if(IsMiddleHandle(m_nMouseDrag))
	{
		if(IsHorzLine(nLine))
		{
			if((m_PolyLine[nLine].y+nY) <= 0)
			{
				nY = -m_PolyLine[nLine].y;
			}
			else if(XVUI_GRIDSIZE <=(m_PolyLine[nLine].y+nY))
			{
				nY = XVUI_GRIDSIZE-m_PolyLine[nLine].y;
			}
			if((m_PolyLine[nLine+1].y+nY) <= 0)
			{
				nY = -m_PolyLine[nLine+1].y;
			}
			else if(XVUI_GRIDSIZE <=(m_PolyLine[nLine+1].y+nY))
			{
				nY = XVUI_GRIDSIZE-m_PolyLine[nLine+1].y;
			}

			m_PolyLine[nLine].Offset(0, nY);
			m_PolyLine[nLine+1].Offset(0, nY);
		}
		else
		{
			if((m_PolyLine[nLine].x+nX) <= 0)
			{
				nX = -m_PolyLine[nLine].x;
			}
			else if(XVUI_GRIDSIZE <=(m_PolyLine[nLine].x+nX))
			{
				nX = XVUI_GRIDSIZE-m_PolyLine[nLine].x;
			}
			if((m_PolyLine[nLine+1].x+nX) <= 0)
			{
				nX = -m_PolyLine[nLine+1].x;
			}
			else if(XVUI_GRIDSIZE <=(m_PolyLine[nLine+1].x+nX))
			{
				nX = XVUI_GRIDSIZE-m_PolyLine[nLine+1].x;
			}
			m_PolyLine[nLine].Offset(nX, 0);
			m_PolyLine[nLine+1].Offset(nX, 0);
		}
	}
	else
	{
		if((m_PolyLine[nPoint].x+nX) <= 0)
		{
			nX = -m_PolyLine[nPoint].x;
		}
		else if(XVUI_GRIDSIZE <=(m_PolyLine[nPoint].x+nX))
		{
			nX = XVUI_GRIDSIZE-m_PolyLine[nPoint].x;
		}
		if((m_PolyLine[nPoint].y+nY) <= 0)
		{
			nY = -m_PolyLine[nPoint].y;
		}
		else if(XVUI_GRIDSIZE <=(m_PolyLine[nPoint].y+nY))
		{
			nY = XVUI_GRIDSIZE-m_PolyLine[nPoint].y;
		}
		bHorz1 = IsHorzLine(nPoint-1); //Previous line 
		bHorz2 = IsHorzLine(nPoint); //Next line
		m_PolyLine[nPoint].Offset(nX, nY);
		if(bHorz1) //Previous line 
		{
			m_PolyLine[nPoint-1].Offset(0, nY);
		}
		else
		{
			m_PolyLine[nPoint-1].Offset(nX, 0);
		}
		if(bHorz2) //Next line 
		{
			m_PolyLine[nPoint+1].Offset(0, nY);
		}
		else
		{
			m_PolyLine[nPoint+1].Offset(nX, 0);
		}
	}
}

void CVUI_PolyLine::MoveGhostCenter(CPoint ptOff)
{
	int nX, nY;
	nX = ptOff.x;
	nY = ptOff.y;

	int nCount = (int)m_TrackLine.size();
	int i;

	for(i = 0; i < nCount; i++)
	{
		if((m_TrackLine[i].x+nX) <= 0)
		{
			nX = -m_TrackLine[i].x;
		}
		else if(XVUI_GRIDSIZE <=(m_TrackLine[i].x+nX))
		{
			nX = XVUI_GRIDSIZE-m_TrackLine[i].x;
		}

		if((m_TrackLine[i].y+nY) <= 0)
		{
			nY = -m_TrackLine[i].y;
		}
		else if(XVUI_GRIDSIZE <=(m_TrackLine[i].y+nY))
		{
			nY = XVUI_GRIDSIZE-m_TrackLine[i].y;
		}
	}

	for(i = 0; i < nCount; i++)
	{
		m_TrackLine[i].Offset(nX, nY);
	}
}

void CVUI_PolyLine::MoveGhostHead(CPoint ptOff)
{
	int nX, nY;

	nX = ptOff.x;
	nY = ptOff.y;

    if((m_TrackLine[0].x+nX) <= 0)
	{
		nX = -m_TrackLine[0].x;
	}
	else if(XVUI_GRIDSIZE <=(m_TrackLine[0].x+nX))
	{
		nX = XVUI_GRIDSIZE-m_TrackLine[0].x;
	}

	if((m_TrackLine[0].y+nY) <= 0)
	{
		nY = -m_TrackLine[0].y;
	}
	else if(XVUI_GRIDSIZE <=(m_TrackLine[0].y+nY))
	{
		nY = XVUI_GRIDSIZE-m_TrackLine[0].y;
	}

	if(m_TrackLine.size() <= 2)
	{
		if(IsTailMovable())
		{
			if(m_TrackLine[0].y == m_TrackLine[1].y)
			{
				m_TrackLine[0].Offset(nX, nY);
				m_TrackLine[1].Offset(0, nY);
			}
			else
			{
				m_TrackLine[0].Offset(nX, nY);
				m_TrackLine[1].Offset(nX, 0);
			}
		}
		else
		{
		}
	}
	else
	{
		if(m_TrackLine[0].y == m_TrackLine[1].y)
		{
			m_TrackLine[0].Offset(nX, nY);
			m_TrackLine[1].Offset(0, nY);
		}
		else
		{
			m_TrackLine[0].Offset(nX, nY);
			m_TrackLine[1].Offset(nX, 0);
		}
	}
}

void CVUI_PolyLine::MoveGhostTail(CPoint ptOff)
{
	int nX, nY;

	nX = ptOff.x;
	nY = ptOff.y;

	int i = (int)m_TrackLine.size()-1;
	int iLine = (int)m_TrackLine.size()-2;

    if((m_TrackLine[i].x+nX) <= 0)
	{
		nX = -m_TrackLine[i].x;
	}
	else if(XVUI_GRIDSIZE <=(m_TrackLine[i].x+nX))
	{
		nX = XVUI_GRIDSIZE-m_TrackLine[i].x;
	}

	if((m_TrackLine[i].y+nY) <= 0)
	{
		nY = -m_TrackLine[i].y;
	}
	else if(XVUI_GRIDSIZE <=(m_TrackLine[i].y+nY))
	{
		nY = XVUI_GRIDSIZE-m_TrackLine[i].y;
	}

	if((int)m_TrackLine.size() <= 2)
	{
		if(IsHeadMovable())
		{
			if(m_TrackLine[1].y == m_TrackLine[0].y)
			{
				m_TrackLine[1].Offset(nX, nY);
				m_TrackLine[0].Offset(0, nY);
			}
			else
			{
				m_TrackLine[1].Offset(nX, nY);
				m_TrackLine[0].Offset(nX, 0);
			}
		}
		else
		{
		}
	}
	else
	{
		if(m_TrackLine[i].y == m_TrackLine[i-1].y)
		{
			m_TrackLine[i].Offset(nX, nY);
			m_TrackLine[i-1].Offset(0, nY);
		}
		else
		{
			m_TrackLine[i].Offset(nX, nY);
			m_TrackLine[i-1].Offset(nX, 0);
		}
	}
}

void CVUI_PolyLine::MoveGhostActiveHandle(CPoint ptOff)
{
	int nX, nY;

	nX = ptOff.x;
	nY = ptOff.y;

	bool bHorz1, bHorz2;

	int nPoint = GetHandlePointIndex(m_nMouseDrag);
	int nLine = GetHandleLineIndex(m_nMouseDrag);
	if(IsMiddleHandle(m_nMouseDrag))
	{
		if(IsHorzLine(nLine))
		{
			if((m_TrackLine[nLine].y+nY) <= 0)
			{
				nY = -m_TrackLine[nLine].y;
			}
			else if(XVUI_GRIDSIZE <=(m_TrackLine[nLine].y+nY))
			{
				nY = XVUI_GRIDSIZE-m_TrackLine[nLine].y;
			}
			if((m_TrackLine[nLine+1].y+nY) <= 0)
			{
				nY = -m_TrackLine[nLine+1].y;
			}
			else if(XVUI_GRIDSIZE <=(m_TrackLine[nLine+1].y+nY))
			{
				nY = XVUI_GRIDSIZE-m_TrackLine[nLine+1].y;
			}

			m_TrackLine[nLine].Offset(0, nY);
			m_TrackLine[nLine+1].Offset(0, nY);
		}
		else
		{
			if((m_TrackLine[nLine].x+nX) <= 0)
			{
				nX = -m_TrackLine[nLine].x;
			}
			else if(XVUI_GRIDSIZE <=(m_TrackLine[nLine].x+nX))
			{
				nX = XVUI_GRIDSIZE-m_TrackLine[nLine].x;
			}
			if((m_TrackLine[nLine+1].x+nX) <= 0)
			{
				nX = -m_TrackLine[nLine+1].x;
			}
			else if(XVUI_GRIDSIZE <=(m_TrackLine[nLine+1].x+nX))
			{
				nX = XVUI_GRIDSIZE-m_TrackLine[nLine+1].x;
			}
			m_TrackLine[nLine].Offset(nX, 0);
			m_TrackLine[nLine+1].Offset(nX, 0);
		}
	}
	else
	{
		if((m_TrackLine[nPoint].x+nX) <= 0)
		{
			nX = -m_TrackLine[nPoint].x;
		}
		else if(XVUI_GRIDSIZE <=(m_TrackLine[nPoint].x+nX))
		{
			nX = XVUI_GRIDSIZE-m_TrackLine[nPoint].x;
		}
		if((m_TrackLine[nPoint].y+nY) <= 0)
		{
			nY = -m_TrackLine[nPoint].y;
		}
		else if(XVUI_GRIDSIZE <=(m_TrackLine[nPoint].y+nY))
		{
			nY = XVUI_GRIDSIZE-m_TrackLine[nPoint].y;
		}
		bHorz1 = IsHorzLine(nPoint-1); //Previous line 
		bHorz2 = IsHorzLine(nPoint); //Next line
		m_TrackLine[nPoint].Offset(nX, nY);
		if(bHorz1) //Previous line 
		{
			m_TrackLine[nPoint-1].Offset(0, nY);
		}
		else
		{
			m_TrackLine[nPoint-1].Offset(nX, 0);
		}
		if(bHorz2) //Next line 
		{
			m_TrackLine[nPoint+1].Offset(0, nY);
		}
		else
		{
			m_TrackLine[nPoint+1].Offset(nX, 0);
		}
	}
}

void CVUI_PolyLine::AdjustIntersects(void)
{
	int nCount = GetLineCount();
	for(int i = 0; i < nCount; i++)
	{
		if(IsHorzLine(i))
		{
			if(m_PolyLine[i].HasPoint())
			{
				if(IsWestEastLine(i))
				{
					m_PolyLine[i].SortPoint(false);
				}
				else
				{
					m_PolyLine[i].SortPoint(true);
				}
			}
		}
	}
}

void CVUI_PolyLine::ClearIntersects(void)
{
	int nCount = GetLineCount();
	for(int i = 0; i < nCount; i++)
	{
		m_PolyLine[i].CleanList();
	}
}

void CVUI_PolyLine::DrawLineSegment(CDC* pDC, CVUI_LinkPoint& pt1, CVUI_LinkPoint& pt2)
{
	if(pDC == NULL || pt1.y != pt2.y)
		return;

	if(!pt1.HasPoint() || abs(pt1.x - pt2.x) <= XVUI_ARC_CX*2)
	{
		pDC->LineTo(pt2.x, pt2.y);
		return;
	}

	std::vector<CSize>  arcList; //cx: center, cy: radius

	int i, nx, nLen;
	int nCount = pt1.GetPointCount();
    
	for(i = 0; i < nCount; i++)
	{
		nx = pt1.GetPoint(i);
		arcList.push_back(CSize(nx, XVUI_ARC_CX));
	}

	//First arc
	if(abs(arcList[0].cx - pt1.x) < XVUI_ARC_CX)
	{
		arcList[0].cy = abs(arcList[0].cx - pt1.x);
	}
	if(abs(arcList[(int)arcList.size()-1].cx - pt2.x) < XVUI_ARC_CX)
	{
		arcList[(int)arcList.size()-1].cy = abs(arcList[(int)arcList.size()-1].cx - pt2.x);
	}


	int i1, i2;
	for(i1 = 0; i1 < (int)arcList.size();)
	{
		i2 = i1+1;
		if((int)arcList.size()-1 < i2)
			break;

		if(arcList[i1].cy + arcList[i2].cy <= abs(arcList[i1].cx - arcList[i2].cx))
		{
			i1++;
			continue;
		}
		else
		{
			nLen = (arcList[i1].cy + arcList[i2].cy + abs(arcList[i1].cx - arcList[i2].cx))/2;
			nx = (arcList[i1].cx + arcList[i2].cx)/2;
			arcList[i1].cx = nx;
			arcList[i1].cy = nLen;
			std::vector<CSize>::iterator iter = arcList.begin() + (std::vector<CSize>::difference_type)i2;
			if(iter != arcList.end())
			{
				arcList.erase(iter);
				continue;
			}
		}
	}

	CPoint ptFrist = (CPoint)pt1;
	CPoint ptLast = (CPoint)pt2;
	CPoint ptCur = ptFrist;
	CPoint ptNext = ptFrist;
	CPoint ptStart = ptFrist;
	CPoint ptEnd = ptFrist;
	CRect rect;
    
	bool bAscend = pt1.x < pt2.x;
    
	if(bAscend)
	{
		ptNext.x = arcList[0].cx - arcList[0].cy;
	}
	else
	{
		ptNext.x = arcList[0].cx + arcList[0].cy;
	}

	for(i = 0; i < (int)arcList.size(); i++)
	{
		//pDC->MoveTo(ptCur);
		pDC->LineTo(ptNext);

/*
		rect.left = arcList[i].cx - arcList[i].cy;
		rect.right = arcList[i].cx + arcList[i].cy;
		rect.top = pt1.y - XVUI_ARC_CY;
		rect.bottom = pt1.y + XVUI_ARC_CY;
		ptStart.x = rect.right;
		//ptStart.y = pt1.y;
		ptEnd.x = rect.left;
		//ptEnd.y = pt1.y;
		pDC->Arc(&rect, ptStart, ptEnd);
*/
		if(bAscend)
		{
			pDC->LineTo(arcList[i].cx - arcList[i].cy, pt1.y);
			pDC->LineTo(arcList[i].cx - arcList[i].cy, pt1.y - XVUI_ARC_CY);
			pDC->LineTo(arcList[i].cx + arcList[i].cy, pt1.y - XVUI_ARC_CY);
			pDC->LineTo(arcList[i].cx + arcList[i].cy, pt1.y);

			//ptCur.x = arcList[i].cx + arcList[i].cy;
			if(i < (int)arcList.size()-1)
			{
				ptNext.x = arcList[i+1].cx - arcList[i+1].cy;
			}
			else
			{
				ptNext.x = ptLast.x;
			}
		}
		else
		{
			pDC->LineTo(arcList[i].cx + arcList[i].cy, pt1.y);
			pDC->LineTo(arcList[i].cx + arcList[i].cy, pt1.y - XVUI_ARC_CY);
			pDC->LineTo(arcList[i].cx - arcList[i].cy, pt1.y - XVUI_ARC_CY);
			pDC->LineTo(arcList[i].cx - arcList[i].cy, pt1.y);

			//ptCur.x = arcList[i].cx - arcList[i].cy;
			if(i < (int)arcList.size()-1)
			{
				ptNext.x = arcList[i+1].cx + arcList[i+1].cy;
			}
			else
			{
				ptNext.x = ptLast.x;
			}
		}
	}

	//pDC->MoveTo(ptCur);
	pDC->LineTo(ptNext);
}

bool CVUI_PolyLine::ResetIntersects(void)
{
	bool bRet = true;
	
	if(m_Manager == NULL)
		return bRet;

	CVUI_GraphMap::iterator iter;
	CVUI_PolyLine* pPLine;
	int nLines = GetLineCount();
	int nLines2;
	int i, j;
	CPoint ptV1, ptV2;
	CPoint ptH1, ptH2;

	for(i = 0; i < nLines; i++)
	{
		if(!IsHorzLine(i))
		{
			ptV1 = (CPoint)m_PolyLine[i]; 
			ptV2 = (CPoint)m_PolyLine[i+1]; 
			for(iter = m_Manager->m_GraphMap.begin(); iter != m_Manager->m_GraphMap.end(); ++iter)
			{
				if(XVSM_PU_LINK_FIRST < iter->first)
					break;

				pPLine = (CVUI_PolyLine*)iter->second;
				if(pPLine == NULL)
					continue;

				nLines2 = pPLine->GetLineCount();
				for(j = 0; j < nLines2; j++)
				{
					if(pPLine->IsHorzLine(j))
					{
						ptH1 = (CPoint)pPLine->m_PolyLine[j];  
						ptH2 = (CPoint)pPLine->m_PolyLine[j+1];  
						if(CVUI_PLIntersect::IsIntersect(ptV1, ptV2, ptH1, ptH2))
						{
							pPLine->m_PolyLine[j].AddPoint(ptV1.x);
						}
					}
				}
			}
		}
	}

	return bRet;
}

bool CVUI_PolyLine::HeadOffset(CPoint ptOff)
{
	return HeadOffset(ptOff.x, ptOff.y);
}

bool CVUI_PolyLine::HeadOffset(int nX, int nY)
{
	bool bRet = true;

	bool bHorz = (m_PolyLine[0].y == m_PolyLine[1].y);
	
	m_PolyLine[0].Offset(nX, nY);
	
	if((int)m_PolyLine.size() == 2)
	{
		if(IsTailMovable())
		{
			m_PolyLine[1].Offset(nX, nY);
		}
		else
		{
			CPoint pt1, pt2;

			if(bHorz)
			{
				pt1.x = (m_PolyLine[0].x + m_PolyLine[1].x)/2;
				pt1.y = m_PolyLine[0].y;	
				pt2.x = pt1.x;
				pt2.y = m_PolyLine[1].y;	
			}
			else
			{
				pt1.x = m_PolyLine[0].x;
				pt1.y = (m_PolyLine[0].y+m_PolyLine[1].y)/2;	
				pt2.x = m_PolyLine[1].x;
				pt2.y = pt1.y;	
			}
			m_PolyLine.insert(m_PolyLine.begin()+1, pt1);
			m_PolyLine.insert(m_PolyLine.begin()+2, pt2);
		}
	}
	else
	{
		if(bHorz)
		{
			m_PolyLine[1].y = m_PolyLine[0].y;
		}
		else
		{
			m_PolyLine[1].x = m_PolyLine[0].x;
		}
	}

	return bRet;
}

bool CVUI_PolyLine::TailOffset(CPoint ptOff)
{
	return TailOffset(ptOff.x, ptOff.y);
}

bool CVUI_PolyLine::TailOffset(int nX, int nY)
{
	bool bRet = true;

	int nLast = (int)m_PolyLine.size() - 1;

	bool bHorz = (m_PolyLine[nLast].y == m_PolyLine[nLast-1].y);

	m_PolyLine[nLast].Offset(nX, nY);
	
	if((int)m_PolyLine.size() == 2)
	{
		if(IsHeadMovable())
		{
			m_PolyLine[0].Offset(nX, nY);
		}
		else
		{
			CPoint pt1, pt2;

			if(bHorz)
			{
				pt1.x = (m_PolyLine[0].x + m_PolyLine[1].x)/2;
				pt1.y = m_PolyLine[0].y;	
				pt2.x = pt1.x;
				pt2.y = m_PolyLine[1].y;	
			}
			else
			{
				pt1.x = m_PolyLine[0].x;
				pt1.y = (m_PolyLine[0].y+m_PolyLine[1].y)/2;	
				pt2.x = m_PolyLine[1].x;
				pt2.y = pt1.y;	
			}
			m_PolyLine.insert(m_PolyLine.begin()+1, pt1);
			m_PolyLine.insert(m_PolyLine.begin()+2, pt2);
		}
	}
	else
	{
		if(bHorz)
		{
			m_PolyLine[nLast-1].y = m_PolyLine[nLast].y;
		}
		else
		{
			m_PolyLine[nLast-1].x = m_PolyLine[nLast].x;
		}
	}

	return bRet;
}

int CVUI_PolyLine::GetHeadDir(void)
{
	int nDir = XVUI_DIR_NS;
	bool bHorz = (m_PolyLine[0].y == m_PolyLine[1].y);
	if(bHorz) //
	{
		if(m_PolyLine[0].x <= m_PolyLine[1].x) // <- direction
		{
			nDir = XVUI_DIR_EW;
		}
		else //-> direction
		{
			nDir = XVUI_DIR_WE;
		}
	}
	else
	{
		if(m_PolyLine[0].y <= m_PolyLine[1].y) // Upper
		{
			nDir = XVUI_DIR_SN;
		}
		else
		{
			nDir = XVUI_DIR_NS;
		}
	}
	return nDir;
}

int CVUI_PolyLine::GetTailDir(void)
{
	int nDir = XVUI_DIR_NS;
	int nLast = (int)m_PolyLine.size() -1;

	bool bHorz = (m_PolyLine[nLast-1].y == m_PolyLine[nLast].y);
	if(bHorz) //
	{
		if(m_PolyLine[nLast].x <= m_PolyLine[nLast-1].x) // <- direction
		{
			nDir = XVUI_DIR_EW;
		}
		else //-> direction
		{
			nDir = XVUI_DIR_WE;
		}
	}
	else
	{
		if(m_PolyLine[nLast].y <= m_PolyLine[nLast-1].y) // Upper
		{
			nDir = XVUI_DIR_SN;
		}
		else
		{
			nDir = XVUI_DIR_NS;
		}
	}
	return nDir;
}

void CVUI_PolyLine::RotateHead(int nDir)
{
	int nOffset = XVUI_ARROW_CX*2;
	if(XVUI_ARROW_ROTATE90 <= nDir && nDir <= XVUI_ARROW_ROTATE270)
	{
		CRect rect1;
		CRect rect2;
		CRect rect;

		int nAD = GetHeadDir();
		CVUI_LinkPoint pt1, pt2, pt3;
		rect1 = GetBoundaryExt();
		if(nAD == XVUI_DIR_NS) //0
		{
			if(XVUI_ARROW_ROTATE90 == nDir)
			{
				pt1.x = m_PolyLine[0].x - nOffset; 
				pt1.y = m_PolyLine[0].y; 
				pt2.x = pt1.x;
				pt2.y = m_PolyLine[1].y;
				m_PolyLine.insert(m_PolyLine.begin()+1, pt1);
				m_PolyLine.insert(m_PolyLine.begin()+2, pt2);
			}
			else if(XVUI_ARROW_ROTATE180 == nDir)
			{
				pt1.x = m_PolyLine[0].x;
				pt1.y = m_PolyLine[0].y + nOffset; 
				pt2.x = pt1.x - nOffset;
				pt2.y = pt1.y;
				pt3.x = pt2.x;
				pt3.y = m_PolyLine[1].y;
				m_PolyLine.insert(m_PolyLine.begin()+1, pt1);
				m_PolyLine.insert(m_PolyLine.begin()+2, pt2);
				m_PolyLine.insert(m_PolyLine.begin()+3, pt3);
			}
			else if(XVUI_ARROW_ROTATE270 == nDir)
			{
				pt1.x = m_PolyLine[0].x + nOffset; 
				pt1.y = m_PolyLine[0].y; 
				pt2.x = pt1.x;
				pt2.y = m_PolyLine[1].y;
				m_PolyLine.insert(m_PolyLine.begin()+1, pt1);
				m_PolyLine.insert(m_PolyLine.begin()+2, pt2);
			}
		}
		else if(nAD == XVUI_DIR_EW) // 1
		{
			if(XVUI_ARROW_ROTATE90 == nDir)
			{
				pt1.x = m_PolyLine[0].x;
				pt1.y = m_PolyLine[0].y - nOffset;  
				pt2.x = m_PolyLine[1].x;
				pt2.y = pt1.y;
				m_PolyLine.insert(m_PolyLine.begin()+1, pt1);
				m_PolyLine.insert(m_PolyLine.begin()+2, pt2);
			}
			else if(XVUI_ARROW_ROTATE180 == nDir)
			{
				pt1.x = m_PolyLine[0].x - nOffset;
				pt1.y = m_PolyLine[0].y; 
				pt2.x = pt1.x;
				pt2.y = pt1.y + nOffset;
				pt3.x = m_PolyLine[1].x;
				pt3.y = pt2.y;
				m_PolyLine.insert(m_PolyLine.begin()+1, pt1);
				m_PolyLine.insert(m_PolyLine.begin()+2, pt2);
				m_PolyLine.insert(m_PolyLine.begin()+3, pt3);
			}
			else if(XVUI_ARROW_ROTATE270 == nDir)
			{
				pt1.x = m_PolyLine[0].x;
				pt1.y = m_PolyLine[0].y + nOffset;  
				pt2.x = m_PolyLine[1].x;
				pt2.y = pt1.y;
				m_PolyLine.insert(m_PolyLine.begin()+1, pt1);
				m_PolyLine.insert(m_PolyLine.begin()+2, pt2);
			}
		}
		else if(nAD == XVUI_DIR_SN) // 2
		{
			if(XVUI_ARROW_ROTATE90 == nDir)
			{
				pt1.x = m_PolyLine[0].x + nOffset; 
				pt1.y = m_PolyLine[0].y; 
				pt2.x = pt1.x;
				pt2.y = m_PolyLine[1].y;
				m_PolyLine.insert(m_PolyLine.begin()+1, pt1);
				m_PolyLine.insert(m_PolyLine.begin()+2, pt2);
			}
			else if(XVUI_ARROW_ROTATE180 == nDir)
			{
				pt1.x = m_PolyLine[0].x;
				pt1.y = m_PolyLine[0].y - nOffset; 
				pt2.x = pt1.x + nOffset;
				pt2.y = pt1.y;
				pt3.x = pt2.x;
				pt3.y = m_PolyLine[1].y;
				m_PolyLine.insert(m_PolyLine.begin()+1, pt1);
				m_PolyLine.insert(m_PolyLine.begin()+2, pt2);
				m_PolyLine.insert(m_PolyLine.begin()+3, pt3);
			}
			else if(XVUI_ARROW_ROTATE270 == nDir)
			{
				pt1.x = m_PolyLine[0].x - nOffset; 
				pt1.y = m_PolyLine[0].y; 
				pt2.x = pt1.x;
				pt2.y = m_PolyLine[1].y;
				m_PolyLine.insert(m_PolyLine.begin()+1, pt1);
				m_PolyLine.insert(m_PolyLine.begin()+2, pt2);
			}
		}
		else if(nAD == XVUI_DIR_WE) // 3
		{
			if(XVUI_ARROW_ROTATE90 == nDir)
			{
				pt1.x = m_PolyLine[0].x;
				pt1.y = m_PolyLine[0].y + nOffset;  
				pt2.x = m_PolyLine[1].x;
				pt2.y = pt1.y;
				m_PolyLine.insert(m_PolyLine.begin()+1, pt1);
				m_PolyLine.insert(m_PolyLine.begin()+2, pt2);
			}
			else if(XVUI_ARROW_ROTATE180 == nDir)
			{
				pt1.x = m_PolyLine[0].x + nOffset;
				pt1.y = m_PolyLine[0].y; 
				pt2.x = pt1.x;
				pt2.y = pt1.y - nOffset;
				pt3.x = m_PolyLine[1].x;
				pt3.y = pt2.y;
				m_PolyLine.insert(m_PolyLine.begin()+1, pt1);
				m_PolyLine.insert(m_PolyLine.begin()+2, pt2);
				m_PolyLine.insert(m_PolyLine.begin()+3, pt3);
			}
			else if(XVUI_ARROW_ROTATE270 == nDir)
			{
				pt1.x = m_PolyLine[0].x;
				pt1.y = m_PolyLine[0].y - nOffset;  
				pt2.x = m_PolyLine[1].x;
				pt2.y = pt1.y;
				m_PolyLine.insert(m_PolyLine.begin()+1, pt1);
				m_PolyLine.insert(m_PolyLine.begin()+2, pt2);
			}
		}
		AdjustPloyLine();
		rect2 = GetBoundaryExt();
		rect = CVUI_MaxRect::GetBoundary(rect1, rect2);
		if(m_Manager)
			m_Manager->InvalidateRect(&rect);
	}
}

void CVUI_PolyLine::RotateTail(int nDir)
{
	int nOffset = XVUI_ARROW_CX;
	if(XVUI_ARROW_ROTATE90 <= nDir && nDir <= XVUI_ARROW_ROTATE270)
	{
		CRect rect1;
		CRect rect2;
		CRect rect;
		int nAD = GetTailDir();
		CVUI_LinkPoint pt1, pt2;
		rect1 = GetBoundaryExt();
		int nLast = (int)m_PolyLine.size() -1;

 		if(nAD == XVUI_DIR_NS) //0
		{
			if(XVUI_ARROW_ROTATE90 == nDir)
			{
				if(IsTailMovable())
				{
					pt1.x = m_PolyLine[nLast].x + nOffset; 
					pt1.y = m_PolyLine[nLast].y; 
					m_PolyLine.push_back(pt1);
				}
				else
				{
					pt1.x = m_PolyLine[nLast].x - nOffset; 
					pt1.y = m_PolyLine[nLast].y; 
					pt2.x = pt1.x;
					pt2.y = m_PolyLine[nLast-1].y;
					m_PolyLine.insert(m_PolyLine.begin()+nLast, pt1);
					m_PolyLine.insert(m_PolyLine.begin()+nLast+1, pt2);
				}
			}
			else if(XVUI_ARROW_ROTATE270 == nDir)
			{
				if(IsTailMovable())
				{
					pt1.x = m_PolyLine[nLast].x - nOffset; 
					pt1.y = m_PolyLine[nLast].y; 
					m_PolyLine.push_back(pt1);
				}
				else
				{
					pt1.x = m_PolyLine[nLast].x + nOffset; 
					pt1.y = m_PolyLine[nLast].y; 
					pt2.x = pt1.x;
					pt2.y = m_PolyLine[nLast-1].y;
					m_PolyLine.insert(m_PolyLine.begin()+nLast, pt1);
					m_PolyLine.insert(m_PolyLine.begin()+nLast+1, pt2);
				}
			}
		}
		else if(nAD == XVUI_DIR_EW) // 1
		{
			if(XVUI_ARROW_ROTATE90 == nDir)
			{
				if(IsTailMovable())
				{
					pt1.x = m_PolyLine[nLast].x; 
					pt1.y = m_PolyLine[nLast].y + nOffset;  
					m_PolyLine.push_back(pt1);
				}
				else
				{
					pt1.x = m_PolyLine[nLast].x; 
					pt1.y = m_PolyLine[nLast].y - nOffset; 
					pt2.x = m_PolyLine[nLast-1].x;
					pt2.y = pt1.y;
					m_PolyLine.insert(m_PolyLine.begin()+nLast, pt1);
					m_PolyLine.insert(m_PolyLine.begin()+nLast+1, pt2);
				}
			}
			else if(XVUI_ARROW_ROTATE270 == nDir)
			{
				if(IsTailMovable())
				{
					pt1.x = m_PolyLine[nLast].x; 
					pt1.y = m_PolyLine[nLast].y - nOffset;  
					m_PolyLine.push_back(pt1);
				}
				else
				{
					pt1.x = m_PolyLine[nLast].x; 
					pt1.y = m_PolyLine[nLast].y + nOffset; 
					pt2.x = m_PolyLine[nLast-1].x;
					pt2.y = pt1.y;
					m_PolyLine.insert(m_PolyLine.begin()+nLast, pt1);
					m_PolyLine.insert(m_PolyLine.begin()+nLast+1, pt2);
				}
			}
		}
		else if(nAD == XVUI_DIR_SN) // 2
		{
			if(XVUI_ARROW_ROTATE90 == nDir)
			{
				if(IsTailMovable())
				{
					pt1.x = m_PolyLine[nLast].x - nOffset; 
					pt1.y = m_PolyLine[nLast].y; 
					m_PolyLine.push_back(pt1);
				}
				else
				{
					pt1.x = m_PolyLine[nLast].x + nOffset; 
					pt1.y = m_PolyLine[nLast].y; 
					pt2.x = pt1.x;
					pt2.y = m_PolyLine[nLast-1].y;
					m_PolyLine.insert(m_PolyLine.begin()+nLast, pt1);
					m_PolyLine.insert(m_PolyLine.begin()+nLast+1, pt2);
				}
			}
			else if(XVUI_ARROW_ROTATE270 == nDir)
			{
				if(IsTailMovable())
				{
					pt1.x = m_PolyLine[nLast].x + nOffset; 
					pt1.y = m_PolyLine[nLast].y; 
					m_PolyLine.push_back(pt1);
				}
				else
				{
					pt1.x = m_PolyLine[nLast].x - nOffset; 
					pt1.y = m_PolyLine[nLast].y; 
					pt2.x = pt1.x;
					pt2.y = m_PolyLine[nLast-1].y;
					m_PolyLine.insert(m_PolyLine.begin()+nLast, pt1);
					m_PolyLine.insert(m_PolyLine.begin()+nLast+1, pt2);
				}
			}
		}
		else if(nAD == XVUI_DIR_WE) // 3
		{
			if(XVUI_ARROW_ROTATE90 == nDir)
			{
				if(IsTailMovable())
				{
					pt1.x = m_PolyLine[nLast].x; 
					pt1.y = m_PolyLine[nLast].y - nOffset;  
					m_PolyLine.push_back(pt1);
				}
				else
				{
					pt1.x = m_PolyLine[nLast].x; 
					pt1.y = m_PolyLine[nLast].y + nOffset; 
					pt2.x = m_PolyLine[nLast-1].x;
					pt2.y = pt1.y;
					m_PolyLine.insert(m_PolyLine.begin()+nLast, pt1);
					m_PolyLine.insert(m_PolyLine.begin()+nLast+1, pt2);
				}
			}
			else if(XVUI_ARROW_ROTATE270 == nDir)
			{
				if(IsTailMovable())
				{
					pt1.x = m_PolyLine[nLast].x; 
					pt1.y = m_PolyLine[nLast].y + nOffset;  
					m_PolyLine.push_back(pt1);
				}
				else
				{
					pt1.x = m_PolyLine[nLast].x; 
					pt1.y = m_PolyLine[nLast].y - nOffset; 
					pt2.x = m_PolyLine[nLast-1].x;
					pt2.y = pt1.y;
					m_PolyLine.insert(m_PolyLine.begin()+nLast, pt1);
					m_PolyLine.insert(m_PolyLine.begin()+nLast+1, pt2);
				}
			}
		}
		AdjustPloyLine();
		rect2 = GetBoundaryExt();
		rect = CVUI_MaxRect::GetBoundary(rect1, rect2);
		if(m_Manager)
			m_Manager->InvalidateRect(&rect);
	}
}

