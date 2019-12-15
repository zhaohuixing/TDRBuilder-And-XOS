// Project: Visual System Builder
//
// File Name: xvsb_byte.h
//
// Description: The definition of the byte (8 bits) data type
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
#ifndef __XVSB_BYTE_H__
#define __XVSB_BYTE_H__

#include "ivsb_datbas.h"
#include "xvsb_pre.h"

class XVSB_CLASS CVSB_Byte : public IVSB_DataBase
{
//
// @access Constructor/Destructor
//
public:
	//@cmember Constructor
	CVSB_Byte(void);

	//@cmember Constructor
	CVSB_Byte(const wchar_t* szName);

	//@cmember Constructor
	CVSB_Byte(const std::wstring& szName);

	//@cmember Copy Constructor
	CVSB_Byte(const CVSB_Byte& n);

	//@cmember Copy Constructor
	CVSB_Byte(const CVSB_Byte& n, const wchar_t* szName);

	//@cmember Copy Constructor
	CVSB_Byte(const CVSB_Byte& n, const std::wstring& szName);

	//@cmember Constructor
	CVSB_Byte(unsigned char n);

	//@cmember Constructor
	CVSB_Byte(unsigned char n, const wchar_t* szName);

	//@cmember Constructor
	CVSB_Byte(unsigned char n, const std::wstring& szName);

	//@cmember Destructor
	virtual ~CVSB_Byte(void);

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

	//@cmember Convert to unsigned char
	operator unsigned char (void);

	//@cmember Convert to char
	operator wchar_t (void);

	//@cmember Convert to bool
	operator bool (void);

	//@cmember Assignment
	CVSB_Byte& operator = (const CVSB_Byte& data);	
	
	//@cmember Assignment
	CVSB_Byte& operator = (double dv);

	//@cmember Assignment
	CVSB_Byte& operator = (long nv);

	//@cmember Assignment
	CVSB_Byte& operator = (int nv);

	//@cmember Assignment
	CVSB_Byte& operator = (__int64 nv);

	//@cmember Assignment
	CVSB_Byte& operator = (unsigned char nv);

	//@cmember Assignment
	CVSB_Byte& operator = (wchar_t nv);

	//@cmember Assignment
	CVSB_Byte& operator = (bool b);

	//@cmember Increment
	CVSB_Byte& operator += (const CVSB_Byte& data);

	//@cmember Decrement
	CVSB_Byte& operator -= (const CVSB_Byte& data);

	//@cmember Multipile
	CVSB_Byte& operator *= (const CVSB_Byte& data);

	//@cmember Divide
	CVSB_Byte& operator /= (const CVSB_Byte& data);

	//@cmember Increment
	CVSB_Byte& operator += (unsigned char nv);

	//@cmember Decrement
	CVSB_Byte& operator -= (unsigned char nv);

	//@cmember Multipile
	CVSB_Byte& operator *= (unsigned char nv);

	//@cmember Divide
	CVSB_Byte& operator /= (unsigned char nv);

	//@cmember Prefix incremental
	CVSB_Byte& operator ++ (void);

	//@cmember Postfix incremental
	CVSB_Byte operator ++ (int);	

	//@cmember Prefix decremental	
	CVSB_Byte& operator -- (void);	

	//@cmember Postfix decremental	
	CVSB_Byte operator -- (int);	

//
// @access Operation
//
public:
	//@cmember Get the float value
	unsigned char GetValue(void) const;

	//@cmember Set value
	bool Set(IVSB_DataBase* pObj);

	//@cmember Set value
	void Set(const CVSB_Byte& nData);

	//@cmember Set value
	void Set(unsigned char nVal);

	//@cmember Get Value
	void Get(CVSB_Byte& nData);

	//@cmember Get Value
	void Get(unsigned char& nVal);

	//@cmember Comparsion
	bool IsEqual(const CVSB_Byte& n);

	//@cmember Comparsion
	bool IsLarge(const CVSB_Byte& n);
	
	//@cmember Comparsion
	bool IsLargeEqual(const CVSB_Byte& n);
	
	//@cmember Comparsion
	bool IsSmall(const CVSB_Byte& n);
	
