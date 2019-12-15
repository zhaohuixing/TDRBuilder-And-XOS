// Project: Visual System Builder
//
// File Name: xvsb_nspace.cpp
//
// Description: The implementation of the namespace object class
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
#include "xvsb_nspace.h"

CVSB_Namespace::CVSB_Namespace(std::wstring& szNS)
{
	m_szNamespace = szNS;
	m_clsList.clear();
}

CVSB_Namespace::CVSB_Namespace(const wchar_t* szNS)
{
	m_szNamespace = szNS;
	m_clsList.clear();
}

CVSB_Namespace::~CVSB_Namespace(void)
{
	CVSB_ClassUnitFree clsfree;
	clsfree(m_clsList);
}

bool CVSB_Namespace::AddNewClass(std::wstring& szClass)
{
	bool bRet = false;

	if(m_szNamespace.empty() || szClass.empty())
		return bRet;

	CVSB_ClassType clsType(m_szNamespace.c_str(), XVSM_TYPE_CLASS, szClass.c_str());

	CVSB_ClassUnitList::iterator iter = m_clsList.find(clsType);
	if(iter != m_clsList.end())
		return bRet;

	CVSB_ClassUnit* pUnit = new CVSB_ClassUnit(this, clsType);
	if(pUnit == NULL)
		return bRet;

	m_clsList.insert(std::make_pair(clsType, pUnit));
	bRet = true;

	return bRet;
}

bool CVSB_Namespace::AddNewClass(const wchar_t* szClass)
{
	std::wstring sztemp = szClass;
	return AddNewClass(sztemp);
}

bool CVSB_Namespace::AddNewClass(std::wstring& szClass, CVSB_ClassType& cType)
{
	bool bRet = false;

	if(m_szNamespace.empty() || szClass.empty())
		return bRet;

	CVSB_ClassType clsType(m_szNamespace.c_str(), XVSM_TYPE_CLASS, szClass.c_str());

	CVSB_ClassUnitList::iterator iter = m_clsList.find(clsType);
	if(iter != m_clsList.end())
		return bRet;

	CVSB_ClassUnit* pUnit = new CVSB_ClassUnit(this, clsType);
	if(pUnit == NULL)
		return bRet;

	m_clsList.insert(std::make_pair(clsType, pUnit));
	cType = clsType;
	bRet = true;

	return bRet;
}

bool CVSB_Namespace::AddNewClass(const wchar_t* szClass, CVSB_ClassType& cType)
{
	std::wstring sztemp = szClass;
	return AddNewClass(sztemp, cType);
}

bool CVSB_Namespace::RemoveClass(std::wstring& szClass)
{
	bool bRet = false;

	if(m_szNamespace.empty() || szClass.empty())
		return bRet;

	CVSB_ClassType clsType(m_szNamespace.c_str(), XVSM_TYPE_CLASS, szClass.c_str());

	CVSB_ClassUnitList::iterator iter = m_clsList.find(clsType);
	if(iter != m_clsList.end())
	{
		CVSB_ClassUnit* pUnit = iter->second;
		m_clsList.erase(iter);
		if(pUnit)
		{
			delete pUnit;
			bRet = true;
		}
	}

	return bRet;
}

bool CVSB_Namespace::RemoveClass(const wchar_t* szClass)
{
	std::wstring sztemp = szClass;
	return RemoveClass(sztemp);
}

bool CVSB_Namespace::RemoveClass(const CVSB_ClassType& cType)
{
	bool bRet = false;

	CVSB_ClassUnitList::iterator iter = m_clsList.find(cType);
	if(iter != m_clsList.end())
	{
		CVSB_ClassUnit* pUnit = iter->second;
		m_clsList.erase(iter);
		if(pUnit)
		{
			delete pUnit;
		}
		bRet = true;
	}

	return bRet;
}

bool CVSB_Namespace::HasClass(std::wstring& szClass)
{
	bool bRet = false;

	if(m_szNamespace.empty() || szClass.empty())
		return bRet;

	CVSB_ClassType clsType(m_szNamespace.c_str(), XVSM_TYPE_CLASS, szClass.c_str());

	CVSB_ClassUnitList::iterator iter = m_clsList.find(clsType);
	if(iter != m_clsList.end())
	{
		bRet = true;
	}

	return bRet;
}

bool CVSB_Namespace::HasClass(const wchar_t* szClass)
{
	std::wstring sztemp = szClass;
	return HasClass(sztemp);
}

bool CVSB_Namespace::HasClass(const CVSB_ClassType& cType)
{
	bool bRet = false;

	CVSB_ClassUnitList::iterator iter = m_clsList.find(cType);
	if(iter != m_clsList.end())
	{
		bRet = true;
	}
	return bRet;
}

