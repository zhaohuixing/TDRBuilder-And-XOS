// Date: 06/05/2004	
#include "xos_data.h"


double Signed(double d)
{
	if(d < 0.0)
		return -1.0;
	else
		return 1.0;
}

CXOS_Data CXOS_Data::Hypot(const CXOS_Data& d)
{
	if(m_enType == enXOS_VALUE)
		return CXOS_Data(sqrt(GetLength()*GetLength() + d.GetLength()*d.GetLength()));
	else
		return CXOS_Data(0.0);
}

CXOS_Data CXOS_Data::Abs(void)
{
	if(m_enType == enXOS_VALUE)
		return CXOS_Data(sqrt(m_dReal*m_dReal + m_dImagery*m_dImagery));
	else
		return CXOS_Data(0.0);
}

CXOS_Data CXOS_Data::Arg(void)
{
	if(m_enType == enXOS_VALUE)
	{
		if(m_dReal == 0.0)
		{
			return CXOS_Data(atan(Signed(m_dImagery)*XOS_MAX));
		}
		else
		{
			return CXOS_Data(atan(m_dImagery/m_dReal));
		}
	}
	else
	{
		return CXOS_Data(0.0);
	}
}

CXOS_Data CXOS_Data::Polar(void)
{
	if(m_enType == enXOS_VALUE)
	{
		double dM = sqrt(m_dReal*m_dReal + m_dImagery*m_dImagery);
		double dA = (m_dReal == 0.0) ? atan(Signed(m_dImagery)*XOS_MAX):atan(m_dImagery/m_dReal);

		return CXOS_Data(dM, dA);
	}
	else
	{
		return CXOS_Data(0.0);
	}
}

CXOS_Data CXOS_Data::Sin(void)
{
	double dReal = 0.0;
	double dImagery = 0.0;
	
	if(m_enType == enXOS_VALUE)
	{
		if(IsReal())
		{
			dReal = sin(m_dReal);
			dImagery = 0.0;
		}
		else
		{
			dReal = sin(m_dReal) * cosh(m_dImagery);
			dImagery = cos(m_dReal) * sinh(m_dImagery);
		}
	}

	return CXOS_Data(dReal, dImagery);
}

CXOS_Data CXOS_Data::SinH(void)
{
	double dReal = 0.0;
	double dImagery = 0.0;
	
	if(m_enType == enXOS_VALUE)
	{
		if(IsReal())
		{
			dReal = sinh(m_dReal);
			dImagery = 0.0;
		}
		else
		{
			dReal = sinh(m_dReal) * cos(m_dImagery);
			dImagery = cosh(m_dReal) * sin(m_dImagery);
		}
	}
	return CXOS_Data(dReal, dImagery);
}

CXOS_Data CXOS_Data::Cos(void)
{
	double dReal = 0.0;
	double dImagery = 0.0;
	
	if(m_enType == enXOS_VALUE)
	{
		if(IsReal())
		{
			dReal = cos(m_dReal);
			dImagery = 0.0;
		}
		else
		{
			dReal = cos(m_dReal) * cosh(m_dImagery);
			dImagery = -(sin(m_dReal) * sinh(m_dImagery));
		}
	}
	return CXOS_Data(dReal, dImagery);
}

CXOS_Data CXOS_Data::CosH(void)
{
	double dReal = 0.0;
	double dImagery = 0.0;
	
	if(m_enType == enXOS_VALUE)
	{
		if(IsReal())
		{
			dReal = cosh(m_dReal);
			dImagery = 0.0;
		}
		else
		{
			dReal = cosh(m_dReal) * cos(m_dImagery);
			dImagery = sinh(m_dReal) * sin(m_dImagery);
		}
	}
	return CXOS_Data(dReal, dImagery);
}

