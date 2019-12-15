// Project: Visual System Builder
//
// File Name: xvsb_efactry.cpp
//
// Description: The implementation of the factory class for expression creation
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/23/2005	
//
// History:
// 1.    01/23/2005: Create	
//
#include "xvsb_efactry.h"

bool IsSameLevel(enXVSB_OPERATION mType1, enXVSB_OPERATION mType2)
{
	int d1;
	int d2;

	if(mType1 == enXVSB_NONE)
		d1 = 0;
	else if(mType1 == enXVSB_PLUS || mType1 == enXVSB_MINUS)
		d1 = 1;
	else if(mType1 == enXVSB_TIME || mType1 == enXVSB_DIVIDE)
		d1 = 2;
	else
		d1 = 3;


	if(mType2 == enXVSB_NONE)
		d2 = 0;
	else if(mType2 == enXVSB_PLUS || mType2 == enXVSB_MINUS)
		d2 = 1;
	else if(mType2 == enXVSB_TIME || mType2 == enXVSB_DIVIDE)
		d2 = 2;
	else
		d2 = 3;

	return (d1 == d2);
}

int LevelDifference(enXVSB_OPERATION mType1, enXVSB_OPERATION mType2)
{
	int d1;
	int d2;

	if(mType1 == enXVSB_NONE)
		d1 = 0;
	else if(mType1 == enXVSB_PLUS || mType1 == enXVSB_MINUS)
		d1 = 1;
	else if(mType1 == enXVSB_TIME || mType1 == enXVSB_DIVIDE)
		d1 = 2;
	else
		d1 = 3;


	if(mType2 == enXVSB_NONE)
		d2 = 0;
	else if(mType2 == enXVSB_PLUS || mType2 == enXVSB_MINUS)
		d2 = 1;
	else if(mType2 == enXVSB_TIME || mType2 == enXVSB_DIVIDE)
		d2 = 2;
	else
		d2 = 3;

	return (d2 - d1);
}

enXVSB_PRIORITY GetOperationLevel(enXVSB_OPERATION mType)
{
	enXVSB_PRIORITY mLevel;

	if(mType == enXVSB_NONE) 
		mLevel = enXVSB_LEVEL_NONE;
	else if(mType == enXVSB_PLUS || mType == enXVSB_MINUS)
		mLevel = enXVSB_LEVEL1;
	else if(mType == enXVSB_TIME || mType == enXVSB_DIVIDE)
		mLevel = enXVSB_LEVEL2;
	else
		mLevel = enXVSB_LEVEL3;

	return mLevel;
}

CVSB_ExpFactory::CVSB_ExpFactory(void)
{
	m_hExpress = NULL;     
	m_IsShared = false;     
	m_bInProcess = false;
}

CVSB_ExpFactory::~CVSB_ExpFactory(void)
{
	Reset();
}

CVSB_hENode CVSB_ExpFactory::GetExpression(void)
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

CVSB_ExpFactory::operator CVSB_hENode (void)
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

void CVSB_ExpFactory::Reset(void)
{
	if(m_hExpress != NULL)
	{
		if(m_IsShared == false)
		{
			delete m_hExpress;
		}
		m_hExpress = NULL;
	}
	m_IsShared = false; 
	
	m_hCusor = NULL;
	m_opFilter.Reset();
	m_bInProcess = false;
}

bool CVSB_ExpFactory::IsInProcess(void)
{
	return m_bInProcess;
}

bool CVSB_ExpFactory::StartRoot(void)
{
	bool bRet = true;
	Reset();

	CVSB_ENodeCreator mBuilder;
	m_hExpress = mBuilder();
	
	if(m_hExpress == NULL)
		return !bRet;

	m_hExpress->Reset(enXVSB_LEVEL_ROOT, enXVSB_NONE);
	m_hCusor = m_hExpress;

	m_opFilter.AddAction();
	enXVSB_OPERATION Op = enXVSB_NONE;
	m_opFilter.PushType(Op);

	m_bInProcess = true;
	return bRet;
}

bool CVSB_ExpFactory::EndRoot(void)
{
	bool bRet = false;

	if(m_hExpress && m_hCusor && m_opFilter.IsValid() && m_bInProcess)
	{
		bRet = AddOperation(enXVSB_NONE);
	}

	m_opFilter.RemoveTailAction();
	m_hCusor = m_hExpress;
	m_bInProcess = false;
	return bRet;
}

