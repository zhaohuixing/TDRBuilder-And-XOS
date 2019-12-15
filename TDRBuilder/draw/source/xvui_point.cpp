#include "stdafx.h"
#include "xvui_point.h"
#include <algorithm>
#include <functional>


CVUI_LinkPoint::CVUI_LinkPoint()
	: CPoint()
{
	m_ptList.empty();
}

CVUI_LinkPoint::CVUI_LinkPoint(int nX, int nY)
	: CPoint(nX, nY)
{
	m_ptList.empty();
}

CVUI_LinkPoint::CVUI_LinkPoint(POINT initPt)
	: CPoint(initPt)
{
	m_ptList.empty();
}

CVUI_LinkPoint::CVUI_LinkPoint(SIZE initSize)
	: CPoint(initSize)
{
	m_ptList.empty();
}

CVUI_LinkPoint::CVUI_LinkPoint(LPARAM dwPoint)
	: CPoint(dwPoint)
{
	m_ptList.empty();
}

CVUI_LinkPoint::CVUI_LinkPoint(CPoint pt)
	: CPoint(pt)
{
	m_ptList.empty();
}

CVUI_LinkPoint::CVUI_LinkPoint(const CVUI_LinkPoint& pt)
	: CPoint(pt.x, pt.y)
{
	m_ptList.empty();
	for(int i = 0; i < (int)pt.m_ptList.size(); i++)
	{
		m_ptList.push_back(pt.m_ptList[i]);
	}
}

CVUI_LinkPoint::~CVUI_LinkPoint()
{
	CleanList();
}

/////////////////////////////////////////////////////////////////////////////
void CVUI_LinkPoint::CleanList(void)
{
	m_ptList.clear();
}

void CVUI_LinkPoint::AddPoint(int nx)
{
	if(nx == x)
		return;

	for(int i = 0; i < (int)m_ptList.size(); i++)
	{
		if(m_ptList[i] == nx)
			return;
	}

	m_ptList.push_back(nx);
}

void CVUI_LinkPoint::SortPoint(BOOL bAscend)
{
	if(bAscend)
		std::sort(m_ptList.begin(), m_ptList.end(), std::less<int>());
	else
		std::sort(m_ptList.begin(), m_ptList.end(), std::greater<int>());
}

BOOL CVUI_LinkPoint::HasPoint(void)
{
	BOOL bRet = (0 < (int)m_ptList.size());
	return bRet;
}

int CVUI_LinkPoint::GetPointCount(void)
{
	int nRet = (int)m_ptList.size();
	return nRet;
}

int CVUI_LinkPoint::GetPoint(int nIdx)
{
	int nRet = -1;
	if(0 <= nIdx && nIdx < (int)m_ptList.size())
	{
		nRet = m_ptList[nIdx];
	}
	return nRet;
}

CVUI_LinkPoint::operator CPoint ()
{
	return CPoint(x, y);
}

CVUI_LinkPoint::operator POINT ()
{
	POINT pt;
	pt.x = x;
	pt.y = y;
	return pt;
}

CVUI_LinkPoint::operator CSize ()
{
	return CSize(x, y);
}

CVUI_LinkPoint::operator SIZE ()
{
	SIZE size;
	size.cx = x;
	size.cy = y;
	return size;
}

CVUI_LinkPoint& CVUI_LinkPoint::operator = (const CVUI_LinkPoint& pt)
{
	x = pt.x;
	y = pt.y;
	m_ptList.empty();
	for(int i = 0; i < (int)pt.m_ptList.size(); i++)
	{
		m_ptList.push_back(pt.m_ptList[i]);
	}

	return *this;
}

CVUI_LinkPoint& CVUI_LinkPoint::operator = (const CPoint& pt)
{
	if(x != pt.x || y != pt.y)
		m_ptList.empty();

	x = pt.x;
	y = pt.y;
	return *this;
}

CVUI_LinkPoint& CVUI_LinkPoint::operator = (const POINT& pt)
{
	if(x != pt.x || y != pt.y)
		m_ptList.empty();

	x = pt.x;
	y = pt.y;
	return *this;
}

CVUI_LinkPoint& CVUI_LinkPoint::operator = (const SIZE& size)
{
	if(x != size.cx || y != size.cy)
		m_ptList.empty();

	x = size.cx;
	y = size.cy;
	return *this;
}

void CVUI_LinkPoint::operator += (const CVUI_LinkPoint& pt)
{
	m_ptList.empty();

	x += pt.x;
	y += pt.y;
}

void CVUI_LinkPoint::operator += (const CPoint& pt)
{
	m_ptList.empty();

	x += pt.x;
	y += pt.y;
}

