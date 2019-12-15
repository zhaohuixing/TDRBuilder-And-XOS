// Project: Visual System Builder
//
// File Name: xvsb_char.h
//
// Description: The definition of the whcar character (16 bits) data type
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
#ifndef __XVSB_CHAR_H__
#define __XVSB_CHAR_H__

#include "ivsb_datbas.h"
#include "xvsb_pre.h"

class XVSB_CLASS CVSB_Char : public IVSB_DataBase
{
//
// @access Constructor/Destructor
//
public:
	//@cmember Constructor
	CVSB_Char(void);

	//@cmember Constructor
	CVSB_Char(const wchar_t* szName);

	//@cmember Constructor
	CVSB_Char(const std::wstring& szName);

	//@cmember Copy Constructor
	CVSB_Char(const CVSB_Char& n);

	//@cmember Copy Constructor
	CVSB_Char(const CVSB_Char& n, const wchar_t* szName);

	//@cmember Copy Constructor
	CVSB_Char(const CVSB_Char& n, const std::wstring& szName);

	//@cmember Constructor
	CVSB_Char(wchar_t c);

	//@cmember Constructor
	CVSB_Char(wchar_t c, const wchar_t* szName);

	//@cmember Constructor
	CVSB_Char(wchar_t c, const std::wstring& szName);

	//@cmember Destructor
	virtual ~CVSB_Char(void);

//
// @access Operations
//
public:
	//@cmember Convert to double
	operator double (void);

	//@cmember Convert to long
	operator long (void);

	//@cmember Convert to long
	operator int (void);

	//@cmember Convert to long
	operator __int64 (void);

	//@cmember Convert to wchar_t
	operator wchar_t (void);

	//@cmember Convert to unsigned char
	operator unsigned char (void);

	//@cmember Convert to bool
	operator bool (void);

	//@cmember Assignment
	CVSB_Char& operator = (const CVSB_Char& data);	
	
	//@cmember Assignment
	CVSB_Char& operator = (double dv);

	//@cmember Assignment
	CVSB_Char& operator = (long nv);

	//@cmember Assignment
	CVSB_Char& operator = (int nv);

	//@cmember Assignment
	CVSB_Char& operator = (__int64 nv);

	//@cmember Assignment
	CVSB_Char& operator = (unsigned char nv);

	//@cmember Assignment
	CVSB_Char& operator = (wchar_t nv);

	//@cmember Assignment
	CVSB_Char& operator = (bool b);

	//@cmember Increment
	CVSB_Char& operator += (const CVSB_Char& data);

	//@cmember Decrement
	CVSB_Char& operator -= (const CVSB_Char& data);

	//@cmember Increment
	CVSB_Char& operator += (wchar_t nv);

	//@cmember Decrement
	CVSB_Char& operator -= (wchar_t nv);

	//@cmember Prefix incremental
	CVSB_Char& operator ++ (void);

	//@cmember Postfix incremental
	CVSB_Char operator ++ (int);	

	//@cmember Prefix decremental	
	CVSB_Char& operator -- (void);	

	//@cmember Postfix decremental	
	CVSB_Char operator -- (int);	

//
// @access Operation
//
public:
	//@cmember Get the float value
	wchar_t GetValue(void) const;

	//@cmember Set value
	bool Set(IVSB_DataBase* pObj);

	//@cmember Set value
	void Set(const CVSB_Char& nData);

	//@cmember Set value
	void Set(wchar_t nVal);

	//@cmember Get Value
	void Get(CVSB_Char& nData);

	//@cmember Get Value
	void Get(wchar_t& nVal);

	//@cmember Comparsion
	bool IsEqual(const CVSB_Char& n);

	//@cmember Comparsion
	bool IsLarge(const CVSB_Char& n);
	
	//@cmember Comparsion
	bool IsLargeEqual(const CVSB_Char& n);
	
	//@cmember Comparsion
	bool IsSmall(const CVSB_Char& n);
	
	//@cmember Comparsion
	bool IsSmallEqual(const CVSB_Char& n);

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

	//@cmember  Plus	 ("+")
	virtual bool Plus(IVSB_DataBase* d, IVSB_DataBase** pOut);

	//@cmember  Minus	 ("-")
	virtual bool Minus(IVSB_DataBase* d, IVSB_DataBase** pOut);

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
	wchar_t GetDefaultValue(void) const;

	//@cmember Get default value
	void SetDefault(wchar_t nVal);

//
// @access Operations (friend function)
//
public:
	//@cfunction Plus
	friend long operator + (const CVSB_Char& d1, const CVSB_Char& d2);

	//@cfunction Minus
	friend wchar_t operator - (const CVSB_Char& d1, const CVSB_Char& d2);

	//@cfunction Plus
	friend long operator + (const CVSB_Char& d1, wchar_t d2);

	//@cfunction Minus
	friend wchar_t operator - (const CVSB_Char& d1, wchar_t d2);

	//@cfunction Plus
	friend long operator + (wchar_t d1, const CVSB_Char& d2);
	
	//@cfunction Minus
	friend wchar_t operator - (wchar_t d1, const CVSB_Char& d2);

	//@cfunction Equal to
	friend bool operator == (const CVSB_Char& d1, const CVSB_Char& d2);

	//@cfunction Not equal to
	friend bool operator != (const CVSB_Char& d1, const CVSB_Char& d2);

	//@cfunction Comparsion
	friend bool operator < (const CVSB_Char& d1, const CVSB_Char& d2);

	//@cfunction Comparsion
	friend bool operator <= (const CVSB_Char& d1, const CVSB_Char& d2);

	//@cfunction Comparsion
	friend bool operator > (const CVSB_Char& d1, const CVSB_Char& d2);

	//@cfunction Comparsion
	friend bool operator >= (const CVSB_Char& d1, const CVSB_Char& d2);

	//@cfunction Equal to
	friend bool operator == (const CVSB_Char& d1, wchar_t d2);

	//@cfunction Not equal to
	friend bool operator != (const CVSB_Char& d1, wchar_t d2);

	//@cfunction Comparsion
	friend bool operator < (const CVSB_Char& d1, wchar_t d2);

	//@cfunction Comparsion
	friend bool operator <= (const CVSB_Char& d1, wchar_t d2);

	//@cfunction Comparsion
	friend bool operator > (const CVSB_Char& d1, wchar_t d2);

	//@cfunction Comparsion
	friend bool operator >= (const CVSB_Char& d1, wchar_t d2);

	//@cfunction Equal to
	friend bool operator == (wchar_t d1, const CVSB_Char& d2);

	//@cfunction Not equal to
	friend bool operator != (wchar_t d1, const CVSB_Char& d2);

	//@cfunction Comparsion
	friend bool operator < (wchar_t d1, const CVSB_Char& d2);

	//@cfunction Comparsion
	friend bool operator <= (wchar_t d1, const CVSB_Char& d2);

	//@cfunction Comparsion
	friend bool operator > (wchar_t d1, const CVSB_Char& d2);

	//@cfunction Comparsion
	friend bool operator >= (wchar_t d1, const CVSB_Char& d2);

//
// @access Attributions
//
private:
	//@cmember The integer data 
	wchar_t			m_cChar;	

	//@cmember The integer default data 
	wchar_t			m_cDefault;	
};

#endif