	//@cmember Comparsion
	bool IsSmallEqual(const CVSB_Byte& n);

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

	//@cmember  Hypotenuse 
	virtual bool Hypot(IVSB_DataBase* d, IVSB_DataBase** pOut);

	//@cmember  Absolute value  
	virtual bool Abs(IVSB_DataBase** pOut);

	//@cmember  Argument
	virtual bool Arg(IVSB_DataBase** pOut);

	//@cmember  Polar form of the complex number 
	virtual bool Polar(IVSB_DataBase** pOut);

	//@cmember  Sine
	virtual bool Sin(IVSB_DataBase** pOut);

	//@cmember  Hyperbolic Sine
	virtual bool SinH(IVSB_DataBase** pOut);

	//@cmember  Cosine
	virtual bool Cos(IVSB_DataBase** pOut);

	//@cmember  Hyperbolic Cosine
	virtual bool CosH(IVSB_DataBase** pOut);

	//@cmember  Tangent
	virtual bool Tan(IVSB_DataBase** pOut);

	//@cmember  Hyperbolic Tangent
	virtual bool TanH(IVSB_DataBase** pOut);

	//@cmember  Cotangent
	virtual bool CTan(IVSB_DataBase** pOut);

	//@cmember  Hyperbolic Cotangent
	virtual bool CTanH(IVSB_DataBase** pOut);

	//@cmember  Secant
	virtual bool Sec(IVSB_DataBase** pOut);

	//@cmember  Hyperbolic Secant
	virtual bool SecH(IVSB_DataBase** pOut);

	//@cmember  CoSecant
	virtual bool Csc(IVSB_DataBase** pOut);

	//@cmember  Hyperbolic CoSecant
	virtual bool CscH(IVSB_DataBase** pOut);

	//@cmember  ArcSine
	virtual bool ASin(IVSB_DataBase** pOut);

	//@cmember  ArcCosine
	virtual bool ACos(IVSB_DataBase** pOut);

	//@cmember  ArcTangent
	virtual bool ATan(IVSB_DataBase** pOut);

	//@cmember  ArcCoTangent
	virtual bool ACTan(IVSB_DataBase** pOut);

	//@cmember  Square root
	virtual bool Sqrt(IVSB_DataBase** pOut);

	//@cmember  Exponential 
	virtual bool Exp(IVSB_DataBase** pOut);

	//@cmember  Natural Logarithm (base e) 
	virtual bool Ln(IVSB_DataBase** pOut);

	//@cmember  Common Logarithm (base 10) 
	virtual bool Log10(IVSB_DataBase** pOut);

	//@cmember  Common Logarithm
	virtual bool Log(IVSB_DataBase* d, IVSB_DataBase** pOut);

	//@cmember  Power
	virtual bool Pow(IVSB_DataBase* d, IVSB_DataBase** pOut);

	//@cmember  Power
	virtual bool Root(IVSB_DataBase* d, IVSB_DataBase** pOut);

	//@cmember  Factorial  ("n!")
	virtual bool Factorial(IVSB_DataBase** pOut);

	//@cmember  Plus	 ("+")
	virtual bool Plus(IVSB_DataBase* d, IVSB_DataBase** pOut);

	//@cmember  Minus	 ("-")
	virtual bool Minus(IVSB_DataBase* d, IVSB_DataBase** pOut);

	//@cmember  Time	 ("*")
	virtual bool Time(IVSB_DataBase* d, IVSB_DataBase** pOut);

	//@cmember  Divide	 ("/")
	virtual bool Divide(IVSB_DataBase* d, IVSB_DataBase** pOut);

	//@cmember  Modulus  
	virtual bool Mod2(IVSB_DataBase* d, IVSB_DataBase** pOut);

	//@cmember  Modulus  
	virtual bool Mod(IVSB_DataBase** pOut);

	//@cmember  Fraction  
	virtual bool Fraction(IVSB_DataBase** pOut);

	//@cmember  The left part after Modulus  
	virtual bool FMod(IVSB_DataBase* d, IVSB_DataBase** pOut);

