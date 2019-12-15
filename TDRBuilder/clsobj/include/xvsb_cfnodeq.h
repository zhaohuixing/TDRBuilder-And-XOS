// Project: Visual System Builder
//
// File Name: xvsb_cfnodeq.h
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
#ifndef __XVSB_CFNODEQ_H__
#define __XVSB_CFNODEQ_H__

#include "xvsb_cfstack.h"
#include "xvsb_cfqman.h"

class CVSB_CFNodeQFilter : public CVSB_CFNodeQBase
{
public:
	CVSB_CFNodeQFilter(CVSB_hCFnNode hCusor = NULL);
	CVSB_CFNodeQFilter(CVSB_hCFnNode hCusor, CVSB_Method* pOwner);
	CVSB_CFNodeQFilter(CVSB_hCFnNode hCusor, CVSB_CFNodeQBase* prevQ);
	CVSB_CFNodeQFilter(CVSB_hCFnNode hCusor, CVSB_CFnQMan* pQM);
	CVSB_CFNodeQFilter(CVSB_hCFnNode hCusor, CVSB_Method* pOwner, CVSB_CFNodeQBase* prevQ, CVSB_CFnQMan* pQM);
	virtual ~CVSB_CFNodeQFilter();

public:
	virtual enXVSB_NODEQTYPE GetQtype(void){return enXVSB_NODEQ_NODE;}
	virtual bool IsNodeQ(void){return true;}
	virtual bool IsVariableQ(void){return false;}

	bool AddInteger(__int64 n);
	bool AddFloat(double d);
	bool AddByte(unsigned char n);
	bool AddBooleanConstant(bool bConst);
	bool AddMathOp(enXVSB_OPERATION op);

	bool AddOperand(CVSB_CFParamUnitBase* pOp);

//
// @access Operations:
//
public:
	//@cmember Push the operation into queue
	void PushType(enXVSB_OPERATION& ot);

	//@cmember Push the operand into queue
	void PushVar(CVSB_hCFnNode* pd);

	//@cmember Pop up the operation from queue
	enXVSB_OPERATION PopType(void);

	//@cmember Pop up the operand from queue
	CVSB_hCFnNode PopVar(void);

	//@cmember Peep the operation from queue
	enXVSB_OPERATION PeekType(void);

	//@cmember Peep the operand from queue
	CVSB_hCFnNode PeekVar(void);

	//@cmember Check the number of operations in the queue
	int GetTypeCount(void);

	//@cmember Check the number of operands in the queue
	int GetVarCount(void);

protected:
	CVSB_CFOperandQ     m_OperandQ;
	CVSB_OTypeQueue		m_OperationQ;
};


#endif
