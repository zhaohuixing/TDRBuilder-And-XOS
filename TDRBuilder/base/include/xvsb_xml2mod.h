#ifndef __XVSB_XML2MOD_H__
#define __XVSB_XML2MOD_H__

#include "xvsb_module.h"
#include "xxml_tag.h"
#include "xvsb_pre.h"
#include "xvsb_array.h"
#include "xvsb_defs.h"

class XVSB_CLASS CVSB_XMLConvModule
{
public:
	CVSB_XMLConvModule();
	~CVSB_XMLConvModule();

public:
	std::wstring GetError(void);
	const wchar_t* GetError(void) const;

	bool operator () (CXML_hXML* pXML, CVSB_Module** pModule);

private:
	bool _xml2module(void);

	bool _readxpltag(void);
	bool _readmoduletag(void);
	bool _readentrytag(void);
	bool _readinitializetag(void);
	bool _readprocessortag(void);
	bool _readinputtag(void);
	bool _readglobaltag(void);
	bool _readlocaltag(void);
	bool _readvariabletag(void);
	bool _readarraytag(void);
	bool _readarrayelementtag(void);

	bool _readcomeintag(void);
	bool _readgototag(void);
	bool _readyesgototag(void);
	bool _readnogototag(void);
	bool _readmethodtag(void);
	IVSB_ProcessorBase* _createpuobject(std::wstring& szName, int nID, enXVSB_PUTYPE puType);

	bool _addequation(std::wstring& szText);
	bool _addcomparsion(std::wstring& szText);

private:
	std::wstring			m_szError;
	CXML_hXML				m_hXML;
	CXML_hXML				m_hXMLCursor;
	CVSB_Module*			m_pModule;
	IVSB_ProcessorBase*		m_hPUCursor;
	CVSB_Array*				m_pArrayCur;

	int						m_nVRead;
};

#endif