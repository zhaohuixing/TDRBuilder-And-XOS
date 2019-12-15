/*****************************************************/
// Project: 
//
// File Name: XOS_ParType.cpp
//
// Description: The parameter type class implementation.
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2004, All rights reserved.
//
// Creation Date: 09/10/2004	
//
// History:
// 1.    10/27/2004: Freeze for patent application	
//
/*****************************************************/
// Project: Visual System Builder
//
// File Name: xvsb_paratype.cpp
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Updated Date: 05/05/2005	
//
// History:
// 1.    05/05/2005: Updated from XOS_ParType.cpp	
//

#include "xvsb_paratype.h"

CVSB_ParamType::CVSB_ParamType(void)
	: m_ClsType()
{
}

CVSB_ParamType::CVSB_ParamType(std::wstring& szNSpace, std::wstring& szType, std::wstring& szClass)
	: m_ClsType(szNSpace, szType, szClass)
{
}

CVSB_ParamType::CVSB_ParamType(const wchar_t* szNSpace, const wchar_t* szType, const wchar_t* szClass)
	: m_ClsType(szNSpace, szType, szClass)
{
}

CVSB_ParamType::CVSB_ParamType(const CVSB_ClassType& clsType)
	: m_ClsType(clsType)
{
}

CVSB_ParamType::CVSB_ParamType(const CVSB_ParamType& pdes)
	: m_ClsType(pdes.m_ClsType)
{
}

CVSB_ParamType::~CVSB_ParamType(void)
{
}

std::wstring& CVSB_ParamType::GetNameSpace(void)
{
	return m_ClsType.m_szNameSpace;
}

std::wstring& CVSB_ParamType::GetType(void)
{
	return m_ClsType.m_szType;
}

std::wstring& CVSB_ParamType::GetClass(void)
{
	return m_ClsType.m_szClass;
}

const wchar_t* CVSB_ParamType::GetNameSpace(void) const 
{
	return m_ClsType.m_szNameSpace.c_str();
}

const wchar_t* CVSB_ParamType::GetType(void) const 
{
	return m_ClsType.m_szType.c_str();
}

const wchar_t* CVSB_ParamType::GetClass(void) const 
{
	return m_ClsType.m_szClass.c_str();
}

void CVSB_ParamType::SetNameSpace(std::wstring& szNSpace)
{
	m_ClsType.m_szNameSpace = szNSpace;
}

void CVSB_ParamType::SetType(std::wstring& szType)
{
	m_ClsType.m_szType = szType;
}

void CVSB_ParamType::SetClass(std::wstring& szClass)
{
	m_ClsType.m_szClass = szClass;
}

void CVSB_ParamType::SetNameSpace(const wchar_t* szNSpace)
{
	m_ClsType.m_szNameSpace = szNSpace;
}

void CVSB_ParamType::SetType(const wchar_t* szType)
{
	m_ClsType.m_szType = szType;
}

void CVSB_ParamType::SetClass(const wchar_t* szClass)
{
	m_ClsType.m_szClass = szClass;
}

void CVSB_ParamType::Empty(void)
{
	m_ClsType.Empty();
}

bool CVSB_ParamType::IsEmpty(void) const 
{
	return m_ClsType.IsEmpty();
}

bool CVSB_ParamType::IsVoid(void) const
{
	return m_ClsType.IsEmpty();
}

void CVSB_ParamType::SetClassType(const CVSB_ClassType& clsType)
{ 
	m_ClsType = clsType;
}

void CVSB_ParamType::SetClassType(std::wstring& szNSpace, std::wstring& szType, std::wstring& szClass)
{ 
	m_ClsType.Set(szNSpace, szType, szClass);
}

void CVSB_ParamType::SetClassType(const wchar_t* szNSpace, const wchar_t* szType, const wchar_t* szClass)
{ 
	m_ClsType.Set(szNSpace, szType, szClass);
}

CVSB_ClassType CVSB_ParamType::GetClassType(void)
{
	return m_ClsType;
}

bool CVSB_ParamType::IsSameClassType(const CVSB_ClassType& clsType)
{
	return (m_ClsType == clsType);
}

bool CVSB_ParamType::IsSameClassType(const CVSB_ParamType& parType)
{
	return (m_ClsType == parType.m_ClsType);
}

CVSB_ParamType::operator CVSB_ClassType (void)
{
	return m_ClsType;
}	

CVSB_ParamType* CVSB_ParamType::Clone(void)
{
	return new CVSB_ParamType(m_ClsType);
} 	

bool CVSB_ParamType::IsBuildInType(void) const
{
	return m_ClsType.IsBuildInType();
}	

bool CVSB_ParamType::IsArrayType(void) const
{
	return m_ClsType.IsArrayType();
}	

bool CVSB_ParamType::IsIntegerType(void) const
{
	return m_ClsType.IsIntegerType();
}	

bool CVSB_ParamType::IsByteType(void) const
{
	return m_ClsType.IsByteType();
}	

bool CVSB_ParamType::IsFloatType(void) const
{
	return m_ClsType.IsFloatType();
}	

bool CVSB_ParamType::IsBoolType(void) const
{
	return m_ClsType.IsBoolType();
}	

bool CVSB_ParamType::IsCharType(void) const 
{
	return m_ClsType.IsCharType();
}	

std::wstring CVSB_ParamType::GetClassTypeStr(void)
{
	return m_ClsType.GetClassTypeStr();
}

std::wstring CVSB_ParamType::GetNameSpaceClassString(void)
{
	return m_ClsType.GetNameSpaceClassString();
}

CVSB_ParamType& CVSB_ParamType::operator = (const CVSB_ParamType& parType)
{
	m_ClsType = parType.m_ClsType;
	return *this;
}

bool operator == (const CVSB_ParamType& pt1, const CVSB_ParamType& pt2)	
{
	bool bRet;
	bRet = (pt1.m_ClsType == pt2.m_ClsType); 

	return bRet;
}

bool operator != (const CVSB_ParamType& pt1, const CVSB_ParamType& pt2)
{
	return !(pt1 == pt2);
}

bool operator < (const CVSB_ParamType& pt1, const CVSB_ParamType& pt2)
{
	return (pt1.m_ClsType < pt2.m_ClsType);
}

bool operator <= (const CVSB_ParamType& pt1, const CVSB_ParamType& pt2)
{
	return (pt1.m_ClsType <= pt2.m_ClsType);
}

bool operator > (const CVSB_ParamType& pt1, const CVSB_ParamType& pt2)
{
	return (pt1.m_ClsType > pt2.m_ClsType);
}

bool operator >= (const CVSB_ParamType& pt1, const CVSB_ParamType& pt2)
{
	return (pt1.m_ClsType >= pt2.m_ClsType);
}

CVSB_ParamType& CVSB_ParamType::operator = (const CVSB_ClassType& clsType)
{
	m_ClsType = clsType;
	return *this;
}

bool operator == (const CVSB_ClassType& pt1, const CVSB_ParamType& pt2)
{
	bool bRet;
	bRet = (pt1 == pt2.m_ClsType); 

	return bRet;
}

bool operator != (const CVSB_ClassType& pt1, const CVSB_ParamType& pt2)
{
	return !(pt1 == pt2);
}

bool operator == (const CVSB_ParamType& pt1, const CVSB_ClassType& pt2)	
{
	bool bRet;
	bRet = (pt1.m_ClsType == pt2); 

	return bRet;
}

bool operator != (const CVSB_ParamType& pt1, const CVSB_ClassType& pt2)
{
	return !(pt1 == pt2);
}