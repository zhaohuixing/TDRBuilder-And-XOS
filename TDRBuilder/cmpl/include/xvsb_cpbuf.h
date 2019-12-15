// Project: Visual System Builder
//
// File Name: xvsb_cpbuf.h
//
// Description: The definition of the buffer handler class for parsing
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
#ifndef __XVSB_CPBUF_H__
#define __XVSB_CPBUF_H__

#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <stdio.h>

#include "xvsb_defs.h"
#include "xvsb_pre.h"


class IVSB_CPScanBufferHandle 
{
//@access:
public:
	IVSB_CPScanBufferHandle(){};
	virtual ~IVSB_CPScanBufferHandle(){};

	virtual bool StartUp(void) = 0;
	virtual bool ShutDown(void) = 0;
    virtual const wchar_t* GetBuffer(void) = 0;
	virtual bool IsDirectBuffer(void) = 0;
};

class XVSB_CLASS CVSB_CPTextBuffer : public IVSB_CPScanBufferHandle
{
public:
	CVSB_CPTextBuffer();
	CVSB_CPTextBuffer(const std::wstring& szSrc);
	CVSB_CPTextBuffer(const wchar_t* szSrc);
	virtual ~CVSB_CPTextBuffer();

public:
	virtual bool StartUp(void);
	virtual bool ShutDown(void);
    virtual const wchar_t* GetBuffer(void);
	virtual bool IsDirectBuffer(void);

	void SetSource(const std::wstring& szCode);
	void SetSource(const wchar_t* szCode);

public:
	std::wstring	m_SourceCode;
};


#endif