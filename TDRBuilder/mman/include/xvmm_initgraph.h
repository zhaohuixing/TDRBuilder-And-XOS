#ifndef __XVMM_INITGRAPH_H__
#define __XVMM_INITGRAPH_H__

#include "xvui_plgram.h"

/////////////////////////////////////////////////////////////////////////////
// CVUI_Parallelogram

class CVMM_InitGraph : public CVUI_Parallelogram
{
//@Access: Constructors
public:
	//@cmember: Constructor
	CVMM_InitGraph(CVUI_GraphManager*	pManager = NULL);

	//@cmember: Destructor
	virtual ~CVMM_InitGraph();

//@Access: Operations
public:
	//@cmember: Check the header link access
	virtual bool GetHeadLinkAccess(int nLink);

	//@cmember: Check the tail link access
	virtual bool GetTailLinkAccess(int nLink);

//@Access: Attributes
protected:
};


#endif // __XVUI_PLGRAM_H__
