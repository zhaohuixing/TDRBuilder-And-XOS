// Date: 06/09/2004	
#ifndef __XOS_TIME_H__
#define __XOS_TIME_H__

#include <time.h>
#include "xos_clsbase.h"
#include "xos_string.h"
#include "xos_num.h"

class CXOS_Time : public CXOS_ClassObject
{
//
// Construction/Destruction
//
public:
	CXOS_Time(void);
	CXOS_Time(std::wstring& szName); // Constructor
	CXOS_Time(const wchar_t* szName); // Constructor
	CXOS_Time(time_t tv); // Constructor
	CXOS_Time(const wchar_t* szName, time_t tv); // Constructor
	CXOS_Time(std::wstring& szName, time_t tv);  // Constructor
	CXOS_Time(const CXOS_Time& tv); // Constructor
	virtual ~CXOS_Time(void);

//
// Implementation
//
public:
	// Set time
	void SetTime(const CXOS_Time& tv){m_Time = tv.m_Time;} 

	// Set time
	void SetTime(time_t tv){m_Time = tv;} 

	// Comparsion
	bool IsEqual(const CXOS_Time& tv){return (m_Time == tv.m_Time);}

	wchar_t* GetTimeString(void){return _wctime(&m_Time);} 	


	CXOS_Time& operator = (const CXOS_Time& tv);	// Assignment
	CXOS_Time& operator = (time_t tv);	// Assignment
	
	operator time_t (void);	// Type conversion to time_t*
	operator wchar_t* (void);	// Type conversion to wchar_t*
	operator std::wstring (void);	// Type conversion to wstring
	operator CXOS_String(void); // Type conversion to CXOS_Data

	long Second(void);		
	long Minute(void);
	long Hour(void);
	long DayInMonth(void);
	long Month(void);
	long Year(void);
	long DayInYear(void);
	long DayInWeek(void);
	bool IsDST(void);		// Is Daylight saving time
	double Diff(const CXOS_Time& t);
	double Diff(time_t t);

	void AcquireCurrentTime(void);

	friend bool operator == (const CXOS_Time& t1, const CXOS_Time& t2);
	friend bool operator != (const CXOS_Time& t1, const CXOS_Time& t2);

	friend bool operator == (const CXOS_Time& t1, time_t t2);
	friend bool operator != (const CXOS_Time& t1, time_t t2);

	friend bool operator == (time_t t1, const CXOS_Time& t2);
	friend bool operator != (time_t t1, const CXOS_Time& t2);

	friend std::wostream& operator << (std::wostream& out, const CXOS_Time& tm);
	friend std::wistream& operator >> (std::wistream& in, CXOS_Time& tm);

	static std::wstring GetWeekDay(time_t tm);

	virtual bool CanStreamIO(void) const {return true;}

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXOS_Time");}

//
// Attributions
//
public:
	time_t		m_Time;

};

#endif