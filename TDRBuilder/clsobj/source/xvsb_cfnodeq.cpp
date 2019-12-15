// Project: Visual System Builder
//
// File Name: xvsb_cfnodeq.cpp
//
// Description: The definition of the class function process node queue object
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
#include "xvsb_cfnodeq.h"
#include "xvsb_float.h"
#include "xvsb_int.h"
#include "xvsb_byte.h"
#include "xvsb_char.h"
#include "xvsb_bool.h"
#include "xvsb_array.h"
#include "xvsb_fpconst.h"


CVSB_CFNodeQFilter::CVSB_CFNodeQFilter(CVSB_hCFnNode hCusor)
	: CVSB_CFNodeQBase(hCusor)
{
	m_OperandQ.clear();
	m_OperationQ.clear();
}

CVSB_CFNodeQFilter::CVSB_CFNodeQFilter(CVSB_hCFnNode hCusor, CVSB_Method* pOwner)
	: CVSB_CFNodeQBase(hCusor, pOwner)
{
	m_OperandQ.clear();
	m_OperationQ.clear();
}

CVSB_CFNodeQFilter::CVSB_CFNodeQFilter(CVSB_hCFnNode hCusor, CVSB_CFNodeQBase* prevQ)
	: CVSB_CFNodeQBase(hCusor, prevQ)
{
	m_OperandQ.clear();
	m_OperationQ.clear();
}

CVSB_CFNodeQFilter::CVSB_CFNodeQFilter(CVSB_hCFnNode hCusor, CVSB_CFnQMan* pQM)
	: CVSB_CFNodeQBase(hCusor, pQM)
{
	m_OperandQ.clear();
	m_OperationQ.clear();
}

CVSB_CFNodeQFilter::CVSB_CFNodeQFilter(CVSB_hCFnNode hCusor, CVSB_Method* pOwner, CVSB_CFNodeQBase* prevQ, CVSB_CFnQMan* pQM)
	: CVSB_CFNodeQBase(hCusor, pOwner, prevQ, pQM)
{
	m_OperandQ.clear();
	m_OperationQ.clear();
}

CVSB_CFNodeQFilter::~CVSB_CFNodeQFilter()
{
	m_OperandQ.clear();
	m_OperationQ.clear();
}

void CVSB_CFNodeQFilter::PushType(enXVSB_OPERATION& ot)
{
	m_OperationQ.push_back(ot);
}

void CVSB_CFNodeQFilter::PushVar(CVSB_hCFnNode* pd)
{
	m_OperandQ.push_back(*pd);
}

enXVSB_OPERATION CVSB_CFNodeQFilter::PopType(void)
{
	if(m_OperationQ.empty())
		return enXVSB_NONE;

	enXVSB_OPERATION ot = m_OperationQ.front();
	m_OperationQ.pop_front();
	return ot;
}

CVSB_hCFnNode CVSB_CFNodeQFilter::PopVar(void)
{
	if(m_OperandQ.empty())
		return NULL;

	CVSB_hCFnNode hVar = m_OperandQ.front();
	m_OperandQ.pop_front();
	return hVar;
}

enXVSB_OPERATION CVSB_CFNodeQFilter::PeekType(void)
{
	if(m_OperationQ.empty())
		return enXVSB_NONE;

	return m_OperationQ.front();
}

CVSB_hCFnNode CVSB_CFNodeQFilter::PeekVar(void)
{
	if(m_OperandQ.empty())
		return NULL;
	else
		return m_OperandQ.front();
}

int CVSB_CFNodeQFilter::GetTypeCount(void)
{
	return (int)m_OperationQ.size();
}

int CVSB_CFNodeQFilter::GetVarCount(void)
{
	return (int)m_OperandQ.size();
}

bool CVSB_CFNodeQFilter::AddInteger(__int64 n)
{
	bool bRet = false;

	//if((int)m_OperandQ.size() != 0)
	//	return bRet;

	CVSB_CFConstParamUnit* pPara = new CVSB_CFConstParamUnit(n);
	if(pPara == NULL)
		return bRet;

	bRet = AddOperand(pPara);

	return bRet;
}

bool CVSB_CFNodeQFilter::AddFloat(double d)
{
	bool bRet = false;

	//if((int)m_OperandQ.size() != 0)
	//	return bRet;

	CVSB_CFConstParamUnit* pPara = new CVSB_CFConstParamUnit(d);
	if(pPara == NULL)
		return bRet;

	bRet = AddOperand(pPara);

	return bRet;
}

bool CVSB_CFNodeQFilter::AddByte(unsigned char n)
{
	bool bRet = false;

	//if((int)m_OperandQ.size() != 0)
	//	return bRet;

	CVSB_CFConstParamUnit* pPara = new CVSB_CFConstParamUnit(n);
	if(pPara == NULL)
		return bRet;

	bRet = AddOperand(pPara);

	return bRet;
}

bool CVSB_CFNodeQFilter::AddBooleanConstant(bool bConst)
{
	bool bRet = false;

	//if((int)m_OperandQ.size() != 0)
	//	return bRet;

	CVSB_CFConstParamUnit* pPara = new CVSB_CFConstParamUnit(bConst);
	if(pPara == NULL)
		return bRet;

	bRet = AddOperand(pPara);

	return bRet;
}

bool CVSB_CFNodeQFilter::AddMathOp(enXVSB_OPERATION op)
{
	bool bRet = false;

	return bRet;
}

bool CVSB_CFNodeQFilter::AddOperand(CVSB_CFParamUnitBase* pOp)
{
	bool bRet = false;

	CVSB_CFnNode* pNode = new CVSB_CFnNode(pOp, m_hCusor, enXVSB_LEVEL_ROOT, enXVSB_NONE);
	if(pNode)
	{
		m_OperandQ.push_back(pNode);
		bRet = true;
	}

	return bRet;
}