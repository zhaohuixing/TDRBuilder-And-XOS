// Project: Visual System Builder
//
// File Name: xvsb_clsunit.cpp
//
// Description: The implementation of the class object wrapper class
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 05/10/2005	
//
// History:
// 1.    05/10/2005: Create	
//
#include "xvsb_clsunit.h"
#include "ivsb_cufile.h"
#include "xvsb_nspace.h"

CVSB_ClassUnit::CVSB_ClassUnit(CVSB_Namespace*	pNS)
{
	assert(pNS != NULL);
	m_pNamespace = pNS;
	m_UseNSLut.clear();
	m_pClass = NULL;
}

CVSB_ClassUnit::CVSB_ClassUnit(CVSB_Namespace* pNS, std::wstring& szClass)
{
	assert(pNS != NULL);
	m_pNamespace = pNS;
	m_UseNSLut.clear();
	m_pClass = new CVSB_ClassObject(pNS->GetNameSpace(), szClass, this);
}

CVSB_ClassUnit::CVSB_ClassUnit(CVSB_Namespace* pNS, const wchar_t* szClass)
{
	assert(pNS != NULL);
	m_pNamespace = pNS;
	m_UseNSLut.clear();
	m_pClass = new CVSB_ClassObject(pNS->GetNameSpace().c_str(), szClass, this);
}

CVSB_ClassUnit::CVSB_ClassUnit(CVSB_Namespace* pNS, const CVSB_ClassType& clstype)
{
	assert(pNS != NULL);
	assert(pNS->GetNameSpace() == clstype.GetNameSpace());
	m_pNamespace = pNS;
	m_UseNSLut.clear();
	m_pClass = new CVSB_ClassObject(clstype, this);
}

CVSB_ClassUnit::~CVSB_ClassUnit(void)
{
	CVSB_NSpaceLUTFree nsFree;
	nsFree(m_UseNSLut);	
	m_pNamespace = NULL;
	if(m_pClass != NULL)
	{
		delete m_pClass;
		m_pClass = NULL;
	}
}

bool CVSB_ClassUnit::IsUseClass(const CVSB_ClassType& clsType)
{
	bool bRet = false;
	CVSB_Namespace* pNS;

	std::wstring szNS = clsType.GetNameSpace();
	CVSB_NSpaceLUT::iterator iter = m_UseNSLut.find(szNS);
	if(iter != m_UseNSLut.end())
	{
		pNS = iter->second;
		if(pNS)
		{
			bRet = pNS->HasClass(clsType);
		}
	}
	else
	{
		for(iter = m_UseNSLut.begin(); iter != m_UseNSLut.end(); ++iter)
		{
			pNS = iter->second;
			if(pNS)
			{
				bRet = pNS->HasUseClass(clsType);
				if(bRet)
					return bRet;
			}
		}
	}
	return bRet;
}

CVSB_ClassObject* CVSB_ClassUnit::DuplicateUseClass(const CVSB_ClassType& clsType)
{
    CVSB_ClassObject* pReturn = NULL; 
    CVSB_ClassObject* pClass; 
	CVSB_Namespace* pNS;

	std::wstring szNS = clsType.GetNameSpace();
	CVSB_NSpaceLUT::iterator iter = m_UseNSLut.find(szNS);
	if(iter != m_UseNSLut.end())
	{
		pNS = iter->second;
		if(pNS)
		{
			pClass = pNS->QueryClass(clsType);
			if(pClass)
			{
				if(pClass->Clone((IVSB_Base**)&pReturn))
				{
					return pReturn;
				}
			}
		}
	}
	else
	{
		for(iter = m_UseNSLut.begin(); iter != m_UseNSLut.end(); ++iter)
		{
			pNS = iter->second;
			if(pNS)
			{
				pClass = pNS->QueryClass(clsType);
				if(pClass)
				{
					if(pClass->Clone((IVSB_Base**)&pReturn))
					{
						return pReturn;
					}
				}
			}
		}
	}

	return pReturn;
}

CVSB_ClassObject* CVSB_ClassUnit::DuplicateClass(const CVSB_ClassType& clsType)
{
	CVSB_ClassObject* pClass = NULL;
	CVSB_ClassObject* pClsSrc = NULL;

	if(m_pClass != NULL && clsType == m_pClass->GetType())
		return pClass;

	if(m_pNamespace && m_pNamespace->HasClass(clsType))
	{
		pClsSrc = m_pNamespace->QueryClass(clsType);
		if(pClsSrc)
		{
			if(pClsSrc->Clone((IVSB_Base**)&pClass))
			{
				return pClass;
			}
		}
	}
	else
	{
		pClass = DuplicateUseClass(clsType);
	}

	return pClass;
}

