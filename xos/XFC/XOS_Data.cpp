// Date: 06/04/2004	
#include "xos_data.h"
#include "xos_num.h"

CXOS_Data::CXOS_Data(void)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Data";
	m_szName = L"";
	m_dReal = 0.0;
	m_dImagery = 0.0;
	m_enType = enXOS_VALUE;
	m_enParType = enXOS_CONSTANT;
}

CXOS_Data::CXOS_Data(enXOS_PARAMTYPE enParType)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Data";
	m_szName = L"";
	m_dReal = 0.0;
	m_dImagery = 0.0;
	m_enType = enXOS_VALUE;
	m_enParType = enParType;
}

CXOS_Data::CXOS_Data(std::wstring& szName, enXOS_VARTYPE enType, enXOS_PARAMTYPE enParType)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Data";
	m_szName = szName;
	m_dReal = 0.0;
	m_dImagery = 0.0;
	m_enType = enType;
	m_enParType = enParType;
}

CXOS_Data::CXOS_Data(const wchar_t* szName, enXOS_VARTYPE enType, enXOS_PARAMTYPE enParType)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Data";
	m_szName = szName;
	m_dReal = 0.0;
	m_dImagery = 0.0;
	m_enType = enType;
	m_enParType = enParType;
}

CXOS_Data::CXOS_Data(double dReal)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Data";
	wchar_t sTemp[256];
	memset(sTemp, 0, 256*sizeof(wchar_t));
	swprintf(sTemp, L"%f", dReal);
	m_szName = sTemp;
	m_dReal = dReal;
	m_dImagery = 0.0;
	m_enType = enXOS_VALUE;
	m_enParType = enXOS_CONSTANT;
}

CXOS_Data::CXOS_Data(const wchar_t* szName, double dReal)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Data";
	m_szName = szName;
	m_dReal = dReal;
	m_dImagery = 0.0;
	m_enType = enXOS_VALUE;
	m_enParType = enXOS_CONSTANT;
}

CXOS_Data::CXOS_Data(std::wstring& szName, double dReal)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Data";
	m_szName = szName;
	m_dReal = dReal;
	m_dImagery = 0.0;
	m_enType = enXOS_VALUE;
	m_enParType = enXOS_CONSTANT;
}

CXOS_Data::CXOS_Data(double dReal, double dImagery)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Data";
	wchar_t sTemp[256];
	memset(sTemp, 0, 256*sizeof(wchar_t));
	if(dImagery == 0.0)
		swprintf(sTemp, L"%f", dReal);
	else
		swprintf(sTemp, L"%f+i%f", dReal, dImagery);
	m_szName = sTemp;
	m_dReal = dReal;
	m_dImagery = dImagery;
	m_enType = enXOS_VALUE;
	m_enParType = enXOS_CONSTANT;
}

CXOS_Data::CXOS_Data(const wchar_t* szName, double dReal, double dImagery)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Data";
	m_szName = szName;
	m_dReal = dReal;
	m_dImagery = dImagery;
	m_enType = enXOS_VALUE;
	m_enParType = enXOS_CONSTANT;
}

CXOS_Data::CXOS_Data(std::wstring& szName, double dReal, double dImagery)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Data";
	m_szName = szName;
	m_dReal = dReal;
	m_dImagery = dImagery;
	m_enType = enXOS_VALUE;
	m_enParType = enXOS_CONSTANT;
}

CXOS_Data::CXOS_Data(const CXOS_Data& osData, enXOS_PARAMTYPE enParType)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Data";
	m_szName = osData.m_szName;
	m_dReal = osData.m_dReal;
	m_dImagery = osData.m_dImagery;
	m_enType = osData.m_enType;
	m_enParType = enParType;
}

CXOS_Data::~CXOS_Data(void)
{
}

bool CXOS_Data::Set(CXOS_ClassObject* pObj)
{
	bool bRet = false;

	if(pObj && CXOS_Data::TypeCheck(pObj->GetClassStr()))
	{
		bRet = true;
		m_dReal = ((CXOS_Data*)pObj)->m_dReal;
		m_dImagery = ((CXOS_Data*)pObj)->m_dImagery;
		m_enType = ((CXOS_Data*)pObj)->m_enType;
	}

	return bRet;
}

void CXOS_Data::Set(const CXOS_Data& vmData)  
{
	m_dReal = vmData.m_dReal;
	m_dImagery = vmData.m_dImagery;
	m_enType = vmData.m_enType;
}

void CXOS_Data::Set(double dVal)  
{
	m_dReal = dVal;
	m_dImagery = 0.0;
	m_enType = enXOS_VALUE;
}

