// Project: Visual System Builder
//
// File Name: xvsb_array.cpp
//
// Description: The implementation of the fixed size array
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/21/2005	
//
// History:
// 1.    01/21/2005: Create	
//
#include "xvsb_array.h"
#include "xvsb_factry.h"
#include "xvsb_macro.h"

CVSB_Array::CVSB_Array(CVSB_ClassType elmType, int nSize)
	: IVSB_DataBase(XVSM_TYPE_ARRAY)
{
	m_nSize = nSize;

#ifdef _XSVM_DEBUG_
	assert(m_nSize != 0);	
#endif

	if(m_nSize == 0)
	{
		m_bOK = false;
		return;
	}
	m_Array.clear();
	m_elmType = elmType;
	CVSB_DataFactory dFactry(elmType);
	IVSB_DataBase* pData = NULL;

	for(int i = 0; i < nSize; i++)
	{
		pData = dFactry();
		if(pData)
		{
			m_Array.push_back(pData);
		}
		else
		{
			m_bOK = false;
			return;
		}
	}
	m_bOK = true;
}

CVSB_Array::CVSB_Array(CVSB_ClassType elmType, int nSize, const wchar_t* szName)
	: IVSB_DataBase(XVSM_TYPE_ARRAY, szName)
{
	m_nSize = nSize;

#ifdef _XSVM_DEBUG_
	assert(m_nSize != 0);	
#endif

	if(m_nSize == 0)
	{
		m_bOK = false;
		return;
	}
	m_Array.clear();
	m_elmType = elmType;
	CVSB_DataFactory dFactry(elmType);
	IVSB_DataBase* pData = NULL;

	for(int i = 0; i < nSize; i++)
	{
		pData = dFactry();
		if(pData)
		{
			m_Array.push_back(pData);
		}
		else
		{
			m_bOK = false;
			return;
		}
	}
	m_bOK = true;
}

CVSB_Array::CVSB_Array(CVSB_ClassType elmType, int nSize, const std::wstring& szName)
	: IVSB_DataBase(XVSM_TYPE_ARRAY, szName.c_str())
{
	m_nSize = nSize;
	
#ifdef _XSVM_DEBUG_
	assert(m_nSize != 0);	
#endif

	if(m_nSize == 0)
	{
		m_bOK = false;
		return;
	}
	m_Array.clear();
	m_elmType = elmType;
	CVSB_DataFactory dFactry(elmType);
	IVSB_DataBase* pData = NULL;

	for(int i = 0; i < nSize; i++)
	{
		pData = dFactry();
		if(pData)
		{
			m_Array.push_back(pData);
		}
		else
		{
			m_bOK = false;
			return;
		}
	}
	m_bOK = true;
}

CVSB_Array::CVSB_Array(int nTypeID, int nSize, const wchar_t* szName)
	: IVSB_DataBase(XVSM_TYPE_ARRAY, szName)
{
	m_nSize = nSize;
	
#ifdef _XSVM_DEBUG_
	assert(m_nSize != 0);	
#endif

	if(m_nSize == 0)
	{
		m_bOK = false;
		return;
	}

	if(nTypeID == XVSM_DT_FLOAT)
	{
		m_elmType.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_FLOAT);
	}
	else if(nTypeID == XVSM_DT_INTEGER)
	{
		m_elmType.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_INTEGER);
	}
	else if(nTypeID == XVSM_DT_BYTE)
	{
		m_elmType.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BYTE);
	}
	else if(nTypeID == XVSM_DT_BOOL)
	{
		m_elmType.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BOOL);
	}
	else if(nTypeID == XVSM_DT_CHAR)
	{
		m_elmType.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_CHAR);
	}
	else
	{
		m_bOK = false;
		return;
	}

	m_Array.clear();
	CVSB_DataFactory dFactry(m_elmType);
	IVSB_DataBase* pData = NULL;

	for(int i = 0; i < nSize; i++)
	{
		pData = dFactry();
		if(pData)
		{
			m_Array.push_back(pData);
		}
		else
		{
			m_bOK = false;
			return;
		}
	}
	m_bOK = true;
}

