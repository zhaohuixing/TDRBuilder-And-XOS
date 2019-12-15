// Project: Visual System Builder
//
// File Name: xvsb_factry.h
//
// Description: The definitions of the object creation factory classes
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
#ifndef __XVSB_FACTRY_H__
#define __XVSB_FACTRY_H__

#include "ivsb_datbas.h"
#include "xvsb_pre.h"
#include <string>

class XVSB_CLASS CVSB_DataFactory
{
//
// @access Constructor/Destructor:
//
public:
	//@cmember Constructor
	CVSB_DataFactory(const CVSB_ClassType& type);

	//@cmember Constructor
	CVSB_DataFactory(const CVSB_ClassType& type, const std::wstring& name);

	//@cmember Constructor
	CVSB_DataFactory(const CVSB_ClassType& type, const wchar_t* name);

	//@cmember Constructor
	CVSB_DataFactory(int nTypeID, const std::wstring& name);

	//@cmember Constructor
	CVSB_DataFactory(int nTypeID, const wchar_t* name);

//
// @access Operations:
//
public:
	//@cmember Overload the function operator
	IVSB_DataBase* operator ()(void);

	//@cmember Overload the function operator
	IVSB_DataBase* operator ()(const std::wstring& szDefVal);

	//@cmember Overload the function operator to generator a array object
	IVSB_DataBase* operator ()(int nSize);

	//@cmember Query build in type information
	static CVSB_ClassType GetBuildInType(int nTypeID);

	//@cmember Query build in type information
	static std::wstring GetBuildInTypeString(const CVSB_ClassType& cType);

	//@cmember Query build in type information
	static int GetBuildInTypeIndex(const CVSB_ClassType& cType);

//
//@access Attributes:
//
private:
	//@cmember The object type	
	CVSB_ClassType		m_Type;

	//@cmember The object name	
	std::wstring		m_Name;

};

#endif
