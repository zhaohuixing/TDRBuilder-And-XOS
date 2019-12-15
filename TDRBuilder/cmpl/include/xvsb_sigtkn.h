// Project: Visual System Builder
//
// File Name: xvsb_sigtkn.h
//
// Description: The definition of the special sign type token class for 
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
#ifndef __XVSB_SIGTKN_H__
#define __XVSB_SIGTKN_H__

#include "ivsb_cptkn.h"
#include "xvsb_pre.h"

////////////////////////////////////////////////////////
//  CVSB_SpecialToken: Token class for special sign.
////////////////////////////////////////////////////////
class XVSB_CLASS CVSB_SpecialToken : public IVSB_CPToken
{
protected:
	CVSB_WCTokenLUT			m_TknLUT;

public:
	CVSB_SpecialToken();

public:
	virtual void Get(IVSB_ScanBufferBase &buffer);
    virtual bool IsDelimiter(void) const;
	virtual void Print(IVSB_TextOutBuffer * pOut = NULL) const;
	virtual	bool Translate(IVSB_Translator* pTrans);
};


#endif