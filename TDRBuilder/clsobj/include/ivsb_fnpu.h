// Project: Visual System Builder
//
// File Name: ivsb_fnpu.h
//
// Description: The definition of the abstract interface of class member function 
//				processor unit
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 05/12/2005	
//
// History:
// 1.    05/12/2005: Create	
//
#ifndef __IVSB_FNPU_H__
#define __IVSB_FNPU_H__

//#include "xvsb_clsfn.h"
#include <vector>
#include <algorithm>
#include <map>
#include "ivsb_callback.h"
#include "ivsb_export.h"
#include "xvsb_defs.h"
#include "tvsb_cpputil.h"

class CVSB_Method;

class IVSB_ClsFnPUBase  // : public IVSB_Base
{
public:
	IVSB_ClsFnPUBase(CVSB_Method* pOwner = NULL, int nID = 0)
	{
		m_pOwner = pOwner; 
		m_puID = nID;
		m_PrevPUlist.clear();
		m_NextPUlist.clear();
		m_szPUName.clear();
		m_pCallBack = NULL;
	}
	virtual ~IVSB_ClsFnPUBase()
	{
		m_pOwner = NULL;
		m_pCallBack = NULL;
	}

public:
	virtual void Attach(CVSB_Method*	pOwner){m_pOwner = pOwner;}
	void Detach(void){m_pOwner = NULL;}
	CVSB_Method* GetOwner(void) const {return m_pOwner;}

	virtual int GetID(void){return m_puID;} 
	virtual void SetID(int nID){m_puID = nID;} 
	virtual bool IsValidID(void){return (m_puID != -1);}

	//@cmember Query error ocde
	enXVSB_ERRORCODE GetError(void) const
	{
		return m_errCode;
	}

	enXVSB_PUTYPE GetPUType(void) const
	{
		return m_PUType;
	}

	std::wstring GetPUName(void)
	{
		return m_szPUName;
	}

	const wchar_t* GetPUName(void) const
	{
		return m_szPUName.c_str();
	}

	virtual void SetPUName(const std::wstring& szName)
	{
		m_szPUName = szName;
	}

	virtual void SetPUName(const wchar_t* szName)
	{
		m_szPUName = szName;
	}

	virtual bool AddPrevPU(int nID)
	{
		bool bRet = false;
		if(nID == -1)
			return bRet;

		CVSB_IDList::iterator iter;
		iter = std::find(m_PrevPUlist.begin(), m_PrevPUlist.end(), nID);
		if(iter == m_PrevPUlist.end())
		{
			m_PrevPUlist.push_back(nID);
		}

		bRet = true;
		return bRet;
	}

	virtual bool RemovePrevPU(int nID)
	{
		bool bRet = true;
		if(nID == -1)
			return bRet;

		CVSB_IDList::iterator iter;
		iter = std::find(m_PrevPUlist.begin(), m_PrevPUlist.end(), nID);
		if(iter != m_PrevPUlist.end())
		{
			m_PrevPUlist.erase(iter);
		}

		bRet = true;
		return bRet;
	}
	
	virtual void CleanAllPrevPU(void)
	{
		m_PrevPUlist.clear();
	}
	
	virtual bool AddNextPU(int nID)
	{
		bool bRet = false;
		if(nID == -1)
			return bRet;

		CVSB_IDList::iterator iter;
		iter = std::find(m_NextPUlist.begin(), m_NextPUlist.end(), nID);
		if(iter == m_NextPUlist.end())
		{
			m_NextPUlist.push_back(nID);
		}

		bRet = true;
		return bRet;
	}
	
	virtual bool RemoveNextPU(int nID)
	{
		bool bRet = true;
		if(nID == -1)
			return bRet;

		CVSB_IDList::iterator iter;
		iter = std::find(m_NextPUlist.begin(), m_NextPUlist.end(), nID);
		if(iter != m_NextPUlist.end())
		{
			m_NextPUlist.erase(iter);
		}

		bRet = true;
		return bRet;
	}

	
	virtual void CleanAllNextPU(void)
	{
		m_NextPUlist.clear();
	}
	
	virtual void CleanAllPU(void)
	{
		m_PrevPUlist.clear();
		m_NextPUlist.clear();
	}

	virtual bool HavePrevPU(void) 
	{
		return !m_PrevPUlist.empty();
	}

	virtual bool HaveNextPU(void) 
	{
		return !m_NextPUlist.empty();
	}

	virtual bool Initialize(void) = 0;
	virtual bool Start(void) = 0;
	virtual bool Run(void) = 0;
	virtual bool Reset(void) = 0;

	virtual bool FirstStepRun(void) = 0;
	virtual bool NextStepRun(void) = 0;
	virtual bool RunRestSteps(void) = 0;
	virtual bool IsStepRunOver(void) = 0;
	virtual bool Clone(IVSB_ClsFnPUBase** ppPU) = 0;

	virtual bool ReSetup(void)
	{
		return true;
	}

	virtual int GetPrevPU(void)
	{
		if(m_PrevPUlist.empty())
			return -1;
		else
			return m_PrevPUlist[0];
	}

	virtual int GetFirstNextPU(void)
	{
		if(m_NextPUlist.empty())
			return -1;
		else
			return m_NextPUlist[0];
	}

	virtual int GetPrevPUCount(void)
	{
		return (int)m_PrevPUlist.size();
	}

	virtual int GetNextPUCount(void)
	{
		return (int)m_NextPUlist.size();
	}

	virtual int GetInnerCount(void)
	{
		return (int)m_NextPUlist.size();
	}

	virtual bool ReplaceNextPU(int nID)
	{
		if(m_NextPUlist.empty())
			return false;
		else
			m_NextPUlist[0] = nID;

		return true;
	}

	virtual void SetCallBack(IVSB_CallBack*	pCallBack)
	{
		m_pCallBack = pCallBack;
	}

	virtual bool Export(CVSB_hFileExport* hExport)
	{
		return true;
	}

	virtual bool Export(CVSB_hFileExport* hExport, std::wstring& szName)
	{
		return true;
	}

	virtual int GetPrintLineCount(void) const
	{
		return 1;
	}

protected:
	CVSB_Method*		m_pOwner;
	
	int					m_puID;

	std::wstring		m_szPUName;

	//@cmember Error code
	enXVSB_ERRORCODE	m_errCode;

	enXVSB_PUTYPE		m_PUType;

	IVSB_CallBack*		m_pCallBack;

public:
	CVSB_IDList			m_PrevPUlist;
	CVSB_IDList			m_NextPUlist;
};

typedef std::map<int, IVSB_ClsFnPUBase*>						CVSB_CFnPUMap;
typedef TVSB_PairDeletor<CVSB_CFnPUMap::value_type>				CVSB_CFnPUMapDelete;
typedef TVSB_Dealloc<CVSB_CFnPUMap, CVSB_CFnPUMapDelete>		CVSB_CFnPUMapFree;

#endif