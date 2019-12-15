// Project: Visual System Builder
//
// File Name: xvsb_defs.h
//
// Description: The constant types 
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/14/2005	
//
// History:
// 1.    01/14/2005: Create	
//
#ifndef __XVSB_DEFS_H__
#define __XVSB_DEFS_H__

#include "xvsb_strdefs.h"
#include <vector>
#include <deque>

typedef enum _enXVSB_CMPTYPE
{
	enXVSB_EQUAL = 0,		// == 
	enXVSB_NOTEQUAL,		// != 
	enXVSB_LARGEEQUAL,		// >=
	enXVSB_LARGE,			// >
	enXVSB_SMALLEQUAL,		// <=
	enXVSB_SMALL			// <
} enXVSB_CMPTYPE;

typedef enum _enXVSB_LGLINK
{
	enXVSB_LGOR = 0,		// Or  ||
	enXVSB_LGAND			// And   &&
} enXVSB_LGLINK;

typedef enum _enXVSB_PARATYPE
{
	enXVSB_PARA_VAR = 0,	// Variable
	enXVSB_PARA_VARARY,		// Array element type variable
	enXVSB_PARA_CONST,		// Constant
} enXVSB_PARATYPE;

typedef enum _enXVSB_PARAMTYPE
{
	enXVSB_PARAM_CONST,		// Constant
	enXVSB_PARAM_VAR,	// Variable
	enXVSB_PARAM_ARRAY,		// Array element type variable
	enXVSB_PARAM_EXPRESSION,	// Expression type variable
	enXVSB_PARAM_FUNCTION,		// Function type variable
} enXVSB_PARAMTYPE;

typedef enum _enXVSB_NODEQTYPE
{
	enXVSB_NODEQ_NODE,		// Constant
	enXVSB_NODEQ_VAR,	// Variable
} enXVSB_NODEQTYPE;

typedef enum _enXVSB_OPERATION
{
	enXVSB_NONE = 0,
	enXVSB_ABS,
	enXVSB_PLUS,
	enXVSB_MINUS,
	enXVSB_TIME,
	enXVSB_DIVIDE,
	enXVSB_SIN,
	enXVSB_SINH,
	enXVSB_ASIN,
	enXVSB_CSC,	  //
	enXVSB_CSCH,  //
	enXVSB_COS,
	enXVSB_COSH,
	enXVSB_ACOS,
	enXVSB_SEC,	 //
	enXVSB_SECH, //
	enXVSB_TAN,
	enXVSB_TANH,
	enXVSB_ATAN,
	enXVSB_CTG,	 //
	enXVSB_CTGH, //
	enXVSB_ACTG, //
	enXVSB_EXP,
	enXVSB_LN,
	enXVSB_LOG10,
	enXVSB_LOG,
	enXVSB_SQRT,
	enXVSB_POW,
	enXVSB_ROOT,
	enXVSB_FACTORIAL,
	enXVSB_HYPOT,
	enXVSB_ARG,
	enXVSB_POLAR,
	enXVSB_MOD,		// Modulus
	enXVSB_MOD2,	// Modulus
	enXVSB_FMOD,	// The left of modulus
	enXVSB_FMOD2,	// The left of modulus
	enXVSB_LSHIFT,	// Operation "<<"
	enXVSB_RSHIFT,  // Operation ">>"
	enXVSB_AND,		// Operation "&"
	enXVSB_EXOR,	// Operation "^"
	enXVSB_INOR,	// Operation "|"
	enXVSB_NOT,		// Operation "~"
	enXVSB_FRACTION,// Fraction
} enXVSB_OPERATION;

typedef std::deque<enXVSB_OPERATION>	CVSB_OTypeQueue;

typedef enum _enXVSB_PRIORITY
{
	enXVSB_LEVEL_ROOT = 0,		
	enXVSB_LEVEL_NONE = 0,
	enXVSB_LEVEL1 = 1,	       
	enXVSB_LEVEL2 = 2,
	enXVSB_LEVEL3 = 3,
} enXVSB_PRIORITY;

typedef enum _enXVSB_BRACKET
{
	enXVSB_BKT_NONE = 0,
	enXVSB_BKT_ROUND,
	enXVSB_BKT_SQUARE,
	enXVSB_BKT_CURLY
} enXVSB_BRACKET;

typedef enum _enXVSB_OPTYPE
{
	enXVSB_UNARY = 0,
	enXVSB_BINARY
} enXVSB_OPTYPE;

typedef enum _enXVSB_ARYIDX_TYPE
{
	enXVSB_IDX_CONST = 0,
	enXVSB_IDX_VAR
} enXVSB_ARYIDX_TYPE;

typedef enum _enXVSB_ERRORCODE
{
    enXVSB_ERRNONE = 0,
    enXVSB_ERRSYNTAXERROR,					//General syntax error
    enXVSB_ERRVARNOTEXIST,					//The variable is not existed
    enXVSB_ERRNOCONTAINER,					//No container                  
    enXVSB_ERRARRYIDXNOTSIMPLEVAR,			//The array index variable is not supported
    enXVSB_ERRTOOMANYDATAINQ,				//Too many operand variables in the parser Q
    enXVSB_ERRTOOMANYOPERTORINQ,			//Too many operator variables in the parser Q
    enXVSB_ERRNOOPERTORINQ,					//Too no necessary operator variables in the parser Q
    enXVSB_ERRARYINDEXOUTOFRANGE,			//The array index out of range
    enXVSB_ERRNOLVNAME,						//The the left variable string of equation is empty
    enXVSB_ERRLVARNOTEXIST,					//The the left variable is not exist
    enXVSB_ERRLVARWRONGTYPE,				//The the left variable type not match to the data in variable tableis
    enXVSB_ERRRVARWRONGTYPE,				//The the right variable type not match to the data in variable tableis
    enXVSB_ERREXPRESSIONINVLIAD,			//The the expression is not valid
	enXVSB_ERREXPRESSIONNOTWORK,			//The the expression is not workable
	enXVSB_ERRFAILEDALLOCBUFFER,			//Failed to allocate buffer
	enXVSB_ERRFAILEDSTARTPARSE,				//Failed to initialize the parser
	enXVSB_ERRFAILEDCREATEEXP,				//Failed to parse out the expression
	enXVSB_ERRINVALIDSTRING,				//The string is not valid as the variable
}enXVSB_ERRORCODE;

