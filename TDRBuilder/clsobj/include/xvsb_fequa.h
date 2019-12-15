// Project: Visual System Builder
//
// File Name: xvsb_fequa.h
//
// Description: The definition of the equation class for class member function object
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
#ifndef __XVSB_FEQUA_H__
#define __XVSB_FEQUA_H__

#include "xvsb_clsfn.h"
#include "xvsb_fnode.h"
#include "xvsb_fpunit.h"
#include "tvsb_cpputil.h"
#include "ivsb_fnbase.h"
#include <string>           
#include <vector>           


class XVSB_CLASS CVSB_CFnEquation : public IVSB_CFnUnitBase
{
//
// @access Constructor/Destructor:
//
public:
	//@cmember The Constructor
	CVSB_CFnEquation(CVSB_Method* hOwner);

	//@cmember The Constructor
	CVSB_CFnEquation(CVSB_Method* hOwner, const std::wstring& szLStr, const std::wstring& szRExp);

	//@cmember The Constructor
	CVSB_CFnEquation(CVSB_Method* hOwner, const wchar_t* szLStr, const wchar_t* szRExp);

	//@cmember The Copy Constructor
	CVSB_CFnEquation(const CVSB_CFnEquation& hEqua);

	//@cmember The Destructor
	virtual ~CVSB_CFnEquation();

//
// @access Operations:
//
public:
	//@cmember Clean up
	virtual void Reset(void);

	//@cmember Clean up
	virtual void CleanAll(void);

	//@cmember Initialize
	virtual bool Startup(void);

	//@cmember Initialize
	virtual bool Run(void);

	//@cmember Initialize
	virtual bool Shutdown(void);

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

	//@cmember Get the left variable object
	IVSB_DataBase* GetLVarData(void) const;

	//@cmember Get the right expression object
	CVSB_hCFnNode GetRFormula(void) const;

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
	CVSB_CFParamUnitBase*	m_pLVar;

	//@cmember The right expression presentation string
	std::wstring			m_RExpStr;

	//@cmember The right expression object
	CVSB_hCFnNode			m_RFormula;
};

#endif
