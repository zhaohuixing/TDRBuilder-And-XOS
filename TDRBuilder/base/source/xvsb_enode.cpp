// Project: Visual System Builder
//
// File Name: xvsb_enode.cpp
//
// Description: The implementation of the expression node
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/20/2005	
//
// History:
// 1.    01/20/2005: Create	
//
//#include "stdafx.h"
#include "xvsb_enode.h"
#include "xvsb_array.h"

CVSB_ExpressNode::CVSB_ExpressNode(void) : m_Operand()
{
	m_SubOps.clear();
	m_pParent = NULL;
	m_hOwner = NULL;
	m_Operate = enXVSB_NONE;
	m_pResult = NULL;
	m_Level = enXVSB_LEVEL_NONE;
	m_bSubRootNode = false;
}

CVSB_ExpressNode::CVSB_ExpressNode(CVSB_ExpressNode* pParent, enXVSB_PRIORITY lvl, enXVSB_OPERATION oType)
	: m_Operand()
{
	m_SubOps.clear();
	m_pParent = pParent;
	m_hOwner = NULL;
	m_Operate = oType;
	m_pResult = NULL;
	m_Level = lvl;
	m_bSubRootNode = false;
}

CVSB_ExpressNode::CVSB_ExpressNode(const CVSB_Parameter& param, CVSB_ExpressNode* pParent, enXVSB_PRIORITY lvl, enXVSB_OPERATION oType)
	: m_Operand(param)
{
	m_SubOps.clear();
	m_pParent = pParent;
	m_hOwner = NULL;
	m_Operate = oType;
	m_pResult = NULL;
	m_Level = lvl;
	m_bSubRootNode = false;
}

CVSB_ExpressNode::~CVSB_ExpressNode(void)
{
	Clear();
}

void CVSB_ExpressNode::Clear(void)
{
	CleanBuffer();
	CleanSubRootFlag();
}

void CVSB_ExpressNode::CleanBuffer(void)
{
	CVSB_ExpFree expFree;
	expFree(m_SubOps);

	if(m_pResult)
	{
		delete m_pResult;
		m_pResult = NULL;
	}
}

CVSB_ExpressNode::operator IVSB_DataBase* ()
{
	return m_pResult;
}

IVSB_DataBase* CVSB_ExpressNode::GetResult(void)
{
	return m_pResult;
}

void CVSB_ExpressNode::SetAsSubRoot(void)
{
	m_bSubRootNode = true;
}

void CVSB_ExpressNode::CleanSubRootFlag(void)
{
	m_bSubRootNode = false;
}

void CVSB_ExpressNode::AddSubOp(CVSB_ExpressNode* subOp)
{
#ifdef _XSVM_DEBUG_
	assert(subOp != NULL);
#endif
	if(subOp != NULL)
		m_SubOps.push_back(subOp);
}

bool CVSB_ExpressNode::Reset(enXVSB_PRIORITY lvl, enXVSB_OPERATION oType)
{
	m_Operate = oType;
	m_Level = lvl;
	return true;
}

bool CVSB_ExpressNode::IsDirty(void)
{
	return (!m_SubOps.empty());
}

enXVSB_PRIORITY CVSB_ExpressNode::GetLevel(void)
{
	return m_Level;
}

void CVSB_ExpressNode::SetLevel(enXVSB_PRIORITY lvl)
{
	m_Level = lvl;
}

enXVSB_OPERATION CVSB_ExpressNode::GetOperation(void)
{
	return m_Operate;
}

void CVSB_ExpressNode::SetOperation(enXVSB_OPERATION op)
{
	m_Operate = op;
}

void CVSB_ExpressNode::SetParentNode(CVSB_ExpressNode* pParent)
{
	m_pParent = pParent;
}

