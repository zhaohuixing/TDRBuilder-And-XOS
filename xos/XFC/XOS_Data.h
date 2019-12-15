// Date: 06/04/2004	
#ifndef __XOS_DATA_H__
#define __XOS_DATA_H__

#include "xos_clsbase.h"
#include "xos_const.h"
#include <stdio.h>
#include <math.h>
#include <iostream>

////////////////////////////////////////////////////////
// The data type definition
////////////////////////////////////////////////////////
typedef enum _enXOS_VARTYPE
{
	enXOS_VARIABLE = 0,		// Variable type 
	enXOS_VALUE				// Value type
} enXOS_VARTYPE;

typedef enum _enXOS_PARAMTYPE
{
	enXOS_PARAMETER = 0,	// Parameter type
	enXOS_CONSTANT			// Constant type 
} enXOS_PARAMTYPE;

extern "C"
{
	double Signed(double d);
};

////////////////////////////////////////////////////////
// The forward declaration
////////////////////////////////////////////////////////
class CXOS_Number;

////////////////////////////////////////////////////////
// The CXOS_Data class: 
// Present the regular or complex type data (floating)
////////////////////////////////////////////////////////

class CXOS_Data : public CXOS_ClassObject
{
//
// Construction/Destruction
//
public:
	CXOS_Data(void);  // Constructor
	CXOS_Data(enXOS_PARAMTYPE enParType); // Constructor
	CXOS_Data(std::wstring& szName, enXOS_VARTYPE enType = enXOS_VARIABLE, enXOS_PARAMTYPE enParType = enXOS_PARAMETER); // Constructor
	CXOS_Data(const wchar_t* szName, enXOS_VARTYPE enType = enXOS_VARIABLE, enXOS_PARAMTYPE enParType = enXOS_PARAMETER); // Constructor
	CXOS_Data(double dReal); // Constructor
	CXOS_Data(const wchar_t* szName, double dReal); // Constructor
	CXOS_Data(std::wstring& szName, double dReal);  // Constructor
	CXOS_Data(double dReal, double dImagery);  // Constructor 
	CXOS_Data(const wchar_t* szName, double dReal, double dImagery); // Constructor
	CXOS_Data(std::wstring& szName, double dReal, double dImagery); // Constructor
	CXOS_Data(const CXOS_Data& osData, enXOS_PARAMTYPE enParType = enXOS_PARAMETER); // Constructor
	virtual ~CXOS_Data(void); 	// Destructor

//
// Implementation
//
public:
	virtual bool Set(CXOS_ClassObject* pObj);
	virtual void Set(const CXOS_Data& vmData);			// Set value
	virtual void Set(double dVal);						// Set value
	virtual void Set(double dReal, double dImagery);	// Set value 

	virtual void Get(CXOS_Data& vmData);				// Get Value
	virtual void Get(double& dVal);						// Get Value
	virtual void Get(double& dReal, double& dImagery);  // Get Value
	virtual CXOS_ClassObject* Get(std::wstring& szFnName) const {return NULL;}


	double Real(void) const {return m_dReal;}	// Get Real Value
	double Imagery(void) const {return m_dImagery;}	// Get Real Value

	double GetLength(void) const;	// Get Complex length

	// Set data type
	void SetType(enXOS_VARTYPE enType) {m_enType = enType;} 

	// Get data type
	enXOS_VARTYPE GetType(void) const {return m_enType;}

	bool IsEqual(const CXOS_Data& d);		// Comparsion
	bool IsLarge(const CXOS_Data& d);		// Comparsion
	bool IsLargeEqual(const CXOS_Data& d);	// Comparsion
	bool IsSmall(const CXOS_Data& d);		// Comparsion
	bool IsSmallEqual(const CXOS_Data& d);	// Comparsion

	// Check zero value
	bool IsZero(void) const {return (abs(m_dReal) <= XOS_EPSILON && abs(m_dImagery) <= XOS_EPSILON && m_enType == enXOS_VALUE);}

	// Is real type data
	bool IsReal(void) const {return (abs(m_dImagery) <= XOS_EPSILON);}

	// Is complex type data
	bool IsCompex(void) const {return (m_enType == enXOS_VALUE && XOS_EPSILON < abs(m_dImagery));}

	// Is variable
	bool IsVariable(void) const {return (m_enType == enXOS_VARIABLE);}


	bool IsParameter(void) const {return (m_enParType == enXOS_PARAMETER);}

	bool IsConstant(void) const {return (m_enParType == enXOS_CONSTANT);}

//
// Operations
//
public:
	CXOS_Data& operator = (const CXOS_Data& data);	// Assignment
	CXOS_Data& operator = (const CXOS_Number& data);	// Assignment
	CXOS_Data& operator = (double dv);				// Assignment
	CXOS_Data& operator = (long nv);				// Assignment

	CXOS_Data& operator += (const CXOS_Data& data);
	CXOS_Data& operator -= (const CXOS_Data& data);
	CXOS_Data& operator *= (const CXOS_Data& data);
	CXOS_Data& operator /= (const CXOS_Data& data);

	CXOS_Data& operator += (double dv);
	CXOS_Data& operator -= (double dv);
	CXOS_Data& operator *= (double dv);
	CXOS_Data& operator /= (double dv);

