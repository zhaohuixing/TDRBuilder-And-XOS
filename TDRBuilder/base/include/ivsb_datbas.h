// Project: Visual System Builder
//
// File Name: ivsb_datbas.h
//
// Description: The definition of the interface for all type 
//				data objects
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/13/2005	
//
// History:
// 1.    01/13/2005: Create	
//
#ifndef __IVSB_DATBAS_H__
#define __IVSB_DATBAS_H__

#include "ivsb_base.h"
#include "xvsb_paratype.h"
#include "xvsb_macro.h"
#include "xvsb_defs.h"
#include "xvsb_helper.h"
#include "tvsb_cpputil.h"
#include <vector>

class IVSB_DataBase : public IVSB_Base
{
//
//@access Constructions/Destruction:
//
public:
	//@cmember  Constructor 
	IVSB_DataBase(void) : IVSB_Base(XVSM_NS_GENERIC, XVSM_TYPE_DATA, L""){}; 

	//@cmember  Constructor 
	IVSB_DataBase(const wchar_t* szClass) : IVSB_Base(XVSM_NS_GENERIC, XVSM_TYPE_DATA, szClass){}; 

	//@cmember  Constructor 
	IVSB_DataBase(const std::wstring& szClass) : IVSB_Base(XVSM_NS_GENERIC, XVSM_TYPE_DATA, szClass.c_str()){}; 
	
	//@cmember  Constructor 
	IVSB_DataBase(const wchar_t* szClass, const wchar_t* szName) : IVSB_Base(XVSM_NS_GENERIC, XVSM_TYPE_DATA, szClass, szName){}; 

	//@cmember  Constructor 
	IVSB_DataBase(const std::wstring& szClass, const std::wstring& szName) : IVSB_Base(XVSM_NS_GENERIC, XVSM_TYPE_DATA, szClass.c_str(), szName.c_str()){}; 
	
	//@cmember  Destructor 
	virtual ~IVSB_DataBase(void){};

//
//@access Mathmatical operations:
//
public:
	//@cmember  Get parameter type
	virtual CVSB_ParamType GetParamType(void){return CVSB_ParamType(GetType());}

	//@cmember  Check built-in data type
	virtual bool IsBuiltInType(void){return true;}

	//@cmember  Check class data type
	virtual bool IsClassType(void){return false;}

	//@cmember  Hypotenuse 
	virtual bool Hypot(IVSB_DataBase* d, IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Absolute value  
	virtual bool Abs(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Argument
	virtual bool Arg(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Polar form of the complex number 
	virtual bool Polar(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Sine
	virtual bool Sin(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Hyperbolic Sine
	virtual bool SinH(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Cosine
	virtual bool Cos(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Hyperbolic Cosine
	virtual bool CosH(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Tangent
	virtual bool Tan(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Hyperbolic Tangent
	virtual bool TanH(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Cotangent
	virtual bool CTan(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Hyperbolic Cotangent
	virtual bool CTanH(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Secant
	virtual bool Sec(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Hyperbolic Secant
	virtual bool SecH(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  CoSecant
	virtual bool Csc(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Hyperbolic CoSecant
	virtual bool CscH(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  ArcSine
	virtual bool ASin(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  ArcCosine
	virtual bool ACos(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  ArcTangent
	virtual bool ATan(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  ArcCoTangent
	virtual bool ACTan(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Square root
	virtual bool Sqrt(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Exponential 
	virtual bool Exp(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Natural Logarithm (base e) 
	virtual bool Ln(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Common Logarithm (base 10) 
	virtual bool Log10(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Common Logarithm
	virtual bool Log(IVSB_DataBase* d, IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Power
	virtual bool Pow(IVSB_DataBase* d, IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Power
	virtual bool Root(IVSB_DataBase* d, IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Factorial  ("n!")
	virtual bool Factorial(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Plus	 ("+")
	virtual bool Plus(IVSB_DataBase* d, IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Minus	 ("-")
	virtual bool Minus(IVSB_DataBase* d, IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Time	 ("*")
	virtual bool Time(IVSB_DataBase* d, IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Divide	 ("/")
	virtual bool Divide(IVSB_DataBase* d, IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Modulus  
	virtual bool Mod2(IVSB_DataBase* d, IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Modulus  
	virtual bool Mod(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  The left part after Modulus  
	virtual bool FMod(IVSB_DataBase* d, IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  The left part after Modulus  
	virtual bool FMod2(IVSB_DataBase* d, IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Fraction  
	virtual bool Fraction(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Left Shift	 ("<<")
	virtual bool LShift(IVSB_DataBase* d, IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Right Shift	 (">>")
	virtual bool RShift(IVSB_DataBase* d, IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  bitwise-AND 	 ("&")
	virtual bool And(IVSB_DataBase* d, IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  bitwise-exclusive-OR  ("^")
	virtual bool ExOR(IVSB_DataBase* d, IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  bitwise-inclusive-OR  ("|")
	virtual bool InOR(IVSB_DataBase* d, IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Complement ("~")
	virtual bool Not(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Negative ("-")
	virtual bool Negative(IVSB_DataBase** pOut){XVSB_Assert(false); return false;}

	//@cmember  Assignment ("=")
	virtual bool Assign(IVSB_DataBase* pData) = 0;

	//@cmember  Assignment ("=")
	virtual bool AssignDefault(IVSB_DataBase* pData) = 0;

	//@cmember  Logical Comparsion
	virtual bool Compare(IVSB_DataBase* pObj, enXVSB_CMPTYPE cmp) = 0; 

	//@cmember  Get data type index
	virtual int GetDataTypeIndex(void) = 0; 

	//@cmember  Get data type presentation string
	virtual const wchar_t* GetDataTypeStr(void) const = 0; 

	//@cmember  Get data type presentation string
	virtual std::wstring GetDataTypeStr(void) = 0; 

	//@cmember  Get data type presentation string
	virtual std::wstring GetDataValueStr(void) = 0; 

	//@cmember  Get data type presentation string
	virtual const wchar_t* GetDataValueStr(void) const = 0; 

	//@cmember  Get data type presentation string
	virtual std::wstring GetDefaultValueStr(void) = 0; 

	//@cmember  Get data type presentation string
	virtual const wchar_t* GetDefaultValueStr(void) const = 0; 

	//@cmember  Reset data to default
	virtual void Reset(void) = 0;

//
//@access Attributes:
//
protected:
	//@cmember  The string presenting the value 
	mutable std::wstring		m_szValStr; 
};

typedef IVSB_DataBase*	CVSB_DataHandle;

typedef std::vector<IVSB_DataBase*>							IVSB_ArrayBase;
typedef TVSB_Deletor<IVSB_DataBase>							IVSB_ArrayBaseDelete;
typedef TVSB_Dealloc<IVSB_ArrayBase, IVSB_ArrayBaseDelete>	IVSB_ArrayBaseFree;

typedef std::map<std::wstring, IVSB_DataBase*>				IVSB_DataTable;
typedef TVSB_PairDeletor<IVSB_DataTable::value_type>		IVSB_DataTableDelete;
typedef TVSB_Dealloc<IVSB_DataTable, IVSB_DataTableDelete>  IVSB_DataTableFree;

#endif