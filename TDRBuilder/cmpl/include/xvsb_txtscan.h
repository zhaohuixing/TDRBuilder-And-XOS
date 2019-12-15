// Project: Visual System Builder
//
// File Name: xvsb_txtscan.h
//
// Description: The definition of the text scanner class.	
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
#ifndef __XVSB_TXTSCAN_H__
#define __XVSB_TXTSCAN_H__

#include "ivsb_scan.h"
#include "ivsb_inbuf.h"
#include "xvsb_pre.h"

class XVSB_CLASS CVSB_TextScanner : public IVSB_ScanBase
{
//
//@access: Contruction/Destruction:
//
public:
	//@cmember: Constructor
	CVSB_TextScanner(IVSB_ScanBufferBase *pBuffer);

	//@cmember: Destructor
	virtual ~CVSB_TextScanner(void);

//
//@access: Operations:
//
public:
	//@cmember: Check current scan line position
	virtual int GetCurrentScanLineNumber(void);

	//@cmember: Check current scan position in current line position
	virtual int GetCurrentPos(void);

	//@cmember: Begin process
	virtual bool StartUp(void);

	//@cmember: End process
	virtual bool ShutDown(void);

	//@cmember: Get token object
    virtual IVSB_CPToken* Get(void);

	//@cmember: Attachment the input buffer
	void SetInputBuffer(IVSB_ScanBufferBase* pBuf);

//
//@access: Implementations:
//
private:
	//@cmember: Skip whitspace
    void _skipwhitespace(void);

//
//@access: Attributes
//
private:
	//@cmember: Input buffer object
    IVSB_ScanBufferBase*	m_pInputBuffer;  // ptr to input text buffer to scan

};

#endif