CVSB_Array::CVSB_Array(int nTypeID, int nSize, const std::wstring& szName)
	: IVSB_DataBase(XVSM_TYPE_ARRAY, szName.c_str())
{
	m_nSize = nSize;
	
#ifdef _XSVM_DEBUG_
	assert(m_nSize != 0);	
#endif

	if(m_nSize == 0)
	{
		m_bOK = false;
		return;
	}

	if(nTypeID == XVSM_DT_FLOAT)
	{
		m_elmType.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_FLOAT);
	}
	else if(nTypeID == XVSM_DT_INTEGER)
	{
		m_elmType.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_INTEGER);
	}
	else if(nTypeID == XVSM_DT_BYTE)
	{
		m_elmType.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BYTE);
	}
	else if(nTypeID == XVSM_DT_BOOL)
	{
		m_elmType.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BOOL);
	}
	else if(nTypeID == XVSM_DT_CHAR)
	{
		m_elmType.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_CHAR);
	}
	else
	{
		m_bOK = false;
		return;
	}

	m_Array.clear();
	CVSB_DataFactory dFactry(m_elmType);
	IVSB_DataBase* pData = NULL;

	for(int i = 0; i < nSize; i++)
	{
		pData = dFactry();
		if(pData)
		{
			m_Array.push_back(pData);
		}
		else
		{
			m_bOK = false;
			return;
		}
	}
	m_bOK = true;
}

CVSB_Array::CVSB_Array(IVSB_DataBase* elmVal, int nSize)
	: IVSB_DataBase(XVSM_TYPE_ARRAY)
{
	m_nSize = nSize;
	m_bOK = false;

#ifdef _XSVM_DEBUG_
	assert(m_nSize != 0);	
#endif

	if(m_nSize == 0)
	{
		m_bOK = false;
		return;
	}
	
#ifdef _XSVM_DEBUG_
	assert(elmVal != NULL);
#endif

	if(elmVal == NULL)
	{
		m_bOK = false;
		return;
	}
	m_elmType = elmVal->GetType();

	m_Array.clear();

	CVSB_DataFactory dFactry(m_elmType);
	IVSB_DataBase* pData = NULL;

	for(int i = 0; i < nSize; i++)
	{
		pData = dFactry();
		if(pData)
		{
			pData->Assign(elmVal);
			m_Array.push_back(pData);
		}
		else
		{
			m_bOK = false;
			return;
		}
	}
	m_bOK = true;
}

CVSB_Array::CVSB_Array(IVSB_DataBase* elmVal, int nSize, const wchar_t* szName)
	: IVSB_DataBase(XVSM_TYPE_ARRAY, szName)
{
	m_nSize = nSize;
	m_bOK = false;
	
#ifdef _XSVM_DEBUG_
	assert(m_nSize != 0);	
#endif

	if(m_nSize == 0)
	{
		m_bOK = false;
		return;
	}
	
#ifdef _XSVM_DEBUG_
	assert(elmVal != NULL);
#endif

	if(elmVal == NULL)
	{
		m_bOK = false;
		return;
	}
	m_elmType = elmVal->GetType();
	m_Array.clear();

	CVSB_DataFactory dFactry(m_elmType);
	IVSB_DataBase* pData = NULL;

	for(int i = 0; i < nSize; i++)
	{
		pData = dFactry();
		if(pData)
		{
			pData->Assign(elmVal);
			m_Array.push_back(pData);
		}
		else
		{
			m_bOK = false;
			return;
		}
	}
	m_bOK = true;
}

CVSB_Array::CVSB_Array(IVSB_DataBase* elmVal, int nSize, const std::wstring& szName)
	: IVSB_DataBase(XVSM_TYPE_ARRAY, szName.c_str())
{
	m_nSize = nSize;
	m_bOK = false;
	
#ifdef _XSVM_DEBUG_
	assert(m_nSize != 0);	
#endif

	if(m_nSize == 0)
	{
		m_bOK = false;
		return;
	}
	
#ifdef _XSVM_DEBUG_
	assert(elmVal != NULL);
#endif

	if(elmVal == NULL)
	{
		m_bOK = false;
		return;
	}
	m_elmType = elmVal->GetType();
	
	m_Array.clear();

	CVSB_DataFactory dFactry(m_elmType);
	IVSB_DataBase* pData = NULL;

	for(int i = 0; i < nSize; i++)
	{
		pData = dFactry();
		if(pData)
		{
			pData->Assign(elmVal);
			m_Array.push_back(pData);
		}
		else
		{
			m_bOK = false;
			return;
		}
	}
	m_bOK = true;
}

