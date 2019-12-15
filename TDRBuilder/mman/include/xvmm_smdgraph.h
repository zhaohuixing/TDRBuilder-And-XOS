#ifndef __XVMM_SMDGRAPH_H__
#define __XVMM_SMDGRAPH_H__
#include "xvui_graph.h"
#include <map>
#include <string>

/////////////////////////////////////////////////////////////////////////////
// CVMM_PUGraph

class CVMM_SMDGraph : public CVUI_GraphBase
{
//@Access: Constructors
protected:
// Constructors
public:
	//@cmember: Constructor
	CVMM_SMDGraph(long	nID, CVUI_GraphManager*	pManager = NULL);

	//@cmember: Destructor
	virtual ~CVMM_SMDGraph();

//@Access: Attributes
public:

//@Access: Attributes
protected:
	//@cmember: Drawing normal
	virtual void DrawNormal(CDC* pDC);

	//@cmember: Drawing highlight state
	virtual void DrawSelected(CDC* pDC);

	//@cmember: Drawing debug state
	virtual void DrawDebug(CDC* pDC);

	//@cmember: Drawing corner state
	void DrawCorner(CDC* pDC);

//@Access: Operations
public:
	//@cmember: Check the head link access
	virtual bool GetHeadLinkAccess(int nLink);

	//@cmember: Check the tail link access
	virtual bool GetTailLinkAccess(int nLink);
};

#endif // __XVMM_SMDGRAPH_H__
