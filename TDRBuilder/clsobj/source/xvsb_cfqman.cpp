// Project: Visual System Builder
//
// File Name: xvsb_cfqman.cpp
//
// Description: The implementation of the class member function node stack queue manager class
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
#include "xvsb_cfqman.h"
#include "xvsb_cfpvarq.h"
#include "xvsb_cfnodeq.h"

CVSB_CFnQMan::CVSB_CFnQMan(CVSB_Method* pOwner)
{
	m_hOwner = pOwner;
	m_hExpress = NULL;
	m_IsShared = false; 
	m_bInProcess = false;
}

CVSB_CFnQMan::~CVSB_CFnQMan()
{
	m_hOwner = NULL;
	Reset();
}

bool CVSB_CFnQMan::IsInProcess(void)
{
	return m_bInProcess;
}

CVSB_hCFnNode CVSB_CFnQMan::GetExpression(void)
{
	if(m_bInProcess == true)
	{
		// In expression creation process, 
		// locking the access to the expression handle
		return NULL;
	}
	else
	{
		m_IsShared = true;     
		return m_hExpress;     
	}
}

void CVSB_CFnQMan::Reset(void)
{
	if(m_hExpress != NULL)
	{
		if(m_IsShared == false)
		{
			delete m_hExpress;
		}
		m_hExpress = NULL;
	}
	CleanQ();
	m_IsShared = false; 
	m_bInProcess = false;
}

bool CVSB_CFnQMan::StartRoot(void)
{
	bool bRet = false;
	Reset();

	m_hExpress = new CVSB_CFnNode();
	m_hExpress->AttachOwner(m_hOwner);
	m_hExpress->Reset(enXVSB_LEVEL_ROOT, enXVSB_NONE);

	CVSB_CFNodeQFilter* pFNodeQ = new CVSB_CFNodeQFilter(m_hExpress, m_hOwner, NULL, this);
    if(pFNodeQ)
	{
		enXVSB_OPERATION Op = enXVSB_NONE;
		pFNodeQ->PushType(Op);
		m_stackQ.push(pFNodeQ);
		m_bInProcess = true;
		bRet = true;
	}

	return bRet;
}

bool CVSB_CFnQMan::EndRoot(void)
{
	bool bRet = false;

/*
	if(m_hExpress && m_hCusor && m_opFilter.IsValid() && m_bInProcess)
	{
		bRet = AddOperation(enXVSB_NONE);
	}

	m_opFilter.RemoveTailAction();
	m_hCusor = m_hExpress;
	m_bInProcess = false;
*/
	m_bInProcess = false;

	return bRet;
}


void CVSB_CFnQMan::AttachOwner(CVSB_Method* hOwner)
{
	if(hOwner == NULL)
	{
#ifdef _XSVM_DEBUG_
		assert(false);
#endif
		return;
	}
	else
	{
		m_hOwner = hOwner;
	}
}

bool CVSB_CFnQMan::AddInteger(__int64 n)
{
	bool bRet = false;
	CVSB_CFNodeQBase* q = m_stackQ.top();
	if(q)
	{
		if(q->GetQtype() == enXVSB_NODEQ_NODE)
		{
			CVSB_CFNodeQFilter* pFNodeQ = (CVSB_CFNodeQFilter*)q;
			bRet = pFNodeQ->AddInteger(n);
		}
	}

	return bRet;
}

bool CVSB_CFnQMan::AddFloat(double d)
{
	bool bRet = false;
	CVSB_CFNodeQBase* q = m_stackQ.top();
	if(q)
	{
		if(q->GetQtype() == enXVSB_NODEQ_NODE)
		{
			CVSB_CFNodeQFilter* pFNodeQ = (CVSB_CFNodeQFilter*)q;
			bRet = pFNodeQ->AddFloat(d);
		}
	}

	return bRet;
}

bool CVSB_CFnQMan::AddByte(unsigned char n)
{
	bool bRet = false;
	CVSB_CFNodeQBase* q = m_stackQ.top();
	if(q)
	{
		if(q->GetQtype() == enXVSB_NODEQ_NODE)
		{
			CVSB_CFNodeQFilter* pFNodeQ = (CVSB_CFNodeQFilter*)q;
			bRet = pFNodeQ->AddByte(n);
		}
	}

	return bRet;
}

bool CVSB_CFnQMan::AddVariable(std::wstring& szVar)
{
	bool bRet = false;
	CVSB_CFNodeQBase* q = m_stackQ.top();
	if(q)
	{
	}

	return bRet;
}

bool CVSB_CFnQMan::AddVariable(const wchar_t* szVar)
{
	bool bRet = false;
	std::wstring szTemp = szVar;
	bRet = AddVariable(szTemp);
	return bRet;
}

bool CVSB_CFnQMan::AddBooleanConstant(bool bConst)
{
	bool bRet = false;
	CVSB_CFNodeQBase* q = m_stackQ.top();
	if(q)
	{
		if(q->GetQtype() == enXVSB_NODEQ_NODE)
		{
			CVSB_CFNodeQFilter* pFNodeQ = (CVSB_CFNodeQFilter*)q;
			bRet = pFNodeQ->AddBooleanConstant(bConst);
		}
	}

	return bRet;
}

bool CVSB_CFnQMan::AddMathOp(enXVSB_OPERATION op)
{
	bool bRet = false;
	CVSB_CFNodeQBase* q = m_stackQ.top();
	if(q)
	{
		if(q->GetQtype() == enXVSB_NODEQ_NODE)
		{
			CVSB_CFNodeQFilter* pFNodeQ = (CVSB_CFNodeQFilter*)q;
			bRet = pFNodeQ->AddMathOp(op);
		}
	}

	return bRet;
}

bool CVSB_CFnQMan::AddLParen(void)
{
	bool bRet = false;

	return bRet;
}

bool CVSB_CFnQMan::AddRParen(void)
{
	bool bRet = false;

	return bRet;
}

bool CVSB_CFnQMan::AddLBracket(void)
{
	bool bRet = false;

	return bRet;
}

bool CVSB_CFnQMan::AddRBracket(void)
{
	bool bRet = false;

	return bRet;
}

bool CVSB_CFnQMan::AddComma(void)
{
	bool bRet = false;

	return bRet;
}

bool CVSB_CFnQMan::AddDot(void)
{
	bool bRet = false;

	return bRet;
}

void CVSB_CFnQMan::CleanQ(void)
{
	while(!m_stackQ.empty())
	{
		CVSB_CFNodeQBase* p = m_stackQ.top();
		if(p)
		{
			delete p;
			p = NULL;
		}
		m_stackQ.pop();		
	}
}
