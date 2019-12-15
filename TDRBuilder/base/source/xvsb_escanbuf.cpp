#include "xvsb_escanbuf.h"
#include "xvsb_wcutil.h"

CVSB_ExpScanBuffer::CVSB_ExpScanBuffer(void) : IVSB_ScanBufferBase()
{
	m_CurrentNestingLevel = 0;
	m_CurrentLineNumber = 0;
}

CVSB_ExpScanBuffer::CVSB_ExpScanBuffer(IVSB_CPScanBufferHandle* pBuf) : IVSB_ScanBufferBase(pBuf)
{
	m_CurrentNestingLevel = 0;
	m_CurrentLineNumber = 0;
}

CVSB_ExpScanBuffer::~CVSB_ExpScanBuffer(void)
{
}

wchar_t CVSB_ExpScanBuffer::GetLine(void)
{
    //--If at the end of the source file, return the end-of-file char.
	char ct = 0x7F;
	wchar_t ch;
	Ascii2WChar(ct, ch); 
    if(m_BufferHandle == NULL) 
	{
		return ch;
	}
    else //--Else read the next source line and print it to the list file.
	{
		if(m_BufferHandle->IsDirectBuffer())
		{
			++m_pChar;   // point to first source line char
			std::wstring szCheck = m_pChar;
			if(szCheck.empty())
			{
				return ch;
			}
			//PrintLine();
		}
		else
		{
			m_pChar = (wchar_t*)m_BufferHandle->GetBuffer();
			if(IsEOF(*m_pChar))
			{
				return ch;
			}
			//PrintLine();
		}
    }

    m_nCurrentPos = 0;
    return *m_pChar;
}

int CVSB_ExpScanBuffer::GetCurrentLineNumber(void)
{
	return m_CurrentLineNumber;
}

bool CVSB_ExpScanBuffer::StartUp(void)
{
	bool bRet = false;
	if(m_BufferHandle == NULL)
		return bRet;

	//m_List.Initialize(m_BufferHandle->GetFileName());
	if(IVSB_ScanBufferBase::StartUp())
	{
		m_pChar = (wchar_t*)m_BufferHandle->GetBuffer();
		if(!IsEOF(*m_pChar))
		{
			//PrintLine();
			bRet = true;
		}
	}
	return bRet;
}