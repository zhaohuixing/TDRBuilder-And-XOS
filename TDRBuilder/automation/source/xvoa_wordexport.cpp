//2005/03/04
#include "stdafx.h"
#include "xvoa_wordexport.h"
#include "xvoa_wordfont.h"
#include "xvsb_macro.h"
#include "xvsb_defs.h"
#include "xvsb_filconst.h"
#include "xvsb_array.h"
#include "xvoa_wordcell.h"


// Word versions
enum enXVOA_WORDVERSION 
{									
	enXVOA_WORDVERSION9 = 0,								// New version
	enXVOA_WORDVERSION8,							// Word8 (Office97)
	enXVOA_WORDVERSION5,								// Word5 (Office95)
};

// Word ProgIDs for every version of Word
const OLECHAR FAR* szWordProgID[] = 
{					
	OLESTR("Word.Application"),							// Word ProgID
	OLESTR("Word.Application.8"),						// Word8 ProgID
	OLESTR("Word.Application.5"),						// Word5 ProgID
};

typedef struct XVOA_FONTSET
{
	CStringW	m_FontName;
	float		m_FontSize;
	long		m_FontBold;

	XVOA_FONTSET(LPCTSTR szName, float nSize, long nBold)
	{
		m_FontName = szName;
		m_FontSize = nSize;
		m_FontBold = nBold;
	}

} XVOA_FONTSET;

const XVOA_FONTSET  fontTitle1(_T("Times New Roman"), 14.0, 1);
const XVOA_FONTSET  fontTitle2(_T("Times New Roman"), 12.0, 1);
const XVOA_FONTSET  fontTitle3(_T("Arial"), 8.0, 1);
const XVOA_FONTSET  fontText(_T("Arial"), 8.0, 0);

CVOA_WordExport::CVOA_WordExport()
{
	m_nCurRow = 0;
}

CVOA_WordExport::~CVOA_WordExport()
{
	m_nCurRow = 0;
	Close();
}

bool CVOA_WordExport::CanExport2Word(void)
{
	// Check avaliable CLSID of Word application
    CLSID	clsid;
    for (int i = enXVOA_WORDVERSION9; i <= enXVOA_WORDVERSION5; i++ )
    {
		if (SUCCEEDED(CLSIDFromProgID(szWordProgID[i], &clsid)))
		{
			return true;
		}
    }
    return false;
}

bool CVOA_WordExport::ExportResult(const std::wstring& szFile, CVSB_Module* pModule, bool bShow)
{
	return ExportResult(szFile.c_str(), pModule, bShow);
}

bool CVOA_WordExport::ExportResult(const wchar_t* szFile, CVSB_Module* pModule, bool bShow)
{
	bool			bRet = false;
    CStringW		szProgID;
    CStringW		szText;
	bool			bStart = false;
    long			nWordVer;
	COleVariant		covOptional(DISP_E_PARAMNOTFOUND, VT_ERROR);
    COleVariant		vTrue((short)TRUE),  vFalse((short)FALSE);

	if(pModule == NULL || szFile == NULL)
		return bRet;

	m_nCurRow = 0;
	if(m_wdApp.m_lpDispatch == NULL) 
	{
		for(long i = enXVOA_WORDVERSION9; i <= enXVOA_WORDVERSION5; i++)
		{
			szProgID = szWordProgID[i];
			if(m_wdApp.CreateDispatch(szProgID.GetBuffer()))
			{
				bStart = true;
				nWordVer = i;
				szProgID.ReleaseBuffer();
				break;
			}
			szProgID.ReleaseBuffer();
		}
	}
    if(!bStart)
    {
		return bRet;
    }
	if(bShow)
	{
		// Show Excel to the user.
		m_wdApp.put_Visible(TRUE);
	}
	else
	{
		m_wdApp.put_Visible(FALSE);
	}

	m_wdDocuments = m_wdApp.get_Documents();
	m_wdDoc = m_wdDocuments.AddOld(covOptional, covOptional);
	m_wdDoc = m_wdApp.get_ActiveDocument();

	m_wdRange = m_wdDoc.get_Content();

	CVOA_WordFont	fontT1(m_wdRange.get_Font());
	fontT1.put_Name(fontTitle1.m_FontName);
	fontT1.put_Bold(fontTitle1.m_FontBold);
	fontT1.put_Size(fontTitle1.m_FontSize);

	szText = XVSM_MACRO_MODULE;
	szText += _T(": ");
	szText += pModule->GetName().c_str();
	m_wdRange.put_Text(szText.GetBuffer());

	szText.GetBuffer();
	m_wdRange.InsertParagraphAfter();
	m_wdRange.Collapse(COleVariant((short)0));	
	m_wdRange.InsertParagraphAfter();
	m_wdRange.Collapse(COleVariant((short)0));	

	m_nCurRow += 2;

	bRet = ExportInput(pModule, true);

	if(!bRet)
	{
		if(m_wdDoc.m_lpDispatch)
		{
			m_wdDoc.Close(vFalse, vTrue, vFalse);
			m_wdDoc.ReleaseDispatch();
			m_wdDoc.m_lpDispatch = NULL;
		}
		Close();
		return bRet;
	}

	bRet = ExportGlobal(pModule, true);
	if(!bRet)
	{
		if(m_wdDoc.m_lpDispatch)
		{
			m_wdDoc.Close(vFalse, vTrue, vFalse);
			m_wdDoc.ReleaseDispatch();
			m_wdDoc.m_lpDispatch = NULL;
		}
		Close();
		return bRet;
	}

	bRet = ExportLocal(pModule, true);
	if(!bRet)
	{
		if(m_wdDoc.m_lpDispatch)
		{
			m_wdDoc.Close(vFalse, vTrue, vFalse);
			m_wdDoc.ReleaseDispatch();
			m_wdDoc.m_lpDispatch = NULL;
		}
		Close();
		return bRet;
	}

	long nFmt = m_wdDoc.get_SaveFormat();
	szText = szFile;
	m_wdDoc.SaveAs(COleVariant(szText.GetBuffer()), 
				   COleVariant((short)nFmt), vFalse, COleVariant(_T("")), vTrue, COleVariant(_T("")),
                   vFalse, vFalse, vFalse, vFalse, vFalse);

	m_wdDoc.Close(vFalse, vTrue, vFalse);
	szText.ReleaseBuffer();
    m_wdDoc.ReleaseDispatch();
	m_wdDoc.m_lpDispatch = NULL;

	Close();
	return bRet;
}

bool CVOA_WordExport::ExportResult2(const std::wstring& szFile, CVSB_Module* pModule, bool bLocal, bool bShow)
{
	return ExportResult2(szFile.c_str(), pModule, bLocal, bShow);
}

