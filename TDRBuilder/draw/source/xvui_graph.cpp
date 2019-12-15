#include "stdafx.h"

#include "xvui_graphman.h"
#include "xvui_graph.h"
#include "xvui_uiutils.h"

CVUI_GraphBase::CVUI_GraphBase(int	nID, CVUI_GraphManager*	pManager)
{
	m_nID = nID;
	m_Manager = pManager;
	m_nMouseDrag = -1;
	m_nMouseState = enMOUSE_NONE;
	m_strName = _T("Base Graph");
	m_clrPen = XVUI_BLOCK_LINERGB;

	m_logBrush.lbStyle = BS_SOLID;
	m_logBrush.lbColor = XVUI_BLOCK_FILLRGB;
	m_logBrush.lbHatch = HS_HORIZONTAL;

	m_selBrush.lbStyle = BS_SOLID;
	m_selBrush.lbColor = XVUI_BLOCK_ACTIVERGB;
	m_selBrush.lbHatch = HS_CROSS;

	m_debugBrush.lbStyle = BS_SOLID;
	m_debugBrush.lbColor = XVUI_BLOCK_DEBUGRGB;
	m_debugBrush.lbHatch = HS_DIAGCROSS;


	m_ptCenter.x = XVUI_ENODE_CX;
	m_ptCenter.y = XVUI_ENODE_CY;
	m_ptLastHit = m_ptCenter;

	m_Radius.cx = XVUI_ENODE_CX;
	m_Radius.cy = XVUI_ENODE_CY;
	m_nZoom = XVUI_ZOOM_DEFAULT;
	m_nState = XGRAPH_NORMAL;
	m_bShadow = true;

	m_TextFont.CreateFont(XVUI_BLOCK_FONTSIZE, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, 
						  ANSI_CHARSET, OUT_DEFAULT_PRECIS, 
						  CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
						  DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	m_txtRect.left = 0;
	m_txtRect.top = 0;
	m_txtRect.right = 1;
	m_txtRect.bottom = 1;

	m_puType = enXVSB_PUNONE;
}

CVUI_GraphBase::~CVUI_GraphBase()
{
	m_Manager = NULL;
	m_TextFont.DeleteObject();
}

int CVUI_GraphBase::GetHandleCount(void)
{
	return XVUI_BLOCK_HANDLES;
}

CRect CVUI_GraphBase::GetBoundaryExt(void)
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

	int nW = max(m_txtRect.Width()/2+1, m_Radius.cx);
	int nH = max(m_txtRect.Height()/2+1, m_Radius.cy);

	nW += nSzie*2;
	nH += nSzie*2;

	CRect rect(m_ptCenter.x-nW, m_ptCenter.y-nH, 
		       m_ptCenter.x+nW+nSX, m_ptCenter.y+nH+nSY);
/*
	CRect rect(m_ptCenter.x-nW-nSzie*2, m_ptCenter.y-nH-nSzie*2, 
		       m_ptCenter.x+nW+nSzie*2+nSX, m_ptCenter.y+nH+nSzie*2+nSY);
*/

	return rect;
}

void CVUI_GraphBase::SetMan(CVUI_GraphManager*	pManager)
{
	m_Manager = pManager;
}

void CVUI_GraphBase::DeSelected(void)
{
	// Only remove the tacker grid from block
	if(m_nState == XGRAPH_SELECTED || m_nState == XGRAPH_ACTIVE)
	{
		m_nState = XGRAPH_ACTIVE; 
	}
}

void CVUI_GraphBase::SetSelected(void)
{
	m_nState = XGRAPH_SELECTED;
}

void CVUI_GraphBase::SetDebug(void)
{
	if(m_nState == XGRAPH_SELECTED || XGRAPH_ACTIVE)
	{
		m_nState = XGRAPH_ACTIVEDEBUG;
	}
	else
	{
		m_nState = XGRAPH_DEBUG;
	}
}

void CVUI_GraphBase::ResetDebug(void)
{
	if(m_nState == XGRAPH_ACTIVEDEBUG)
	{
		m_nState = XGRAPH_ACTIVE; 
	}
	else
	{
		m_nState = XGRAPH_NORMAL;
	}
}

void CVUI_GraphBase::CleanState(void)
{
	m_nState = XGRAPH_NORMAL;
}

