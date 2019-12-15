#ifndef __XVMM_DOCGRAPH_H__
#define __XVMM_DOCGRAPH_H__
#include "xvui_rrect.h"

/////////////////////////////////////////////////////////////////////////////
// CVUI_GraphBase - base class for all diagram 'drawable objects'

class CVMM_TextGraph : public CVUI_RoundRect
{
//@Access: Constructors
public:
	//@cmember: Constructor
	CVMM_TextGraph(long	nID, CVUI_GraphManager*	pManager = NULL);

	//@cmember: Destructor
	virtual ~CVMM_TextGraph();

//@Access: Attributes
public:
	//@cmember: Check the header link access
	virtual bool GetHeadLinkAccess(int nLink){return false;}

	//@cmember: Check the tail link access
	virtual bool GetTailLinkAccess(int nLink){return false;}

//@Access: Operations
protected:
};


#endif // __XVUI_RRECT_H__
