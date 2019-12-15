// 2005/02/17
#include <string.h>
#include "xvsb_chdrfile.h"
#include "xvsb_filconst.h"

CVSB_CHeaderFile::CVSB_CHeaderFile(std::wstring& szDir, std::wstring& szName)
	: IVSB_FileExport(szDir, szName)
{
	m_szFile = m_szDirectory;
	m_szFile += L"\\";
	m_szFile += m_szModule;
	m_szFile += XVSM_MACRO_HEXT;
}

CVSB_CHeaderFile::CVSB_CHeaderFile(const wchar_t* szDir, const wchar_t* szName)
	: IVSB_FileExport(szDir, szName)
{
	m_szFile = m_szDirectory;
	m_szFile += L"\\";
	m_szFile += m_szModule;
	m_szFile += XVSM_MACRO_HEXT;
}

CVSB_CHeaderFile::~CVSB_CHeaderFile(void)
{
}

bool CVSB_CHeaderFile::WriteHeader(std::wstring& str)
{
	bool bRet = true;
	m_ExportFile << L"/*" << str.c_str() << L"*/" << std::endl;
	return bRet;
}

bool CVSB_CHeaderFile::WriteHeader(const wchar_t* str)
{
	bool bRet = true;
	m_ExportFile << L"/*" << str << L"*/" << std::endl;
	return bRet;
}

bool CVSB_CHeaderFile::WriteFooter(std::wstring& str)
{
	bool bRet = true;
	m_ExportFile << L"/*" << str.c_str() << L"*/" << std::endl;
	return bRet;
}

bool CVSB_CHeaderFile::WriteFooter(const wchar_t* str)
{
	bool bRet = true;
	m_ExportFile << L"/*" << str << L"*/" << std::endl;
	return bRet;
}

bool CVSB_CHeaderFile::BeginExport(void)
{
	bool bRet = false;
	wchar_t* strUp;

	strUp = _wcsdup(m_szModule.c_str());
	if(strUp == NULL)
		return bRet;

	strUp = _wcsupr(strUp);

	//
	std::wstring szHGuard;
	szHGuard = XVSM_PREV_DUNDERSCORE;
	szHGuard += strUp;
	szHGuard += XVSM_SUNDERSCORE;
	szHGuard += XVSM_MACRO_UPPERH;
	szHGuard += XVSM_LAST_DUNDERSCORE;

	// Write #ifndef __XXXX_H__
	std::wstring szText;
	szText = XVSM_MACRO_IFNOTDEF;
	szText += szHGuard;

	m_ExportFile << szText.c_str() << std::endl;

	// Write #define __XXXX_H__
	szText = XVSM_MACRO_DEFINE;
	szText += szHGuard;

	m_ExportFile << szText.c_str() << L"\n\n"<< std::endl;

	bRet = true;

	free(strUp);
	return bRet;
}

bool CVSB_CHeaderFile::EndExport(void)
{
	bool bRet = true;

	// Write #endif
	std::wstring szText;
	szText = XVSM_MACRO_ENDIF;
	m_ExportFile << szText.c_str() << std::endl;

	return bRet;
}

bool CVSB_CHeaderFile::BeginModule(void)
{
	bool bRet = true;

	// Write class XXXXXX
	//       {
	std::wstring szText;
	szText = XVSM_MACRO_CLASSID;
	szText += L" ";
	szText += m_szModule;
	m_ExportFile << szText.c_str() << std::endl;

	szText = XVSM_MACRO_LB;
	m_ExportFile << szText.c_str() << std::endl;

	// Write public:
	WritePublic();

	// Write constructor
	szText = L"\t";
	szText += m_szModule;
	szText += XVSM_MACRO_VOIDPARA;
	szText += XVSM_MACRO_SEMICOLON;

	m_ExportFile << szText.c_str() << std::endl;

	// Write destructor
	szText = L"\t";
	szText += XVSM_MACRO_NOTSIGN;
	szText += m_szModule;
	szText += XVSM_MACRO_VOIDPARA;
	szText += XVSM_MACRO_SEMICOLON;

	m_ExportFile << szText.c_str() << std::endl;

	// Write private:
	szText = XVSM_MACRO_PRIVATE;
	szText += XVSM_MACRO_COLON;
	m_ExportFile << szText.c_str() << std::endl;

	// Write step counter m_nID
	szText = L"\t";
	szText += XVSM_MACRO_PRELONG;
	szText += L" ";
	szText += XVSM_MACRO_COUNTERVAR;
	szText += XVSM_MACRO_SEMICOLON;

	m_ExportFile << szText.c_str() << L"\n" << std::endl;

	return bRet;
}