bool CVUI_GraphBase::IsSelected(void)
{
	return (m_nState == XGRAPH_SELECTED);
}

bool CVUI_GraphBase::IsActive(void)
{
	return (m_nState == XGRAPH_ACTIVE || m_nState == XGRAPH_SELECTED);
}

bool CVUI_GraphBase::IsActiveOnly(void)
{
	return (m_nState == XGRAPH_ACTIVE);
}

bool CVUI_GraphBase::IsDebug(void)
{
	return (m_nState == XGRAPH_DEBUG || m_nState == XGRAPH_ACTIVEDEBUG);
}

bool CVUI_GraphBase::IsNormal(void)
{
	return (m_nState == XGRAPH_NORMAL);
}

CPoint CVUI_GraphBase::GetHandle(int nHandle)
{
	CPoint pt(0, 0);
	switch(nHandle)
	{
		case 0:
			pt.x = m_ptCenter.x - m_Radius.cx;
			pt.y = m_ptCenter.y;
			break;
		case 1:
			pt.x = m_ptCenter.x - m_Radius.cx;
			pt.y = m_ptCenter.y - m_Radius.cy;
			break;
		case 2:
			pt.x = m_ptCenter.x;
			pt.y = m_ptCenter.y - m_Radius.cy;
			break;
		case 3:
			pt.x = m_ptCenter.x + m_Radius.cx;
			pt.y = m_ptCenter.y - m_Radius.cy;
			break;
		case 4:
			pt.x = m_ptCenter.x + m_Radius.cx;
			pt.y = m_ptCenter.y;
			break;
		case 5:
			pt.x = m_ptCenter.x + m_Radius.cx;
			pt.y = m_ptCenter.y + m_Radius.cy;
			break;
		case 6:
			pt.x = m_ptCenter.x;
			pt.y = m_ptCenter.y + m_Radius.cy;
			break;
		case 7:
			pt.x = m_ptCenter.x - m_Radius.cx;
			pt.y = m_ptCenter.y + m_Radius.cy;
			break;
	}

	return pt;
}
	
CRect CVUI_GraphBase::GetHandleRect(int nHandleID)
{
	CRect rect(0, 0, 8, 8);
	int nSzie = xvui_ztsize[XVUI_ZOOM_DEFAULT];
	if(0 <= m_nZoom && m_nZoom < XVUI_ZOOMS)
		nSzie = xvui_ztsize[m_nZoom];

	CPoint pt = GetHandle(nHandleID);

	rect.left = pt.x - nSzie;
	rect.top = pt.y - nSzie;
	rect.right = pt.x + nSzie;
	rect.bottom = pt.y + nSzie;

	return rect;
}

HCURSOR CVUI_GraphBase::GetHandleCursor(int nHandle)
{
	ASSERT(this);

	LPCTSTR id;
	switch (nHandle)
	{
		default:
			ASSERT(FALSE);

		case 0:
		case 4:
			id = IDC_SIZEWE;
			break;

		case 1:
		case 5:
			id = IDC_SIZENWSE;
			break;

		case 2:
		case 6:
			id = IDC_SIZENS;
			break;

		case 3:
		case 7:
			id = IDC_SIZENESW;
			break;
	}

	return AfxGetApp()->LoadStandardCursor(id);
}

int CVUI_GraphBase::GetLinkCount(void)
{
	return XVUI_BLOCK_LINKS;
}
	
CPoint CVUI_GraphBase::GetLink(int nLink)
{
	CPoint pt(0, 0);
	switch(nLink)
	{
		case 0:
			pt.x = m_ptCenter.x - m_Radius.cx;
			pt.y = m_ptCenter.y;
			break;
		case 1:
			pt.x = m_ptCenter.x;
			pt.y = m_ptCenter.y - m_Radius.cy;
			break;
		case 2:
			pt.x = m_ptCenter.x + m_Radius.cx;
			pt.y = m_ptCenter.y;
			break;
		case 3:
			pt.x = m_ptCenter.x;
			pt.y = m_ptCenter.y + m_Radius.cy;
			break;
	}

	return pt;
}