bool CVSB_ExpressNode::IsSubOpSimple(void)
{
	bool bRet = true;

	if(m_SubOps.empty())
		return bRet;

	CVSB_ExpIterator iter;
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

bool CVSB_ExpressNode::HasRootNode(void)
{
	bool bRet = false;

	if(m_Level == enXVSB_LEVEL_ROOT || m_bSubRootNode == true)
		return !bRet;

	if(m_SubOps.empty())
		return bRet;

	CVSB_ExpIterator iter;
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

void CVSB_ExpressNode::SetOperand(const CVSB_Parameter& param)
{
	m_Operand = param;
}

bool CVSB_ExpressNode::AttachVarOperand(IVSB_DataBase* pData)
{
	return m_Operand.AttachVar(pData);
}

void CVSB_ExpressNode::AttachOwner(CVSB_OwnerBase* hOwner)
{
	m_hOwner = hOwner;
	if(!m_SubOps.empty())
	{
		CVSB_ExpIterator iter;
		for(iter = m_SubOps.begin(); iter != m_SubOps.end(); iter++)
		{
			(*iter)->AttachOwner(hOwner);
		}
	}
}

bool CVSB_ExpressNode::ResetResult(void)
{
	if(m_pResult)
	{
		delete m_pResult;
		m_pResult = NULL;
	}
	CVSB_ExpIterator iter;
	for(iter = m_SubOps.begin(); iter != m_SubOps.end(); iter++)
	{
		(*iter)->ResetResult();
	}

	return true;
}

bool CVSB_ExpressNode::Run(IVSB_DataBase* pInPrev)
{
	bool bRet = false;
	IVSB_DataBase* pOperand = NULL;
	IVSB_DataBase* pTemp = NULL;

	if(IsDirty())
	{
		CVSB_ExpIterator iter;
		for(iter = m_SubOps.begin(); iter != m_SubOps.end(); ++iter)
		{
			if((*iter)->Run(pOperand))
			//if((*iter)->Run(pTemp))
			{
				pOperand = (*iter)->GetResult();
				//pTemp = (*iter)->GetResult();
			}
		}

		if(pOperand)
		{
/*
//			CStringW s1= pOperand->GetType().GetNameSpace().c_str();
//			CStringW s2= pOperand->GetType().GetType().c_str();
//			CStringW s3= pOperand->GetType().GetClass().c_str();
//			TRACE(_T("%s, %s, %s\n"), s1, s2, s3); 
			//pOperand->Clone((IVSB_Base**)&pTemp);
*/
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
			if(!m_Operand.IsParamValid())
			{
				bRet = _attachoperand();
//#ifdef _XSVM_DEBUG_
//				assert(bRet);
//#endif
			}
//			m_Operand.GetParamData()->Clone((IVSB_Base**)&pTemp);
			pTemp = m_Operand.GetParamData();
		}
	}


	//assert(pTemp != NULL);
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

	bRet = _calculate(pInPrev, pTemp);

//	if(pTemp)
//	{
//		delete pTemp;
//		pTemp = NULL;
//	}


	return bRet;
}

bool CVSB_ExpressNode::_attachoperand(void)
{
	bool bRet = false;
	if(m_Operand.IsConstant() || m_hOwner == NULL)
		return bRet;

	// Find the primary object from the owner variable table
	IVSB_DataBase* pVar1 = m_hOwner->GetVar(m_Operand.GetParamName());


	if(pVar1 == NULL)
		return bRet;

	if(m_Operand.IsVariable())
	{
		bRet = m_Operand.AttachVar(pVar1);
		return bRet;
	}
	else if(m_Operand.IsArrayElement() && pVar1->GetType().GetClass() == XVSM_TYPE_ARRAY)
	{
		IVSB_DataBase* pVar2;
		if(m_Operand.IsConstAryIdx())
		{
			pVar2 = ((CVSB_Array*)pVar1)->At(m_Operand.GetConstAryIdx());
			if(pVar2 == NULL)
				return bRet;
			bRet = m_Operand.AttachVar(pVar2);
			return bRet;
		}
		else 
		{
			// Find the index object from the owner variable table
			IVSB_DataBase* pIdx = m_hOwner->GetVar(m_Operand.GetAryIdxVarName());
			if(pIdx == NULL)
				return bRet;
			
			if(pIdx->GetType().GetClass() == XVSM_TYPE_INTEGER || 
			   pIdx->GetType().GetClass() == XVSM_TYPE_BYTE ||
			   pIdx->GetType().GetClass() == XVSM_TYPE_FLOAT ||
			   pIdx->GetType().GetClass() == XVSM_TYPE_CHAR ||
			   pIdx->GetType().GetClass() == XVSM_TYPE_BOOL)
			{
				int nIdx = 0;
				if(pIdx->GetType().GetClass() == XVSM_TYPE_INTEGER)
				{
					nIdx = (int)(*((CVSB_Integer*)pIdx));
				}
				else if(pIdx->GetType().GetClass() == XVSM_TYPE_BYTE)
				{
					nIdx = (int)(*((CVSB_Byte*)pIdx));
				}
				else if(pIdx->GetType().GetClass() == XVSM_TYPE_FLOAT)
				{
					nIdx = (int)(*((CVSB_Float*)pIdx));
				}
				else if(pIdx->GetType().GetClass() == XVSM_TYPE_CHAR)
				{
					nIdx = (int)(*((CVSB_Char*)pIdx));
				}
				else if(pIdx->GetType().GetClass() == XVSM_TYPE_BOOL)
				{
					nIdx = (int)(*((CVSB_Bool*)pIdx));
				}
				pVar2 = ((CVSB_Array*)pVar1)->At(nIdx);
				if(pVar2 == NULL)
					return bRet;
				bRet = m_Operand.AttachVar(pVar2);
				return bRet;
			}
		}
	}

	return bRet;
}

bool CVSB_ExpressNode::_calculate(IVSB_DataBase* pInput, IVSB_DataBase* pOperand)
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

CVSB_hENode CVSB_ENodeCreator::operator()(void)
{
	return (new CVSB_ExpressNode());
}

CVSB_hENode CVSB_ENodeCreator::operator()(CVSB_ExpressNode* pParent, enXVSB_PRIORITY lvl, enXVSB_OPERATION oType)
{
	return (new CVSB_ExpressNode(pParent, lvl, oType));
}

CVSB_hENode CVSB_ENodeCreator::operator()(const CVSB_Parameter& param, CVSB_ExpressNode* pParent, enXVSB_PRIORITY lvl, enXVSB_OPERATION oType)
{
	return (new CVSB_ExpressNode(param, pParent, lvl, oType));
}

void CXOS_EUnitRelease::operator()(CVSB_hENode& hENdoe)
{
	if(hENdoe)
	{
		delete hENdoe;
		hENdoe = NULL;
	}
}


