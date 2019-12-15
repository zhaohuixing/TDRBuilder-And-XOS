// Project: Visual System Builder
//
// File Name: xvsb_tknchk.cpp
//
// Description: The implementation of token check class
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
#include "xvsb_tknchk.h"

bool CVSB_TokenCheck::IsBuildInTypeToken(enXVSB_CPTKNCODE token)
{
	return (token == enXVSB_TCTYPEINT ||
			token == enXVSB_TCTYPEDOUBLE ||
			token == enXVSB_TCTYPEFLOAT ||
			token == enXVSB_TCTYPEBYTE ||
			token == enXVSB_TCTYPEBOOL ||
			token == enXVSB_TCTYPECHAR ||
			token == enXVSB_TCTYPESTRING);
}

bool CVSB_TokenCheck::IsMathOpToken(enXVSB_CPTKNCODE token)
{
	return (token == enXVSB_TCABS ||
			token == enXVSB_TCSIN ||
			token == enXVSB_TCSINH ||
			token == enXVSB_TCASIN ||
			token == enXVSB_TCCSC ||
			token == enXVSB_TCCSCH ||
			token == enXVSB_TCCOS ||
			token == enXVSB_TCCOSH ||
			token == enXVSB_TCACOS ||
			token == enXVSB_TCSEC ||
			token == enXVSB_TCSECH ||
			token == enXVSB_TCTAN ||
			token == enXVSB_TCTANH ||
			token == enXVSB_TCATAN ||
			token == enXVSB_TCCTG ||
			token == enXVSB_TCCTGH ||
			token == enXVSB_TCACTG ||
			token == enXVSB_TCEXP ||
			token == enXVSB_TCLN ||
			token == enXVSB_TCLOG10 ||
			token == enXVSB_TCLOG ||
			token == enXVSB_TCSQRT ||
			token == enXVSB_TCPOW ||
			token == enXVSB_TCROOT ||
			token == enXVSB_TCFACTORIAL ||
			token == enXVSB_TCHYPOT ||
			token == enXVSB_TCARG ||
			token == enXVSB_TCPOLAR ||
			token == enXVSB_TCMOD ||
			token == enXVSB_TCMOD2 ||
			token == enXVSB_TCFRACTION ||
			token == enXVSB_TCFMOD ||
			token == enXVSB_TCFMOD2 ||
			token == enXVSB_TCLSHIFT ||
			token == enXVSB_TCRSHIFT ||
			token == enXVSB_TCBWAND ||
			token == enXVSB_TCBWEXOR ||
			token == enXVSB_TCBWINOR ||
			token == enXVSB_TCBWNOT ||
			token == enXVSB_TCTIME ||
			token == enXVSB_TCDIVIDE ||
			token == enXVSB_TCPLUS ||
			token == enXVSB_TCMINUS);
}

bool CVSB_TokenCheck::IsLogicCmpToken(enXVSB_CPTKNCODE token)
{
	return (token == enXVSB_TCSAME ||
			token == enXVSB_TCNOTSAME ||
			token == enXVSB_TCLT ||
			token == enXVSB_TCLE ||
			token == enXVSB_TCGT ||
			token == enXVSB_TCGE);
}

bool CVSB_TokenCheck::IsLogicLnkToken(enXVSB_CPTKNCODE token)
{
	return (enXVSB_TCLGOR || token == enXVSB_TCLGAND);
}