bool CVOA_WordExport::ExportResult2(const wchar_t* szFile, CVSB_Module* pModule, bool bLocal, bool bShow)
{
	bool			bRet = false;
    CStringW		szProgID;
    CStringW		szText;
	bool			bStart = false;
    long			nWordVer;
	COleVariant		covOptional(DISP_E_PARAMNOTFOUND, VT_ERROR);
    COleVariant		vTrue((short)TRUE),  vFalse((short)FALSE);

	if(pModule == NULL || szFile == NULL)
		return bRet;

	m_nCurRow = 0;
	if(m_wdApp.m_lpDispatch == NULL) 
	{
		for(long i = enXVOA_WORDVERSION9; i <= enXVOA_WORDVERSION5; i++)
		{
			szProgID = szWordProgID[i];
			if(m_wdApp.CreateDispatch(szProgID.GetBuffer()))
			{
				bStart = true;
				nWordVer = i;
				szProgID.ReleaseBuffer();
				break;
			}
			szProgID.ReleaseBuffer();
		}
	}
    if(!bStart)
    {
		return bRet;
    }
	if(bShow)
	{
		// Show Excel to the user.
		m_wdApp.put_Visible(TRUE);
	}
	else
	{
		m_wdApp.put_Visible(FALSE);
	}

	m_wdDocuments = m_wdApp.get_Documents();
	m_wdDoc = m_wdDocuments.AddOld(covOptional, covOptional);
	m_wdDoc = m_wdApp.get_ActiveDocument();

	m_wdRange = m_wdDoc.get_Content();

	CVOA_WordFont	fontT1(m_wdRange.get_Font());
	fontT1.put_Name(fontTitle1.m_FontName);
	fontT1.put_Bold(fontTitle1.m_FontBold);
	fontT1.put_Size(fontTitle1.m_FontSize);

	szText = XVSM_MACRO_MODULE;
	szText += _T(": ");
	szText += pModule->GetName().c_str();
	m_wdRange.put_Text(szText.GetBuffer());

	szText.GetBuffer();
	m_wdRange.InsertParagraphAfter();
	m_wdRange.Collapse(COleVariant((short)0));	
	m_wdRange.InsertParagraphAfter();
	m_wdRange.Collapse(COleVariant((short)0));	

	m_nCurRow += 2;

	bRet = ExportInput(pModule, true);

	if(!bRet)
	{
		if(m_wdDoc.m_lpDispatch)
		{
			m_wdDoc.Close(vFalse, vTrue, vFalse);
			m_wdDoc.ReleaseDispatch();
			m_wdDoc.m_lpDispatch = NULL;
		}
		Close();
		return bRet;
	}

	bRet = ExportGlobal(pModule, true);
	if(!bRet)
	{
		if(m_wdDoc.m_lpDispatch)
		{
			m_wdDoc.Close(vFalse, vTrue, vFalse);
			m_wdDoc.ReleaseDispatch();
			m_wdDoc.m_lpDispatch = NULL;
		}
		Close();
		return bRet;
	}

	if(bLocal)
	{
		bRet = ExportLocal(pModule, true);
		if(!bRet)
		{
			if(m_wdDoc.m_lpDispatch)
			{
				m_wdDoc.Close(vFalse, vTrue, vFalse);
				m_wdDoc.ReleaseDispatch();
				m_wdDoc.m_lpDispatch = NULL;
			}
			Close();
			return bRet;
		}
	}

	long nFmt = m_wdDoc.get_SaveFormat();
	szText = szFile;
	m_wdDoc.SaveAs(COleVariant(szText.GetBuffer()), 
				   COleVariant((short)nFmt), vFalse, COleVariant(_T("")), vTrue, COleVariant(_T("")),
                   vFalse, vFalse, vFalse, vFalse, vFalse);

	m_wdDoc.Close(vFalse, vTrue, vFalse);
	szText.ReleaseBuffer();
    m_wdDoc.ReleaseDispatch();
	m_wdDoc.m_lpDispatch = NULL;

	Close();
	return bRet;
}

bool CVOA_WordExport::ExportModule(const std::wstring& szFile, CVSB_Module* pModule, bool bShow)
{
	return ExportModule(szFile.c_str(), pModule, bShow);
}

bool CVOA_WordExport::ExportModule(const wchar_t* szFile, CVSB_Module* pModule, bool bShow)
{
	bool			bRet = false;
    CStringW		szProgID;
    CStringW		szText;
	bool			bStart = false;
    long			nWordVer;
	COleVariant		covOptional(DISP_E_PARAMNOTFOUND, VT_ERROR);
    COleVariant		vTrue((short)TRUE),  vFalse((short)FALSE);

	if(pModule == NULL || szFile == NULL)
		return bRet;

	m_nCurRow = 0;
	if(m_wdApp.m_lpDispatch == NULL) 
	{
		for(long i = enXVOA_WORDVERSION9; i <= enXVOA_WORDVERSION5; i++)
		{
			szProgID = szWordProgID[i];
			if(m_wdApp.CreateDispatch(szProgID.GetBuffer()))
			{
				bStart = true;
				nWordVer = i;
				szProgID.ReleaseBuffer();
				break;
			}
			szProgID.ReleaseBuffer();
		}
	}
    if(!bStart)
    {
		return bRet;
    }
	if(bShow)
	{
		// Show Word to the user.
		m_wdApp.put_Visible(TRUE);
	}
	else
	{
		m_wdApp.put_Visible(FALSE);
	}

	m_wdDocuments = m_wdApp.get_Documents();
	m_wdDoc = m_wdDocuments.AddOld(covOptional, covOptional);
	m_wdDoc = m_wdApp.get_ActiveDocument();

	m_wdRange = m_wdDoc.get_Content();

	CVOA_WordFont	fontT1(m_wdRange.get_Font());
	fontT1.put_Name(fontTitle1.m_FontName);
	fontT1.put_Bold(fontTitle1.m_FontBold);
	fontT1.put_Size(fontTitle1.m_FontSize);

	szText = XVSM_MACRO_MODULE;
	szText += _T(": ");
	szText += pModule->GetName().c_str();
	m_wdRange.put_Text(szText.GetBuffer());

	szText.GetBuffer();
	m_wdRange.InsertParagraphAfter();
	m_wdRange.Collapse(COleVariant((short)0));	
	m_wdRange.InsertParagraphAfter();
	m_wdRange.Collapse(COleVariant((short)0));	

	m_nCurRow += 2;

	bRet = ExportInput(pModule, false);

	if(!bRet)
	{
		if(m_wdDoc.m_lpDispatch)
		{
			m_wdDoc.Close(vFalse, vTrue, vFalse);
			m_wdDoc.ReleaseDispatch();
			m_wdDoc.m_lpDispatch = NULL;
		}
		Close();
		return bRet;
	}

	bRet = ExportGlobal(pModule, false);
	if(!bRet)
	{
		if(m_wdDoc.m_lpDispatch)
		{
			m_wdDoc.Close(vFalse, vTrue, vFalse);
			m_wdDoc.ReleaseDispatch();
			m_wdDoc.m_lpDispatch = NULL;
		}
		Close();
		return bRet;
	}

	bRet = ExportLocal(pModule, false);
	if(!bRet)
	{
		if(m_wdDoc.m_lpDispatch)
		{
			m_wdDoc.Close(vFalse, vTrue, vFalse);
			m_wdDoc.ReleaseDispatch();
			m_wdDoc.m_lpDispatch = NULL;
		}
		Close();
		return bRet;
	}

	bRet = ExportPU(pModule);
	if(!bRet)
	{
		if(m_wdDoc.m_lpDispatch)
		{
			m_wdDoc.Close(vFalse, vTrue, vFalse);
			m_wdDoc.ReleaseDispatch();
			m_wdDoc.m_lpDispatch = NULL;
		}
		Close();
		return bRet;
	}

	long nFmt = m_wdDoc.get_SaveFormat();
	szText = szFile;
	m_wdDoc.SaveAs(COleVariant(szText.GetBuffer()), 
				   COleVariant((short)nFmt), vFalse, COleVariant(_T("")), vTrue, COleVariant(_T("")),
                   vFalse, vFalse, vFalse, vFalse, vFalse);

	szText.ReleaseBuffer();
	m_wdDoc.Close(vFalse, vTrue, vFalse);
    m_wdDoc.ReleaseDispatch();
	m_wdDoc.m_lpDispatch = NULL;

	Close();
	return bRet;
}

void CVOA_WordExport::Close(void)
{
    COleVariant vTrue((short)TRUE),
                vFalse((short)FALSE),
                vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	if(m_wdApp.m_lpDispatch != NULL) 
	{
		m_wdApp.Quit(vFalse, vOpt, vOpt);
		m_wdApp.ReleaseDispatch();
		m_wdApp.m_lpDispatch = NULL;
	}
}

