//2005/03/02
#ifndef __XVOA_WORDEXPORT_H__
#define __XVOA_WORDEXPORT_H__

#include "xvsb_module.h"
#include "xvsb_pre.h"
#include "xvoa_wordapp.h"
#include "xvoa_wordrange.h"
#include "xvoa_worddocs.h"
#include "xvoa_worddoc.h"
#include "xvoa_wordtbls.h"
#include "xvoa_wordtbl.h"
#include "xvoa_wordparagraphs.h"
#include "xvoa_wordparagraph.h"
#include "xvoa_wordsel.h"
#include "xvsb_lpu.h"
#include "xvsb_spu.h"


class CVOA_WordExport
{
public:
	CVOA_WordExport();
	~CVOA_WordExport();

public:
	bool CanExport2Word(void);
	bool ExportResult(const std::wstring& szFile, CVSB_Module* pModule, bool bShow);
	bool ExportResult(const wchar_t* szFile, CVSB_Module* pModule, bool bShow);
	bool ExportResult2(const std::wstring& szFile, CVSB_Module* pModule, bool bLocal, bool bShow);
	bool ExportResult2(const wchar_t* szFile, CVSB_Module* pModule, bool bLocal, bool bShow);

	bool ExportModule(const std::wstring& szFile, CVSB_Module* pModule, bool bShow);
	bool ExportModule(const wchar_t* szFile, CVSB_Module* pModule, bool bShow);

	void Close(void);

	bool ExportInput(CVSB_Module* pModule, bool bFinalVal);
	bool ExportGlobal(CVSB_Module* pModule, bool bFinalVal);
	bool ExportLocal(CVSB_Module* pModule, bool bFinalVal);
	bool ExportPU(CVSB_Module* pModule);

protected:
	bool ExportInitPU(CVSB_Module* pModule);
	bool ExportSPU(CVSB_SPU* pSPU);
	bool ExportLPU(CVSB_LPU* pLPU);

protected:
	CVOA_WordApp			m_wdApp;
	CVOA_WordRange			m_wdRange;
	CVOA_Documents			m_wdDocuments;
	CVOA_Document			m_wdDoc;
	CVOA_WordParagraphs		m_wdParagraphs;
	CVOA_WordParagraph		m_wdPara;
	CVOA_Tables				m_wdTables;	
	CVOA_Table				m_wdTable;	
	CVOA_Selection			m_wdSelection;

	int						m_nCurRow;
	int						m_nCurPURow;

};


#endif