// Project: Visual System Builder
//
// File Name: ivsb_fnbase.h
//
// Description: The definition of the class member function object basic unit
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 05/14/2005	
//
// History:
// 1.    05/14/2005: Create	
//
#ifndef __IVSB_FNBASE_H__
#define __IVSB_FNBASE_H__

#include "xvsb_pre.h"
#include <string>
#include "xvsb_clsfn.h"

class XVSB_CLASS IVSB_CFnUnitBase
{
public:
	IVSB_CFnUnitBase(CVSB_Method* hOwner)
	{
		m_hOwner = hOwner;
		m_errCode = enXVSB_ERRNONE;
		m_errString.clear();
	}

	virtual ~IVSB_CFnUnitBase()
	{
		m_hOwner = NULL;
		m_errCode = enXVSB_ERRNONE;
		m_errString.clear();
	}

public:
	//@cmember Clean up
	virtual void Reset(void) = 0;

	//@cmember Clean up
	virtual void CleanAll(void) = 0;

	//@cmember Initialize
	virtual bool Startup(void) = 0;

	//@cmember Initialize
	virtual bool Run(void) = 0;

	//@cmember Initialize
	virtual bool Shutdown(void) = 0;

	//@cmember Attach to the owner
	inline bool SetOwner(CVSB_Method* hOwner)
	{
		bool bRet = false;
		if(hOwner == NULL)
		{
			m_errCode = enXVSB_ERRNOCONTAINER;
			return bRet;
		}

		m_hOwner = hOwner;
		bRet = true;

		return bRet;
	}

	//@cmember Query error ocde
	virtual enXVSB_ERRORCODE GetError(void) const
	{
		return m_errCode;
	}

	//@cmember Query error content information
	virtual std::wstring GetErrorInfo(void)
	{
		return m_errString;
	}
	
	//@cmember Query error content information
	virtual const wchar_t* GetErrorInfo(void) const
	{
		return m_errString.c_str();
	}

public:
	//@cmember Container object
	CVSB_Method*			m_hOwner;

	//@cmember Error code
	enXVSB_ERRORCODE		m_errCode;

	//@cmember Error information string
	mutable std::wstring 	m_errString;
};

typedef std::vector<IVSB_CFnUnitBase*>							CVSB_CFnUnitGroup;
typedef TVSB_Deletor<IVSB_CFnUnitBase>							CVSB_CFnUnitDelete;
typedef TVSB_Dealloc<IVSB_CFnUnitBase, CVSB_CFnUnitDelete>		CVSB_CFnUnitFree;



#endif