#ifndef __XVUI_GRAPH_H__
#define __XVUI_GRAPH_H__
#include "xvsb_defs.h"
#include "tvsb_cpputil.h"
#include "xvui_uidefs.h"
#include <map>
#include <string>

/////////////////////////////////////////////////////////////////////////////
// CVUI_GraphBase - base class for all diagram 'drawable objects'

class CVUI_GraphManager;

class CVUI_GraphBase
{
//@Access: Constructors
protected:
// Constructors
public:
	//@cmember: Constructor
	CVUI_GraphBase(int	nID = 0, CVUI_GraphManager*	pManager = NULL);

	//@cmember: Destructor
	virtual ~CVUI_GraphBase();

//@Access: Attributes
public:
	//@cmember: Diagram block graphic status

	//@cmember: Diagram block state
	enXVUI_GRAPHSTATE	m_nState;

	//@cmember: Diagram block id
	int					m_nID;

	//@cmember: Diagram block shadow theme enable
	bool				m_bShadow;

	//@cmember: Diagram block name
	CStringW			m_strName;

	//@cmember: Diagram block graph center
	CPoint				m_ptCenter;

	//@cmember: Old diagram block graph center
	CPoint				m_ptOldCenter;

	//@cmember: The mouse hit point
	CPoint				m_ptLastHit;

	//@cmember: Diagram block graph radius in X axis and Y axis
	CSize				m_Radius;

	//@cmember: The pen object color
	COLORREF			m_clrPen;

	//@cmember: The logic brush object
	LOGBRUSH			m_logBrush;

	//@cmember: The logic brush object for active state
	LOGBRUSH			m_selBrush;

	//@cmember: The logic brush object for brush state
	LOGBRUSH			m_debugBrush;

	//@cmember: The zoom factor
	int					m_nZoom;

	//@cmember: The text font
	CFont				m_TextFont;

	//@cmember: The upper container
	CVUI_GraphManager*	m_Manager;

	//@cmember: The mouse dragging state
	int					m_nMouseDrag;

	//@cmember: The mouse state
	enXVUI_MOUSESTATE	m_nMouseState;


	//@cmember: The block type presented by graph
	enXVSB_PUTYPE		m_puType;

//@Access: Attributes
protected:
	//@cmember: The text rectange
	CRect			m_txtRect;

//@Access: Operations
public:
	//@cmember: Set upper conatiner
	virtual void SetMan(CVUI_GraphManager*	pManager);

	//@cmember: Set the block ID
	virtual void SetID(int nID){m_nID = nID;}

	//@cmember: Get the block ID
	virtual int GetID(void){return m_nID;}

	//@cmember: Set the block name
	virtual void SetName(CStringW& szName){m_strName = szName;}

	//@cmember: Get the block name
	virtual CStringW GetName(void){return m_strName;}

	//@cmember: Set the graph state
	virtual void SetGraphState(enXVUI_GRAPHSTATE nState){m_nState = nState;}

	//@cmember: Get the graph state
	virtual enXVUI_GRAPHSTATE GetGraphState(void){return m_nState;}

	//@cmember: Set the graph shadow drawing
	virtual void SetShadow(bool bShadow){m_bShadow = bShadow;}

	//@cmember: Unselect the block
	virtual void DeSelected(void);

	//@cmember: Select the block
	virtual void SetSelected(void);

	//@cmember: Set the block as debug state
	virtual void SetDebug(void);

	//@cmember: Reset the block from debug state
	virtual void ResetDebug(void);

	//@cmember: Set state to nomral
	virtual void CleanState(void);

	//@cmember: Check selected state
	virtual bool IsSelected(void);

	//@cmember: Check active state
	virtual bool IsActiveOnly(void);

	//@cmember: Check active state
	virtual bool IsActive(void);

	//@cmember: Check debug state
	virtual bool IsDebug(void);

	//@cmember: Check normal state
	virtual bool IsNormal(void);

	//@cmember: Get the graph shadow drawing
	virtual bool GetShadow(void){return m_bShadow;}

	//@cmember: Set the graph zoom index
	virtual void SetZoom(int nZoom){m_nZoom = nZoom;}

	//@cmember: Get the boundary rectangle including the handle box 
	virtual CRect GetBoundaryExt(void);

	//@cmember: The highlight points/handle number
	virtual int GetHandleCount(void);
	
	//@cmember: Get the highlight point 
	virtual CPoint GetHandle(int nHandle);
	
