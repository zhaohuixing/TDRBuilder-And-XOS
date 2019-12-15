#ifndef __XVUI_POLYLINE_H__
#define __XVUI_POLYLINE_H__

#include "xvui_point.h"
#include "xvui_graph.h"

/////////////////////////////////////////////////////////////////////////////
// CVUI_PolyLine
class CVUI_PolyLine : public CVUI_GraphBase
{
//@Access: Constructors
public:
	//@cmember: Constructor
	CVUI_PolyLine(int nID = 0, CVUI_GraphManager*	pManager = NULL);

	//@cmember: Constructor
	CVUI_PolyLine(const CPoint pts[], int nCount, int nID = 0, CVUI_GraphManager* pManager = NULL);

	//@cmember: Constructor
	CVUI_PolyLine(int nID, int nShape = 1, CVUI_GraphManager* pManager = NULL);

	//@cmember: Destructor
	virtual ~CVUI_PolyLine();

//@Access: Attributes
public:
	//@cmember: The intersection point list
	CVUI_LPointArray		m_PolyLine;

	//@cmember: The tracker line
	CVUI_PointArray			m_TrackLine;

	//@cmember: The flag to draw tracker line
	bool					m_bDrawTrack;

	//@cmember: The mouse moving head or tail flag
	bool					m_bMoveHeadTail;

	//@cmember: The cursor before mouse moving
	HCURSOR					m_hOldCursor;

	//@cmember: The real mouse track point
	CPoint					m_ptRealTrack;
//@Access: Operations
public:
	//@cmember: Drawing highlight tracker
	virtual void DrawTracker(CDC* pDC);

	//@cmember: Show cursor
	virtual bool DisplayCursor(CPoint point);

	//@cmember: Hit Test
	virtual bool HitTest(CPoint point, int& nHandle);

	//@cmember: Hit handle test
	virtual bool HitHandleTest(CPoint point, int& nHandle);

	//@cmember: Hit head or tail handle test
	virtual bool HitHeadTailTest(CPoint point, int& nHandle);

	//@cmember: Is head handler
	virtual bool IsHeadHandle(int nHandle);

	//@cmember: Is tail handler
	virtual bool IsTailHandle(int nHandle);

	//@cmember: The line count
	virtual int GetLineCount(void);

	//@cmember: The point count
	virtual int GetPointCount(void);

	//@cmember: The highlight points/handle number
	virtual int GetHandleCount(void);
	
	//@cmember: Get the highlight point 
	virtual CPoint GetHandle(int nHandle);

	//@cmember: Get the head point 
	virtual CPoint GetHeadPoint(void);

	//@cmember: Get the tail point 
	virtual CPoint GetTailPoint(void);

	//@cmember: Get the highlight point/handle rectangle 
	virtual CRect GetHandleRect(int nHandleID);

	//@cmember: Get the highlight point/handle rectangle 
	virtual CRect GetHandleRectExt(int nHandleID);

	//@cmember: Get the highlight point/handle line index 
	virtual int GetHandleLineIndex(int nHandleID);

	//@cmember: Get the highlight point/handle point index 
	virtual int GetHandlePointIndex(int nHandleID);

	//@cmember: Get the highlight point/handle cursor resource
	virtual HCURSOR GetHandleCursor(int nHandle);

	//@cmember: Get the line segment direction
	virtual bool IsHorzLine(int nIndx);

	//@cmember: Get the line segment direction
	virtual bool IsWestEastLine(int nIndx);

	//@cmember: Get the boundary rectangle including the handle box 
	virtual CRect GetBoundaryExt(void);

	//@cmember: Process double click left mouse button
	virtual bool OnLMouseBtnDblClick(CPoint point, int& nID);

	//@cmember: Process left mouse button down
	virtual bool OnLMouseBtnDown(CPoint point);

	//@cmember: Process mouse moving
	virtual bool OnMouseMove(CPoint point);

	//@cmember: Process left mouse button up
	virtual bool OnLMouseBtnUp(CPoint point);

	//@cmember: Adjust the polyline line segment
	virtual bool AdjustPloyLine(void);

	//@cmember: Adjust the intersection points
	virtual void AdjustIntersects(void);

	//@cmember: Clear the intersection points
	virtual void ClearIntersects(void);

	//@cmember: Update the intersection
	virtual bool ResetIntersects(void);

	//@cmember: Move block with specific x, y
	virtual void MoveCenter(CPoint ptOff);

	//@cmember: Update the overlay points
	virtual bool RemoveOverlay(void);

	//@cmember: Update the overlay points
	virtual bool StraightLine(void);

	//@cmember: Head offset
	virtual bool HeadOffset(CPoint ptOff);

	//@cmember: Head offset
	virtual bool HeadOffset(int nX, int nY);

	//@cmember: Tail offset
	virtual bool TailOffset(CPoint ptOff);

	//@cmember: Tail offset
	virtual bool TailOffset(int nX, int nY);

	//@cmember: Rotate the head
	virtual void RotateHead(int nDir);

	//@cmember: Rotate the tail
	virtual void RotateTail(int nDir);

	//@cmember: Get head arrow direction
	virtual int GetHeadDir(void);

	//@cmember: Get tail direction
	virtual int GetTailDir(void);

	//@cmember: Move the head
	virtual void MoveHead(CPoint ptOff);

	//@cmember: Move the tail
	virtual void MoveTail(CPoint ptOff);

//@Access: Operations
protected:
	//@cmember: Drawing normal
	virtual void DrawNormal(CDC* pDC);

	//@cmember: Drawing shadow
	virtual void DrawShadow(CDC* pDC);

	//@cmember: Drawing highlight state
	virtual void DrawSelected(CDC* pDC);

	//@cmember: Drawing tracker line
	virtual void DrawGhost(CDC* pDC);

	//@cmember: Drawing debug state
	virtual void DrawDebug(CDC* pDC);

	//@cmember: Drawing connection points
	virtual void DrawLinkers(CDC* pDC);

	//@cmember: Hit block test
	virtual bool HitBlock(CPoint point);

	//@cmember: Check handle type
	virtual bool IsMiddleHandle(int nHandle);

	//@cmember: Move tracker block with specific x, y
	virtual void MoveGhostCenter(CPoint ptOff);

	//@cmember: Change block with specific x, y
	virtual void ChangeShape(CPoint ptOff);

	//@cmember: Update the intersection
	virtual bool UpdateIntersection(void);

	//@cmember: Is head movable
	virtual bool IsHeadMovable(void);

	//@cmember: Is tail movable
	virtual bool IsTailMovable(void);

	//@cmember: Move the handle
	virtual void MoveActiveHandle(CPoint ptOff);

	//@cmember: Move the tracker line head
	virtual void MoveGhostHead(CPoint ptOff);

	//@cmember: Move the tracker linetail
	virtual void MoveGhostTail(CPoint ptOff);

	//@cmember: Move the tracker linehandle
	virtual void MoveGhostActiveHandle(CPoint ptOff);

	//@cmember: Move the tracker linehandle
	virtual void DrawLineSegment(CDC* pDC, CVUI_LinkPoint& pt1, CVUI_LinkPoint& pt2);

};

#endif // __XVUI_POINT_H__
