// Project: Visual System Builder
//
// File Name: xvsb_fnode.cpp
//
// Description: The implementation of the class function object internal expression node
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 05/13/2005	
//
// History:
// 1.    05/13/2005: Create	
//
//#include "stdafx.h"
#include "xvsb_fnode.h"
//#include "xvsb_array.h"

CVSB_CFnNode::CVSB_CFnNode(void) 
{
	m_Operand = NULL;
	m_SubOps.clear();
	m_pParent = NULL;
	m_hOwner = NULL;
	m_Operate = enXVSB_NONE;
	m_pResult = NULL;
	m_Level = enXVSB_LEVEL_NONE;
	m_bSubRootNode = false;
}

CVSB_CFnNode::CVSB_CFnNode(CVSB_CFnNode* pParent, enXVSB_PRIORITY lvl, enXVSB_OPERATION oType)
{
	m_Operand = NULL;
	m_SubOps.clear();
	m_pParent = pParent;
	m_hOwner = NULL;
	m_Operate = oType;
	m_pResult = NULL;
	m_Level = lvl;
	m_bSubRootNode = false;
}

CVSB_CFnNode::CVSB_CFnNode(CVSB_CFParamUnitBase* param, CVSB_CFnNode* pParent, enXVSB_PRIORITY lvl, enXVSB_OPERATION oType)
{
	m_Operand = param;
	m_SubOps.clear();
	m_pParent = pParent;
	m_hOwner = NULL;
	m_Operate = oType;
	m_pResult = NULL;
	m_Level = lvl;
	m_bSubRootNode = false;
}

CVSB_CFnNode::~CVSB_CFnNode(void)
{
	Clear();
}

void CVSB_CFnNode::Clear(void)
{
	CleanBuffer();
	CleanSubRootFlag();
}

void CVSB_CFnNode::CleanBuffer(void)
{
	CVSB_CFnNodeFree expFree;
	expFree(m_SubOps);

	if(m_pResult)
	{
		delete m_pResult;
		m_pResult = NULL;
	}

	if(m_Operand)
	{
		delete m_Operand;
		m_Operand = NULL;
	}
}

CVSB_CFnNode::operator IVSB_DataBase* ()
{
	return m_pResult;
}

IVSB_DataBase* CVSB_CFnNode::GetResult(void)
{
	return m_pResult;
}

void CVSB_CFnNode::SetAsSubRoot(void)
{
	m_bSubRootNode = true;
}

void CVSB_CFnNode::CleanSubRootFlag(void)
{
	m_bSubRootNode = false;
}

void CVSB_CFnNode::AddSubOp(CVSB_CFnNode* subOp)
{
#ifdef _XSVM_DEBUG_
	assert(subOp != NULL);
#endif
	if(subOp != NULL)
		m_SubOps.push_back(subOp);
}

bool CVSB_CFnNode::Reset(enXVSB_PRIORITY lvl, enXVSB_OPERATION oType)
{
	m_Operate = oType;
	m_Level = lvl;
	return true;
}

bool CVSB_CFnNode::IsDirty(void)
{
	return (!m_SubOps.empty());
}

enXVSB_PRIORITY CVSB_CFnNode::GetLevel(void)
{
	return m_Level;
}

void CVSB_CFnNode::SetLevel(enXVSB_PRIORITY lvl)
{
	m_Level = lvl;
}

enXVSB_OPERATION CVSB_CFnNode::GetOperation(void)
{
	return m_Operate;
}

void CVSB_CFnNode::SetOperation(enXVSB_OPERATION op)
{
	m_Operate = op;
}

void CVSB_CFnNode::SetParentNode(CVSB_CFnNode* pParent)
{
	m_pParent = pParent;
}

bool CVSB_CFnNode::IsSubOpSimple(void)
{
	bool bRet = true;

	if(m_SubOps.empty())
		return bRet;

	CVSB_CFnNodeList::iterator iter;
	for(iter = m_SubOps.begin(); iter != m_SubOps.end(); iter++)
	{
		if((*iter)->IsDirty() || ((*iter)->m_Level == enXVSB_LEVEL_ROOT || (*iter)->m_bSubRootNode == true))
		{
			bRet = false;
			return bRet;
		}
	}

	return bRet;
}

