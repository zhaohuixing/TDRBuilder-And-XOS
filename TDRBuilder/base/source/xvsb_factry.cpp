// Project: Visual System Builder
//
// File Name: xvsb_factry.cpp
//
// Description: The implementations of the object creation factory classes
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
#include "xvsb_factry.h"
#include "xvsb_float.h"
#include "xvsb_int.h"
#include "xvsb_byte.h"
#include "xvsb_char.h"
#include "xvsb_bool.h"
#include "xvsb_array.h"
#include "xvsb_macro.h"
#include "xvsb_clsobj.h"
#include <assert.h>


CVSB_DataFactory::CVSB_DataFactory(const CVSB_ClassType& type) : m_Type(type), m_Name(L"")
{
}

CVSB_DataFactory::CVSB_DataFactory(const CVSB_ClassType& type, const std::wstring& name)
	: m_Type(type), m_Name(name)
{
}

CVSB_DataFactory::CVSB_DataFactory(const CVSB_ClassType& type, const wchar_t* name)
	: m_Type(type), m_Name(name)
{
}

CVSB_DataFactory::CVSB_DataFactory(int nTypeID, const std::wstring& name)
	: m_Name(name)
{
	if(nTypeID == XVSM_DT_FLOAT)
	{
		m_Type.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_FLOAT);
	}
	else if(nTypeID == XVSM_DT_INTEGER)
	{
		m_Type.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_INTEGER);
	}
	else if(nTypeID == XVSM_DT_BYTE)
	{
		m_Type.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BYTE);
	}
	else if(nTypeID == XVSM_DT_BOOL)
	{
		m_Type.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BOOL);
	}
	else if(nTypeID == XVSM_DT_CHAR)
	{
		m_Type.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_CHAR);
	}
}

CVSB_DataFactory::CVSB_DataFactory(int nTypeID, const wchar_t* name)
	: m_Name(name)
{
	if(nTypeID == XVSM_DT_FLOAT)
	{
		m_Type.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_FLOAT);
	}
	else if(nTypeID == XVSM_DT_INTEGER)
	{
		m_Type.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_INTEGER);
	}
	else if(nTypeID == XVSM_DT_BYTE)
	{
		m_Type.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BYTE);
	}
	else if(nTypeID == XVSM_DT_BOOL)
	{
		m_Type.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BOOL);
	}
	else if(nTypeID == XVSM_DT_CHAR)
	{
		m_Type.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_CHAR);
	}
}


IVSB_DataBase* CVSB_DataFactory::operator ()(void)
{
	IVSB_DataBase* pData = NULL;

	if(m_Type.IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_FLOAT))
	{
		pData = new CVSB_Float(m_Name);
	}
	else if(m_Type.IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_INTEGER))
	{
		pData = new CVSB_Integer(m_Name);
	}
	else if(m_Type.IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BYTE))
	{
		pData = new CVSB_Byte(m_Name);
	}
	else if(m_Type.IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_CHAR))
	{
		pData = new CVSB_Char(m_Name);
	}
	else if(m_Type.IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BOOL))
	{
		pData = new CVSB_Bool(m_Name);
	}

	return pData;
}

IVSB_DataBase* CVSB_DataFactory::operator ()(const std::wstring& szDefVal)
{
	IVSB_DataBase* pData = NULL;

	if(m_Type.IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_FLOAT))
	{
		pData = new CVSB_Float(m_Name);
		double dVal;
		dVal = _wtof(szDefVal.c_str());
		((CVSB_Float*)pData)->SetDefault(dVal);
	}
	else if(m_Type.IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_INTEGER))
	{
		pData = new CVSB_Integer(m_Name);
		__int64 nVal;
		nVal = _wtoi64(szDefVal.c_str());
		((CVSB_Integer*)pData)->SetDefault(nVal);
	}
	else if(m_Type.IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BYTE))
	{
		pData = new CVSB_Byte(m_Name);
		unsigned char btVal;
		btVal = (unsigned char)_wtol(szDefVal.c_str());
		((CVSB_Byte*)pData)->SetDefault(btVal);
	}
	else if(m_Type.IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_CHAR))
	{
		pData = new CVSB_Char(m_Name);
		wchar_t cVal;
		cVal = szDefVal[0];
		((CVSB_Char*)pData)->SetDefault(cVal);
	}
	else if(m_Type.IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BOOL))
	{
		pData = new CVSB_Bool(m_Name);
		bool bVal;
		bVal = (szDefVal == L"true"? true : false);
		((CVSB_Bool*)pData)->SetDefault(bVal);
	}

	return pData;
}

IVSB_DataBase* CVSB_DataFactory::operator ()(int nSize)
{
	IVSB_DataBase* pData = NULL;

	bool bRet = (m_Type.IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_FLOAT) ||
		         m_Type.IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_INTEGER) ||
				 m_Type.IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BYTE) ||
				 m_Type.IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_CHAR) ||
				 m_Type.IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BOOL));
	if(bRet && 0 < nSize)
	{
		pData = new CVSB_Array(m_Type, nSize, m_Name);
	}

	return pData;
}

CVSB_ClassType CVSB_DataFactory::GetBuildInType(int nTypeID)
{
	CVSB_ClassType cType;

	if(nTypeID == XVSM_DT_FLOAT)
	{
		cType.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_FLOAT);
	}
	else if(nTypeID == XVSM_DT_INTEGER)
	{
		cType.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_INTEGER);
	}
	else if(nTypeID == XVSM_DT_BYTE)
	{
		cType.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BYTE);
	}
	else if(nTypeID == XVSM_DT_BOOL)
	{
		cType.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BOOL);
	}
	else if(nTypeID == XVSM_DT_CHAR)
	{
		cType.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_CHAR);
	}
	else if(nTypeID == XVSM_DT_ARRAY)
	{
		cType.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_ARRAY);
	}

	return cType;
}

std::wstring CVSB_DataFactory::GetBuildInTypeString(const CVSB_ClassType& cType)
{
	std::wstring szTemp;
	szTemp.clear();
	if(cType.IsBuildInType())
	{
		if(cType.IsBoolType())
		{
			szTemp = XVSM_DTSTR[XVSM_DT_BOOL];
		}
		else if(cType.IsByteType())
		{
			szTemp = XVSM_DTSTR[XVSM_DT_BYTE];
		}
		else if(cType.IsCharType())
		{
			szTemp = XVSM_DTSTR[XVSM_DT_CHAR];
		}
		else if(cType.IsIntegerType())
		{
			szTemp = XVSM_DTSTR[XVSM_DT_INTEGER];
		}
		else if(cType.IsFloatType())
		{
			szTemp = XVSM_DTSTR[XVSM_DT_FLOAT];
		}
	}

	return szTemp;
}


int CVSB_DataFactory::GetBuildInTypeIndex(const CVSB_ClassType& cType)
{
	int nType = -1;

	if(cType.IsBuildInType())
	{
		if(cType.IsBoolType())
		{
			nType = XVSM_DT_BOOL;
		}
		else if(cType.IsByteType())
		{
			nType = XVSM_DT_BYTE;
		}
		else if(cType.IsCharType())
		{
			nType = XVSM_DT_CHAR;
		}
		else if(cType.IsIntegerType())
		{
			nType = XVSM_DT_INTEGER;
		}
		else if(cType.IsFloatType())
		{
			nType = XVSM_DT_FLOAT;
		}
	}

	return nType;
}