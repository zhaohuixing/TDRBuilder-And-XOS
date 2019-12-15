// Project: Visual System Builder
//
// File Name: xvsb_clsunit.h
//
// Description: The definition of the class object wraper class
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 05/10/2005	
//
// History:
// 1.    05/10/2005: Create	
//
#ifndef __XVSB_CLSUNIT_H__
#define __XVSB_CLSUNIT_H__

#include "xvsb_pre.h"
#include "xvsb_defs.h"
#include "ivsb_datbas.h"
#include "xvsb_clsfn.h"
#include "xvsb_clsobj.h"
#include "tvsb_cpputil.h"
#include "xvsb_strutil.h"
#include "xvsb_clstype.h"
#include <vector>
#include <map>
#include <string>

class XVSB_CLASS IVSB_CUFileHandler;
class XVSB_CLASS CVSB_Namespace;

typedef std::map<std::wstring, CVSB_Namespace*>					CVSB_NSpaceLUT;
typedef TVSB_PairDeletor<CVSB_NSpaceLUT::value_type>			CVSB_NSpaceLUTDelete;
typedef TVSB_Dealloc<CVSB_NSpaceLUT, CVSB_NSpaceLUTDelete>	    CVSB_NSpaceLUTFree;

class XVSB_CLASS CVSB_ClassUnit
{
public:

public:
	CVSB_ClassUnit(CVSB_Namespace* pNS);
	CVSB_ClassUnit(CVSB_Namespace* pNS, std::wstring& szClass);
	CVSB_ClassUnit(CVSB_Namespace* pNS, const wchar_t* szClass);
	CVSB_ClassUnit(CVSB_Namespace* pNS, const CVSB_ClassType& clstype);
	virtual ~CVSB_ClassUnit(void);


public:
	CVSB_ClassObject* GetClassObject(void){return m_pClass;}

	bool IsUseClass(const CVSB_ClassType& clsType);
	CVSB_ClassObject* DuplicateUseClass(const CVSB_ClassType& clsType);

	CVSB_ClassObject* DuplicateClass(const CVSB_ClassType& clsType);

	CVSB_ClassObject* QueryUseClassReference(const CVSB_ClassType& clsType);
	CVSB_ClassObject* QueryClassReference(const CVSB_ClassType& clsType);

	std::wstring GetClassName(void);

	bool SetNewClassName(std::wstring& szName);
	bool SetNewClassName(const wchar_t* szName);

	CVSB_ClassType GetClassAnchesterType(void);
	CVSB_ClassType GetClassType(void);
/*
	void AddUnitPath(std::wstring& szfile, std::wstring& szPath);
	void AddUnitPath(const wchar_t* szfile, const wchar_t* szPath);

	void AddUseUnit(CVSB_ClassUnit* pUnit);

	bool LoadUseUnits(IVSB_CUFileHandler* pLoader);
*/

public:
	_eq_pairlist		m_UUFilelist;	//Used class unit path information, first: class/file name
										//second: directory name, can be empty 	
	CVSB_ClassObject*   m_pClass;

	CVSB_Namespace*		m_pNamespace;

	CVSB_NSpaceLUT		m_UseNSLut;
};

typedef std::map<CVSB_ClassType, CVSB_ClassUnit*>				CVSB_ClassUnitList;
typedef TVSB_PairDeletor<CVSB_ClassUnitList::value_type>		CVSB_ClassUnitDelete;
typedef TVSB_Dealloc<CVSB_ClassUnitList, CVSB_ClassUnitDelete>	CVSB_ClassUnitFree;

#endif