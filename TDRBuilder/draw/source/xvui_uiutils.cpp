#include "stdafx.h"
#include "xvui_uiutils.h"

BOOL CVUI_HitUtility::PtInPloy(const CPoint* pPts, int nNum, const CPoint& pt)
{
	BOOL bRet = FALSE;

	if(pPts == NULL || nNum == 0)
		return bRet;

	if(nNum == 1)
	{
		bRet = (pPts[0] == pt);
	}
	else if(nNum == 2)
	{
		bRet = PtInLine(pPts[0], pPts[1], pt);
	}
	else
	{
		CPoint* tempPTs = new CPoint[nNum+2];
		memcpy((void*)&tempPTs[1], pPts, nNum*sizeof(CPoint));
		tempPTs[0] = tempPTs[nNum];
		tempPTs[nNum + 1] = tempPTs[1];

		CPoint LinePstart, LinePend, LineTstart, LineTend;

		LineTstart = pt;
		LineTend = pt;
		LineTend.x = 10000;//INT_MAX; 

		int iCount = 0;
		int j = 0;
		for(int i = 1; i <= nNum; i++)
		{
			// Build the line segment with the two
			// vertex points of the polygon
			LinePstart = tempPTs[i];
			LinePend = tempPTs[i];

			// Check the intersection of reference line segment
			// with the line segment of the two polygon vertex
			// points
			if(!Intersect(LinePstart, LinePend, LineTstart, LineTend))
			{
				LinePend = tempPTs[j];
				j = i;

				// If intersected
				if(Intersect(LinePstart, LinePend, LineTstart, LineTend))
					iCount++;
			}
		}

		//Release the memory
		delete []tempPTs;

		// If number of intersection is odd,
		// the point is inside of the polygon.
		bRet = ((iCount & 1) == 1);
	}

	return bRet;
}

BOOL CVUI_HitUtility::PtInLine(const CPoint& linestart, const CPoint& lineend, const CPoint& pt)
{
	BOOL bRet = FALSE;

	if(linestart == pt || lineend == pt)
	{
		bRet = TRUE;	
	}
	else
	{
		int ndx1 = pt.x - linestart.x;
		int ndx2 = lineend.x - pt.x;
		int ndy1 = pt.y - linestart.y;
		int ndy2 = lineend.y - pt.y;

		if((ndy1 == 0 && ndy2 != 0) && (ndy1 != 0 && ndy2 == 0))
		{
			bRet = FALSE;	
			return bRet;
		}
		else if(ndy1 == 0 && ndy2 == 0)
		{
			if(ndx1 == 0 && ndx2 == 0)
			{
				bRet = TRUE;	
				return bRet;
			}
			else
			{
				if(min(linestart.x, lineend.x) <= pt.x && pt.x <= max(linestart.x, lineend.x))
				{
					bRet = TRUE;	
					return bRet;
				}
				else
				{
					bRet = FALSE;	
					return bRet;
				}
			}
		}
		else 
		{
			bRet = (ndx1*ndy2 == ndx2*ndy1);
		}
	}

	return bRet;
}