void CXOS_Data::Set(double dReal, double dImagery)
{
	m_dReal = dReal;
	m_dImagery = dImagery;
	m_enType = enXOS_VALUE;
}

void CXOS_Data::Get(CXOS_Data& vmData)  
{
	vmData.m_dReal = m_dReal;
	vmData.m_dImagery = m_dImagery;
	vmData.m_enType = m_enType;
}

void CXOS_Data::Get(double& dVal)  
{
	dVal = m_dReal;	
}

void CXOS_Data::Get(double& dReal, double& dImagery)  
{
	dReal = m_dReal;	
	dImagery = m_dImagery;
}

double CXOS_Data::GetLength(void) const
{
	double d = 0.0;
	if(m_enType == enXOS_VALUE)
	{
		if(m_dImagery == 0.0)
		{
			d = (double)abs(m_dReal);
		}
		else
		{
			d = (double)sqrt(m_dReal*m_dReal + m_dImagery*m_dImagery);
		}
	}
	return d;
}

bool CXOS_Data::IsEqual(const CXOS_Data& d)
{
	bool bRet = false;
	if(m_enType != d.m_enType)
	{
		return bRet;
	}
	else
	{
		if(m_enType == enXOS_VALUE)
		{
			bRet = (m_dReal == d.m_dReal);

			if(bRet)
				bRet = (m_dImagery == d.m_dImagery);
		}
		else
		{
			bRet = (m_szName == d.m_szName);
		}
	}

	return bRet;
}

bool CXOS_Data::IsLarge(const CXOS_Data& d)
{
	bool bRet = false;
	if(m_enType != d.m_enType)
	{
		bRet = (d.m_enType < m_enType);
	}
	else
	{
		if(m_enType == enXOS_VALUE)
		{
			if(m_dImagery == 0.0 && d.m_dImagery == 0.0)
			{
				bRet = (d.m_dReal < m_dReal);
			}
			else
			{
				double dL1 = GetLength();
				double dL2 = d.GetLength();
				bRet = (dL2 < dL1);
			}
		}
		else
		{
			bRet = (d.m_szName < m_szName);
		}
	}

	return bRet;
}

bool CXOS_Data::IsLargeEqual(const CXOS_Data& d)
{
	bool bRet = false;
	if(m_enType != d.m_enType)
	{
		bRet = (d.m_enType <= m_enType);
	}
	else
	{
		if(m_enType == enXOS_VALUE)
		{
			if(m_dImagery == 0.0 && d.m_dImagery == 0.0)
			{
				bRet = (d.m_dReal <= m_dReal);
			}
			else
			{
				double dL1 = GetLength();
				double dL2 = d.GetLength();
				bRet = (dL2 <= dL1);
			}
		}
		else
		{
			bRet = (d.m_szName <= m_szName);
		}
	}

	return bRet;
}

bool CXOS_Data::IsSmall(const CXOS_Data& d)
{
	bool bRet = false;
	if(m_enType != d.m_enType)
	{
		bRet = (m_enType < d.m_enType);
	}
	else
	{
		if(m_enType == enXOS_VALUE)
		{
			if(m_dImagery == 0.0 && d.m_dImagery == 0.0)
			{
				bRet = (m_dReal < d.m_dReal);
			}
			else
			{
				double dL1 = GetLength();
				double dL2 = d.GetLength();
				bRet = (dL1 < dL2);
			}
		}
		else
		{
			bRet = (m_szName < d.m_szName);
		}
	}

	return bRet;
}

bool CXOS_Data::IsSmallEqual(const CXOS_Data& d)
{
	bool bRet = false;
	if(m_enType != d.m_enType)
	{
		bRet = (m_enType <= d.m_enType);
	}
	else
	{
		if(m_enType == enXOS_VALUE)
		{
			if(m_dImagery == 0.0 && d.m_dImagery == 0.0)
			{
				bRet = (m_dReal <= d.m_dReal);
			}
			else
			{
				double dL1 = GetLength();
				double dL2 = d.GetLength();
				bRet = (dL1 <= dL2);
			}
		}
		else
		{
			bRet = (m_szName <= d.m_szName);
		}
	}

	return bRet;
}

CXOS_Data& CXOS_Data::operator = (const CXOS_Data& data)
{
	m_dReal = data.m_dReal;
	m_dImagery = data.m_dImagery;
	m_enType = data.m_enType;
	m_szName = data.m_szName;

	return *this;
}