	CXOS_Data& operator ++ (void);	// Prefix incremental
	CXOS_Data operator ++ (int);	// Postfix incremental
	CXOS_Data& operator -- (void);	// Prefix decremental	
	CXOS_Data operator -- (int);	// Postfix decremental	

	operator double (void);	// Type conversion to double
	operator long (void);	// Type conversion to long
	operator CXOS_Number(void); // Type conversion to CXOS_Number
//
// Arithmetic Operations
//
public:
	CXOS_Data Hypot(const CXOS_Data& d);	//Hypotenuse 

	CXOS_Data Abs(void);	// Modulus
	CXOS_Data Arg(void);	// Argument
	CXOS_Data Polar(void);	// Polar form of the complex number 

	CXOS_Data Sin(void);	// Sine
	CXOS_Data SinH(void);	// Hyperbolic Sine
	CXOS_Data Cos(void);	// Cosine
	CXOS_Data CosH(void);	// Hyperbolic Cosine
	CXOS_Data Tan(void);	// Tangent
	CXOS_Data TanH(void);	// Hyperbolic Tangent
	CXOS_Data CTan(void);	// Cotangent
	CXOS_Data CTanH(void);	// Hyperbolic Cotangent

	CXOS_Data Sec(void);	// Secant
	CXOS_Data SecH(void);	// Hyperbolic Secant
	CXOS_Data Csc(void);	// CoSecant
	CXOS_Data CscH(void);	// Hyperbolic CoSecant

	CXOS_Data ASin(void);	// ArcSine
	CXOS_Data ACos(void);	// ArcCosine
	CXOS_Data ATan(void);	// ArcTangent
	CXOS_Data ATan2(void);	// ArcTangent
	CXOS_Data ACTan(void);	// ArcCoTangent

	CXOS_Data Sqrt(void);	// Square root
	CXOS_Data Exp(void);	// Exponential 
	CXOS_Data Ln(void);		// Natural Logarithm (base e) 
	CXOS_Data Log10(void);	// Common Logarithm (base 10) 
	CXOS_Data Pow(double d);// Power
	CXOS_Data Pow(const CXOS_Data& d); // Power
	CXOS_Data Root(double d);// Power
	CXOS_Data Root(const CXOS_Data& d); // Power

	CXOS_Data Factorial(void); // Factorial

private:
	static long FactorialL(long n);
//
// Operations (friend function)
//
public:
	friend CXOS_Data operator + (const CXOS_Data& d1, const CXOS_Data& d2);
	friend CXOS_Data operator - (const CXOS_Data& d1, const CXOS_Data& d2);
	friend CXOS_Data operator * (const CXOS_Data& d1, const CXOS_Data& d2);
	friend CXOS_Data operator / (const CXOS_Data& d1, const CXOS_Data& d2);

	friend CXOS_Data operator + (const CXOS_Data& d1, double d2);
	friend CXOS_Data operator - (const CXOS_Data& d1, double d2);
	friend CXOS_Data operator * (const CXOS_Data& d1, double d2);
	friend CXOS_Data operator / (const CXOS_Data& d1, double d2);

	friend CXOS_Data operator + (double d1, const CXOS_Data& d2);
	friend CXOS_Data operator - (double d1, const CXOS_Data& d2);
	friend CXOS_Data operator * (double d1, const CXOS_Data& d2);
	friend CXOS_Data operator / (double d1, const CXOS_Data& d2);

	friend bool operator == (const CXOS_Data& d1, const CXOS_Data& d2);
	friend bool operator != (const CXOS_Data& d1, const CXOS_Data& d2);
	friend bool operator < (const CXOS_Data& d1, const CXOS_Data& d2);
	friend bool operator <= (const CXOS_Data& d1, const CXOS_Data& d2);
	friend bool operator > (const CXOS_Data& d1, const CXOS_Data& d2);
	friend bool operator >= (const CXOS_Data& d1, const CXOS_Data& d2);

	friend std::wostream& operator << (std::wostream& out, const CXOS_Data& d);
	friend std::wistream& operator >> (std::wistream& in, CXOS_Data& d);


	//Hypotenuse 
	friend CXOS_Data Hypot(const CXOS_Data& d1, const CXOS_Data& d2);

	// Power
	friend CXOS_Data Pow(const CXOS_Data& d1, const CXOS_Data& d2);
	friend CXOS_Data Pow(const CXOS_Data& d1, double d2);
	friend CXOS_Data Pow(double d1, const CXOS_Data& d2);

	// Root
	friend CXOS_Data Root(const CXOS_Data& d1, const CXOS_Data& d2);
	friend CXOS_Data Root(const CXOS_Data& d1, double d2);
	friend CXOS_Data Root(double d1, const CXOS_Data& d2);

	virtual bool CanStreamIO(void) const {return true;}

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXOS_Data");}

//
// Attributions
//
public:
	double				m_dReal;	// The real portion
	double				m_dImagery;	// The imagery portion
	enXOS_VARTYPE		m_enType;	// The Data type

private:
	enXOS_PARAMTYPE		m_enParType;
};

#endif