CVSB_Array::CVSB_Array(IVSB_DataBase* Array[], int nSize, const std::wstring& szName)
	: IVSB_DataBase(XVSM_TYPE_ARRAY, szName.c_str())
{
	m_nSize = nSize;
	m_bOK = false;
	
#ifdef _XSVM_DEBUG_
	assert(m_nSize != 0);	
#endif

	if(m_nSize == 0)
	{
		m_bOK = false;
		return;
	}
	
	m_Array.clear();

	for(int i = 0; i < nSize; i++)
	{
		m_Array.push_back(Array[i]);
	}
	m_bOK = true;
}


CVSB_Array::CVSB_Array(const CVSB_Array& array)
	: IVSB_DataBase(XVSM_TYPE_ARRAY, array.GetName())
{
	m_nSize = array.Size();
	
#ifdef _XSVM_DEBUG_
	assert(m_nSize != 0);	
#endif

	if(m_nSize == 0)
	{
		m_bOK = false;
		return;
	}
	m_elmType = array.GetElementType();

	m_Array.clear();

	CVSB_DataFactory dFactry(m_elmType);
	IVSB_DataBase* pData = NULL;
	
	for(int i = 0; i < m_nSize; i++)
	{
		pData = dFactry();
		if(pData && array[i])
		{
			pData->Assign(const_cast<IVSB_DataBase*>(array[i]));
			m_Array.push_back(pData);
		}
		else
		{
			m_bOK = false;
			return;
		}
	}
	m_bOK = true;
}

CVSB_Array::CVSB_Array(const CVSB_Array& array, const wchar_t* szName)
	: IVSB_DataBase(XVSM_TYPE_ARRAY, szName)
{
	m_nSize = array.Size();
	
#ifdef _XSVM_DEBUG_
	assert(m_nSize != 0);	
#endif
	if(m_nSize == 0)
	{
		m_bOK = false;
		return;
	}
	m_elmType = array.GetElementType();

	m_Array.clear();

	CVSB_DataFactory dFactry(m_elmType);
	IVSB_DataBase* pData = NULL;

	for(int i = 0; i < m_nSize; i++)
	{
		pData = dFactry();
		if(pData && array[i])
		{
			pData->Assign(const_cast<IVSB_DataBase*>(array[i]));
			m_Array.push_back(pData);
		}
		else
		{
			m_bOK = false;
			return;
		}
	}
	m_bOK = true;
}

CVSB_Array::CVSB_Array(const CVSB_Array& array, const std::wstring& szName)
	: IVSB_DataBase(XVSM_TYPE_ARRAY, szName)
{
	m_nSize = array.Size();
	
#ifdef _XSVM_DEBUG_
	assert(m_nSize != 0);	
#endif

	if(m_nSize == 0)
	{
		m_bOK = false;
		return;
	}
	m_elmType = array.GetElementType();

	m_Array.clear();

	CVSB_DataFactory dFactry(m_elmType);
	IVSB_DataBase* pData = NULL;

	for(int i = 0; i < m_nSize; i++)
	{
		pData = dFactry();
		if(pData && array[i])
		{
			pData->Assign(const_cast<IVSB_DataBase*>(array[i]));
			m_Array.push_back(pData);
		}
		else
		{
			m_bOK = false;
			return;
		}
	}
	m_bOK = true;
}

CVSB_Array::~CVSB_Array(void)
{
	IVSB_ArrayBaseFree aryFree;
	aryFree(m_Array);
}

CVSB_ClassType CVSB_Array::GetElementType(void)	const
{
	return m_elmType;
}

int CVSB_Array::Size(void) const
{
	return m_nSize;
}

