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

bool CVSB_ExpFactory::_sameop(enXVSB_OPERATION ot)
{
	bool bRet = false;
	
	// Check handle
	bool bOK = (m_hExpress && m_hCusor && m_opFilter.IsValid() && m_bInProcess);

#ifdef _XSVM_DEBUG_
	assert(bOK);
#endif
	if(!bOK)
		return bRet;

	// Check the two op types relation
	enXVSB_OPERATION prevOP;
	prevOP = m_opFilter.PeekType();
	int nDif = LevelDifference(prevOP, ot);

	bOK = (nDif == 0);
#ifdef _XSVM_DEBUG_
	assert(bOK);
#endif
	if(!bOK)
		return bRet;
	
	CVSB_hENode pTemp = NULL;

	if(ot == enXVSB_NONE)
	{
		prevOP = m_opFilter.PopType();
		pTemp = (CVSB_hENode)m_opFilter.PopVar();
		pTemp->m_pParent = m_hCusor;
		pTemp->Reset(enXVSB_LEVEL1, enXVSB_NONE);
		m_hCusor->AddSubOp(pTemp);
		return true;
	}

	// Check level information
	enXVSB_PRIORITY mLvl;

	mLvl = GetOperationLevel(ot);
	bOK = (mLvl == enXVSB_LEVEL1 || mLvl == enXVSB_LEVEL2);
#ifdef _XSVM_DEBUG_
	assert(bOK);
#endif
	if(!bOK)
		return bRet;

	prevOP = m_opFilter.PopType();
	pTemp = (CVSB_hENode)m_opFilter.PopVar();
	if(pTemp)
	{
		pTemp->m_pParent = m_hCusor->m_pParent;
		pTemp->Reset(mLvl, prevOP);
		m_hCusor->m_pParent->AddSubOp(pTemp);
		m_opFilter.PushType(ot);

		//Keep the m_hCusor in the same level of ot
		m_hCusor = pTemp;              
		bRet = true;
	}

	return bRet;
}

