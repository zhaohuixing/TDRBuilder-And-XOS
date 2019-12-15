/*****************************************************/
// Project: 
//
// File Name: XOS_ParType.h
//
// Description: The parameter type class definition
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
// File Name: xvsb_paratype.h
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Updated Date: 05/05/2005	
//
// History:
// 1.    05/05/2005: Updated from XOS_ParType.h	
//

#pragma warning(disable:4530)
#ifndef __XVSB_PARATYPE_H__
#define __XVSB_PARATYPE_H__

#include <string>
#include <map>
#include <vector>
#include "xvsb_pre.h"
#include "tvsb_cpputil.h"
#include "xvsb_helper.h"
#include "xvsb_clstype.h"
#include "xvsb_defs.h"


class XVSB_CLASS CVSB_ParamType 
{
public:
	CVSB_ParamType(void); // Constructor
	CVSB_ParamType(std::wstring& szNSpace, std::wstring& szType, std::wstring& szClass); // Constructor
	CVSB_ParamType(const wchar_t* szNSpace, const wchar_t* szType, const wchar_t* szClass);
	CVSB_ParamType(const CVSB_ClassType& clsType); // Constructor
	CVSB_ParamType(const CVSB_ParamType& pdes);
	virtual ~CVSB_ParamType(void); // Destructor

	std::wstring& GetNameSpace(void);
	std::wstring& GetType(void);
	std::wstring& GetClass(void);

	const wchar_t* GetNameSpace(void) const;
	const wchar_t* GetType(void) const;
	const wchar_t* GetClass(void) const;

	void SetNameSpace(std::wstring& szNSpace);
	void SetType(std::wstring& szType);
	void SetClass(std::wstring& szClass);

	void SetNameSpace(const wchar_t* szNSpace);
	void SetType(const wchar_t* szType);
	void SetClass(const wchar_t* szClass);

	void Empty(void);

	bool IsEmpty(void) const;

	bool IsVoid(void) const;

	void SetClassType(const CVSB_ClassType& clsType);
	void SetClassType(std::wstring& szNSpace, std::wstring& szType, std::wstring& szClass);
	void SetClassType(const wchar_t* szNSpace, const wchar_t* szType, const wchar_t* szClass);
	CVSB_ClassType GetClassType(void);

	bool IsSameClassType(const CVSB_ClassType& clsType);
	bool IsSameClassType(const CVSB_ParamType& parType);

	//@cmember Type conversion to CVSB_ClassType
	operator CVSB_ClassType (void);

    CVSB_ParamType* Clone(void);

	bool IsBuildInType(void) const; 
	bool IsArrayType(void) const;
	bool IsIntegerType(void) const; 
	bool IsByteType(void) const; 
	bool IsFloatType(void) const; 
	bool IsBoolType(void) const; 
	bool IsCharType(void) const; 
	std::wstring GetClassTypeStr(void);
	std::wstring GetNameSpaceClassString(void);

	CVSB_ParamType& operator = (const CVSB_ParamType& parType);
	friend bool operator == (const CVSB_ParamType& pt1, const CVSB_ParamType& pt2);	
	friend bool operator != (const CVSB_ParamType& pt1, const CVSB_ParamType& pt2);
	friend bool operator < (const CVSB_ParamType& pt1, const CVSB_ParamType& pt2);
	friend bool operator <= (const CVSB_ParamType& pt1, const CVSB_ParamType& pt2);
	friend bool operator > (const CVSB_ParamType& pt1, const CVSB_ParamType& pt2);
	friend bool operator >= (const CVSB_ParamType& pt1, const CVSB_ParamType& pt2);

	CVSB_ParamType& operator = (const CVSB_ClassType& clsType);
	friend bool operator == (const CVSB_ClassType& pt1, const CVSB_ParamType& pt2);	
	friend bool operator != (const CVSB_ClassType& pt1, const CVSB_ParamType& pt2);
	friend bool operator == (const CVSB_ParamType& pt1, const CVSB_ClassType& pt2);	
	friend bool operator != (const CVSB_ParamType& pt1, const CVSB_ClassType& pt2);

// Attributions
public:
	CVSB_ClassType				m_ClsType;
};

typedef std::vector<CVSB_ParamType*>	CVSB_ParamTypeQueue;	
typedef TVSB_Deletor<CVSB_ParamType>	CVSB_ParamTypeDelete;
typedef TVSB_Dealloc<CVSB_ParamTypeQueue, CVSB_ParamTypeDelete> CVSB_ParamTypeFree;

typedef CVSB_ParamTypeQueue::iterator			ptyp_iterator;
typedef CVSB_ParamTypeQueue::const_iterator		ptyp_constiterator;

typedef std::vector<CVSB_ParamType>	CVSB_ParamTypeList;	


#endif