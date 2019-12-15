// Project: Visual System Builder
//
// File Name: ivsb_cufile.h
//
// Description: The definition of the class object unit file handler interface class
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 05/11/2005	
//
// History:
// 1.    05/11/2005: Create	
//
#ifndef __IVSB_CUFILE_H__
#define __IVSB_CUFILE_H__

#include "xvsb_pre.h"
#include <string>
#include "xvsb_clsunit.h"

class XVSB_CLASS IVSB_CUFileHandler
{
public:
	IVSB_CUFileHandler(){};
	virtual ~IVSB_CUFileHandler(){};
	
public:
	virtual CVSB_ClassUnit* LoadUnit(std::wstring& file, std::wstring& path) = 0;
	virtual CVSB_ClassUnit* LoadUnit(const wchar_t* file, const wchar_t* path) = 0;

};

#endif