bool CVSB_ExpFactory::_down1op(enXVSB_OPERATION ot)
{
	bool bRet = false;
	bool bOK = 	(m_hExpress && m_hCusor && m_opFilter.IsValid() && m_bInProcess);

#ifdef _XSVM_DEBUG_
	assert(bOK);
#endif
	if(!bOK)
		return bRet;

	enXVSB_OPERATION prevOP;
	prevOP = m_opFilter.PeekType();
	int nDif = LevelDifference(prevOP, ot);

	bOK = (nDif == 1);
#ifdef _XSVM_DEBUG_
	assert(bOK);
#endif
	if(!bOK)
		return bRet;

	enXVSB_PRIORITY mLvl;

	mLvl = GetOperationLevel(ot);
	CVSB_hENode pTemp = NULL;
	CVSB_hENode pMath = NULL;
	CVSB_ENodeCreator mBuilder;

	if(mLvl == enXVSB_LEVEL1)  // Prev OP: None; New OP: +,-      
	{
		prevOP = m_opFilter.PopType();

		pTemp = (CVSB_hENode)m_opFilter.PopVar();
		if(pTemp)
		{
			pTemp->m_pParent = m_hCusor;
			pTemp->Reset(mLvl, prevOP);
			m_hCusor->AddSubOp(pTemp);

			//Keep the m_hCusor in the same level of ot
			m_opFilter.PushType(ot);
			m_hCusor = pTemp;              
			bRet = true;
		}
		else
		{
			pTemp = mBuilder((CVSB_hENode)m_hCusor, enXVSB_LEVEL1, prevOP);
			m_hCusor->AddSubOp(pTemp);
			//Keep the m_hCusor in the same level of ot
			m_opFilter.PushType(ot);
			m_hCusor = pTemp;              
			bRet = true;
		}
	}
	else if(mLvl == enXVSB_LEVEL2) // Prev OP: +, -; New OP: *,/      
	{
		prevOP = m_opFilter.PopType();
		pTemp = (CVSB_hENode)m_opFilter.PopVar();

		// Create the temparay level 1 node for "prevOP" operation
		pMath = mBuilder((CVSB_hENode)m_hCusor->m_pParent, enXVSB_LEVEL1, prevOP);
		if(pMath)
		{
			m_hCusor->m_pParent->AddSubOp(pMath);
			m_hCusor = pMath;
			pTemp->m_pParent = m_hCusor;
			pTemp->Reset(mLvl, enXVSB_NONE);
			m_hCusor->AddSubOp(pTemp);

			//Keep the m_hCusor in the same level of ot
			m_opFilter.PushType(ot);
			m_hCusor = pTemp;
			bRet = true;
		}
	}
	else if(mLvl == enXVSB_LEVEL3) // Prev OP: *, /; New OP: level 3 OPs
	{
		if(ot == enXVSB_FACTORIAL) // Replace the current data on the top of filter
		{
			pTemp = (CVSB_hENode)m_opFilter.PopVar();
			
			if(pTemp)
			{
				// Create the temparay level 2 node for "prevOP" operation
				// Don't push factorial ot into filter stack
				pMath = mBuilder((CVSB_hENode)m_hCusor->m_pParent, enXVSB_LEVEL2, prevOP);
				if(pMath)
				{
					pTemp->m_pParent = pMath;
					pTemp->Reset(mLvl, ot);
					pMath->AddSubOp(pTemp);
					m_opFilter.PushVar(&pMath);
					bRet = true;
				}
			}
		}
		else
		{
			prevOP = m_opFilter.PopType();
			pTemp = (CVSB_hENode)m_opFilter.PopVar();
			if(pTemp && (ot == enXVSB_LSHIFT || ot == enXVSB_RSHIFT || ot == enXVSB_AND || ot == enXVSB_EXOR || ot == enXVSB_INOR))
			{
				// Create the temparay level 2 node for "prevOP" operation
				pMath = mBuilder((CVSB_hENode)m_hCusor->m_pParent, enXVSB_LEVEL2, prevOP);
				if(pMath)
				{
					m_hCusor->m_pParent->AddSubOp(pMath);
					pTemp->m_pParent = pMath;
					pTemp->Reset(mLvl, enXVSB_NONE);
					pMath->AddSubOp(pTemp);
			
					//Keep the m_hCusor in the same level of ot
					m_opFilter.PushType(ot);
					m_hCusor = pTemp;
					bRet = true;
				}
			}
			else if(pTemp == NULL)
			{
				// Create the temparay level 2 node for "prevOP" operation
				pMath = mBuilder((CVSB_hENode)m_hCusor->m_pParent, enXVSB_LEVEL2, prevOP);
				if(pMath)
				{
					m_hCusor->m_pParent->AddSubOp(pMath);
					
					//Keep cusor in level 2 temperary node
					//?????????????????
					m_opFilter.PushType(ot);
					m_hCusor = pMath;
					bRet = true;
					//?????????????????


					/*pTemp = mBuilder((CVSB_hENode)pMath, mLvl, enXVSB_NONE);
					if(pTemp)
					{
						//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						//Don't add current temperary node into pMath sub-node operation 
						//list !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						//????????????????
						//pMath->AddSubOp(pTemp);
						//????????????????
			
						//Keep the m_hCusor in the same level of ot
						m_opFilter.PushType(ot);
						m_hCusor = pTemp;
						bRet = true;
					}
					*/
				}
			}
		}
	}

	return bRet;
}