CRect CVUI_GraphBase::GetLinkRect(int nLink)
{
	CRect rect(0, 0, 8, 8);
	int nSzie = xvui_ztsize[XVUI_ZOOM_DEFAULT];
	if(0 <= m_nZoom && m_nZoom < XVUI_ZOOMS)
		nSzie = xvui_ztsize[m_nZoom];

	CPoint pt = GetLink(nLink);

	rect.left = pt.x - nSzie;
	rect.top = pt.y - nSzie;
	rect.right = pt.x + nSzie;
	rect.bottom = pt.y + nSzie;

	return rect;
}

bool CVUI_GraphBase::GetHeadLinkAccess(int nLink)
{
	return true;
}

bool CVUI_GraphBase::GetTailLinkAccess(int nLink)
{
	return true;
}

HCURSOR CVUI_GraphBase::GetLinkCursor(int nLink)
{
	ASSERT(this);

	LPCTSTR id;
	switch (nLink)
	{
		default:
			ASSERT(FALSE);

		case 0:
		case 2:
			id = IDC_SIZEWE;
			break;

		case 1:
		case 3:
			id = IDC_SIZENS;
			break;
	}

	return AfxGetApp()->LoadStandardCursor(id);
}

CRect CVUI_GraphBase::GetRect(void)
{
	CRect rect(m_ptCenter.x-m_Radius.cx, m_ptCenter.y-m_Radius.cy, m_ptCenter.x+m_Radius.cx, m_ptCenter.y+m_Radius.cy);
	return rect;
}

void CVUI_GraphBase::SetLineColor(COLORREF color)
{
	m_clrPen = color;
}
	
void CVUI_GraphBase::SetFillColor(COLORREF color)
{
	m_logBrush.lbColor = color;
}

void CVUI_GraphBase::SetActiveColor(COLORREF color)
{
	m_selBrush.lbColor = color;
}

void CVUI_GraphBase::SetDebugColor(COLORREF color)
{
	m_debugBrush.lbColor = color;
}

CPoint CVUI_GraphBase::GetCenter(void)
{
	return m_ptCenter;
}

void CVUI_GraphBase::SetCenter(CPoint pt)
{
	m_ptCenter = pt;
}

void CVUI_GraphBase::SetCenter(int nx, int ny)
{
	m_ptCenter.x = nx;
	m_ptCenter.y = ny;
}

void CVUI_GraphBase::SetHitPoint(CPoint pt)
{
	m_ptLastHit = pt;
}

CPoint CVUI_GraphBase::GetHitPoint(void)
{
	return m_ptLastHit;
}

void CVUI_GraphBase::Invalidate(void)
{
}

void CVUI_GraphBase::Draw(CDC* pDC)
{
	if(pDC)
	{
		if(m_bShadow)
			DrawShadow(pDC);

		switch(m_nState)
		{
			case XGRAPH_NORMAL:
				DrawNormal(pDC);
				break;
			case XGRAPH_SELECTED: 
			case XGRAPH_ACTIVE:
				DrawSelected(pDC);
				break;
			case XGRAPH_ACTIVEDEBUG:
			case XGRAPH_DEBUG:
				DrawDebug(pDC);
				break;
		}

		DrawLinkers(pDC);
	}
}

void CVUI_GraphBase::DrawTracker(CDC* pDC)
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
	CPen penGreen;
	penGreen.CreatePen(PS_DOT, 0, XVUI_TRACKER_RGB);
	CPen* pOldP;
	CRect rect;
	int nSzie = xvui_ztsize[XVUI_ZOOM_DEFAULT];
	if(0 <= m_nZoom && m_nZoom < XVUI_ZOOMS)
		nSzie = xvui_ztsize[m_nZoom];

	int nMode = pDC->SetROP2(R2_COPYPEN);

	for (int nHandle = 0; nHandle < nHandleCount; nHandle++)
	{
		pOldP = pDC->SelectObject(&penGreen);
		CPoint handle = GetHandle(nHandle);
		CPoint handle2 = GetHandle(nHandle%(nHandleCount-1)+1);
		pDC->MoveTo(handle);
		pDC->LineTo(handle2);
		pDC->SelectObject(pOldP);

		pOldP = pDC->SelectObject(&penOne);
		rect.left = handle.x - nSzie;
		rect.top = handle.y - nSzie;
		rect.right = handle.x + nSzie;
		rect.bottom = handle.y + nSzie;
		pDC->Rectangle(&rect);

		pDC->SelectObject(pOldP);
	}
	pDC->SetROP2(nMode);
	pDC->SelectObject(pOldB);
}

