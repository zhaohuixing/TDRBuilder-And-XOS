#ifndef __XVMM_MLINKER_H__
#define __XVMM_MLINKER_H__

#include "xvui_polyline.h"

/////////////////////////////////////////////////////////////////////////////
// CVUI_PolyLine
class CVMM_ModuleLinker : public CVUI_PolyLine
{
//@Access: Constructors
public:
	//@cmember: Constructor
	CVMM_ModuleLinker(int nID, CVUI_GraphManager*	pManager = NULL);

	//@cmember: Constructor
	CVMM_ModuleLinker(const CPoint pts[], int nCount, int nID, CVUI_GraphManager* pManager = NULL);

	//@cmember: Constructor
	CVMM_ModuleLinker(int nID, int nShape = 1, CVUI_GraphManager* pManager = NULL);

	//@cmember: Destructor
	virtual ~CVMM_ModuleLinker();

//@Access: Attributes
public:

//@Access: Operations
public:
	//@cmember: Move block with specific x, y
	virtual void MoveCenter(CPoint ptOff);

	//@cmember: Get head link ID
	virtual int GetHeadLink(void){return m_nHeadLink;}

	//@cmember: Get tail link ID
	virtual int GetTailLink(void){return m_nTailLink;}

	//@cmember: Is head linked
	virtual bool IsHeadLink(void){return m_bHeadLink;}

	//@cmember: Is tail linked
	virtual bool IsTailLink(void){return m_bTailLink;}

	//@cmember: Update linkage
	virtual void UpdateLinkage(void);

//@Access: Operations
protected:
	//@cmember: Drawing normal
	virtual void DrawNormal(CDC* pDC);

	//@cmember: Drawing highlight state
	virtual void DrawSelected(CDC* pDC);

	//@cmember: Drawing tracker line
	virtual void DrawGhost(CDC* pDC);

	//@cmember: Change block with specific x, y
	virtual void ChangeShape(CPoint ptOff);

	//@cmember: Update header linkage
	virtual void UpdateHeadLink(void);

	//@cmember: Update tail linkage
	virtual void UpdateTailLink(void);

	//@cmember: Invalidate module block linkage
	virtual void ValidateLinkage(int nOldHead, int nOldTail);

	//@cmember: Update ghost head link
	virtual void UpdateGhostHeadLink(void);

	//@cmember: Update real head link
	virtual void UpdateRealHeadLink(void);

	//@cmember: Update ghost tail link
	virtual void UpdateGhostTailLink(void);

	//@cmember: Update real tail link
	virtual void UpdateRealTailLink(void);

	//@cmember: Is head movable
	virtual bool IsHeadMovable(void);

	//@cmember: Is tail movable
	virtual bool IsTailMovable(void);

//@Access: Attributes
public:
	bool	m_bHeadLink;
	bool	m_bTailLink;
	bool	m_bGhostHeadLink;
	bool	m_bGhostTailLink;

	CRect	m_rectGHLink;
	CRect	m_rectGTLink;

	int		m_nHeadLink;	
	int		m_nTailLink;	

	bool	m_bTail2Logic;
	bool	m_bTail2LogicYes;
};

#endif // __XVMM_MLINKER_H__
