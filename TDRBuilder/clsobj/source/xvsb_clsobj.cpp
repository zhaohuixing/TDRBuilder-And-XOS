// Project: Visual System Builder
//
// File Name: xvsb_clsobj.cpp
//
// Description: The implementation of the class object class
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 05/06/2005	
//
// History:
// 1.    05/06/2005: Create	
//
#include "xvsb_clsunit.h"
#include "xvsb_clsobj.h"

CVSB_ClassObject::CVSB_ClassObject(void)
{
	SetType(L"", L"", L"");
	m_FuncTable.clear();
	m_PropertyList.clear();
	m_Ancestor = NULL;
	m_szValStr = L"...";
	m_ClassUnit = NULL;
}

CVSB_ClassObject::CVSB_ClassObject(CVSB_ClassUnit* pUnit)
{
	SetType(L"", L"", L"");
	m_FuncTable.clear();
	m_PropertyList.clear();
	m_Ancestor = NULL;
	m_szValStr = L"...";
	m_ClassUnit = pUnit;
}

CVSB_ClassObject::CVSB_ClassObject(const CVSB_ClassType& clsType, CVSB_ClassUnit* pUnit)
{
	SetType(clsType);
	m_FuncTable.clear();
	m_PropertyList.clear();
	m_Ancestor = NULL;
	m_szValStr = L"...";
	m_ClassUnit = pUnit;
}

CVSB_ClassObject::CVSB_ClassObject(std::wstring& szNS, std::wstring& szCls, CVSB_ClassUnit* pUnit)
{
	SetType(szNS.c_str(), XVSM_TYPE_CLASS, szCls.c_str());
	m_FuncTable.clear();
	m_PropertyList.clear();
	m_Ancestor = NULL;
	m_szValStr = L"...";
	m_ClassUnit = pUnit;
}

CVSB_ClassObject::CVSB_ClassObject(const wchar_t* szNS, const wchar_t* szCls, CVSB_ClassUnit* pUnit)
{
	SetType(szNS, XVSM_TYPE_CLASS, szCls);
	m_FuncTable.clear();
	m_PropertyList.clear();
	m_Ancestor = NULL;
	m_szValStr = L"...";
	m_ClassUnit = pUnit;
}

CVSB_ClassObject::CVSB_ClassObject(const CVSB_ClassObject& clsobj, CVSB_ClassUnit* pUnit)
{
	SetType(clsobj.m_Type);
	m_FuncTable.clear();
	m_PropertyList.clear();
	m_Ancestor = NULL;
	m_szValStr = L"...";

	m_ClassUnit = pUnit;

	if(clsobj.m_Ancestor)
	{
		m_Ancestor = new CVSB_ClassObject(*clsobj.m_Ancestor);
		//m_Ancestor = clsobj.m_Ancestor;
	}

	CVSB_MethodTable::const_iterator fiter;
	CVSB_Method* pFn;
	for(fiter = clsobj.m_FuncTable.begin(); fiter != clsobj.m_FuncTable.end(); ++fiter)
	{
		pFn = NULL;
		if(fiter->second->Clone(&pFn, this))
		{
			m_FuncTable.insert(std::make_pair(fiter->first, pFn));
		}
	}

	IVSB_DataTable::const_iterator diter;
	IVSB_DataBase* pData;
	for(diter = clsobj.m_PropertyList.begin(); diter != clsobj.m_PropertyList.end(); ++diter)
	{
		pData = NULL;
		if(diter->second->Clone((IVSB_Base**)&pData, diter->first))
		{
			m_PropertyList.insert(std::make_pair(diter->first, pData));
		}
	}
}