CXOS_Data& CXOS_Data::operator = (const CXOS_Number& data)
{
	m_dReal = (double)data.m_nNumber;
	m_dImagery = 0.0;
	m_enType = enXOS_VALUE;

	return *this;
}

CXOS_Data& CXOS_Data::operator = (double dv)
{
	m_dReal = dv;
	m_dImagery = 0.0;
	m_enType = enXOS_VALUE;

	return *this;
}

CXOS_Data& CXOS_Data::operator = (long nv)
{
	m_dReal = (double)nv;
	m_dImagery = 0.0;
	m_enType = enXOS_VALUE;

	return *this;
}

CXOS_Data& CXOS_Data::operator += (const CXOS_Data& data)
{
	*this = *this + data;

	return *this;
}

CXOS_Data& CXOS_Data::operator -= (const CXOS_Data& data)
{
	*this = *this - data;

	return *this;
}

CXOS_Data& CXOS_Data::operator *= (const CXOS_Data& data)
{
	*this = *this * data;

	return *this;
}

CXOS_Data& CXOS_Data::operator /= (const CXOS_Data& data)
{
	*this = *this / data;

	return *this;
}

CXOS_Data& CXOS_Data::operator += (double dv)
{
	*this = *this + dv;

	return *this;
}

CXOS_Data& CXOS_Data::operator -= (double dv)
{
	*this = *this - dv;

	return *this;
}

CXOS_Data& CXOS_Data::operator *= (double dv)
{
	*this = *this * dv;

	return *this;
}

CXOS_Data& CXOS_Data::operator /= (double dv)
{
	*this = *this / dv;

	return *this;
}

CXOS_Data& CXOS_Data::operator ++ (void)
{
	if(IsReal())
	{
		m_dReal++;
	}
	else
	{
		m_dReal++;
		m_dImagery++;
	}

	return *this;
}

CXOS_Data CXOS_Data::operator ++ (int)
{
	CXOS_Data temp(*this);
	operator++();
	return temp;
}

CXOS_Data& CXOS_Data::operator -- (void)
{
	if(IsReal())
	{
		m_dReal--;
	}
	else
	{
		m_dReal--;
		m_dImagery--;
	}

	return *this;
}

CXOS_Data CXOS_Data::operator -- (int)
{
	CXOS_Data temp(*this);
	operator--();
	return temp;
}

CXOS_Data::operator double (void)
{
	if(m_enType == enXOS_VALUE)
	{
		if(abs(m_dImagery) < XOS_EPSILON)
		{
			return m_dReal;
		}
		else
		{
			return GetLength();
		}
	}
	else
	{
		return 0.0;
	}
}

CXOS_Data::operator long (void)
{
	if(m_enType == enXOS_VALUE)
	{
		if(abs(m_dImagery) < XOS_EPSILON)
		{
			return (long)m_dReal;
		}
		else
		{
			return (long)GetLength();
		}
	}
	else
	{
		return 0;
	}
}

CXOS_Data::operator CXOS_Number(void)
{
	if(m_enType == enXOS_VALUE)
	{
		if(abs(m_dImagery) < XOS_EPSILON)
		{
			return CXOS_Number((long)m_dReal);
		}
		else
		{
			return CXOS_Number((long)GetLength());
		}
	}
	else
	{
		return CXOS_Number();
	}
}

///////////////////////////////////////////////////////////
//
// The friend functions
//
///////////////////////////////////////////////////////////
CXOS_Data operator + (const CXOS_Data& d1, const CXOS_Data& d2)
{
	double dReal = d1.m_dReal + d2.m_dReal;
	double dImagery = d1.m_dImagery + d2.m_dImagery;

	return CXOS_Data(dReal, dImagery);
}

CXOS_Data operator - (const CXOS_Data& d1, const CXOS_Data& d2)
{
	double dReal = d1.m_dReal - d2.m_dReal;
	double dImagery = d1.m_dImagery - d2.m_dImagery;

	return CXOS_Data(dReal, dImagery);
}

CXOS_Data operator * (const CXOS_Data& d1, const CXOS_Data& d2)
{
	double dReal = d1.m_dReal * d2.m_dReal - d1.m_dImagery * d2.m_dImagery;
	double dImagery = d1.m_dReal * d2.m_dImagery + d1.m_dImagery * d2.m_dReal;

	return CXOS_Data(dReal, dImagery);
}
                                                            
