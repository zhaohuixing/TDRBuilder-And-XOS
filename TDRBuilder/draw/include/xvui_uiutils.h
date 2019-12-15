//2005/02/04 
#ifndef __XVUI_UIUTILS_H__
#define __XVUI_UIUTILS_H__

class CVUI_HitUtility
{
public:
	CVUI_HitUtility(){};

	BOOL PtInPloy(const CPoint* pPts, int nNum, const CPoint& pt);
	BOOL PtInLine(const CPoint& linestart, const CPoint& lineend, const CPoint& pt);
	BOOL PtInLine(const CPoint& linestart, const CPoint& lineend, const CPoint& pt, long nXOffset);
	BOOL Intersect(const CPoint& line1start, const CPoint& line1end, const CPoint& line2start, const CPoint& line2end);

private:
	int CounterClockwise(const CPoint& pt0, const CPoint& pt1, const CPoint& pt2);
};

class CVUI_MaxRect
{
public:
	static CRect GetBoundary(const CRect& rect1, const CRect& rect2);
};

class CVUI_PLIntersect
{
public:
	static BOOL IsIntersect(const CPoint& ptV1, const CPoint& ptV2, const CPoint& ptH1, const CPoint& ptH2);
};

#endif