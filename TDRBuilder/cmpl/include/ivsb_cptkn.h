// Project: Visual System Builder
//
// File Name: ivsb_cptkn.h
//
// Description: The definition of the abstrct interface of the token class for 
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
#pragma warning(disable:4530)
#ifndef __IVSB_CPTKN_H__
#define __IVSB_CPTKN_H__

#include "ivsb_inbuf.h"
#include "ivsb_cpobuf.h"
#include "ivsb_cptrans.h"
#include "xvsb_cpdefs.h"
#include <string>

////////////////////////////////////////////////////////
//  IVSB_CPToken: Token base class.
////////////////////////////////////////////////////////
class IVSB_CPToken
{
protected:
    enXVSB_CPTKNCODE 	m_TokenCode;
    enXVSB_CPDATATTYPE	m_DataType;
    unXVSB_CPDATAVALUE	m_DataValue;
    std::wstring		m_String;

public:
    IVSB_CPToken(void)
    {
		m_TokenCode = enXVSB_TCDUMMY;
		m_DataType = enXVSB_TYDUMMY;
		m_DataValue.m_Integer = 0;
		m_String.clear();
    }

	enXVSB_CPTKNCODE	Code()   const {return m_TokenCode;}
    enXVSB_CPDATATTYPE  Type()   const {return m_DataType;}
    unXVSB_CPDATAVALUE  Value()  const {return m_DataValue;}
	const wchar_t*	  String() const {return m_String.c_str();}
	std::wstring	  String() {return m_String;}	

    virtual void Get(IVSB_ScanBufferBase &buffer) = 0;
    virtual bool IsDelimiter(void) const = 0;
    virtual void Print(IVSB_TextOutBuffer * pOut = NULL) const = 0;
	virtual	bool Translate(IVSB_Translator* pTrans) = 0;
};


#endif