BOOL CVUI_HitUtility::PtInLine(const CPoint& linestart, const CPoint& lineend, const CPoint& cpt, long nXOffset)
{
	BOOL bRet;

	int left, top, right, bottom;
	if(linestart.x == lineend.x)
	{
		left = linestart.x - nXOffset;
		right = linestart.x + nXOffset;
		if(linestart.y == lineend.y)
		{
			top = linestart.y - nXOffset;
			bottom = linestart.y + nXOffset;
		}
		else
		{
			top = min(linestart.y, lineend.y);
			bottom = max(linestart.y, lineend.y);
		}
	}
	else
	{
		if(linestart.y == lineend.y)
		{
			left = min(linestart.x, lineend.x);
			right = max(linestart.x, lineend.x);
			top = linestart.y - nXOffset;
			bottom = linestart.y + nXOffset;
		}
		else
		{
			left = linestart.x - nXOffset;
			right = linestart.x + nXOffset;
			top = min(linestart.y, lineend.y);
			bottom = max(linestart.y, lineend.y);
		}
	}
	CRect rect(left, top, right, bottom);
	bRet = rect.PtInRect(cpt);

/*
	CPoint pt[4];
	if(linestart.x == lineend.x)
	{
		pt[0].x = linestart.x - nXOffset;
		pt[1].x = linestart.x + nXOffset;
		pt[2].x = linestart.x + nXOffset;
		pt[3].x = linestart.x - nXOffset;
		if(linestart.y == lineend.y)
		{
			pt[0].y = linestart.y - nXOffset;
			pt[1].y = linestart.y - nXOffset;
			pt[2].y = linestart.y + nXOffset;
			pt[3].y = linestart.y + nXOffset;
		}
		else
		{
			pt[0].y = linestart.y;
			pt[1].y = linestart.y;
			pt[2].y = lineend.y;
			pt[3].y = lineend.y;
		}
	}
	else
	{
		if(linestart.y == lineend.y)
		{
			pt[0].x = linestart.x;
			pt[1].x = lineend.x;
			pt[2].x = lineend.x;
			pt[3].x = linestart.x;
			pt[0].y = linestart.y - nXOffset;
			pt[1].y = linestart.y - nXOffset;
			pt[2].y = linestart.y + nXOffset;
			pt[3].y = linestart.y + nXOffset;
		}
		else
		{
			pt[0].x = linestart.x - nXOffset;
			pt[1].x = linestart.x + nXOffset;
			pt[2].x = lineend.x + nXOffset;
			pt[3].x = lineend.x - nXOffset;
			pt[0].y = linestart.y;
			pt[1].y = linestart.y;
			pt[2].y = lineend.y;
			pt[3].y = lineend.y;
		}
	}

	bRet = PtInPloy(pt, 4, cpt);
*/
	return bRet;
}

int CVUI_HitUtility::CounterClockwise(const CPoint& pt0, const CPoint& pt1, const CPoint& pt2)
{
	int iX1, iX2, iY1, iY2;

	iX1 = pt1.x - pt0.x;
    iY1 = pt1.y - pt0.y;
	iX2 = pt2.x - pt0.x;
    iY2 = pt2.y - pt0.y;

	if(iX1*iY2 > iY1*iX2)
		return 1;
	
	if(iX1*iY2 < iY1*iX2)
		return -1;

	if((iX1*iX2 < 0) || (iY1*iY2 < 0))
		return -1;

	if((iX1*iX1 + iY1*iY1) < (iX2*iX2 + iY2*iY2))
		return 1;

	return 0;
}

BOOL CVUI_HitUtility::Intersect(const CPoint& line1start, const CPoint& line1end, const CPoint& line2start, const CPoint& line2end)
{
	int iCCW1 = CounterClockwise(line1start, line1end, line2start);
    int iCCW2 = CounterClockwise(line1start, line1end, line2end);
	int iCCW3 = CounterClockwise(line2start, line2end, line1start);
    int iCCW4 = CounterClockwise(line2start, line2end, line1end);

	return ((iCCW1*iCCW2 <= 0) && (iCCW3*iCCW4 <= 0));
}

CRect CVUI_MaxRect::GetBoundary(const CRect& rect1, const CRect& rect2)
{
	int nminx;
	int nminy;
	int nmaxx;
	int nmaxy;
	nminx = min(rect1.left, rect2.left);  
	nmaxx = max(rect1.right, rect2.right);  
	nminy = min(rect1.top, rect2.top);  
	nmaxy = max(rect1.bottom, rect2.bottom);  
	CRect rect(nminx, nminy, nmaxx, nmaxy);
	return rect;
}

BOOL CVUI_PLIntersect::IsIntersect(const CPoint& ptV1, const CPoint& ptV2, const CPoint& ptH1, const CPoint& ptH2)
{
	BOOL bRet = FALSE;
	if(ptV1.x == ptH1.x || ptV1.x == ptH2.x || ptV1.x != ptV2.x || ptH1.y != ptH2.y || ptH1.x == ptH2.x)
		return bRet;

	int nDif1, nDif2, nDif;
	
	//Check x axis
	nDif = abs(ptH1.x - ptH2.x);
	nDif1 = abs(ptV1.x - ptH1.x);
	nDif2 = abs(ptV1.x - ptH2.x);

	if(nDif < nDif1 || nDif < nDif2)
		return bRet;

	//Check y axis
	nDif = abs(ptV1.y - ptV2.y);
	nDif1 = abs(ptH1.y - ptV1.y);
	nDif2 = abs(ptH1.y - ptV2.y);

	if(nDif < nDif1 || nDif < nDif2)
		return bRet;

	bRet = TRUE;
	return bRet;
}