CVSB_ClassObject::CVSB_ClassObject(const CVSB_ClassObject& clsobj)
{
	SetType(clsobj.m_Type);
	m_FuncTable.clear();
	m_PropertyList.clear();
	m_Ancestor = NULL;
	m_szValStr = L"...";

	m_ClassUnit = clsobj.m_ClassUnit;

	if(clsobj.m_Ancestor)
	{
		m_Ancestor = new CVSB_ClassObject(*clsobj.m_Ancestor);
		//m_Ancestor = clsobj.m_Ancestor;
	}

	CVSB_MethodTable::const_iterator fiter;
	CVSB_Method* pFn;
	for(fiter = clsobj.m_FuncTable.begin(); fiter != clsobj.m_FuncTable.end(); ++fiter)
	{
		pFn = NULL;
		if(fiter->second->Clone(&pFn, this))
		{
			m_FuncTable.insert(std::make_pair(fiter->first, pFn));
		}
	}

	IVSB_DataTable::const_iterator diter;
	IVSB_DataBase* pData;
	for(diter = clsobj.m_PropertyList.begin(); diter != clsobj.m_PropertyList.end(); ++diter)
	{
		pData = NULL;
		if(diter->second->Clone((IVSB_Base**)&pData, diter->first))
		{
			m_PropertyList.insert(std::make_pair(diter->first, pData));
		}
	}
}

CVSB_ClassObject::~CVSB_ClassObject(void)
{
	Cleanup();
	m_ClassUnit = NULL;
}

void CVSB_ClassObject::CleanFuncTable(void)
{
	CVSB_MethodTableFree fnFree;
	fnFree(m_FuncTable);
}

void CVSB_ClassObject::CleanProperty(void)
{
	IVSB_DataTableFree	dataFree;
	dataFree(m_PropertyList);
}

bool CVSB_ClassObject::SetNewClassName(std::wstring& szName)
{
	bool bRet = false;
	if(szName.empty())
		return bRet;

	m_Type.SetClass(szName);
	bRet = true;
	return bRet;
}

bool CVSB_ClassObject::SetNewClassName(const wchar_t* szName)
{
	std::wstring sztemp = szName;
	return SetNewClassName(sztemp);
}


void CVSB_ClassObject::Cleanup(void)
{
	CleanFuncTable();
	CleanProperty();

	if(m_Ancestor)
	{
		delete m_Ancestor;
		m_Ancestor = NULL;
	}

}

bool CVSB_ClassObject::HasProperty(std::wstring& szName)
{
	bool bRet = false;

	IVSB_DataTable::iterator iter;
	iter = m_PropertyList.find(szName);
	if(iter != m_PropertyList.end())
	{
		bRet = true;
		return bRet;
	}
	else
	{
		if(m_Ancestor != NULL)
		{
			bRet = m_Ancestor->HasProperty(szName);
		}
	}

	return bRet;
}

bool CVSB_ClassObject::HasProperty(const wchar_t* szName)
{
	bool bRet = false;
	std::wstring name = szName;

	bRet = HasProperty(name);

	return bRet;
}

IVSB_DataBase* CVSB_ClassObject::GetProperty(std::wstring& szName)
{
	IVSB_DataBase* pRet = NULL;

	IVSB_DataTable::iterator iter;
	iter = m_PropertyList.find(szName);
	if(iter != m_PropertyList.end())
	{
		pRet = iter->second;
		return pRet;
	}
	else
	{
		if(m_Ancestor != NULL)
		{
			pRet = m_Ancestor->GetProperty(szName);
		}
	}

	return pRet;
}

IVSB_DataBase* CVSB_ClassObject::GetProperty(const wchar_t* szName)
{
	IVSB_DataBase* pRet = NULL;
	std::wstring name = szName;

	pRet = GetProperty(name);

	return pRet;
}

bool CVSB_ClassObject::AddProperty(std::wstring& szName, IVSB_DataBase* pData)
{
	bool bRet = false;

	if(HasProperty(szName) || pData == NULL)
		return bRet;


	m_PropertyList.insert(std::make_pair(szName, pData));
	bRet = true;

	return bRet;
}

bool CVSB_ClassObject::AddProperty(const wchar_t* szName, IVSB_DataBase* pData)
{
	bool bRet = false;
	std::wstring name = szName;

	bRet = AddProperty(name, pData);

	return bRet;
}

