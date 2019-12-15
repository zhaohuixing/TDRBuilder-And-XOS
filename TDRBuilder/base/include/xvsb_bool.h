// Project: Visual System Builder
//
// File Name: xvsb_bool.h
//
// Description: The definition of the boolean data type
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
#ifndef __XVSB_BOOL_H__
#define __XVSB_BOOL_H__

#include "ivsb_datbas.h"
#include "xvsb_pre.h"

class XVSB_CLASS CVSB_Bool : public IVSB_DataBase
{
//
// @access Constructor/Destructor
//
public:
	//@cmember Constructor
	CVSB_Bool(void);

	//@cmember Constructor
	CVSB_Bool(const wchar_t* szName);

	//@cmember Constructor
	CVSB_Bool(const std::wstring& szName);

	//@cmember Copy Constructor
	CVSB_Bool(const CVSB_Bool& n);

	//@cmember Copy Constructor
	CVSB_Bool(const CVSB_Bool& n, const wchar_t* szName);

	//@cmember Copy Constructor
	CVSB_Bool(const CVSB_Bool& n, const std::wstring& szName);
	
	//@cmember Constructor
	CVSB_Bool(bool b);

	//@cmember Constructor
	CVSB_Bool(bool b, const wchar_t* szName);

	//@cmember Constructor
	CVSB_Bool(bool b, const std::wstring& szName);

	//@cmember Destructor
	virtual ~CVSB_Bool(void);

//
// @access Operations
//
public:
	//@cmember Convert to double
	operator double (void);

	//@cmember Convert to long
	operator long (void);

	//@cmember Convert to int
	operator int (void);

	//@cmember Convert to int
	operator __int64 (void);

	//@cmember Convert to wchar_t
	operator wchar_t (void);

	//@cmember Convert to unsigned char
	operator unsigned char (void);

	//@cmember Convert to bool
	operator bool (void);

	//@cmember Assignment
	CVSB_Bool& operator = (const CVSB_Bool& data);	
	
	//@cmember Assignment
	CVSB_Bool& operator = (double dv);

	//@cmember Assignment
	CVSB_Bool& operator = (long nv);

	//@cmember Assignment
	CVSB_Bool& operator = (int nv);

	//@cmember Assignment
	CVSB_Bool& operator = (__int64 nv);

	//@cmember Assignment
	CVSB_Bool& operator = (unsigned char nv);

	//@cmember Assignment
	CVSB_Bool& operator = (wchar_t nv);

	//@cmember Assignment
	CVSB_Bool& operator = (bool b);

//
// @access Operation
//
public:
	//@cmember Get the float value
	bool GetValue(void) const;

	//@cmember Set value
	bool Set(IVSB_DataBase* pObj);

	//@cmember Set value
	void Set(const CVSB_Bool& nData);

	//@cmember Set value
	void Set(bool nVal);

	//@cmember Get Value
	void Get(CVSB_Bool& nData);

	//@cmember Get Value
	void Get(bool& nVal);

	//@cmember Comparsion
	bool IsEqual(const CVSB_Bool& n);

//
// @access Operation
//
public:
	//@cmember  Assignment ("=")
	virtual bool Assign(IVSB_DataBase* pData);

	//@cmember  Assignment ("=")
	virtual bool AssignDefault(IVSB_DataBase* pData);

	//@cmember  Logical Comparsion
	virtual bool Compare(IVSB_DataBase* pObj, enXVSB_CMPTYPE cmp); 

	//@cmember  Clone the object
	virtual bool Clone(IVSB_Base** ppObj);

	//@cmember  Clone the object
	virtual bool Clone(IVSB_Base** ppObj, const std::wstring& szName);

	//@cmember  Clone the object
	virtual bool Clone(IVSB_Base** ppObj, const wchar_t* szName);

	//@cmember  bitwise-AND 	 ("&")
	virtual bool And(IVSB_DataBase* d, IVSB_DataBase** pOut);

	//@cmember  bitwise-exclusive-OR  ("^")
	virtual bool ExOR(IVSB_DataBase* d, IVSB_DataBase** pOut);

	//@cmember  bitwise-inclusive-OR  ("|")
	virtual bool InOR(IVSB_DataBase* d, IVSB_DataBase** pOut);

	//@cmember  Complement ("~")
	virtual bool Not(IVSB_DataBase** pOut);

	//@cmember  Negative ("-")
	virtual bool Negative(IVSB_DataBase** pOut);

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

	//@cmember  Get data type presentation string
	virtual std::wstring GetDefaultValueStr(void); 

	//@cmember  Get data type presentation string
	virtual const wchar_t* GetDefaultValueStr(void) const; 

	//@cmember  Reset data to default
	virtual void Reset(void);

	//@cmember Get the char default value
	bool GetDefaultValue(void) const;

	//@cmember Get default value
	void SetDefault(bool bVal);

//
// @access Operations (friend function)
//
public:
	//@cfunction Equal to
	friend bool operator == (const CVSB_Bool& d1, const CVSB_Bool& d2);

	//@cfunction Not equal to
	friend bool operator != (const CVSB_Bool& d1, const CVSB_Bool& d2);

	//@cfunction Equal to
	friend bool operator == (const CVSB_Bool& d1, bool d2);

	//@cfunction Not equal to
	friend bool operator != (const CVSB_Bool& d1, bool d2);

	//@cfunction Equal to
	friend bool operator == (bool d1, const CVSB_Bool& d2);

	//@cfunction Not equal to
	friend bool operator != (bool d1, const CVSB_Bool& d2);

//
// @access Attributions
//
private:
	//@cmember The bool data 
	bool			m_bBool;	

	//@cmember The bool default data 
	bool			m_bDefault;	
};

#endif