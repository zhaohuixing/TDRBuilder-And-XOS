// Project: Visual System Builder
//
// File Name: xvsb_wcutil.h
//
// Description: The unicode char utility function
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/24/2005	
//
// History:
// 1.    01/24/2005: Create	
//
#ifndef __XVSB_WCUTIL_H__
#define __XVSB_WCUTIL_H__

#include <stdlib.h>
#include <string>

extern "C"
{
	inline bool IsEOF(wchar_t wc)
	{
		bool bRet = false;
		char c = 0;
		if(wctomb(&c, wc) == -1)
			return bRet;

		bRet = (c == 0x7F);
		return bRet;
	}

	inline bool IsNewLine(wchar_t wc)
	{
		bool bRet = false;
		char c = 0;
		if(wctomb(&c, wc) == -1)
			return bRet;

		bRet = (c == '\0');
		return bRet;
	}

	inline bool IsSameChar(wchar_t wc, char c)
	{
		bool bRet = false;
		char ct = 0;
		if(wctomb(&ct, wc) == -1)
			return bRet;

		bRet = (ct == c);
		return bRet;
	}

	inline bool Ascii2WChar(char c, wchar_t& wc)
	{
		bool bRet = (mbtowc(&wc, &c, 1) == -1);
		return bRet;
	}

	inline bool WChar2Ascii(wchar_t wc, char& c)
	{
		bool bRet = false;
		if(wctomb(&c, wc) == -1)
			return bRet;
		else
			bRet = true;

		return bRet;
	}

	inline char WC2Char(wchar_t wc)
	{
		char c = 0;
		wctomb(&c, wc);
		return c;
	}

	inline wchar_t C2WChar(char c)
	{
		wchar_t wc = 0;
		mbtowc(&wc, &c, 1);
		return wc;
	}

	inline wchar_t EOFWC(void)
	{
		return C2WChar(0x7F);
	}

	inline bool IsBadString(wchar_t* ws)
	{
		std::wstring str = ws;
		return str.empty();
	}
};

#endif