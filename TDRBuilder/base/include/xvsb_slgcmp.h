// Project: Visual System Builder
//
// File Name: xvsb_slgcmp.h
//
// Description: The definition of the simple comparsion class
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
#ifndef __XVSB_SLGCMP_H__
#define __XVSB_SLGCMP_H__

#include "ivsb_lgcmp.h"
#include "xvsb_pre.h"
#include "xvsb_para.h"

class XVSB_CLASS CVSB_SimpleCompare : public IVSB_LogicCompare
{
//
// @access Constructor/Destructor
//
public:
	//@cmember Constructor
	CVSB_SimpleCompare(void);

	//@cmember Constructor
	CVSB_SimpleCompare(CVSB_OwnerBase* pOwner, enXVSB_CMPTYPE lgCmp, enXVSB_LGLINK lgLink);

	//@cmember Constructor
	CVSB_SimpleCompare(CVSB_OwnerBase* pOwner, enXVSB_CMPTYPE lgCmp, enXVSB_LGLINK lgLink, const std::wstring& szLeft, const std::wstring& szRight);

	//@cmember Copy Constructor
	CVSB_SimpleCompare(const CVSB_SimpleCompare& sCmp);

	//@cmember Destructor
	~CVSB_SimpleCompare(void);


//
// @access Operations:
//
public:
	//@cmember Start up
	virtual bool Startup(void);

	//@cmember Run
	virtual bool Run(void);

	//@cmember Shut down
	virtual bool Shutdown(void);

	//@cmember Set left variable string
	virtual void SetLeftVar(const std::wstring&	szStr);	

	//@cmember Set left variable string
	virtual void SetLeftVar(const wchar_t*	szStr);	

	//@cmember Set right variable string
	virtual void SetRightVar(const std::wstring& szStr);	

	//@cmember Set right variable string
	virtual void SetRightVar(const wchar_t*	szStr);	

	//@cmember Get left variable string
	virtual std::wstring GetLeftVar(void);	

	//@cmember Get left variable string
	virtual const wchar_t* GetLeftVar(void) const;	

	//@cmember Get right variable string
	virtual std::wstring GetRightVar(void);	

	//@cmember Get right variable string
	virtual const wchar_t* GetRightVar(void) const;	

	//@cmember Clean variable
	virtual void Reset(void);

	//@cmember Clone a copy of the comparsion object
	virtual bool Clone(IVSB_LogicCompare** ppCmp);

	//@cmember Get comparsion string
	virtual std::wstring GetCMPStr(void);

//
// @access Operations:
//
private:
	//@cmember parse out the left variable
	bool _processlvar(void);

	//@cmember parse out the right variable
	bool _processrvar(void);

	//@cmember attach the left variable with the object
	bool _attachlvar(void);

	//@cmember attach the right variable with the object
	bool _attachrvar(void);

//
// @access Attributes:
//
protected:
	//@cmember Left variable string
	std::wstring			m_LVarStr;	

	//@cmember Left variable object
	CVSB_Parameter			m_LVarObj;	

	//@cmember Right variable string
	std::wstring			m_RVarStr;	

	//@cmember Right variable object
	CVSB_Parameter			m_RVarObj;	
};

class CVSB_SimpleCMPParse
{
public:
	IVSB_LgCmpArray		m_CMPlist;

	CVSB_SimpleCMPParse(CVSB_OwnerBase* pOwner){m_CMPlist.clear(); m_pOwner = pOwner;}
	~CVSB_SimpleCMPParse(){m_CMPlist.clear(); m_pOwner = NULL;}

	bool operator ()(const std::wstring& szCMP);

private:
	CVSB_SimpleCompare* _createcomparsion(const std::wstring& szCMP, enXVSB_LGLINK lgLink);
private:
	CVSB_OwnerBase*		m_pOwner;
};

#endif