CVSB_ClassUnit* CVSB_Namespace::QueryClassUnit(std::wstring& szClass)
{
	CVSB_ClassUnit* pUnit = NULL;

	if(m_szNamespace.empty() || szClass.empty())
		return pUnit;

	CVSB_ClassType clsType(m_szNamespace.c_str(), XVSM_TYPE_CLASS, szClass.c_str());

	CVSB_ClassUnitList::iterator iter = m_clsList.find(clsType);
	if(iter != m_clsList.end())
	{
		pUnit = iter->second;
	}

	return pUnit;
}

CVSB_ClassUnit* CVSB_Namespace::QueryClassUnit(const wchar_t* szClass)
{
	std::wstring sztemp = szClass;
	return QueryClassUnit(sztemp);
}

CVSB_ClassUnit* CVSB_Namespace::QueryClassUnit(const CVSB_ClassType& cType)
{
	CVSB_ClassUnit* pUnit = NULL;

	CVSB_ClassUnitList::iterator iter = m_clsList.find(cType);
	if(iter != m_clsList.end())
	{
		pUnit = iter->second;
	}

	return pUnit;
}

CVSB_ClassObject* CVSB_Namespace::QueryClass(std::wstring& szClass)
{
	CVSB_ClassObject* pClass = NULL;

	if(m_szNamespace.empty() || szClass.empty())
		return pClass;

	CVSB_ClassType clsType(m_szNamespace.c_str(), XVSM_TYPE_CLASS, szClass.c_str());

	CVSB_ClassUnitList::iterator iter = m_clsList.find(clsType);
	if(iter != m_clsList.end())
	{
		pClass = iter->second->GetClassObject();
	}

	return pClass;
}

CVSB_ClassObject* CVSB_Namespace::QueryClass(const wchar_t* szClass)
{
	std::wstring sztemp = szClass;
	return QueryClass(sztemp);
}

CVSB_ClassObject* CVSB_Namespace::QueryClass(const CVSB_ClassType& cType)
{
	CVSB_ClassObject* pClass = NULL;

	CVSB_ClassUnitList::iterator iter = m_clsList.find(cType);
	if(iter != m_clsList.end())
	{
		pClass = iter->second->GetClassObject();
	}

	return pClass;
}

bool CVSB_Namespace::HasUseClass(const CVSB_ClassType& cType)
{
	bool bRet = false;

	bRet = HasClass(cType);
	if(bRet == false)
	{
		CVSB_ClassUnitList::iterator iter;
		for(iter = m_clsList.begin(); iter != m_clsList.end(); ++iter)
		{
			bRet = iter->second->IsUseClass(cType);
			if(bRet == true)
				return bRet;
		}
	}

	return bRet;
}

CVSB_ClassObject* CVSB_Namespace::QueryUseClass(const CVSB_ClassType& cType)
{
	CVSB_ClassObject* pClass = NULL;

	pClass = QueryClass(cType);
	if(pClass == NULL)
	{
		CVSB_ClassUnitList::iterator iter;
		for(iter = m_clsList.begin(); iter != m_clsList.end(); ++iter)
		{
			pClass = iter->second->QueryUseClassReference(cType);
			if(pClass != NULL)
				return pClass;
		}
	}

	return pClass;
}

bool CVSB_Namespace::RenameClass(std::wstring& szOldClass, std::wstring& szNewClass)
{
	bool bRet = false;
	CVSB_ClassUnit* pUnit = NULL;


	if(m_szNamespace.empty() || szOldClass.empty() || szNewClass.empty())
		return bRet;

	CVSB_ClassType clsOldType(m_szNamespace.c_str(), XVSM_TYPE_CLASS, szOldClass.c_str());
	CVSB_ClassType clsNewType(m_szNamespace.c_str(), XVSM_TYPE_CLASS, szNewClass.c_str());

	CVSB_ClassUnitList::iterator iterold = m_clsList.find(clsOldType);
	CVSB_ClassUnitList::iterator iternew = m_clsList.find(clsNewType);
	if(iternew != m_clsList.end())
	{
		return bRet;
	}

	if(iterold != m_clsList.end())
	{
		pUnit = iterold->second;
		m_clsList.erase(iterold);
		pUnit->SetNewClassName(szNewClass);
		m_clsList.insert(std::make_pair(clsNewType, pUnit));
		bRet = true;
	}

	return bRet;
}

bool CVSB_Namespace::RenameClass(const wchar_t* szOldClass, const wchar_t* szNewClass)
{
	std::wstring szOld = szOldClass;
	std::wstring szNew = szNewClass;
	return RenameClass(szOld, szNew);
}