bool CVSB_ClassObject::RemoveProperty(std::wstring& szName)
{
	bool bRet = false;

	if(!HasProperty(szName))
		return bRet;

	IVSB_DataTable::iterator iter;
	IVSB_DataBase* pData;
	iter = m_PropertyList.find(szName);
	if(iter != m_PropertyList.end())
	{
		pData = iter->second;
		m_PropertyList.erase(iter);
		if(pData)
		{
			delete pData;
			pData = NULL;
		}
		bRet = true;
	}


	return bRet;
}

bool CVSB_ClassObject::RemoveProperty(const wchar_t* szName)
{
	bool bRet = false;
	std::wstring name = szName;

	bRet = RemoveProperty(name);

	return bRet;
}

bool CVSB_ClassObject::HasMethod(std::wstring& szFunc)
{
	bool bRet = false;

	CVSB_MethodTable::iterator iter;
	for(iter = m_FuncTable.begin(); iter != m_FuncTable.end(); ++iter)
	{
		if(iter->first.m_szFunc == szFunc)
		{
			bRet = true;
			return bRet;
		}
	}
	if(!bRet)
	{
		if(m_Ancestor != NULL)
		{
			bRet = m_Ancestor->HasMethod(szFunc);
		}
	}

	return bRet;
}

bool CVSB_ClassObject::HasMethod(const wchar_t* szFunc)
{
	bool bRet = false;
	std::wstring sfunc = szFunc;

	bRet = HasMethod(sfunc);

	return bRet;
}

bool CVSB_ClassObject::HasMethod(CVSB_FnParamPattern& fpat)
{
	bool bRet = false;

	CVSB_MethodTable::iterator iter;
	iter = m_FuncTable.find(fpat);
	if(iter != m_FuncTable.end())
	{
		bRet = true;
		return bRet;
	}
	else
	{
		if(m_Ancestor != NULL)
		{
			bRet = m_Ancestor->HasMethod(fpat);
		}
	}

	return bRet;
}

CVSB_Method* CVSB_ClassObject::GetMethod(CVSB_FnParamPattern& fpat)
{
	CVSB_Method* pFn = NULL;

	CVSB_MethodTable::iterator iter;
	iter = m_FuncTable.find(fpat);
	if(iter != m_FuncTable.end())
	{
		pFn = iter->second;
		return pFn;
	}
	else
	{
		if(m_Ancestor != NULL)
		{
			pFn = m_Ancestor->GetMethod(fpat);
		}
	}

	return pFn;
}

bool CVSB_ClassObject::AddMethod(CVSB_FnParamPattern& fpat, CVSB_Method* pFn)
{
	bool bRet = false;

	if(HasMethod(fpat) || pFn == NULL)
		return bRet;

	m_FuncTable.insert(std::make_pair(fpat, pFn));
	bRet = true;

	return bRet;
}

bool CVSB_ClassObject::RemoveMethod(CVSB_FnParamPattern& fpat)
{
	bool bRet = false;

	CVSB_MethodTable::iterator iter;
	iter = m_FuncTable.find(fpat);
	CVSB_Method* pFn = NULL;
	if(iter != m_FuncTable.end())
	{
		pFn = iter->second;
		m_FuncTable.erase(iter);
		if(pFn)
		{
			delete pFn;
			pFn = NULL;
		}
		bRet = true;
		return bRet;
	}

	return bRet;
}

bool CVSB_ClassObject::EraseMethod(CVSB_FnParamPattern& fpat)
{
	bool bRet = false;

	CVSB_MethodTable::iterator iter;
	iter = m_FuncTable.find(fpat);
	if(iter != m_FuncTable.end())
	{
		m_FuncTable.erase(iter);
		bRet = true;
		return bRet;
	}

	return bRet;
}

bool CVSB_ClassObject::HasMethod(CVSB_FnPattern& fpat)
{
	CVSB_FnParamPattern  fpp = fpat;

	return HasMethod(fpp);
}

