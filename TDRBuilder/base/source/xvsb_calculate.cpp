#include "xvsb_calculate.h"

int CVSB_Calculate::GetBiggest(int n1, int n2)
{
	if (n2 <= n1)	
		return n1;
	if (n2 > n1)	
		return n2;
	return -1; // equal
}

float CVSB_Calculate::GetSmallestF(float f1, float f2)
{
	if (f1 <= f2)	
		return f1;
	if (f2 < f1)	
		return f2;
	return -1.0f; // equal
}
