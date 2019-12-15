// 2005/02/21
#include "xvsb_xpltrans.h"
#include "xvsb_xmloader.h"
#include "xdom_domclassinc.h"
#include "xvsb_xml2mod.h"
#include "xvsb_defs.h"

CVSB_XPLTranslator::CVSB_XPLTranslator(void)
	:m_szXMLFile(), m_szError()
{
}

CVSB_XPLTranslator::CVSB_XPLTranslator(const std::wstring& szFile)
	:m_szXMLFile(szFile), m_szError()
{
}

CVSB_XPLTranslator::CVSB_XPLTranslator(const wchar_t* szFile)
	:m_szXMLFile(szFile), m_szError()
{
}

bool CVSB_XPLTranslator::operator () (const std::wstring& szFile, CVSB_Module* pModule)
{
	bool bRet = false;

	if(pModule == NULL)
	{
		m_szError = XVSB_STR_NOMODULEOBJ;
		return bRet;
	}

	m_szXMLFile = szFile;

	if(m_szXMLFile.empty())
	{
		m_szError = XVSB_STR_NOFILENAME;
		return bRet;
	}

	bRet = _translate(&pModule);

	return bRet;
}

bool CVSB_XPLTranslator::operator () (const wchar_t* szFile, CVSB_Module* pModule)
{
	bool bRet = false;

	if(pModule == NULL)
	{
		m_szError = XVSB_STR_NOMODULEOBJ;
		return bRet;
	}

	m_szXMLFile = szFile;

	if(m_szXMLFile.empty())
	{
		m_szError = XVSB_STR_NOFILENAME;
		return bRet;
	}

	bRet = _translate(&pModule);

	return bRet;
}

bool CVSB_XPLTranslator::operator () (CVSB_Module*	pModule)
{
	bool bRet = false;

	if(pModule == NULL)
	{
		m_szError = XVSB_STR_NOMODULEOBJ;
		return bRet;
	}

	if(m_szXMLFile.empty())
	{
		m_szError = XVSB_STR_NOFILENAME;
		return bRet;
	}

	bRet = _translate(&pModule);

	return bRet;
}

std::wstring CVSB_XPLTranslator::GetError(void)
{
	return m_szError;
}

const wchar_t* CVSB_XPLTranslator::GetError(void) const
{
	return m_szError.c_str();
}

bool CVSB_XPLTranslator::_translate(CVSB_Module** pModule)
{
	bool bRet = false;

	CDOM_MSDOMParser	msDOMParser;

	bRet = msDOMParser.Load(m_szXMLFile);
	if(!bRet)
	{
		m_szError = XVSB_STR_FAILTOLOAD;
		return bRet;
	}
	
	CXML_hXML hXML = CXML_CreateXMLTree();
	if(hXML == NULL)
	{
		m_szError = XVSB_STR_FAILALLOC;
		return bRet;
	}

	bRet = msDOMParser.ExploreXMLTree(&hXML);
	if(!bRet)
	{
		m_szError = XVSB_STR_FAILXMLTREE;
		return bRet;
	}

	bRet = _xml2module(&hXML, pModule);

	CXML_DeleteXMLTree(hXML);

	return bRet;
}

bool CVSB_XPLTranslator::_xml2module(CXML_hXML* pXML, CVSB_Module** pModule)
{
	bool bRet = false;

	CVSB_XMLConvModule xmltrans;
	bRet = xmltrans(pXML, pModule);
	m_szError = xmltrans.GetError();

	return bRet;
}