bool CVSB_CFnNode::HasRootNode(void)
{
	bool bRet = false;

	if(m_Level == enXVSB_LEVEL_ROOT || m_bSubRootNode == true)
		return !bRet;

	if(m_SubOps.empty())
		return bRet;

	CVSB_CFnNodeList::iterator iter;
	for(iter = m_SubOps.begin(); iter != m_SubOps.end(); iter++)
	{
		if((*iter)->HasRootNode() == true)
		{
			bRet = true;
			return bRet;
		}
	}

	return bRet;
}

void CVSB_CFnNode::SetOperand(CVSB_CFParamUnitBase* param)
{
	if(param)
	{
		if(m_Operand)
		{
			delete m_Operand;
			m_Operand = NULL;
		}
		m_Operand = param;
	}
}

bool CVSB_CFnNode::AttachVarOperand(IVSB_DataBase* pData)
{
	bool bRet = true;
	//return m_Operand.AttachVar(pData);

	return bRet;
}

void CVSB_CFnNode::AttachOwner(CVSB_Method* hOwner)
{
	m_hOwner = hOwner;
	if(!m_SubOps.empty())
	{
		CVSB_CFnNodeList::iterator iter;
		for(iter = m_SubOps.begin(); iter != m_SubOps.end(); iter++)
		{
			(*iter)->AttachOwner(hOwner);
		}
	}

	if(m_Operand)
	{
		m_Operand->SetOwner(hOwner);
	}
}

bool CVSB_CFnNode::ResetResult(void)
{
	if(m_pResult)
	{
		delete m_pResult;
		m_pResult = NULL;
	}
	CVSB_CFnNodeList::iterator iter;
	for(iter = m_SubOps.begin(); iter != m_SubOps.end(); iter++)
	{
		(*iter)->ResetResult();
	}

	return true;
}

bool CVSB_CFnNode::Run(IVSB_DataBase* pInPrev)
{
	bool bRet = false;
	IVSB_DataBase* pOperand = NULL;
	IVSB_DataBase* pTemp = NULL;

	if(IsDirty())
	{
		CVSB_CFnNodeList::iterator iter;
		for(iter = m_SubOps.begin(); iter != m_SubOps.end(); ++iter)
		{
			if((*iter)->Run(pOperand))
			{
				pOperand = (*iter)->GetResult();
			}
		}

		if(pOperand)
		{
			pTemp = pOperand;
		}
		else 
		{
#ifdef _XSVM_DEBUG_
			assert(false);
#endif
		}

	}
	else
	{
		if(m_Level != enXVSB_LEVEL_ROOT)
		{
			if(m_Operand)
				pTemp = m_Operand->GetParamObject();
		}

	}


	if(pTemp == NULL && m_Level != enXVSB_LEVEL_ROOT)
	{
		if(m_Level == enXVSB_LEVEL1 && m_Operate == enXVSB_NONE)
		{
			bRet = true;
			return bRet;
		}
		else
		{
			bRet = false;
			return bRet;
		}
	}

	//assert(pTemp != NULL);
	bRet = _calculate(pInPrev, pTemp);

	return bRet;
}

