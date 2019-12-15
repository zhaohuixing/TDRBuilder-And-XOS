// Project: Visual System Builder
//
// File Name: xvsb_macro.h
//
// Description: The definition of the macros for all
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
#ifndef __XVSB_MACRO_H__
#define __XVSB_MACRO_H__

#ifdef WIN32
#include <float.h>
#endif

#define XVSM_NS_GENERIC			L"XVS_System"
#define XVSM_NS_OWNERBASE		L"CVSB_OwnerBase"
#define XVSM_NS_MODULE			L"CVSB_Module"
#define XVSM_TYPE_DATA			L"XVS_DataType"
#define XVSM_TYPE_CLASS			L"XVS_ClassType"
#define XVSM_TYPE_FLOAT			L"CVSB_Float"
#define XVSM_TYPE_INTEGER		L"CVSB_Integer"
#define XVSM_TYPE_BYTE			L"CVSB_Byte"
#define XVSM_TYPE_CHAR			L"CVSB_Char"
#define XVSM_TYPE_BOOL			L"CVSB_Bool"
#define XVSM_TYPE_ARRAY			L"CVSB_Array"

#define XVSM_PUSTR_ENTRY		L"Entry"
#define XVSM_PUSTR_END			L"Exit"
#define XVSM_PUSTR_INIT			L"Initialize"
#define XVSM_PUSTR_PPU			L"Processor"
#define XVSM_PUSTR_LPU			L"?"
#define XVSM_PUSTR_LPUCMP		L"Compare"
#define XVSM_PUSTR_LPUYES		L"Yes"
#define XVSM_PUSTR_LPUNO		L"No"
#define XVSM_PUSTR_COMMENT		L"Comment"
#define XVSM_PUSTR_CLASS		L"Class"
#define XVSM_PUSTR_CPU			L"Sub-Module"


#define XVSM_FACTORIALSIGN		L"factorial"

#define XVSM_SHEET1				L"Sheet1"; 
#define XVSM_FIRSTLETTER		L"A"; 

#define XVSM_INPUTVARTITLE		L"Input variables:"

#ifndef XVSM_EULA
#define XVSM_EULA    2.718281828459045235360287471352662497757
#endif

#ifndef XVSM_PI
#define XVSM_PI 		3.14159265358979323846
#endif

#ifndef XVSM_HALFPI
#define XVSM_HALFPI 	1.57079632679489661923
#endif

#ifndef XVSM_2PI
#define XVSM_2PI 	6.28318530717958647692
#endif

#ifndef XVSM_GAMMA
#define XVSM_GAMMA 	0.577215664901532860606512090082402431042
#endif

#ifndef XVSM_MAX
#ifdef WIN32
#define XVSM_MAX		DBL_MAX
#else
#define XVSM_MAX		1.7976931348623158e+308
#endif
#endif

#ifndef XVSM_MIN
#ifdef WIN32
#define XVSM_MIN		DBL_MIN
#else
#define XVSM_MIN		2.2250738585072014e-308
#endif
#endif

#ifndef XVSM_NMAX
#ifdef WIN32
#define XVSM_NMAX	(1.0-DBL_MAX)
#else
#define XVSM_NMAX	-1.7976931348623157e+308
#endif
#endif

#ifndef XVSM_EPSILON
#ifdef WIN32
#define XVSM_EPSILON   DBL_EPSILON
#else
#define XVSM_EPSILON   2.2204460492503131e-016
#endif
#endif

#ifndef XVSM_MAXBUF
#define XVSM_MAXBUF			   2560	
#endif

#define XVSM_PU_DEFAULT			0
#define XVSM_PU_ERROR			-1
#define XVSM_PU_START			-2
#define XVSM_PU_INIT			-3
#define XVSM_PU_END				-4
#define XVSM_PU_LINK_FIRST		-5

#define XVSM_BTRUE_STR			L"true"
#define XVSM_BFALSE_STR			L"false"


#define XVSM_DT_TYPECOUNT		6
#define XVSM_DT_ERROR			-1
#define XVSM_DT_FLOAT			0
#define XVSM_DT_INTEGER			1
#define XVSM_DT_BYTE			2
#define XVSM_DT_BOOL			3
#define XVSM_DT_ARRAY			4
#define XVSM_DT_CHAR			5
#define XVSM_DT_STRING			6
#define XVSM_DT_CLASS			7

#define XVSM_VERSION			2.0

#endif