bool CVSB_CHeaderFile::BeginModule(std::wstring& szModule)
{
	m_szModule = szModule;
	return BeginModule();
}

bool CVSB_CHeaderFile::EndModule(void)
{
	bool bRet = true;

	// Write };
	std::wstring szText;
	szText = XVSM_MACRO_RB;
	szText += XVSM_MACRO_SEMICOLON;
	m_ExportFile << szText.c_str() << L"\n\n" << std::endl;

	return bRet;
}

bool CVSB_CHeaderFile::BeginEntry(void)
{
	bool bRet = true;

	std::wstring szText;

	// Write public:
	WritePublic();

	//Write Startup declaration
	szText = L"\t";
	szText += XVSM_MACRO_PREVOID;
	szText += L" ";
	szText += XVSM_MACRO_SETENTRY;
	szText += XVSM_MACRO_VOIDPARA;
	szText += XVSM_MACRO_SEMICOLON;
	m_ExportFile << szText.c_str() << std::endl;

	WriteNextLine();

	return bRet;
}

bool CVSB_CHeaderFile::EndEntry(void)
{
	bool bRet = true;

	//WriteNextLine();
	//WriteNextLine();

	return bRet;
}

bool CVSB_CHeaderFile::BeginInitialize(void)
{
	bool bRet = true;

	std::wstring szText;

	WritePublic();
	//Write Initialize declaration
	szText = L"\t";
	szText += XVSM_MACRO_PRELONG;
	szText += L" ";
	szText += XVSM_MACRO_INITIALIZE;
	szText += XVSM_MACRO_VOIDPARA;
	szText += XVSM_MACRO_SEMICOLON;
	m_ExportFile << szText.c_str() << std::endl;

	WriteNextLine();

	return bRet;
}

bool CVSB_CHeaderFile::EndInitialize(void)
{
	bool bRet = true;

	return bRet;
}

bool CVSB_CHeaderFile::WriteVariable(std::wstring& szType, std::wstring& szName, std::wstring& szVal)
{
	return WriteVariable(szType.c_str(), szName.c_str(), szVal.c_str());
}

bool CVSB_CHeaderFile::WriteVariable(const wchar_t* szType, const wchar_t* szName, const wchar_t* szVal)
{
	bool bRet = true;

	m_ExportFile << L"\t" << szType << L" " << szName << L";"<< std::endl;

	return bRet;
}

bool CVSB_CHeaderFile::WritePublic(void)
{
	bool bRet = true;

	m_ExportFile << XVSM_MACRO_PUBLIC << XVSM_MACRO_COLON << std::endl;

	return bRet;
}

bool CVSB_CHeaderFile::WriteProtected(void)
{
	bool bRet = true;

	m_ExportFile << XVSM_MACRO_PROTECTED << XVSM_MACRO_COLON << std::endl;

	return bRet;
}

bool CVSB_CHeaderFile::WritePrivate(void)
{
	bool bRet = true;

	m_ExportFile << XVSM_MACRO_PRIVATE << XVSM_MACRO_COLON << std::endl;

	return bRet;
}

bool CVSB_CHeaderFile::WriteNextLine(void)
{
	bool bRet = true;

	m_ExportFile << L"\n" << std::endl;

	return bRet;
}

bool CVSB_CHeaderFile::WriteArrayDeclaration(std::wstring szElemType, std::wstring szName, long nSize)
{
	return WriteArrayDeclaration(szElemType.c_str(), szName.c_str(), nSize);
}

bool CVSB_CHeaderFile::WriteArrayDeclaration(const wchar_t* szElemType, const wchar_t* szName, long nSize)
{
	bool bRet = true;

	wchar_t szSize[256];
	memset(szSize, 0, 256*sizeof(wchar_t));
	_itow(nSize, szSize, 10);

	m_ExportFile << L"\t" << szElemType << L" " << szName << L"[" << szSize << L"]" << L";"<< std::endl;

	return bRet;
}

bool CVSB_CHeaderFile::WritePlainFunction(std::wstring& szFunc, std::wstring& szReturn)
{
	return WritePlainFunction(szFunc.c_str(), szReturn.c_str());
}

bool CVSB_CHeaderFile::WritePlainFunction(const wchar_t* szFunc, const wchar_t* szReturn)
{
	bool bRet = true;

	m_ExportFile << L"\t" << szReturn << L" " << szFunc << XVSM_MACRO_VOIDPARA << L";"<< std::endl;

	return bRet;
}