bool CVSB_CFnNode::_calculate(IVSB_DataBase* pInput, IVSB_DataBase* pOperand)
{
	bool bRet = false;

#ifdef _XSVM_DEBUG_
	assert(pOperand != NULL);
#endif
	if(pOperand == NULL)
		return bRet;

	//?????????????????????????????????????? 
	//?????????????????????????????????????? Update the clone m_pResult method later
	//?????????????????????????????????????? 	
	switch(m_Operate)
	{
		case enXVSB_NONE:
			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = true;
			break;
		case enXVSB_ARG:
//			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = pOperand->Arg(&m_pResult);
			break;
		case enXVSB_POLAR:
//			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = pOperand->Polar(&m_pResult);
			break;
		case enXVSB_ABS:
//			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = pOperand->Abs(&m_pResult);
			break;
		case enXVSB_PLUS:
//#ifdef _XSVM_DEBUG_
//			assert(pInput != NULL);
//#endif
//			if(pInput == NULL)
//			{
//				return bRet;
//			}
//			pInput->Clone((IVSB_Base **)&m_pResult);
			if(pInput != NULL) 
			{
				bRet = pInput->Plus(pOperand, &m_pResult);
			}
			else
			{
				pOperand->Clone((IVSB_Base **)&m_pResult);
				bRet = true;
			}
			break;
		case enXVSB_MINUS:
//#ifdef _XSVM_DEBUG_
//			assert(pInput != NULL);
//#endif
//			if(pInput == NULL)
//			{
//				return bRet;
//			}
//			pInput->Clone((IVSB_Base **)&m_pResult);
			if(pInput != NULL) 
				bRet = pInput->Minus(pOperand, &m_pResult);
			else
				bRet = pOperand->Negative(&m_pResult);
			break;
		case enXVSB_TIME:
#ifdef _XSVM_DEBUG_
			assert(pInput != NULL);
#endif
			if(pInput == NULL)
			{
				return bRet;
			}
//			pInput->Clone((IVSB_Base **)&m_pResult);
			bRet = pInput->Time(pOperand, &m_pResult);
			break;
		case enXVSB_DIVIDE:
#ifdef _XSVM_DEBUG_
			assert(pInput != NULL);
#endif
			if(pInput == NULL)
			{
				return bRet;
			}
//			pInput->Clone((IVSB_Base **)&m_pResult);
			bRet = pInput->Divide(pOperand, &m_pResult);
			break;
		case enXVSB_SIN:
//			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = pOperand->Sin(&m_pResult);
			break;
		case enXVSB_SINH:
//			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = pOperand->SinH(&m_pResult);
			break;
		case enXVSB_ASIN:
//			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = pOperand->ASin(&m_pResult);
			break;
		case enXVSB_CSC:
//			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = pOperand->Csc(&m_pResult);
			break;
		case enXVSB_CSCH:
//			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = pOperand->CscH(&m_pResult);
			break;
		case enXVSB_COS:
//			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = pOperand->Cos(&m_pResult);
			break;
		case enXVSB_COSH:
//			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = pOperand->CosH(&m_pResult);
			break;
		case enXVSB_ACOS:
//			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = pOperand->ACos(&m_pResult);
			break;
		case enXVSB_SEC:
//			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = pOperand->Sec(&m_pResult);
			break;
		case enXVSB_SECH:
//			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = pOperand->SecH(&m_pResult);
			break;
		case enXVSB_TAN:
//			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = pOperand->Tan(&m_pResult);
			break;
		case enXVSB_TANH:
//			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = pOperand->TanH(&m_pResult);
			break;
		case enXVSB_ATAN:
//			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = pOperand->ATan(&m_pResult);
			break;
		case enXVSB_CTG:
//			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = pOperand->CTan(&m_pResult);
			break;
		case enXVSB_CTGH:
//			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = pOperand->CTanH(&m_pResult);
			break;
		case enXVSB_ACTG:
//			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = pOperand->ACTan(&m_pResult);
			break;
		case enXVSB_EXP:
//			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = pOperand->Exp(&m_pResult);
			break;
		case enXVSB_LN:
//			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = pOperand->Ln(&m_pResult);
			break;
		case enXVSB_LOG10:
//			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = pOperand->Log10(&m_pResult);
			break;
		case enXVSB_LOG:
#ifdef _XSVM_DEBUG_
			assert(pInput != NULL);
#endif
			if(pInput == NULL)
			{
				return bRet;
			}
//			pInput->Clone((IVSB_Base **)&m_pResult);
			bRet = pInput->Log(pOperand, &m_pResult);
			break;
		case enXVSB_SQRT:
//			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = pOperand->Sqrt(&m_pResult);
			break;
		case enXVSB_POW:
#ifdef _XSVM_DEBUG_
			assert((IVSB_Base **)pInput != NULL);
#endif
			if(pInput == NULL)
			{
				return bRet;
			}
//			pInput->Clone((IVSB_Base **)&m_pResult);
			bRet = pInput->Pow(pOperand, &m_pResult);
			break;
		case enXVSB_ROOT:
#ifdef _XSVM_DEBUG_
			assert(pInput != NULL);
#endif
			if(pInput == NULL)
			{
				return bRet;
			}
//			pInput->Clone((IVSB_Base **)&m_pResult);
			bRet = pInput->Root(pOperand, &m_pResult);
			break;
		case enXVSB_FACTORIAL:
//			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = pOperand->Factorial(&m_pResult);
			break;
		case enXVSB_HYPOT:
#ifdef _XSVM_DEBUG_
			assert(pInput != NULL);
#endif
			if(pInput == NULL)
			{
				return bRet;
			}
//			pInput->Clone((IVSB_Base **)&m_pResult);
			bRet = pInput->Hypot(pOperand, &m_pResult);
			break;
		case enXVSB_MOD:
			bRet = pOperand->Mod(&m_pResult);
			break;
		case enXVSB_MOD2:
#ifdef _XSVM_DEBUG_
			assert(pInput != NULL);
#endif
			if(pInput == NULL)
			{
				return bRet;
			}
			bRet = pInput->Mod2(pOperand, &m_pResult);
			break;
		case enXVSB_FRACTION:
			bRet = pOperand->Fraction(&m_pResult);
			break;
		case enXVSB_FMOD:
#ifdef _XSVM_DEBUG_
			assert(pInput != NULL);
#endif
			if(pInput == NULL)
			{
				return bRet;
			}
//			pInput->Clone((IVSB_Base **)&m_pResult);
			bRet = pInput->FMod(pOperand, &m_pResult);
			break;
		case enXVSB_FMOD2:
#ifdef _XSVM_DEBUG_
			assert(pInput != NULL);
#endif
			if(pInput == NULL)
			{
				return bRet;
			}
			bRet = pInput->FMod2(pOperand, &m_pResult);
			break;
		case enXVSB_LSHIFT:
#ifdef _XSVM_DEBUG_
			assert(pInput != NULL);
#endif
			if(pInput == NULL)
			{
				return bRet;
			}
//			pInput->Clone((IVSB_Base **)&m_pResult);
			bRet = pInput->LShift(pOperand, &m_pResult);
			break;
		case enXVSB_RSHIFT:
#ifdef _XSVM_DEBUG_
			assert(pInput != NULL);
#endif
			if(pInput == NULL)
			{
				return bRet;
			}
//			pInput->Clone((IVSB_Base **)&m_pResult);
			bRet = pInput->RShift(pOperand, &m_pResult);
			break;
		case enXVSB_AND:
#ifdef _XSVM_DEBUG_
			assert(pInput != NULL);
#endif
			if(pInput == NULL)
			{
				return bRet;
			}
//			pInput->Clone((IVSB_Base **)&m_pResult);
			bRet = pInput->And(pOperand, &m_pResult);
			break;
		case enXVSB_EXOR:
#ifdef _XSVM_DEBUG_
			assert(pInput != NULL);
#endif
			if(pInput == NULL)
			{
				return bRet;
			}
//			pInput->Clone((IVSB_Base **)&m_pResult);
			bRet = pInput->ExOR(pOperand, &m_pResult);
			break;
		case enXVSB_INOR:
#ifdef _XSVM_DEBUG_
			assert(pInput != NULL);
#endif
			if(pInput == NULL)
			{
				return bRet;
			}
//			pInput->Clone((IVSB_Base **)&m_pResult);
			bRet = pInput->InOR(pOperand, &m_pResult);
			break;
		case enXVSB_NOT:
//			pOperand->Clone((IVSB_Base **)&m_pResult);
			bRet = pOperand->Not(&m_pResult);
			break;
		default:
#ifdef _XSVM_DEBUG_
			assert(false);
#endif
			break;
	}

	return bRet;
}

