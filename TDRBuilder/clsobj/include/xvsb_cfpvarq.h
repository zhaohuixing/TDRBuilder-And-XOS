// Project: Visual System Builder
//
// File Name: xvsb_cfpvarq.h
//
// Description: The definition of the class function process variable parameter queue object
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 05/19/2005	
//
// History:
// 1.    05/19/2005: Create	
//
#ifndef __XVSB_CFPVARQ_H__
#define __XVSB_CFPVARQ_H__

#include "xvsb_cfstack.h"
#include "xvsb_cfqman.h"

class XVSB_CLASS CVSB_CFVarQFilter : public CVSB_CFNodeQBase
{
public:
	CVSB_CFVarQFilter(CVSB_hCFnNode hCusor = NULL);
	CVSB_CFVarQFilter(CVSB_hCFnNode hCusor, CVSB_Method* pOwner);
	CVSB_CFVarQFilter(CVSB_hCFnNode hCusor, CVSB_CFNodeQBase*	prevQ);
	CVSB_CFVarQFilter(CVSB_hCFnNode hCusor, CVSB_CFnQMan*	pQM);
	CVSB_CFVarQFilter(CVSB_hCFnNode hCusor, CVSB_Method* pOwner, CVSB_CFNodeQBase* prevQ, CVSB_CFnQMan* pQM);
	virtual ~CVSB_CFVarQFilter();

public:
	virtual enXVSB_NODEQTYPE GetQtype(void){return enXVSB_NODEQ_VAR;}
	virtual bool IsNodeQ(void){return false;}
	virtual bool IsVariableQ(void){return true;}

protected:
};


#endif
