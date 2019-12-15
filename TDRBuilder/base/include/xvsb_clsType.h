// Project: Visual System Builder
//
// File Name: xvsb_clstype.h
//
// Description: The definition of the object attribute information.
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/13/2005	
//
// History:
// 1.    01/13/2005: Create	
//
#ifndef __XVSB_CLSTYPE_H__
#define __XVSB_CLSTYPE_H__

#include <string>
#include <map>
#include <vector>
#include "xvsb_macro.h"

class CVSB_ClassType
{
public:
	CVSB_ClassType(void) : m_szNameSpace(L""),m_szType(L""),m_szClass(L""){};
	
	CVSB_ClassType(const std::wstring& szNSpace, const std::wstring& szType, const std::wstring& szClass)
		: m_szNameSpace(szNSpace),m_szType(szType),m_szClass(szClass){};

	CVSB_ClassType(const wchar_t* szNSpace, const wchar_t* szType, const wchar_t* szClass)
		: m_szNameSpace(szNSpace),m_szType(szType),m_szClass(szClass){};

	CVSB_ClassType(const CVSB_ClassType& pdes) 
		: m_szNameSpace(pdes.m_szNameSpace),m_szType(pdes.m_szType),m_szClass(pdes.m_szClass){};

	~CVSB_ClassType(void)
	{
		m_szNameSpace.clear();
		m_szType.clear();
		m_szClass.clear();
	}

	inline std::wstring& GetNameSpace(void){return m_szNameSpace;}
	inline std::wstring& GetType(void){return m_szType;}
	inline std::wstring& GetClass(void){return m_szClass;}
	inline const wchar_t* GetNameSpace(void) const {return m_szNameSpace.c_str();}
	inline const wchar_t* GetType(void) const {return m_szType.c_str();}
	inline const wchar_t* GetClass(void) const {return m_szClass.c_str();}

	inline void SetNameSpace(const std::wstring& szNSpace){m_szNameSpace = szNSpace;}
	inline void SetType(const std::wstring& szType){m_szType = szType;}
	inline void SetClass(const std::wstring& szClass){m_szClass = szClass;}
	inline void SetNameSpace(const wchar_t* szNSpace){m_szNameSpace = szNSpace;}
	inline void SetType(const wchar_t* szType){m_szType = szType;}
	inline void SetClass(const wchar_t* szClass){m_szClass = szClass;}

	inline void Set(const std::wstring& szNSpace, const std::wstring& szType, const std::wstring& szClass)
	{
		m_szNameSpace = szNSpace;
		m_szType = szType;
		m_szClass = szClass;
	}
	inline void Set(const wchar_t* szNSpace, const wchar_t* szType, const wchar_t* szClass)
	{
		m_szNameSpace = szNSpace;
		m_szType = szType;
		m_szClass = szClass;
	}
	inline void Set(const CVSB_ClassType& pdes)
	{
		m_szNameSpace = pdes.GetNameSpace();
		m_szType = pdes.GetType();
		m_szClass = pdes.GetClass();
	}


	inline void Empty(void)
	{
		m_szNameSpace.clear();
		m_szType.clear();
		m_szClass.clear();
	}

	inline bool IsEmpty(void) const 
	{
		return (m_szNameSpace.empty() && m_szType.empty() && m_szClass.empty());
	}

	inline bool IsSame(const std::wstring& szNSpace) const 
	{
		return (m_szNameSpace == szNSpace);
	}

	inline bool IsSame(const wchar_t* szNSpace) const 
	{
		return (m_szNameSpace == szNSpace);
	}

	inline bool IsSame(const std::wstring& szNSpace, const std::wstring& szType) const 
	{
		return (m_szNameSpace == szNSpace && m_szType == szType);
	}

	inline bool IsSame(const wchar_t* szNSpace, const wchar_t* szType) const 
	{
		return (m_szNameSpace == szNSpace && m_szType == szType);
	}

	inline bool IsSame(const std::wstring& szNSpace, const std::wstring& szType, const std::wstring& szClass) const 
	{
		return (m_szNameSpace == szNSpace && m_szType == szType && m_szClass == szClass);
	}

	inline bool IsSame(const wchar_t* szNSpace, const wchar_t* szType, const wchar_t* szClass) const 
	{
		return (m_szNameSpace == szNSpace && m_szType == szType && m_szClass == szClass);
	}

	inline bool IsBuildInType(void) const 
	{
		bool bRet = (m_szNameSpace == XVSM_NS_GENERIC &&
			         m_szType == XVSM_TYPE_DATA && 
					 (m_szClass == XVSM_TYPE_FLOAT || 
					  m_szClass == XVSM_TYPE_INTEGER ||
					  m_szClass == XVSM_TYPE_BYTE ||
					  m_szClass == XVSM_TYPE_CHAR ||
					  m_szClass == XVSM_TYPE_BOOL));

		return bRet;

	}