CXOS_Data CXOS_Data::Tan(void)
{
	double dReal = 0.0;
	double dImagery = 0.0;
	
	if(m_enType == enXOS_VALUE)
	{
		if(IsReal())
		{
			dReal = tan(m_dReal);
			dImagery = 0.0;
		}
		else
		{
			double dRe2 = 2.0 * m_dReal;
			double dIm2 = 2.0 * m_dImagery;
			double dTemp = cos(dRe2) + cosh(dIm2);

			if(abs(dTemp) < XOS_EPSILON)
			{
				if(0.0 < Signed(sin(dRe2)))
				{
					if(abs(sin(dRe2)) < XOS_EPSILON)
					{
						dReal = Signed(dTemp);
					}
					else
					{
						if(0.0 < Signed(dTemp))
							dReal = XOS_MAX;
						else
							dReal = XOS_NMAX;
					}
				}
				else 
				{
					if(abs(sin(dRe2)) < XOS_EPSILON)
					{
						dReal = -Signed(dTemp);
					}
					else
					{
						if(0.0 < Signed(dTemp))
							dReal = XOS_NMAX;
						else
							dReal = XOS_MAX;
					}
				}

				if(0.0 < Signed(sinh(dIm2)))
				{
					if(abs(sinh(dIm2)) < XOS_EPSILON)
					{
						dImagery = Signed(dTemp);
					}
					else
					{
						if(0.0 < Signed(dTemp))
							dImagery = XOS_MAX;
						else
							dImagery = XOS_NMAX;
					}
				}
				else 
				{
					if(abs(sinh(dIm2)) < XOS_EPSILON)
					{
						dImagery = -Signed(dTemp);
					}
					else
					{
						if(0.0 < Signed(dTemp))
							dImagery = XOS_NMAX;
						else
							dImagery = XOS_MAX;
					}
				}
			}
			else
			{
				dReal = sin(dRe2)/dTemp;
				dImagery = sinh(dIm2)/dTemp;
			}
		}
	}
	return CXOS_Data(dReal, dImagery);
}

CXOS_Data CXOS_Data::TanH(void)
{
	double dReal = 0.0;
	double dImagery = 0.0;
	
	if(m_enType == enXOS_VALUE)
	{
		if(IsReal())
		{
			dReal = tanh(m_dReal);
			dImagery = 0.0;
		}
		else
		{
			double dRe2 = 2.0 * m_dReal;
			double dIm2 = 2.0 * m_dImagery;
			double dTemp = cosh(dRe2) + cos(dIm2);

			if(abs(dTemp) < XOS_EPSILON)
			{
				if(0.0 < Signed(sinh(dRe2)))
				{
					if(abs(sinh(dRe2)) < XOS_EPSILON)
					{
						dReal = Signed(dTemp);
					}
					else
					{
						if(0.0 < Signed(dTemp))
							dReal = XOS_MAX;
						else
							dReal = XOS_NMAX;
					}
				}
				else 
				{
					if(abs(sinh(dRe2)) < XOS_EPSILON)
					{
						dReal = -Signed(dTemp);
					}
					else
					{
						if(0.0 < Signed(dTemp))
							dReal = XOS_NMAX;
						else
							dReal = XOS_MAX;
					}
				}

				if(0.0 < Signed(sin(dIm2)))
				{
					if(abs(sin(dIm2)) < XOS_EPSILON)
					{
						dImagery = Signed(dTemp);
					}
					else
					{
						if(0.0 < Signed(dTemp))
							dImagery = XOS_MAX;
						else
							dImagery = XOS_NMAX;
					}
				}
				else 
				{
					if(abs(sin(dIm2)) < XOS_EPSILON)
					{
						dImagery = -Signed(dTemp);
					}
					else
					{
						if(0.0 < Signed(dTemp))
							dImagery = XOS_NMAX;
						else
							dImagery = XOS_MAX;
					}
				}
			}
			else
			{
				dReal = sinh(dRe2)/dTemp;
				dImagery = sin(dIm2)/dTemp;
			}
		}
	}

	return CXOS_Data(dReal, dImagery);
}

CXOS_Data CXOS_Data::CTan(void)
{
	CXOS_Data dTemp = Tan();
	return 1.0/dTemp;
}

CXOS_Data CXOS_Data::CTanH(void)
{
	CXOS_Data dTemp = TanH();
	return 1.0/dTemp;
}

CXOS_Data CXOS_Data::Sec(void)
{
	return 1.0/Cos();
}

CXOS_Data CXOS_Data::SecH(void)
{
	return 1.0/CosH();
}

CXOS_Data CXOS_Data::Csc(void)
{
	return 1.0/Sin();
}

CXOS_Data CXOS_Data::CscH(void)
{
	return 1.0/SinH();
}

//////////////////////////
// Updated future
//////////////////////////
CXOS_Data CXOS_Data::ASin(void)
{
	return CXOS_Data(asin(m_dReal));
}

