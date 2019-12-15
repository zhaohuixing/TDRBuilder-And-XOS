// Project: Visual System Builder
//
// File Name: ivsb_inbuf.h
//
// Description: The definition of the abstrct interface of the source code input 
//				buffer which wrap up the input soruce handle object	
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
#ifndef __IVSB_INBUF_H__
#define __IVSB_INBUF_H__

#include "xvsb_cpbuf.h"
#include "xvsb_wcutil.h"

class IVSB_ScanBufferBase 
{
//
//@access: Attributes
//
protected:
	//@cmember: Source code buffer handle
	IVSB_CPScanBufferHandle*	m_BufferHandle;

	//@cmember: Pointer to the current reading char in the text buffer
    wchar_t*					m_pChar;                

	//@cmember: Current reading char position
	int  m_nCurrentPos;    

//
//@access:
//
protected:
	//@cmember: Get the on char current line
    virtual wchar_t GetLine(void) = 0;

//
//@access:
//
public:
	IVSB_ScanBufferBase(void)
	{
		m_BufferHandle = NULL;
		m_nCurrentPos = 0;
		m_pChar = NULL;
	}

	IVSB_ScanBufferBase(IVSB_CPScanBufferHandle* pBuf)
	{
		m_BufferHandle = pBuf;
		m_nCurrentPos = 0;
		m_pChar = NULL;
	}

    virtual ~IVSB_ScanBufferBase(void)
    {
		ShutDown();
    }

    inline wchar_t Char(void) const 
	{ 
		return *m_pChar; 
	}

    inline wchar_t WChar(void) const 
	{ 
		return *m_pChar; 
	}

	inline wchar_t GetChar(void)
	{
		const int tabSize = 8;		// size of tabs
		char ct;
		wchar_t ch;					// character to return

		if(IsBadString(m_pChar) || IsEOF(*m_pChar)) 
		{
			ct = 0x7F;
			Ascii2WChar(ct, ch); 
			// end of file
			return ch;  
		}
		else if(*m_pChar == L'\0' || *m_pChar == L'\n')    
		{
			// end of line
			ch = GetLine();  
		}
		else 
		{                                       // next char
			++m_pChar;
			++m_nCurrentPos;
			ch = *m_pChar;
		}

		//--If tab character, increment inputPosition to the next
		//--multiple of tabSize.
		if(ch == L'\t') 
		{
			m_nCurrentPos += tabSize - m_nCurrentPos%tabSize;
		}
		return ch;
	}
    

	inline wchar_t PutBackChar(void)
	{
		--m_pChar;
		--m_nCurrentPos;
		return *m_pChar;
	}

	inline virtual bool StartUp(void)
	{
		if(m_BufferHandle == NULL || !m_BufferHandle->StartUp())
		{
			return false;
		}
		m_nCurrentPos = 0;
		m_pChar = NULL;
		return true;
	}

	inline virtual bool ShutDown(void)
	{
		if(m_BufferHandle != NULL)
		{
			delete m_BufferHandle;
			m_BufferHandle = NULL;
		}
		m_nCurrentPos = 0;
		m_pChar = NULL;
		return true;
	}

	inline virtual void SetBufferHandle(IVSB_CPScanBufferHandle* pBuf)
	{
		if(m_BufferHandle != NULL)
		{
			delete m_BufferHandle;
		}
		m_BufferHandle = pBuf;
	}

	inline virtual int GetCurrentPos(void)
	{
		return m_nCurrentPos;
	}

	virtual int GetCurrentLineNumber(void) = 0;
};


#endif