CVSB_Method* CVSB_ClassObject::GetMethod(CVSB_FnPattern& fpat)
{
	CVSB_FnParamPattern  fpp = fpat;

	return GetMethod(fpp);
}

bool CVSB_ClassObject::AddMethod(CVSB_FnPattern& fpat, CVSB_Method* pFn)
{
	CVSB_FnParamPattern  fpp = fpat;

	return AddMethod(fpp, pFn);
}

bool CVSB_ClassObject::RemoveMethod(CVSB_FnPattern& fpat)
{
	CVSB_FnParamPattern  fpp = fpat;

	return RemoveMethod(fpp);
}

bool CVSB_ClassObject::EraseMethod(CVSB_FnPattern& fpat)
{
	CVSB_FnParamPattern  fpp = fpat;

	return EraseMethod(fpp);
}

CVSB_ClassObject& CVSB_ClassObject::operator = (const CVSB_ClassObject& clsobj)
{
	Cleanup();
	SetType(clsobj.m_Type);

	if(clsobj.m_Ancestor)
	{
		m_Ancestor = new CVSB_ClassObject(*clsobj.m_Ancestor);
		//m_Ancestor = clsobj.m_Ancestor;
	}

	CVSB_MethodTable::const_iterator fiter;
	CVSB_Method* pFn;
	for(fiter = clsobj.m_FuncTable.begin(); fiter != clsobj.m_FuncTable.end(); ++fiter)
	{
		pFn = NULL;
		if(fiter->second->Clone(&pFn, this))
		{
			m_FuncTable.insert(std::make_pair(fiter->first, pFn));
		}
	}

	IVSB_DataTable::const_iterator diter;
	IVSB_DataBase* pData;
	for(diter = clsobj.m_PropertyList.begin(); diter != clsobj.m_PropertyList.end(); ++diter)
	{
		pData = NULL;
		if(diter->second->Clone((IVSB_Base**)&pData, diter->first))
		{
			m_PropertyList.insert(std::make_pair(diter->first, pData));
		}
	}

	return *this;
}

bool CVSB_ClassObject::Clone(IVSB_Base** ppObj)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_ClassObject(*this);
	if(*ppObj == NULL)
		return false;

	bRet = true;
	return bRet;
}

bool CVSB_ClassObject::Clone(IVSB_Base** ppObj, const std::wstring& szName)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_ClassObject(*this);
	if(*ppObj == NULL)
		return false;

	(*ppObj)->SetName(szName);
	bRet = true;
	return bRet;
}

bool CVSB_ClassObject::Clone(IVSB_Base** ppObj, const wchar_t* szName)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_ClassObject(*this);
	if(*ppObj == NULL)
		return false;

	(*ppObj)->SetName(szName);
	bRet = true;
	return bRet;
}

bool CVSB_ClassObject::Assign(IVSB_DataBase* pData)
{
	bool bRet = false;
	if(pData == NULL || pData->GetType() != GetType())
		return bRet;

	IVSB_DataTable::iterator iter1, iter2;
	CVSB_ClassObject* pClass = (CVSB_ClassObject*)pData;
	for(iter1 = m_PropertyList.begin(), iter2 = pClass->m_PropertyList.begin();
		iter1 != m_PropertyList.end() && iter2 != pClass->m_PropertyList.end();
		++iter1, ++iter2)
	{
		bRet = iter1->second->Assign(iter2->second);
	}

	return bRet;
}

bool CVSB_ClassObject::AssignDefault(IVSB_DataBase* pData)
{
	bool bRet = false;

	if(pData == NULL || pData->GetType() != GetType())
		return bRet;

	IVSB_DataTable::iterator iter1, iter2;
	CVSB_ClassObject* pClass = (CVSB_ClassObject*)pData;
	for(iter1 = m_PropertyList.begin(), iter2 = pClass->m_PropertyList.begin();
		iter1 != m_PropertyList.end() && iter2 != pClass->m_PropertyList.end();
		++iter1, ++iter2)
	{
		bRet = iter1->second->AssignDefault(iter2->second);
	}

	return bRet;
}

