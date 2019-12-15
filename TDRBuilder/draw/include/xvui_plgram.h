#ifndef __XVUI_PLGRAM_H__
#define __XVUI_PLGRAM_H__
#include "xvui_graph.h"

/////////////////////////////////////////////////////////////////////////////
// CVUI_Parallelogram

class CVUI_Parallelogram : public CVUI_GraphBase
{
//@Access: Constructors
public:
	//@cmember: Constructor
	CVUI_Parallelogram(long	nID = 0, CVUI_GraphManager*	pManager = NULL);

	//@cmember: Destructor
	virtual ~CVUI_Parallelogram();

//@Access: Operations
public:
	//@cmember: Get the boundary rectangle including the handle box 
	virtual CRect GetBoundaryExt(void);

//@Access: Attributes
protected:
	//@cmember: The ration to calculate the slope 
	double			m_nRaito;

	//@cmember: The the offset of slope edge
	int				m_nOffset;

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

	//@cmember: Change block with specific x, y
	virtual void ChangeShape(CPoint ptOff);

};


#endif // __XVUI_PLGRAM_H__
