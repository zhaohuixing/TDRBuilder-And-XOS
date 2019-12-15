// Date: 06/07/2004	
#ifndef __XOS_MATH_H__
#define __XOS_MATH_H__

#include "xos_clsbase.h"
#include "xos_data.h"

typedef enum _XM_OPERATION
{
	enXM_NONE = 0,
	enXM_ABS,
	enXM_PLUS,
	enXM_MINUS,
	enXM_TIME,
	enXM_DIVIDE,
	enXM_SIN,
	enXM_SINH,
	enXM_ASIN,
	enXM_CSC,	  //
	enXM_CSCH,	  //
	enXM_COS,
	enXM_COSH,
	enXM_ACOS,
	enXM_SEC,	 //
	enXM_SECH,	 //
	enXM_TAN,
	enXM_TANH,
	enXM_ATAN,
	enXM_CTG,	 //
	enXM_CTGH,	 //
	enXM_ACTG,   //
	enXM_EXP,
	enXM_LOG,
	enXM_LOG10,
	enXM_SQRT,
	enXM_POW,
	enXM_ROOT,
	enXM_FACTORIAL,
	enXM_HYPOT
} XM_OPERATION;

typedef enum _XM_PRIORITY
{
	enXM_LEVEL_ROOT = 0,
	enXM_LEVEL1 = 1,
	enXM_LEVEL2 = 2,
	enXM_LEVEL3,
	enXM_LEVEL_NONE
} XM_PRIORITY;

typedef enum _XM_OPTYPE
{
	enXM_UNARY = 0,
	enXM_BINARY
} XM_OPTYPE;

static const wchar_t * XM_OPNAME[] = 
{
	L"NONE",
	L"ABS",
	L"PLUS",
	L"MINUS",
	L"TIME",
	L"DIVIDE",
	L"SIN",
	L"SINH",
	L"ASIN",
	L"CSC",
	L"CSCH",
	L"COS",
	L"COSH",
	L"ACOS",
	L"SEC",
	L"SECH",
	L"TAN",
	L"TANH",
	L"ATAN",
	L"CTG",
	L"CTGH",
	L"ACTG",
	L"EXP",
	L"LOG",
	L"LOG10",
	L"SQRT",
	L"POW",
	L"ROOT",
	L"FACTORIAL",
	L"HYPOTENUSE",
};


class CXOS_MathFunction : public CXOS_Method
{
//
// Construction/Destruction
//
public:
	CXOS_MathFunction(void);	// Constructor
	CXOS_MathFunction(std::wstring& szName); // Constructor
	CXOS_MathFunction(const wchar_t* szName); // Constructor
	CXOS_MathFunction(CXOS_Data* in1, CXOS_Data* in2, CXOS_Data* mo, XM_OPERATION op); // Constructor
	CXOS_MathFunction(const wchar_t* szName, CXOS_Data* in1, CXOS_Data* in2, CXOS_Data* mo, XM_OPERATION op); // Constructor
	CXOS_MathFunction(std::wstring& szName, CXOS_Data* in1, CXOS_Data* in2, CXOS_Data* mo, XM_OPERATION op);  // Constructor
	CXOS_MathFunction(const CXOS_MathFunction& mFunc); // Constructor
	virtual ~CXOS_MathFunction(void);	// Destructor

//
// Implementation
//
public:
	virtual int operator ()(void);	// Override operator () 

	virtual bool Run (void);	// Run the operation 

	virtual bool IsOK(void);	// Check working status

	virtual XM_PRIORITY Level(void);	// Check operation level

	virtual XM_OPTYPE OperType(void);	// Check operation type

	// Get operation name
	virtual std::wstring GetOperateName(void) {return std::wstring(XM_OPNAME[(int)m_Op]);} 

	// Get operation name
	virtual const wchar_t* GetOperateName(void) const {return XM_OPNAME[(int)m_Op];} 

	// Override dereference operator
	virtual CXOS_MathFunction& operator* (){return (*this);}

	// Check operation
	virtual XM_OPERATION Operation(void) const {return m_Op;} 

	// Get operation object reference
	virtual XM_OPERATION& Operation(void) {return m_Op;} 

	// Assign the input variable
	virtual bool SetVar1(CXOS_Data* m){m_dIn1 = m; return true;}

	// Assign the input variable
	virtual bool SetVar2(CXOS_Data* m){m_dIn2 = m; return true;}

	// Assign the output variable
	virtual bool SetOut(CXOS_Data* m){m_dOut = m; return true;}

	// Assign the operation
	virtual bool SetOperation(XM_OPERATION	op){m_Op = op; return true;}

	// Get output variable
	operator CXOS_Data* (){return m_dOut;}

	friend std::wostream& operator << (std::wostream& out, const CXOS_MathFunction& mp);
	friend std::wistream& operator >> (std::wistream& in, CXOS_MathFunction& mp);

	virtual bool CanStreamIO(void) const {return true;}

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXOS_MathFunction");}

//
// Attributions
//
protected:
	CXOS_Data*		m_dIn1;
	CXOS_Data*		m_dIn2;
	CXOS_Data*		m_dOut;
	bool			m_bOK;
	XM_OPERATION	m_Op;
};

#endif