#ifndef __XVUI_ELLIPSE_H__
#define __XVUI_ELLIPSE_H__
#include "xvui_graph.h"

/////////////////////////////////////////////////////////////////////////////
// CVUI_Ellipse

class CVUI_Ellipse : public CVUI_GraphBase
{
//@Access: Constructors
public:
	//@cmember: Constructor
	CVUI_Ellipse(long nID = 0, CVUI_GraphManager* pManager = NULL);

	//@cmember: Destructor
	virtual ~CVUI_Ellipse();

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