void CVUI_GraphBase::DrawNormal(CDC* pDC)
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

void CVUI_GraphBase::DrawShadow(CDC* pDC)
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

	CRect rect(m_ptCenter.x-m_Radius.cx, m_ptCenter.y-m_Radius.cy, m_ptCenter.x+m_Radius.cx, m_ptCenter.y+m_Radius.cy);
	rect.OffsetRect(XVUI_ENODE_SHADOWX, XVUI_ENODE_SHADOWY);
	pDC->Rectangle(&rect);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pBrush);
	pDC->SetROP2(nOldMode);
}

void CVUI_GraphBase::DrawSelected(CDC* pDC)
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

void CVUI_GraphBase::DrawDebug(CDC* pDC)
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

void CVUI_GraphBase::DrawLinkers(CDC* pDC)
{
	ASSERT(this);
	ASSERT(pDC);

	int nSzie = xvui_ztsize[XVUI_ZOOM_DEFAULT];
	if(0 <= m_nZoom && m_nZoom < XVUI_ZOOMS)
		nSzie = xvui_ztsize[m_nZoom];

	CPen pen;
	pen.CreatePen(PS_SOLID, 0, XVUI_LINKER_LINERGB);
	CPen* pOldPen;
	pOldPen = pDC->SelectObject(&pen);

	int nLinks = GetLinkCount();
	CPoint pt;

	for(int i = 0; i < nLinks; i++)
	{
		pt = GetLink(i);

		pDC->MoveTo(pt.x - nSzie, pt.y);
		pDC->LineTo(pt.x + nSzie, pt.y);
		pDC->MoveTo(pt.x, pt.y - nSzie);
		pDC->LineTo(pt.x, pt.y + nSzie);
	}


	pDC->SelectObject(pOldPen);
}

bool CVUI_GraphBase::HitHandleTest(CPoint point, int& nHandle)
{
	bool bRet = false;
	nHandle = -1;
	int nHandleCount = GetHandleCount();
	CRect rect;

	for (int i = 0; i < nHandleCount; i++)
	{
		rect = GetHandleRect(i);
		if(rect.PtInRect(point))
		{
			bRet = true;
			nHandle = i;
			return bRet;
		}
	}
	return bRet;
}

bool CVUI_GraphBase::HitLinkTest(CPoint point, int& nLink)
{
	bool bRet = false;
	nLink = -1;
	int nLinkCount = GetLinkCount();
	CRect rect;

	for (int i = 0; i < nLinkCount; i++)
	{
		rect = GetLinkRect(i);
		if(rect.PtInRect(point))
		{
			bRet = true;
			nLink = i;
			return bRet;
		}
	}
	return bRet;
}

bool CVUI_GraphBase::HitBlock(CPoint point)
{
	bool bRet = false;
	CRect rect = GetRect();
	if(rect.PtInRect(point))
	{
		bRet = true;
		return bRet;
	}

	return bRet;
}

bool CVUI_GraphBase::HitTest(CPoint point, int& nHandle)
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
		bRet = HitLinkTest(point, nHandle);
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