bool CVOA_WordExport::ExportInput(CVSB_Module* pModule, bool bFinalVal)
{
	bool			bRet = false;
    CStringW		szText;
    CStringW		szCol;
    CStringW		szTemp;
	COleVariant		covOptional(DISP_E_PARAMNOTFOUND, VT_ERROR);
	long			nCol;
	CVOA_WordCell   tblCell;
	long			i;
	CVOA_WordRange	cellRange;

	if((int)pModule->m_InputVars.m_ObjTbl.size() <= 0)
		return true;

	if(bFinalVal)
	{
		nCol = 4;
	}
	else
	{
		nCol = 3;
	}

	CVOA_WordFont	fontT2(m_wdRange.get_Font());
	fontT2.put_Name(fontTitle2.m_FontName);
	fontT2.put_Bold(fontTitle2.m_FontBold);
	fontT2.put_Size(fontTitle2.m_FontSize);

	szText = XVSM_MACRO_INPUTVAR;
	szText += _T(":");
	m_wdRange.put_Text(szText.GetBuffer());
	szText.GetBuffer();
	m_nCurRow ++;

	m_wdRange.Collapse(COleVariant((short)0));	
	m_wdRange.InsertParagraph();

	//m_wdRange = m_wdDoc.get_Content();//m_wdSelection.get_Range();
	m_wdTables = m_wdRange.get_Tables();
	m_wdTable = m_wdTables.AddOld(m_wdRange, (long)pModule->m_InputVars.m_ObjTbl.size()+1, nCol);
	for(i = 1; i <= nCol; i++)
	{
		szTemp = XVSM_VAR_TITLESTR[i-1];
		tblCell = m_wdTable.Cell(1, i);
		cellRange = tblCell.get_Range();

		CVOA_WordFont	fontT3(cellRange.get_Font());
		fontT3.put_Name(fontTitle3.m_FontName);
		fontT3.put_Bold(fontTitle3.m_FontBold);
		fontT3.put_Size(fontTitle3.m_FontSize);

		cellRange.put_Text(szTemp.GetBuffer());
		szTemp.ReleaseBuffer();
		m_nCurRow ++;
	}

	CVSB_VarObjTable::iterator iter;
	IVSB_DataBase*	pData;
	CStringW		szType;		
	CStringW		szName;		
	CStringW		szVal;
	CStringW		szDefVal;
	long			nIdx;
	long			nStep;

	nStep = 2;
	for(iter = pModule->m_InputVars.m_ObjTbl.begin(); iter != pModule->m_InputVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szName = iter->first.c_str();
		if(pData)
		{
			nIdx = pData->GetDataTypeIndex();
			szType = XVSM_DTSTR[nIdx];
			szDefVal = pData->GetDefaultValueStr().c_str();
			i = 1;
			tblCell = m_wdTable.Cell(nStep, i);
			cellRange = tblCell.get_Range();
			CVOA_WordFont	fonti1(cellRange.get_Font());
			fonti1.put_Name(fontText.m_FontName);
			fonti1.put_Bold(fontText.m_FontBold);
			fonti1.put_Size(fontText.m_FontSize);
			cellRange.put_Text(szName.GetBuffer());
			szName.ReleaseBuffer();

			i = 2;
			tblCell = m_wdTable.Cell(nStep, i);
			cellRange = tblCell.get_Range();
			CVOA_WordFont	fonti2(cellRange.get_Font());
			fonti2.put_Name(fontText.m_FontName);
			fonti2.put_Bold(fontText.m_FontBold);
			fonti2.put_Size(fontText.m_FontSize);
			cellRange.put_Text(szType.GetBuffer());
			szType.ReleaseBuffer();

			i = 3;
			tblCell = m_wdTable.Cell(nStep, i);
			cellRange = tblCell.get_Range();
			CVOA_WordFont	fonti3(cellRange.get_Font());
			fonti3.put_Name(fontText.m_FontName);
			fonti3.put_Bold(fontText.m_FontBold);
			fonti3.put_Size(fontText.m_FontSize);
			cellRange.put_Text(szDefVal.GetBuffer());
			szDefVal.ReleaseBuffer();
			if(nCol == 4)
			{
				szVal = pData->GetDataValueStr().c_str();

				i = 4;
				tblCell = m_wdTable.Cell(nStep, i);
				cellRange = tblCell.get_Range();
				CVOA_WordFont	fonti4(cellRange.get_Font());
				fonti4.put_Name(fontText.m_FontName);
				fonti4.put_Bold(fontText.m_FontBold);
				fonti4.put_Size(fontText.m_FontSize);
				cellRange.put_Text(szVal.GetBuffer());
				szVal.ReleaseBuffer();
			}
			nStep++;
			m_nCurRow ++;
		}
	}
	m_nCurRow +=2;

	m_wdRange = m_wdTable.get_Range();

	m_wdRange.Collapse(COleVariant((short)0));	
	m_wdRange.InsertParagraph();
	m_wdRange.Collapse(COleVariant((short)0));	
	m_wdRange.InsertParagraph();
	m_wdRange.Collapse(COleVariant((short)0));	

	bRet = true;
	return bRet;
}

