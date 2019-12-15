// Project: Visual System Builder
//
// File Name: xvsb_eoftkn.h
//
// Description: The definition of the EOF flag token class for 
//				expression parsing.	
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
#ifndef __XVSB_EOFTKN_H__
#define __XVSB_EOFTKN_H__

#include "ivsb_cptkn.h"
#include "xvsb_pre.h"

////////////////////////////////////////////////////////
//  CVSB_EOFToken: Token class for EOF flag.
////////////////////////////////////////////////////////
class XVSB_CLASS CVSB_EOFToken : public IVSB_CPToken
{
public:
	CVSB_EOFToken();

public:
	virtual void Get(IVSB_ScanBufferBase &buffer);
    virtual bool IsDelimiter(void) const;
	virtual void Print(IVSB_TextOutBuffer * pOut = NULL) const;
	virtual	bool Translate(IVSB_Translator* pTrans);
};


#endif