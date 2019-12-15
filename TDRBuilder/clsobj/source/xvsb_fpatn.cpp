/*****************************************************/
// Project: 
//
// File Name: XOS_FnPatrn.cpp
//
// Description: The function pattern class implementation
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2004, All rights reserved.
//
// Date: 09/10/2004	
//
/*****************************************************/
// Project: Visual System Builder
//
// File Name: xvsb_fpatn.cpp
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Updated Date: 05/06/2005	
//
// History:
// 1.    05/06/2005: Updated from XOS_FnPatrn.cpp
//

#include "xvsb_fpatn.h"

CVSB_FnPattern::CVSB_FnPattern(void)
{
	m_ParaList.clear();
	m_Return.Empty();
	m_szFunc.clear();
}

CVSB_FnPattern::CVSB_FnPattern(std::wstring& szFunc)
{
	m_ParaList.clear();
	m_Return.Empty();
	m_szFunc = szFunc;
}

CVSB_FnPattern::CVSB_FnPattern(const wchar_t* szFunc)
{
	m_ParaList.clear();
	m_Return.Empty();
	m_szFunc = szFunc;
}

CVSB_FnPattern::CVSB_FnPattern(const CVSB_FnPattern& fnType)
{
	m_ParaList.clear();
	m_Return.Empty();
	m_szFunc.clear();

	if(!fnType.m_ParaList.empty())
	{
		for(int i = 0; i < (int)fnType.m_ParaList.size(); ++i)
		{
			m_ParaList.push_back(fnType.m_ParaList[i]);
		}
	}
	m_Return = fnType.m_Return;
	m_szFunc = fnType.m_szFunc;
}

CVSB_FnPattern::CVSB_FnPattern(const CVSB_FnParamPattern& fnType)
{
	m_ParaList.clear();
	m_szFunc.clear();

	if(!fnType.m_ParaList.empty())
	{
		for(int i = 0; i < (int)fnType.m_ParaList.size(); ++i)
		{
			m_ParaList.push_back(fnType.m_ParaList[i]);
		}
	}
	m_szFunc = fnType.m_szFunc;
}

CVSB_FnPattern::~CVSB_FnPattern(void)
{
	Reset();
}

void CVSB_FnPattern::Reset(void)
{
	m_ParaList.clear();
	m_Return.Empty();
	m_szFunc.clear();
}

void CVSB_FnPattern::AddParameter(const CVSB_ParamType& par)
{
	if(!par.IsEmpty())
	{
		m_ParaList.push_back(par);
	}
}

void CVSB_FnPattern::AddParameter(const CVSB_ClassType& par)
{
	if(!par.IsEmpty())
	{
		m_ParaList.push_back(CVSB_ParamType(par));
	}
}

void CVSB_FnPattern::AddParameter(std::wstring& szNSpace, std::wstring& szType, std::wstring& szClass)
{
	if(!szNSpace.empty() && !szType.empty() && !szClass.empty())
	{
		m_ParaList.push_back(CVSB_ParamType(szNSpace, szType, szClass));
	}
}

void CVSB_FnPattern::AddParameter(const wchar_t* szNSpace, const wchar_t* szType, const wchar_t* szClass)
{
	if(szNSpace != NULL && szType != NULL && szClass != NULL)
	{
		m_ParaList.push_back(CVSB_ParamType(szNSpace, szType, szClass));
	}
}

void CVSB_FnPattern::SetReturn(const CVSB_ParamType& par)
{
	m_Return = par;
}

void CVSB_FnPattern::SetReturn(const CVSB_ClassType& par)
{
	m_Return = par;
}

void CVSB_FnPattern::SetReturn(std::wstring& szNSpace, std::wstring& szType, std::wstring& szClass)
{
	if((!szNSpace.empty() && !szType.empty() && !szClass.empty()) ||
	   (szNSpace.empty() && szType.empty() && szClass.empty()))

	{
		m_Return.SetClassType(szNSpace, szType, szClass);
	}
}

void CVSB_FnPattern::SetReturn(const wchar_t* szNSpace, const wchar_t* szType, const wchar_t* szClass)
{
	if((szNSpace != NULL && szType != NULL && szClass != NULL) ||
	   (szNSpace == NULL && szType == NULL && szClass == NULL))

	{
		m_Return.SetClassType(szNSpace, szType, szClass);
	}
}

void CVSB_FnPattern::SetVoidReturn(void)
{
	m_Return.Empty();
}

void CVSB_FnPattern::SetFunction(std::wstring& szFunc)
{
	m_szFunc = szFunc;
}