bool CVOA_WordExport::ExportGlobal(CVSB_Module* pModule, bool bFinalVal)
{
	bool			bRet = false;
    CStringW		szText;
    CStringW		szCol;
    CStringW		szTemp;
	COleVariant		covOptional(DISP_E_PARAMNOTFOUND, VT_ERROR);
	long			nCol;
	CVOA_WordCell   tblCell;
	long			i;
	CVOA_WordRange	cellRange;

	if((int)pModule->m_OutputVars.m_ObjTbl.size() <= 0)
		return true;

	if(bFinalVal)
	{
		nCol = 4;
	}
	else
	{
		nCol = 3;
	}

	CVOA_WordFont	fontT2(m_wdRange.get_Font());
	fontT2.put_Name(fontTitle2.m_FontName);
	fontT2.put_Bold(fontTitle2.m_FontBold);
	fontT2.put_Size(fontTitle2.m_FontSize);

	szText = XVSM_MACRO_GLOBALVAR;
	szText += _T(":");
	m_wdRange.put_Text(szText.GetBuffer());
	szText.GetBuffer();
	m_nCurRow ++;

	m_wdRange.Collapse(COleVariant((short)0));	
	m_wdRange.InsertParagraph();

	long nGlobalRows = pModule->GetOutputPrintLineCount();

	m_wdTables = m_wdRange.get_Tables();
	m_wdTable = m_wdTables.AddOld(m_wdRange, nGlobalRows+1, nCol);
	for(i = 1; i <= nCol; i++)
	{
		szTemp = XVSM_VAR_TITLESTR[i-1];
		tblCell = m_wdTable.Cell(1, i);
		cellRange = tblCell.get_Range();

		CVOA_WordFont	fontT3(cellRange.get_Font());
		fontT3.put_Name(fontTitle3.m_FontName);
		fontT3.put_Bold(fontTitle3.m_FontBold);
		fontT3.put_Size(fontTitle3.m_FontSize);

		cellRange.put_Text(szTemp.GetBuffer());
		szTemp.ReleaseBuffer();
		m_nCurRow ++;
	}

	CVSB_VarObjTable::iterator iter;
	IVSB_DataBase*	pData;
	CStringW		szType;		
	CStringW		szName;		
	CStringW		szVal;
	CStringW		szDefVal;
	int				nIdx;
	int				nStep;
	int				nAEType;
	int				nASize;

	nStep = 2;
	for(iter = pModule->m_OutputVars.m_ObjTbl.begin(); iter != pModule->m_OutputVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szName = iter->first.c_str();
		if(pData)
		{
			nIdx = pData->GetDataTypeIndex();
			if(nIdx != XVSM_DT_ARRAY)
			{
				szType = XVSM_DTSTR[nIdx];
				szDefVal = pData->GetDefaultValueStr().c_str();
				i = 1;
				tblCell = m_wdTable.Cell(nStep, i);
				cellRange = tblCell.get_Range();
				CVOA_WordFont	fonti1(cellRange.get_Font());
				fonti1.put_Name(fontText.m_FontName);
				fonti1.put_Bold(fontText.m_FontBold);
				fonti1.put_Size(fontText.m_FontSize);
				cellRange.put_Text(szName.GetBuffer());
				szName.ReleaseBuffer();

				i = 2;
				tblCell = m_wdTable.Cell(nStep, i);
				cellRange = tblCell.get_Range();
				CVOA_WordFont	fonti2(cellRange.get_Font());
				fonti2.put_Name(fontText.m_FontName);
				fonti2.put_Bold(fontText.m_FontBold);
				fonti2.put_Size(fontText.m_FontSize);
				cellRange.put_Text(szType.GetBuffer());
				szType.ReleaseBuffer();

				i = 3;
				tblCell = m_wdTable.Cell(nStep, i);
				cellRange = tblCell.get_Range();
				CVOA_WordFont	fonti3(cellRange.get_Font());
				fonti3.put_Name(fontText.m_FontName);
				fonti3.put_Bold(fontText.m_FontBold);
				fonti3.put_Size(fontText.m_FontSize);
				cellRange.put_Text(szDefVal.GetBuffer());
				szDefVal.ReleaseBuffer();
				if(nCol == 4)
				{
					szVal = pData->GetDataValueStr().c_str();

					i = 4;
					tblCell = m_wdTable.Cell(nStep, i);
					cellRange = tblCell.get_Range();
					CVOA_WordFont	fonti4(cellRange.get_Font());
					fonti4.put_Name(fontText.m_FontName);
					fonti4.put_Bold(fontText.m_FontBold);
					fonti4.put_Size(fontText.m_FontSize);
					cellRange.put_Text(szVal.GetBuffer());
					szVal.ReleaseBuffer();
				}
				nStep++;
				m_nCurRow ++;
			}
			else
			{
				nAEType = ((CVSB_Array*)pData)->GetElementDataTypeIndex();
				szType = XVSM_DTSTR[nAEType];
				nASize = ((CVSB_Array*)pData)->Size();

				i = 1;
				tblCell = m_wdTable.Cell(nStep, i);
				cellRange = tblCell.get_Range();
				CVOA_WordFont	fontia1(cellRange.get_Font());
				fontia1.put_Name(fontText.m_FontName);
				fontia1.put_Bold(fontText.m_FontBold);
				fontia1.put_Size(fontText.m_FontSize);
				cellRange.put_Text(szName.GetBuffer());
				szName.ReleaseBuffer();

				i = 2;
				szText = XVSM_DTSTR[XVSM_DT_ARRAY];
				szText += _T("/");
				szText += szType;
				tblCell = m_wdTable.Cell(nStep, i);
				cellRange = tblCell.get_Range();
				CVOA_WordFont	fontia2(cellRange.get_Font());
				fontia2.put_Name(fontText.m_FontName);
				fontia2.put_Bold(fontText.m_FontBold);
				fontia2.put_Size(fontText.m_FontSize);
				cellRange.put_Text(szText.GetBuffer());
				szText.ReleaseBuffer();

				i = 3;
				szTemp = XVSM_MACRO_ARRAYSIZE;
				szText.Format(_T("%s: %d"), szTemp, nASize);
				tblCell = m_wdTable.Cell(nStep, i);
				cellRange = tblCell.get_Range();
				CVOA_WordFont	fontia3(cellRange.get_Font());
				fontia3.put_Name(fontText.m_FontName);
				fontia3.put_Bold(fontText.m_FontBold);
				fontia3.put_Size(fontText.m_FontSize);
				cellRange.put_Text(szText.GetBuffer());
				szText.ReleaseBuffer();
				
				if(nCol == 4) //Adjust the row text height)
				{
					i = 4;
					tblCell = m_wdTable.Cell(nStep, i);
					cellRange = tblCell.get_Range();
					CVOA_WordFont	fontia41(cellRange.get_Font());
					fontia41.put_Name(fontText.m_FontName);
					fontia41.put_Bold(fontText.m_FontBold);
					fontia41.put_Size(fontText.m_FontSize);
					szText = _T("");
					cellRange.put_Text(szText);
					szText.ReleaseBuffer();
				}
				m_nCurRow++;
				nStep++;

				for(int iLoop = 0; iLoop < nASize; iLoop++)
				{
					szDefVal = ((CVSB_Array*)pData)->At(iLoop)->GetDefaultValueStr().c_str();
					szVal = ((CVSB_Array*)pData)->At(iLoop)->GetDataValueStr().c_str();

					// Adjust the row text height
					i = 1;
					tblCell = m_wdTable.Cell(nStep, i);
					cellRange = tblCell.get_Range();
					CVOA_WordFont	fontia11(cellRange.get_Font());
					fontia11.put_Name(fontText.m_FontName);
					fontia11.put_Bold(fontText.m_FontBold);
					fontia11.put_Size(fontText.m_FontSize);
					szText = _T("");
					cellRange.put_Text(szText);
					szText.ReleaseBuffer();

					i = 2;
					szText.Format(_T("%s[%d]"), szName, iLoop);
					tblCell = m_wdTable.Cell(nStep, i);
					cellRange = tblCell.get_Range();
					CVOA_WordFont	fontia4(cellRange.get_Font());
					fontia4.put_Name(fontText.m_FontName);
					fontia4.put_Bold(fontText.m_FontBold);
					fontia4.put_Size(fontText.m_FontSize);
					cellRange.put_Text(szText.GetBuffer());
					szText.ReleaseBuffer();

					i = 3;
					tblCell = m_wdTable.Cell(nStep, i);
					cellRange = tblCell.get_Range();
					CVOA_WordFont	fontia5(cellRange.get_Font());
					fontia5.put_Name(fontText.m_FontName);
					fontia5.put_Bold(fontText.m_FontBold);
					fontia5.put_Size(fontText.m_FontSize);
					cellRange.put_Text(szDefVal.GetBuffer());
					szDefVal.ReleaseBuffer();

					if(nCol == 4)
					{
						i = 4;
						tblCell = m_wdTable.Cell(nStep, i);
						cellRange = tblCell.get_Range();
						CVOA_WordFont	fontia6(cellRange.get_Font());
						fontia6.put_Name(fontText.m_FontName);
						fontia6.put_Bold(fontText.m_FontBold);
						fontia6.put_Size(fontText.m_FontSize);
						cellRange.put_Text(szVal.GetBuffer());
						szVal.ReleaseBuffer();
					}
					m_nCurRow++;
					nStep++;
				}
			}
		}
	}

	m_wdRange = m_wdTable.get_Range();

	m_wdRange.Collapse(COleVariant((short)0));	
	m_wdRange.InsertParagraph();
	m_wdRange.Collapse(COleVariant((short)0));	
	m_wdRange.InsertParagraph();
	m_wdRange.Collapse(COleVariant((short)0));	

	bRet = true;
	return bRet;
}

