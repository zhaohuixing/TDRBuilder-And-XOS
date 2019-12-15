// Project: Visual System Builder
//
// File Name: xvsb_enode.h
//
// Description: The definition of the expression node
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
#ifndef __XVSB_ENODE_H__
#define __XVSB_ENODE_H__

#include "xvsb_pre.h"
#include "xvsb_defs.h"
#include "ivsb_datbas.h"
#include "xvsb_para.h"
#include "tvsb_cpputil.h"
#include "xvsb_owner.h"
#include <vector>

class XVSB_CLASS CVSB_ExpressNode
{
//
// @access Typedef
//
public:
	typedef std::vector<CVSB_ExpressNode*>					CVSB_ExpressList;
    typedef CVSB_ExpressList::iterator						CVSB_ExpIterator;
	typedef TVSB_Deletor<CVSB_ExpressNode>					CVSB_ExpDelete;
	typedef TVSB_Dealloc<CVSB_ExpressList, CVSB_ExpDelete>	CVSB_ExpFree;

//
// @access Constructor/Destructor
//
public:
	//@cmember Constructor
	CVSB_ExpressNode(void);

	//@cmember Constructor
	CVSB_ExpressNode(CVSB_ExpressNode* pParent, enXVSB_PRIORITY lvl = enXVSB_LEVEL_ROOT, enXVSB_OPERATION oType = enXVSB_NONE);

	//@cmember Constructor
	CVSB_ExpressNode(const CVSB_Parameter& param, CVSB_ExpressNode* pParent = NULL, enXVSB_PRIORITY lvl = enXVSB_LEVEL_ROOT, enXVSB_OPERATION oType = enXVSB_NONE);

	//@cmember Destructor
	virtual ~CVSB_ExpressNode(void);

//
//@access Operations
//
public:
	//@cmember Clear everthing
    void Clear(void);

	//@cmember Clean buffer
    void CleanBuffer(void);

	//@cmember Type conversion
    operator IVSB_DataBase* ();

	//@cmember Get result object
    IVSB_DataBase* GetResult(void);

	//@cmember Set the node as a sub-node for sub-expression under bracket
    void SetAsSubRoot(void);

	//@cmember Clean the sub-node flag
    void CleanSubRootFlag(void);

	//@cmember Add the sub-node into sub expression list
	void AddSubOp(CVSB_ExpressNode* subOp);

	//@cmember Reset operation level and type	
	bool Reset(enXVSB_PRIORITY	lvl, enXVSB_OPERATION oType);

	//@cmember Check the sub-operation list
	bool IsDirty(void);

	//@cmember Get operation level
	enXVSB_PRIORITY GetLevel(void);

	//@cmember Set operation level
	void SetLevel(enXVSB_PRIORITY lvl);

	//@cmember Set operation type
	enXVSB_OPERATION GetOperation(void);

	//@cmember Set operation type
	void SetOperation(enXVSB_OPERATION op);

	//@cmember Set the parent node
	void SetParentNode(CVSB_ExpressNode* pParent);

	//@cmember Check the sub-operation list simplicity
	bool IsSubOpSimple(void);

	//@cmember Check the existance of root node
	bool HasRootNode(void);

	//@cmember Set the operand object	
	void SetOperand(const CVSB_Parameter& param);

	//@cmember Set the operand object	
	bool AttachVarOperand(IVSB_DataBase* pData);

	//@cmember Set the ownership	
	void AttachOwner(CVSB_OwnerBase* hOwner);

	//@cmember Calculation
	bool Run(IVSB_DataBase* pInPrev = NULL);

	//@cmember Clean result
	bool ResetResult(void);
//
//@access Operation
//
private:
	//@cmember Attach operand
	bool _attachoperand(void);

	//@cmember The calculation
	bool _calculate(IVSB_DataBase* pInput, IVSB_DataBase* pOperand);

//
// @access Attributes
//
public:
	//@cmember Sub-expression
	CVSB_ExpressList			m_SubOps;

	//@cmember The parent node
	CVSB_ExpressNode*			m_pParent;

	//@cmember The onwer/container 
	CVSB_OwnerBase*				m_hOwner;

//
// @access Attributes
//
protected:
	//@cmember The operand object
	CVSB_Parameter				m_Operand;

	//@cmember The operation
	enXVSB_OPERATION			m_Operate;

	//@cmember The result
	IVSB_DataBase*				m_pResult;

	//@cmember The operation level
	enXVSB_PRIORITY				m_Level;		// Root: The entry of the simple expression,m_pResult, m_pParent, m_SubLevelOps
												//       make sense, others not be cared (empty or null) 
												// Level1, Level2, Level3: math operations

	//@cmember Sub root node indicator
	bool						m_bSubRootNode;  
};

typedef CVSB_ExpressNode* CVSB_hENode;

class XVSB_CLASS CVSB_ENodeCreator
{
public:
	CVSB_hENode operator()(void);
	CVSB_hENode operator()(CVSB_ExpressNode* pParent, enXVSB_PRIORITY lvl = enXVSB_LEVEL_ROOT, enXVSB_OPERATION oType = enXVSB_NONE);
	CVSB_hENode operator()(const CVSB_Parameter& param, CVSB_ExpressNode* pParent = NULL, enXVSB_PRIORITY lvl = enXVSB_LEVEL_ROOT, enXVSB_OPERATION oType = enXVSB_NONE);
};

class XVSB_CLASS CXOS_EUnitRelease
{
public:
	void operator()(CVSB_hENode& hENdoe);
};

#endif