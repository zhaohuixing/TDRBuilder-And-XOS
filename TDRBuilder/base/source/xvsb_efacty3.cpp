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

bool CVSB_ExpFactory::_down3op(enXVSB_OPERATION ot)
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

	bOK = (nDif == 3);
#ifdef _XSVM_DEBUG_
	assert(bOK);
#endif
	if(!bOK)
		return bRet;

	enXVSB_PRIORITY mLvl;

	mLvl = GetOperationLevel(ot);
	CVSB_hENode pTemp = NULL;
	CVSB_hENode pMTemp1 = NULL;
	CVSB_hENode pMTemp2 = NULL;
	CVSB_ENodeCreator mBuilder;

	if(mLvl == enXVSB_LEVEL3)  // Prev OP: None; New OP: level 3 operations      
	{
		if(ot == enXVSB_FACTORIAL) // Replace the current data on the top of filter
		{
			pTemp = (CVSB_hENode)m_opFilter.PopVar();
			
			if(pTemp)
			{
				// Create the level 1 temperary node
				pMTemp1 = mBuilder((CVSB_hENode)m_hCusor, enXVSB_LEVEL1, enXVSB_NONE);

				// Create the level 2 temperary node
				pMTemp2 = mBuilder((CVSB_hENode)pMTemp1, enXVSB_LEVEL2, enXVSB_NONE);
				pMTemp1->AddSubOp(pMTemp2);
				if(pMTemp2)
				{
					pTemp->m_pParent = pMTemp2;
					pTemp->Reset(mLvl, ot);
					pMTemp2->AddSubOp(pTemp);
					// Push level temperary node into filter stack
					m_opFilter.PushVar(&pMTemp1);
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
				// Create the temparay level 1 node for "prevOP" operation
				pMTemp1 = mBuilder((CVSB_hENode)m_hCusor, enXVSB_LEVEL1, prevOP);
				m_hCusor->AddSubOp(pMTemp1);
		
				//Move cursor to level 1 temperary node
				m_hCusor = pMTemp1;

				// Create the level 2 temperary node
				pMTemp2 = mBuilder((CVSB_hENode)m_hCusor, enXVSB_LEVEL2, enXVSB_NONE);
				m_hCusor->AddSubOp(pMTemp2);

				//Move cursor to level 2 temperary node
				m_hCusor = pMTemp2;

				if(pMTemp2)
				{
					pTemp->m_pParent = pMTemp2;
					pTemp->Reset(mLvl, enXVSB_NONE);
					pMTemp2->AddSubOp(pTemp);
			
					//Keep the m_hCusor in the same level of ot
					m_opFilter.PushType(ot);
					m_hCusor = pTemp;
					bRet = true;
				}
			}
			else if(pTemp == NULL)
			{
				// Create the temparay level 1 node for "prevOP" operation
				pMTemp1 = mBuilder((CVSB_hENode)m_hCusor, enXVSB_LEVEL1, prevOP);
				m_hCusor->AddSubOp(pMTemp1);
		
				//Move cursor to level 1 temperary node
				m_hCusor = pMTemp1;

				// Create the level 2 temperary node
				pMTemp2 = mBuilder((CVSB_hENode)m_hCusor, enXVSB_LEVEL2, enXVSB_NONE);
				m_hCusor->AddSubOp(pMTemp2);

				//Move cursor to level 2 temperary node
				m_hCusor = pMTemp2;

				//???????????????????????????
				m_opFilter.PushType(ot);
				bRet = true;
				//???????????????????????????

/*
				if(pMTemp2)
				{
					// Create the temperary level 3 node 
					pTemp = mBuilder((CVSB_hENode)pMTemp2, mLvl, enXVSB_NONE);
					if(pTemp)
					{
						//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						//Don't add current temperary node into pMTemp2 sub-node operation 
						//list !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						//Keep the m_hCusor in the same level of ot
						//????????????????
						pMTemp2->AddSubOp(pTemp);
						//????????????????

						m_opFilter.PushType(ot);
						m_hCusor = pTemp;
						bRet = true;
					}
				}
*/
			}
		}
	}

	return bRet;
}

bool CVSB_ExpFactory::_up3op(enXVSB_OPERATION ot)
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

	bOK = (nDif == -3);
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

	if(mLvl == enXVSB_LEVEL_NONE)  // Prev OP: level 3 operations ; New OP: None      
	{
		prevOP = m_opFilter.PopType();
		pTemp = (CVSB_hENode)m_opFilter.PopVar();

		if(prevOP == enXVSB_LSHIFT || prevOP == enXVSB_RSHIFT || prevOP == enXVSB_AND || prevOP == enXVSB_EXOR || prevOP == enXVSB_INOR)
		{
			if(pTemp)
			{
				pTemp->m_pParent = m_hCusor->m_pParent;
				pTemp->Reset(enXVSB_LEVEL3, prevOP);
				m_hCusor->m_pParent->AddSubOp(pTemp);

				//Keep the m_hCusor in the same level of ot,
				m_opFilter.PushType(ot);
				m_hCusor = m_hCusor->m_pParent->m_pParent->m_pParent;              
				bRet = true;
			}
		}
		else 
		{
			pDelNode = m_hCusor;
			if(prevOP == enXVSB_POW || prevOP == enXVSB_ROOT || prevOP == enXVSB_HYPOT ||
			   prevOP == enXVSB_LOG || prevOP == enXVSB_MOD2 || prevOP == enXVSB_FMOD || prevOP == enXVSB_FMOD2)
			{
				pTemp2 = (CVSB_hENode)m_opFilter.PopVar();
				if(pTemp2 && pTemp)
				{
					pTemp->m_pParent = m_hCusor;
					pTemp->Reset(enXVSB_LEVEL3, enXVSB_NONE);
					m_hCusor->AddSubOp(pTemp);

					pTemp2->m_pParent = m_hCusor;
					pTemp2->Reset(enXVSB_LEVEL3, prevOP);
					m_hCusor->AddSubOp(pTemp2);

					//Keep the m_hCusor in the same level of ot,
					m_opFilter.PushType(ot);
					m_hCusor = m_hCusor->m_pParent->m_pParent;    
/*
					pTemp->m_pParent = m_hCusor->m_pParent;
					pTemp->Reset(enXVSB_LEVEL3, enXVSB_NONE);
					m_hCusor->m_pParent->AddSubOp(pTemp);

					pTemp2->m_pParent = m_hCusor->m_pParent;
					pTemp2->Reset(enXVSB_LEVEL3, prevOP);
					m_hCusor->m_pParent->AddSubOp(pTemp2);

					//Keep the m_hCusor in the same level of ot,
					m_opFilter.PushType(ot);
					m_hCusor = m_hCusor->m_pParent->m_pParent->m_pParent;    
					
					//Delete the temperary node.
					//????????????????
					//
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

					//Keep the m_hCusor in the same level of ot,
					m_opFilter.PushType(ot);
					m_hCusor = m_hCusor->m_pParent->m_pParent;    
/*
					pTemp->m_pParent = m_hCusor->m_pParent;
					pTemp->Reset(enXVSB_LEVEL3, prevOP);
					m_hCusor->m_pParent->AddSubOp(pTemp);

					//Keep the m_hCusor in the same level of ot,
					m_opFilter.PushType(ot);
					m_hCusor = m_hCusor->m_pParent->m_pParent->m_pParent;    
					
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
		}
	}
	return bRet;
}