void CVUI_LinkPoint::operator += (const CSize& size)
{
	m_ptList.empty();

	x += size.cx;
	y += size.cy;
}

void CVUI_LinkPoint::operator += (const POINT& pt)
{
	m_ptList.empty();

	x += pt.x;
	y += pt.y;
}

void CVUI_LinkPoint::operator += (const SIZE& size)
{
	m_ptList.empty();

	x += size.cx;
	y += size.cy;
}

void CVUI_LinkPoint::operator -= (const CVUI_LinkPoint& pt)
{
	m_ptList.empty();

	x -= pt.x;
	y -= pt.y;
}

void CVUI_LinkPoint::operator -= (const CPoint& pt)
{
	m_ptList.empty();

	x -= pt.x;
	y -= pt.y;
}

void CVUI_LinkPoint::operator -= (const CSize& size)
{
	m_ptList.empty();

	x -= size.cx;
	y -= size.cy;
}

void CVUI_LinkPoint::operator -= (const POINT& pt)
{
	m_ptList.empty();

	x -= pt.x;
	y -= pt.y;
}

void CVUI_LinkPoint::operator -= (const SIZE& size)
{
	m_ptList.empty();

	x -= size.cx;
	y -= size.cy;
}

bool operator == (const CVUI_LinkPoint& pt1, const CVUI_LinkPoint& pt2)
{
	bool bRet = false;

	bRet = (pt1.x == pt2.x && pt1.y == pt2.y);

	if(!bRet)
		return bRet;

	bRet = (pt1.m_ptList.size() == pt2.m_ptList.size());
	if(!bRet)
		return bRet;

	for(int i = 0; i < (int)pt1.m_ptList.size(); i++)
	{
		bRet = (pt1.m_ptList[i] == pt2.m_ptList[i]);
		if(!bRet)
			return bRet;
	}

	return bRet;
}

bool operator != (const CVUI_LinkPoint& pt1, const CVUI_LinkPoint& pt2)
{
	return !(pt1 == pt2);
}

bool operator == (const CVUI_LinkPoint& pt1, const CPoint& pt2)
{
	bool bRet = false;

	bRet = (pt1.x == pt2.x && pt1.y == pt2.y);

	return bRet;
}

bool operator != (const CVUI_LinkPoint& pt1, const CPoint& pt2)
{
	return !(pt1 == pt2);
}

bool operator == (const CVUI_LinkPoint& pt1, const POINT& pt2)
{
	bool bRet = false;

	bRet = (pt1.x == pt2.x && pt1.y == pt2.y);

	return bRet;
}

bool operator != (const CVUI_LinkPoint& pt1, const POINT& pt2)
{
	return !(pt1 == pt2);
}

bool operator == (const CPoint& pt1, const CVUI_LinkPoint& pt2)
{
	bool bRet = false;

	bRet = (pt1.x == pt2.x && pt1.y == pt2.y);

	return bRet;
}

bool operator != (const CPoint& pt1, const CVUI_LinkPoint& pt2)
{
	return !(pt1 == pt2);
}

bool operator == (const POINT& pt1, const CVUI_LinkPoint& pt2)
{
	bool bRet = false;

	bRet = (pt1.x == pt2.x && pt1.y == pt2.y);

	return bRet;
}

bool operator != (const POINT& pt1, const CVUI_LinkPoint& pt2)
{
	return !(pt1 == pt2);
}

bool operator == (const CVUI_LinkPoint& pt1, const CSize& pt2)
{
	bool bRet = false;

	bRet = (pt1.x == pt2.cx && pt1.y == pt2.cy);

	return bRet;
}

bool operator != (const CVUI_LinkPoint& pt1, const CSize& pt2)
{
	return !(pt1 == pt2);
}

bool operator == (const CVUI_LinkPoint& pt1, const SIZE& pt2)
{
	bool bRet = false;

	bRet = (pt1.x == pt2.cx && pt1.y == pt2.cy);

	return bRet;
}

bool operator != (const CVUI_LinkPoint& pt1, const SIZE& pt2)
{
	return !(pt1 == pt2);
}

bool operator == (const CSize& pt1, const CVUI_LinkPoint& pt2)
{
	bool bRet = false;

	bRet = (pt1.cx == pt2.x && pt1.cy == pt2.y);

	return bRet;
}

bool operator != (const CSize& pt1, const CVUI_LinkPoint& pt2)
{
	return !(pt1 == pt2);
}

bool operator == (const SIZE& pt1, const CVUI_LinkPoint& pt2)
{
	bool bRet = false;

	bRet = (pt1.cx == pt2.x && pt1.cy == pt2.y);

	return bRet;
}

bool operator != (const SIZE& pt1, const CVUI_LinkPoint& pt2)
{
	return !(pt1 == pt2);
}