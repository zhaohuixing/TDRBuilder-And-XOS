// Project: Visual System Builder
//
// File Name: xvsb_vartbl.cpp
//
// Description: The definition of the variable table for process
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
#include "xvsb_vartbl.h"
#include "xvsb_array.h"


CVSB_VarTable::CVSB_VarTable()
{
	m_TNLut.clear(); 
	m_ObjTbl.clear();
}	

CVSB_VarTable::~CVSB_VarTable()
{
	m_TNLut.clear(); 
	CVSB_VarObjRelease vfree; 
	vfree(m_ObjTbl);
}	

bool CVSB_VarTable::AddVar(IVSB_DataBase* pVar)
{
	bool bRet = false;
	bool bExist = false;
	std::wstring szName;

#ifdef _XSVM_DEBUG_
	assert(pVar != NULL);
#endif

	if(pVar != NULL)
	{
		szName = pVar->GetName();

#ifdef _XSVM_DEBUG_
		assert(!szName.empty());
#endif
		if(!szName.empty())
		{
			CVSB_VarObjTable::iterator iter = m_ObjTbl.find(szName);

#ifdef _XSVM_DEBUG_
			assert(iter == m_ObjTbl.end());
#endif
			if(iter == m_ObjTbl.end())
			{
				CVSB_ClassType type = pVar->GetType();
				bExist = _checkname(type, szName);
				if(!bExist) // OK for not existing
				{
					m_TNLut.insert(std::make_pair(type, szName));
					m_ObjTbl.insert(std::make_pair(szName, pVar));
					bRet = true;
				}
			}
		}
	}

	return bRet;
}

bool CVSB_VarTable::AddVar(IVSB_DataBase* pVar, const std::wstring& name)
{
	bool bRet = false;
	bool bExist = false;

#ifdef _XSVM_DEBUG_
	assert(pVar != NULL);
#endif

	if(pVar != NULL)
	{
#ifdef _XSVM_DEBUG_
		assert(!name.empty());
#endif
		if(!name.empty())
		{
			CVSB_VarObjTable::iterator iter = m_ObjTbl.find(name);
#ifdef _XSVM_DEBUG_
			assert(iter == m_ObjTbl.end());
#endif
			if(iter == m_ObjTbl.end())
			{
				CVSB_ClassType type = pVar->GetType();
				bExist = _checkname(type, name);
				if(!bExist) // OK for not existing
				{
					m_TNLut.insert(std::make_pair(type, name));
					m_ObjTbl.insert(std::make_pair(name, pVar));
					bRet = true;
				}
			}
		}
	}

	return bRet;
}

bool CVSB_VarTable::AddVar(IVSB_DataBase* pVar, const wchar_t* name)
{
	std::wstring szName = name;
	return AddVar(pVar, szName);
}

bool CVSB_VarTable::ReplaceVar(IVSB_DataBase* pVar)
{
	bool bRet = false;
	std::wstring szName;

#ifdef _XSVM_DEBUG_
	assert(pVar != NULL);
#endif

	if(pVar != NULL)
	{
		szName = pVar->GetName();
	
#ifdef _XSVM_DEBUG_
		assert(!szName.empty());
#endif
		if(!szName.empty())
		{
			RemoveVar(szName);
			bRet = AddVar(pVar);

#ifdef _XSVM_DEBUG_
			assert(bRet);
#endif
		}
	}
	return bRet;
}

bool CVSB_VarTable::ReplaceVar(IVSB_DataBase* pVar, const std::wstring& name)
{
	bool bRet = false;
	
#ifdef _XSVM_DEBUG_
	assert(pVar != NULL);
#endif
	if(pVar != NULL)
	{
#ifdef _XSVM_DEBUG_
		assert(!name.empty());
#endif
		if(!name.empty())
		{
			RemoveVar(name);
			bRet = AddVar(pVar, name);
#ifdef _XSVM_DEBUG_
			assert(bRet);
#endif
		}
	}
	return bRet;
}

