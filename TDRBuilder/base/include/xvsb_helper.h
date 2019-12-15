// Project: Visual System Builder
//
// File Name: xvsb_helper.h
//
// Description: The helper functions
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
#ifndef __XVSB_HELPER_H__
#define __XVSB_HELPER_H__

#include <math.h>
#include <assert.h>
#include "xvsb_macro.h"

extern "C"
{
	inline double XVSB_Signed(double d)
	{
		if(d < 0.0)
			return -1.0;
		else
			return 1.0;
	}

	inline double XVSB_Hypot(double d1, double d2)
	{
		double d;
		d = sqrt(d1*d1 + d2*d2);
		return d;
	}

	inline __int64 XVSB_Factorial(__int64 n)
	{
		__int64 nRet = 1;
		__int64 ndx;
		if(n == 0)
			return nRet;

		if(0 < n)
		{
			for(ndx = 1; ndx <= n; ndx++)
			{
				nRet *= ndx;
			}
		}
		else
		{
			for(ndx = n; ndx <= -1; ndx++)
			{
				nRet *= ndx;
			}
		}
		return nRet;
	}

	inline double XVSB_FactorialF(double n)
	{
		double nRet = 1.0;
		double ndx;
		if(n == 0.0)
			return nRet;

		if(0.0 < n)
		{
			for(ndx = 1.0; ndx <= n;)
			{
				nRet *= ndx;
				ndx += 1.0;
			}
		}
		else
		{
			for(ndx = n; ndx <= -1.0;)
			{
				nRet *= ndx;
				ndx += 1.0;
			}
		}
		return nRet;
	}

	inline double XVSB_Abs_Fraction(double d)
	{
		double fract, integ;
	
		fract = modf(d, &integ);   

		return abs(fract);
	}

	inline int XVSB_GetDecimalCount(double d)
	{
		double fract;
		double dTemp;
		int	   nTemp;
		int n = 0;
	
		fract = XVSB_Abs_Fraction(d);   
		if(abs(fract - XVSM_EPSILON) <= XVSM_EPSILON)
			return (n+1);

		for(n = 1; n < 32; n++)
		{
			dTemp = fract*pow(10.0, n);
			nTemp = (int)(dTemp);
			dTemp = ((double)nTemp)/(pow(10.0, n));
			fract = fract - dTemp;   
			if(abs(fract - XVSM_EPSILON) <= XVSM_EPSILON)
				return (n+1);
		}

		return (n+1);
	}

	inline void XVSB_Assert(bool bOK)
	{
		assert(bOK);
	}
};

#endif