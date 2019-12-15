/*****************************************************/
// Project: 
//
// File Name: XOS_FnPatrn.h
//
// Description: The function pattern class definition
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
// File Name: xvsb_fpatn.h
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Updated Date: 05/06/2005	
//
// History:
// 1.    05/06/2005: Updated from XOS_FnPatrn.h
//

#pragma warning(disable:4530)
#ifndef __XVSB_FPATN_H__
#define __XVSB_FPATN_H__

#include "xvsb_paratype.h"

class XVSB_CLASS CVSB_FnParamPattern;

class XVSB_CLASS CVSB_FnPattern 
{
public:
	CVSB_FnPattern(void); // Constructor
	CVSB_FnPattern(std::wstring& szFunc); // Constructor
	CVSB_FnPattern(const wchar_t* szFunc); // Constructor
	CVSB_FnPattern(const CVSB_FnPattern& fbPat);
	CVSB_FnPattern(const CVSB_FnParamPattern& fbPat);
	virtual ~CVSB_FnPattern(void); // Destructor

	void Reset(void);

	void AddParameter(const CVSB_ParamType& par);
	void AddParameter(const CVSB_ClassType& par);
	void AddParameter(std::wstring& szNSpace, std::wstring& szType, std::wstring& szClass);
	void AddParameter(const wchar_t* szNSpace, const wchar_t* szType, const wchar_t* szClass);

	void SetReturn(const CVSB_ParamType& par);
	void SetReturn(const CVSB_ClassType& par);
	void SetReturn(std::wstring& szNSpace, std::wstring& szType, std::wstring& szClass);
	void SetReturn(const wchar_t* szNSpace, const wchar_t* szType, const wchar_t* szClass);
	void SetVoidReturn(void);

	void SetFunction(std::wstring& szFunc);
	void SetFunction(const wchar_t* szFunc);

	bool IsValid(void);
	bool IsVoidReturn(void);

	CVSB_ParamType	GetReturn(void){return m_Return;}

	CVSB_FnPattern& operator = (const CVSB_FnPattern& parType);
	CVSB_FnPattern& operator = (const CVSB_FnParamPattern& parType);
	friend bool operator == (const CVSB_FnPattern& pt1, const CVSB_FnPattern& pt2);	
	friend bool operator != (const CVSB_FnPattern& pt1, const CVSB_FnPattern& pt2)
	{
		return !(pt1 == pt2);
	}

	friend bool operator < (const CVSB_FnPattern& pt1, const CVSB_FnPattern& pt2);
	friend bool operator <= (const CVSB_FnPattern& pt1, const CVSB_FnPattern& pt2);
	friend bool operator > (const CVSB_FnPattern& pt1, const CVSB_FnPattern& pt2)
	{
		return (pt2 < pt1);
	}
	friend bool operator >= (const CVSB_FnPattern& pt1, const CVSB_FnPattern& pt2)
	{
		return (pt2 <= pt1);
	}

// Attributions
public:
	CVSB_ParamTypeList		m_ParaList;
	std::wstring			m_szFunc;	

	CVSB_ParamType			m_Return;
};

class XVSB_CLASS CVSB_FnParamPattern
{
public:
	CVSB_FnParamPattern(void); // Constructor
	CVSB_FnParamPattern(std::wstring& szFunc); // Constructor
	CVSB_FnParamPattern(const wchar_t* szFunc); // Constructor
	CVSB_FnParamPattern(const CVSB_FnPattern& fbPat);
	CVSB_FnParamPattern(const CVSB_FnParamPattern& fbPat);
	virtual ~CVSB_FnParamPattern(void); // Destructor

	void Reset(void);

	void AddParameter(const CVSB_ParamType& par);
	void AddParameter(const CVSB_ClassType& par);
	void AddParameter(std::wstring& szNSpace, std::wstring& szType, std::wstring& szClass);
	void AddParameter(const wchar_t* szNSpace, const wchar_t* szType, const wchar_t* szClass);

	void SetFunction(std::wstring& szFunc);
	void SetFunction(const wchar_t* szFunc);

	bool IsValid(void);

	CVSB_FnParamPattern& operator = (const CVSB_FnParamPattern& parType);
	CVSB_FnParamPattern& operator = (const CVSB_FnPattern& parType);
	friend bool operator == (const CVSB_FnParamPattern& pt1, const CVSB_FnParamPattern& pt2);	
	friend bool operator != (const CVSB_FnParamPattern& pt1, const CVSB_FnParamPattern& pt2)
	{
		return !(pt1 == pt2);
	}

	friend bool operator < (const CVSB_FnParamPattern& pt1, const CVSB_FnParamPattern& pt2);
	friend bool operator <= (const CVSB_FnParamPattern& pt1, const CVSB_FnParamPattern& pt2);
	friend bool operator > (const CVSB_FnParamPattern& pt1, const CVSB_FnParamPattern& pt2)
	{
		return (pt2 < pt1);
	}
	friend bool operator >= (const CVSB_FnParamPattern& pt1, const CVSB_FnParamPattern& pt2)
	{
		return (pt2 <= pt1);
	}

	friend bool operator == (const CVSB_FnParamPattern& pt1, const CVSB_FnPattern& pt2);	
	friend bool operator == (const CVSB_FnPattern& pt1, const CVSB_FnParamPattern& pt2)
	{
		return (pt2 == pt1);
	}

	friend bool operator != (const CVSB_FnParamPattern& pt1, const CVSB_FnPattern& pt2)
	{
		return !(pt1 == pt2);
	}
	friend bool operator != (const CVSB_FnPattern& pt1, const CVSB_FnParamPattern& pt2)
	{
		return !(pt1 == pt2);
	}



	friend bool operator < (const CVSB_FnParamPattern& pt1, const CVSB_FnPattern& pt2);
	friend bool operator <= (const CVSB_FnParamPattern& pt1, const CVSB_FnPattern& pt2);
	friend bool operator > (const CVSB_FnParamPattern& pt1, const CVSB_FnPattern& pt2)
	{
		return (pt2 < pt1);
	}
	friend bool operator >= (const CVSB_FnParamPattern& pt1, const CVSB_FnPattern& pt2)
	{
		return (pt2 <= pt1);
	}

	friend bool operator < (const CVSB_FnPattern& pt1, const CVSB_FnParamPattern& pt2)
	{
		return (pt2 > pt1);
	}
	friend bool operator <= (const CVSB_FnPattern& pt1, const CVSB_FnParamPattern& pt2)
	{
		return (pt2 >= pt1);
	}
	friend bool operator > (const CVSB_FnPattern& pt1, const CVSB_FnParamPattern& pt2)
	{
		return (pt2 < pt1);
	}
	friend bool operator >= (const CVSB_FnPattern& pt1, const CVSB_FnParamPattern& pt2)
	{
		return (pt2 <= pt1);
	}

// Attributions
public:
	CVSB_ParamTypeList		m_ParaList;
	std::wstring			m_szFunc;	
};

#endif