bool CVUI_GraphBase::DisplayCursor(CPoint point)
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
	else
	{
		bRet = HitLinkTest(point, nHandle);
		if(bRet)
		{

			hCursor = GetLinkCursor(nHandle);
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

bool CVUI_GraphBase::OnLMouseBtnDown(CPoint point)
{
	bool bRet = true;

	if(m_Manager)
		m_Manager->SetGraphSelected(m_nID);

	if(!HitHandleTest(point, m_nMouseDrag))
	{
		m_nMouseDrag = -1;
	}
	m_ptLastHit = point;
	m_nMouseState = enMOUSE_LDOWN;
	m_ptOldCenter = m_ptCenter;

	return bRet;
}

bool CVUI_GraphBase::OnLMouseBtnDblClick(CPoint point, int& nID)
{
	bool bRet = true;

	if(m_Manager)
		m_Manager->SetGraphSelected(m_nID);

	m_nMouseDrag = -1;
	m_nMouseState = enMOUSE_NONE;
	nID = m_nID;

	return bRet;
}

bool CVUI_GraphBase::OnLMouseBtnUp(CPoint point)
{
	bool bRet = true;

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
		CPoint ptOrgDist = m_ptCenter - m_ptOldCenter;
		CRect rect3(0, 0, 1, 1);
		CRect rTmp(0, 0, 1, 1);
		if(AdjustNeighbor(ptOrgDist, rect3))
		{
			rTmp = CVUI_MaxRect::GetBoundary(rect1, rect3);
		}
		else
		{
			rTmp = rect1;
		}
		rect2 = GetBoundaryExt();
		rect = CVUI_MaxRect::GetBoundary(rTmp, rect2);
		bRet = true;
		if(m_Manager)
			m_Manager->InvalidateRect(&rect);
	}

	m_nMouseDrag = -1;
	m_nMouseState = enMOUSE_NONE;
	return bRet;
}

bool CVUI_GraphBase::OnMouseMove(CPoint point)
{
	bool bRet = false;

	CRect rect, rect1, rect2;
	CPoint ptOff;

	if(m_nMouseState == enMOUSE_LDOWN || m_nMouseState == enMOUSE_LMOVE)
	{
		m_nMouseState = enMOUSE_LMOVE; 
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

		rect2 = GetBoundaryExt();
		rect = CVUI_MaxRect::GetBoundary(rect1, rect2);
		bRet = true;
		if(m_Manager)
			m_Manager->InvalidateRect(&rect);
	}

	return bRet;
}

bool CVUI_GraphBase::IsMouseMobile(void)
{
	bool bRet;

	bRet = (m_nMouseState != enMOUSE_NONE);

	return bRet;
}

void CVUI_GraphBase::MoveCenter(CPoint ptOff)
{
	int nX, nY;

	nX = ptOff.x;
	nY = ptOff.y;

	if((m_ptCenter.x+nX) <= 0)
	{
		nX = -m_ptCenter.x;
	}
	else if(XVUI_GRIDSIZE <=(m_ptCenter.x+nX))
	{
		nX = XVUI_GRIDSIZE-m_ptCenter.x;
	}

	if((m_ptCenter.y+nY) <= 0)
	{
		nY = -m_ptCenter.y;
	}
	else if(XVUI_GRIDSIZE <=(m_ptCenter.y+nY))
	{
		nY = XVUI_GRIDSIZE-m_ptCenter.y;
	}

	m_ptCenter.Offset(nX, nY);
}

void CVUI_GraphBase::ChangeShape(CPoint ptOff)
{
	switch(m_nMouseDrag)
	{
		case 0:
			m_Radius.cx -= ptOff.x;
			break;
		case 1:
			m_Radius.cx -= ptOff.x;
			m_Radius.cy -= ptOff.y;
			break;
		case 2:
			m_Radius.cy -= ptOff.y;
			break;
		case 3:
			m_Radius.cx += ptOff.x;
			m_Radius.cy -= ptOff.y;
			break;
		case 4:
			m_Radius.cx += ptOff.x;
			break;
		case 5:
			m_Radius.cx += ptOff.x;
			m_Radius.cy += ptOff.y;
			break;
		case 6:
			m_Radius.cy += ptOff.y;
			break;
		case 7:
			m_Radius.cx -= ptOff.x;
			m_Radius.cy += ptOff.y;
			break;
		default:
			ASSERT(false);
	}
	if(m_Radius.cx <= XVUI_ENODE_MINX)
		m_Radius.cx = XVUI_ENODE_MINX;
	if(m_Radius.cy <= XVUI_ENODE_MINY)
		m_Radius.cy = XVUI_ENODE_MINY;
}

void CVUI_GraphBase::MoveTo(CPoint pt)
{
	CPoint ptOff;
	ptOff = pt - m_ptCenter;
	MoveCenter(ptOff);
}

bool CVUI_GraphBase::AdjustNeighbor(CPoint ptOff, CRect& rect)
{
	bool bRet = false;
	if(m_Manager)
		bRet = m_Manager->AdjustNeighborGraph(m_nID, ptOff, rect);

	return bRet;
}

bool CVUI_GraphBase::OnRMouseDown(CPoint point, int& nID)
{
	bool bRet = true;

	if(m_Manager)
		m_Manager->SetGraphSelected(m_nID);

	nID = m_nID;

	return bRet;
}

enXVSB_PUTYPE CVUI_GraphBase::GetType(void)
{
	return m_puType;
}

/////////////////////////////////////////////////////////////////////////////