bool CVSB_ExpFactory::StartSubRoot(void)
{
	bool bRet = false;
	CVSB_hENode pTemp1 = NULL;
	CVSB_hENode pTemp2 = NULL;
	enXVSB_PRIORITY mLvl;
	CVSB_ENodeCreator mBuilder;


	if(m_hExpress && m_hCusor && m_opFilter.IsValid() && m_bInProcess)
	{
		enXVSB_OPERATION prevOP = m_opFilter.PeekType();
		mLvl = GetOperationLevel(prevOP);

		// Create the first temp node and move the cursor to this node
		pTemp1 = mBuilder((CVSB_hENode)m_hCusor, mLvl, prevOP);
		if(pTemp1)
		{
			m_SubExps.push(pTemp1);
			pTemp2 = mBuilder((CVSB_hENode)pTemp1, enXVSB_LEVEL_ROOT, enXVSB_NONE);
			pTemp1->AddSubOp(pTemp2);
		
			if(pTemp2)
			{
				m_hCusor = pTemp2;
				pTemp2->SetAsSubRoot();
				m_opFilter.AddAction();
				enXVSB_OPERATION Op = enXVSB_NONE;
				m_opFilter.PushType(Op);
				bRet = true;
			}
		}
	}
	// Don't release the following buffers
    // they will be automatically managed and released
	// by the math expression 
	pTemp1 = NULL;
	return bRet;
}

bool CVSB_ExpFactory::EndSubRoot(void)
{
	bool bRet = false;
	CVSB_hENode pTemp1 = NULL;

	if(m_hExpress && m_hCusor && m_opFilter.IsValid() && m_bInProcess && m_SubExps.size() != 0)
	{
		bRet = AddOperation(enXVSB_NONE);

		if(bRet)
		{
			m_opFilter.RemoveTailAction();
			pTemp1 = (CVSB_hENode)m_SubExps.top();

			m_opFilter.PushVar(&pTemp1);

			m_hCusor = pTemp1->m_pParent;

			m_SubExps.pop();
		}
	}

	// Don't release the following buffers
    // they will be automatically managed and released
	// by the expression 
	pTemp1 = NULL;
	return bRet;
}

int CVSB_ExpFactory::GetTCountInStack(void)
{
	return m_opFilter.GetTypeCount();
}

int CVSB_ExpFactory::GetVCountInStack(void)
{
	return m_opFilter.GetVarCount();
}

enXVSB_OPERATION CVSB_ExpFactory::PeekTypeInStack(void)
{
	return m_opFilter.PeekType();
}

enXVSB_OPERATION CVSB_ExpFactory::RemoveTypeInStack(void)
{
	return m_opFilter.PopType();
}

bool CVSB_ExpFactory::PushType2Stack(enXVSB_OPERATION ot)
{
	m_opFilter.PushType(ot);
	return true;
}

bool CVSB_ExpFactory::AddVariable(const CVSB_Parameter& param)
{
	bool bRet = false;
	CVSB_ExpressNode* pMath = NULL;

	if(m_hExpress && m_hCusor && m_opFilter.IsValid() && m_bInProcess)
	{
		pMath = new CVSB_ExpressNode(param, m_hCusor, enXVSB_LEVEL_NONE, enXVSB_NONE);
		if(pMath)
		{
			m_opFilter.PushVar(&pMath);
			bRet = true;
		}
	}

	pMath = NULL;
	return bRet;
}

/*

Rule: m_hCusor is alway in the same level of "ot" (the one in the top of m_opFilter
after AddOperation except "factorical(n!)"

*/
bool CVSB_ExpFactory::AddOperation(enXVSB_OPERATION ot)
{
	bool bRet = false;
	enXVSB_OPERATION prevOP;

	if(m_hExpress && m_hCusor && m_opFilter.IsValid() && m_bInProcess)
	{
		prevOP = m_opFilter.PeekType();
		int nDif = LevelDifference(prevOP, ot);
		if(nDif == 0)
		{
			bRet = _sameop(ot);
		}
		else if(nDif == 1)
		{
			bRet = _down1op(ot);
		}
		else if(nDif == 2)
		{
			bRet = _down2op(ot);
		}
		else if(nDif == 3)
		{
			bRet = _down3op(ot);
		}
		else if(nDif == -1)
		{
			bRet = _up1op(ot);
		}
		else if(nDif == -2)
		{
			bRet = _up2op(ot);
		}
		else if(nDif == -3)
		{
			bRet = _up3op(ot);
		}
		else
		{
#ifdef _XSVM_DEBUG_
			assert(false);
#endif
		}
	}

	return bRet;
}