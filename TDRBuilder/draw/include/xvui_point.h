#ifndef __XVUI_POINT_H__
#define __XVUI_POINT_H__
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CVUI_LinkPoint

class CVUI_LinkPoint : public CPoint
{
//@Access: Constructors
public:
	//@cmember: Constructor
	CVUI_LinkPoint();

	//@cmember: Constructor
	CVUI_LinkPoint(int nX, int nY);

	//@cmember: Constructor
	CVUI_LinkPoint(POINT initPt);

	//@cmember: Constructor
	CVUI_LinkPoint(SIZE initSize);

	//@cmember: Constructor
	CVUI_LinkPoint(LPARAM dwPoint);

	//@cmember: Constructor
	CVUI_LinkPoint(CPoint pt);

	//@cmember: Constructor
	CVUI_LinkPoint(const CVUI_LinkPoint& pt);

	//@cmember: Destructor
	virtual ~CVUI_LinkPoint();

//@Access: Attributes
public:
	//@cmember: The intersection point list
	std::vector<int>	m_ptList;

//@Access: Operations
public:
	//@cmember: Type conversion
	void CleanList(void);

	//@cmember: Add new intersection point (x axis value only)
	void AddPoint(int nx);

	//@cmember: Sort the points
	void SortPoint(BOOL bAscend = TRUE);

	//@cmember: Check the points
	BOOL HasPoint(void);

	//@cmember: Check the points number
	int GetPointCount(void);

	//@cmember: Get the specific point 
	int GetPoint(int nIdx);

	//@cmember: Type conversion
	operator CPoint ();

	//@cmember: Type conversion
	operator POINT ();

	//@cmember: Type conversion
	operator CSize ();

	//@cmember: Type conversion
	operator SIZE ();

	//@cmember: Overload operator "="
	CVUI_LinkPoint& operator = (const CVUI_LinkPoint& pt);

	//@cmember: Overload operator "="
	CVUI_LinkPoint& operator = (const CPoint& pt);

	//@cmember: Overload operator "="
	CVUI_LinkPoint& operator = (const CSize& size);

	//@cmember: Overload operator "="
	CVUI_LinkPoint& operator = (const POINT& pt);

	//@cmember: Overload operator "="
	CVUI_LinkPoint& operator = (const SIZE& size);

	//@cmember: Overload operator "+="
	void operator += (const CVUI_LinkPoint& pt);

	//@cmember: Overload operator "+="
	void operator += (const CPoint& pt);

	//@cmember: Overload operator "+="
	void operator += (const CSize& size);

	//@cmember: Overload operator "+="
	void operator += (const POINT& pt);

	//@cmember: Overload operator "+="
	void operator += (const SIZE& size);

	//@cmember: Overload operator "-="
	void operator -= (const CVUI_LinkPoint& pt);

	//@cmember: Overload operator "-="
	void operator -= (const CPoint& pt);

	//@cmember: Overload operator "-="
	void operator -= (const CSize& size);

	//@cmember: Overload operator "-="
	void operator -= (const POINT& pt);

	//@cmember: Overload operator "-="
	void operator -= (const SIZE& size);

	friend bool operator == (const CVUI_LinkPoint& pt1, const CVUI_LinkPoint& pt2);
	friend bool operator != (const CVUI_LinkPoint& pt1, const CVUI_LinkPoint& pt2);

	friend bool operator == (const CVUI_LinkPoint& pt1, const CPoint& pt2);
	friend bool operator != (const CVUI_LinkPoint& pt1, const CPoint& pt2);

	friend bool operator == (const CVUI_LinkPoint& pt1, const POINT& pt2);
	friend bool operator != (const CVUI_LinkPoint& pt1, const POINT& pt2);

	friend bool operator == (const CPoint& pt1, const CVUI_LinkPoint& pt2);
	friend bool operator != (const CPoint& pt1, const CVUI_LinkPoint& pt2);

	friend bool operator == (const POINT& pt1, const CVUI_LinkPoint& pt2);
	friend bool operator != (const POINT& pt1, const CVUI_LinkPoint& pt2);

	friend bool operator == (const CVUI_LinkPoint& pt1, const CSize& pt2);
	friend bool operator != (const CVUI_LinkPoint& pt1, const CSize& pt2);

	friend bool operator == (const CVUI_LinkPoint& pt1, const SIZE& pt2);
	friend bool operator != (const CVUI_LinkPoint& pt1, const SIZE& pt2);

	friend bool operator == (const CSize& pt1, const CVUI_LinkPoint& pt2);
	friend bool operator != (const CSize& pt1, const CVUI_LinkPoint& pt2);

	friend bool operator == (const SIZE& pt1, const CVUI_LinkPoint& pt2);
	friend bool operator != (const SIZE& pt1, const CVUI_LinkPoint& pt2);
};

typedef std::vector<CVUI_LinkPoint>		CVUI_LPointArray;
typedef std::vector<CPoint>				CVUI_PointArray;

#endif // __XVUI_POINT_H__