enXVSB_OPERATION CVSB_TokenCheck::GetMathOpByToken(enXVSB_CPTKNCODE token)
{
	enXVSB_OPERATION opType = enXVSB_NONE;

	switch(token)
	{
		case enXVSB_TCABS:			// abs    
			opType = enXVSB_ABS;
			break;
		case enXVSB_TCSIN:			// sin
			opType = enXVSB_SIN;
			break;
		case enXVSB_TCSINH:			// sinh
			opType = enXVSB_SINH;
			break;
		case enXVSB_TCASIN:			// arcsin
			opType = enXVSB_ASIN;
			break;
		case enXVSB_TCCSC:			// csc
			opType = enXVSB_CSC;
			break;
		case enXVSB_TCCSCH:			// csch
			opType = enXVSB_CSCH;
			break;
		case enXVSB_TCCOS:			// cos
			opType = enXVSB_COS;
			break;
		case enXVSB_TCCOSH:			// cosh
			opType = enXVSB_COSH;
			break;
		case enXVSB_TCACOS:			// arccos
			opType = enXVSB_ACOS;
			break;
		case enXVSB_TCSEC:			// sec
			opType = enXVSB_SEC;
			break;
		case enXVSB_TCSECH:			// sech
			opType = enXVSB_SECH;
			break;
		case enXVSB_TCTAN:			// tg
			opType = enXVSB_TAN;
			break;
		case enXVSB_TCTANH:			// tgh
			opType = enXVSB_TANH;
			break;
		case enXVSB_TCATAN:			// arctg
			opType = enXVSB_ATAN;
			break;
		case enXVSB_TCCTG:			// ctg
			opType = enXVSB_CTG;
			break;
		case enXVSB_TCCTGH:			// ctgh
			opType = enXVSB_CTGH;
			break;
		case enXVSB_TCACTG:			// arcctg
			opType = enXVSB_ACTG;
			break;
		case enXVSB_TCEXP:			// exponent
			opType = enXVSB_EXP;
			break;
		case enXVSB_TCLN:			// ln
			opType = enXVSB_LN;
			break;
		case enXVSB_TCLOG10:			// log10(x)
			opType = enXVSB_LOG10;
			break;
		case enXVSB_TCLOG:			// log(x, y) = ln(x)/ln(y)
			opType = enXVSB_LOG;
			break;
		case enXVSB_TCSQRT:			// sqrt
			opType = enXVSB_SQRT;
			break;
		case enXVSB_TCPOW:			// pow
			opType = enXVSB_POW;
			break;
		case enXVSB_TCROOT:			// root
			opType = enXVSB_ROOT;
			break;
		case enXVSB_TCFACTORIAL:		// factorial n!
			opType = enXVSB_FACTORIAL;
			break;
		case enXVSB_TCHYPOT:			// hypotenuse
			opType = enXVSB_HYPOT;
			break;
		case enXVSB_TCARG:			// argument 
			opType = enXVSB_ARG;
			break;
		case enXVSB_TCPOLAR:			// argument 
			opType = enXVSB_POLAR;
			break;
		case enXVSB_TCMOD:			// modulus "integer"
			opType = enXVSB_MOD;
			break;
		case enXVSB_TCMOD2:			// modulus "modulus"
			opType = enXVSB_MOD2;
			break;
		case enXVSB_TCFRACTION:		// fraction "fraction"
			opType = enXVSB_FRACTION;
			break;
		case enXVSB_TCFMOD:			// the left part of modulus "fmod"
			opType = enXVSB_FMOD;
			break;
		case enXVSB_TCFMOD2:		// the left fraction part of modulus "fmod"
			opType = enXVSB_FMOD2;
			break;
		case enXVSB_TCLSHIFT:		// bitwise left shift <<
			opType = enXVSB_LSHIFT;
			break;
		case enXVSB_TCRSHIFT:		// bitwise right shift >>
			opType = enXVSB_RSHIFT;
			break;
		case enXVSB_TCBWAND:			// bitwise AND &
			opType = enXVSB_AND;
			break;
		case enXVSB_TCBWEXOR:		// bitwise exclusive OR ^
			opType = enXVSB_EXOR;
			break;
		case enXVSB_TCBWINOR:		// bitwise inclusive OR | 
			opType = enXVSB_INOR;
			break;
		case enXVSB_TCBWNOT:			// bitwise NOT ~ 
			opType = enXVSB_NOT;
			break;

		// Level 2
		case enXVSB_TCTIME:			// time *
			opType = enXVSB_TIME;
			break;
		case enXVSB_TCDIVIDE:		// divide /
			opType = enXVSB_DIVIDE;
			break;
	
		// Level 1
		case enXVSB_TCPLUS:			// plus +
			opType = enXVSB_PLUS;
			break;
		case enXVSB_TCMINUS:			// minus - 
			opType = enXVSB_MINUS;
			break;
	}

	return opType;
}