bool CVOA_WordExport::ExportLocal(CVSB_Module* pModule, bool bFinalVal)
{
	bool			bRet = false;
    CStringW		szText;
    CStringW		szCol;
    CStringW		szTemp;
	COleVariant		covOptional(DISP_E_PARAMNOTFOUND, VT_ERROR);
	long			nCol;
	CVOA_WordCell   tblCell;
	long			i;
	CVOA_WordRange	cellRange;

	if((int)pModule->m_LocalVars.m_ObjTbl.size() <= 0)
		return true;

	if(bFinalVal)
	{
		nCol = 4;
	}
	else
	{
		nCol = 3;
	}

	CVOA_WordFont	fontT2(m_wdRange.get_Font());
	fontT2.put_Name(fontTitle2.m_FontName);
	fontT2.put_Bold(fontTitle2.m_FontBold);
	fontT2.put_Size(fontTitle2.m_FontSize);

	szText = XVSM_MACRO_LOCALVAR;
	szText += _T(":");
	m_wdRange.put_Text(szText.GetBuffer());
	szText.GetBuffer();
	m_nCurRow ++;

	m_wdRange.Collapse(COleVariant((short)0));	
	m_wdRange.InsertParagraph();

	long nLocalRows = pModule->GetLocalPrintLineCount();

	m_wdTables = m_wdRange.get_Tables();
	m_wdTable = m_wdTables.AddOld(m_wdRange, nLocalRows+1, nCol);
	for(i = 1; i <= nCol; i++)
	{
		szTemp = XVSM_VAR_TITLESTR[i-1];
		tblCell = m_wdTable.Cell(1, i);
		cellRange = tblCell.get_Range();

		CVOA_WordFont	fontT3(cellRange.get_Font());
		fontT3.put_Name(fontTitle3.m_FontName);
		fontT3.put_Bold(fontTitle3.m_FontBold);
		fontT3.put_Size(fontTitle3.m_FontSize);

		cellRange.put_Text(szTemp.GetBuffer());
		szTemp.ReleaseBuffer();
		m_nCurRow ++;
	}

	CVSB_VarObjTable::iterator iter;
	IVSB_DataBase*	pData;
	CStringW		szType;		
	CStringW		szName;		
	CStringW		szVal;
	CStringW		szDefVal;
	long			nIdx;
	long			nStep;
	long			nAEType;
	long			nASize;

	nStep = 2;
	for(iter = pModule->m_LocalVars.m_ObjTbl.begin(); iter != pModule->m_LocalVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szName = iter->first.c_str();
		if(pData)
		{
			nIdx = pData->GetDataTypeIndex();
			if(nIdx != XVSM_DT_ARRAY)
			{
				szType = XVSM_DTSTR[nIdx];
				szDefVal = pData->GetDefaultValueStr().c_str();
				i = 1;
				tblCell = m_wdTable.Cell(nStep, i);
				cellRange = tblCell.get_Range();
				CVOA_WordFont	fonti1(cellRange.get_Font());
				fonti1.put_Name(fontText.m_FontName);
				fonti1.put_Bold(fontText.m_FontBold);
				fonti1.put_Size(fontText.m_FontSize);
				cellRange.put_Text(szName.GetBuffer());
				szName.ReleaseBuffer();

				i = 2;
				tblCell = m_wdTable.Cell(nStep, i);
				cellRange = tblCell.get_Range();
				CVOA_WordFont	fonti2(cellRange.get_Font());
				fonti2.put_Name(fontText.m_FontName);
				fonti2.put_Bold(fontText.m_FontBold);
				fonti2.put_Size(fontText.m_FontSize);
				cellRange.put_Text(szType.GetBuffer());
				szType.ReleaseBuffer();

				i = 3;
				tblCell = m_wdTable.Cell(nStep, i);
				cellRange = tblCell.get_Range();
				CVOA_WordFont	fonti3(cellRange.get_Font());
				fonti3.put_Name(fontText.m_FontName);
				fonti3.put_Bold(fontText.m_FontBold);
				fonti3.put_Size(fontText.m_FontSize);
				cellRange.put_Text(szDefVal.GetBuffer());
				szDefVal.ReleaseBuffer();
				if(nCol == 4)
				{
					szVal = pData->GetDataValueStr().c_str();

					i = 4;
					tblCell = m_wdTable.Cell(nStep, i);
					cellRange = tblCell.get_Range();
					CVOA_WordFont	fonti4(cellRange.get_Font());
					fonti4.put_Name(fontText.m_FontName);
					fonti4.put_Bold(fontText.m_FontBold);
					fonti4.put_Size(fontText.m_FontSize);
					cellRange.put_Text(szVal.GetBuffer());
					szVal.ReleaseBuffer();
				}
				nStep++;
				m_nCurRow ++;
			}
			else
			{
				nAEType = ((CVSB_Array*)pData)->GetElementDataTypeIndex();
				szType = XVSM_DTSTR[nAEType];
				nASize = ((CVSB_Array*)pData)->Size();

				i = 1;
				tblCell = m_wdTable.Cell(nStep, i);
				cellRange = tblCell.get_Range();
				CVOA_WordFont	fontia1(cellRange.get_Font());
				fontia1.put_Name(fontText.m_FontName);
				fontia1.put_Bold(fontText.m_FontBold);
				fontia1.put_Size(fontText.m_FontSize);
				cellRange.put_Text(szName.GetBuffer());
				szName.ReleaseBuffer();

				i = 2;
				szText = XVSM_DTSTR[XVSM_DT_ARRAY];
				szText += _T("/");
				szText += szType;
				tblCell = m_wdTable.Cell(nStep, i);
				cellRange = tblCell.get_Range();
				CVOA_WordFont	fontia2(cellRange.get_Font());
				fontia2.put_Name(fontText.m_FontName);
				fontia2.put_Bold(fontText.m_FontBold);
				fontia2.put_Size(fontText.m_FontSize);
				cellRange.put_Text(szText.GetBuffer());
				szText.ReleaseBuffer();

				i = 3;
				szTemp = XVSM_MACRO_ARRAYSIZE;
				szText.Format(_T("%s: %d"), szTemp, nASize);
				tblCell = m_wdTable.Cell(nStep, i);
				cellRange = tblCell.get_Range();
				CVOA_WordFont	fontia3(cellRange.get_Font());
				fontia3.put_Name(fontText.m_FontName);
				fontia3.put_Bold(fontText.m_FontBold);
				fontia3.put_Size(fontText.m_FontSize);
				cellRange.put_Text(szText.GetBuffer());
				szText.ReleaseBuffer();
				
				if(nCol == 4) //Adjust the row text height)
				{
					i = 4;
					tblCell = m_wdTable.Cell(nStep, i);
					cellRange = tblCell.get_Range();
					CVOA_WordFont	fontia41(cellRange.get_Font());
					fontia41.put_Name(fontText.m_FontName);
					fontia41.put_Bold(fontText.m_FontBold);
					fontia41.put_Size(fontText.m_FontSize);
					szText = _T("");
					cellRange.put_Text(szText);
					szText.ReleaseBuffer();
				}
				m_nCurRow++;
				nStep++;

				for(int iLoop = 0; iLoop < nASize; iLoop++)
				{
					szDefVal = ((CVSB_Array*)pData)->At(iLoop)->GetDefaultValueStr().c_str();
					szVal = ((CVSB_Array*)pData)->At(iLoop)->GetDataValueStr().c_str();

					// Adjust the row text height
					i = 1;
					tblCell = m_wdTable.Cell(nStep, i);
					cellRange = tblCell.get_Range();
					CVOA_WordFont	fontia11(cellRange.get_Font());
					fontia11.put_Name(fontText.m_FontName);
					fontia11.put_Bold(fontText.m_FontBold);
					fontia11.put_Size(fontText.m_FontSize);
					szText = _T("");
					cellRange.put_Text(szText);
					szText.ReleaseBuffer();

					i = 2;
					szText.Format(_T("%s[%d]"), szName, iLoop);
					tblCell = m_wdTable.Cell(nStep, i);
					cellRange = tblCell.get_Range();
					CVOA_WordFont	fontia4(cellRange.get_Font());
					fontia4.put_Name(fontText.m_FontName);
					fontia4.put_Bold(fontText.m_FontBold);
					fontia4.put_Size(fontText.m_FontSize);
					cellRange.put_Text(szText.GetBuffer());
					szText.ReleaseBuffer();

					i = 3;
					tblCell = m_wdTable.Cell(nStep, i);
					cellRange = tblCell.get_Range();
					CVOA_WordFont	fontia5(cellRange.get_Font());
					fontia5.put_Name(fontText.m_FontName);
					fontia5.put_Bold(fontText.m_FontBold);
					fontia5.put_Size(fontText.m_FontSize);
					cellRange.put_Text(szDefVal.GetBuffer());
					szDefVal.ReleaseBuffer();

					if(nCol == 4)
					{
						i = 4;
						tblCell = m_wdTable.Cell(nStep, i);
						cellRange = tblCell.get_Range();
						CVOA_WordFont	fontia6(cellRange.get_Font());
						fontia6.put_Name(fontText.m_FontName);
						fontia6.put_Bold(fontText.m_FontBold);
						fontia6.put_Size(fontText.m_FontSize);
						cellRange.put_Text(szVal.GetBuffer());
						szVal.ReleaseBuffer();
					}
					m_nCurRow++;
					nStep++;
				}
			}
		}
	}

	m_wdRange = m_wdTable.get_Range();

	m_wdRange.Collapse(COleVariant((short)0));	
	m_wdRange.InsertParagraph();
	m_wdRange.Collapse(COleVariant((short)0));	
	m_wdRange.InsertParagraph();
	m_wdRange.Collapse(COleVariant((short)0));	

	bRet = true;
	return bRet;
}