	//@cmember: Get the highlight point/handle rectangle 
	virtual CRect GetHandleRect(int nHandleID);

	//@cmember: Get the highlight point/handle cursor resource
	virtual HCURSOR GetHandleCursor(int nHandle);

	//@cmember: The highlight link points number
	virtual int GetLinkCount(void);
	
	//@cmember: Get the highlight point 
	virtual CPoint GetLink(int nLink);
	
	//@cmember: Get the highlight point/handle rectangle 
	virtual CRect GetLinkRect(int nLink);

	//@cmember: Check the header link access
	virtual bool GetHeadLinkAccess(int nLink);

	//@cmember: Check the tail link access
	virtual bool GetTailLinkAccess(int nLink);

	//@cmember: Get the highlight point/handle cursor resource
	virtual HCURSOR GetLinkCursor(int nLink);

	//@cmember: Get the regular rectangle 
	virtual CRect GetRect(void);

	//@cmember: Set the line color
	virtual void SetLineColor(COLORREF color);
	
	//@cmember: Set the filling color
	virtual void SetFillColor(COLORREF color);

	//@cmember: Set the active color
	virtual void SetActiveColor(COLORREF color);

	//@cmember: Set the debug color
	virtual void SetDebugColor(COLORREF color);

	//@cmember: Re-paint 
	virtual void Invalidate(void);

	//@cmember: Drawing
	virtual void Draw(CDC* pDC);

	//@cmember: Drawing highlight tracker
	virtual void DrawTracker(CDC* pDC);

	//@cmember: Get center point
	virtual CPoint GetCenter(void);

	//@cmember: Set center point
	virtual void SetCenter(CPoint pt);

	//@cmember: Set center point
	virtual void SetCenter(int nx, int ny);

	//@cmember: Set hit point
	virtual void SetHitPoint(CPoint pt);

	//@cmember: Get hit point
	virtual CPoint GetHitPoint(void);

	//@cmember: Move center point to
	virtual void MoveTo(CPoint pt);

	//@cmember: Hit Test
	virtual bool HitTest(CPoint point, int& nHandle);

	//@cmember: Hit handle test
	virtual bool HitHandleTest(CPoint point, int& nHandle);

	//@cmember: Hit handle test
	virtual bool HitLinkTest(CPoint point, int& nLink);

	//@cmember: Show cursor
	virtual bool DisplayCursor(CPoint point);

	//@cmember: Process left mouse button down
	virtual bool OnLMouseBtnDown(CPoint point);

	//@cmember: Process double click left mouse button
	virtual bool OnLMouseBtnDblClick(CPoint point, int& nID);

	//@cmember: Process left mouse button up
	virtual bool OnLMouseBtnUp(CPoint point);

	//@cmember: Process mouse moving
	virtual bool OnMouseMove(CPoint point);

	//@cmember: Process right mouse button down
	virtual bool OnRMouseDown(CPoint point, int& nID);

	//@cmember: Process mouse moving
	virtual bool IsMouseMobile(void);

	//@cmember: Get the block type
	virtual enXVSB_PUTYPE GetType(void);

//@Access: Operations
protected:
	//@cmember: Drawing normal
	virtual void DrawNormal(CDC* pDC);

	//@cmember: Drawing shadow
	virtual void DrawShadow(CDC* pDC);

	//@cmember: Drawing highlight state
	virtual void DrawSelected(CDC* pDC);

	//@cmember: Drawing debug state
	virtual void DrawDebug(CDC* pDC);

	//@cmember: Drawing connection points
	virtual void DrawLinkers(CDC* pDC);

	//@cmember: Hit block test
	virtual bool HitBlock(CPoint point);

	//@cmember: Move block with specific x, y
	virtual void MoveCenter(CPoint ptOff);

	//@cmember: Change block with specific x, y
	virtual void ChangeShape(CPoint ptOff);

	//@cmember: Change block with specific x, y
	virtual bool AdjustNeighbor(CPoint ptOff, CRect& rect);
};

typedef std::map<int, CVUI_GraphBase*>					CVUI_GraphMap;
typedef TVSB_PairDeletor<CVUI_GraphMap::value_type>		CVUI_GMapDelete;
typedef TVSB_Dealloc<CVUI_GraphMap, CVUI_GMapDelete>	CVUI_GMapRelease;


#endif // __XVUI_GRAPH_H__
