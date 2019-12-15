// Project: Visual System Builder
//
// File Name: xvsb_fpara.cpp
//
// Description: The implementation of the class member function parameter object
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
#include "xvsb_fpara.h"

CVSB_FnParam::CVSB_FnParam(void)
	: m_parName(L""), m_parType()
{
	m_pData = NULL;
}

CVSB_FnParam::CVSB_FnParam(std::wstring& szPName, CVSB_ParamType& parType)
	: m_parName(szPName), m_parType(parType)
{
	m_pData = NULL;
}

CVSB_FnParam::CVSB_FnParam(const wchar_t* szPName, CVSB_ParamType& parType)
	: m_parName(szPName), m_parType(parType)
{
	m_pData = NULL;
}

CVSB_FnParam::CVSB_FnParam(std::wstring& szPName, CVSB_ClassType& clsType)
	: m_parName(szPName), m_parType(clsType)
{
	m_pData = NULL;
}


CVSB_FnParam::CVSB_FnParam(const wchar_t* szPName, CVSB_ClassType& clsType)
	: m_parName(szPName), m_parType(clsType)
{
	m_pData = NULL;
}


CVSB_FnParam::CVSB_FnParam(const CVSB_FnParam& para)
	: m_parName(para.GetName()), m_parType(para.GetType())
{
	m_pData = NULL;
}

CVSB_FnParam::~CVSB_FnParam(void)
{
	Reset();
}

void CVSB_FnParam::Reset(void)
{
	m_pData = NULL;
}

bool CVSB_FnParam::AttachData(IVSB_DataBase* pData)
{
	bool bRet = false;

	if(pData == NULL || pData->GetParamType() != m_parType || m_parType.IsVoid())
		return bRet;

	m_pData = NULL;
	bRet = true;
	return bRet;
}

CVSB_FnParam& CVSB_FnParam::operator = (const CVSB_FnParam& para)
{
	m_parName = para.GetName();
	m_parType = para.GetType();

	return *this;
}