bool CVOA_WordExport::ExportPU(CVSB_Module* pModule)
{
	bool			bRet = false;
    CStringW		szText;
    CStringW		szCol;
    CStringW		szTemp;
	COleVariant		covOptional(DISP_E_PARAMNOTFOUND, VT_ERROR);
	long			nCol = 4;
	CVOA_WordCell   tblCell;
	CVOA_WordRange	cellRange;

	CVOA_WordFont	fontT2(m_wdRange.get_Font());
	fontT2.put_Name(fontTitle2.m_FontName);
	fontT2.put_Bold(fontTitle2.m_FontBold);
	fontT2.put_Size(fontTitle2.m_FontSize);

	szText =  XVSB_STR_PRINTPUTITLE;
	m_wdRange.put_Text(szText.GetBuffer());
	szText.GetBuffer();
	m_nCurRow ++;

	m_wdRange.Collapse(COleVariant((short)0));	
	m_wdRange.InsertParagraph();

	long nPURows = pModule->GetPUPrintLineCount();

	m_wdTables = m_wdRange.get_Tables();
	m_wdTable = m_wdTables.AddOld(m_wdRange, nPURows, nCol);

	m_nCurPURow = 1;
    bRet = ExportInitPU(pModule);
	if(!bRet)
		return bRet;

	CVSB_PUMap::iterator puiter;

	for(puiter = pModule->m_PUmap.begin(); puiter != pModule->m_PUmap.end(); ++puiter)
	{
		if(puiter->second->GetPUType() == enXVSB_PUSIMPLE)
		{
			bRet = ExportSPU((CVSB_SPU*)puiter->second);
			if(!bRet)
				return bRet;
		}
		else if(puiter->second->GetPUType() == enXVSB_PULOGIC)
		{
			bRet = ExportLPU((CVSB_LPU*)puiter->second);
			if(!bRet)
				return bRet;
		}
	}

	bRet = true;
	return bRet;
}

bool CVOA_WordExport::ExportInitPU(CVSB_Module* pModule)
{
	bool			bRet = false;
    CStringW		szText;
    CStringW		szCol;
    CStringW		szTemp;
	COleVariant		covOptional(DISP_E_PARAMNOTFOUND, VT_ERROR);
	long			nCol = 4;
	CVOA_WordCell   tblCell;
	long			i;
	long			j;
	long			nID;
	long			n;
	CVOA_WordRange	cellRange;

    i = 1;
	szText = pModule->m_Initialize.GetPUName().c_str(); 
	tblCell = m_wdTable.Cell(m_nCurPURow, i);
	cellRange = tblCell.get_Range();

	CVOA_WordFont	fontTi1(cellRange.get_Font());
	fontTi1.put_Name(fontTitle3.m_FontName);
	fontTi1.put_Bold(fontTitle3.m_FontBold);
	fontTi1.put_Size(fontTitle3.m_FontSize);

	cellRange.put_Text(szText.GetBuffer());
	szText.ReleaseBuffer();

    i = 2;
	szText = _T(""); 
	tblCell = m_wdTable.Cell(m_nCurPURow, i);
	cellRange = tblCell.get_Range();
	CVOA_WordFont	fontTi2(cellRange.get_Font());
	fontTi2.put_Name(fontTitle3.m_FontName);
	fontTi2.put_Bold(fontTitle3.m_FontBold);
	fontTi2.put_Size(fontTitle3.m_FontSize);
	cellRange.put_Text(szText.GetBuffer());
	szText.ReleaseBuffer();

    i = 3;
	szText = _T(""); 
	tblCell = m_wdTable.Cell(m_nCurPURow, i);
	cellRange = tblCell.get_Range();
	CVOA_WordFont	fontTi3(cellRange.get_Font());
	fontTi3.put_Name(fontTitle3.m_FontName);
	fontTi3.put_Bold(fontTitle3.m_FontBold);
	fontTi3.put_Size(fontTitle3.m_FontSize);
	cellRange.put_Text(szText.GetBuffer());
	szText.ReleaseBuffer();

    i = 4;
	szText = XVSM_PU_ATTRSTR[(int)enXVSB_PUINIT]; 
	tblCell = m_wdTable.Cell(m_nCurPURow, i);
	cellRange = tblCell.get_Range();
	CVOA_WordFont	fontTi4(cellRange.get_Font());
	fontTi4.put_Name(fontTitle3.m_FontName);
	fontTi4.put_Bold(fontTitle3.m_FontBold);
	fontTi4.put_Size(fontTitle3.m_FontSize);
	cellRange.put_Text(szText.GetBuffer());
	szText.ReleaseBuffer();

	m_nCurPURow++;
	for(j = 0; 	j < (long)pModule->m_Initialize.m_PrevPUlist.size(); j++)
	{
		i = 1;
		szText = _T("");
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi5(cellRange.get_Font());
		fontiTi5.put_Name(fontText.m_FontName);
		fontiTi5.put_Bold(fontText.m_FontBold);
		fontiTi5.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();

		i = 2;
		szText = XVSB_STR_PRINTLINKPREV;
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi6(cellRange.get_Font());
		fontiTi6.put_Name(fontText.m_FontName);
		fontiTi6.put_Bold(fontText.m_FontBold);
		fontiTi6.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();

		i = 3;
		szText = _T("");
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi7(cellRange.get_Font());
		fontiTi7.put_Name(fontText.m_FontName);
		fontiTi7.put_Bold(fontText.m_FontBold);
		fontiTi7.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();

		i = 4;
		nID = pModule->m_Initialize.m_PrevPUlist[j];
		szText = _T("ID: ");
		if(nID == XVSM_PU_START || nID == XVSM_PU_INIT || nID == XVSM_PU_END)
		{
			n = XVSM_PU_START;
			n = abs(nID) - abs(n);
			szText += XVSM_PUID_ATTRSTR[n];
		}
		else
		{
			szText.Format(_T("ID: %d"), nID);

		}
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi8(cellRange.get_Font());
		fontiTi8.put_Name(fontText.m_FontName);
		fontiTi8.put_Bold(fontText.m_FontBold);
		fontiTi8.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();
		m_nCurPURow++;
	}
	for(j = 0; 	j < (long)pModule->m_Initialize.m_NextPUlist.size(); j++)
	{
		i = 1;
		szText = _T("");
		szText = _T("");
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi9(cellRange.get_Font());
		fontiTi9.put_Name(fontText.m_FontName);
		fontiTi9.put_Bold(fontText.m_FontBold);
		fontiTi9.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();

		i = 2;
		szText = XVSB_STR_PRINTLINKNEXT;
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi10(cellRange.get_Font());
		fontiTi10.put_Name(fontText.m_FontName);
		fontiTi10.put_Bold(fontText.m_FontBold);
		fontiTi10.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();

		i = 3;
		szText = _T("");
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi11(cellRange.get_Font());
		fontiTi11.put_Name(fontText.m_FontName);
		fontiTi11.put_Bold(fontText.m_FontBold);
		fontiTi11.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();


		i = 4;
		nID = pModule->m_Initialize.m_NextPUlist[j];
		szText = _T("ID: ");
		if(nID == XVSM_PU_START || nID == XVSM_PU_INIT || nID == XVSM_PU_END)
		{
			n = XVSM_PU_START;
			n = abs(nID) - abs(n);
			szText += XVSM_PUID_ATTRSTR[n];
		}
		else
		{
			szText.Format(_T("ID: %d"), nID);
		}
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi12(cellRange.get_Font());
		fontiTi12.put_Name(fontText.m_FontName);
		fontiTi12.put_Bold(fontText.m_FontBold);
		fontiTi12.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();
		m_nCurPURow++;
	}

	bRet = true;
	return bRet;
}

