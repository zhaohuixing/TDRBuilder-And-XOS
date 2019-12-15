#include "xos_helper.h"
#include "xos_const.h"
#include "xos_clsbase.h"


CXOS_Method::CXOS_Method(void)
{
	m_szClass = L"CXOS_Method";
	m_szName = L"";
	m_LocalVarTable.clear();
	m_InputVarTable.clear();
	m_FN2True.clear();	
	m_FN2False.clear();
	m_OutputTable.clear();

	m_Condition.SetName(m_szName);

	m_pOwner = NULL;
}

CXOS_Method::CXOS_Method(std::wstring& szName)
{
	m_szClass = L"CXOS_Method";
	m_szName = szName;

	m_LocalVarTable.clear();
	m_InputVarTable.clear();
	m_OutputTable.clear();

	m_FN2True.clear();	
	m_FN2False.clear();
	m_Condition.SetName(m_szName);
	m_pOwner = NULL;
}

CXOS_Method::CXOS_Method(const wchar_t* szName)
{
	m_szClass = L"CXOS_Method";
	m_szName = szName;

	m_LocalVarTable.clear();
	m_InputVarTable.clear();
	m_OutputTable.clear();

	m_FN2True.clear();	
	m_FN2False.clear();
	m_Condition.SetName(m_szName);
	m_pOwner = NULL;
}

CXOS_Method::~CXOS_Method(void)
{
	Reset();
	m_pOwner = NULL;
}

void CXOS_Method::ClearInput(void)
{
	m_InputVarTable.clear();
}

void CXOS_Method::ClearLocal(void)
{
	CXOS_ClassObjTableFree objFree;
	objFree(m_LocalVarTable);
}

void CXOS_Method::ClearOutput(void)
{
	m_OutputTable.clear();
}

void CXOS_Method::ClearFnTrue(void)
{
	CXOS_MethodTableFree FnFree;
	FnFree(m_FN2True);
}

void CXOS_Method::ClearFnFalse(void)
{
	CXOS_MethodTableFree FnFree;
	FnFree(m_FN2False);
}

void CXOS_Method::Reset(void)
{
	ClearInput();
	ClearLocal();
	ClearOutput();
	m_Condition.Reset();
}

bool CXOS_Method::AddOutput(CXOS_ClassObject* pOut)
{
	bool bRet = true;

	if(pOut == NULL)
	{
		return !bRet;
	}

	CXOS_ClassObjTable::iterator iter = m_OutputTable.find(pOut->GetName());
	if(iter == m_OutputTable.end())
	{
		m_OutputTable.insert(std::make_pair(pOut->GetName(), pOut));
	}
	else
	{
		return !bRet;
	}
	
	return bRet;
}

bool CXOS_Method::AddInput(CXOS_ClassObject* pObj)
{
	bool bRet = true;

	if(pObj == NULL)
	{
		return !bRet;
	}

	CXOS_ClassObjTable::iterator iter = m_InputVarTable.find(pObj->GetName());
	if(iter == m_InputVarTable.end())
	{
		m_InputVarTable.insert(std::make_pair(pObj->GetName(), pObj));
	}
	else
	{
		return !bRet;
	}
	
	return bRet;
}

bool CXOS_Method::AddLocal(CXOS_ClassObject* pObj)
{
	bool bRet = true;

	if(pObj == NULL)
	{
		return !bRet;
	}

	CXOS_ClassObjTable::iterator iter = m_LocalVarTable.find(pObj->GetName());
	if(iter == m_LocalVarTable.end())
	{
		m_LocalVarTable.insert(std::make_pair(pObj->GetName(), pObj));
	}
	else
	{
		return !bRet;
	}
	
	return bRet;
}

bool CXOS_Method::AddFn2True(CXOS_Method* pFn)
{
	bool bRet = false;

	if(pFn == NULL)
	{
		return bRet;
	}

/*
	CXOS_MethodTable::iterator iter = m_FN2True.find(pFn->GetName());
	if(iter == m_FN2True.end())
	{
		m_FN2True.insert(std::make_pair(pFn->GetName(), pFn));
	}
	else
	{
		return !bRet;
	}
*/
	CXOS_MethodTable::iterator iter;
	bool bFind = false;

	for(iter = m_FN2True.begin(); iter != m_FN2True.end(); ++iter)
	{
		if((*iter)->GetNameStr() == pFn->GetNameStr())
		{
			bFind = true;
			break;
		}
	}

	if(bFind == false)
	{
		bRet = true;
		m_FN2True.push_back(pFn);
	}

	return bRet;
}

bool CXOS_Method::AddFn2False(CXOS_Method* pFn)
{
	bool bRet = false;

	if(pFn == NULL)
	{
		return bRet;
	}

/*
	CXOS_MethodTable::iterator iter = m_FN2False.find(pFn->GetName());
	if(iter == m_FN2False.end())
	{
		m_FN2False.insert(std::make_pair(pFn->GetName(), pFn));
	}
	else
	{
		return !bRet;
	}
*/	
	CXOS_MethodTable::iterator iter;
	bool bFind = false;

	for(iter = m_FN2False.begin(); iter != m_FN2False.end(); ++iter)
	{
		if((*iter)->GetNameStr() == pFn->GetNameStr())
		{
			bFind = true;
			break;
		}
	}

	if(bFind == false)
	{
		bRet = true;
		m_FN2False.push_back(pFn);
	}

	return bRet;

	return bRet;
}

int CXOS_Method::operator ()(void)
{
	int bRet = 1;
	CXOS_MethodTable::iterator iter;
	CXOS_Method* pFn;

	if(m_Condition())
	{
		for(iter = m_FN2True.begin(); iter != m_FN2True.end(); ++iter)
		{
			//pFn = iter->second;
			pFn = *iter;
			if(pFn)
			{
				bRet = (*pFn)();
				if(bRet == XOS_ERR)
					break;
			}
		}
	}
	else
	{
		for(iter = m_FN2False.begin(); iter != m_FN2False.end(); ++iter)
		{
			//pFn = iter->second;
			pFn = *iter;
			if(pFn)
			{
				bRet = (*pFn)();
				if(bRet == XOS_ERR)
					break;
			}
		}
	}

	return bRet;
}