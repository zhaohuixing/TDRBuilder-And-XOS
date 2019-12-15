// Project: Visual System Builder
//
// File Name: xvsb_array.h
//
// Description: The definition of the fixed size array
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/21/2005	
//
// History:
// 1.    01/21/2005: Create	
//
#ifndef __XVSB_ARRAY_H__
#define __XVSB_ARRAY_H__

#include "ivsb_datbas.h"
#include "xvsb_pre.h"

class XVSB_CLASS CVSB_Array : public IVSB_DataBase
{
//
//@access Constructions/Destruction:
//
public:
	//@cmember Constructor
	CVSB_Array(CVSB_ClassType elmType, int nSize);

	//@cmember Constructor
	CVSB_Array(CVSB_ClassType elmType, int nSize, const wchar_t* szName);

	//@cmember Constructor
	CVSB_Array(CVSB_ClassType elmType, int nSize, const std::wstring& szName);

	//@cmember Constructor
	CVSB_Array(int nType, int nSize, const wchar_t* szName);

	//@cmember Constructor
	CVSB_Array(int nType, int nSize, const std::wstring& szName);

	//@cmember Constructor
	CVSB_Array(IVSB_DataBase* elmVal, int nSize);

	//@cmember Constructor
	CVSB_Array(IVSB_DataBase* elmVal, int nSize, const wchar_t* szName);

	//@cmember Constructor
	CVSB_Array(IVSB_DataBase* elmVal, int nSize, const std::wstring& szName);

	//@cmember Constructor
	CVSB_Array(IVSB_DataBase* Array[], int nSize, const std::wstring& szName);

	//@cmember Copy constructor
	CVSB_Array(const CVSB_Array& array);

	//@cmember Copy constructor
	CVSB_Array(const CVSB_Array& array, const wchar_t* szName);

	//@cmember Copy constructor
	CVSB_Array(const CVSB_Array& array, const std::wstring& szName);

	//@cmember Destructor
	virtual ~CVSB_Array(void);

	//@cmember  Get data type index
	virtual int GetDataTypeIndex(void); 

	//@cmember  Get data type presentation string
	virtual const wchar_t* GetDataTypeStr(void) const; 

	//@cmember  Get data type presentation string
	virtual std::wstring GetDataTypeStr(void); 

	//@cmember  Get data type presentation string
	virtual std::wstring GetDataValueStr(void); 

	//@cmember  Get data type presentation string
	virtual const wchar_t* GetDataValueStr(void) const; 

	//@cmember  Get data type index
	virtual int GetElementDataTypeIndex(void); 

	//@cmember  Get data type presentation string
	virtual const wchar_t* GetElementDataTypeStr(void) const; 

	//@cmember  Get data type presentation string
	virtual std::wstring GetElementDataTypeStr(void); 

	//@cmember  Get data type presentation string
	virtual std::wstring GetDefaultValueStr(void); 

	//@cmember  Get data type presentation string
	virtual const wchar_t* GetDefaultValueStr(void) const; 

	//@cmember  Reset data to default
	virtual void Reset(void);

//
//@access Operations:
//
public:
	//@cmember Get the element type
	CVSB_ClassType GetElementType(void)	const;
	
	//@cmember Get the array size
	int Size(void) const;

	//@cmember Override operator []
	const IVSB_DataBase* operator [] (int idx) const; 

	////@cmember Override operator []
	IVSB_DataBase* operator [] (int idx);

	//@cmember Query the element at the specified position 
	IVSB_DataBase* At(int idx); 

	//@cmember Query the element at the specified position 
	const IVSB_DataBase* At(int idx) const; 

	//@cmember Query the element at the specified position 
	bool GetAt(int idx, IVSB_DataBase* pElem);

	//@cmember Set the element value at the specified position 
	bool SetAt(int idx, IVSB_DataBase* pElem);

	//@cmember Check array status
	bool IsCorrupt(void) const;

	//@cmember Check array status
	bool IsOK(void) const;

//
//@access Operations:
//
public:
    //@cmember  Clone the object
	virtual bool Clone(IVSB_Base** ppObj);

	//@cmember  Clone the object
	virtual bool Clone(IVSB_Base** ppObj, const std::wstring& szName);

	//@cmember  Clone the object
	virtual bool Clone(IVSB_Base** ppObj, const wchar_t* szName);

	//@cmember  Assignment ("=")
	virtual bool Assign(IVSB_DataBase* pData);

	//@cmember  Assignment ("=")
	virtual bool AssignDefault(IVSB_DataBase* pData);

	//@cmember  Logical Comparsion
	virtual bool Compare(IVSB_DataBase* pObj, enXVSB_CMPTYPE cmp); 

//
//@access Attributes:
//
private:
	//@cmember The array size	
	int				m_nSize;

	//@cmember The array container	
	IVSB_ArrayBase		m_Array;

	//@cmember The array element type	
	CVSB_ClassType		m_elmType;

	//@cmember The array size	
	bool				m_bOK;
};

#endif