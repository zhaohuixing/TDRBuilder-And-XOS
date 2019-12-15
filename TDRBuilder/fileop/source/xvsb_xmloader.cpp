// 2005/02/21
#include "xvsb_xmloader.h"
#include "xdom_domclassinc.h"

bool CVSB_MSDOMXMLLoader::operator () (const std::wstring& szFile, CXML_hXML* pXML)
{
	bool bRet = false;

	CDOM_MSDOMParser mDOMParser;
	bRet = mDOMParser.Load(szFile);
	if(bRet)
		bRet = mDOMParser.ExploreXMLTree(pXML);

	return bRet;
}

bool CVSB_MSDOMXMLLoader::operator () (const wchar_t* szFile, CXML_hXML* pXML)
{
	bool bRet = false;

	CDOM_MSDOMParser mDOMParser;
	bRet = mDOMParser.Load(szFile);
	if(bRet)
		bRet = mDOMParser.ExploreXMLTree(pXML);

	return bRet;
}