	//@cmember  The left remainding after Modulus  
	virtual bool FMod2(IVSB_DataBase* d, IVSB_DataBase** pOut);

	//@cmember  Left Shift	 ("<<")
	virtual bool LShift(IVSB_DataBase* d, IVSB_DataBase** pOut);

	//@cmember  Right Shift	 (">>")
	virtual bool RShift(IVSB_DataBase* d, IVSB_DataBase** pOut);

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
	unsigned char GetDefaultValue(void) const;

	//@cmember Get default value
	void SetDefault(unsigned char nVal);

//
// @access Operations (friend function)
//
public:
	//@cfunction Plus
	friend long operator + (const CVSB_Byte& d1, const CVSB_Byte& d2);

	//@cfunction Minus
	friend unsigned char operator - (const CVSB_Byte& d1, const CVSB_Byte& d2);

	//@cfunction Time
	friend long operator * (const CVSB_Byte& d1, const CVSB_Byte& d2);

	//@cfunction Divide
	friend double operator / (const CVSB_Byte& d1, const CVSB_Byte& d2);

	//@cfunction Plus
	friend long operator + (const CVSB_Byte& d1, unsigned char d2);

	//@cfunction Minus
	friend unsigned char operator - (const CVSB_Byte& d1, unsigned char d2);

	//@cfunction Time
	friend long operator * (const CVSB_Byte& d1, unsigned char d2);

	//@cfunction Divide
	friend double operator / (const CVSB_Byte& d1, unsigned char d2);

	//@cfunction Plus
	friend long operator + (unsigned char d1, const CVSB_Byte& d2);
	
	//@cfunction Minus
	friend unsigned char operator - (unsigned char d1, const CVSB_Byte& d2);

	//@cfunction Time
	friend long operator * (unsigned char d1, const CVSB_Byte& d2);

	//@cfunction Divide
	friend double operator / (unsigned char d1, const CVSB_Byte& d2);

	//@cfunction Equal to
	friend bool operator == (const CVSB_Byte& d1, const CVSB_Byte& d2);

	//@cfunction Not equal to
	friend bool operator != (const CVSB_Byte& d1, const CVSB_Byte& d2);

	//@cfunction Comparsion
	friend bool operator < (const CVSB_Byte& d1, const CVSB_Byte& d2);

	//@cfunction Comparsion
	friend bool operator <= (const CVSB_Byte& d1, const CVSB_Byte& d2);

	//@cfunction Comparsion
	friend bool operator > (const CVSB_Byte& d1, const CVSB_Byte& d2);

	//@cfunction Comparsion
	friend bool operator >= (const CVSB_Byte& d1, const CVSB_Byte& d2);

	//@cfunction Equal to
	friend bool operator == (const CVSB_Byte& d1, unsigned char d2);

	//@cfunction Not equal to
	friend bool operator != (const CVSB_Byte& d1, unsigned char d2);

	//@cfunction Comparsion
	friend bool operator < (const CVSB_Byte& d1, unsigned char d2);

	//@cfunction Comparsion
	friend bool operator <= (const CVSB_Byte& d1, unsigned char d2);

	//@cfunction Comparsion
	friend bool operator > (const CVSB_Byte& d1, unsigned char d2);

	//@cfunction Comparsion
	friend bool operator >= (const CVSB_Byte& d1, unsigned char d2);

	//@cfunction Equal to
	friend bool operator == (unsigned char d1, const CVSB_Byte& d2);

	//@cfunction Not equal to
	friend bool operator != (unsigned char d1, const CVSB_Byte& d2);

	//@cfunction Comparsion
	friend bool operator < (unsigned char d1, const CVSB_Byte& d2);

	//@cfunction Comparsion
	friend bool operator <= (unsigned char d1, const CVSB_Byte& d2);

	//@cfunction Comparsion
	friend bool operator > (unsigned char d1, const CVSB_Byte& d2);

	//@cfunction Comparsion
	friend bool operator >= (unsigned char d1, const CVSB_Byte& d2);

//
// @access Attributions
//
private:
	//@cmember The byte data 
	unsigned char			m_nByte;	

	//@cmember The byte default data 
	unsigned char			m_nDefault;	
};

#endif