void CVSB_FnPattern::SetFunction(const wchar_t* szFunc)
{
	m_szFunc = szFunc;
}

bool CVSB_FnPattern::IsValid(void)
{
	return !m_szFunc.empty();
}

bool CVSB_FnPattern::IsVoidReturn(void)
{
	return m_Return.IsEmpty();
}

CVSB_FnPattern& CVSB_FnPattern::operator = (const CVSB_FnPattern& fnType)
{
	Reset();

	if(!fnType.m_ParaList.empty())
	{
		for(int i = 0; i < (int)fnType.m_ParaList.size(); ++i)
		{
			m_ParaList.push_back(fnType.m_ParaList[i]);
		}
	}
	m_Return = fnType.m_Return;
	m_szFunc = fnType.m_szFunc;

	return *this;
}

CVSB_FnPattern& CVSB_FnPattern::operator = (const CVSB_FnParamPattern& fnType)
{
	Reset();

	if(!fnType.m_ParaList.empty())
	{
		for(int i = 0; i < (int)fnType.m_ParaList.size(); ++i)
		{
			m_ParaList.push_back(fnType.m_ParaList[i]);
		}
	}
	m_szFunc = fnType.m_szFunc;

	return *this;
}

bool operator == (const CVSB_FnPattern& pt1, const CVSB_FnPattern& pt2)	
{
	bool bRet = true;

	bRet = (pt1.m_szFunc == pt2.m_szFunc);
	if(!bRet)
		return bRet;

	bRet = (pt1.m_Return == pt2.m_Return);
	if(!bRet)
		return bRet;

	bRet = ((int)pt1.m_ParaList.size() == (int)pt2.m_ParaList.size());
	if(!bRet)
		return bRet;

	for(int i = 0; i < (int)pt1.m_ParaList.size(); i++)
	{
		bRet = (pt1.m_ParaList[i] == pt2.m_ParaList[i]);
		if(!bRet)
			return bRet;
	}

	return bRet;
}

bool operator < (const CVSB_FnPattern& pt1, const CVSB_FnPattern& pt2)
{
	bool bRet = true;

	bRet = (pt1.m_szFunc < pt2.m_szFunc);
	if(bRet)
		return bRet;

	if(!bRet && pt1.m_szFunc == pt2.m_szFunc)
	{
		bRet = (pt1.m_Return < pt2.m_Return);
	}
	else
	{
		return bRet;
	}

	if(bRet)
		return bRet;

	if(!bRet && pt1.m_Return == pt2.m_Return)
	{
		bRet = ((int)pt1.m_ParaList.size() < (int)pt2.m_ParaList.size());
	}
	else
	{
		return bRet;
	}

	if(bRet)
		return bRet;

	if(!bRet && ((int)pt1.m_ParaList.size() != (int)pt2.m_ParaList.size()))
		return bRet;

	for(int i = 0; i < (int)pt1.m_ParaList.size(); i++)
	{
		bRet = (pt1.m_ParaList[i] < pt2.m_ParaList[i]);
		if(bRet)
			return bRet;

		if(!bRet && pt1.m_ParaList[i] != pt2.m_ParaList[i])
			return bRet;
	}

	return bRet;
}

bool operator <= (const CVSB_FnPattern& pt1, const CVSB_FnPattern& pt2)
{
	bool bRet = true;

	bRet = (pt1.m_szFunc <= pt2.m_szFunc);
	if(!bRet)
		return bRet;

	if(bRet && pt1.m_szFunc == pt2.m_szFunc)
	{
		bRet = (pt1.m_Return <= pt2.m_Return);
	}
	else
	{
		return bRet;
	}

	if(!bRet)
		return bRet;


	if(bRet && pt1.m_Return == pt2.m_Return)
	{
		bRet = ((int)pt1.m_ParaList.size() <= (int)pt2.m_ParaList.size());
	}
	else
	{
		return bRet;
	}

	if(!bRet)
		return bRet;

	if(bRet && ((int)pt1.m_ParaList.size() != (int)pt2.m_ParaList.size()))
		return bRet;

	for(int i = 0; i < (int)pt1.m_ParaList.size(); i++)
	{
		bRet = (pt1.m_ParaList[i] <= pt2.m_ParaList[i]);
		if(!bRet)
			return bRet;

		if(bRet && pt1.m_ParaList[i] != pt2.m_ParaList[i])
			return bRet;
	}

	return bRet;
}



CVSB_FnParamPattern::CVSB_FnParamPattern(void)
{
	m_ParaList.clear();
	m_szFunc.empty();
}

