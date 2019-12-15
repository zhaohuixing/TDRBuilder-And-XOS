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
#include <stdlib.h>
#include "xvsb_ccmap.h"
#include "xvsb_wcutil.h"

static enXVSB_CPCCODE charCodeMap[128];
static bool isInit = false;

bool CVSB_CharCodeMap::IsInit(void)
{
	return isInit;
}

void CVSB_CharCodeMap::Initialize(void)
{
    int i;

    //--Initialize the character code map.
    for (i = 0; i <= 127; ++i) 
		charCodeMap[i] = enXVSB_CCERROR;

    //--from '!'(33) 
    for (i = 33; i < 127; ++i) 
		charCodeMap[i] = enXVSB_CCSPECIAL;

	// from 'a'(97) to 'z'(122) 
    for (i = 97; i <= 122; ++i) 
		charCodeMap[i] = enXVSB_CCLETTER;

	// from 'A'(65) to 'Z'(90) 
    for (i = 65; i <= 90; ++i) 
		charCodeMap[i] = enXVSB_CCLETTER;

	// sign '_' (95)
	charCodeMap[95] = enXVSB_CCLETTER;

	// from '0'(48) to '9'(57) 
    for (i = 48; i <= 57; ++i) 
		charCodeMap[i] = enXVSB_CCDIGIT;

	charCodeMap[WC2Char(L' ')] = charCodeMap[WC2Char(L'\t')] = enXVSB_CCWHITESPACE;
    
	charCodeMap[WC2Char(L'\n')] = charCodeMap[WC2Char(L'\0')] = enXVSB_CCWHITESPACE;

	charCodeMap[WC2Char(L'\'')] = enXVSB_CCQUOTE;
    
	// 0x7F (127) end of file sign
	charCodeMap[127] = enXVSB_CCEOF;

	isInit = true;
}

void CVSB_CharCodeMap::SetCCode(int idx, enXVSB_CPCCODE ccode)
{
	if(0 <= idx && idx < 128)
	{
		charCodeMap[idx] = ccode;
	}
}

enXVSB_CPCCODE CVSB_CharCodeMap::GetCCode(int idx)
{
	if(0 <= idx && idx < 128)
	{
		return charCodeMap[idx];
	}
	else
	{
		return enXVSB_CCERROR; 
	}
}