CVSB_hCFnNode CVSB_CFnNodeCreate::operator()(void)
{
	return (new CVSB_CFnNode());
}

CVSB_hCFnNode CVSB_CFnNodeCreate::operator()(CVSB_CFnNode* pParent, enXVSB_PRIORITY lvl, enXVSB_OPERATION oType)
{
	return (new CVSB_CFnNode(pParent, lvl, oType));
}

CVSB_hCFnNode CVSB_CFnNodeCreate::operator()(CVSB_CFParamUnitBase* param, CVSB_CFnNode* pParent, enXVSB_PRIORITY lvl, enXVSB_OPERATION oType)
{
	return (new CVSB_CFnNode(param, pParent, lvl, oType));
}

void CXOS_CFnNodeRelease::operator()(CVSB_hCFnNode& hENdoe)
{
	if(hENdoe)
	{
		delete hENdoe;
		hENdoe = NULL;
	}
}

CVSB_ParamType CVSB_CFnNode::GetOperandParamType(void)
{
	CVSB_ParamType parType;
	parType.Empty();

	if(m_Operand != NULL)
	{
		parType = m_Operand->GetParamType();
	}

	if(parType.IsEmpty())
	{
		CVSB_CFnNodeList::iterator iter;
		for(iter = m_SubOps.begin(); iter != m_SubOps.end(); iter++)
		{
			parType = (*iter)->GetOperandParamType();
			if(!parType.IsEmpty())
				return parType;
		}
	}

	return parType;
}