CXOS_Data operator / (const CXOS_Data& d1, const CXOS_Data& d2)
{
	double dDivider = d2.m_dReal*d2.m_dReal + d2.m_dImagery*d2.m_dImagery;
	double dReal = (d1.m_dReal*d2.m_dReal + d1.m_dImagery*d2.m_dImagery);
	double dImagery = (d1.m_dImagery*d2.m_dReal - d1.m_dReal*d2.m_dImagery);
	if(dDivider <= XOS_MIN)
	{
		if(abs(dReal) <= XOS_EPSILON && abs(dImagery) <= XOS_EPSILON)
		{
			return CXOS_Data(1.0);
		}
		else if(abs(dReal) <= XOS_MIN)
		{
			if(dImagery < 0.0)
				return CXOS_Data(1.0, XOS_NMAX);
			else
				return CXOS_Data(1.0, XOS_MAX);
		}
		else if(abs(dImagery) <= XOS_MIN)
		{
			if(dReal < 0.0)
				return CXOS_Data(XOS_NMAX, 1.0);
			else
				return CXOS_Data(XOS_MAX, 1.0);
		}
		else
		{
			if(dReal < 0.0)
				dReal = XOS_NMAX;
			else
				dReal = XOS_MAX;

			if(dImagery < 0.0)
				dImagery = XOS_NMAX;
			else
				dImagery = XOS_MAX;
		}
	}
	else
	{
		dReal = dReal/dDivider;
		dImagery = dImagery/dDivider;
	}

	return CXOS_Data(dReal, dImagery);
}

CXOS_Data operator + (const CXOS_Data& d1, double d2)
{
	double dReal = d1.m_dReal + d2;
	double dImagery = d1.m_dImagery;

	return CXOS_Data(dReal, dImagery);
}

CXOS_Data operator - (const CXOS_Data& d1, double d2)
{
	double dReal = d1.m_dReal - d2;
	double dImagery = d1.m_dImagery;

	return CXOS_Data(dReal, dImagery);
}

CXOS_Data operator * (const CXOS_Data& d1, double d2)
{
	double dReal = d1.m_dReal * d2;
	double dImagery = d1.m_dImagery * d2;

	return CXOS_Data(dReal, dImagery);
}

CXOS_Data operator / (const CXOS_Data& d1, double d2)
{
	double dReal;
	double dImagery;
	if(abs(d2) <= XOS_EPSILON)
	{
		if(abs(d1.m_dReal) <= XOS_EPSILON && abs(d1.m_dImagery) <= XOS_EPSILON)
		{
			return CXOS_Data(1.0);
		}
		else if(abs(d1.m_dReal) <= XOS_EPSILON)
		{
			if(d1.m_dImagery < 0.0)
				return CXOS_Data(1.0, XOS_NMAX);
			else
				return CXOS_Data(1.0, XOS_MAX);
		}
		else if(abs(d1.m_dImagery) <= XOS_MIN)
		{
			if(d1.m_dReal < 0.0)
				return CXOS_Data(XOS_NMAX, 1.0);
			else
				return CXOS_Data(XOS_MAX, 1.0);
		}
		else
		{
			if(d1.m_dReal < 0.0)
				dReal = XOS_NMAX;
			else
				dReal = XOS_MAX;

			if(d1.m_dImagery < 0.0)
				dImagery = XOS_NMAX;
			else
				dImagery = XOS_MAX;
		}
	}
	else
	{
		dReal = d1.m_dReal/d2;
		dImagery = d1.m_dImagery/d2;
	}
	return CXOS_Data(dReal, dImagery);
}

CXOS_Data operator + (double d1, const CXOS_Data& d2)
{
	return (CXOS_Data(d1) + d2);
}

CXOS_Data operator - (double d1, const CXOS_Data& d2)
{
	return (CXOS_Data(d1) - d2);
}

CXOS_Data operator * (double d1, const CXOS_Data& d2)
{
	return (CXOS_Data(d1) * d2);
}

CXOS_Data operator / (double d1, const CXOS_Data& d2)
{
	return (CXOS_Data(d1) / d2);
}

bool operator == (const CXOS_Data& d1, const CXOS_Data& d2)
{
	bool bRet = false;
	if(d1.m_enType != d2.m_enType)
	{
		return bRet;
	}
	else
	{
		if(d1.m_enType == enXOS_VALUE)
		{
			bRet = (d1.m_dReal == d2.m_dReal);

			if(bRet)
				bRet = (d1.m_dImagery == d2.m_dImagery);

			if(bRet)
				bRet = (d1.m_szName == d2.m_szName);
		}
		else
		{
			bRet = (d1.m_szName == d2.m_szName);
		}
	}

	return bRet;
}

