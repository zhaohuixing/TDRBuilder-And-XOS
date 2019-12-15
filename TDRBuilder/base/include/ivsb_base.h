// Project: Visual System Builder
//
// File Name: ivsb_base.h
//
// Description: The definition of the base class for all
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/12/2005	
//
// History:
// 1.    01/12/2005: Create	
//
#ifndef __IVSB_BASE_H__
#define __IVSB_BASE_H__

#include "xvsb_clstype.h"

class IVSB_Base
{
public:
	IVSB_Base() : m_Type(), m_szName(L""){}; 
	IVSB_Base(const CVSB_ClassType& type) : m_Type(type), m_szName(L""){}; 
	IVSB_Base(const std::wstring&	szName) : m_Type(), m_szName(szName){}; 
	IVSB_Base(const std::wstring& szNSpace, const std::wstring& szType, const std::wstring& szClass) : m_Type(szNSpace, szType, szClass), m_szName(L""){}; 
	IVSB_Base(const std::wstring& szNSpace, const std::wstring& szType, const std::wstring& szClass, std::wstring& szName) : m_Type(szNSpace, szType, szClass), m_szName(szName){}; 
	IVSB_Base(const wchar_t* szName) : m_Type(), m_szName(szName){}; 
	IVSB_Base(const wchar_t* szNSpace, const wchar_t* szType, const wchar_t* szClass) : m_Type(szNSpace, szType, szClass), m_szName(L""){}; 
	IVSB_Base(const wchar_t* szNSpace, const wchar_t* szType, const wchar_t* szClass, const wchar_t* szName) : m_Type(szNSpace, szType, szClass), m_szName(szName){}; 

	virtual ~IVSB_Base(void){};

	inline virtual CVSB_ClassType GetType(void){return m_Type;}
	inline virtual void SetType(const CVSB_ClassType& type){m_Type = type;}
	inline virtual void SetType(std::wstring& szNSpace, std::wstring& szType, std::wstring& szClass)
	{
		m_Type.Set(szNSpace, szType, szClass);
	}
	inline virtual void SetType(const wchar_t* szNSpace, const wchar_t* szType, const wchar_t* szClass)
	{
		m_Type.Set(szNSpace, szType, szClass);
	}

	inline virtual std::wstring& GetName(void){return m_szName;}
	inline virtual const wchar_t* GetName(void) const {return m_szName.c_str();}
	inline virtual void SetName(const std::wstring& szName){m_szName = szName;}
	inline virtual void SetName(const wchar_t* szName){m_szName = szName;}

	inline virtual bool IsSameType(const CVSB_ClassType& type) const {return (m_Type == type);}
	inline virtual bool IsSame(const CVSB_ClassType& type) const {return (m_Type == type);}
	inline virtual bool IsSame(const std::wstring& szNSpace) const {return m_Type.IsSame(szNSpace);}
	inline virtual bool IsSame(const wchar_t* szNSpace) const {return m_Type.IsSame(szNSpace);}
	inline virtual bool IsSame(const std::wstring& szNSpace, const std::wstring& szType) const {return m_Type.IsSame(szNSpace, szType);}
	inline virtual bool IsSame(const wchar_t* szNSpace, const wchar_t* szType) const {return m_Type.IsSame(szNSpace, szType);} 
	inline virtual bool IsSame(const std::wstring& szNSpace, const std::wstring& szType, const std::wstring& szClass) const 
	{
		return m_Type.IsSame(szNSpace, szType, szClass);
	}
	inline virtual bool IsSame(const wchar_t* szNSpace, const wchar_t* szType, const wchar_t* szClass) const 
	{
		return m_Type.IsSame(szNSpace, szType, szClass);
	}


	//@cmember  Clone the object
	virtual bool Clone(IVSB_Base** ppObj) = 0;

	//@cmember  Clone the object
	virtual bool Clone(IVSB_Base** ppObj, const std::wstring& szName) = 0;

	//@cmember  Clone the object
	virtual bool Clone(IVSB_Base** ppObj, const wchar_t* szName) = 0;

protected:
	CVSB_ClassType				m_Type;			//The type atrribute
	std::wstring				m_szName;		//The object name
};

#endif