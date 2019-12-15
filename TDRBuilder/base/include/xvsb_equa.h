// Project: Visual System Builder
//
// File Name: xvsb_equa.h
//
// Description: The definition of the equation class
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/27/2005	
//
// History:
// 1.    01/27/2005: Create	
//
#ifndef __XVSB_EQUAL_H__
#define __XVSB_EQUAL_H__

#include "xvsb_owner.h"
#include "xvsb_enode.h"
#include "xvsb_para.h"
#include "tvsb_cpputil.h"
#include <string>           
#include <vector>           


class XVSB_CLASS CVSB_Equation
{
//
// @access Constructor/Destructor:
//
public:
	//@cmember The Constructor
	CVSB_Equation(CVSB_OwnerBase* hOwner);

	//@cmember The Constructor
	CVSB_Equation(CVSB_OwnerBase* hOwner, const std::wstring& szLStr, const std::wstring& szRExp);

	//@cmember The Constructor
	CVSB_Equation(CVSB_OwnerBase* hOwner, const wchar_t* szLStr, const wchar_t* szRExp);

	//@cmember The Copy Constructor
	CVSB_Equation(const CVSB_Equation& hEqua);

	//@cmember The Destructor
	~CVSB_Equation();

//
// @access Operations:
//
public:
	//@cmember Clean up
	void Reset(void);

	//@cmember Clean up
	void CleanAll(void);

	//@cmember Initialize
	bool Startup(void);

	//@cmember Initialize
	bool Run(void);

	//@cmember Initialize
	bool Shutdown(void);

	//@cmember Set the left variable string
	void SetLVarStr(const std::wstring& szLStr);

	//@cmember Set the left variable string
	void SetLVarStr(const wchar_t* szLStr);

	//@cmember Get the left variable string
	std::wstring GetLVarStr(void);

	//@cmember Get the left variable string
	const wchar_t* GetLVarStr(void) const;

	//@cmember Set the right expression string
	void SetRExpStr(const std::wstring& szRExp);

	//@cmember Set the right expression string
	void SetRExpStr(const wchar_t* szRExp);

	//@cmember Get the right expression string
	std::wstring GetRExpStr(void);

	//@cmember Get the right expression string
	const wchar_t* GetRExpStr(void) const;

	//@cmember Attach to the owner
	bool SetOwner(CVSB_OwnerBase* hOwner);

	//@cmember Get the left variable object
	IVSB_DataBase* GetLVarData(void) const;

	//@cmember Get the right expression object
	CVSB_hENode GetRFormula(void) const;

	//@cmember Query error ocde
	enXVSB_ERRORCODE GetError(void) const;

	//@cmember Query error content information
	virtual std::wstring GetErrorInfo(void);
	
	//@cmember Query error content information
	virtual const wchar_t* GetErrorInfo(void) const;

	//@cmember Reset to rerun;
	bool ReSetup(void);

	//@cmember Get the right CPP format string;
	std::wstring GetCPPFmtRExpStr(void);

	//@cmember Get the equation string;
	std::wstring GetEquation(void);

	//@cmember Get the C++ format equation string;
	std::wstring GetCPPFmtEquation(void);

//
// @access Operations:
//
private:
	//@cmember Process the left variable
	bool _processleftvar(void);

	//@cmember Create the right side expression
	bool _createformula(void);

	//@cmember Attach left variable object
	bool _attachlvar(void);

//
// @access Attributes:
//
private:
	//@cmember The left variable presentation string
	std::wstring			m_LVarStr;

	//@cmember The left variable object
	CVSB_Parameter			m_LVar;

	//@cmember The right expression presentation string
	std::wstring			m_RExpStr;

	//@cmember The right expression object
	CVSB_hENode				m_RFormula;

	//@cmember Container object
	CVSB_OwnerBase*			m_hOwner;

	//@cmember Error code
	enXVSB_ERRORCODE		m_errCode;

	//@cmember Error information string
	mutable std::wstring 	m_errString;
};

typedef std::vector<CVSB_Equation*>							CVSB_EquaGroup;
typedef TVSB_Deletor<CVSB_Equation>							CVSB_EquaDelete;
typedef TVSB_Dealloc<CVSB_EquaGroup, CVSB_EquaDelete>		CVSB_EquaGroupFree;

#endif
