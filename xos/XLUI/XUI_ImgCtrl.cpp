#ifdef __USE_WTL__
#ifndef _WTL_NO_WTYPES
#define _WTL_NO_WTYPES
#endif
#include "stdafx.h"
#endif

#include "xui_imgctrl.h"
#include "xui_msg.h"

CXUI_ImageCtrl::CXUI_ImageCtrl()
{
#ifdef __USE_WTL__
	m_Picture = NULL;
#endif
	m_bStretch = false;
}

CXUI_ImageCtrl::~CXUI_ImageCtrl()
{
	CleanImage();
}

bool CXUI_ImageCtrl::LoadImage(std::wstring szImage)
{
	return LoadImage(szImage.c_str());
}

bool CXUI_ImageCtrl::LoadImage(const wchar_t* szImage)
{
	bool bRet = false;
#ifdef __USE_WTL__
	if(szImage != NULL)
	{
		CleanImage();

		// Open file
		HANDLE hFile = ::CreateFile(CW2CT(szImage), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
			return bRet;
	
		// Get file size
		DWORD dwFileSize = ::GetFileSize(hFile, NULL);
	
		if(dwFileSize == (DWORD)-1)
		{
			CloseHandle(hFile);
			return bRet;
		}
	
		LPVOID pvData = NULL;
	
		// Alloc memory based on file size
		HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, dwFileSize);
	
		if(hGlobal == NULL)
		{
			::CloseHandle(hFile);
			return bRet;
		}
	
		pvData = ::GlobalLock(hGlobal);
	
		if(pvData == NULL)
		{
			::GlobalUnlock(hGlobal);
			::CloseHandle(hFile);
			return bRet;
		}
	
		DWORD dwBytesRead = 0;
	
		// Read file and store in global memory
		BOOL bRead = ::ReadFile(hFile,
							  pvData,
							  dwFileSize,
							  &dwBytesRead,
							  NULL);
	
		::GlobalUnlock(hGlobal);
		::CloseHandle(hFile);
	
		if(!bRead)
			return bRet;
	
		LPSTREAM pstm = NULL;
	
		// Create IStream* from global memory
		HRESULT hr = ::CreateStreamOnHGlobal(hGlobal, TRUE, &pstm);
	
		if(!(SUCCEEDED(hr)))
		{
			if (pstm != NULL)
				pstm->Release();
		
			return bRet;
		}
		else if(pstm == NULL)
		{
			return bRet;
		}
	
		// Create IPicture from image file
		hr = ::OleLoadPicture(pstm,
							  dwFileSize,
							  FALSE,
							  IID_IPicture,
							  (LPVOID *)&m_Picture);
	
		if(!(SUCCEEDED(hr)))
		{
			pstm->Release();
			return bRet;
		}
		else if(m_Picture == NULL)
		{
			pstm->Release();
			return bRet;
		}
		pstm->Release();
		bRet = true;
		BOOL bHandle;
		OnPaint(0, 0, 0, bHandle);
	}

#endif
	return bRet;
}

#ifdef __USE_WTL__
LRESULT CXUI_ImageCtrl::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{

	CPaintDC dc(m_hWnd);

//	CDC dcMem;

//    dcMem.CreateCompatibleDC ( dc );

	dc.SaveDC();
//    dcMem.SaveDC();

	CRect rcDraw;
	GetClientRect(rcDraw);


    dc.FillSolidRect(&rcDraw, GetCtrlBkClr());

	//DrawImage(&dcMem, rcDraw.CenterPoint(), rcDraw);
	DrawImage(&dc, rcDraw.CenterPoint(), rcDraw);

/*
	dc.BitBlt(rcDraw.left,  
			  rcDraw.top,
			  rcDraw.Width()+1,
			  rcDraw.Height()+1,
			  dcMem, 0, 0, SRCCOPY);
*/

	return 1L;
}


