// Project: Visual System Builder
//
// File Name: xvsb_efactry.h
//
// Description: The definition of the factory class for expression creation
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
#ifndef __XVSB_EFACTRY_H__
#define __XVSB_EFACTRY_H__

#include "xvsb_enutil.h"

class XVSB_CLASS CVSB_ExpFactory
{
//
// @access Constructor/Destructor:
//
public:
	//@cmember Constructor
	CVSB_ExpFactory(void);

	//@cmember Destructor
	~CVSB_ExpFactory(void);

//
// @access Operations:
//
public:
	//@cmember Share the expression handle
	CVSB_hENode GetExpression(void);

	//@cmember Share the expression handle
	operator CVSB_hENode (void);

	//@cmember Reset everything
	void Reset(void);

	//@cmember Check process status
	bool IsInProcess(void);

	//@cmember The end process of the root node creation
	virtual bool StartRoot(void);

	//@cmember The end process of the root node creation
	virtual bool EndRoot(void);

	//@cmember Create the sub-root node
	virtual bool StartSubRoot(void);

	//@cmember The end process of the sub-root node creation
	virtual bool EndSubRoot(void);

	//@cmember Push the operand object into the stack
	virtual bool AddVariable(const CVSB_Parameter& param);

	//@cmember Push the operation into the stack
	virtual bool AddOperation(enXVSB_OPERATION ot);
							   
	//@cmember Check the number of operations on the top of Q stack
	long GetTCountInStack(void);

	//@cmember Check the number of operands on the top of Q stack
	long GetVCountInStack(void);

	//@cmember Peek the operation from the top of the Q stack
	enXVSB_OPERATION PeekTypeInStack(void);

//
//@access Attributes
//
private:
	//@cmember The tree structure storage of the expression
	CVSB_hENode			m_hExpress;     

	//@cmember The tree structure storage of the expression
	bool				m_IsShared;  

	//@cmember The flag of processing
	bool			    m_bInProcess;

	//@cmember The sub tree structure list for the sub expression
	CVSB_ENodeStack		m_SubExps;   

	//@cmember The indicator to point the current position of expression tree node
	CVSB_hENode			m_hCusor;    

	//@cmember The stack to store operation and data and create the node for express tree
	CVSB_ENodeFilter	m_opFilter;    
};

#endif