bool CVOA_WordExport::ExportSPU(CVSB_SPU* pSPU)
{
	bool			bRet = false;
    CStringW		szText;
    CStringW		szCol;
    CStringW		szTemp;
	COleVariant		covOptional(DISP_E_PARAMNOTFOUND, VT_ERROR);
	long			nCol = 4;
	CVOA_WordCell   tblCell;
	long			i;
	long			j;
	long			nID;
	long			n;
	CVOA_WordRange	cellRange;

    i = 1;
	szText = pSPU->GetPUName().c_str(); 
	tblCell = m_wdTable.Cell(m_nCurPURow, i);
	cellRange = tblCell.get_Range();

	CVOA_WordFont	fontTi1(cellRange.get_Font());
	fontTi1.put_Name(fontTitle3.m_FontName);
	fontTi1.put_Bold(fontTitle3.m_FontBold);
	fontTi1.put_Size(fontTitle3.m_FontSize);

	cellRange.put_Text(szText.GetBuffer());
	szText.ReleaseBuffer();

    i = 2;
	szText.Format(_T("ID: %d"), pSPU->GetID()); 
	tblCell = m_wdTable.Cell(m_nCurPURow, i);
	cellRange = tblCell.get_Range();
	CVOA_WordFont	fontTi3(cellRange.get_Font());
	fontTi3.put_Name(fontTitle3.m_FontName);
	fontTi3.put_Bold(fontTitle3.m_FontBold);
	fontTi3.put_Size(fontTitle3.m_FontSize);
	cellRange.put_Text(szText.GetBuffer());
	szText.ReleaseBuffer();

    i = 3;
	szText = _T(""); 
	tblCell = m_wdTable.Cell(m_nCurPURow, i);
	cellRange = tblCell.get_Range();
	CVOA_WordFont	fontTi2(cellRange.get_Font());
	fontTi2.put_Name(fontTitle3.m_FontName);
	fontTi2.put_Bold(fontTitle3.m_FontBold);
	fontTi2.put_Size(fontTitle3.m_FontSize);
	cellRange.put_Text(szText.GetBuffer());
	szText.ReleaseBuffer();

    i = 4;
	szText = XVSM_PU_ATTRSTR[(int)enXVSB_PUSIMPLE]; 
	tblCell = m_wdTable.Cell(m_nCurPURow, i);
	cellRange = tblCell.get_Range();
	CVOA_WordFont	fontTi4(cellRange.get_Font());
	fontTi4.put_Name(fontTitle3.m_FontName);
	fontTi4.put_Bold(fontTitle3.m_FontBold);
	fontTi4.put_Size(fontTitle3.m_FontSize);
	cellRange.put_Text(szText.GetBuffer());
	szText.ReleaseBuffer();
	m_nCurPURow++;

	for(j = 0; 	j < (long)pSPU->m_PrevPUlist.size(); j++)
	{
		i = 1;
		szText = _T("");
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi5(cellRange.get_Font());
		fontiTi5.put_Name(fontText.m_FontName);
		fontiTi5.put_Bold(fontText.m_FontBold);
		fontiTi5.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();

		i = 2;
		szText = XVSB_STR_PRINTLINKPREV;
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi6(cellRange.get_Font());
		fontiTi6.put_Name(fontText.m_FontName);
		fontiTi6.put_Bold(fontText.m_FontBold);
		fontiTi6.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();

		i = 3;
		szText = _T("");
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi7(cellRange.get_Font());
		fontiTi7.put_Name(fontText.m_FontName);
		fontiTi7.put_Bold(fontText.m_FontBold);
		fontiTi7.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();

		i = 4;
		nID = pSPU->m_PrevPUlist[j];
		szText = _T("ID: ");
		if(nID == XVSM_PU_START || nID == XVSM_PU_INIT || nID == XVSM_PU_END)
		{
			n = XVSM_PU_START;
			n = abs(nID) - abs(n);
			szText += XVSM_PUID_ATTRSTR[n];
		}
		else
		{
			szText.Format(_T("ID: %d"), nID);

		}
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi8(cellRange.get_Font());
		fontiTi8.put_Name(fontText.m_FontName);
		fontiTi8.put_Bold(fontText.m_FontBold);
		fontiTi8.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();
		m_nCurPURow++;
	}
	for(j = 0; 	j < (long)pSPU->m_NextPUlist.size(); j++)
	{
		i = 1;
		szText = _T("");
		szText = _T("");
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi9(cellRange.get_Font());
		fontiTi9.put_Name(fontText.m_FontName);
		fontiTi9.put_Bold(fontText.m_FontBold);
		fontiTi9.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();

		i = 2;
		szText = XVSB_STR_PRINTLINKNEXT;
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi10(cellRange.get_Font());
		fontiTi10.put_Name(fontText.m_FontName);
		fontiTi10.put_Bold(fontText.m_FontBold);
		fontiTi10.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();

		i = 3;
		szText = _T("");
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi11(cellRange.get_Font());
		fontiTi11.put_Name(fontText.m_FontName);
		fontiTi11.put_Bold(fontText.m_FontBold);
		fontiTi11.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();


		i = 4;
		nID = pSPU->m_NextPUlist[j];
		szText = _T("ID: ");
		if(nID == XVSM_PU_START || nID == XVSM_PU_INIT || nID == XVSM_PU_END)
		{
			n = XVSM_PU_START;
			n = abs(nID) - abs(n);
			szText += XVSM_PUID_ATTRSTR[n];
		}
		else
		{
			szText.Format(_T("ID: %d"), nID);
		}
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi12(cellRange.get_Font());
		fontiTi12.put_Name(fontText.m_FontName);
		fontiTi12.put_Bold(fontText.m_FontBold);
		fontiTi12.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();
		m_nCurPURow++;
	}

	for(j = 0; j < pSPU->GetInnerCount(); j++)
	{
		i = 1;
		szText = _T("");
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi13(cellRange.get_Font());
		fontiTi13.put_Name(fontText.m_FontName);
		fontiTi13.put_Bold(fontText.m_FontBold);
		fontiTi13.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();

		i = 2;
		szText = XVSB_STR_PRINTEQUATION;
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi14(cellRange.get_Font());
		fontiTi14.put_Name(fontText.m_FontName);
		fontiTi14.put_Bold(fontText.m_FontBold);
		fontiTi14.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();

		i = 3;
		szText = _T("");
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi15(cellRange.get_Font());
		fontiTi15.put_Name(fontText.m_FontName);
		fontiTi15.put_Bold(fontText.m_FontBold);
		fontiTi15.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();

		i = 4;
		szText = pSPU->GetEquationStr(j).c_str();
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi16(cellRange.get_Font());
		fontiTi16.put_Name(fontText.m_FontName);
		fontiTi16.put_Bold(fontText.m_FontBold);
		fontiTi16.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();
		m_nCurPURow++;
	}

	bRet = true;
	return bRet;
}

