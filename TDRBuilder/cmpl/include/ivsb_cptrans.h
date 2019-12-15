// Project: Visual System Builder
//
// File Name: ivsb_cptrans.h
//
// Description: The definition of the interface of the source code translator 
//              which translates the parsing out token information into the
//				expression structure.
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
#ifndef __IVSB_CPTRANS_H__
#define __IVSB_CPTRANS_H__

#include "xvsb_cpdefs.h"
#include "xvsb_defs.h"

class IVSB_Translator
{
public:
	IVSB_Translator(){};
	virtual ~IVSB_Translator(){};

public:
	virtual bool TranslateToken(const enXVSB_CPTKNCODE& ct, const enXVSB_CPDATATTYPE& cdt, const unXVSB_CPDATAVALUE& dv) = 0;
	virtual bool StartUp(void) = 0;
	virtual bool End(void) = 0;
	virtual enXVSB_ERRORCODE GetError(void) = 0;
	virtual std::wstring GetErrorInfo(void) = 0;
	virtual const wchar_t* GetErrorInfo(void) const = 0;
};

#endif