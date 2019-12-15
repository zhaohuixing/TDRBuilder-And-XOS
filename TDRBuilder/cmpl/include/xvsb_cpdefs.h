// Project: Visual System Builder
//
// File Name: xvsb_cpdefs.h
//
// Description: The definition of the token related data type for expression parsing
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/24/2005	
//
// History:
// 1.    01/24/2005: Create	
//
#ifndef __XVSB_CPDEFS_H__
#define __XVSB_CPDEFS_H__

#include <string>
#include <map>
#include "xvsb_strutil.h"

////////////////////////////////////////////////////////
//  enXVSB_CPCCODE: Character codes.
////////////////////////////////////////////////////////
typedef enum _enXVSB_CPCCODE 
{
    enXVSB_CCLETTER, 
	enXVSB_CCDIGIT, 
	enXVSB_CCSPECIAL, 
	enXVSB_CCQUOTE, 
	enXVSB_CCWHITESPACE,
    enXVSB_CCEOF, 
	enXVSB_CCERROR,
}enXVSB_CPCCODE;

////////////////////////////////////////////////////////
// enXVSB_CPTKNCODE: Token codes.
////////////////////////////////////////////////////////
typedef enum _enXVSB_CPTKNCODE 
{
	//
	// General token code
	//
    enXVSB_TCDUMMY = 0,		// Nothing	
	enXVSB_TCIDENTIFIER,	//	ID token
	enXVSB_TCWORD = enXVSB_TCIDENTIFIER, // Word token
	enXVSB_TCSTRING,		// String token
	enXVSB_TCNUMBER,		// Double token
	enXVSB_TCEOF,			// End flag        
	enXVSB_TCERROR,			// Error flag

	//
	// Built-In data type token code
	//
	enXVSB_TCTYPEINT,		// Integer
	enXVSB_TCTYPEDOUBLE,	// Float (double)	
	enXVSB_TCTYPEFLOAT,		// Float
	enXVSB_TCTYPEBYTE,		// Byte
	enXVSB_TCTYPEBOOL,		// Boolean
	enXVSB_TCTYPECHAR,		// Char
	enXVSB_TCTYPESTRING,	// String	

	//
	// Mathmatical operation token code
	//
	// Level 3
	enXVSB_TCABS,			// abs    
	enXVSB_TCSIN,			// sin
	enXVSB_TCSINH,			// sinh
	enXVSB_TCASIN,			// arcsin
	enXVSB_TCCSC,			// csc
	enXVSB_TCCSCH,			// csch
	enXVSB_TCCOS,			// cos
	enXVSB_TCCOSH,			// cosh
	enXVSB_TCACOS,			// arccos
	enXVSB_TCSEC,			// sec
	enXVSB_TCSECH,			// sech
	enXVSB_TCTAN,			// tg
	enXVSB_TCTANH,			// tgh
	enXVSB_TCATAN,			// arctg
	enXVSB_TCCTG,			// ctg
	enXVSB_TCCTGH,			// ctgh
	enXVSB_TCACTG,			// arcctg
	enXVSB_TCEXP,			// exponent
	enXVSB_TCLN,			// ln
	enXVSB_TCLOG10,			// log10(x)
	enXVSB_TCLOG,			// log(x, y) = ln(x)/ln(y)
	enXVSB_TCSQRT,			// sqrt
	enXVSB_TCPOW,			// pow
	enXVSB_TCROOT,			// root
	enXVSB_TCFACTORIAL,		// factorial n!
	enXVSB_TCHYPOT,			// hypotenuse
	enXVSB_TCARG,			// argument 
	enXVSB_TCPOLAR,         // polar
	enXVSB_TCMOD,			// modulus "integer
	enXVSB_TCMOD2,			// modulus "modulus"
	enXVSB_TCFRACTION,     	// fraction after modulus
	enXVSB_TCFMOD,			// the left part of modulus "fmod"
	enXVSB_TCFMOD2,			// the left fraction of modulus "fmod"
	enXVSB_TCLSHIFT,		// bitwise left shift <<
	enXVSB_TCRSHIFT,		// bitwise right shift >>
	enXVSB_TCBWAND,			// bitwise AND &
	enXVSB_TCBWEXOR,		// bitwise exclusive OR ^
	enXVSB_TCBWINOR,		// bitwise inclusive OR | 
	enXVSB_TCBWNOT,			// bitwise NOT ~ 
	// Level 2
	enXVSB_TCTIME,			// time *
	enXVSB_TCDIVIDE,		// divide /
	// Level 1
	enXVSB_TCPLUS,			// plus +
	enXVSB_TCMINUS,			// minus - 

	//
	// Logical comparsion token code
	//
	enXVSB_TCSAME,			// equal to ==    
    enXVSB_TCNOTSAME,		// not equal to == 
	enXVSB_TCLT,			// less than <
	enXVSB_TCLE,			// less or equal to <= 
    enXVSB_TCGT,			// larger than >
	enXVSB_TCGE,			// larger or equal to >=

	//
	// Logical relationship token code
	//
	enXVSB_TCLGOR,			// logical OR	||
    enXVSB_TCLGAND,			// logical AND	&& 

	//
	// Brackets' token code
	//
	enXVSB_TCLBRACE,		// {
	enXVSB_TCRBRACE,		// } 
	enXVSB_TCLPAREN,		// ( 
	enXVSB_TCRPAREN,		// ) 
	enXVSB_TCLBRACKET,		// [ 
	enXVSB_TCRBRACKET,		// ] 

	//
	// Bool constant token code
	//
	enXVSB_TCDATATRUE,		// "true"
	enXVSB_TCDATAFALSE,		// "false"

	//
	// Accessor token code
	//
	enXVSB_TCPUBLIC,		// public identifier
	enXVSB_TCPROTECTED,		// protected identifier
	enXVSB_TCPRIVATE,		// provate identifier

	//
	// NameSpace token code
	//
	enXVSB_TCNAMESPACE,		// namespace identifier

	//
	// Class token code
	//
	enXVSB_TCCLASS,			// class identifier
	
	//
	// void token code
	//
	enXVSB_TCTYPEVOID,		// void identifier

	//
	// Others
	//
    enXVSB_TCEQUAL,			// Assignment = 
	enXVSB_TCRBRACEEND, 
	enXVSB_TCCOLON, 
	enXVSB_TCSEMICOLON, 
	enXVSB_TCCOMMA, 
	enXVSB_TCDOT,
	enXVSB_TCCOLONEQUAL, 
    enXVSB_TCNE, 
	enXVSB_TCDOTDOT,
	//
	enXVSB_TCARRAY, 
	enXVSB_TCBEGIN, 
	enXVSB_TCCASE, 
	enXVSB_TCCONST, 
	enXVSB_TCDIV,
    enXVSB_TCDO, 
	enXVSB_TCDOWNTO, 
	enXVSB_TCELSE, 
	enXVSB_TCEND, 
	enXVSB_TCFILE, 
	enXVSB_TCFOR, 
	enXVSB_TCFUNCTION,
    enXVSB_TCGOTO, 
	enXVSB_TCIF, 
	enXVSB_TCIN, 
	enXVSB_TCLABEL, 
	enXVSB_TCNIL, 
	enXVSB_TCNOT, 
	enXVSB_TCOF, 
    enXVSB_TCPACKED, 
	enXVSB_TCPROCEDURE, 
	enXVSB_TCPROGRAM, 
	enXVSB_TCRECORD, 
	enXVSB_TCREPEAT, 
	enXVSB_TCSET,
    enXVSB_TCTHEN, 
	enXVSB_TCTO, 
	enXVSB_TCTYPE, 
	enXVSB_TCUNTIL, 
	enXVSB_TCVAR, 
	enXVSB_TCWHILE, 
	enXVSB_TCWITH,

}enXVSB_CPTKNCODE;

////////////////////////////////////////////////////////
//  enXVSB_CPDATATTYPE : Data type.
////////////////////////////////////////////////////////
typedef enum _enXVSB_CPDATATTYPE 
{
    enXVSB_TYDUMMY, 
	enXVSB_TYINTEGER, 
	enXVSB_TYREAL, 
	enXVSB_TYCHAR, 
	enXVSB_TYSTRING,
	enXVSB_TYBYTE, 
	enXVSB_TYBOOL, 
	enXVSB_TYVOID, 
	enXVSB_TYCLASS, 
	enXVSB_TYNAMESPACE, 
}enXVSB_CPDATATTYPE;


typedef std::map<std::wstring, enXVSB_CPTKNCODE, CVSB_StrCmp> CVSB_TokenLUT; //Key: token string, 
typedef std::map<wchar_t, enXVSB_CPTKNCODE> CVSB_WCTokenLUT; //Key: token character, 


#endif