bool CVOA_WordExport::ExportLPU(CVSB_LPU* pLPU)
{
	bool			bRet = false;
    CStringW		szText;
    CStringW		szCol;
    CStringW		szTemp;
	COleVariant		covOptional(DISP_E_PARAMNOTFOUND, VT_ERROR);
	long			nCol = 4;
	CVOA_WordCell   tblCell;
	long			i;
	long			j;
	long			nID;
	long			n;
	CVOA_WordRange	cellRange;

    i = 1;
	szText = pLPU->GetPUName().c_str(); 
	tblCell = m_wdTable.Cell(m_nCurPURow, i);
	cellRange = tblCell.get_Range();

	CVOA_WordFont	fontTi1(cellRange.get_Font());
	fontTi1.put_Name(fontTitle3.m_FontName);
	fontTi1.put_Bold(fontTitle3.m_FontBold);
	fontTi1.put_Size(fontTitle3.m_FontSize);

	cellRange.put_Text(szText.GetBuffer());
	szText.ReleaseBuffer();

    i = 2;
	szText.Format(_T("ID: %d"), pLPU->GetID()); 
	tblCell = m_wdTable.Cell(m_nCurPURow, i);
	cellRange = tblCell.get_Range();
	CVOA_WordFont	fontTi3(cellRange.get_Font());
	fontTi3.put_Name(fontTitle3.m_FontName);
	fontTi3.put_Bold(fontTitle3.m_FontBold);
	fontTi3.put_Size(fontTitle3.m_FontSize);
	cellRange.put_Text(szText.GetBuffer());
	szText.ReleaseBuffer();

    i = 3;
	szText = _T(""); 
	tblCell = m_wdTable.Cell(m_nCurPURow, i);
	cellRange = tblCell.get_Range();
	CVOA_WordFont	fontTi2(cellRange.get_Font());
	fontTi2.put_Name(fontTitle3.m_FontName);
	fontTi2.put_Bold(fontTitle3.m_FontBold);
	fontTi2.put_Size(fontTitle3.m_FontSize);
	cellRange.put_Text(szText.GetBuffer());
	szText.ReleaseBuffer();

    i = 4;
	szText = XVSM_PU_ATTRSTR[(int)enXVSB_PULOGIC]; 
	tblCell = m_wdTable.Cell(m_nCurPURow, i);
	cellRange = tblCell.get_Range();
	CVOA_WordFont	fontTi4(cellRange.get_Font());
	fontTi4.put_Name(fontTitle3.m_FontName);
	fontTi4.put_Bold(fontTitle3.m_FontBold);
	fontTi4.put_Size(fontTitle3.m_FontSize);
	cellRange.put_Text(szText.GetBuffer());
	szText.ReleaseBuffer();
	m_nCurPURow++;

	for(j = 0; 	j < (long)pLPU->m_PrevPUlist.size(); j++)
	{
		i = 1;
		szText = _T("");
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi5(cellRange.get_Font());
		fontiTi5.put_Name(fontText.m_FontName);
		fontiTi5.put_Bold(fontText.m_FontBold);
		fontiTi5.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();

		i = 2;
		szText = XVSB_STR_PRINTLINKPREV;
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi6(cellRange.get_Font());
		fontiTi6.put_Name(fontText.m_FontName);
		fontiTi6.put_Bold(fontText.m_FontBold);
		fontiTi6.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();

		i = 3;
		szText = _T("");
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi7(cellRange.get_Font());
		fontiTi7.put_Name(fontText.m_FontName);
		fontiTi7.put_Bold(fontText.m_FontBold);
		fontiTi7.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();

		i = 4;
		nID = pLPU->m_PrevPUlist[j];
		szText = _T("ID: ");
		if(nID == XVSM_PU_START || nID == XVSM_PU_INIT || nID == XVSM_PU_END)
		{
			n = XVSM_PU_START;
			n = abs(nID) - abs(n);
			szText += XVSM_PUID_ATTRSTR[n];
		}
		else
		{
			szText.Format(_T("ID: %d"), nID);

		}
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi8(cellRange.get_Font());
		fontiTi8.put_Name(fontText.m_FontName);
		fontiTi8.put_Bold(fontText.m_FontBold);
		fontiTi8.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();
		m_nCurPURow++;
	}

	i = 1;
	szText = _T("");
	tblCell = m_wdTable.Cell(m_nCurPURow, i);
	cellRange = tblCell.get_Range();
	CVOA_WordFont	fontiTi9(cellRange.get_Font());
	fontiTi9.put_Name(fontText.m_FontName);
	fontiTi9.put_Bold(fontText.m_FontBold);
	fontiTi9.put_Size(fontText.m_FontSize);
	cellRange.put_Text(szText);
	szText.ReleaseBuffer();

	i = 2;
	szText = XVSB_STR_PRINTLINKYESNEXT;
	tblCell = m_wdTable.Cell(m_nCurPURow, i);
	cellRange = tblCell.get_Range();
	CVOA_WordFont	fontiTi10(cellRange.get_Font());
	fontiTi10.put_Name(fontText.m_FontName);
	fontiTi10.put_Bold(fontText.m_FontBold);
	fontiTi10.put_Size(fontText.m_FontSize);
	cellRange.put_Text(szText);
	szText.ReleaseBuffer();

	i = 3;
	szText = _T("");
	tblCell = m_wdTable.Cell(m_nCurPURow, i);
	cellRange = tblCell.get_Range();
	CVOA_WordFont	fontiTi11(cellRange.get_Font());
	fontiTi11.put_Name(fontText.m_FontName);
	fontiTi11.put_Bold(fontText.m_FontBold);
	fontiTi11.put_Size(fontText.m_FontSize);
	cellRange.put_Text(szText);
	szText.ReleaseBuffer();

	i = 4;
	nID = pLPU->m_nYesNextPU;
	szText = _T("ID: ");
	if(nID == XVSM_PU_START || nID == XVSM_PU_INIT || nID == XVSM_PU_END)
	{
		n = XVSM_PU_START;
		n = abs(nID) - abs(n);
		szText += XVSM_PUID_ATTRSTR[n];
	}
	else
	{
		szText.Format(_T("ID: %d"), nID);
	}
	tblCell = m_wdTable.Cell(m_nCurPURow, i);
	cellRange = tblCell.get_Range();
	CVOA_WordFont	fontiTi12(cellRange.get_Font());
	fontiTi12.put_Name(fontText.m_FontName);
	fontiTi12.put_Bold(fontText.m_FontBold);
	fontiTi12.put_Size(fontText.m_FontSize);
	cellRange.put_Text(szText);
	szText.ReleaseBuffer();
	m_nCurPURow++;

	i = 1;
	szText = _T("");
	tblCell = m_wdTable.Cell(m_nCurPURow, i);
	cellRange = tblCell.get_Range();
	CVOA_WordFont	fontiTi9a(cellRange.get_Font());
	fontiTi9a.put_Name(fontText.m_FontName);
	fontiTi9a.put_Bold(fontText.m_FontBold);
	fontiTi9a.put_Size(fontText.m_FontSize);
	cellRange.put_Text(szText);
	szText.ReleaseBuffer();

	i = 2;
	szText = XVSB_STR_PRINTLINKNONEXT;
	tblCell = m_wdTable.Cell(m_nCurPURow, i);
	cellRange = tblCell.get_Range();
	CVOA_WordFont	fontiTi10a(cellRange.get_Font());
	fontiTi10a.put_Name(fontText.m_FontName);
	fontiTi10a.put_Bold(fontText.m_FontBold);
	fontiTi10a.put_Size(fontText.m_FontSize);
	cellRange.put_Text(szText);
	szText.ReleaseBuffer();

	i = 3;
	szText = _T("");
	tblCell = m_wdTable.Cell(m_nCurPURow, i);
	cellRange = tblCell.get_Range();
	CVOA_WordFont	fontiTi11a(cellRange.get_Font());
	fontiTi11a.put_Name(fontText.m_FontName);
	fontiTi11a.put_Bold(fontText.m_FontBold);
	fontiTi11a.put_Size(fontText.m_FontSize);
	cellRange.put_Text(szText);
	szText.ReleaseBuffer();

	i = 4;
	nID = pLPU->m_nNoNextPU;
	szText = _T("ID: ");
	if(nID == XVSM_PU_START || nID == XVSM_PU_INIT || nID == XVSM_PU_END)
	{
		n = XVSM_PU_START;
		n = abs(nID) - abs(n);
		szText += XVSM_PUID_ATTRSTR[n];
	}
	else
	{
		szText.Format(_T("ID: %d"), nID);
	}
	tblCell = m_wdTable.Cell(m_nCurPURow, i);
	cellRange = tblCell.get_Range();
	CVOA_WordFont	fontiTi12a(cellRange.get_Font());
	fontiTi12a.put_Name(fontText.m_FontName);
	fontiTi12a.put_Bold(fontText.m_FontBold);
	fontiTi12a.put_Size(fontText.m_FontSize);
	cellRange.put_Text(szText);
	szText.ReleaseBuffer();
	m_nCurPURow++;


	for(j = 0; j < pLPU->GetInnerCount(); j++)
	{
		i = 1;
		szText = _T("");
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi13a(cellRange.get_Font());
		fontiTi13a.put_Name(fontText.m_FontName);
		fontiTi13a.put_Bold(fontText.m_FontBold);
		fontiTi13a.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();

		i = 2;
		szText = XVSB_STR_PRINTCOMPARE;
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi14a(cellRange.get_Font());
		fontiTi14a.put_Name(fontText.m_FontName);
		fontiTi14a.put_Bold(fontText.m_FontBold);
		fontiTi14a.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();

		i = 3;
		szText = XVSM_LGRSTR[(int)pLPU->GetLGRelation(j)]; 
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi15a(cellRange.get_Font());
		fontiTi15a.put_Name(fontText.m_FontName);
		fontiTi15a.put_Bold(fontText.m_FontBold);
		fontiTi15a.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();

		i = 4;
		szText = pLPU->GetSingleCMPStr(j).c_str();
		tblCell = m_wdTable.Cell(m_nCurPURow, i);
		cellRange = tblCell.get_Range();
		CVOA_WordFont	fontiTi16a(cellRange.get_Font());
		fontiTi16a.put_Name(fontText.m_FontName);
		fontiTi16a.put_Bold(fontText.m_FontBold);
		fontiTi16a.put_Size(fontText.m_FontSize);
		cellRange.put_Text(szText);
		szText.ReleaseBuffer();
		m_nCurPURow++;
	}

	bRet = true;
	return bRet;
}