CVSB_ClassObject* CVSB_ClassUnit::QueryUseClassReference(const CVSB_ClassType& clsType)
{
    CVSB_ClassObject* pReturn = NULL; 

    CVSB_ClassObject* pClass; 
	CVSB_Namespace* pNS;

	std::wstring szNS = clsType.GetNameSpace();
	CVSB_NSpaceLUT::iterator iter = m_UseNSLut.find(szNS);
	if(iter != m_UseNSLut.end())
	{
		pNS = iter->second;
		if(pNS)
		{
			pClass = pNS->QueryClass(clsType);
			if(pClass)
			{
				pReturn = pClass;
				return pReturn;
			}
		}
	}
	else
	{
		for(iter = m_UseNSLut.begin(); iter != m_UseNSLut.end(); ++iter)
		{
			pNS = iter->second;
			if(pNS)
			{
				pClass = pNS->QueryClass(clsType);
				if(pClass)
				{
					pReturn = pClass;
					return pReturn;
				}
			}
		}
	}

	return pReturn;
}


CVSB_ClassObject* CVSB_ClassUnit::QueryClassReference(const CVSB_ClassType& clsType)
{
    CVSB_ClassObject* pReturn = NULL; 
	CVSB_Namespace* pNS;
    CVSB_ClassObject* pClass; 
	pClass = GetClassObject();
	if(pClass)
	{
		if(pClass->IsSameType(clsType))
		{
			pReturn = pClass;
			return pReturn;
		}
	}

	std::wstring szNS = clsType.GetNameSpace();
	CVSB_NSpaceLUT::iterator iter = m_UseNSLut.find(szNS);
	if(iter != m_UseNSLut.end())
	{
		pNS = iter->second;
		if(pNS)
		{
			pClass = pNS->QueryClass(clsType);
			if(pClass)
			{
				pReturn = pClass;
				return pReturn;
			}
		}
	}
	else
	{
		for(iter = m_UseNSLut.begin(); iter != m_UseNSLut.end(); ++iter)
		{
			pNS = iter->second;
			if(pNS)
			{
				pClass = pNS->QueryClass(clsType);
				if(pClass)
				{
					pReturn = pClass;
					return pReturn;
				}
			}
		}
	}
	return pReturn;
}

std::wstring CVSB_ClassUnit::GetClassName(void)
{
	std::wstring szName;
	szName.clear();
	if(m_pClass)
	{
		szName = m_pClass->GetType().GetClass();
	}

	return szName;
}

bool CVSB_ClassUnit::SetNewClassName(std::wstring& szName)
{
	bool bRet = false;
	if(m_pClass)
	{
		bRet = m_pClass->SetNewClassName(szName);
	}

	return bRet;
}

bool CVSB_ClassUnit::SetNewClassName(const wchar_t* szName)
{
	bool bRet = false;
	if(m_pClass)
	{
		bRet = m_pClass->SetNewClassName(szName);
	}

	return bRet;
}

CVSB_ClassType CVSB_ClassUnit::GetClassAnchesterType(void)
{
	CVSB_ClassType clstype;
	clstype.Empty();
	if(m_pClass)
	{
		clstype = m_pClass->GetClassAnchesterType();
	}
	return clstype;
}

CVSB_ClassType CVSB_ClassUnit::GetClassType(void)
{
	CVSB_ClassType clstype;
	clstype.Empty();
	if(m_pClass)
	{
		clstype = m_pClass->GetType();
	}
	return clstype;
}



/*
void CVSB_ClassUnit::AddUnitPath(std::wstring& szfile, std::wstring& szPath)
{
	m_UUFilelist.push_back(std::make_pair(szfile, szPath));
}

void CVSB_ClassUnit::AddUnitPath(const wchar_t* szfile, const wchar_t* szPath)
{
	m_UUFilelist.push_back(std::make_pair(szfile, szPath));
}

void CVSB_ClassUnit::AddUseUnit(CVSB_ClassUnit* pUnit)
{
	m_UUClsList.push_back(pUnit);
}

bool CVSB_ClassUnit::LoadUseUnits(IVSB_CUFileHandler* pLoader)
{
	bool bRet = false;

	if(pLoader == NULL)
		return bRet;

	_eq_pairlist::iterator iter;
	CVSB_ClassUnit* pUnit;
	for(iter = m_UUFilelist.begin(); iter != m_UUFilelist.end(); ++iter)
	{
		pUnit = pLoader->LoadUnit(iter->first, iter->second);
		if(pUnit)
		{
			AddUseUnit(pUnit);
		}
	}

	bRet = true;
	return bRet;
}
*/