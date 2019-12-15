// Project: Visual System Builder
//
// File Name: xvsb_owner.h
//
// Description: The definition of the ownership base interface
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/19/2005	
//
// History:
// 1.    01/19/2005: Create	
//
#ifndef __XVSB_OWNER_H__
#define __XVSB_OWNER_H__

#include "ivsb_base.h"
#include "xvsb_macro.h"
#include "xvsb_defs.h"
#include "xvsb_helper.h"
#include "xvsb_vartbl.h"
#include "ivsb_callback.h"


class XVSB_CLASS CVSB_OwnerBase : public IVSB_Base
{
//
// @access Constructor/Destructor
//
public:
	//@cmember Constructor
	CVSB_OwnerBase(void);

	//@cmember Constructor
	CVSB_OwnerBase(const wchar_t* szName);

	//@cmember Constructor
	CVSB_OwnerBase(const std::wstring& szName);

	//@cmember Destructor
	virtual ~CVSB_OwnerBase(void);

//
// @access Operations
//
public:
	//@cmember Add input variable
	bool AddInputVar(IVSB_DataBase* pVar, const std::wstring& name);

	//@cmember Add input variable
	bool AddInputVar(IVSB_DataBase* pVar, const wchar_t* name);

	//@cmember Assign input variable
	bool AssignInputVarValue(const std::wstring& name, IVSB_DataBase* pVal);

	//@cmember Assign input variable
	bool AssignInputVarValue(const wchar_t* name, IVSB_DataBase* pVal);

	//@cmember Replace input variable
	bool ReplaceInputVar(IVSB_DataBase* pVar, const std::wstring& name);

	//@cmember Replace input variable
	bool ReplaceInputVar(IVSB_DataBase* pVar, const wchar_t* name);

	//@cmember Add Output variable
	bool AddOutputVar(IVSB_DataBase* pVar);

	//@cmember Add Output variable
	bool AddOutputVar(IVSB_DataBase* pVar, const std::wstring& name);

	//@cmember Add Output variable
	bool AddOutputVar(IVSB_DataBase* pVar, const wchar_t* name);

	//@cmember Assign Output variable
	bool AssignOutputVarValue(const std::wstring& name, IVSB_DataBase* pVal);

	//@cmember Assign Output variable
	bool AssignOutputVarValue(const wchar_t* name, IVSB_DataBase* pVal);

	//@cmember Replace Output variable
	bool ReplaceOutputVar(IVSB_DataBase* pVar, const std::wstring& name);

	//@cmember Replace Output variable
	bool ReplaceOutputVar(IVSB_DataBase* pVar, const wchar_t* name);

	//@cmember Add local variable
	bool AddLocalVar(IVSB_DataBase* pVar);

	//@cmember Add local variable
	bool AddLocalVar(IVSB_DataBase* pVar, const std::wstring& name);

	//@cmember Add local variable
	bool AddLocalVar(IVSB_DataBase* pVar, const wchar_t* name);

	//@cmember Assign local variable
	bool AssignLocalVarValue(const std::wstring& name, IVSB_DataBase* pVal);

	//@cmember Assign local variable
	bool AssignLocalVarValue(const wchar_t* name, IVSB_DataBase* pVal);

	//@cmember Replace local variable
	bool ReplaceLocalVar(IVSB_DataBase* pVar, const std::wstring& name);

	//@cmember Replace local variable
	bool ReplaceLocalVar(IVSB_DataBase* pVar, const wchar_t* name);

	//@cmember Get variable
	IVSB_DataBase* GetVar(const std::wstring& name);

	//@cmember Get variable
	IVSB_DataBase* GetVar(const wchar_t* name);

	//@cmember Get variable
	IVSB_DataBase* GetInputVar(const std::wstring& name);

	//@cmember Get variable
	IVSB_DataBase* GetInputVar(const wchar_t* name);

	//@cmember Get variable
	IVSB_DataBase* GetOutputVar(const std::wstring& name);

	//@cmember Get variable
	IVSB_DataBase* GetOutputVar(const wchar_t* name);

	//@cmember Get variable
	IVSB_DataBase* GetLocalVar(const std::wstring& name);

	//@cmember Get variable
	IVSB_DataBase* GetLocalVar(const wchar_t* name);

	//@cmember Check variable existance
	bool HasVar(const std::wstring& name);

	//@cmember Check variable existance
	bool HasVar(const wchar_t* name);

	//@cmember Check input variable existance
	bool IsInputVar(const std::wstring& name);

	//@cmember Check input variable existance
	bool IsInputVar(const wchar_t* name);

	//@cmember Check Output variable existance
	bool IsOutputVar(const std::wstring& name);

	//@cmember Check Output variable existance
	bool IsOutputVar(const wchar_t* name);

	//@cmember Check local variable existance
	bool IsLocalVar(const std::wstring& name);

	//@cmember Check local variable existance
	bool IsLocalVar(const wchar_t* name);

