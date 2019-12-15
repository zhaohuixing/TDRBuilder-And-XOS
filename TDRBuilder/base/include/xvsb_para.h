// Project: Visual System Builder
//
// File Name: xvsb_para.h
//
// Description: The definition of the parameter object for expression
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/20/2005	
//
// History:
// 1.    01/20/2005: Create	
//
#ifndef __XVSB_PARA_H__
#define __XVSB_PARA_H__

#include "xvsb_pre.h"
#include "xvsb_defs.h"
#include "ivsb_datbas.h"

#include "xvsb_bool.h"
#include "xvsb_float.h"
#include "xvsb_int.h"
#include "xvsb_byte.h"
#include "xvsb_char.h"

class XVSB_CLASS CVSB_Parameter
{
public:
	CVSB_Parameter(void);
	CVSB_Parameter(IVSB_DataBase* pData);
	CVSB_Parameter(double d);
	CVSB_Parameter(__int64 n);
	CVSB_Parameter(unsigned char bt);
	CVSB_Parameter(bool b);
	CVSB_Parameter(wchar_t c);
	CVSB_Parameter(const CVSB_Float& d);
	CVSB_Parameter(const CVSB_Integer& n);
	CVSB_Parameter(const CVSB_Byte& bt);
	CVSB_Parameter(const CVSB_Bool& b);
	CVSB_Parameter(const CVSB_Char& c);
	CVSB_Parameter(const std::wstring& szPName); 
	CVSB_Parameter(const std::wstring& szPName, int nIndx);
	CVSB_Parameter(const std::wstring& szPName, const std::wstring& VarIdx);
	CVSB_Parameter(const CVSB_Parameter& para);
	
	virtual ~CVSB_Parameter(void);

public:
	void Reset(void);
	void Set(double d);
	void Set(__int64 n);
	void Set(unsigned char bt);
	void Set(bool b);
	void Set(wchar_t c);
	void Set(const CVSB_Float& d);
	void Set(const CVSB_Integer& n);
	void Set(const CVSB_Byte& bt);
	void Set(const CVSB_Bool& b);
	void Set(const CVSB_Char& c);

	void SetVar(const std::wstring& szPName); 
	void SetVar(const wchar_t* szPName); 
	void SetArrayVar(const std::wstring& szPName);
	void SetArrayVar(const wchar_t* szPName);
	void SetArrayVar(const std::wstring& szPName, int nIndx);
	void SetArrayVar(const wchar_t* szPName, int nIndx);
	void SetArrayVar(const std::wstring& szPName, const std::wstring& VarIdx);
	void SetArrayVar(const std::wstring& szPName, const wchar_t* VarIdx);
	void SetArrayVar(const wchar_t* szPName, const std::wstring& VarIdx);
	void SetArrayVar(const wchar_t* szPName, const wchar_t* VarIdx);


	bool AttachVar(IVSB_DataBase*	pData);

	bool IsConstant(void) const;

	bool IsVariable(void) const;

	bool IsArrayElement(void) const;

	std::wstring GetParamName(void) const;

	IVSB_DataBase* GetParamData(void) const;

	enXVSB_PARATYPE	GetParamType(void) const;

	bool IsParamValid(void) const;
public:
	void CleanArySet(void);

	bool IsVarAryIdx(void) const;

	bool IsConstAryIdx(void) const;

	enXVSB_ARYIDX_TYPE GetAryIdxType(void) const;

	int GetConstAryIdx(void) const;

	std::wstring GetAryIdxVarName(void);

	const wchar_t* GetAryIdxVarName(void) const;

	bool SetConstAryIdx(int n);

	bool SetAryIdxVarName(const std::wstring& name);

	bool SetAryIdxVarName(const wchar_t* name);

	CVSB_Parameter& operator = (const CVSB_Parameter& para);

private:
	IVSB_DataBase*		m_pData;
	enXVSB_PARATYPE		m_parType;
	std::wstring		m_parName;

private:
	enXVSB_ARYIDX_TYPE	m_AIdxType;
	int					m_nAryIdx;
	std::wstring		m_szAryIdxVar;
};

#endif