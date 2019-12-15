// Project: Visual System Builder
//
// File Name: ivsb_cpobuf.h
//
// Description: The definition of the abstrct interface of the source code output 
//				buffer.
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
#pragma warning(disable:4530)
#ifndef __IVSB_CPOBUF_H__
#define __IVSB_CPOBUF_H__

#include <string>

class IVSB_TextOutBuffer
{
public:
	IVSB_TextOutBuffer():m_Text(){};
	virtual ~IVSB_TextOutBuffer(){};

public:
	std::wstring m_Text;  // output text buffer

public:
	virtual void PutLine(void) = 0;

    void PutLine(const wchar_t *pText)
    {
		m_Text = pText;
		PutLine();
    }

	const wchar_t* GetBuffer(void)
	{
		return m_Text.c_str();
	}
};

#endif