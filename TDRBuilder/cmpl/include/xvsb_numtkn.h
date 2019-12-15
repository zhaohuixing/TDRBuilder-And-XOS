// Project: Visual System Builder
//
// File Name: xvsb_numtkn.h
//
// Description: The definition of the numeric type token class for 
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
#ifndef __XVSB_NUMTKN_H__
#define __XVSB_NUMTKN_H__

#include "ivsb_cptkn.h"
#include "xvsb_pre.h"

////////////////////////////////////////////////////////
//  CVSB_NumberToken: Token class for numeric.
////////////////////////////////////////////////////////
class XVSB_CLASS CVSB_NumberToken : public IVSB_CPToken
{
protected:
    wchar_t		m_ch;              // char fetched from input buffer
    int			m_digitCount;      // total no. of digits in number
    bool		m_countErrorFlag;  // true if too many digits, else false

protected:
    bool AccumulateValue(IVSB_ScanBufferBase &buffer, double &value);

public:
	CVSB_NumberToken();

public:
	virtual void Get(IVSB_ScanBufferBase &buffer);
    virtual bool IsDelimiter(void) const;
	virtual void Print(IVSB_TextOutBuffer * pOut = NULL) const;
	virtual	bool Translate(IVSB_Translator* pTrans);
};


#endif