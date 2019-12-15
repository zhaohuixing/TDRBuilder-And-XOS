// Project: Visual System Builder
//
// File Name: xvsb_cmplutil.cpp
//
// Description: The implementation of the compiler operation utility class
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 05/20/2005	
//
// History:
// 1.    05/20/2005: Create	
//
#include "xvsb_cmplutil.h"

bool CVSB_CMPLUtility::IsSameLevel(enXVSB_OPERATION mType1, enXVSB_OPERATION mType2)
{
	int d1;
	int d2;

	if(mType1 == enXVSB_NONE)
		d1 = 0;
	else if(mType1 == enXVSB_PLUS || mType1 == enXVSB_MINUS)
		d1 = 1;
	else if(mType1 == enXVSB_TIME || mType1 == enXVSB_DIVIDE)
		d1 = 2;
	else
		d1 = 3;


	if(mType2 == enXVSB_NONE)
		d2 = 0;
	else if(mType2 == enXVSB_PLUS || mType2 == enXVSB_MINUS)
		d2 = 1;
	else if(mType2 == enXVSB_TIME || mType2 == enXVSB_DIVIDE)
		d2 = 2;
	else
		d2 = 3;

	return (d1 == d2);
}

int CVSB_CMPLUtility::LevelDifference(enXVSB_OPERATION mType1, enXVSB_OPERATION mType2)
{
	int d1;
	int d2;

	if(mType1 == enXVSB_NONE)
		d1 = 0;
	else if(mType1 == enXVSB_PLUS || mType1 == enXVSB_MINUS)
		d1 = 1;
	else if(mType1 == enXVSB_TIME || mType1 == enXVSB_DIVIDE)
		d1 = 2;
	else
		d1 = 3;


	if(mType2 == enXVSB_NONE)
		d2 = 0;
	else if(mType2 == enXVSB_PLUS || mType2 == enXVSB_MINUS)
		d2 = 1;
	else if(mType2 == enXVSB_TIME || mType2 == enXVSB_DIVIDE)
		d2 = 2;
	else
		d2 = 3;

	return (d2 - d1);
}

enXVSB_PRIORITY CVSB_CMPLUtility::GetOperationLevel(enXVSB_OPERATION mType)
{
	enXVSB_PRIORITY mLevel;

	if(mType == enXVSB_NONE) 
		mLevel = enXVSB_LEVEL_NONE;
	else if(mType == enXVSB_PLUS || mType == enXVSB_MINUS)
		mLevel = enXVSB_LEVEL1;
	else if(mType == enXVSB_TIME || mType == enXVSB_DIVIDE)
		mLevel = enXVSB_LEVEL2;
	else
		mLevel = enXVSB_LEVEL3;

	return mLevel;
}

bool CVSB_CMPLUtility::NeedParen(enXVSB_OPERATION op)
{
	bool bRet;
	bRet = (op == enXVSB_ABS ||
			op == enXVSB_SIN ||
			op == enXVSB_SINH||
			op == enXVSB_ASIN||
			op == enXVSB_CSC||	  //
			op == enXVSB_CSCH||  //
			op == enXVSB_COS||
			op == enXVSB_COSH||
			op == enXVSB_ACOS||
			op == enXVSB_SEC||	 //
			op == enXVSB_SECH|| //
			op == enXVSB_TAN||
			op == enXVSB_TANH||
			op == enXVSB_ATAN||
			op == enXVSB_CTG||	 //
			op == enXVSB_CTGH|| //
			op == enXVSB_ACTG|| //
			op == enXVSB_EXP||
			op == enXVSB_LN||
			op == enXVSB_LOG10||
			op == enXVSB_LOG||
			op == enXVSB_SQRT||
			op == enXVSB_POW||
			op == enXVSB_ROOT||
			op == enXVSB_FACTORIAL||
			op == enXVSB_HYPOT||
			op == enXVSB_ARG||
			op == enXVSB_POLAR||
			op == enXVSB_FMOD ||
			op == enXVSB_FMOD2 ||
			op == enXVSB_FRACTION||
			op == enXVSB_MOD2 ||
			op == enXVSB_MOD);		// Modulus

	return bRet;
}		
