// Project: Visual System Builder
//
// File Name: xvsb_fpara.h
//
// Description: The definition of the class member function parameter object
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
#ifndef __XVSB_FPARA_H__
#define __XVSB_FPARA_H__

#include "xvsb_pre.h"
#include "xvsb_defs.h"
#include "ivsb_datbas.h"
#include "xvsb_paratype.h"
#include <vector>

class XVSB_CLASS CVSB_FnParam
{
public:
	CVSB_FnParam(void);
	CVSB_FnParam(std::wstring& szPName, CVSB_ParamType& parType);
	CVSB_FnParam(const wchar_t* szPName, CVSB_ParamType& parType);
	CVSB_FnParam(std::wstring& szPName, CVSB_ClassType& clsType);
	CVSB_FnParam(const wchar_t* szPName, CVSB_ClassType& clsType);
	CVSB_FnParam(const CVSB_FnParam& para);
	
	virtual ~CVSB_FnParam(void);

public:
	void Reset(void);

	std::wstring GetName(void) {return m_parName;}
	const wchar_t* GetName(void) const {return m_parName.c_str();}

	void SetName(std::wstring szPName) {m_parName = szPName;}
	void SetName(const wchar_t* szPName) {m_parName = szPName;}

	CVSB_ParamType GetType(void) const {return m_parType;}
	void SetType(CVSB_ParamType pType) {m_parType = pType;}

	CVSB_ClassType GetClassType(void) {return m_parType.GetClassType();}

	bool AttachData(IVSB_DataBase* pData);

	CVSB_FnParam& operator = (const CVSB_FnParam& para);

	IVSB_DataBase* GetParamObject(void){return m_pData;}

public:
	IVSB_DataBase*		m_pData;
	std::wstring		m_parName;
	CVSB_ParamType		m_parType;
};

typedef std::vector<CVSB_FnParam> CVSB_CFnParamList; 


#endif