void CXUI_ImageCtrl::DrawItem(LPDRAWITEMSTRUCT lpdis)
{
	CDCHandle dc = lpdis->hDC;
	CDC dcMem;

    dcMem.CreateCompatibleDC ( dc );
//    dc.SaveDC();
//    dcMem.SaveDC();

	CRect rcDraw;
	rcDraw = lpdis->rcItem;

//    dc.FillSolidRect(&lpdis->rcItem, GetCtrlBkClr());

	DrawImage(&dcMem, rcDraw.CenterPoint(), rcDraw);

	dc.BitBlt(rcDraw.left,  
			  rcDraw.top,
			  rcDraw.Width()+1,
			  rcDraw.Height()+1,
			  dcMem, 0, 0, SRCCOPY);

}

COLORREF CXUI_ImageCtrl::GetCtrlBkClr(void)
{
	if(m_hWnd == NULL)
		return RGB(255, 255, 255);

	CWindow pParent = GetParent();

	if(!pParent.IsWindow())
		return RGB(255, 255, 255);

	HDC hDC = ::GetDC(pParent.m_hWnd);

	if(hDC == NULL)
		return RGB(255, 255, 255);

	return ::GetBkColor(hDC);
}

// a couple of helper functions:
int GetBiggest(int n1, int n2)
{
	if (n2 <= n1)	
		return n1;
	if (n2 > n1)	
		return n2;
	return -1; // equal
}

float GetSmallestF(float f1, float f2)
{
	if (f1 <= f2)	
		return f1;
	if (f2 < f1)	
		return f2;
	return -1.0f; // equal
}

BOOL CXUI_ImageCtrl::DrawImage(CDC* pDC, CPoint ptCenter, CRect rectImage)
{
	BOOL bRet = TRUE;
    if(pDC == NULL || m_Picture == NULL)
        return !bRet;

    //Get width and height of picture
    long hmWidth  = 0;
    long hmHeight = 0;

	m_Picture->get_Width(&hmWidth);
	m_Picture->get_Height(&hmHeight);

	CSize szImg(hmWidth, hmHeight);
	pDC->HIMETRICtoLP(&szImg);

	int nLeft, nTop, nRight, nBottom;
	CRect rcDest = rectImage, rcSrc = CRect(0, 0, szImg.cx, szImg.cy);
		
	// if the image wont fit without being shrunk...
	if(m_bStretch == false)
	{
		if (GetBiggest(rcDest.Width(), rcSrc.Width()) == rcSrc.Width() ||
			GetBiggest(rcDest.Height(), rcSrc.Height()) == rcSrc.Height())
		{
			float nDX = (float)rcDest.Width(), nDY = (float)rcDest.Height(),
				  nSX = (float)rcSrc.Width(), nSY = (float)rcSrc.Height();
			float nModX = nDX / nSX;
			float nModY = nDY / nSY;
			float nMod = GetSmallestF(nModX, nModY);
			
			// float -> int conversion
			nRight = (int)(rcSrc.Width() * nMod);
			nBottom = (int)(-(rcSrc.Height() * nMod));
			nLeft = rcDest.left + (rcDest.Width() / 2) - (nRight / 2);
			nTop = rcDest.top + (rcDest.Height() / 2) - (nBottom / 2);
		}
		else
		{
			// center the image
			nLeft = rcDest.left + (rcDest.Width() / 2) - (szImg.cx / 2);
			nTop = rcDest.top + (rcDest.Height() / 2) - (szImg.cy / 2) + szImg.cy;
			nRight = szImg.cx;
			nBottom = -(szImg.cy);
		}
	}
	else
	{
		nLeft = rcDest.left;
		nTop = rcDest.top;
		nRight = rcSrc.Width();
		nBottom = -rcSrc.Height();
	}

    HRESULT hr = m_Picture->Render(pDC->m_hDC, nLeft, nTop, nRight, nBottom,
			0, 0, hmWidth, hmHeight, NULL);
		
    bRet = (SUCCEEDED(hr));

    return bRet;
}

#endif