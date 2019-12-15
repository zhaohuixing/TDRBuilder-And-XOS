#ifndef __XVUI_DIAMOND_H__
#define __XVUI_DIAMOND_H__
#include "xvui_graph.h"

/////////////////////////////////////////////////////////////////////////////
// CVUI_Diamond

class CVUI_Diamond : public CVUI_GraphBase
{
//@Access: Constructors
public:
	//@cmember: Constructor
	CVUI_Diamond(long	nID = 0, CVUI_GraphManager*	pManager = NULL);

	//@cmember: Destructor
	virtual ~CVUI_Diamond();

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
