// 2005/02/21
#ifndef __XVSB_XPLTRANS_H__
#define __XVSB_XPLTRANS_H__

#include "xvsb_module.h"
#include "xxml_tag.h"
#include "xvsb_pre.h"

class XVSB_CLASS CVSB_XPLTranslator
{
public:
	CVSB_XPLTranslator();
	CVSB_XPLTranslator(const std::wstring& szFile);
	CVSB_XPLTranslator(const wchar_t* szFile);

public:
	bool operator () (const std::wstring& szFile, CVSB_Module* pModule);
	bool operator () (const wchar_t* szFile, CVSB_Module* pModule);
	bool operator () (CVSB_Module*	pModule);

	std::wstring GetError(void);
	const wchar_t* GetError(void) const;

private:
	bool _translate(CVSB_Module** pModule);
	bool _xml2module(CXML_hXML* pXML, CVSB_Module** pModule);

private:
	std::wstring		m_szXMLFile;
	std::wstring		m_szError;
};

#endif