CVSB_FnParamPattern::CVSB_FnParamPattern(std::wstring& szFunc)
{
	m_ParaList.clear();
	m_szFunc = szFunc;
}

CVSB_FnParamPattern::CVSB_FnParamPattern(const wchar_t* szFunc)
{
	m_ParaList.clear();
	m_szFunc = szFunc;
}

CVSB_FnParamPattern::CVSB_FnParamPattern(const CVSB_FnPattern& fnType)
{
	m_ParaList.clear();
	m_szFunc.clear();

	if(!fnType.m_ParaList.empty())
	{
		for(int i = 0; i < (int)fnType.m_ParaList.size(); ++i)
		{
			m_ParaList.push_back(fnType.m_ParaList[i]);
		}
	}
	m_szFunc = fnType.m_szFunc;
}

CVSB_FnParamPattern::CVSB_FnParamPattern(const CVSB_FnParamPattern& fnType)
{
	m_ParaList.clear();
	m_szFunc.clear();

	if(!fnType.m_ParaList.empty())
	{
		for(int i = 0; i < (int)fnType.m_ParaList.size(); ++i)
		{
			m_ParaList.push_back(fnType.m_ParaList[i]);
		}
	}
	m_szFunc = fnType.m_szFunc;
}

CVSB_FnParamPattern::~CVSB_FnParamPattern(void)
{
	Reset();
}

void CVSB_FnParamPattern::Reset(void)
{
	m_ParaList.clear();
	m_szFunc.clear();
}

void CVSB_FnParamPattern::AddParameter(const CVSB_ParamType& par)
{
	if(!par.IsEmpty())
	{
		m_ParaList.push_back(par);
	}
}

void CVSB_FnParamPattern::AddParameter(const CVSB_ClassType& par)
{
	if(!par.IsEmpty())
	{
		m_ParaList.push_back(CVSB_ParamType(par));
	}
}

void CVSB_FnParamPattern::AddParameter(std::wstring& szNSpace, std::wstring& szType, std::wstring& szClass)
{
	if(!szNSpace.empty() && !szType.empty() && !szClass.empty())
	{
		m_ParaList.push_back(CVSB_ParamType(szNSpace, szType, szClass));
	}
}

void CVSB_FnParamPattern::AddParameter(const wchar_t* szNSpace, const wchar_t* szType, const wchar_t* szClass)
{
	if(szNSpace != NULL && szType != NULL && szClass != NULL)
	{
		m_ParaList.push_back(CVSB_ParamType(szNSpace, szType, szClass));
	}
}

void CVSB_FnParamPattern::SetFunction(std::wstring& szFunc)
{
	m_szFunc = szFunc;
}

void CVSB_FnParamPattern::SetFunction(const wchar_t* szFunc)
{
	m_szFunc = szFunc;
}

bool CVSB_FnParamPattern::IsValid(void)
{
	return !m_szFunc.empty();
}

CVSB_FnParamPattern& CVSB_FnParamPattern::operator = (const CVSB_FnParamPattern& fnType)
{
	Reset();

	if(!fnType.m_ParaList.empty())
	{
		for(int i = 0; i < (int)fnType.m_ParaList.size(); ++i)
		{
			m_ParaList.push_back(fnType.m_ParaList[i]);
		}
	}
	m_szFunc = fnType.m_szFunc;

	return *this;
}

CVSB_FnParamPattern& CVSB_FnParamPattern::operator = (const CVSB_FnPattern& fnType)
{
	Reset();

	if(!fnType.m_ParaList.empty())
	{
		for(int i = 0; i < (int)fnType.m_ParaList.size(); ++i)
		{
			m_ParaList.push_back(fnType.m_ParaList[i]);
		}
	}
	m_szFunc = fnType.m_szFunc;

	return *this;
}

bool operator == (const CVSB_FnParamPattern& pt1, const CVSB_FnParamPattern& pt2)
{
	bool bRet = true;

	bRet = (pt1.m_szFunc == pt2.m_szFunc);
	if(!bRet)
		return bRet;

	bRet = ((int)pt1.m_ParaList.size() == (int)pt2.m_ParaList.size());
	if(!bRet)
		return bRet;

	for(int i = 0; i < (int)pt1.m_ParaList.size(); i++)
	{
		bRet = (pt1.m_ParaList[i] == pt2.m_ParaList[i]);
		if(!bRet)
			return bRet;
	}

	return bRet;
}

