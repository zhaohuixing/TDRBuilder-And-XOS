// Project: Visual System Builder
//
// File Name: ivsb_varkey.h
//
// Description: The definition of the variable key for process
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
#ifndef __IVSB_VARKEY_H__
#define __IVSB_VARKEY_H__

#include "ivsb_datbas.h"
#include "ivsb_cpputil.h"
#include <string>
#include <assert.h>

class CVSB_VariableKey
{
public:
	CVSB_VariableKey(const CVSB_ClassType& type, const std::wstring& sname) : m_Type(type), m_Name(sname){}; 
	CVSB_VariableKey(const CVSB_ClassType& type, const wchar_t* sname) : m_Type(type), m_Name(sname){}; 
	~CVSB_VariableKey(){};

public:
	inline CVSB_ClassType	GetType(void) const {return m_Type;}
	inline std::wstring		GetName(void) const {return m_Name;}

	inline void	Set(const CVSB_ClassType& type, const std::wstring& sname)
	{
		m_Type = type;
		m_Name = sname;

#ifdef _XSVM_DEBUG_
		assert(!m_Name.empty());
#endif
	}
	inline void	Set(const CVSB_ClassType& type, const wchar_t* sname)
	{
		m_Type = type;
		m_Name = sname;

#ifdef _XSVM_DEBUG_
		assert(!m_Name.empty());
#endif
	}
	inline void	SetType(const CVSB_ClassType& type)
	{
		m_Type = type;
	}
	inline void	SetName(const std::wstring& sname)
	{
		m_Name = sname;

#ifdef _XSVM_DEBUG_
		assert(!m_Name.empty());
#endif
	}
	inline void	SetName(const wchar_t* sname)
	{
		m_Name = sname;
		
#ifdef _XSVM_DEBUG_
		assert(!m_Name.empty());
#endif
	}

	operator CVSB_ClassType	(void) {return m_Type;}
	operator std::wstring	(void) {return m_Name;}
	CVSB_VariableKey& operator = (const CVSB_VariableKey& var)
	{
		m_Type = var.GetType();
		m_Name = var.GetName();

#ifdef _XSVM_DEBUG_
		assert(!m_Name.empty());
#endif

		return *this;
	}

	//@cfunction Equal to
	friend bool operator == (const CVSB_VariableKey& v1, const CVSB_VariableKey& v2)
	{
		return (v1.m_Type == v2.m_Type && v1.m_Name == v2.m_Name);
	}

	//@cfunction Not equal to
	friend bool operator != (const CVSB_VariableKey& v1, const CVSB_VariableKey& v2)
	{
		return !(v1 == v2);
	}

	//@cfunction Comparsion
	friend bool operator < (const CVSB_VariableKey& v1, const CVSB_VariableKey& v2)
	{
		bool bRet = (v1.m_Type < v2.m_Type);
		if(!bRet)
		{
			if(v1.m_Type == v2.m_Type)
			{
				bRet = (v1.m_Name < v2.m_Name);
			}
		}
	}

	//@cfunction Comparsion
	friend bool operator <= (const CVSB_VariableKey& v1, const CVSB_VariableKey& v2)
	{
		bool bRet = (v1.m_Type <= v2.m_Type);
		if(bRet)
		{
			if(v1.m_Type == v2.m_Type)
			{
				bRet = (v1.m_Name <= v2.m_Name);
			}
		}
	}

	//@cfunction Comparsion
	friend bool operator > (const CVSB_VariableKey& v1, const CVSB_VariableKey& v2)
	{
		return (v2 < v1);
	}

	//@cfunction Comparsion
	friend bool operator >= (const CVSB_VariableKey& v1, const CVSB_VariableKey& v2)
	{
		return (v2 <= v1);
	}


private:
	CVSB_ClassType		m_Type;
	std::wstring		m_Name;
};

#endif