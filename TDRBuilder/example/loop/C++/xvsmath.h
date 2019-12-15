#ifndef __XVSMATH_H__
#define __XVSMATH_H__

extern "C"
{
	double lg (double d1, double d2);
	double ln (double d1);
	double tg(double d);
	double tgh(double d);
	double atg(double d);
	double ctg(double d);
	double ctgh(double d);
	double actg(double d);
	double csc(double d);
	double csch(double d);
	double sec(double d);
	double sech(double d);
	double root(double d1, double d2);
	double hypot(double d1, double d2);
	double arg(double d);
	double polar(double d);
	double factorial(double d);
	double minteger(double d);
	double fraction(double d);
	double modulus(double d1, double d2);
	double remainder(double d1, double d2);
	double rfraction(double d1, double d2);
};

#endif