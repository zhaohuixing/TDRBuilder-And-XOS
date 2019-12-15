// Project: Visual System Builder
//
// File Name: xvsb_tknchk.h
//
// Description: The definition of the token check class
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
#ifndef __XVSB_TKNCHK_H__
#define __XVSB_TKNCHK_H__

#include "xvsb_pre.h"
#include "xvsb_cpdefs.h"
#include "xvsb_defs.h"

class XVSB_CLASS CVSB_TokenCheck
{
public:
	static bool IsBuildInTypeToken(enXVSB_CPTKNCODE token); 
	static bool IsMathOpToken(enXVSB_CPTKNCODE token); 
	static bool IsLogicCmpToken(enXVSB_CPTKNCODE token); 
	static bool IsLogicLnkToken(enXVSB_CPTKNCODE token);

	static enXVSB_OPERATION GetMathOpByToken(enXVSB_CPTKNCODE token);
};

#endif