bool operator != (const CXOS_Data& d1, const CXOS_Data& d2)
{
	return !(d1 == d2);
}

bool operator < (const CXOS_Data& d1, const CXOS_Data& d2)
{
	bool bRet = false;
	if(d1.m_enType != d2.m_enType)
	{
		bRet = (d1.m_enType < d2.m_enType);
	}
	else
	{
		if(d1.m_enType == enXOS_VALUE)
		{
			if(d1.m_dImagery == 0.0 && d2.m_dImagery == 0.0)
			{
				bRet = (d1.m_dReal < d2.m_dReal);

				if(!bRet && d1.m_dReal == d2.m_dReal)
					bRet = (d1.m_szName < d2.m_szName);
			}
			else
			{
				double dL1 = d1.GetLength();
				double dL2 = d2.GetLength();
				bRet = (dL1 < dL2);
				if(!bRet && dL1 == dL2)
				{
					bRet = (d1.m_szName < d2.m_szName);
				}
			}
		}
		else
		{
			bRet = (d1.m_szName < d2.m_szName);
		}
	}

	return bRet;
}

bool operator <= (const CXOS_Data& d1, const CXOS_Data& d2)
{
	bool bRet = true;
	if(d1.m_enType != d2.m_enType)
	{
		bRet = (d1.m_enType <= d2.m_enType);
	}
	else
	{
		if(d1.m_enType == enXOS_VALUE)
		{
			if(d1.m_dImagery == 0.0 && d2.m_dImagery == 0.0)
			{
				bRet = (d1.m_dReal <= d2.m_dReal);

//				if(!bRet)
//					bRet = (d1.m_szName <= d2.m_szName);
			}
			else
			{
				double dL1 = d1.GetLength();
				double dL2 = d2.GetLength();
				bRet = (dL1 <= dL2);
//				if(!bRet)
//				{
//					bRet = (d1.m_szName <= d2.m_szName);
//				}
			}
		}
		else
		{
			bRet = (d1.m_szName <= d2.m_szName);
		}
	}

	return bRet;
}

bool operator > (const CXOS_Data& d1, const CXOS_Data& d2)
{
	return (d2 < d1);
}

bool operator >= (const CXOS_Data& d1, const CXOS_Data& d2)
{
	return (d2 <= d1);
}

std::wostream& operator << (std::wostream& out, const CXOS_Data& d)
{
	if(d.IsReal())
		out << d.m_dReal;
	else
		out << L"(" << d.m_dReal << L",i" << d.m_dImagery << L")";

	return out;
}

std::wistream& operator >> (std::wistream& in, CXOS_Data& d)
{
	in >> d.m_dReal;

	return in;
}

CXOS_Data Hypot(const CXOS_Data& d1, const CXOS_Data& d2)
{
	CXOS_Data temp1 = d1*d1 + d2*d2;
	CXOS_Data ret = Pow(temp1, 0.5);

	return ret;
}

CXOS_Data Pow(const CXOS_Data& d1, const CXOS_Data& d2)
{
	double dLr = log(d1.GetLength());
	double dLi = atan2(d1.m_dImagery, d1.m_dReal);
	double dX = exp(dLr*d2.m_dReal - dLi*d2.m_dImagery);
	double dY = dLi*d2.m_dReal + dLr*d2.m_dImagery;

	return CXOS_Data(dX*cos(dY), dX*sin(dY));
}

CXOS_Data Pow(const CXOS_Data& d1, double d2)
{
	double dLr = log(d1.GetLength());
	double dLi = atan2(d1.m_dImagery, d1.m_dReal);
	double dX = exp(dLr*d2);
	double dY = dLi*d2;

	return CXOS_Data(dX*cos(dY), dX*sin(dY));
}

CXOS_Data Pow(double d1, const CXOS_Data& d2)
{
	double dLr = log(d1);
	double dX = exp(dLr*d2.m_dReal);
	double dY = dLr*d2.m_dImagery;

	return CXOS_Data(dX*cos(dY), dX*sin(dY));
}

CXOS_Data Root(const CXOS_Data& d1, const CXOS_Data& d2)
{
	CXOS_Data temp = 1.0/d2;

	return Pow(d1, temp);
}

CXOS_Data Root(const CXOS_Data& d1, double d2)
{
	if(d2 == 0.0)
		return CXOS_Data(XOS_MAX);

	double temp = 1.0/d2;

	return Pow(d1, temp);
}

CXOS_Data Root(double d1, const CXOS_Data& d2)
{
	CXOS_Data temp = 1.0/d2;

	return Pow(d1, temp);
}