const IVSB_DataBase* CVSB_Array::operator [] (int idx) const 
{
	if(idx < 0 || m_nSize <= idx || m_bOK == false)
		return NULL;
	else
		return m_Array[idx];
}

IVSB_DataBase* CVSB_Array::operator [] (int idx)
{
	if(idx < 0 || m_nSize <= idx || m_bOK == false)
		return NULL;
	else
		return m_Array[idx];
}

IVSB_DataBase* CVSB_Array::At(int idx) 
{
	if(idx < 0 || m_nSize <= idx || m_bOK == false)
		return NULL;
	else
		return m_Array[idx];
}

const IVSB_DataBase* CVSB_Array::At(int idx) const 
{
	if(idx < 0 || m_nSize <= idx || m_bOK == false)
		return NULL;
	else
		return m_Array[idx];
}

bool CVSB_Array::GetAt(int idx, IVSB_DataBase* pElem) 
{
	bool bRet = false;
	
#ifdef _XSVM_DEBUG_
	assert(pElem == NULL);
#endif

	if(pElem != NULL)
		return bRet;
	if(0 <= idx && idx < m_nSize && m_bOK == true)
	{
		bRet = m_Array[idx]->Clone((IVSB_Base**)&pElem);
	}

	return bRet;
}

bool CVSB_Array::SetAt(int idx, IVSB_DataBase* pElem)
{
	bool bRet = false;
	if(0 <= idx && idx < m_nSize && m_bOK == true)
	{
		bRet = m_Array[idx]->Assign(pElem);
	}

	return bRet;
}

bool CVSB_Array::IsCorrupt(void) const
{
	return (m_bOK == false);
}

bool CVSB_Array::IsOK(void) const
{
	return (m_bOK == true);
}

bool CVSB_Array::Clone(IVSB_Base** ppObj)
{
	bool bRet = false;

	if(ppObj == NULL || m_bOK == false)
		return bRet;

	*ppObj = new CVSB_Array(*this);
	if(*ppObj == NULL)
		return false;

	bRet = true;
	return bRet;
}

bool CVSB_Array::Clone(IVSB_Base** ppObj, const std::wstring& szName)
{
	bool bRet = false;

	if(ppObj == NULL || m_bOK == false)
		return bRet;

	*ppObj = new CVSB_Array(*this, szName);
	if(*ppObj == NULL)
		return false;

	bRet = true;
	return bRet;
}

bool CVSB_Array::Clone(IVSB_Base** ppObj, const wchar_t* szName)
{
	bool bRet = false;

	if(ppObj == NULL || m_bOK == false)
		return bRet;

	*ppObj = new CVSB_Array(*this, szName);
	if(*ppObj == NULL)
		return false;

	bRet = true;
	return bRet;
}

bool CVSB_Array::Assign(IVSB_DataBase* pData)
{
	bool bRet = false;
	if(pData && m_bOK == true)
	{
		int i;
		if(pData->GetType().GetClass() != XVSM_TYPE_ARRAY)
		{
			for(i = 0; i < m_nSize; i++)
			{
				bRet = m_Array[i]->Assign(pData);
				if(bRet == false)
					return bRet;
			}
		}
		else if(pData->GetType().GetClass() == XVSM_TYPE_ARRAY)
		{
			CVSB_Array* pArray = (CVSB_Array*)pData;
			int nSize = std::min(m_nSize, pArray->Size());
			for(i = 0; i < nSize; i++)
			{
				bRet = m_Array[i]->Assign(pArray->At(i));
				if(bRet == false)
					return bRet;
			}
		}
	}

	return bRet;
}

bool CVSB_Array::AssignDefault(IVSB_DataBase* pData)
{
	bool bRet = false;
	if(pData && m_bOK == true)
	{
		int i;
		if(pData->GetType().GetClass() != XVSM_TYPE_ARRAY)
		{
			for(i = 0; i < m_nSize; i++)
			{
				bRet = m_Array[i]->AssignDefault(pData);
				if(bRet == false)
					return bRet;
			}
		}
		else if(pData->GetType().GetClass() == XVSM_TYPE_ARRAY)
		{
			CVSB_Array* pArray = (CVSB_Array*)pData;
			int nSize = std::min(m_nSize, pArray->Size());
			for(i = 0; i < nSize; i++)
			{
				bRet = m_Array[i]->AssignDefault(pArray->At(i));
				if(bRet == false)
					return bRet;
			}
		}
	}

	return bRet;
}

