// Project: Visual System Builder
//
// File Name: xvsb_tknlut.h
//
// Description: The definition of the token constant look-up table creation 
//				helper class for expression parsing.
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/24/2005	
//
// History:
// 1.    01/24/2005: Create	
//
#pragma warning(disable:4530)
#ifndef __XVSB_TKNLUT_H__
#define __XVSB_TKNLUT_H__

#include "xvsb_cpdefs.h"
#include "xvsb_pre.h"

class XVSB_CLASS CVSB_WordTokenGenerator
{
public:
	CVSB_WordTokenGenerator(){};
	void operator ()(CVSB_TokenLUT* pTLUT);
};

class XVSB_CLASS CVSB_SignTokenGenerator
{
public:
	CVSB_SignTokenGenerator(){};
	void operator ()(CVSB_WCTokenLUT* pTLUT);
};

#endif