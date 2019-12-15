// Project: Visual System Builder
//
// File Name: xvsb_nspace.h
//
// Description: The definition of the namespace object class
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 05/29/2005	
//
// History:
// 1.    05/29/2005: Create	
//
#ifndef __XVSB_NSPACE_H__
#define __XVSB_NSPACE_H__

#include "xvsb_pre.h"
#include "xvsb_defs.h"
#include "ivsb_datbas.h"
#include "xvsb_clsunit.h"

class XVSB_CLASS CVSB_Namespace
{
public:
	CVSB_Namespace(std::wstring& szNS);
	CVSB_Namespace(const wchar_t* szNS);
	virtual ~CVSB_Namespace(void);

public:
	std::wstring GetNameSpace(void){return m_szNamespace;}

	bool AddNewClass(std::wstring& szClass);
	bool AddNewClass(const wchar_t* szClass);
	bool AddNewClass(std::wstring& szClass, CVSB_ClassType& cType);
	bool AddNewClass(const wchar_t* szClass, CVSB_ClassType& cType);

	bool RemoveClass(std::wstring& szClass);
	bool RemoveClass(const wchar_t* szClass);
	bool RemoveClass(const CVSB_ClassType& cType);

	bool HasClass(std::wstring& szClass);
	bool HasClass(const wchar_t* szClass);
	bool HasClass(const CVSB_ClassType& cType);

	CVSB_ClassUnit* QueryClassUnit(std::wstring& szClass);
	CVSB_ClassUnit* QueryClassUnit(const wchar_t* szClass);
	CVSB_ClassUnit* QueryClassUnit(const CVSB_ClassType& cType);

	CVSB_ClassObject* QueryClass(std::wstring& szClass);
	CVSB_ClassObject* QueryClass(const wchar_t* szClass);
	CVSB_ClassObject* QueryClass(const CVSB_ClassType& cType);

	bool HasUseClass(const CVSB_ClassType& cType);
	CVSB_ClassObject* QueryUseClass(const CVSB_ClassType& cType);

	bool RenameClass(std::wstring& szOldClass, std::wstring& szNewClass);
	bool RenameClass(const wchar_t* szOldClass, const wchar_t* szNewClass);

private:
	std::wstring		m_szNamespace;

public:
	CVSB_ClassUnitList	m_clsList;
};

#endif