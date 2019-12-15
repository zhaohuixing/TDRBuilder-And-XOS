// Date: 06/11/2004	
#include "xos_clsbase.h"
#include "xos_const.h"

CXOS_ClassObject::CXOS_ClassObject(void)
	:CXOS_Object()
{
	m_szClass = L"CXOS_ClassObject";
	m_szName = L"";
	m_Method.clear();
	m_Property.clear();
	m_pOwner = NULL;
}

CXOS_ClassObject::CXOS_ClassObject(std::wstring& szName)
	:CXOS_Object()
{
	m_szClass = L"CXOS_ClassObject";
	m_szName = szName;
	m_Method.clear();
	m_Property.clear();
	m_pOwner = NULL;
}

CXOS_ClassObject::CXOS_ClassObject(const wchar_t* szName)
	:CXOS_Object()
{
	m_szClass = L"CXOS_ClassObject";
	m_szName = szName;
	m_Method.clear();
	m_Property.clear();
	m_pOwner = NULL;
}

CXOS_ClassObject::~CXOS_ClassObject(void)
{
	Reset();
}

void CXOS_ClassObject::Reset(void)
{
	ClearMethod();
	ClearProperty();
}

void CXOS_ClassObject::ClearMethod(void)
{
	CXOS_MethodTableFree fnFree;
	fnFree(m_Method);
}

void CXOS_ClassObject::ClearProperty(void)
{
	CXOS_ClassObjTableFree objFree;
	objFree(m_Property);
}

bool CXOS_ClassObject::Method(CXOS_Method* pFn)
{
	bool bRet = false;
	if(pFn == NULL)
		return bRet;

/*
	CXOS_MethodTable::iterator iter = m_Method.find(pFn->GetName());
	if(iter == m_Method.end())
	{
		m_Method.insert(std::make_pair(pFn->GetName(), pFn));
		bRet = true;
	}
*/
	bool bFind = false;
	CXOS_MethodTable::iterator iter;
	for(iter = m_Method.begin(); iter != m_Method.end(); ++iter)
	{
		if((*iter)->GetNameStr() == pFn->GetNameStr())
		{
			bFind = true;
			break;
		}
	}

	if(bFind == false)
	{
		m_Method.push_back(pFn);
		bRet = true;
	}

	return bRet;
}


bool CXOS_ClassObject::Set(CXOS_ClassObject* pObj)
{
	bool bRet = false;
	if(pObj == NULL)
		return bRet;

	CXOS_ClassObjTable::iterator iter = m_Property.find(pObj->GetName());
	if(iter == m_Property.end())
	{
		m_Property.insert(std::make_pair(pObj->GetName(), pObj));
		bRet = true;
	}

	return bRet;
}


CXOS_ClassObject* CXOS_ClassObject::Get(std::wstring& szFnName) const
{
	CXOS_ClassObjTable::const_iterator iter = m_Property.find(szFnName.c_str());
	if(iter == m_Property.end())
		return NULL;

	return iter->second;
}

CXOS_Method* CXOS_ClassObject::Method(std::wstring& szFnName) const
{
/*
	CXOS_MethodTable::const_iterator iter = m_Method.find(szFnName.c_str());
	if(iter == m_Method.end())
		return NULL;

	return iter->second;
*/
	CXOS_MethodTable::const_iterator iter;
	for(iter = m_Method.begin(); iter != m_Method.end(); ++iter)
	{
		if((*iter)->GetNameStr() == szFnName)
		{
			return *iter;
		}
	}
	return NULL;
}

bool CXOS_ClassObject::CheckProperty(std::wstring& szFnName) const
{
	CXOS_ClassObjTable::const_iterator iter = m_Property.find(szFnName.c_str());
	if(iter == m_Property.end())
		return false;

	return true;
}

bool CXOS_ClassObject::CheckMethod(std::wstring& szFnName) const
{
/*
	CXOS_MethodTable::const_iterator iter = m_Method.find(szFnName.c_str());
	if(iter == m_Method.end())
		return false;

	return true;
*/
	CXOS_MethodTable::const_iterator iter;
	for(iter = m_Method.begin(); iter != m_Method.end(); ++iter)
	{
		if((*iter)->GetNameStr() == szFnName)
		{
			return true;
		}
	}
	return false;

}

void CXOS_ClassObject::SetOwnership(void)
{
	CXOS_ClassObjTable::iterator iter;
	for(iter = m_Property.begin(); iter != m_Property.end(); ++iter)
	{
		iter->second->SetOwner((CXOS_ClassObject*)this);
	}


	CXOS_MethodTable::iterator fiter;
	for(fiter = m_Method.begin(); fiter != m_Method.end(); ++fiter)
	{
		//fiter->second->SetOwner((CXOS_ClassObject*)this);
		(*fiter)->SetOwner((CXOS_ClassObject*)this);
	}
}

int CXOS_ClassObject::operator()(std::wstring& szFnName)
{
	int nRet = XOS_ERR;
/*
	CXOS_MethodTable::iterator iter = m_Method.find(szFnName.c_str());
	if(iter == m_Method.end())
		return nRet;

	nRet = (*(iter->second))();
*/
	CXOS_MethodTable::iterator iter;
	for(iter = m_Method.begin(); iter != m_Method.end(); ++iter)
	{
		if((*iter)->GetNameStr() == szFnName)
		{
			nRet = (*(*iter))();
			break;
		}
	}

	return nRet;
}

int CXOS_ClassObject::operator()(const wchar_t* szFnName)
{
	std::wstring szFn = szFnName;

	return (*this)(szFn);
}