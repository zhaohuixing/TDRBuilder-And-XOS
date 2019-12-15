#ifndef __XVMM_CMPGRAPH_H__
#define __XVMM_CMPGRAPH_H__

#include "xvui_triangle.h"

/////////////////////////////////////////////////////////////////////////////
// CVUI_Triangle
class CVMM_CnditGraph : public CVUI_Triangle
{
//@Access: Constructors
public:
	//@cmember: Constructor
	CVMM_CnditGraph(long nID, CVUI_GraphManager* pManager = NULL);

	//@cmember: Destructor
	virtual ~CVMM_CnditGraph();

//@Access: Operations
public:
	//@cmember: Check the header link access
	virtual bool GetHeadLinkAccess(int nLink);

	//@cmember: Check the tail link access
	virtual bool GetTailLinkAccess(int nLink);

//@Access: Attributes
public:

//@Access: Operations
protected:
};


#endif // __XVUI_ELLIPSE_H__
