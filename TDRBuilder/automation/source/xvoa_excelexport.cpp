//2005/03/02
#include "stdafx.h"
#include "xvoa_excelexport.h"
#include "xvsb_macro.h"
#include "xvsb_defs.h"
#include "xvsb_filconst.h"
#include "xvsb_array.h"
#include "xvsb_lpu.h"
#include "xvsb_spu.h"

// Excel versions
enum enXVOA_EXCELVERSION 
{									
	enXVOA_EXCELVERSION8 = 0,							// Excel8 (Office97)
	enXVOA_EXCELVERSION5,								// Excel5 (Office95)
	enXVOA_EXCELVERSION9								// New version
};

const int nExcelFileFormat[] = 
{
	-4143,												// Excel8(Office98) : xlWorkbookNormal = -4143
	1,													// Excel5(Office95) : xlWorkbook = 1
	-4143,												// New version : the same as excel8	 
};		
														
// Excel ProgIDs for every version of Excel
const OLECHAR FAR* szExcelProgID[] = 
{					
	OLESTR("Excel.Application.8"),						// Excel8 ProgID
	OLESTR("Excel.Application.5"),						// Excel5 ProgID
	OLESTR("Excel.Application"),						// Excel ProgID
};

CVOA_ExcelExport::CVOA_ExcelExport()
{
	m_nCurRow = 0;
}

CVOA_ExcelExport::~CVOA_ExcelExport()
{
	m_nCurRow = 0;
	Close();
}

bool CVOA_ExcelExport::CanExport2Excel(void)
{
	// Check avaliable CLSID of excel application
    CLSID	clsid;
    for (int i = enXVOA_EXCELVERSION8; i <= enXVOA_EXCELVERSION9; i++ )
    {
		if (SUCCEEDED(CLSIDFromProgID(szExcelProgID[i], &clsid)))
		{
			return true;
		}
    }
    return false;
}

bool CVOA_ExcelExport::ExportResult(const std::wstring& szFile, CVSB_Module* pModule, bool bShow)
{
	return ExportResult(szFile.c_str(), pModule, bShow);
}

