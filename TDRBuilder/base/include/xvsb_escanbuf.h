#ifndef __XVSB_ESCANBUF_H__
#define __XVSB_ESCANBUF_H__

#include "ivsb_inbuf.h"
#include "xvsb_pre.h"

class XVSB_CLASS CVSB_ExpScanBuffer : public IVSB_ScanBufferBase
{
public:
	CVSB_ExpScanBuffer(void);
	
	CVSB_ExpScanBuffer(IVSB_CPScanBufferHandle* pBuf);

	virtual ~CVSB_ExpScanBuffer(void);


//
//@access:
//
protected:
	//@cmember: Get the on char current line
    virtual wchar_t GetLine(void);

//
//@access:
//
public:
	virtual int GetCurrentLineNumber(void);

	virtual bool StartUp(void);

protected:
	int m_CurrentNestingLevel;
	int m_CurrentLineNumber;

};

#endif