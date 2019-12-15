// Project: Visual System Builder
//
// File Name: xvsb_errtkn.h
//
// Description: The definition of the error flag token class for 
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
#ifndef __XVSB_ERRTKN_H__
#define __XVSB_ERRTKN_H__

#include "ivsb_cptkn.h"
#include "xvsb_pre.h"

////////////////////////////////////////////////////////
//  CVSB_ErrorToken: Token class for error flag.
////////////////////////////////////////////////////////
class XVSB_CLASS CVSB_ErrorToken : public IVSB_CPToken
{
public:
	CVSB_ErrorToken();

public:
	virtual void Get(IVSB_ScanBufferBase &buffer);
    virtual bool IsDelimiter(void) const;
	virtual void Print(IVSB_TextOutBuffer * pOut = NULL) const;
	virtual	bool Translate(IVSB_Translator* pTrans);
};


#endif