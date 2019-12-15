// Project: Visual System Builder
//
// File Name: xvsb_strutil.h
//
// Description: The definition of the utility for string process
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/27/2005	
//
// History:
// 1.    01/27/2005: Create	
//
#ifndef __XVSB_STRUTIL_H__
#define __XVSB_STRUTIL_H__

#include <string>
#include <map>
#include <vector>
#include <ctype.h>
#include "xvsb_defs.h"

// Checking string is decimal integer string 
class CVSB_DISCheck
{
public:
	CVSB_DISCheck(){};

	bool operator () (const std::wstring& szVar);
};

class CVSB_DFSCheck
{
public:
	CVSB_DFSCheck(){};

	bool operator () (const std::wstring& szVar);
};

class CVSB_StrCmp
{
public:
	CVSB_StrCmp(){};

	inline bool operator () (const std::wstring& sz1, const std::wstring& sz2) const
	{
		return (sz1 < sz2);
	}
};

class CVSB_Str2Data
{
public:
	CVSB_Str2Data(){};

	bool operator () (const std::wstring& szVar, int nType, unXVSB_CPDATAVALUE& unData);
};

class CVSB_StrMarker2Fact
{
public:
	CVSB_StrMarker2Fact(){};

	std::wstring operator () (const std::wstring& szSrc);
};

class CVSB_CPPType2XMLType
{
public:
	CVSB_CPPType2XMLType();

	std::wstring operator () (const std::wstring& szCPPType);

private:
	std::map<std::wstring, std::wstring>	m_TypeMap;	
};


class CVSB_VTypeFinder
{
public:
	CVSB_VTypeFinder();

	int operator () (const std::wstring& szVType);

private:
	std::map<std::wstring, int>	m_VTypeLut;
};

typedef std::vector<std::pair<std::wstring, std::wstring> >	_eq_pairlist;

class CVSB_EquaStrParse
{
public:
	CVSB_EquaStrParse();

	bool operator () (const std::wstring& szEquas);

public:
	_eq_pairlist	m_EquasTable;
};


#endif