	//@cmember Remove variable (non input)
	bool RemoveVar(const std::wstring& name);

	//@cmember Remove variable (non input)
	bool RemoveVar(const wchar_t* name);

	//@cmember Remove input variable
	bool RemoveInputVar(const std::wstring& name);

	//@cmember Remove Output variable
	bool RemoveInputVar(const wchar_t* name);

	//@cmember Remove Output variable
	bool RemoveOutputVar(const std::wstring& name);

	//@cmember Remove Output variable
	bool RemoveOutputVar(const wchar_t* name);

	//@cmember Remove local variable
	bool RemoveLocalVar(const std::wstring& name);

	//@cmember Remove local variable
	bool RemoveLocalVar(const wchar_t* name);

	//@cmember Remove all input variables
	void CleanUpInput(void);

	//@cmember Remove all Output variables
	void CleanUpOutput(void);

	//@cmember Remove all local variables
	void CleanUpLocal(void);

	//@cmember Remove all variables
	void CleanUpAllVars(void);

	//@cmember Reset variable to default value
	void ResetVars(void);

	//@cmember Reset input variable to default value
	void SetInputDefaultVars(void);

	//@cmember Set Callback object
	virtual void SetCallBack(IVSB_CallBack*	pCallBack);

	//@cmember Set Input variables printout line count
	virtual int GetInputPrintLineCount(void) const;

	//@cmember Set Output variables printout line count
	virtual int GetOutputPrintLineCount(void) const;

	//@cmember Set Local variables printout line count
	virtual int GetLocalPrintLineCount(void) const;

	//@cmember Add both variable
	bool AddBothVar(IVSB_DataBase* pVar, const std::wstring& name);

	//@cmember Add both variable
	bool AddBothVar(IVSB_DataBase* pVar, const wchar_t* name);

	//@cmember Assign both variable
	bool AssignBothVarValue(const std::wstring& name, IVSB_DataBase* pVal);

	//@cmember Assign both variable
	bool AssignBothVarValue(const wchar_t* name, IVSB_DataBase* pVal);

	//@cmember Replace both variable
	bool ReplaceBothVar(IVSB_DataBase* pVar, const std::wstring& name);

	//@cmember Replace both variable
	bool ReplaceBothVar(IVSB_DataBase* pVar, const wchar_t* name);

	//@cmember Get both variable
	IVSB_DataBase* GetBothVar(const std::wstring& name);

	//@cmember Get both variable
	IVSB_DataBase* GetBothVar(const wchar_t* name);

	//@cmember Check both variable existance
	bool IsBothVar(const std::wstring& name);

	//@cmember Check both variable existance
	bool IsBothVar(const wchar_t* name);

	//@cmember Remove both variable
	bool RemoveBothVar(const std::wstring& name);

	//@cmember Remove both variable
	bool RemoveBothVar(const wchar_t* name);

	//@cmember Remove all local variables
	void CleanUpBoth(void);

	//@cmember Set Local variables printout line count
	virtual int GetBothPrintLineCount(void) const;

	virtual void ResetInputVars(void);
	virtual void ResetOutputVars(void);
	virtual void ResetBothVars(void);
	virtual void ResetLocalVars(void);
	virtual void ResetAllVars(void);

	//@cmember Validate variable string
	virtual bool ValidateVariable(const wchar_t* name);

	//@cmember Validate variable string
	virtual bool ValidateVariable(const std::wstring& name);

	//@cmember Validate input variable string
	virtual bool ValidateInputVariable(const wchar_t* name);

	//@cmember Validate input variable string
	virtual bool ValidateInputVariable(const std::wstring& name);

	//@cmember Validate output variable string
	virtual bool ValidateOutputVariable(const wchar_t* name);

	//@cmember Validate output variable string
	virtual bool ValidateOutputVariable(const std::wstring& name);

	//@cmember Validate input/output variable string
	virtual bool ValidateBothVariable(const wchar_t* name);

	//@cmember Validate input/output variable string
	virtual bool ValidateBothVariable(const std::wstring& name);

	//@cmember Validate local variable string
	virtual bool ValidateLocalVariable(const wchar_t* name);

	//@cmember Validate local variable string
	virtual bool ValidateLocalVariable(const std::wstring& name);

	//@cmember Check the variable is class type or not
	virtual bool IsClassVar(const wchar_t* name);

	//@cmember Check the variable is class type or not
	virtual bool IsClassVar(const std::wstring& name);

//
// @access Attributes
//
public:
	//@cmember Input variable table
	CVSB_VarTable		m_InputVars;

	//@cmember Output variable table
	CVSB_VarTable		m_OutputVars;

	//@cmember Input/Output variable table
	CVSB_VarTable		m_BothVars;


	//@cmember Call back object
	IVSB_CallBack*		m_pCallBack;

//
// @access Attributes
//
public:
	//@cmember Local variable table
	CVSB_VarTable		m_LocalVars;

	//@cmember Name
	//std::wstring		m_sName;
};


#endif
