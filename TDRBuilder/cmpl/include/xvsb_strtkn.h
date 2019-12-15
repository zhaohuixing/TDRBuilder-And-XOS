// Project: Visual System Builder
//
// File Name: xvsb_strtkn.h
//
// Description: The definition of the string type token class for 
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
#ifndef __XVSB_STRTKN_H__
#define __XVSB_STRTKN_H__

#include "ivsb_cptkn.h"
#include "xvsb_pre.h"

////////////////////////////////////////////////////////
//  CVSB_StringToken: Token class for string.
////////////////////////////////////////////////////////
class XVSB_CLASS CVSB_StringToken : public IVSB_CPToken
{
public:
	CVSB_StringToken();

public:
	virtual void Get(IVSB_ScanBufferBase &buffer);
    virtual bool IsDelimiter(void) const;
	virtual void Print(IVSB_TextOutBuffer * pOut = NULL) const;
	virtual	bool Translate(IVSB_Translator* pTrans);
};


#endif