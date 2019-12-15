// Project: Visual System Builder
//
// File Name: xvsb_clsobj.h
//
// Description: The definition of the class object class
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
#ifndef __XVSB_CLSOBJ_H__
#define __XVSB_CLSOBJ_H__

#include "xvsb_pre.h"
#include "xvsb_defs.h"
#include "ivsb_datbas.h"
#include "xvsb_clsfn.h"

class CVSB_ClassUnit;

class XVSB_CLASS CVSB_ClassObject : public IVSB_DataBase
{
public:
	CVSB_ClassObject(void);
	CVSB_ClassObject(CVSB_ClassUnit* pUnit); //
	CVSB_ClassObject(const CVSB_ClassType& clsType, CVSB_ClassUnit* pUnit); //
	CVSB_ClassObject(std::wstring& szNS, std::wstring& szCls, CVSB_ClassUnit* pUnit); //
	CVSB_ClassObject(const wchar_t* szNS, const wchar_t* szCls, CVSB_ClassUnit* pUnit); //
	CVSB_ClassObject(const CVSB_ClassObject& clsobj, CVSB_ClassUnit* pUnit);//
	CVSB_ClassObject(const CVSB_ClassObject& clsobj);
	virtual ~CVSB_ClassObject(void);

public:
    void CleanFuncTable(void);
    void CleanProperty(void);
    void Cleanup(void);

	bool SetNewClassName(std::wstring& szName);
	bool SetNewClassName(const wchar_t* szName);

	bool HasProperty(std::wstring& szName);
	bool HasProperty(const wchar_t* szName);

	IVSB_DataBase* GetProperty(std::wstring& szName);
	IVSB_DataBase* GetProperty(const wchar_t* szName);

	bool AddProperty(std::wstring& szName, IVSB_DataBase* pData);
	bool AddProperty(const wchar_t* szName, IVSB_DataBase* pData);

	bool RemoveProperty(std::wstring& szName);
	bool RemoveProperty(const wchar_t* szName);

	bool HasMethod(std::wstring& szFunc);
	bool HasMethod(const wchar_t* szFunc);
	bool HasMethod(CVSB_FnParamPattern& fpat);
	CVSB_Method* GetMethod(CVSB_FnParamPattern& fpat);
	bool AddMethod(CVSB_FnParamPattern& fpat, CVSB_Method* pFn);
	bool RemoveMethod(CVSB_FnParamPattern& fpat);
	bool EraseMethod(CVSB_FnParamPattern& fpat);

	bool HasMethod(CVSB_FnPattern& fpat);
	CVSB_Method* GetMethod(CVSB_FnPattern& fpat);
	bool AddMethod(CVSB_FnPattern& fpat, CVSB_Method* pFn);
	bool RemoveMethod(CVSB_FnPattern& fpat);
	bool EraseMethod(CVSB_FnPattern& fpat);


	CVSB_ClassObject& operator = (const CVSB_ClassObject& clsobj);


	//@cmember  Check built-in data type
	virtual bool IsBuiltInType(void){return false;}

	//@cmember  Check class data type
	virtual bool IsClassType(void){return true;}

	virtual bool Clone(IVSB_Base** ppObj);
	virtual bool Clone(IVSB_Base** ppObj, const std::wstring& szName);
	virtual bool Clone(IVSB_Base** ppObj, const wchar_t* szName);

	//@cmember  Assignment ("=")
	virtual bool Assign(IVSB_DataBase* pData);

	//@cmember  Assignment ("=")
	virtual bool AssignDefault(IVSB_DataBase* pData);

	//@cmember  Logical Comparsion
	virtual bool Compare(IVSB_DataBase* pObj, enXVSB_CMPTYPE cmp); 

	//@cmember  Get data type index
	virtual int GetDataTypeIndex(void); 

	//@cmember  Get data type presentation string
	virtual const wchar_t* GetDataTypeStr(void) const; 

	//@cmember  Get data type presentation string
	virtual std::wstring GetDataTypeStr(void); 

	//@cmember  Get class type presentation string
	virtual std::wstring GetClassTypeStr(void); 

	//@cmember  Get data type presentation string
	virtual std::wstring GetDataValueStr(void); 

	//@cmember  Get data type presentation string
	virtual const wchar_t* GetDataValueStr(void) const; 

	//@cmember  Get data type presentation string
	virtual std::wstring GetDefaultValueStr(void); 

	//@cmember  Get data type presentation string
	virtual const wchar_t* GetDefaultValueStr(void) const; 

	//@cmember  Reset data to default
	virtual void Reset(void);

	//@cmember  Create Ancestor
	virtual void CreateAncestor(const CVSB_ClassType& clsType);

	//@cmember  Create Ancestor
	virtual void CreateAncestor(CVSB_ClassObject* pCls);

	//@cmember  Create Ancestor
	virtual void AttachAncestor(CVSB_ClassObject* pCls);

	//@cmember  Remove Ancestor
	virtual void RemoveAncestor(void);

	//@cmember  Check the confliction with Ancestor
	virtual bool CheckAncestorConflict(void);

	//@cmember  Check Ancestor class type
	virtual CVSB_ClassType GetClassAnchesterType(void);

	//@cmember  Assing Unit
	virtual void SetClassUnit(CVSB_ClassUnit* pClsUnit){m_ClassUnit = pClsUnit;}

	//@cmember  Create Unsed class type
	CVSB_ClassObject* DuplicateUseClass(const CVSB_ClassType& clsType);

	//@cmember  Create Unsed class type
	CVSB_ClassObject* DuplicateUseClass(CVSB_ParamType& paraType);

	//@cmember  Query Unsed class object reference 
	CVSB_ClassObject* QueryClassReference(const CVSB_ClassType& clsType);

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

	//@cmember  Check the class type is used or not
	bool IsCirclurClassType(CVSB_ClassType clstype);

public:
	CVSB_MethodTable	m_FuncTable;	
	IVSB_DataTable		m_PropertyList;

	CVSB_ClassObject*	m_Ancestor;	

	CVSB_ClassUnit*		m_ClassUnit;	

private:
	mutable std::wstring m_szClassType;
};

#endif