typedef enum _enXVSB_PUTYPE
{
	enXVSB_PUNONE = -2,
	enXVSB_LINK = -1,
	enXVSB_PUSTART = 0,
	enXVSB_PUINIT,
	enXVSB_PUEND,
	enXVSB_PUSIMPLE,
	enXVSB_PUCOMPLEX,
	enXVSB_PULOGIC,
	enXVSB_PUCLASS,
	enXVSB_PUCOMMENT,
}enXVSB_PUTYPE;

typedef enum _enXVSB_EDITVAR
{
	enVAR_INPUTNEW,
	enVAR_INPUTEDIT,
	enVAR_BOTHNEW,
	enVAR_BOTHEDIT,
	enVAR_OUTPUTNEW,
	enVAR_OUTPUTEDIT,
	enVAR_LOCALNEW,
	enVAR_LOCALEDIT,
}enXVSB_EDITVAR;


////////////////////////////////////////////////////////
//  unXVSB_CPDATAVALUE          Data value.
////////////////////////////////////////////////////////
//??????????????????????????????????????????????????????
//??????????????????????????????????????????????????????
union unXVSB_CPDATAVALUE 
{
    __int64				m_Integer;
    double				m_Real;
    wchar_t				m_Character;
	wchar_t*			m_pString;
    unsigned char		m_Byte;
	bool				m_Bool;
};
//??????????????????????????????????????????????????????
//??????????????????????????????????????????????????????

typedef std::vector<int>	CVSB_IDList;


/*
typedef enum _enXVSB_TABORTCODE 
{
    enXVSB_ABORTNORMAL					 = 0,
    XTAC_ABORTINVALIDCOMMANDLINEARGS     = -1,
    XTAC_abortSourceFileOpenFailed       = -2,
    XTAC_abortIFormFileOpenFailed        = -3,
    XTAC_abortAssemblyFileOpenFailed     = -4,
    XTAC_abortTooManySyntaxErrors        = -5,
    XTAC_abortStackOverflow              = -6,
    XTAC_abortCodeSegmentOverflow        = -7,
    XTAC_abortNestingTooDeep             = -8,
    XTAC_abortRuntimeError               = -9,
    XTAC_abortUnimplementedFeature       = -10,
}enXVSB_TABORTCODE;
*/
/*
typedef enum _enXVSB_TERRORCODE
{
    XTEC_errNone,
    XTEC_errUnrecognizable,
    XTEC_errTooMany,
    XTEC_errUnexpectedEndOfFile,
    XTEC_errInvalidNumber,
    XTEC_errInvalidFraction,
    XTEC_errInvalidExponent,
    XTEC_errTooManyDigits,
    XTEC_errRealOutOfRange,
    XTEC_errIntegerOutOfRange,
    XTEC_errMissingRightParen,
    XTEC_errInvalidExpression,
    XTEC_errInvalidAssignment,
    XTEC_errMissingIdentifier,
    XTEC_errMissingColonEqual,
    XTEC_errUndefinedIdentifier,
    XTEC_errStackOverflow,
    XTEC_errInvalidStatement,
    XTEC_errUnexpectedToken,
    XTEC_errMissingSemicolon,
    XTEC_errMissingComma,
    XTEC_errMissingDO,
    XTEC_errMissingUNTIL,
    XTEC_errMissingTHEN,
    XTEC_errInvalidFORControl,
    XTEC_errMissingOF,
    XTEC_errInvalidConstant,
    XTEC_errMissingConstant,
    XTEC_errMissingColon,
    XTEC_errMissingEND,
    XTEC_errMissingTOorDOWNTO,
    XTEC_errRedefinedIdentifier,
    XTEC_errMissingEqual,
    XTEC_errInvalidType,
    XTEC_errNotATypeIdentifier,
    XTEC_errInvalidSubrangeType,
    XTEC_errNotAConstantIdentifier,
    XTEC_errMissingDotDot,
    XTEC_errIncompatibleTypes,
    XTEC_errInvalidTarget,
    XTEC_errInvalidIdentifierUsage,
    XTEC_errIncompatibleAssignment,
    XTEC_errMinGtMax,
    XTEC_errMissingLeftBracket,
    XTEC_errMissingRightBracket,
    XTEC_errInvalidIndexType,
    XTEC_errMissingBEGIN,
    XTEC_errMissingPeriod,
    XTEC_errTooManySubscripts,
    XTEC_errInvalidField,
    XTEC_errNestingTooDeep,
    XTEC_errMissingPROGRAM,
    XTEC_errAlreadyForwarded,
    XTEC_errWrongNumberOfParms,
    XTEC_errInvalidVarParm,
    XTEC_errNotARecordVariable,
    XTEC_errMissingVariable,
    XTEC_errCodeSegmentOverflow,
    XTEC_errUnimplementedFeature,
    XTEC_errWrongMarkSign,
}enXVSB_TERRORCODE;
*/
      

#endif