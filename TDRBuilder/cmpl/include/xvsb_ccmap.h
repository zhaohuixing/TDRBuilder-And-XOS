// Project: Visual System Builder
//
// File Name: xvsb_ccmap.h
//
// Description: The definition of the character code map class for 
//				expression parsing
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Reference: Ronald Mak "Writing Compilers and Interpreters" 2nd Edition.
//			  Publisher: John Wiley & Sons, Inc.	
//			  ISBN: 0-471-11353-0	
//
// Creation Date: 01/24/2005	
//
// History:
// 1.    01/24/2005: Create	
//
#pragma warning(disable:4530)
#ifndef __XVSB_CCMAP_H__
#define __XVSB_CCMAP_H__

#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>

#include "xvsb_cpdefs.h"
#include "xvsb_pre.h"

class XVSB_CLASS CVSB_CharCodeMap
{
public:
	static void Initialize(void);
	static bool IsInit(void);
	static void SetCCode(int idx, enXVSB_CPCCODE ccode);
	static enXVSB_CPCCODE GetCCode(int idx);

public:
};

#endif