// Project: Visual System Builder
//
// File Name: xvsb_fnode.h
//
// Description: The definition of the class function object internal expression node
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
#ifndef __XVSB_FNODE_H__
#define __XVSB_FNODE_H__

#include "xvsb_pre.h"
#include "xvsb_defs.h"
#include "ivsb_datbas.h"
#include "xvsb_fpunit.h"
#include "tvsb_cpputil.h"
#include "xvsb_clsfn.h"
#include <vector>

class XVSB_CLASS CVSB_CFnNode;

typedef std::vector<CVSB_CFnNode*>							CVSB_CFnNodeList;
typedef TVSB_Deletor<CVSB_CFnNode>							CVSB_CFnNodeDelete;
typedef TVSB_Dealloc<CVSB_CFnNodeList, CVSB_CFnNodeDelete>	CVSB_CFnNodeFree;


class XVSB_CLASS CVSB_CFnNode
{
//
// @access Constructor/Destructor
//
public:
	//@cmember Constructor
	CVSB_CFnNode(void);

	//@cmember Constructor
	CVSB_CFnNode(CVSB_CFnNode* pParent, enXVSB_PRIORITY lvl = enXVSB_LEVEL_ROOT, enXVSB_OPERATION oType = enXVSB_NONE);

	//@cmember Constructor
	CVSB_CFnNode(CVSB_CFParamUnitBase* param, CVSB_CFnNode* pParent = NULL, enXVSB_PRIORITY lvl = enXVSB_LEVEL_ROOT, enXVSB_OPERATION oType = enXVSB_NONE);

	//@cmember Destructor
	virtual ~CVSB_CFnNode(void);

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
	void AddSubOp(CVSB_CFnNode* subOp);

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
	void SetParentNode(CVSB_CFnNode* pParent);

	//@cmember Check the sub-operation list simplicity
	bool IsSubOpSimple(void);

	//@cmember Check the existance of root node
	bool HasRootNode(void);

	//@cmember Set the operand object	
	void SetOperand(CVSB_CFParamUnitBase* param);

	//@cmember Set the operand object	
	bool AttachVarOperand(IVSB_DataBase* pData);

	//@cmember Set the ownership	
	void AttachOwner(CVSB_Method* hOwner);

	//@cmember Calculation
	bool Run(IVSB_DataBase* pInPrev = NULL);

	//@cmember Clean result
	bool ResetResult(void);

	//@cmember Get Operand parameter type
	CVSB_ParamType GetOperandParamType(void);

//
//@access Operation
//
private:
	//@cmember The calculation
	bool _calculate(IVSB_DataBase* pInput, IVSB_DataBase* pOperand);

//
// @access Attributes
//
public:
	//@cmember Sub-expression
	CVSB_CFnNodeList			m_SubOps;

	//@cmember The parent node
	CVSB_CFnNode*				m_pParent;

	//@cmember The onwer/container 
	CVSB_Method*				m_hOwner;

//
// @access Attributes
//
protected:
	//@cmember The operand object
	CVSB_CFParamUnitBase*		m_Operand;

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

typedef CVSB_CFnNode* CVSB_hCFnNode;

class XVSB_CLASS CVSB_CFnNodeCreate
{
public:
	CVSB_hCFnNode operator()(void);
	CVSB_hCFnNode operator()(CVSB_CFnNode* pParent, enXVSB_PRIORITY lvl = enXVSB_LEVEL_ROOT, enXVSB_OPERATION oType = enXVSB_NONE);
	CVSB_hCFnNode operator()(CVSB_CFParamUnitBase* param, CVSB_CFnNode* pParent = NULL, enXVSB_PRIORITY lvl = enXVSB_LEVEL_ROOT, enXVSB_OPERATION oType = enXVSB_NONE);
};

class XVSB_CLASS CXOS_CFnNodeRelease
{
public:
	void operator()(CVSB_hCFnNode& hENdoe);
};

#endif