#ifndef __XVUI_TRIANGLE_H__
#define __XVUI_TRIANGLE_H__
#include "xvui_graph.h"

/////////////////////////////////////////////////////////////////////////////
// CVUI_Triangle

class CVUI_Triangle : public CVUI_GraphBase
{
//@Access: Constructors
public:
	//@cmember: Constructor
	CVUI_Triangle(long	nID = 0, CVUI_GraphManager*	pManager = NULL);

	//@cmember: Destructor
	virtual ~CVUI_Triangle();

//@Access: Operations
public:
	//@cmember: The highlight link points number
	virtual int GetLinkCount(void);
	
	//@cmember: Get the highlight point 
	virtual CPoint GetLink(int nLink);
	
	//@cmember: Get the highlight point/handle cursor resource
	virtual HCURSOR GetLinkCursor(int nLink);

	//@cmember: Get the boundary rectangle including the handle box 
	virtual CRect GetBoundaryExt(void);

//@Access: Attributes
public:

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

	//@cmember: Hit block test
	virtual bool HitBlock(CPoint point);

};


#endif // __XVUI_ELLIPSE_H__
