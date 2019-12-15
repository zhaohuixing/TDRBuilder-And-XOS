// Project: Visual System Builder
//
// File Name: xvsb_cfqman.h
//
// Description: The definition of the class member function node stack queue manager class
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 05/19/2005	
//
// History:
// 1.    05/19/2005: Create	
//
#ifndef __XVSB_CFQMAN_H__
#define __XVSB_CFQMAN_H__

#include "xvsb_cfstack.h"

class XVSB_CLASS CVSB_CFnQMan
{
public:
	CVSB_CFnQMan(CVSB_Method* pOwner = NULL);
	virtual ~CVSB_CFnQMan();

public:
	bool IsInProcess(void);
	CVSB_hCFnNode GetExpression(void);
	void Reset(void);
	bool StartRoot(void);
	bool EndRoot(void);

	void AttachOwner(CVSB_Method* pOwner);
	bool AddInteger(__int64 n);
	bool AddFloat(double d);
	bool AddByte(unsigned char n);
	bool AddVariable(std::wstring& szVar);
	bool AddVariable(const wchar_t* szVar);
	bool AddBooleanConstant(bool bConst);
	bool AddMathOp(enXVSB_OPERATION op);
	bool AddLParen(void);
	bool AddRParen(void);
	bool AddLBracket(void);
	bool AddRBracket(void);
	bool AddComma(void);
	bool AddDot(void);

protected:
	void CleanQ(void);

protected:
	CVSB_CFNodeQStack	m_stackQ;
	CVSB_Method*		m_hOwner;
	CVSB_hCFnNode		m_hExpress;
	bool				m_IsShared; 
	bool				m_bInProcess;
};

#endif