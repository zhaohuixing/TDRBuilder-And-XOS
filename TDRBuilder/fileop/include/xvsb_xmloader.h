// 2005/02/21
#ifndef __XVSB_XMLOADER_H__
#define __XVSB_XMLOADER_H__

#include "xxml_tag.h"

class CVSB_MSDOMXMLLoader
{
public:
	CVSB_MSDOMXMLLoader(){};

public:
	bool operator () (const std::wstring& szFile, CXML_hXML* pXML);
	bool operator () (const wchar_t* szFile, CXML_hXML* pXML);
};

#endif