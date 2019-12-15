#ifndef __XVUI_RRECT_H__
#define __XVUI_RRECT_H__
#include "xvui_graph.h"

/////////////////////////////////////////////////////////////////////////////
// CVUI_GraphBase - base class for all diagram 'drawable objects'

class CVUI_RoundRect : public CVUI_GraphBase
{
//@Access: Constructors
public:
	//@cmember: Constructor
	CVUI_RoundRect(long	nID = 0, CVUI_GraphManager*	pManager = NULL);

	//@cmember: Destructor
	virtual ~CVUI_RoundRect();

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

};


#endif // __XVUI_RRECT_H__