bool CVOA_ExcelExport::ExportResult(const wchar_t* szFile, CVSB_Module* pModule, bool bShow)
{
	bool			bRet = false;
    CStringW		szProgID;
    CStringW		szText;
	bool			bStart = false;
    long			nExcelVer;
	COleVariant		covOptional(DISP_E_PARAMNOTFOUND, VT_ERROR);

	if(pModule == NULL || szFile == NULL)
		return bRet;

	m_nCurRow = 0;
	if(m_xlsApp.m_lpDispatch == NULL) 
	{
		for(long i = enXVOA_EXCELVERSION8; i <= enXVOA_EXCELVERSION9; i++)
		{
			szProgID = szExcelProgID[i];
			if(m_xlsApp.CreateDispatch(szProgID.GetBuffer()))
			{
				bStart = true;
				nExcelVer = i;
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
		m_xlsApp.put_Visible(TRUE);
		m_xlsApp.put_UserControl(TRUE);
	}
	else
	{
		m_xlsApp.put_Visible(FALSE);
		m_xlsApp.put_UserControl(FALSE);
	}

	m_xlsWBooks = m_xlsApp.get_Workbooks();
	m_xlsWBook = m_xlsWBooks.Add(covOptional);
	m_xlsWSheets = m_xlsWBook.get_Worksheets();
	m_xlsWSheet = m_xlsWSheets.get_Item(COleVariant((short)1));
	szText = XVSM_SHEET1;
	m_xlsWSheet.put_Name(szText.GetBuffer());
	szText.ReleaseBuffer();

	CStringW szCol = XVSM_FIRSTLETTER;
	szText.Format(_T("%s%d"), szCol, m_nCurRow+1);
	m_xlsRange = m_xlsWSheet.get_Range(COleVariant(szText.GetBuffer()),covOptional);
	szText.GetBuffer();
	szText = XVSM_MACRO_MODULE;
	szText += _T(": ");
	szText += pModule->GetName().c_str();
	m_xlsRange.put_Value(COleVariant(COleVariant(szText.GetBuffer())));
	szText.GetBuffer();

	m_nCurRow += 2;

	bRet = ExportInput(pModule, true);

	if(!bRet)
	{
		if(m_xlsWBook.m_lpDispatch)
		{
			m_xlsWBook.Close(COleVariant((short)FALSE), COleVariant(szText.GetBuffer()), covOptional);
			szText.ReleaseBuffer();
		}
		Close();
	}

	bRet = ExportGlobal(pModule, true);
	if(!bRet)
	{
		if(m_xlsWBook.m_lpDispatch)
		{
			m_xlsWBook.Close(COleVariant((short)FALSE), COleVariant(szText.GetBuffer()), covOptional);
			szText.ReleaseBuffer();
		}
		Close();
	}

	bRet = ExportLocal(pModule, true);
	if(!bRet)
	{
		if(m_xlsWBook.m_lpDispatch)
		{
			m_xlsWBook.Close(COleVariant((short)FALSE), COleVariant(szText.GetBuffer()), covOptional);
			szText.ReleaseBuffer();
		}
		Close();
	}

	nExcelVer = m_xlsWBook.get_FileFormat();
	szText = szFile;

	m_xlsWBook.SaveAs2(COleVariant(szText.GetBuffer()), 
					    COleVariant((short)nExcelVer), 
						covOptional, 
						covOptional, 
						covOptional, 
						covOptional, 
						covOptional, 
						covOptional, 
						covOptional, 
						covOptional, 
						covOptional);
	szText.ReleaseBuffer();

	if(m_xlsWBook.m_lpDispatch)
	{
		m_xlsWBook.Close(COleVariant((short)FALSE), COleVariant(szText.GetBuffer()), covOptional);
		szText.ReleaseBuffer();
	}

	Close();
	return bRet;
}

bool CVOA_ExcelExport::ExportResult2(const std::wstring& szFile, CVSB_Module* pModule, bool bLocal, bool bShow)
{
	return ExportResult2(szFile.c_str(), pModule, bLocal, bShow);
}

bool CVOA_ExcelExport::ExportResult2(const wchar_t* szFile, CVSB_Module* pModule, bool bLocal, bool bShow)
{
	bool			bRet = false;
    CStringW		szProgID;
    CStringW		szText;
	bool			bStart = false;
    long			nExcelVer;
	COleVariant		covOptional(DISP_E_PARAMNOTFOUND, VT_ERROR);

	if(pModule == NULL || szFile == NULL)
		return bRet;

	m_nCurRow = 0;
	if(m_xlsApp.m_lpDispatch == NULL) 
	{
		for(long i = enXVOA_EXCELVERSION8; i <= enXVOA_EXCELVERSION9; i++)
		{
			szProgID = szExcelProgID[i];
			if(m_xlsApp.CreateDispatch(szProgID.GetBuffer()))
			{
				bStart = true;
				nExcelVer = i;
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
		m_xlsApp.put_Visible(TRUE);
		m_xlsApp.put_UserControl(TRUE);
	}
	else
	{
		m_xlsApp.put_Visible(FALSE);
		m_xlsApp.put_UserControl(FALSE);
	}

	m_xlsWBooks = m_xlsApp.get_Workbooks();
	m_xlsWBook = m_xlsWBooks.Add(covOptional);
	m_xlsWSheets = m_xlsWBook.get_Worksheets();
	m_xlsWSheet = m_xlsWSheets.get_Item(COleVariant((short)1));
	szText = XVSM_SHEET1;
	m_xlsWSheet.put_Name(szText.GetBuffer());
	szText.ReleaseBuffer();

	CStringW szCol = XVSM_FIRSTLETTER;
	szText.Format(_T("%s%d"), szCol, m_nCurRow+1);
	m_xlsRange = m_xlsWSheet.get_Range(COleVariant(szText.GetBuffer()),covOptional);
	szText.GetBuffer();
	szText = XVSM_MACRO_MODULE;
	szText += _T(": ");
	szText += pModule->GetName().c_str();
	m_xlsRange.put_Value(COleVariant(COleVariant(szText.GetBuffer())));
	szText.GetBuffer();

	m_nCurRow += 2;

	bRet = ExportInput(pModule, true);

	if(!bRet)
	{
		if(m_xlsWBook.m_lpDispatch)
		{
			m_xlsWBook.Close(COleVariant((short)FALSE), COleVariant(szText.GetBuffer()), covOptional);
			szText.ReleaseBuffer();
		}
		Close();
	}

	bRet = ExportGlobal(pModule, true);
	if(!bRet)
	{
		if(m_xlsWBook.m_lpDispatch)
		{
			m_xlsWBook.Close(COleVariant((short)FALSE), COleVariant(szText.GetBuffer()), covOptional);
			szText.ReleaseBuffer();
		}
		Close();
	}

	if(bLocal)
	{
		bRet = ExportLocal(pModule, true);
		if(!bRet)
		{
			if(m_xlsWBook.m_lpDispatch)
			{
				m_xlsWBook.Close(COleVariant((short)FALSE), COleVariant(szText.GetBuffer()), covOptional);
				szText.ReleaseBuffer();
			}
			Close();
		}
	}

	nExcelVer = m_xlsWBook.get_FileFormat();
	szText = szFile;

	m_xlsWBook.SaveAs2(COleVariant(szText.GetBuffer()), 
					    COleVariant((short)nExcelVer), 
						covOptional, 
						covOptional, 
						covOptional, 
						covOptional, 
						covOptional, 
						covOptional, 
						covOptional, 
						covOptional, 
						covOptional);
	szText.ReleaseBuffer();

	if(m_xlsWBook.m_lpDispatch)
	{
		m_xlsWBook.Close(COleVariant((short)FALSE), COleVariant(szText.GetBuffer()), covOptional);
		szText.ReleaseBuffer();
	}

	Close();
	return bRet;
}

bool CVOA_ExcelExport::ExportModule(const std::wstring& szFile, CVSB_Module* pModule, bool bShow)
{
	return ExportModule(szFile.c_str(), pModule, bShow);
}

bool CVOA_ExcelExport::ExportModule(const wchar_t* szFile, CVSB_Module* pModule, bool bShow)
{
	bool			bRet = false;
    CStringW		szProgID;
    CStringW		szText;
	bool			bStart = false;
    long			nExcelVer;
	COleVariant		covOptional(DISP_E_PARAMNOTFOUND, VT_ERROR);

	if(pModule == NULL || szFile == NULL)
		return bRet;

	m_nCurRow = 0;
	if(m_xlsApp.m_lpDispatch == NULL) 
	{
		for(long i = enXVOA_EXCELVERSION8; i <= enXVOA_EXCELVERSION9; i++)
		{
			szProgID = szExcelProgID[i];
			if(m_xlsApp.CreateDispatch(szProgID.GetBuffer()))
			{
				bStart = true;
				nExcelVer = i;
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
		m_xlsApp.put_Visible(TRUE);
		m_xlsApp.put_UserControl(TRUE);
	}
	else
	{
		m_xlsApp.put_Visible(FALSE);
		m_xlsApp.put_UserControl(FALSE);
	}

	m_xlsWBooks = m_xlsApp.get_Workbooks();
	m_xlsWBook = m_xlsWBooks.Add(covOptional);
	m_xlsWSheets = m_xlsWBook.get_Worksheets();
	m_xlsWSheet = m_xlsWSheets.get_Item(COleVariant((short)1));
	szText = XVSM_SHEET1;
	m_xlsWSheet.put_Name(szText.GetBuffer());
	szText.ReleaseBuffer();

	CStringW szCol = XVSM_FIRSTLETTER;
	szText.Format(_T("%s%d"), szCol, m_nCurRow+1);
	m_xlsRange = m_xlsWSheet.get_Range(COleVariant(szText.GetBuffer()),covOptional);
	szText.GetBuffer();
	szText = XVSM_MACRO_MODULE;
	szText += _T(": ");
	szText += pModule->GetName().c_str();
	m_xlsRange.put_Value(COleVariant(COleVariant(szText.GetBuffer())));
	szText.GetBuffer();

	m_nCurRow += 2;

	bRet = ExportInput(pModule, false);

	if(!bRet)
	{
		if(m_xlsWBook.m_lpDispatch)
		{
			m_xlsWBook.Close(COleVariant((short)FALSE), COleVariant(szText.GetBuffer()), covOptional);
			szText.ReleaseBuffer();
		}
		Close();
	}

	bRet = ExportGlobal(pModule, false);
	if(!bRet)
	{
		if(m_xlsWBook.m_lpDispatch)
		{
			m_xlsWBook.Close(COleVariant((short)FALSE), COleVariant(szText.GetBuffer()), covOptional);
			szText.ReleaseBuffer();
		}
		Close();
	}

	bRet = ExportLocal(pModule, false);
	if(!bRet)
	{
		if(m_xlsWBook.m_lpDispatch)
		{
			m_xlsWBook.Close(COleVariant((short)FALSE), COleVariant(szText.GetBuffer()), covOptional);
			szText.ReleaseBuffer();
		}
		Close();
	}

	bRet = ExportPU(pModule);
	if(!bRet)
	{
		if(m_xlsWBook.m_lpDispatch)
		{
			m_xlsWBook.Close(COleVariant((short)FALSE), COleVariant(szText.GetBuffer()), covOptional);
			szText.ReleaseBuffer();
		}
		Close();
	}

	nExcelVer = m_xlsWBook.get_FileFormat();
	szText = szFile;

	m_xlsWBook.SaveAs2(COleVariant(szText.GetBuffer()), 
					    COleVariant((short)nExcelVer), 
						covOptional, 
						covOptional, 
						covOptional, 
						covOptional, 
						covOptional, 
						covOptional, 
						covOptional, 
						covOptional, 
						covOptional);
	szText.ReleaseBuffer();

	if(m_xlsWBook.m_lpDispatch)
	{
		m_xlsWBook.Close(COleVariant((short)FALSE), COleVariant(szText.GetBuffer()), covOptional);
		szText.ReleaseBuffer();
	}

	Close();
	return bRet;
}

void CVOA_ExcelExport::Close(void)
{
	if(m_xlsApp.m_lpDispatch != NULL) 
	{
		m_xlsApp.Quit();
		m_xlsApp.ReleaseDispatch();
		m_xlsApp.m_lpDispatch = NULL;
	}
	m_nCurRow = 0;
}

bool CVOA_ExcelExport::ExportInput(CVSB_Module* pModule, bool bFinalVal)
{
	bool			bRet = false;
    CStringW		szText;
    CStringW		szCol;
    CStringW		szTemp;
	COleVariant		covOptional(DISP_E_PARAMNOTFOUND, VT_ERROR);
	long			nCol;
	//long			nColWidth;

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

	szCol = XVSM_FIRSTLETTER;
	szText.Format(_T("%s%d"), szCol, m_nCurRow+1);
	m_xlsRange = m_xlsWSheet.get_Range(COleVariant(szText.GetBuffer()),covOptional);
	szText.GetBuffer();
	szText = XVSM_MACRO_INPUTVAR;
	szText += _T(":");
	m_xlsRange.put_Value(COleVariant(COleVariant(szText.GetBuffer())));
	szText.GetBuffer();

	m_nCurRow++;

	CVSB_VarObjTable::iterator iter;
	IVSB_DataBase*	pData;
	CStringW		szType;		
	CStringW		szName;		
	CStringW		szVal;
	CStringW		szDefVal;
	long			nIdx;
	long			i;
	COleSafeArray	saArray;
	BSTR			bstr;
	long			nTemp;

	nTemp = 1;
	saArray.Create(VT_BSTR, 1, (DWORD*)&nCol);

	szText.Format(_T("%s%d"), szCol, m_nCurRow+1);
	m_xlsRange = m_xlsWSheet.get_Range(COleVariant(szText.GetBuffer()),covOptional);
	szText.GetBuffer();

	m_xlsRange = m_xlsRange.get_Resize(COleVariant((short)1),COleVariant((short)nCol));
	for(i = 0; i < nCol; i++)
	{
		szTemp = XVSM_VAR_TITLESTR[i];
		bstr = szTemp.AllocSysString();
		saArray.PutElement(&i, bstr);
		SysFreeString(bstr);
	}
	m_xlsRange.put_Value(COleVariant(saArray));
	m_nCurRow++;

	for(iter = pModule->m_InputVars.m_ObjTbl.begin(); iter != pModule->m_InputVars.m_ObjTbl.end(); ++iter)
	{
		szText.Format(_T("%s%d"), szCol, m_nCurRow+1);
		m_xlsRange = m_xlsWSheet.get_Range(COleVariant(szText.GetBuffer()),covOptional);
		szText.GetBuffer();
		m_xlsRange = m_xlsRange.get_Resize(COleVariant((short)1),COleVariant((short)nCol));

		pData = iter->second;
		szName = iter->first.c_str();
		if(pData)
		{
			nIdx = pData->GetDataTypeIndex();
			szType = XVSM_DTSTR[nIdx];
			szDefVal = pData->GetDefaultValueStr().c_str();
			if(nCol == 3)
			{
				i = 0;
				bstr = szName.AllocSysString();
				saArray.PutElement(&i, bstr);
				SysFreeString(bstr);

				i = 1;
				bstr = szType.AllocSysString();
				saArray.PutElement(&i, bstr);
				SysFreeString(bstr);

				i = 2;
				bstr = szDefVal.AllocSysString();
				saArray.PutElement(&i, bstr);
				SysFreeString(bstr);
			}
			else
			{
				szVal = pData->GetDataValueStr().c_str();

				i = 0;
				bstr = szName.AllocSysString();
				saArray.PutElement(&i, bstr);
				SysFreeString(bstr);

				i = 1;
				bstr = szType.AllocSysString();
				saArray.PutElement(&i, bstr);
				SysFreeString(bstr);

				i = 2;
				bstr = szDefVal.AllocSysString();
				saArray.PutElement(&i, bstr);
				SysFreeString(bstr);

				i = 3;
				bstr = szVal.AllocSysString();
				saArray.PutElement(&i, bstr);
				SysFreeString(bstr);
			}
		}
		m_xlsRange.put_Value(COleVariant(saArray));
		m_nCurRow++;
	}

	m_nCurRow += 2;
	bRet = true;
	return bRet;
}

bool CVOA_ExcelExport::ExportGlobal(CVSB_Module* pModule, bool bFinalVal)
{
	bool			bRet = false;
    CStringW		szText;
    CStringW		szCol;
    CStringW		szTemp;
	COleVariant		covOptional(DISP_E_PARAMNOTFOUND, VT_ERROR);
	long			nCol;
	//long			nColWidth;

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

	szCol = XVSM_FIRSTLETTER;
	szText.Format(_T("%s%d"), szCol, m_nCurRow+1);
	m_xlsRange = m_xlsWSheet.get_Range(COleVariant(szText.GetBuffer()),covOptional);
	szText.GetBuffer();
	szText = XVSM_MACRO_GLOBALVAR;
	szText += _T(":");
	m_xlsRange.put_Value(COleVariant(COleVariant(szText.GetBuffer())));
	szText.GetBuffer();

	m_nCurRow++;

	CVSB_VarObjTable::iterator iter;
	IVSB_DataBase*	pData;
	CStringW		szType;		
	CStringW		szName;		
	CStringW		szVal;
	CStringW		szDefVal;
	long			nIdx;
	long			nAEType;
	long			nASize;
	long			i;
	COleSafeArray	saArray;
	BSTR			bstr;
	long			nTemp;

	nTemp = 1;
	saArray.Create(VT_BSTR, 1, (DWORD*)&nCol);

	szText.Format(_T("%s%d"), szCol, m_nCurRow+1);
	m_xlsRange = m_xlsWSheet.get_Range(COleVariant(szText.GetBuffer()),covOptional);
	szText.GetBuffer();

	m_xlsRange = m_xlsRange.get_Resize(COleVariant((short)1),COleVariant((short)nCol));
	for(i = 0; i < nCol; i++)
	{
		szTemp = XVSM_VAR_TITLESTR[i];
		bstr = szTemp.AllocSysString();
		saArray.PutElement(&i, bstr);
		SysFreeString(bstr);
	}
	m_xlsRange.put_Value(COleVariant(saArray));
	m_nCurRow++;

	for(iter = pModule->m_OutputVars.m_ObjTbl.begin(); iter != pModule->m_OutputVars.m_ObjTbl.end(); ++iter)
	{
		szText.Format(_T("%s%d"), szCol, m_nCurRow+1);
		m_xlsRange = m_xlsWSheet.get_Range(COleVariant(szText.GetBuffer()),covOptional);
		szText.GetBuffer();
		m_xlsRange = m_xlsRange.get_Resize(COleVariant((short)1),COleVariant((short)nCol));

		pData = iter->second;
		szName = iter->first.c_str();
		if(pData)
		{
			nIdx = pData->GetDataTypeIndex();
			if(nIdx != XVSM_DT_ARRAY)
			{
				szType = XVSM_DTSTR[nIdx];
				szDefVal = pData->GetDefaultValueStr().c_str();
				if(nCol == 3)
				{
					i = 0;
					bstr = szName.AllocSysString();
					saArray.PutElement(&i, bstr);
					SysFreeString(bstr);

					i = 1;
					bstr = szType.AllocSysString();
					saArray.PutElement(&i, bstr);
					SysFreeString(bstr);

					i = 2;
					bstr = szDefVal.AllocSysString();
					saArray.PutElement(&i, bstr);
					SysFreeString(bstr);
				}
				else
				{
					szVal = pData->GetDataValueStr().c_str();

					i = 0;
					bstr = szName.AllocSysString();
					saArray.PutElement(&i, bstr);
					SysFreeString(bstr);

					i = 1;
					bstr = szType.AllocSysString();
					saArray.PutElement(&i, bstr);
					SysFreeString(bstr);

					i = 2;
					bstr = szDefVal.AllocSysString();
					saArray.PutElement(&i, bstr);
					SysFreeString(bstr);

					i = 3;
					bstr = szVal.AllocSysString();
					saArray.PutElement(&i, bstr);
					SysFreeString(bstr);
				}
				m_xlsRange.put_Value(COleVariant(saArray));
				m_nCurRow++;
			}
			else
			{
				nAEType = ((CVSB_Array*)pData)->GetElementDataTypeIndex();
				szType = XVSM_DTSTR[nAEType];
				nASize = ((CVSB_Array*)pData)->Size();

				i = 0;
				bstr = szName.AllocSysString();
				saArray.PutElement(&i, bstr);
				SysFreeString(bstr);

				i = 1;
				szText = XVSM_DTSTR[XVSM_DT_ARRAY];
				szText += _T("/");
				szText += szType;
				bstr = szText.AllocSysString();
				saArray.PutElement(&i, bstr);
				SysFreeString(bstr);

				i = 2;
				szTemp = XVSM_MACRO_ARRAYSIZE;
				szText.Format(_T("%s: %d"), szTemp, nASize);
				bstr = szText.AllocSysString();
				saArray.PutElement(&i, bstr);
				SysFreeString(bstr);
				
				if(nCol == 4)
				{
					i = 3;
					szText = _T("");
					bstr = szText.AllocSysString();
					saArray.PutElement(&i, bstr);
					SysFreeString(bstr);
				}
				m_xlsRange.put_Value(COleVariant(saArray));
				m_nCurRow++;

				for(int iLoop = 0; iLoop < nASize; iLoop++)
				{
					szText.Format(_T("%s%d"), szCol, m_nCurRow+1);
					m_xlsRange = m_xlsWSheet.get_Range(COleVariant(szText.GetBuffer()),covOptional);
					szText.GetBuffer();
					m_xlsRange = m_xlsRange.get_Resize(COleVariant((short)1),COleVariant((short)nCol));

					szDefVal = ((CVSB_Array*)pData)->At(iLoop)->GetDefaultValueStr().c_str();
					szVal = ((CVSB_Array*)pData)->At(iLoop)->GetDataValueStr().c_str();

					i = 0;
					szText = _T("");
					bstr = szText.AllocSysString();
					saArray.PutElement(&i, bstr);
					SysFreeString(bstr);

					i = 1;
					szText.Format(_T("%s[%d]"), szName, iLoop);
					bstr = szText.AllocSysString();
					saArray.PutElement(&i, bstr);
					SysFreeString(bstr);

					i = 2;
					bstr = szDefVal.AllocSysString();
					saArray.PutElement(&i, bstr);
					SysFreeString(bstr);

					if(nCol == 4)
					{
						i = 3;
						bstr = szVal.AllocSysString();
						saArray.PutElement(&i, bstr);
						SysFreeString(bstr);
					}
					m_xlsRange.put_Value(COleVariant(saArray));
					m_nCurRow++;
				}
			}
		}
	}

	m_nCurRow += 2;
	bRet = true;
	return bRet;
}

bool CVOA_ExcelExport::ExportLocal(CVSB_Module* pModule, bool bFinalVal)
{
	bool			bRet = false;
    CStringW		szText;
    CStringW		szCol;
    CStringW		szTemp;
	COleVariant		covOptional(DISP_E_PARAMNOTFOUND, VT_ERROR);
	long			nCol;
	//long			nColWidth;

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

	szCol = XVSM_FIRSTLETTER;
	szText.Format(_T("%s%d"), szCol, m_nCurRow+1);
	m_xlsRange = m_xlsWSheet.get_Range(COleVariant(szText.GetBuffer()),covOptional);
	szText.GetBuffer();
	szText = XVSM_MACRO_LOCALVAR;
	szText += _T(":");
	m_xlsRange.put_Value(COleVariant(COleVariant(szText.GetBuffer())));
	szText.GetBuffer();

	m_nCurRow++;

	CVSB_VarObjTable::iterator iter;
	IVSB_DataBase*	pData;
	CStringW		szType;		
	CStringW		szName;		
	CStringW		szVal;
	CStringW		szDefVal;
	long			nIdx;
	long			nAEType;
	long			nASize;
	long			i;
	COleSafeArray	saArray;
	BSTR			bstr;
	long			nTemp;

	nTemp = 1;
	saArray.Create(VT_BSTR, 1, (DWORD*)&nCol);

	szText.Format(_T("%s%d"), szCol, m_nCurRow+1);
	m_xlsRange = m_xlsWSheet.get_Range(COleVariant(szText.GetBuffer()),covOptional);
	szText.GetBuffer();

	m_xlsRange = m_xlsRange.get_Resize(COleVariant((short)1),COleVariant((short)nCol));
	for(i = 0; i < nCol; i++)
	{
		szTemp = XVSM_VAR_TITLESTR[i];
		bstr = szTemp.AllocSysString();
		saArray.PutElement(&i, bstr);
		SysFreeString(bstr);
	}
	m_xlsRange.put_Value(COleVariant(saArray));
	m_nCurRow++;

	for(iter = pModule->m_LocalVars.m_ObjTbl.begin(); iter != pModule->m_LocalVars.m_ObjTbl.end(); ++iter)
	{
		szText.Format(_T("%s%d"), szCol, m_nCurRow+1);
		m_xlsRange = m_xlsWSheet.get_Range(COleVariant(szText.GetBuffer()),covOptional);
		szText.GetBuffer();
		m_xlsRange = m_xlsRange.get_Resize(COleVariant((short)1),COleVariant((short)nCol));

		pData = iter->second;
		szName = iter->first.c_str();
		if(pData)
		{
			nIdx = pData->GetDataTypeIndex();
			if(nIdx != XVSM_DT_ARRAY)
			{
				szType = XVSM_DTSTR[nIdx];
				szDefVal = pData->GetDefaultValueStr().c_str();
				if(nCol == 3)
				{
					i = 0;
					bstr = szName.AllocSysString();
					saArray.PutElement(&i, bstr);
					SysFreeString(bstr);

					i = 1;
					bstr = szType.AllocSysString();
					saArray.PutElement(&i, bstr);
					SysFreeString(bstr);

					i = 2;
					bstr = szDefVal.AllocSysString();
					saArray.PutElement(&i, bstr);
					SysFreeString(bstr);
				}
				else
				{
					szVal = pData->GetDataValueStr().c_str();

					i = 0;
					bstr = szName.AllocSysString();
					saArray.PutElement(&i, bstr);
					SysFreeString(bstr);

					i = 1;
					bstr = szType.AllocSysString();
					saArray.PutElement(&i, bstr);
					SysFreeString(bstr);

					i = 2;
					bstr = szDefVal.AllocSysString();
					saArray.PutElement(&i, bstr);
					SysFreeString(bstr);

					i = 3;
					bstr = szVal.AllocSysString();
					saArray.PutElement(&i, bstr);
					SysFreeString(bstr);
				}
				m_xlsRange.put_Value(COleVariant(saArray));
				m_nCurRow++;
			}
			else
			{
				nAEType = ((CVSB_Array*)pData)->GetElementDataTypeIndex();
				szType = XVSM_DTSTR[nAEType];
				nASize = ((CVSB_Array*)pData)->Size();

				i = 0;
				bstr = szName.AllocSysString();
				saArray.PutElement(&i, bstr);
				SysFreeString(bstr);

				i = 1;
				szText = XVSM_DTSTR[XVSM_DT_ARRAY];
				szText += _T("/");
				szText += szType;
				bstr = szText.AllocSysString();
				saArray.PutElement(&i, bstr);
				SysFreeString(bstr);

				i = 2;
				szTemp = XVSM_MACRO_ARRAYSIZE;
				szText.Format(_T("%s: %d"), szTemp, nASize);
				bstr = szText.AllocSysString();
				saArray.PutElement(&i, bstr);
				SysFreeString(bstr);
				
				if(nCol == 4)
				{
					i = 3;
					szText = _T("");
					bstr = szText.AllocSysString();
					saArray.PutElement(&i, bstr);
					SysFreeString(bstr);
				}
				m_xlsRange.put_Value(COleVariant(saArray));
				m_nCurRow++;

				for(int iLoop = 0; iLoop < nASize; iLoop++)
				{
					szText.Format(_T("%s%d"), szCol, m_nCurRow+1);
					m_xlsRange = m_xlsWSheet.get_Range(COleVariant(szText.GetBuffer()),covOptional);
					szText.GetBuffer();
					m_xlsRange = m_xlsRange.get_Resize(COleVariant((short)1),COleVariant((short)nCol));

					szDefVal = ((CVSB_Array*)pData)->At(iLoop)->GetDefaultValueStr().c_str();
					szVal = ((CVSB_Array*)pData)->At(iLoop)->GetDataValueStr().c_str();

					i = 0;
					szText = _T("");
					bstr = szText.AllocSysString();
					saArray.PutElement(&i, bstr);
					SysFreeString(bstr);

					i = 1;
					szText.Format(_T("%s[%d]"), szName, iLoop);
					bstr = szText.AllocSysString();
					saArray.PutElement(&i, bstr);
					SysFreeString(bstr);

					i = 2;
					bstr = szDefVal.AllocSysString();
					saArray.PutElement(&i, bstr);
					SysFreeString(bstr);

					if(nCol == 4)
					{
						i = 3;
						bstr = szVal.AllocSysString();
						saArray.PutElement(&i, bstr);
						SysFreeString(bstr);
					}
					m_xlsRange.put_Value(COleVariant(saArray));
					m_nCurRow++;
				}
			}
		}
	}

	m_nCurRow += 2;
	bRet = true;
	return bRet;
}

bool CVOA_ExcelExport::ExportPU(CVSB_Module* pModule)
{
	bool			bRet = false;
    CStringW		szText;
    CStringW		szCol;
    CStringW		szTemp;
	COleVariant		covOptional(DISP_E_PARAMNOTFOUND, VT_ERROR);
	long			nCol = 4;
	COleSafeArray	saArray;
	BSTR			bstr;
	//wchar_t			ch[256];
	CStringW		szName;		
	CStringW		szLeft;
	long			i;
	long			j;
	long			nID, n; 


	saArray.Create(VT_BSTR, 1, (DWORD*)&nCol);

	szCol = XVSM_FIRSTLETTER;
	szText.Format(_T("%s%d"), szCol, m_nCurRow+1);
	m_xlsRange = m_xlsWSheet.get_Range(COleVariant(szText.GetBuffer()),covOptional);
	m_xlsRange = m_xlsRange.get_Resize(COleVariant((short)1),COleVariant((short)nCol));

	i = 0;
	szText = XVSM_PUSTR_INIT;
	szText += _T(":");
	bstr = szText.AllocSysString();
	saArray.PutElement(&i, bstr);
	SysFreeString(bstr);

	i = 1;
	szText = _T("");
	bstr = szText.AllocSysString();
	saArray.PutElement(&i, bstr);
	SysFreeString(bstr);

	i = 2;
	szText = _T("");
	bstr = szText.AllocSysString();
	saArray.PutElement(&i, bstr);
	SysFreeString(bstr);

	i = 3;
	szText = XVSM_PU_ATTRSTR[(int)enXVSB_PUINIT]; 
	bstr = szText.AllocSysString();
	saArray.PutElement(&i, bstr);
	SysFreeString(bstr);
	m_xlsRange.put_Value(COleVariant(saArray));
	m_nCurRow++;

	for(j = 0; 	j < (long)pModule->m_Initialize.m_PrevPUlist.size(); j++)
	{
		szText.Format(_T("%s%d"), szCol, m_nCurRow+1);
		m_xlsRange = m_xlsWSheet.get_Range(COleVariant(szText.GetBuffer()),covOptional);
		szText.GetBuffer();
		m_xlsRange = m_xlsRange.get_Resize(COleVariant((short)1),COleVariant((short)nCol));

		i = 0;
		szText = _T("");
		bstr = szText.AllocSysString();
		saArray.PutElement(&i, bstr);
		SysFreeString(bstr);

		i = 1;
		szText = XVSB_STR_PRINTLINKPREV;
		bstr = szText.AllocSysString();
		saArray.PutElement(&i, bstr);
		SysFreeString(bstr);

		i = 2;
		szText = _T("");
		bstr = szText.AllocSysString();
		saArray.PutElement(&i, bstr);
		SysFreeString(bstr);

		i = 3;
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
		bstr = szText.AllocSysString();
		saArray.PutElement(&i, bstr);
		SysFreeString(bstr);
		m_xlsRange.put_Value(COleVariant(saArray));
		m_nCurRow++;
	}
	for(j = 0; 	j < (long)pModule->m_Initialize.m_NextPUlist.size(); j++)
	{
		szText.Format(_T("%s%d"), szCol, m_nCurRow+1);
		m_xlsRange = m_xlsWSheet.get_Range(COleVariant(szText.GetBuffer()),covOptional);
		szText.GetBuffer();
		m_xlsRange = m_xlsRange.get_Resize(COleVariant((short)1),COleVariant((short)nCol));

		i = 0;
		szText = _T("");
		bstr = szText.AllocSysString();
		saArray.PutElement(&i, bstr);
		SysFreeString(bstr);

		i = 1;
		szText = XVSB_STR_PRINTLINKNEXT;
		bstr = szText.AllocSysString();
		saArray.PutElement(&i, bstr);
		SysFreeString(bstr);

		i = 2;
		szText = _T("");
		bstr = szText.AllocSysString();
		saArray.PutElement(&i, bstr);
		SysFreeString(bstr);

		i = 3;
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
		bstr = szText.AllocSysString();
		saArray.PutElement(&i, bstr);
		SysFreeString(bstr);
		m_xlsRange.put_Value(COleVariant(saArray));
		m_nCurRow++;
	}
	m_nCurRow++;


	CVSB_PUMap::iterator puiter;

	for(puiter = pModule->m_PUmap.begin(); puiter != pModule->m_PUmap.end(); ++puiter)
	{
		szText.Format(_T("%s%d"), szCol, m_nCurRow+1);
		m_xlsRange = m_xlsWSheet.get_Range(COleVariant(szText.GetBuffer()),covOptional);
		szText.GetBuffer();
		m_xlsRange = m_xlsRange.get_Resize(COleVariant((short)1), COleVariant((short)nCol));

		i = 0;
		szText = puiter->second->GetPUName().c_str();
		szText += _T(":");
		bstr = szText.AllocSysString();
		saArray.PutElement(&i, bstr);
		SysFreeString(bstr);

		i = 1;
		szText.Format(_T("ID: %d"), (long)puiter->first);	
		bstr = szText.AllocSysString();
		saArray.PutElement(&i, bstr);
		SysFreeString(bstr);

		i = 2;
		szText = _T("");
		bstr = szText.AllocSysString();
		saArray.PutElement(&i, bstr);
		SysFreeString(bstr);

		i = 3;
		szText = XVSM_PU_ATTRSTR[(int)puiter->second->GetPUType()];
		bstr = szText.AllocSysString();
		saArray.PutElement(&i, bstr);
		SysFreeString(bstr);
		
		m_xlsRange.put_Value(COleVariant(saArray));
		m_nCurRow++;


		for(j = 0; 	j < (long)puiter->second->m_PrevPUlist.size(); j++)
		{
			szText.Format(_T("%s%d"), szCol, m_nCurRow+1);
			m_xlsRange = m_xlsWSheet.get_Range(COleVariant(szText.GetBuffer()),covOptional);
			szText.GetBuffer();
			m_xlsRange = m_xlsRange.get_Resize(COleVariant((short)1), COleVariant((short)nCol));

			i = 0;
			szText = _T("");
			bstr = szText.AllocSysString();
			saArray.PutElement(&i, bstr);
			SysFreeString(bstr);

			i = 1;
			nID = puiter->second->m_PrevPUlist[j];
			szText = XVSB_STR_PRINTLINKPREV;
			bstr = szText.AllocSysString();
			saArray.PutElement(&i, bstr);
			SysFreeString(bstr);

			i = 2;
			szText = _T("");
			bstr = szText.AllocSysString();
			saArray.PutElement(&i, bstr);
			SysFreeString(bstr);

			i = 3;
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
			bstr = szText.AllocSysString();
			saArray.PutElement(&i, bstr);
			SysFreeString(bstr);

			m_xlsRange.put_Value(COleVariant(saArray));
			m_nCurRow++;
		}

		if(puiter->second->GetPUType() != enXVSB_PULOGIC)
		{
			for(j = 0; 	j < (long)puiter->second->m_NextPUlist.size(); j++)
			{
				szText.Format(_T("%s%d"), szCol, m_nCurRow+1);
				m_xlsRange = m_xlsWSheet.get_Range(COleVariant(szText.GetBuffer()),covOptional);
				szText.GetBuffer();
				m_xlsRange = m_xlsRange.get_Resize(COleVariant((short)1), COleVariant((short)nCol));

				i = 0;
				szText = _T("");
				bstr = szText.AllocSysString();
				saArray.PutElement(&i, bstr);
				SysFreeString(bstr);

				i = 1;
				szText = XVSB_STR_PRINTLINKNEXT;
				bstr = szText.AllocSysString();
				saArray.PutElement(&i, bstr);
				SysFreeString(bstr);

				i = 2;
				szText = _T("");
				bstr = szText.AllocSysString();
				saArray.PutElement(&i, bstr);
				SysFreeString(bstr);

				i = 3;
				nID = puiter->second->m_NextPUlist[j];
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
				bstr = szText.AllocSysString();
				saArray.PutElement(&i, bstr);
				SysFreeString(bstr);

				m_xlsRange.put_Value(COleVariant(saArray));
				m_nCurRow++;
			}
		}
		else
		{
			szText.Format(_T("%s%d"), szCol, m_nCurRow+1);
			m_xlsRange = m_xlsWSheet.get_Range(COleVariant(szText.GetBuffer()),covOptional);
			szText.GetBuffer();
			m_xlsRange = m_xlsRange.get_Resize(COleVariant((short)1), COleVariant((short)nCol));

			i = 0;
			szText = _T("");
			bstr = szText.AllocSysString();
			saArray.PutElement(&i, bstr);
			SysFreeString(bstr);

			i = 1;
			szText = XVSB_STR_PRINTLINKYESNEXT;
			bstr = szText.AllocSysString();
			saArray.PutElement(&i, bstr);
			SysFreeString(bstr);

			i = 2;
			szText = _T("");
			bstr = szText.AllocSysString();
			saArray.PutElement(&i, bstr);
			SysFreeString(bstr);

			i = 3;
			nID = ((CVSB_LPU*)puiter->second)->m_nYesNextPU;
			szText += _T("ID: ");
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
			bstr = szText.AllocSysString();
			saArray.PutElement(&i, bstr);
			SysFreeString(bstr);
			m_xlsRange.put_Value(COleVariant(saArray));
			m_nCurRow++;

			szText.Format(_T("%s%d"), szCol, m_nCurRow+1);
			m_xlsRange = m_xlsWSheet.get_Range(COleVariant(szText.GetBuffer()),covOptional);
			szText.GetBuffer();
			m_xlsRange = m_xlsRange.get_Resize(COleVariant((short)1), COleVariant((short)nCol));

			i = 0;
			szText = _T("");
			bstr = szText.AllocSysString();
			saArray.PutElement(&i, bstr);
			SysFreeString(bstr);

			i = 1;
			szText = XVSB_STR_PRINTLINKNONEXT;
			bstr = szText.AllocSysString();
			saArray.PutElement(&i, bstr);
			SysFreeString(bstr);

			i = 2;
			szText = _T("");
			bstr = szText.AllocSysString();
			saArray.PutElement(&i, bstr);
			SysFreeString(bstr);

			i = 3;
			nID = ((CVSB_LPU*)puiter->second)->m_nNoNextPU;
			szText += _T("ID: ");
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
			bstr = szText.AllocSysString();
			saArray.PutElement(&i, bstr);
			SysFreeString(bstr);
			m_xlsRange.put_Value(COleVariant(saArray));
			m_nCurRow++;
		}

		if(puiter->second->GetPUType() == enXVSB_PUSIMPLE)
		{
			for(j = 0; j < ((CVSB_SPU*)puiter->second)->GetInnerCount(); j++)
			{
				szText.Format(_T("%s%d"), szCol, m_nCurRow+1);
				m_xlsRange = m_xlsWSheet.get_Range(COleVariant(szText.GetBuffer()),covOptional);
				szText.GetBuffer();
				m_xlsRange = m_xlsRange.get_Resize(COleVariant((short)1), COleVariant((short)nCol));

				i = 0;
				szText = _T("");
				bstr = szText.AllocSysString();
				saArray.PutElement(&i, bstr);
				SysFreeString(bstr);

				i = 1;
				szText = XVSB_STR_PRINTEQUATION;
				bstr = szText.AllocSysString();
				saArray.PutElement(&i, bstr);
				SysFreeString(bstr);

				i = 2;
				szText = _T("");
				bstr = szText.AllocSysString();
				saArray.PutElement(&i, bstr);
				SysFreeString(bstr);

				i = 3;
				szText = ((CVSB_SPU*)puiter->second)->GetEquationStr(j).c_str();
				bstr = szText.AllocSysString();
				saArray.PutElement(&i, bstr);
				SysFreeString(bstr);
				m_xlsRange.put_Value(COleVariant(saArray));
				m_nCurRow++;
			}
		}
		else if(puiter->second->GetPUType() == enXVSB_PULOGIC)
		{
			for(j = 0; j < ((CVSB_SPU*)puiter->second)->GetInnerCount(); j++)
			{
				szText.Format(_T("%s%d"), szCol, m_nCurRow+1);
				m_xlsRange = m_xlsWSheet.get_Range(COleVariant(szText.GetBuffer()),covOptional);
				szText.GetBuffer();
				m_xlsRange = m_xlsRange.get_Resize(COleVariant((short)1), COleVariant((short)nCol));

				i = 0;
				szText = _T("");
				bstr = szText.AllocSysString();
				saArray.PutElement(&i, bstr);
				SysFreeString(bstr);

				i = 1;
				szText = XVSB_STR_PRINTCOMPARE;
				bstr = szText.AllocSysString();
				saArray.PutElement(&i, bstr);
				SysFreeString(bstr);

				i = 2;
				szText = XVSM_LGRSTR[(int)((CVSB_LPU*)puiter->second)->GetLGRelation(j)]; 
				bstr = szText.AllocSysString();
				saArray.PutElement(&i, bstr);
				SysFreeString(bstr);

				i = 3;
				szText = ((CVSB_LPU*)puiter->second)->GetSingleCMPStr(j).c_str();
				bstr = szText.AllocSysString();
				saArray.PutElement(&i, bstr);
				SysFreeString(bstr);
				m_xlsRange.put_Value(COleVariant(saArray));
				m_nCurRow++;
			}
		}
		m_nCurRow++;
	}

	m_nCurRow++;

	bRet = true;
	return bRet;
}