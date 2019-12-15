#ifndef __XVUI_GRAPHMAN_H__
#define __XVUI_GRAPHMAN_H__
#include "xvui_graph.h"
#include "xvui_gsignal.h"

/////////////////////////////////////////////////////////////////////////////
// CVUI_GraphManager

class CVUI_GraphManager
{
// Constructors
public:
	//@cmember: Constructor
	CVUI_GraphManager(CVUI_GraphCallBack* pHandler = NULL);

	//@cmember: Destructor
	virtual ~CVUI_GraphManager();

//@Access: Attributes
public:
	//@cmember: Diagram block table
	CVUI_GraphMap		m_GraphMap;

	//@cmember: Active diagram block id
	int					m_nActiveID;


	CVUI_GraphCallBack* m_pMsgHandler;

//@Access: Operations
public:
	//@cmember: Clean the block table
	virtual void SetMsgHandler(CVUI_GraphCallBack* pHandler)
	{
		m_pMsgHandler = pHandler;
	}

	//@cmember: Check the selected block ID
	virtual int GetActiveID(void){return m_nActiveID;}

	//@cmember: Clean the block table
	virtual bool AddGraph(CVUI_GraphBase* pBlock);

	//@cmember: Check the selected block existance
	virtual bool HasSelectedGraph(void);

	//@cmember: Set the block as selected
	virtual bool SetGraphSelected(int nID);

	//@cmember: Deselect the selected block
	virtual bool DeSelectedGraph(void);

	//@cmember: Set the block as denug 
	virtual bool SetGraphDebug(int nID);

	//@cmember: Reset the block debug state
	virtual bool ResetGraphDebug(int nID);

	//@cmember: Clean all block state
	virtual bool CleanGraphState(void);

	//@cmember: Display all blocks
	virtual void Draw(CDC* pDC);

	//@cmember: Set graph zoom factor
	virtual void SetGraphZoom(int nZoom);

	//@cmember: Set the graph shadow drawing
	virtual void SetShadow(bool bShadow);

	//@cmember: Show cursor when over the block
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
	virtual bool OnRMouseDown(CPoint point, int& nID, int& nHandle);

	//@cmember: Clean the block table
	virtual void InvalidateRect(CRect* pRect)
	{
		if(m_pMsgHandler)
		{
			m_pMsgHandler->InvalidateRect(pRect);
		}
	}

	//@cmember: Reset polyline intersections
	virtual bool ResetPolyLinePoints(void);

	//@cmember: Check whether hit sth
	virtual bool IsHitBlock(CPoint point);

	//@cmember: Move the neighbor graphs
	virtual bool AdjustNeighborGraph(int nSrcID, CPoint ptOff, CRect& rect){return false;}

	//@cmember: Rotate connector head
	virtual void RotateLinkHead(int nID, int nDir);

	//@cmember: Rotate connector tail
	virtual void RotateLinkTail(int nID, int nDir);

	//@cmember: Delete active block
	virtual void DeleteActive(void);

	//@cmember: Delete selected block
	virtual void DeleteSelectBlock(int nID);

	//@cmember: Get graph object
	virtual CVUI_GraphBase* GetGraph(int nID);

	//@cmember: Get graph object type
	virtual enXVSB_PUTYPE GetGraphType(int nID);

	//@cmember: Check possibility of set linker head linkage
	virtual bool CanSetHeadLink (int nLinkID, int nHeadID){return true;}

	//@cmember: Check possibility of set linker tail linkage
	virtual bool CanSetTailLink (int nLinkID, int nTailID){return true;}


//@Access: Operations
protected:
	//@cmember: Clean the block table
	virtual void CleanMap(void);

};

#endif // __XVUI_GRAPHMAN_H__