bool CVSB_ClassObject::Compare(IVSB_DataBase* pObj, enXVSB_CMPTYPE cmp) 
{
	bool bRet = false;

	return bRet;
}

int CVSB_ClassObject::GetDataTypeIndex(void) 
{
	return XVSM_DT_CLASS;
}

const wchar_t* CVSB_ClassObject::GetDataTypeStr(void) const 
{
	m_szClassType = m_Type.m_szNameSpace;
	m_szClassType += L"::";
	m_szClassType += m_Type.m_szType;
	m_szClassType += L"::";
	m_szClassType += m_Type.m_szClass;
	return m_szClassType.c_str();
}

std::wstring CVSB_ClassObject::GetDataTypeStr(void) 
{
	m_szClassType = m_Type.GetClassTypeStr();
	return m_szClassType;
}

std::wstring CVSB_ClassObject::GetClassTypeStr(void)
{
	return m_Type.GetNameSpaceClassString();
}

std::wstring CVSB_ClassObject::GetDataValueStr(void) 
{
	return m_szValStr;
}

const wchar_t* CVSB_ClassObject::GetDataValueStr(void) const
{
	return m_szValStr.c_str();
}

std::wstring CVSB_ClassObject::GetDefaultValueStr(void)
{
	return m_szValStr;
}

const wchar_t* CVSB_ClassObject::GetDefaultValueStr(void) const
{
	return m_szValStr.c_str();
}

void CVSB_ClassObject::Reset(void)
{
	IVSB_DataTable::iterator iter;
	for(iter = m_PropertyList.begin(); iter != m_PropertyList.end(); ++iter)
	{
		iter->second->Reset();
	}
}

void CVSB_ClassObject::CreateAncestor(const CVSB_ClassType& clsType)
{
	if(!clsType.IsBuildInType() && !clsType.IsEmpty() && m_ClassUnit)
	{
		RemoveAncestor();
		//m_Ancestor = m_ClassUnit->DuplicateUseClass(clsType);
		m_Ancestor = m_ClassUnit->QueryUseClassReference(clsType);
	}
}

void CVSB_ClassObject::CreateAncestor(CVSB_ClassObject* pCls)
{
	if(pCls)
	{
		RemoveAncestor();
		pCls->Clone((IVSB_Base**)&m_Ancestor);
		//m_Ancestor = pCls->m_Ancestor;
	}
}

void CVSB_ClassObject::RemoveAncestor(void)
{
	if(m_Ancestor)
	{
		delete m_Ancestor;
		m_Ancestor = NULL;
	}
}

void CVSB_ClassObject::AttachAncestor(CVSB_ClassObject* pCls)
{
	if(pCls)
	{
		RemoveAncestor();
		//m_Ancestor = pCls;
		pCls->Clone((IVSB_Base**)&m_Ancestor);
	}
}

bool CVSB_ClassObject::CheckAncestorConflict(void)
{
	bool bRet = true;

	return bRet;
}

CVSB_ClassType CVSB_ClassObject::GetClassAnchesterType(void)
{
	CVSB_ClassType clstype;
	clstype.Empty();
	if(m_Ancestor)
	{
		clstype = m_Ancestor->GetType();
	}
	return clstype;
}

CVSB_ClassObject* CVSB_ClassObject::DuplicateUseClass(const CVSB_ClassType& clsType)
{
	CVSB_ClassObject* pClass = NULL;

	if(!clsType.IsBuildInType() && !clsType.IsEmpty() && m_ClassUnit)
	{
		pClass = m_ClassUnit->DuplicateUseClass(clsType);
	}

	return pClass;
}

CVSB_ClassObject* CVSB_ClassObject::DuplicateUseClass(CVSB_ParamType& paraType)
{
	CVSB_ClassType clsType = paraType.GetClassType();
	CVSB_ClassObject* pClass = NULL;

	pClass = DuplicateUseClass(clsType);

	return pClass;
}

