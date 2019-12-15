//2005/03/02
#ifndef __XVOA_EXCELEXPORT_H__
#define __XVOA_EXCELEXPORT_H__

#include "xvsb_module.h"
#include "xvsb_pre.h"
#include "xvoa_excelapp.h"
#include "xvoa_excelrange.h"
#include "xvoa_excelwbk.h"
#include "xvoa_excelwbks.h"
#include "xvoa_excelwsht.h"
#include "xvoa_excelwshts.h"

class CVOA_ExcelExport
{
public:
	CVOA_ExcelExport();
	~CVOA_ExcelExport();

public:
	bool CanExport2Excel(void);
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
	CVOA_ExcelApp			m_xlsApp;
	CVOA_ExcelWorkbook		m_xlsWBook;
	CVOA_ExcelWorkbooks		m_xlsWBooks;
	CVOA_ExcelWorksheet		m_xlsWSheet;
	CVOA_ExcelWorksheets	m_xlsWSheets;
	CVOA_ExcelRange			m_xlsRange;
	int						m_nCurRow;
};


#endif