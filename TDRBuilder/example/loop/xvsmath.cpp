#include <math.h>
#include <stdio.h>
#include "xvsmath.h"

#define XVSMMAX		1.7976931348623158e+308
#define XVSMEULA    2.718281828459045235360287471352662497757
#define XVSM2PI 	6.28318530717958647692

double lg (double d1, double d2)
{
	double d;
	double dLog = log(d2);

	if(dLog != 0.0)
	{
		d = log(d1)/dLog;
	}
	else
	{
		double dTemp = log(d1);
		if(dTemp == 0.0)
			d = 1.0;
		else if(dTemp < 0)
			d = -1.0*(XVSMMAX-1.0);
		else
			d = XVSMMAX;
	}

	return d;
}

double ln (double d1)
{
	double d = log(d1);

	return d;
}

double tg(double d)
{
	double dTemp = tan(d);
	return dTemp;
}

double tgh(double d)
{
	double dTemp = tanh(d);
	return dTemp;
}

double atg(double d)
{
	double dTemp = atan(d);
	return dTemp;
}

double ctg(double d)
{
	double dTan = tan(d);
	double dTemp;
	if(dTan != 0.0)
	{
		dTemp = 1.0/dTan;
	}
	else
	{
		dTemp = XVSMMAX;
	}

	return dTemp;
}

double ctgh(double d)
{
	double dTan = tanh(d);
	double dTemp;
	if(dTan != 0.0)
	{
		dTemp = 1.0/dTan;
	}
	else
	{
		dTemp = XVSMMAX;
	}

	return dTemp;
}

double actg(double d)
{
	double dTemp;
	if(d != 0.0)
	{
		dTemp = atg(1.0/d);
	}
	else
	{
		dTemp = atg(XVSMMAX);
	}

	return dTemp;
}

double csc(double d)
{
	double dSin = sin(d);
	double dTemp;
	if(dSin != 0.0)
	{
		dTemp = 1.0/dSin;
	}
	else
	{
		dTemp = XVSMMAX;
	}

	return dTemp;
}

double csch(double d)
{
	double dSin = sinh(d);
	double dTemp;
	if(dSin != 0.0)
	{
		dTemp = 1.0/dSin;
	}
	else
	{
		dTemp = XVSMMAX;
	}

	return dTemp;
}

double sec(double d)
{
	double dCos = cos(d);
	double dTemp;
	if(dCos != 0.0)
	{
		dTemp = 1.0/dCos;
	}
	else
	{
		dTemp = XVSMMAX;
	}

	return dTemp;
}

double sech(double d)
{
	double dCos = cosh(d);
	double dTemp;
	if(dCos != 0.0)
	{
		dTemp = 1.0/dCos;
	}
	else
	{
		dTemp = XVSMMAX;
	}

	return dTemp;
}

double root(double d1, double d2)
{
	double d;
	double dE;
	if(d2 == 0.0)
		dE = XVSMMAX;
	else 
		dE = 1.0/d2;

	d = pow(d1, dE);

	return d;
}

double hypot(double d1, double d2)
{
	double d;
	d = sqrt(d1*d1+d2*d2);
	return d;
}

//For complex only
double arg(double d)
{
	return 0;
}

//For complex only
double polar(double d)
{
	return abs(d);
}

double _xfactorial(double n)
{
	double nRet = 1.0;
	double ndx;
	if(n == 0)
		return nRet;

	if(0.0 < n)
	{
		for(ndx = 1.0; ndx <= n; )
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

double factorial(double d)
{
	double dTemp;
	double fract, integ;
	
	fract = modf(d, &integ);   
	if(fract == 0.0)
	{
		dTemp = _xfactorial(integ);
	}
	else
	{
		dTemp = pow(d, d)*sqrt(XVSM2PI*d)*(1.0+1.0/(12.0*d))/pow(XVSMEULA, d);
	}

	return dTemp;
}

double minteger(double d)
{
	double dInt;
	modf(d, &dInt); 
	return dInt;
}

double fraction(double d)
{
	double dInt, dRem;
	dRem = modf(d, &dInt); 
	return dRem;
}

double modulus(double d1, double d2)
{
	double dInt;
	double dTemp;
	if(d2 == 0.0)
		dTemp = XVSMMAX;
	else
		dTemp = d1 / d2;
	modf(dTemp, &dInt); 

	return dInt;
}

double remainder(double d1, double d2)
{
	double dTemp;
	dTemp = fmod(d1, d2);
	return dTemp;
}

double rfraction(double d1, double d2)
{
	double dTemp;
	if(d2 == 0.0)
		dTemp = XVSMMAX;
	else
		dTemp = d1 / d2;
	
	double dInt, dRem;
	dRem = modf(dTemp, &dInt); 
	return dRem;
}