#ifndef __XVMM_PUGRAPH_H__
#define __XVMM_PUGRAPH_H__
#include "xvui_graph.h"
#include <map>
#include <string>

/////////////////////////////////////////////////////////////////////////////
// CVMM_PUGraph

class CVMM_PUGraph: public CVUI_GraphBase
{
//@Access: Constructors
protected:
// Constructors
public:
	//@cmember: Constructor
	CVMM_PUGraph(long	nID, CVUI_GraphManager*	pManager = NULL);

	//@cmember: Destructor
	virtual ~CVMM_PUGraph();

//@Access: Attributes
public:

//@Access: Attributes
protected:

//@Access: Operations
public:
	//@cmember: Check the head link access
	virtual bool GetHeadLinkAccess(int nLink);

	//@cmember: Check the tail link access
	virtual bool GetTailLinkAccess(int nLink);
};

#endif // __XVUI_GRAPH_H__