bool CVSB_Array::Compare(IVSB_DataBase* pObj, enXVSB_CMPTYPE cmp) 
{
	bool bRet = false;
	
#ifdef _XSVM_DEBUG_
	assert(false);
#endif

	return bRet;
}

int CVSB_Array::GetDataTypeIndex(void)
{
	return XVSM_DT_ARRAY;
}

const wchar_t* CVSB_Array::GetDataTypeStr(void) const 
{
	return XVSM_DTSTR[XVSM_DT_ARRAY];
}

std::wstring CVSB_Array::GetDataTypeStr(void) 
{
	return std::wstring(XVSM_DTSTR[XVSM_DT_ARRAY]);
}

std::wstring CVSB_Array::GetDataValueStr(void) 
{
	m_szValStr.clear();
	m_szValStr = L"{";

    for(int i = 0; i < m_nSize; i++)
	{
		m_szValStr += m_Array[i]->GetDataValueStr();
		if(i < m_nSize-1)
		{
			m_szValStr += L",";
		}
	}
	m_szValStr += L"}";
	return m_szValStr;
}

const wchar_t* CVSB_Array::GetDataValueStr(void) const 
{
	m_szValStr.clear();
	m_szValStr = L"{";

    for(int i = 0; i < m_nSize; i++)
	{
		m_szValStr += m_Array[i]->GetDataValueStr();
		if(i < m_nSize-1)
		{
			m_szValStr += L",";
		}
	}
	m_szValStr += L"}";
	return m_szValStr.c_str();
}

int CVSB_Array::GetElementDataTypeIndex(void) 
{
	int nType = 0;

	if(m_elmType.IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_FLOAT))
	{
		nType = XVSM_DT_FLOAT;
	}
	else if(m_elmType.IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_INTEGER))
	{
		nType = XVSM_DT_INTEGER;
	}
	else if(m_elmType.IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BYTE))
	{
		nType = XVSM_DT_BYTE;
	}
	else if(m_elmType.IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BOOL))
	{
		nType = XVSM_DT_BOOL;		
	}

	return nType;
}

const wchar_t* CVSB_Array::GetElementDataTypeStr(void) const 
{
	int nType = 0;

	if(m_elmType.IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_FLOAT))
	{
		nType = XVSM_DT_FLOAT;
	}
	else if(m_elmType.IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_INTEGER))
	{
		nType = XVSM_DT_INTEGER;
	}
	else if(m_elmType.IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BYTE))
	{
		nType = XVSM_DT_BYTE;
	}
	else if(m_elmType.IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BOOL))
	{
		nType = XVSM_DT_BOOL;		
	}
	return XVSM_DTSTR[nType];
}

std::wstring CVSB_Array::GetElementDataTypeStr(void) 
{
	int nType = GetElementDataTypeIndex();
	return std::wstring(XVSM_DTSTR[nType]);
}

std::wstring CVSB_Array::GetDefaultValueStr(void) 
{
	m_szValStr.clear();
	m_szValStr = L"{";

    for(int i = 0; i < m_nSize; i++)
	{
		m_szValStr += m_Array[i]->GetDefaultValueStr();
		if(i < m_nSize-1)
		{
			m_szValStr += L",";
		}
	}
	m_szValStr += L"}";
	return m_szValStr;
}

const wchar_t* CVSB_Array::GetDefaultValueStr(void) const 
{
	m_szValStr.clear();
	m_szValStr = L"{";

    for(int i = 0; i < m_nSize; i++)
	{
		m_szValStr += m_Array[i]->GetDefaultValueStr();
		if(i < m_nSize-1)
		{
			m_szValStr += L",";
		}
	}
	m_szValStr += L"}";
	return m_szValStr.c_str();
}

void CVSB_Array::Reset(void)
{
    for(int i = 0; i < m_nSize; i++)
	{
		m_Array[i]->Reset();
	}
}
