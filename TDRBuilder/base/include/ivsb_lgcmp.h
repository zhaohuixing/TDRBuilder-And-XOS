// Project: Visual System Builder
//
// File Name: ivsb_lgcmp.h
//
// Description: The definition of the abstract interface of comparsion unit
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/28/2005	
//
// History:
// 1.    01/28/2005: Create	
//
#ifndef __IVSB_LGCMP_H__
#define __IVSB_LGCMP_H__

#include "xvsb_defs.h"
#include "xvsb_owner.h"
#include "tvsb_cpputil.h"
#include <vector>

class IVSB_LogicCompare  //: public IVSB_Base
{
public:
	IVSB_LogicCompare(void)
	{
		m_bCompare = true;
		m_pOwner = NULL;
		m_lgCmp = enXVSB_EQUAL;
		m_lgLink = enXVSB_LGOR;
		m_errCode = enXVSB_ERRNONE;
	}

	IVSB_LogicCompare(CVSB_OwnerBase* pOwner, enXVSB_CMPTYPE lgCmp, enXVSB_LGLINK lgLink)
	{
		m_bCompare = true;
		m_pOwner = pOwner;
		m_lgCmp = lgCmp;
		m_lgLink = lgLink;
		m_errCode = enXVSB_ERRNONE;
	}

	virtual ~IVSB_LogicCompare(void)
	{
		m_pOwner = NULL;
	}


public:
	//@cmember Convert to double
	operator bool (void){return m_bCompare;}

	operator enXVSB_LGLINK (void){return m_lgLink;}
	
	bool GetResult(void) const {return m_bCompare;}

	enXVSB_CMPTYPE GetCmpType(void) const {return m_lgCmp;}

	enXVSB_LGLINK GetLogicLink(void) const {return m_lgLink;}

	void SetCmpType(enXVSB_CMPTYPE cmptype)
	{
		m_lgCmp = cmptype;
	}

	void SetLogicLink(enXVSB_LGLINK lglink)
	{
		m_lgLink = lglink;
	}

	bool SetOwner(CVSB_OwnerBase* pOwner)
	{
		bool bRet = false;
		
#ifdef _XSVM_DEBUG_
		assert(pOwner != NULL);
#endif

		if(pOwner != NULL)
		{
			m_errCode = enXVSB_ERRNOCONTAINER;
			m_pOwner = pOwner;
			bRet = true;
		}
		return bRet;
	}

	virtual bool Startup(void) = 0;

	virtual bool Run(void) = 0;

	virtual bool Shutdown(void) = 0;

	//@cmember Set left variable string
	virtual void SetLeftVar(const std::wstring&	szStr) = 0;	

	//@cmember Set left variable string
	virtual void SetLeftVar(const wchar_t*	szStr) = 0;	

	//@cmember Set right variable string
	virtual void SetRightVar(const std::wstring& szStr) = 0;	

	//@cmember Set right variable string
	virtual void SetRightVar(const wchar_t*	szStr) = 0;	

	//@cmember Get left variable string
	virtual std::wstring GetLeftVar(void) = 0;	

	//@cmember Get left variable string
	virtual const wchar_t* GetLeftVar(void) const = 0;	

	//@cmember Get right variable string
	virtual std::wstring GetRightVar(void) = 0;	

	//@cmember Get right variable string
	virtual const wchar_t* GetRightVar(void) const = 0;	

	//@cmember Clean variable
	virtual void Reset(void) = 0;

	//@cmember Clone a copy of the comparsion object
	virtual bool Clone(IVSB_LogicCompare** ppCmp) = 0;

	//@cmember Get comparsion string
	virtual std::wstring GetCMPStr(void) = 0;	

	virtual enXVSB_ERRORCODE GetError(void){return m_errCode;}

	//@cmember Query error content information
	virtual std::wstring GetErrorInfo(void){return m_errString;}
	
	//@cmember Query error content information
	virtual const wchar_t* GetErrorInfo(void) const {return m_errString.c_str();}

protected:
	bool					m_bCompare;
	CVSB_OwnerBase*			m_pOwner;
	enXVSB_CMPTYPE			m_lgCmp;
	enXVSB_LGLINK			m_lgLink;

	//@cmember Error code
	enXVSB_ERRORCODE		m_errCode;

	//@cmember Error information string
	mutable std::wstring 	m_errString;

};

typedef std::vector<IVSB_LogicCompare*>							IVSB_LgCmpArray;
typedef TVSB_Deletor<IVSB_LogicCompare>							IVSB_LgCmpArrayDelete;
typedef TVSB_Dealloc<IVSB_LgCmpArray, IVSB_LgCmpArrayDelete>	IVSB_LgCmpArrayFree;


#endif