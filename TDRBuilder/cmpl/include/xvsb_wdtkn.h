// Project: Visual System Builder
//
// File Name: xvsb_wdtkn.h
//
// Description: The definition of the word type token class for 
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
#ifndef __XVSB_WDTKN_H__
#define __XVSB_WDTKN_H__

#include "ivsb_cptkn.h"
#include "xvsb_pre.h"

////////////////////////////////////////////////////////
//  CVSB_WordToken: Token class for integer.
////////////////////////////////////////////////////////
class XVSB_CLASS CVSB_WordToken : public IVSB_CPToken
{
protected:
    void CheckForReservedWord(void);

protected:
	CVSB_TokenLUT			m_TknLUT;

public:
	CVSB_WordToken();

public:
	virtual void Get(IVSB_ScanBufferBase &buffer);
    virtual bool IsDelimiter(void) const;
	virtual void Print(IVSB_TextOutBuffer * pOut = NULL) const;
	virtual	bool Translate(IVSB_Translator* pTrans);
};


#endif