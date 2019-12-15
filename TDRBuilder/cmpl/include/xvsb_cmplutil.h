// Project: Visual System Builder
//
// File Name: xvsb_cmplutil.h
//
// Description: The definition of the compiler operation utility class
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 05/20/2005	
//
// History:
// 1.    05/20/2005: Create	
//
#ifndef __XVSB_CMPLUTIL_H__
#define __XVSB_CMPLUTIL_H__

#include "xvsb_pre.h"
#include "xvsb_defs.h"

class XVSB_CLASS CVSB_CMPLUtility
{
public:
	static bool IsSameLevel(enXVSB_OPERATION mType1, enXVSB_OPERATION mType2);
	static int LevelDifference(enXVSB_OPERATION mType1, enXVSB_OPERATION mType2);
	static enXVSB_PRIORITY GetOperationLevel(enXVSB_OPERATION mType);
	static bool NeedParen(enXVSB_OPERATION op);
};

#endif