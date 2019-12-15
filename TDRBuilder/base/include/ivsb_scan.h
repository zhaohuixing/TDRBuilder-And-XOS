// Project: Visual System Builder
//
// File Name: ivsb_scan.h
//
// Description: The definition of the interface class for scanner.	
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/25/2005	
//
// History:
// 1.    01/25/2005: Create	
//
#ifndef __IVSB_SCAN_H__
#define __IVSB_SCAN_H__

#include "xvsb_wdtkn.h"
#include "xvsb_numtkn.h"
#include "xvsb_strtkn.h"
#include "xvsb_sigtkn.h"
#include "xvsb_eoftkn.h"
#include "xvsb_errtkn.h"


class IVSB_ScanBase
{
public:
	IVSB_ScanBase(void){};
	virtual ~IVSB_ScanBase(void){};

public:
	virtual int GetCurrentScanLineNumber(void) = 0;
	virtual bool StartUp(void) = 0;
	virtual bool ShutDown(void) = 0;
    virtual IVSB_CPToken* Get(void) = 0;

protected:
    CVSB_WordToken    m_wordToken;
    CVSB_NumberToken  m_numberToken;
    CVSB_StringToken  m_stringToken;
    CVSB_SpecialToken m_specialToken;
    CVSB_EOFToken     m_eofToken;
    CVSB_ErrorToken   m_errorToken;
};

#endif