	inline bool IsArrayType(void) const 
	{
		bool bRet = (m_szNameSpace == XVSM_NS_GENERIC && m_szType == XVSM_TYPE_DATA && m_szClass == XVSM_TYPE_ARRAY);

		return bRet;
	}

	inline bool IsIntegerType(void) const 
	{
		bool bRet = (m_szNameSpace == XVSM_NS_GENERIC && m_szType == XVSM_TYPE_DATA && m_szClass == XVSM_TYPE_INTEGER);

		return bRet;
	}

	inline bool IsByteType(void) const 
	{
		bool bRet = (m_szNameSpace == XVSM_NS_GENERIC && m_szType == XVSM_TYPE_DATA && m_szClass == XVSM_TYPE_BYTE);

		return bRet;
	}

	inline bool IsFloatType(void) const 
	{
		bool bRet = (m_szNameSpace == XVSM_NS_GENERIC && m_szType == XVSM_TYPE_DATA && m_szClass == XVSM_TYPE_FLOAT);

		return bRet;
	}

	inline bool IsBoolType(void) const 
	{
		bool bRet = (m_szNameSpace == XVSM_NS_GENERIC && m_szType == XVSM_TYPE_DATA && m_szClass == XVSM_TYPE_BOOL);

		return bRet;
	}

	inline bool IsCharType(void) const 
	{
		bool bRet = (m_szNameSpace == XVSM_NS_GENERIC && m_szType == XVSM_TYPE_DATA && m_szClass == XVSM_TYPE_CHAR);

		return bRet;
	}

	inline CVSB_ClassType* Clone(void){return new CVSB_ClassType(m_szNameSpace, m_szType, m_szClass);}

	inline CVSB_ClassType& operator = (const CVSB_ClassType& parType)
	{
		m_szNameSpace = parType.m_szNameSpace;
		m_szClass = parType.m_szClass; 
		m_szType = parType.m_szType;          
		return *this;
	}

	friend bool operator == (const CVSB_ClassType& pt1, const CVSB_ClassType& pt2)
	{
		bool bRet = (pt1.m_szNameSpace == pt2.m_szNameSpace && pt1.m_szType == pt2.m_szType && 
			pt1.m_szClass == pt2.m_szClass); 

		return bRet;
	}
	friend bool operator != (const CVSB_ClassType& pt1, const CVSB_ClassType& pt2)
	{
		return !(pt1 == pt2);
	}

	friend bool operator < (const CVSB_ClassType& pt1, const CVSB_ClassType& pt2)
	{
		bool bRet = (pt1.m_szNameSpace < pt2.m_szNameSpace);

		if(!bRet && pt1.m_szNameSpace == pt2.m_szNameSpace)
		{
			bRet = (pt1.m_szType < pt2.m_szType);

			if(!bRet && pt1.m_szType == pt2.m_szType)
				bRet = (pt1.m_szClass < pt2.m_szClass); 
		}

		return bRet;
	}

	friend bool operator <= (const CVSB_ClassType& pt1, const CVSB_ClassType& pt2)
	{
		bool bRet = (pt1.m_szNameSpace <= pt2.m_szNameSpace);

		if(bRet && pt1.m_szNameSpace == pt2.m_szNameSpace)
		{
			bRet = (pt1.m_szType <= pt2.m_szType);

			if(bRet && pt1.m_szType == pt2.m_szType)
				bRet = (pt1.m_szClass <= pt2.m_szClass); 
		}

		return bRet;
	}

	friend bool operator > (const CVSB_ClassType& pt1, const CVSB_ClassType& pt2)
	{
		return (pt2 < pt1);
	}

	friend bool operator >= (const CVSB_ClassType& pt1, const CVSB_ClassType& pt2)
	{
		return (pt2 <= pt1);
	}

	inline std::wstring GetClassTypeStr(void)
	{
		std::wstring szTemp;
		szTemp = m_szNameSpace;
		szTemp += L"::";
		szTemp += m_szType;
		szTemp += L"::";
		szTemp += m_szClass;

		return szTemp;
	}

	inline std::wstring GetNameSpaceClassString(void)
	{
		std::wstring szTemp;
		szTemp = m_szNameSpace;
		szTemp += L"::";
		szTemp += m_szClass;

		return szTemp;
	}

// Attributions
public:
	std::wstring				m_szNameSpace;  //Namespace
	std::wstring				m_szType;		//Type name
	std::wstring				m_szClass;		//Class name

};

#endif