CVSB_ClassObject* CVSB_ClassObject::QueryClassReference(const CVSB_ClassType& clsType)
{
	CVSB_ClassObject* pClass = NULL;

	if(GetType() == clsType)
	{
		pClass = this;
		return pClass;
	}

	if(!clsType.IsBuildInType() && !clsType.IsEmpty() && m_ClassUnit)
	{
		pClass = m_ClassUnit->QueryUseClassReference(clsType);
	}

	return pClass;
}

bool CVSB_ClassObject::IsAttribute(std::wstring& szName)
{
	bool bRet = false;

	bRet = HasProperty(szName);

	if(!bRet)
		bRet = HasMethod(szName);

	return bRet;
}

bool CVSB_ClassObject::IsAttribute(const wchar_t* szName)
{
	bool bRet = false;
	if(szName != NULL)
	{
		std::wstring stemp = szName;
		bRet = IsAttribute(stemp);
	}

	return bRet;
}

bool CVSB_ClassObject::IsPropertyAttribute(std::wstring& szName)
{
	bool bRet = false;

	bRet = HasProperty(szName);

	return bRet;
}

bool CVSB_ClassObject::IsPropertyAttribute(const wchar_t* szName)
{
	bool bRet = false;
	if(szName != NULL)
	{
		std::wstring stemp = szName;
		bRet = IsPropertyAttribute(stemp);
	}

	return bRet;
}

bool CVSB_ClassObject::IsMethodAttribute(std::wstring& szName)
{
	bool bRet = false;

	bRet = HasMethod(szName);

	return bRet;
}

bool CVSB_ClassObject::IsMethodAttribute(const wchar_t* szName)
{
	bool bRet = false;
	if(szName != NULL)
	{
		std::wstring stemp = szName;
		bRet = IsMethodAttribute(stemp);
	}

	return bRet;
}

bool CVSB_ClassObject::IsPropertyBuildInType(std::wstring& szName)
{
	bool bRet = false;
	IVSB_DataBase* pData = GetProperty(szName);
	if(pData)
	{
		bRet = pData->IsBuiltInType();
	}

	return bRet;
}

bool CVSB_ClassObject::IsPropertyBuildInType(const wchar_t* szName)
{
	bool bRet = false;
	if(szName != NULL)
	{
		std::wstring stemp = szName;
		bRet = IsPropertyBuildInType(stemp);
	}

	return bRet;
}

bool CVSB_ClassObject::IsPropertyClassType(std::wstring& szName)
{
	bool bRet = false;
	IVSB_DataBase* pData = GetProperty(szName);
	if(pData)
	{
		bRet = pData->IsClassType();
	}

	return bRet;
}

bool CVSB_ClassObject::IsPropertyClassType(const wchar_t* szName)
{
	bool bRet = false;
	if(szName != NULL)
	{
		std::wstring stemp = szName;
		bRet = IsPropertyClassType(stemp);
	}

	return bRet;
}

CVSB_ClassType CVSB_ClassObject::GetPropertyType(std::wstring& szName)
{
	CVSB_ClassType paraType;
	paraType.Empty();
	IVSB_DataBase* pData = GetProperty(szName);
	if(pData)
	{
		paraType = pData->GetType();
	}

	return paraType;
}

CVSB_ClassType CVSB_ClassObject::GetPropertyType(const wchar_t* szName)
{
	CVSB_ClassType paraType;
	paraType.Empty();
	if(szName != NULL)
	{
		std::wstring stemp = szName;
		paraType = GetPropertyType(stemp);
	}

	return paraType;
}

bool CVSB_ClassObject::IsCirclurClassType(CVSB_ClassType clstype)
{
	bool bRet = false;

	CVSB_ClassType mytype = GetType();
	if(mytype == clstype)
	{
		bRet = true;
		return bRet;
	}

	if(m_Ancestor)
	{
		bRet = m_Ancestor->IsCirclurClassType(clstype);
	}

	return bRet;
}