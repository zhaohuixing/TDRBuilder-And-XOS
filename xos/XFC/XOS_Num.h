// Date: 06/05/2004	
#ifndef __XOS_NUMBER_H__
#define __XOS_NUMBER_H__

#include "xos_clsbase.h"

////////////////////////////////////////////////////////
// The forward declaration
////////////////////////////////////////////////////////
class CXOS_Data;

////////////////////////////////////////////////////////
// The CXOS_Data class: 
// Present the regular or complex type data (floating)
////////////////////////////////////////////////////////
class CXOS_Number :	public CXOS_ClassObject
{
//
// Construction/Destruction
//
public:
	CXOS_Number(void);	// Constructor
	CXOS_Number(std::wstring& szName); // Constructor
	CXOS_Number(const wchar_t* szName); // Constructor
	CXOS_Number(long nv); // Constructor
	CXOS_Number(const wchar_t* szName, long nv); // Constructor
	CXOS_Number(std::wstring& szName, long nv);  // Constructor
	CXOS_Number(const CXOS_Number& nNum); // Constructor
	virtual ~CXOS_Number(void);	// Destructor

//
// Implementation
//
public:

	virtual bool Set(CXOS_ClassObject* pObj);
	virtual void Set(const CXOS_Number& vmNum){m_nNumber = vmNum.m_nNumber;}			// Set value
	virtual void Set(long	nVal){m_nNumber = nVal;}									// Set value
	virtual void Set(double dVal){m_nNumber = (long)dVal;}									// Set value

	virtual void Get(CXOS_Number& vmData){vmData.m_nNumber = m_nNumber;}				// Get Value
	virtual void Get(long& nVal){nVal = m_nNumber;}						// Get Value
	virtual void Get(double& dVal){dVal = (double)m_nNumber;}  // Get Value
	virtual long Get(void){return m_nNumber;}  // Get Value
	virtual CXOS_ClassObject* Get(std::wstring& szFnName) const {return NULL;}

	long& Number(void){return m_nNumber;}
	long Number(void) const {return m_nNumber;}

	bool IsEqual(const CXOS_Number& d);			// Comparsion
	bool IsLarge(const CXOS_Number& d);			// Comparsion
	bool IsLargeEqual(const CXOS_Number& d);	// Comparsion
	bool IsSmall(const CXOS_Number& d);			// Comparsion
	bool IsSmallEqual(const CXOS_Number& d);	// Comparsion

//
// Operations
//
public:
	CXOS_Number& operator = (const CXOS_Number& data);	// Assignment
	CXOS_Number& operator = (const CXOS_Data& data);	// Assignment
	CXOS_Number& operator = (double dv);				// Assignment
	CXOS_Number& operator = (long nv);				// Assignment

	CXOS_Number& operator += (const CXOS_Number& data);
	CXOS_Number& operator -= (const CXOS_Number& data);
	CXOS_Number& operator *= (const CXOS_Number& data);
	CXOS_Number& operator /= (const CXOS_Number& data);

	CXOS_Number& operator += (long nv);
	CXOS_Number& operator -= (long nv);
	CXOS_Number& operator *= (long nv);
	CXOS_Number& operator /= (long nv);

	CXOS_Number& operator ++ (void);	// Prefix incremental
	CXOS_Number operator ++ (int);	// Postfix incremental
	CXOS_Number& operator -- (void);	// Prefix decremental	
	CXOS_Number operator -- (int);	// Postfix decremental	

	operator double (void);	// Type conversion to double
	operator long (void);	// Type conversion to long
	operator CXOS_Data(void); // Type conversion to CXOS_Data

//
// Operations (friend function)
//
public:
	friend bool operator == (const CXOS_Number& d1, const CXOS_Number& d2);
	friend bool operator != (const CXOS_Number& d1, const CXOS_Number& d2);
	friend bool operator < (const CXOS_Number& d1, const CXOS_Number& d2);
	friend bool operator <= (const CXOS_Number& d1, const CXOS_Number& d2);
	friend bool operator > (const CXOS_Number& d1, const CXOS_Number& d2);
	friend bool operator >= (const CXOS_Number& d1, const CXOS_Number& d2);

	friend bool operator == (const CXOS_Number& d1, double d2);
	friend bool operator != (const CXOS_Number& d1, double d2);
	friend bool operator < (const CXOS_Number& d1, double d2);
	friend bool operator <= (const CXOS_Number& d1, double d2);
	friend bool operator > (const CXOS_Number& d1, double d2);
	friend bool operator >= (const CXOS_Number& d1, double d2);

	friend bool operator == (double d1, const CXOS_Number& d2);
	friend bool operator != (double d1, const CXOS_Number& d2);
	friend bool operator < (double d1, const CXOS_Number& d2);
	friend bool operator <= (double d1, const CXOS_Number& d2);
	friend bool operator > (double d1, const CXOS_Number& d2);
	friend bool operator >= (double d1, const CXOS_Number& d2);

	friend std::wostream& operator << (std::wostream& out, const CXOS_Number& d);
	friend std::wistream& operator >> (std::wistream& in, CXOS_Number& d);

	virtual bool CanStreamIO(void) const {return true;}

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXOS_Number");}

//
// Attributions
//
public:
	long				m_nNumber;	// The number

};

#endif