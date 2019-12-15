// Project: Visual System Builder
//
// File Name: xvsb_enutil.h
//
// Description: The definition of the utility for expression parse
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
#ifndef __XVSB_ENUTIL_H__
#define __XVSB_ENUTIL_H__

#include "xvsb_enode.h"
#include <stack>

typedef std::stack<CVSB_hENode>			CVSB_ENodeStack;
typedef std::deque<CVSB_hENode>			CVSB_VarQueue;

class XVSB_CLASS CVSB_ENodeQ
{
//
// @access Attributes:
//
public:
	//@cmember Operation queue
	CVSB_OTypeQueue		m_TypeQ;

	//@cmember Operand queue
	CVSB_VarQueue		m_VarQ;

//
// @access Constructor/Destructor:
//
public:
	//@cmember Constructor
	CVSB_ENodeQ(void);

	//@cmember Destructor
	~CVSB_ENodeQ(void);

//
// @access Operations:
//
public:
	//@cmember Push the operation into queue
	void PushType(enXVSB_OPERATION& ot);

	//@cmember Push the operand into queue
	void PushVar(CVSB_hENode* pd);

	//@cmember Pop up the operation from queue
	enXVSB_OPERATION PopType(void);

	//@cmember Pop up the operand from queue
	CVSB_hENode PopVar(void);

	//@cmember Peep the operation from queue
	enXVSB_OPERATION PeekType(void);

	//@cmember Peep the operand from queue
	CVSB_hENode PeekVar(void);

	//@cmember Check the number of operations in the queue
	int GetTypeCount(void);

	//@cmember Check the number of operands in the queue
	int GetVarCount(void);
};

typedef std::stack<CVSB_ENodeQ*> CVSB_ENQStack;

class XVSB_CLASS CVSB_ENodeFilter
{
//
// @access Attributes:
//
public:
	//@cmember operation Q object stack
	CVSB_ENQStack		m_Stack;

//
// @access Constructor/Destructor:
//
public:
	//@cmember Constructor
	CVSB_ENodeFilter(void);

	//@cmember Destructor
	~CVSB_ENodeFilter(void);

//
// @access Operations:
//
public:
	//@cmember Create a new Q object and add into the stack
	void AddAction(void);

	//@cmember Remove all Q objects in the stack
	void RemoveTailAction(void);

	//@cmember Reset the stack
	void Reset(void);

	//@cmember Check the stack status
	bool IsValid(void);

	//@cmember Push the operation into the queue on the top of the Q stack
	void PushType(enXVSB_OPERATION& ot);

	//@cmember Push the operand into the queue on the top of the Q stack
	void PushVar(CVSB_hENode* pd);

	//@cmember Pop up the operation from the queue on the top of the Q stack
	enXVSB_OPERATION PopType(void);

	//@cmember Pop up the operand from the queue on the top of the Q stack
	CVSB_hENode PopVar(void);

	//@cmember Peek the operation from the queue on the top of the Q stack
	enXVSB_OPERATION PeekType(void);

	//@cmember Peek the operand from the queue on the top of the Q stack
	CVSB_hENode PeekVar(void);

	//@cmember Check the number of operations on the top of Q stack
	int GetTypeCount(void);

	//@cmember Check the number of operands on the top of Q stack
	int GetVarCount(void);

};

#endif
