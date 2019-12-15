// Date: 06/12/2004	
#include "xos_app.h"

CXOS_Instance::CXOS_Instance(void)
{
	m_szClass = L"CXOS_Instance";
	m_szName = L"";
//	m_Procedure.clear();
//	m_ObjectTable.clear();
}

CXOS_Instance::CXOS_Instance(std::wstring& szName)
{
	m_szClass = L"CXOS_Instance";
	m_szName = szName;
//	m_Procedure.clear();
//	m_ObjectTable.clear();
}

CXOS_Instance::CXOS_Instance(const wchar_t* szName)
{
	m_szClass = L"CXOS_Instance";
	m_szName = szName;
//	m_Procedure.clear();
//	m_ObjectTable.clear();
}

CXOS_Instance::~CXOS_Instance(void)
{
//	Reset();
}

/*
void CXOS_Instance::ClearProc(void)
{
	CXOS_ProcFree pfnFree;
	pfnFree(m_Procedure);
}

void CXOS_Instance::ClearObject(void)
{
	CXOS_ClassObjTableFree	objFree;
	objFree(m_ObjectTable);
}

void CXOS_Instance::Reset(void)
{
	ClearProc();
	ClearObject();
}
*/

int CXOS_Instance::Run(void)
{
	int nRet = 0;
/*
	CXOS_ProcList::iterator iter;
	CXOS_ClassObjTable::iterator clsit;

	std::wstring szClass;
	std::wstring szObj;
	std::wstring szFunc;

	for(iter = m_Procedure.begin(); iter != m_Procedure.end(); ++iter)
	{
		szClass = (*iter)->Class();
		szObj = (*iter)->Object();
		szFunc = (*iter)->MemFn();

		if(szClass.empty() || szObj.empty() || szFunc.empty())
		{
			nRet = -1;
			return nRet;
		}

		// Check existance of objec
		clsit = m_ObjectTable.find(szObj.c_str());		
		if(clsit == m_ObjectTable.end())
		{
			nRet = -1;
			return nRet;
		}

		// Check class type
		if(!clsit->second->IsClass(szClass))
		{
			nRet = -1;
			return nRet;
		}

		// Check function
		if(!clsit->second->CheckMethod(szFunc))
		{
			nRet = -1;
			return nRet;
		}

		// Run
		nRet = (*clsit->second)(szFunc);
		if(nRet == -1)
		{
			return nRet;
		}


	}
*/
	return nRet;
}