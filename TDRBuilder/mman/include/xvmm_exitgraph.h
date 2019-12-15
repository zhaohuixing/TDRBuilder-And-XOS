#ifndef __XVMM_EXITGRAPH_H__
#define __XVMM_EXITGRAPH_H__
#include "xvui_ellipse.h"

/////////////////////////////////////////////////////////////////////////////
// CVMM_EntryGraph
class CVMM_ExitGraph : public CVUI_Ellipse
{
//@Access: Constructors
public:
	//@cmember: Constructor
	CVMM_ExitGraph(CVUI_GraphManager* pManager = NULL);

	//@cmember: Destructor
	virtual ~CVMM_ExitGraph();

//@Access: Attributes
public:
	//@cmember: Check the header link access
	virtual bool GetHeadLinkAccess(int nLink){return true;}

	//@cmember: Check the tail link access
	virtual bool GetTailLinkAccess(int nLink){return false;}

//@Access: Operations
protected:
};


#endif // __XVUI_ELLIPSE_H__
