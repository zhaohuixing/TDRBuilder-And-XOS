// Project: Visual System Builder
//
// File Name: xvsb_clsfn.h
//
// Description: The definition of the class member function object
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
#ifndef __XVSB_CLSFN_H__
#define __XVSB_CLSFN_H__

#include "xvsb_pre.h"
#include "xvsb_defs.h"
#include "ivsb_datbas.h"
#include "xvsb_paratype.h"
#include "xvsb_fpatn.h"
#include "xvsb_fpara.h"
#include "tvsb_cpputil.h"
#include "ivsb_fnpu.h"
#include "xvsb_fpuentry.h"
#include "xvsb_fpuinit.h"
#include "xvsb_fpuend.h"
#include <string>
#include <vector>
#include <map>

class CVSB_ClassObject;

class XVSB_CLASS CVSB_Method //: public IVSB_Base
{
public:
	CVSB_Method(void);
	CVSB_Method(const CVSB_Method& fn);
	virtual ~CVSB_Method(void);

public:
	bool IsValid(void) {return (m_pOwner == NULL || m_szName.empty());}

	void SetOwner(CVSB_ClassObject*	pOwner){m_pOwner = pOwner;}
	void SetName(std::wstring& szName){m_szName = szName;}
	void SetName(const wchar_t* szName){m_szName = szName;}

	void SetReturn(IVSB_DataBase* pReturn);
	void SetReturn(CVSB_ClassType& Retype);
	void SetReturn(CVSB_ParamType& Retype);
	bool AddParam(CVSB_FnParam fParam);
	bool RemoveParam(std::wstring& szName);
	bool RemoveParam(const wchar_t* szName);

	bool AddLocalVariable(std::wstring& szName, IVSB_DataBase* pData);
	bool AddLocalVariable(const wchar_t* szName, IVSB_DataBase* pData);
	bool RemoveLocalVariable(std::wstring& szName);
	bool RemoveLocalVariable(const wchar_t* szName);

	bool HasVariable(std::wstring& szName);
	bool HasVariable(const wchar_t* szName);

	IVSB_DataBase* GetVariable(std::wstring& szName);
	IVSB_DataBase* GetVariable(const wchar_t* szName);

	CVSB_FnPattern GetFuncPattern(void);
	CVSB_FnParamPattern GeParamPattern(void);

    void CleanParameter(void);
    void CleanDataTable(void);
    void CleanReturn(void);
    void CleanPUMap(void);
    void Cleanup(void);

	bool Clone(CVSB_Method** ppObj);
	bool Clone(CVSB_Method** ppObj, std::wstring& szName);
	bool Clone(CVSB_Method** ppObj, const wchar_t* szName);
	bool Clone(CVSB_Method** ppObj, CVSB_ClassObject* pOwner);
	bool Clone(CVSB_Method** ppObj, CVSB_ClassObject* pOwner, std::wstring& szName);
	bool Clone(CVSB_Method** ppObj, CVSB_ClassObject* pOwner, const wchar_t* szName);

	CVSB_Method& operator = (const CVSB_Method& fn);

	//@cmember Get next avaliable PU ID
	int GetAvaliablePUID(void);

	//@cmember Delete the processor	unit
	bool RemovePU(int puID);

	//@cmember Delete the processor	unit
	IVSB_ClsFnPUBase* QueryPU(int puID);

	//@cmember Check the processor existance
	bool IsPUExist(int puID);

	//@cmember Check the processor type
	enXVSB_PUTYPE GetPUType(int puID);

	//@cmember Add new porcessor 
	bool AddNewPU(IVSB_ClsFnPUBase* pPU);

	//@cmember Add linkage between porcessors
	bool AddLinkage(int nIDFrom, int nIDTo);

	//@cmember Add linkage form logic porcessor Yes node to other processor
	bool AddIfYesLinkage(int nIDFrom, int nIDTo);

	//@cmember Add linkage form logic porcessor No node to other processor
	bool AddIfNoLinkage(int nIDFrom, int nIDTo);

	//@cmember Add linkage between porcessors
	bool RemoveLinkage(int nIDFrom, int nIDTo);

	//@cmember Create parameter reference list
	void CreateParamReference(void);

	//@cmember Clean parameter reference list
	void CleanParamReference(void);

	IVSB_DataBase* GetVarReference(std::wstring& szName);
	IVSB_DataBase* GetVarReference(const wchar_t* szName);

	IVSB_DataBase* GetReturn(void);
	CVSB_ClassType GetReturnClassType(void);
	CVSB_ParamType GetReturnParamType(void);

	CVSB_ClassObject* GetOwner(void){return m_pOwner;}

	bool Run(void);

	//@cmember  Check the attribute name
	bool IsAttribute(std::wstring& szName);

	//@cmember  Check the attribute name
	bool IsAttribute(const wchar_t* szName);

	//@cmember  Check the property attribute
	bool IsPropertyAttribute(std::wstring& szName);

	//@cmember  Check the property attribute
	bool IsPropertyAttribute(const wchar_t* szName);

	//@cmember  Check the property attribute
	bool IsMethodAttribute(std::wstring& szName);

	//@cmember  Check the property attribute
	bool IsMethodAttribute(const wchar_t* szName);

	//@cmember  Check the property class type
	bool IsPropertyBuildInType(std::wstring& szName);

	//@cmember  Check the property class type
	bool IsPropertyBuildInType(const wchar_t* szName);

	//@cmember  Check the property class type
	bool IsPropertyClassType(std::wstring& szName);

	//@cmember  Check the property class type
	bool IsPropertyClassType(const wchar_t* szName);

	//@cmember  Get the property class type
	CVSB_ClassType GetPropertyType(std::wstring& szName);

	//@cmember  Get the property class type
	CVSB_ClassType GetPropertyType(const wchar_t* szName);

public:
	CVSB_ClassObject*	m_pOwner;
	CVSB_CFnParamList	m_ParamList;
	std::wstring		m_szName;
	IVSB_DataTable		m_LocalDataList;
	IVSB_DataBase*		m_pReturn;
	
	CVSB_CFnPUMap		m_PUmap;
	
	//@cmember The start point
	CVSB_FnPUEntry		m_Entry;

	//@cmember The initialization processor
	CVSB_FnPUInit	    m_Initialize;

	//@cmember The exit point
	CVSB_FnPUEnd		m_Exit;

	//@cmember The comment existing flag 
	bool				m_bHasComment;

private:
	//@cmember The paramter reference map for type check
	IVSB_DataTable		m_ParamReferenceMap;

};

//typedef std::map<CVSB_FnPattern, CVSB_Method*> CVSB_MethodTable;  //Key: Function object prototype pattern
typedef std::map<CVSB_FnParamPattern, CVSB_Method*> CVSB_MethodTable;  //Key: Function object prototype pattern
typedef TVSB_PairDeletor<CVSB_MethodTable::value_type> CVSB_MethodTableDelete;
typedef TVSB_Dealloc<CVSB_MethodTable, CVSB_MethodTableDelete> CVSB_MethodTableFree;


#endif