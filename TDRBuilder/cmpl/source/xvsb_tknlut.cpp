// Project: Visual System Builder
//
// File Name: xvsb_tknlut.cpp
//
// Description: The implementation of the token constant look-up table creation 
//				helper class for expression parsing
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
#include <stdlib.h>
#include "xvsb_defs.h"
#include "xvsb_macro.h"
#include "xvsb_tknlut.h"

//////////////////////////////////////////////////////////////////
//  Reserved word token lists
//////////////////////////////////////////////////////////////////
typedef struct _stXVSB_TResTknPair 
{
    const wchar_t*			m_pString;  // ptr to word string
    enXVSB_CPTKNCODE	m_code;     // word code
}stXVSB_TResTknPair;

stXVSB_TResTknPair rwdlist[] = 
{
	//
	//   Data types
	// 
	{XVSM_DTSTR[XVSM_DT_INTEGER],		enXVSB_TCTYPEINT},		// Integer
	{L"double",							enXVSB_TCTYPEDOUBLE},	// Float (double)	
	{XVSM_DTSTR[XVSM_DT_FLOAT],			enXVSB_TCTYPEFLOAT},	// Float
	{XVSM_DTSTR[XVSM_DT_CHAR],			enXVSB_TCTYPECHAR},		// Char
	{L"string",							enXVSB_TCTYPESTRING},	// String	
	{XVSM_DTSTR[XVSM_DT_BYTE],			enXVSB_TCTYPEBYTE},		// Byte
	{XVSM_DTSTR[XVSM_DT_BOOL],			enXVSB_TCTYPEBOOL},		// Boolean
	{XVSM_BTRUE_STR,					enXVSB_TCDATATRUE},		// true
	{XVSM_BFALSE_STR,					enXVSB_TCDATAFALSE},	// false	
	{L"void",							enXVSB_TCTYPEVOID},

	//
	//   Mathmatical operations
	// 
	{L"abs",	enXVSB_TCABS},		// abs
	{L"sin",	enXVSB_TCSIN},		// sine
	{L"sinh",	enXVSB_TCSINH},		// hyperbolic sine
	{L"asin",	enXVSB_TCASIN},		// arc sine
	{L"csc",	enXVSB_TCCSC},		// inverse sine
	{L"csch",	enXVSB_TCCSCH},		// hyperbolic inverse sine
	{L"cos",	enXVSB_TCCOS},		// cosine
	{L"cosh",	enXVSB_TCCOSH},		// hyperbolic cosine
	{L"acos",	enXVSB_TCACOS},		// arc cosine
	{L"sec",	enXVSB_TCSEC},		// inverse cosine
	{L"sech",	enXVSB_TCSECH},		// hyperbolic inverse cosine
	{L"tg",		enXVSB_TCTAN},		// tangent
	{L"tgh",	enXVSB_TCTANH},		// hyperbolic tangent
	{L"atg",	enXVSB_TCATAN},		// arc tangent
	{L"ctg",	enXVSB_TCCTG},		// cotangent
	{L"ctgh",	enXVSB_TCCTGH},		// hyperbolic cotangent
	{L"actg",	enXVSB_TCACTG},		// arc cotange
	{L"exp",	enXVSB_TCEXP},		// exponent
	{L"ln",		enXVSB_TCLN},		// ln
	{L"log10",	enXVSB_TCLOG10},	// log10(x)
	{L"lg",		enXVSB_TCLOG},		// lg(x, y) = ln(x)/ln(y)
	{L"sqrt",	enXVSB_TCSQRT},		// square root
	{L"pow",	enXVSB_TCPOW},		// power
	{L"root",	enXVSB_TCROOT},		// root
	{L"hypot",	enXVSB_TCHYPOT},	// hypotenuse	
	{L"arg",	enXVSB_TCARG},		// argument 
	{L"polar",	enXVSB_TCPOLAR},	// polarize 
	{L"integer",	enXVSB_TCMOD},		// modulus "modf"
	{L"modulus",	enXVSB_TCMOD2},		// modulus "modf"
	{L"fraction",	enXVSB_TCFRACTION}, // fraction "fraction"
	{L"remainder",	enXVSB_TCFMOD},		// the left part of modulus "fmod" 
	{L"rfraction",	enXVSB_TCFMOD2},		// the left fraction part of modulus "fmod" 
};

void CVSB_WordTokenGenerator::operator ()(CVSB_TokenLUT* pTLUT)
{
	if(pTLUT)
	{
		pTLUT->clear();
		int n = sizeof(rwdlist)/sizeof(stXVSB_TResTknPair);
		for(int i = 0; i < n; i++)
		{
			pTLUT->insert(std::make_pair(rwdlist[i].m_pString, rwdlist[i].m_code));
		}
	}
}

typedef struct _stXVSB_TResSignTknPair 
{
    wchar_t				m_sign;		// sign
    enXVSB_CPTKNCODE	m_code;     // word code
}stXVSB_TResSignTknPair;

stXVSB_TResSignTknPair rsgntknlist[] = 
{
	{L'{', enXVSB_TCLBRACE},		// {
	{L'}', enXVSB_TCRBRACE},		// } 
	{L'(', enXVSB_TCLPAREN},		// ( 
	{L')', enXVSB_TCRPAREN},		// ) 
	{L'[', enXVSB_TCLBRACKET},		// [ 
	{L']', enXVSB_TCRBRACKET},		// ] 

	{L'*', enXVSB_TCTIME},			// time *
	{L'/', enXVSB_TCDIVIDE},		// divide /
	{L'+', enXVSB_TCPLUS},			// plus +
	{L'-', enXVSB_TCMINUS},			// minus - 

	{L'!', enXVSB_TCFACTORIAL},		// factorial n!

    {L'^', enXVSB_TCBWEXOR},		// bitwise exclusive OR ^ 
    {L'|', enXVSB_TCBWINOR},		// bitwise inclusive OR | 
    {L'&', enXVSB_TCBWAND},			// bitwise AND &
    {L'~', enXVSB_TCBWNOT},			// bitwise NOT ~ 

	{L'<', enXVSB_TCLT},			// less than <
	{L'>', enXVSB_TCGT},			// larger than >

	{L'=', enXVSB_TCEQUAL},			// Assignment =
	{L';', enXVSB_TCSEMICOLON},
	{L',', enXVSB_TCCOMMA},
	{L':', enXVSB_TCCOLON},
	{L'.', enXVSB_TCDOT},
};

void CVSB_SignTokenGenerator::operator ()(CVSB_WCTokenLUT* pTLUT)
{
	if(pTLUT)
	{
		pTLUT->clear();

		int n = sizeof(rsgntknlist)/sizeof(stXVSB_TResSignTknPair);
		for(int i = 0; i < n; i++)
		{
			pTLUT->insert(std::make_pair(rsgntknlist[i].m_sign, rsgntknlist[i].m_code));
		}

	}
}
