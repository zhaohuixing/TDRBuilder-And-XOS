#ifndef __XVMM_ENTRYGRAPH_H__
#define __XVMM_ENTRYGRAPH_H__
#include "xvui_ellipse.h"

/////////////////////////////////////////////////////////////////////////////
// CVMM_EntryGraph
class CVMM_EntryGraph : public CVUI_Ellipse
{
//@Access: Constructors
public:
	//@cmember: Constructor
	CVMM_EntryGraph(CVUI_GraphManager* pManager = NULL);

	//@cmember: Destructor
	virtual ~CVMM_EntryGraph();

//@Access: Attributes
public:
	//@cmember: Check the header link access
	virtual bool GetHeadLinkAccess(int nLink){return false;}

	//@cmember: Check the tail link access
	virtual bool GetTailLinkAccess(int nLink)
	{
		if(nLink == 3)
			return true;
		else
			return false;
	}

//@Access: Operations
protected:
};


#endif // __XVUI_ELLIPSE_H__
