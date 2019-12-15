// Project: Visual System Builder
//
// File Name: xvsb_cfstack.h
//
// Description: The definition of the variable type class function parameter basic unit object
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 05/18/2005	
//
// History:
// 1.    05/18/2005: Create	
//
#ifndef __XVSB_CFSTACK_H__
#define __XVSB_CFSTACK_H__

#include "xvsb_pre.h"
#include "xvsb_defs.h"
#include "xvsb_clsfn.h"
#include "xvsb_fnode.h"


class XVSB_CLASS CVSB_CFnQMan;

class XVSB_CLASS CVSB_CFNodeQBase
{
public:
	CVSB_CFNodeQBase(CVSB_hCFnNode hCusor = NULL)
	{
		m_pOwner = NULL; 
		m_prevQ = NULL;
		m_QManager = NULL;
		m_hCusor = hCusor;
	}
	
	CVSB_CFNodeQBase(CVSB_hCFnNode hCusor, CVSB_Method* pOwner)
	{
		m_pOwner = pOwner;
		m_prevQ = NULL;
		m_QManager = NULL;
		m_hCusor = hCusor;
	}

	CVSB_CFNodeQBase(CVSB_hCFnNode hCusor, CVSB_CFNodeQBase*	prevQ)
	{
		m_pOwner = NULL;
		m_prevQ = prevQ;
		m_QManager = NULL;
		m_hCusor = hCusor;
	}

	CVSB_CFNodeQBase(CVSB_hCFnNode hCusor, CVSB_CFnQMan*	pQM)
	{
		m_pOwner = NULL;
		m_prevQ = NULL;
		m_QManager = pQM;
		m_hCusor = hCusor;
	}

	CVSB_CFNodeQBase(CVSB_hCFnNode hCusor, CVSB_Method* pOwner, CVSB_CFNodeQBase*	prevQ, CVSB_CFnQMan* pQM)
	{
		m_pOwner = pOwner;
		m_prevQ = prevQ;
		m_QManager = pQM;
		m_hCusor = hCusor;
	}

	virtual ~CVSB_CFNodeQBase()
	{
		m_pOwner = NULL; 
		m_prevQ = NULL;
		m_QManager = NULL;
		m_hCusor = NULL;
	}

public:
	virtual enXVSB_NODEQTYPE GetQtype() = 0;
	virtual bool IsNodeQ() = 0;
	virtual bool IsVariableQ() = 0;

	void SetQwner(CVSB_Method* pOwner){m_pOwner = pOwner;}
	void SetQMan(CVSB_CFnQMan* pQMan){m_QManager = pQMan;}
	void SetPrevQ(CVSB_CFNodeQBase* pPrevQ){m_prevQ = pPrevQ;}
	void SetQCursor(CVSB_hCFnNode hCusor){m_hCusor = hCusor;}
	CVSB_hCFnNode GetQCursor(void){return m_hCusor;}

protected:
	CVSB_Method*		m_pOwner;
	CVSB_CFNodeQBase*	m_prevQ;
	CVSB_CFnQMan*		m_QManager;
	CVSB_hCFnNode		m_hCusor;
};

typedef std::stack<CVSB_CFNodeQBase*>	CVSB_CFNodeQStack;
typedef std::stack<CVSB_hCFnNode>		CVSB_CFNodeStack;
typedef std::deque<CVSB_hCFnNode>		CVSB_CFOperandQ;


#endif