bool CVSB_ExpFactory::_up1op(enXVSB_OPERATION ot)
{
	bool bRet = false;
	bool bOK = 	(m_hExpress && m_hCusor && m_opFilter.IsValid() && m_bInProcess);

#ifdef _XSVM_DEBUG_
	assert(bOK);
#endif
	if(!bOK)
		return bRet;

	enXVSB_OPERATION prevOP;
	prevOP = m_opFilter.PeekType();
	int nDif = LevelDifference(prevOP, ot);

	bOK = (nDif == -1);
#ifdef _XSVM_DEBUG_
	assert(bOK);
#endif
	if(!bOK)
		return bRet;

	enXVSB_PRIORITY mLvl;

	mLvl = GetOperationLevel(ot);
	CVSB_hENode pTemp = NULL;
	CVSB_hENode pTemp2 = NULL;
	CVSB_hENode pDelNode = NULL;

	if(mLvl == enXVSB_LEVEL_NONE)  // Prev OP: +,-; New OP: None      
	{
		prevOP = m_opFilter.PopType();
		pTemp = (CVSB_hENode)m_opFilter.PopVar();
		if(pTemp)
		{
			pTemp->m_pParent = m_hCusor->m_pParent;
			pTemp->Reset(enXVSB_LEVEL1, prevOP);
			m_hCusor->m_pParent->AddSubOp(pTemp);

			//Keep the m_hCusor in the same level of ot, and don't 
			//push ot into filter stack, since it means ending
			m_hCusor = m_hCusor->m_pParent;              
			bRet = true;
		}
	}
	else if(mLvl == enXVSB_LEVEL1) // Prev OP: *, /; New OP: +,-      
	{
		prevOP = m_opFilter.PopType();
		pTemp = (CVSB_hENode)m_opFilter.PopVar();

		if(pTemp)
		{
			pTemp->m_pParent = m_hCusor->m_pParent;
			pTemp->Reset(enXVSB_LEVEL2, prevOP);
			m_hCusor->m_pParent->AddSubOp(pTemp);

			//Keep the m_hCusor in the same level of ot,
			m_opFilter.PushType(ot);
			m_hCusor = m_hCusor->m_pParent;              
			bRet = true;
		}
	}
	else if(mLvl == enXVSB_LEVEL2) // Prev OP: level 3 OPs; New OP: *,/      
	{
		prevOP = m_opFilter.PopType();
		pTemp = (CVSB_hENode)m_opFilter.PopVar();

		if(prevOP == enXVSB_LSHIFT || prevOP == enXVSB_RSHIFT  || prevOP == enXVSB_AND || prevOP == enXVSB_EXOR || prevOP == enXVSB_INOR)
		{
			if(pTemp)
			{
				pTemp->m_pParent = m_hCusor->m_pParent;
				pTemp->Reset(enXVSB_LEVEL3, prevOP);
				m_hCusor->m_pParent->AddSubOp(pTemp);

				//Keep the m_hCusor in the same level of ot,
				m_opFilter.PushType(ot);
				m_hCusor = m_hCusor->m_pParent;              
				bRet = true;
			}
		}
		else 
		{
//			pDelNode = m_hCusor;
			if(prevOP == enXVSB_POW || prevOP == enXVSB_ROOT || prevOP == enXVSB_HYPOT ||
			   prevOP == enXVSB_LOG || prevOP == enXVSB_MOD2 || prevOP == enXVSB_FMOD || prevOP == enXVSB_FMOD2)
			{
				pTemp2 = (CVSB_hENode)m_opFilter.PopVar();
				if(pTemp2 && pTemp)
				{
					//??????????????????????????????
					//Keep the m_hCusor in the previous level
					pTemp->m_pParent = m_hCusor;
					pTemp->Reset(enXVSB_LEVEL3, enXVSB_NONE);
					m_hCusor->AddSubOp(pTemp);

					pTemp2->m_pParent = m_hCusor->m_pParent;
					pTemp2->Reset(enXVSB_LEVEL3, prevOP);
					m_hCusor->AddSubOp(pTemp2);
					//??????????????????????????????



					///*Keep the m_hCusor in the same level of ot,*/
					m_opFilter.PushType(ot);
//					m_hCusor = m_hCusor->m_pParent;    
/*
					pTemp->m_pParent = m_hCusor->m_pParent;
					pTemp->Reset(enXVSB_LEVEL3, enXVSB_NONE);
					m_hCusor->m_pParent->AddSubOp(pTemp);

					pTemp2->m_pParent = m_hCusor->m_pParent;
					pTemp2->Reset(enXVSB_LEVEL3, prevOP);
					m_hCusor->m_pParent->AddSubOp(pTemp2);

					//Keep the m_hCusor in the same level of ot,
					m_opFilter.PushType(ot);
					m_hCusor = m_hCusor->m_pParent;    
					
					//Delete the temperary node.
					//????????????????
					//if(pDelNode)
					//{
					//	delete pDelNode;
					//	pDelNode = NULL;
					//}
					*/

					bRet = true;
				}
			}
			else
			{
				if(pTemp)
				{

					pTemp->m_pParent = m_hCusor;
					pTemp->Reset(enXVSB_LEVEL3, prevOP);
					m_hCusor->AddSubOp(pTemp);

					//Keep the m_hCusor in the previous level
					m_opFilter.PushType(ot);
/*
					pTemp->m_pParent = m_hCusor->m_pParent;
					pTemp->Reset(enXVSB_LEVEL3, prevOP);
					m_hCusor->m_pParent->AddSubOp(pTemp);

					//Keep the m_hCusor in the same level of ot,
					m_opFilter.PushType(ot);
					m_hCusor = m_hCusor->m_pParent;    
					
					//Delete the temperary node.
					//if(pDelNode)
					//{
					//	delete pDelNode;
					//	pDelNode = NULL;
					//}
*/
					bRet = true;
				}
			}
		}
	}

	return bRet;
}
