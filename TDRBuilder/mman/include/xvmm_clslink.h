#ifndef __XVMM_CLSLINK_H__
#define __XVMM_CLSLINK_H__

#include "xvmm_mlinker.h"

/////////////////////////////////////////////////////////////////////////////
// CVUI_PolyLine
class CVMM_ClassLinker : public CVMM_ModuleLinker
{
//@Access: Constructors
public:
	//@cmember: Constructor
	CVMM_ClassLinker(int nID, CVUI_GraphManager*	pManager = NULL);

	//@cmember: Constructor
	CVMM_ClassLinker(const CPoint pts[], int nCount, int nID, CVUI_GraphManager* pManager = NULL);

	//@cmember: Constructor
	CVMM_ClassLinker(int nID, int nShape = 1, CVUI_GraphManager* pManager = NULL);

	//@cmember: Destructor
	virtual ~CVMM_ClassLinker();

//@Access: Attributes
public:

//@Access: Operations
public:

//@Access: Operations
protected:
	//@cmember: Drawing normal
	virtual void DrawNormal(CDC* pDC);

	//@cmember: Invalidate module block linkage
	virtual void ValidateLinkage(int nOldHead, int nOldTail);

};

#endif // __XVMM_MLINKER_H__