//////////////////////////
// Updated future
//////////////////////////
CXOS_Data CXOS_Data::ACos(void)
{
	return CXOS_Data(acos(m_dReal));
}

//////////////////////////
// Updated future
//////////////////////////
CXOS_Data CXOS_Data::ATan(void)
{
	return CXOS_Data(atan(m_dReal));
}

CXOS_Data CXOS_Data::ATan2(void)
{
	if(m_dReal == 0.0)
	{
		return CXOS_Data(atan(XOS_MAX*Signed(m_dImagery)));
	}
	else
	{
		return CXOS_Data(atan(m_dImagery/m_dReal));
	}
}

//////////////////////////
// Updated future
//////////////////////////
CXOS_Data CXOS_Data::ACTan(void)
{
	CXOS_Data d = 1.0/(*this);
	return d.ATan();
}

CXOS_Data CXOS_Data::Sqrt(void)
{
	if(m_enType != enXOS_VALUE)
		return CXOS_Data(0.0);

	CXOS_Data temp = Pow(0.5);
	return temp;
}

CXOS_Data CXOS_Data::Exp(void)
{
	if(m_enType != enXOS_VALUE)
		return CXOS_Data(0.0);

	double dExp = exp(m_dReal); 
	double dReal = dExp*cos(m_dImagery);
	double dImagery = dExp*sin(m_dImagery);

	return CXOS_Data(dReal, dImagery);
}

CXOS_Data CXOS_Data::Ln(void)
{
	if(m_enType != enXOS_VALUE)
		return CXOS_Data(0.0);

	double dReal = log(GetLength());
	double dImagery = atan2(m_dImagery, m_dReal);

	return CXOS_Data(dReal, dImagery);
}

CXOS_Data CXOS_Data::Log10(void)
{
	if(m_enType != enXOS_VALUE)
		return CXOS_Data(0.0);

	double dReal = log10(GetLength());
	double dImagery = atan2(m_dImagery, m_dReal)/log(10.0);

	return CXOS_Data(dReal, dImagery);
}

CXOS_Data CXOS_Data::Pow(double d)
{
	if(m_enType != enXOS_VALUE)
		return CXOS_Data(0.0);

	double dLr = log(GetLength());
	double dLi = atan2(m_dImagery, m_dReal);
	double dX = exp(dLr*d);
	double dY = dLi*d;

	return CXOS_Data(dX*cos(dY), dX*sin(dY));
}  

CXOS_Data CXOS_Data::Pow(const CXOS_Data& d)
{
	if(m_enType != enXOS_VALUE)
		return CXOS_Data(0.0);

	double dLr = log(GetLength());
	double dLi = atan2(m_dImagery, m_dReal);
	double dX = exp(dLr*d.m_dReal - dLi*d.m_dImagery);
	double dY = dLi*d.m_dReal + dLr*d.m_dImagery;

	return CXOS_Data(dX*cos(dY), dX*sin(dY));
}

CXOS_Data CXOS_Data::Root(double d)
{
	if(m_enType != enXOS_VALUE)
		return CXOS_Data(0.0);

	if(d == 0.0)
		return CXOS_Data(XOS_MAX);

	return Pow(1.0/d);
}

CXOS_Data CXOS_Data::Root(const CXOS_Data& d)
{
	if(m_enType != enXOS_VALUE)
		return CXOS_Data(0.0);

	if(d.GetLength() == 0.0)
		return CXOS_Data(XOS_MAX);

	CXOS_Data temp = 1.0/d;
	return Pow(temp);
}

CXOS_Data CXOS_Data::Factorial(void)
{
	if(m_enType != enXOS_VALUE || !IsReal())
		return CXOS_Data(0.0);

	double dRet;
	double fract, integ;
	
	fract = modf(m_dReal, &integ);   
	if(fract == 0.0)
	{
		dRet = (double)CXOS_Data::FactorialL((long)integ);
	}
	else
	{
		dRet = pow(m_dReal, m_dReal)*sqrt(XOS_2PI*m_dReal)*(1.0+1.0/(12.0*m_dReal))/pow(XOS_EULA, m_dReal);
	}

	return CXOS_Data(dRet);
}

long CXOS_Data::FactorialL(long n)
{
	long nRet = 1;
	long ndx;
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