bool operator < (const CVSB_FnParamPattern& pt1, const CVSB_FnParamPattern& pt2)
{
	bool bRet = true;

	bRet = (pt1.m_szFunc < pt2.m_szFunc);
	if(bRet)
		return bRet;

	if(!bRet && pt1.m_szFunc == pt2.m_szFunc)
	{
		bRet = ((int)pt1.m_ParaList.size() < (int)pt2.m_ParaList.size());
	}
	else
	{
		return bRet;
	}

	if(bRet)
		return bRet;

	if(!bRet && ((int)pt1.m_ParaList.size() != (int)pt2.m_ParaList.size()))
		return bRet;

	for(int i = 0; i < (int)pt1.m_ParaList.size(); i++)
	{
		bRet = (pt1.m_ParaList[i] < pt2.m_ParaList[i]);
		if(bRet)
			return bRet;

		if(!bRet && pt1.m_ParaList[i] != pt2.m_ParaList[i])
			return bRet;
	}

	return bRet;
}

bool operator <= (const CVSB_FnParamPattern& pt1, const CVSB_FnParamPattern& pt2)
{
	bool bRet = true;

	bRet = (pt1.m_szFunc <= pt2.m_szFunc);
	if(!bRet)
		return bRet;

	if(bRet && pt1.m_szFunc == pt2.m_szFunc)
	{
		bRet = ((int)pt1.m_ParaList.size() <= (int)pt2.m_ParaList.size());
	}
	else
	{
		return bRet;
	}

	if(!bRet)
		return bRet;

	if(bRet && ((int)pt1.m_ParaList.size() != (int)pt2.m_ParaList.size()))
		return bRet;

	for(int i = 0; i < (int)pt1.m_ParaList.size(); i++)
	{
		bRet = (pt1.m_ParaList[i] <= pt2.m_ParaList[i]);
		if(!bRet)
			return bRet;

		if(bRet && pt1.m_ParaList[i] != pt2.m_ParaList[i])
			return bRet;
	}

	return bRet;
}

bool operator == (const CVSB_FnParamPattern& pt1, const CVSB_FnPattern& pt2)
{
	bool bRet = true;

	bRet = (pt1.m_szFunc == pt2.m_szFunc);
	if(!bRet)
		return bRet;

	bRet = ((int)pt1.m_ParaList.size() == (int)pt2.m_ParaList.size());
	if(!bRet)
		return bRet;

	for(int i = 0; i < (int)pt1.m_ParaList.size(); i++)
	{
		bRet = (pt1.m_ParaList[i] == pt2.m_ParaList[i]);
		if(!bRet)
			return bRet;
	}

	return bRet;
}

bool operator < (const CVSB_FnParamPattern& pt1, const CVSB_FnPattern& pt2)
{
	bool bRet = true;

	bRet = (pt1.m_szFunc < pt2.m_szFunc);
	if(bRet)
		return bRet;

	if(!bRet && pt1.m_szFunc == pt2.m_szFunc)
	{
		bRet = ((int)pt1.m_ParaList.size() < (int)pt2.m_ParaList.size());
	}
	else
	{
		return bRet;
	}

	if(bRet)
		return bRet;

	if(!bRet && ((int)pt1.m_ParaList.size() != (int)pt2.m_ParaList.size()))
		return bRet;

	for(int i = 0; i < (int)pt1.m_ParaList.size(); i++)
	{
		bRet = (pt1.m_ParaList[i] < pt2.m_ParaList[i]);
		if(bRet)
			return bRet;

		if(!bRet && pt1.m_ParaList[i] != pt2.m_ParaList[i])
			return bRet;
	}

	return bRet;
}

bool operator <= (const CVSB_FnParamPattern& pt1, const CVSB_FnPattern& pt2)
{
	bool bRet = true;

	bRet = (pt1.m_szFunc <= pt2.m_szFunc);
	if(!bRet)
		return bRet;

	if(bRet && pt1.m_szFunc == pt2.m_szFunc)
	{
		bRet = ((int)pt1.m_ParaList.size() <= (int)pt2.m_ParaList.size());
	}
	else
	{
		return bRet;
	}

	if(!bRet)
		return bRet;

	if(bRet && ((int)pt1.m_ParaList.size() != (int)pt2.m_ParaList.size()))
		return bRet;

	for(int i = 0; i < (int)pt1.m_ParaList.size(); i++)
	{
		bRet = (pt1.m_ParaList[i] <= pt2.m_ParaList[i]);
		if(!bRet)
			return bRet;

		if(bRet && pt1.m_ParaList[i] != pt2.m_ParaList[i])
			return bRet;
	}

	return bRet;
}