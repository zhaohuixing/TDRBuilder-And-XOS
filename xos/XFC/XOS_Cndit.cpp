#include "xos_clsbase.h"

CXOS_Condition::CXOS_Condition(void)
	:CXOS_ClassObject(), m_Result(true, enXOS_OR)
{
	m_szClass = L"CXOS_Condition";
	m_szName = L"";
//	m_LGList.clear();
}

CXOS_Condition::CXOS_Condition(std::wstring& szName)
	:CXOS_ClassObject(), m_Result(true, enXOS_OR)
{
	m_szClass = L"CXOS_Condition";
	m_szName = szName;
//	m_LGList.clear();
}

CXOS_Condition::CXOS_Condition(const wchar_t* szName)
	:CXOS_ClassObject(), m_Result(true, enXOS_OR)
{
	m_szClass = L"CXOS_Condition";
	m_szName = szName;
//	m_LGList.clear();
}

CXOS_Condition::~CXOS_Condition(void)
{
//	m_LGList.clear();
}

bool CXOS_Condition::Set(CXOS_ClassObject* pObj)
{
	bool bRet = false;

	if(pObj && CXOS_Logic::TypeCheck(pObj->GetClassStr()))
	{
		bRet = CXOS_ClassObject::Set(pObj);
	}

	return bRet;
}

bool CXOS_Condition::operator ()(void)
{
	bool bRet = m_Result.m_Bool;
	bool bTemp = true;
	bool bOR = true;

	if(m_Property.empty())
	{
		return bRet;
	}
	else
	{
		CXOS_ClassObjTable::iterator iter;
		for(iter = m_Property.begin(); iter != m_Property.end(); ++iter)
		{
			bTemp = ((CXOS_Logic*)(iter->second))->Boolean();
			bOR = ((CXOS_Logic*)(iter->second))->Or();
			if(bOR)
			{
				bRet = (bRet || bTemp);
			}
			else
			{
				bRet = (bRet && bTemp);
			}
		}
	}

	return bRet;
}


std::wostream& operator << (std::wostream& out, const CXOS_Condition& ct)
{
	out << ct.m_Result;
	return out;
}

std::wistream& operator >> (std::wistream& in, CXOS_Condition& ct)
{
	in >> ct.m_Result;
	return in;
}


