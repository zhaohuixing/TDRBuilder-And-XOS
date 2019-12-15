// Date: 06/09/2004	
#include "xos_time.h"

CXOS_Time::CXOS_Time(void)
{
	m_szClass = L"CXOS_Time";
	m_szName = L"";
	m_Time = 0;
}

CXOS_Time::CXOS_Time(std::wstring& szName)
{
	m_szClass = L"CXOS_Time";
	m_szName = L"";
	m_Time = 0;
}

CXOS_Time::CXOS_Time(const wchar_t* szName)
{
	m_szClass = L"CXOS_Time";
	m_szName = szName;
	m_Time = 0;
}

CXOS_Time::CXOS_Time(time_t tv)
{
	m_szClass = L"CXOS_Time";
	m_szName = L"";
	m_Time = tv;
}

CXOS_Time::CXOS_Time(const wchar_t* szName, time_t tv)
{
	m_szClass = L"CXOS_Time";
	m_szName = szName;
	m_Time = tv;
}

CXOS_Time::CXOS_Time(std::wstring& szName, time_t tv)
{
	m_szClass = L"CXOS_Time";
	m_szName = szName;
	m_Time = tv;
}

CXOS_Time::CXOS_Time(const CXOS_Time& tv)
{
	m_szClass = L"CXOS_Time";
	m_szName = tv.m_szName;
	m_Time = tv.m_Time;
}

CXOS_Time::~CXOS_Time(void)
{
}

CXOS_Time& CXOS_Time::operator = (const CXOS_Time& tv)
{
	m_szName = tv.m_szName;
	m_Time = tv.m_Time;
	return *this;
}

CXOS_Time& CXOS_Time::operator = (time_t tv)
{
	m_Time = tv;
	return *this;
}

CXOS_Time::operator time_t (void)
{
	return m_Time;
}

CXOS_Time::operator wchar_t* (void)
{
	return _wctime(&m_Time);
}

CXOS_Time::operator std::wstring (void)
{
	return std::wstring(_wctime(&m_Time));
}

CXOS_Time::operator CXOS_String(void)
{
	return CXOS_String(_wctime(&m_Time));
}

long CXOS_Time::Second(void)
{
	long n = 0;
	
	struct tm *ptm = localtime(&m_Time);
	if(ptm)
		n = (long)ptm->tm_sec;

	return n;
}

long CXOS_Time::Minute(void)
{
	long n = 0;
	
	struct tm *ptm = localtime(&m_Time);
	if(ptm)
		n = (long)ptm->tm_min;

	return n;
}

long CXOS_Time::Hour(void)
{
	long n = 0;
	
	struct tm *ptm = localtime(&m_Time);
	if(ptm)
		n = (long)ptm->tm_hour;

	return n;
}

long CXOS_Time::DayInMonth(void)
{
	long n = 0;
	
	struct tm *ptm = localtime(&m_Time);
	if(ptm)
		n = (long)ptm->tm_mday;

	return n;
}

long CXOS_Time::Month(void)
{
	long n = 0;
	
	struct tm *ptm = localtime(&m_Time);
	if(ptm)
		n = (long)ptm->tm_mon;

	return n;
}

long CXOS_Time::Year(void)
{
	long n = 0;
	
	struct tm *ptm = localtime(&m_Time);
	if(ptm)
		n = (long)ptm->tm_year;

	return n;
}

long CXOS_Time::DayInYear(void)
{
	long n = 0;
	
	struct tm *ptm = localtime(&m_Time);
	if(ptm)
		n = (long)ptm->tm_yday;

	return n;
}

long CXOS_Time::DayInWeek(void)
{
	long n = 0;
	
	struct tm *ptm = localtime(&m_Time);
	if(ptm)
		n = (long)ptm->tm_wday;

	return n;
}

bool CXOS_Time::IsDST(void)
{
	bool b = false;
	
	struct tm *ptm = localtime(&m_Time);
	if(ptm)
		b = (0 < ptm->tm_isdst);

	return b;
}

double CXOS_Time::Diff(const CXOS_Time& t)
{
	double d = 0.0;
	
	d = difftime(m_Time, t.m_Time);

	return d;
}

double CXOS_Time::Diff(time_t t)
{
	double d = 0.0;
	
	d = difftime(m_Time, t);

	return d;
}

void CXOS_Time::AcquireCurrentTime(void)
{
	time(&m_Time);
}

std::wstring CXOS_Time::GetWeekDay(time_t tmd)
{
	struct tm *ptm = localtime(&tmd);
	std::wstring str = L"";
	if(ptm)
	{
		switch(ptm->tm_wday)
		{
			case 0:
				str = L"Sunday";
				break;
			case 1:
				str = L"Monday";
				break;
			case 2:
				str = L"Tuesday";
				break;
			case 3:
				str = L"Wednesday";
				break;
			case 4:
				str = L"Thursday";
				break;
			case 5:
				str = L"Friday";
				break;
			case 6:
				str = L"Saturday";
				break;
		}
	}

	return str;
}

bool operator == (const CXOS_Time& t1, const CXOS_Time& t2)
{
	bool bRet = (t1.m_Time == t2.m_Time);

	if(bRet)
		bRet = (t1.m_szName == t2.m_szName);

	return bRet;

}

bool operator != (const CXOS_Time& t1, const CXOS_Time& t2)
{
	return !(t1 == t2);

}

bool operator == (const CXOS_Time& t1, time_t t2)
{
	bool bRet = (t1.m_Time == t2);

	return bRet;

}

bool operator != (const CXOS_Time& t1, time_t t2)
{
	return !(t1 == t2);

}

bool operator == (time_t t1, const CXOS_Time& t2)
{
	bool bRet = (t1 == t2.m_Time);

	return bRet;

}

bool operator != (time_t t1, const CXOS_Time& t2)
{
	return !(t1 == t2);
}

std::wostream& operator << (std::wostream& out, const CXOS_Time& tm)
{
	out << _wctime(&tm.m_Time);
	return out;
}

std::wistream& operator >> (std::wistream& in, CXOS_Time& tm)
{
	in >> tm.m_Time;
	return in;
}


