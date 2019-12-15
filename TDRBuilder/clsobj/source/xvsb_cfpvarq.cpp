// Project: Visual System Builder
//
// File Name: xvsb_cfpvarq.cpp
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
#include "xvsb_cfqman.h"
#include "xvsb_cfpvarq.h"

CVSB_CFVarQFilter::CVSB_CFVarQFilter(CVSB_hCFnNode hCusor)
	: CVSB_CFNodeQBase(hCusor)
{
}

CVSB_CFVarQFilter::CVSB_CFVarQFilter(CVSB_hCFnNode hCusor, CVSB_Method* pOwner)
	: CVSB_CFNodeQBase(hCusor, pOwner)
{
}

CVSB_CFVarQFilter::CVSB_CFVarQFilter(CVSB_hCFnNode hCusor, CVSB_CFNodeQBase* prevQ)
	: CVSB_CFNodeQBase(hCusor, prevQ)
{
}

CVSB_CFVarQFilter::CVSB_CFVarQFilter(CVSB_hCFnNode hCusor, CVSB_CFnQMan* pQM)
	: CVSB_CFNodeQBase(hCusor, pQM)
{
}

CVSB_CFVarQFilter::CVSB_CFVarQFilter(CVSB_hCFnNode hCusor, CVSB_Method* pOwner, CVSB_CFNodeQBase* prevQ, CVSB_CFnQMan* pQM)
	: CVSB_CFNodeQBase(hCusor, pOwner, prevQ, pQM)
{
}

CVSB_CFVarQFilter::~CVSB_CFVarQFilter()
{
}

