// Project: Visual System Builder
//
// File Name: xvsb_vartbl.h
//
// Description: The definition of the variable table for process
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/19/2005	
//
// History:
// 1.    01/19/2005: Create	
//
#ifndef __XVSB_VARTBL_H__
#define __XVSB_VARTBL_H__

#include "ivsb_datbas.h"
#include "tvsb_cpputil.h"
#include "xvsb_pre.h"
#include <string>
#include <map>
#include <assert.h>
#include "xvsb_strutil.h"


typedef std::multimap<CVSB_ClassType, std::wstring>							CVSB_VarLUTable;
typedef TVSB_SimplePairEqual1<CVSB_VarLUTable::value_type, CVSB_ClassType>	CVSB_VarLUTFind1;
typedef TVSB_SimplePairEqual2<CVSB_VarLUTable::value_type, std::wstring>	CVSB_VarLUTFind2;
typedef TVSB_Find<CVSB_VarLUTable, CVSB_VarLUTable::iterator, std::wstring, CVSB_VarLUTFind2>		CVSB_VLFindName;
typedef TVSB_Find<CVSB_VarLUTable, CVSB_VarLUTable::iterator, CVSB_ClassType, CVSB_VarLUTFind1>		CVSB_VLFindType;


typedef std::map<std::wstring, IVSB_DataBase*, CVSB_StrCmp>	CVSB_VarObjTable;
typedef TVSB_PairDeletor<CVSB_VarObjTable::value_type>		CVSB_VarObjDelete;
typedef TVSB_Dealloc<CVSB_VarObjTable, CVSB_VarObjDelete>	CVSB_VarObjRelease;

class XVSB_CLASS CVSB_VarTable
{
public:
	CVSB_VarTable();
	~CVSB_VarTable();

public:
	bool AddVar(IVSB_DataBase* pVar);
	bool AddVar(IVSB_DataBase* pVar, const std::wstring& name);
	bool AddVar(IVSB_DataBase* pVar, const wchar_t* name);

	bool ReplaceVar(IVSB_DataBase* pVar);
	bool ReplaceVar(IVSB_DataBase* pVar, const std::wstring& name);
	bool ReplaceVar(IVSB_DataBase* pVar, const wchar_t* name);

	IVSB_DataBase* GetVar(const std::wstring& name);
	IVSB_DataBase* GetVar(const wchar_t* name);

	bool HasVar(const std::wstring& name);
	bool HasVar(const wchar_t* name);

	bool RemoveVar(const std::wstring& name);
	bool RemoveVar(const wchar_t* name);

	bool AssignVarValue(const std::wstring& name, IVSB_DataBase* pVal);
	bool AssignVarValue(const wchar_t* name, IVSB_DataBase* pVal);

	bool UpdateExistVar(const std::wstring& oldname, const std::wstring& newname, IVSB_DataBase* pVal);
	bool UpdateExistVar(const wchar_t* oldname, const wchar_t* newname, IVSB_DataBase* pVal);

	// For test purpose
	CVSB_ClassType TestLutName(const std::wstring& name);
	CVSB_ClassType TestLutName(const wchar_t* name);

	void CleanUp(void);

	void ResetVars(void);

	CVSB_VarTable& operator = (const CVSB_VarTable& vt);

	int GetPrintLineCount(void) const;


private:
	bool _checkname(const CVSB_ClassType& type, const std::wstring& name);
	bool _checkname(const std::wstring& name);

	bool _removelutname(const std::wstring& name);

public:
	CVSB_VarLUTable		m_TNLut;
	CVSB_VarObjTable	m_ObjTbl;
};

#endif