bool CVSB_VarTable::ReplaceVar(IVSB_DataBase* pVar, const wchar_t* name)
{
	std::wstring szName = name;
	return ReplaceVar(pVar, szName);
}

IVSB_DataBase* CVSB_VarTable::GetVar(const std::wstring& name)
{
	CVSB_VarObjTable::iterator iter = m_ObjTbl.find(name);
	if(iter != m_ObjTbl.end())
		return iter->second;
	else
		return NULL;
}

IVSB_DataBase* CVSB_VarTable::GetVar(const wchar_t* name)
{
	CVSB_VarObjTable::iterator iter = m_ObjTbl.find(name);
	if(iter != m_ObjTbl.end())
		return iter->second;
	else
		return NULL;
}

bool CVSB_VarTable::HasVar(const std::wstring& name)
{
	CVSB_VarObjTable::iterator iter = m_ObjTbl.find(name);
	bool bRet = (iter != m_ObjTbl.end());
	return bRet;
}

bool CVSB_VarTable::HasVar(const wchar_t* name)
{
	CVSB_VarObjTable::iterator iter = m_ObjTbl.find(name);
	bool bRet = (iter != m_ObjTbl.end());
	return bRet;
}

bool CVSB_VarTable::RemoveVar(const std::wstring& name)
{
	bool bRet = true;
	CVSB_VarObjTable::iterator iter = m_ObjTbl.find(name);
	if(iter != m_ObjTbl.end())
	{
		if(iter->second != NULL)
			delete iter->second;
		iter->second = NULL;
		m_ObjTbl.erase(iter);
	}

	bRet = _removelutname(name);

	return bRet;
}

bool CVSB_VarTable::RemoveVar(const wchar_t* name)
{
	bool bRet = true;
	std::wstring sz = name;

	RemoveVar(sz);

	return bRet;
}

bool CVSB_VarTable::UpdateExistVar(const std::wstring& oldname, const std::wstring& newname, IVSB_DataBase* pVal)
{
	bool bRet = false;
	if(RemoveVar(oldname))
	{
		bRet = AddVar(pVal, newname);

#ifdef _XSVM_DEBUG_
		assert(bRet);
#endif
	}

	return bRet;
}

bool CVSB_VarTable::UpdateExistVar(const wchar_t* oldname, const wchar_t* newname, IVSB_DataBase* pVal)
{
	std::wstring oname(oldname);
	std::wstring nname(newname);
	return UpdateExistVar(oname, nname, pVal);
}

bool CVSB_VarTable::AssignVarValue(const std::wstring& name, IVSB_DataBase* pVal)
{
	bool bRet = false;
	CVSB_VarLUTable::iterator iterret;
	CVSB_VarLUTFind2 namecmp;
	CVSB_VLFindName nfind(namecmp);
	iterret = nfind(m_TNLut, name);
	bRet = (iterret != m_TNLut.end());

#ifdef _XSVM_DEBUG_
	assert(bRet);
#endif

	if(!bRet)
		return bRet;

	CVSB_VarObjTable::iterator iter = m_ObjTbl.find(name);
	if(iter != m_ObjTbl.end())
	{
		bRet = iter->second->Assign(pVal);
		
#ifdef _XSVM_DEBUG_
		assert(bRet);
#endif
	}

	return bRet;
}

bool CVSB_VarTable::AssignVarValue(const wchar_t* name, IVSB_DataBase* pVal)
{
	std::wstring szName = name;
	return AssignVarValue(szName, pVal);
}

void CVSB_VarTable::CleanUp(void)
{
	m_TNLut.clear(); 
	CVSB_VarObjRelease vfree; 
	vfree(m_ObjTbl);
}

CVSB_ClassType CVSB_VarTable::TestLutName(const std::wstring& name)
{
	CVSB_ClassType type;
	CVSB_VarLUTable::iterator iterret;
	CVSB_VarLUTFind2 namecmp;
	CVSB_VLFindName nfind(namecmp);
	iterret = nfind(m_TNLut, name);
	if(iterret != m_TNLut.end())
		type = iterret->first;

	return type;
}

CVSB_ClassType CVSB_VarTable::TestLutName(const wchar_t* name)
{
	std::wstring sz = name;
	return TestLutName(sz);
}

CVSB_VarTable& CVSB_VarTable::operator = (const CVSB_VarTable& vt)
{
	m_TNLut.clear(); 
	CVSB_VarObjRelease vfree; 
	vfree(m_ObjTbl);

	CVSB_VarLUTable::const_iterator lutiter;
	for(lutiter = vt.m_TNLut.begin(); lutiter != vt.m_TNLut.end(); ++lutiter)
	{
		CVSB_ClassType cType = lutiter->first;
		std::wstring str = lutiter->second;
		m_TNLut.insert(std::make_pair(cType, str));
	}

	CVSB_VarObjTable::const_iterator voiter;
	for(voiter = vt.m_ObjTbl.begin(); voiter != vt.m_ObjTbl.end(); ++voiter)
	{
		std::wstring strname = voiter->first;
		IVSB_DataBase* pData = NULL;
		if(voiter->second->Clone((IVSB_Base**)&pData, voiter->second->GetName()))
			m_ObjTbl.insert(std::make_pair(strname, pData));
	}
	return *this;
}

bool CVSB_VarTable::_checkname(const CVSB_ClassType& type, const std::wstring& name)
{
	bool bRet = false;
	CVSB_VarLUTable::iterator liter1 = m_TNLut.lower_bound(type), liter2, iterret;
	bRet = (liter1 != m_TNLut.end());
	if(bRet)
	{
		liter2 = m_TNLut.upper_bound(type);
		CVSB_VarLUTFind2 namecmp;
		CVSB_VLFindName nfind(namecmp);
		iterret = nfind(liter1, liter2, name);
		bRet = (iterret != m_TNLut.end() && iterret != liter2);
		if(bRet)
		{
			std::wstring sText = iterret->second;
			CVSB_ClassType newType = iterret->first;
			bRet = (sText == name && newType == type);
		}
	}
	return bRet;
}

bool CVSB_VarTable::_checkname(const std::wstring& name)
{
	bool bRet = false;
	CVSB_VarLUTable::iterator iterret;
	CVSB_VarLUTFind2 namecmp;
	CVSB_VLFindName nfind(namecmp);
	iterret = nfind(m_TNLut, name);
	bRet = (iterret != m_TNLut.end());

	return bRet;
}

bool CVSB_VarTable::_removelutname(const std::wstring& name)
{
	bool bRet = true;
	CVSB_VarLUTable::iterator iterret;
	CVSB_VarLUTFind2 namecmp;
	CVSB_VLFindName nfind(namecmp);
	iterret = nfind(m_TNLut, name);
	if(iterret != m_TNLut.end())
	{
		m_TNLut.erase(iterret);
	}

	return bRet;
}

void CVSB_VarTable::ResetVars(void)
{
	CVSB_VarObjTable::const_iterator voiter;
	for(voiter = m_ObjTbl.begin(); voiter != m_ObjTbl.end(); ++voiter)
	{
		voiter->second->Reset();
	}
}

int CVSB_VarTable::GetPrintLineCount(void) const
{
	CVSB_VarObjTable::const_iterator voiter;
	int nCount = 0;
	for(voiter = m_ObjTbl.begin(); voiter != m_ObjTbl.end(); ++voiter)
	{
		if(voiter->second->GetDataTypeIndex() != XVSM_DT_ARRAY)
		{
			nCount++;
		}
		else
		{
			nCount++;
			nCount += ((CVSB_Array*)voiter->second)->Size();
		}
	}

	return nCount;
}