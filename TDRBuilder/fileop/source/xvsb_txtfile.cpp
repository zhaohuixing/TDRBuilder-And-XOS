//2005/02/26
#include "xvsb_txtfile.h"
#include "xvsb_filconst.h"
#include "xvsb_strutil.h"
#include <assert.h>
#include <time.h>

CVSB_CTextFile::CVSB_CTextFile(std::wstring& szDir, std::wstring& szName)
	: IVSB_FileExport(szDir, szName)
{
	m_szFile = m_szDirectory;
	m_szFile += L"\\";
	m_szFile += m_szModule;
	m_szFile += XVSM_MACRO_TXTEXT;
}

CVSB_CTextFile::CVSB_CTextFile(const wchar_t* szDir, const wchar_t* szName)
	: IVSB_FileExport(szDir, szName)
{
	m_szFile = m_szDirectory;
	m_szFile += L"\\";
	m_szFile += m_szModule;
	m_szFile += XVSM_MACRO_TXTEXT;
}

CVSB_CTextFile::CVSB_CTextFile(std::wstring& szDir, std::wstring& szName, std::wstring& szModule)
	: IVSB_FileExport(szDir, szModule)
{
	m_szFile = m_szDirectory;
	m_szFile += L"\\";
	m_szFile += szName;
	m_szFile += XVSM_MACRO_TXTEXT;
}

CVSB_CTextFile::CVSB_CTextFile(const wchar_t* szDir, const wchar_t* szName, const wchar_t* szModule)
	: IVSB_FileExport(szDir, szModule)
{
	m_szFile = m_szDirectory;
	m_szFile += L"\\";
	m_szFile += szName;
	m_szFile += XVSM_MACRO_TXTEXT;
}

CVSB_CTextFile::~CVSB_CTextFile(void)
{
}

bool CVSB_CTextFile::WriteHeader(std::wstring& str)
{
	bool bRet = true;
	m_ExportFile << L"<<--" << str.c_str() << L"-->>" << std::endl;
	return bRet;
}

bool CVSB_CTextFile::WriteHeader(const wchar_t* str)
{
	bool bRet = true;
	m_ExportFile << L"<<--" << str << L"-->>" << std::endl;
	return bRet;
}

bool CVSB_CTextFile::WriteFooter(std::wstring& str)
{
	bool bRet = true;
	m_ExportFile << L"<<--" << str.c_str() << L"-->>" << std::endl;
	return bRet;
}

bool CVSB_CTextFile::WriteFooter(const wchar_t* str)
{
	bool bRet = true;
	m_ExportFile << L"<<--" << str << L"-->>" << std::endl;
	return bRet;
}

bool CVSB_CTextFile::BeginExport(void)
{
	bool bRet = true;

	return bRet;
}

bool CVSB_CTextFile::EndExport(void)
{
	bool bRet = true;

	return bRet;
}

bool CVSB_CTextFile::BeginModule(void)
{
	bool bRet = true;
	
	std::wstring szValue;


	m_ExportFile << L"[" << XVSM_MACRO_MODULE << L"]" << std::endl;
	m_ExportFile << XVSM_MACRO_NAME << L"=" << m_szModule.c_str() << std::endl;

	time_t		stTime;
	time(&stTime);
	szValue = _wctime(&stTime);
	m_ExportFile << XVSM_MACRO_TIME << L"=" << szValue.c_str() <<std::endl;

	return bRet;
}

bool CVSB_CTextFile::BeginModule(std::wstring& szModule)
{
	m_szModule = szModule;
	return BeginModule();
}

bool CVSB_CTextFile::EndModule(void)
{
	bool bRet = true;
	m_ExportFile << L"[" << XVSM_MACRO_MODULEEND << L"]" << std::endl;
	return bRet;
}

bool CVSB_CTextFile::BeginEntry(void)
{
	bool bRet = true;

	return bRet;
}

bool CVSB_CTextFile::EndEntry(void)
{
	bool bRet = true;

	return bRet;
}

bool CVSB_CTextFile::BeginInitialize(void)
{
	bool bRet = true;

	return bRet;
}

bool CVSB_CTextFile::EndInitialize(void)
{
	bool bRet = true;

	return bRet;
}

bool CVSB_CTextFile::WriteVariable(std::wstring& szType, std::wstring& szName, std::wstring& szVal)
{
	return WriteVariable(szType.c_str(), szName.c_str(), szVal.c_str());
}

bool CVSB_CTextFile::WriteVariable(const wchar_t* szType, const wchar_t* szName, const wchar_t* szVal)
{
	bool bRet = true;
	CVSB_CPPType2XMLType   cpp2xml;
	std::wstring szTemp = szType;
	std::wstring szValue = cpp2xml(szTemp);

	m_ExportFile << L"\t" << XVSM_MACRO_TYPE << L"=" << szValue.c_str();
	m_ExportFile << L"\t" << XVSM_MACRO_NAME << L"=" << szName;
	m_ExportFile << L"\t" << XVSM_MACRO_DEFVALUE << L"=" << szVal <<std::endl;
 	return bRet;
}

bool CVSB_CTextFile::WriteArrayDeclaration(std::wstring& szElemType, std::wstring& szName, long nSize)
{
	return WriteArrayDeclaration(szElemType.c_str(), szName.c_str(), nSize);
}

bool CVSB_CTextFile::WriteArrayDeclaration(const wchar_t* szElemType, const wchar_t* szName, long nSize)
{
	bool bRet = true;
	CVSB_CPPType2XMLType   cpp2xml;
	std::wstring szTemp = szElemType;
	std::wstring szValue = cpp2xml(szTemp);

	m_ExportFile << L"\t" << XVSM_MACRO_TYPE << L"=" << XVSM_MACRO_ARRAY;
	m_ExportFile << L"\t" << XVSM_MACRO_NAME << L"=" << szName;
	m_ExportFile << L"\t" << XVSM_MACRO_ARRAYTYPE << L"=" << szElemType;
	m_ExportFile << L"\t" << XVSM_MACRO_ARRAYSIZE << L"=" << nSize <<std::endl;
 	return bRet;
}

bool CVSB_CTextFile::WriteArrayElement(std::wstring& szAryName, long nIndx, std::wstring& szVal)
{
	return WriteArrayElement(szAryName.c_str(), nIndx, szVal.c_str());
}

bool CVSB_CTextFile::WriteArrayElement(const wchar_t* szAryName, long nIndx, const wchar_t* szVal)
{
	bool bRet = true;
	m_ExportFile << L"\t\t" << szAryName << L"[" << nIndx << L"]" << L"=" << szVal <<std::endl;
 	return bRet;
}

bool CVSB_CTextFile::WriteArrayElement(std::wstring& szAryName, long nIndx, std::wstring& szDefVal, std::wstring& szVal)
{
	return WriteArrayElement(szAryName.c_str(), nIndx, szDefVal.c_str(), szVal.c_str());
}

bool CVSB_CTextFile::WriteArrayElement(const wchar_t* szAryName, long nIndx, const wchar_t* szDefVal, const wchar_t* szVal)
{
	bool bRet = true;

	m_ExportFile << L"\t\t" << XVSM_MACRO_NAME << L"=" << szAryName << L"[" << nIndx << L"]";
	m_ExportFile << L"\t" << XVSM_MACRO_DEFVALUE << L"=" << szDefVal;
	m_ExportFile << L"\t" << XVSM_MACRO_REVALUE << L"=" << szVal <<std::endl;
		
 	return bRet;
}

bool CVSB_CTextFile::WriteVariable(std::wstring& szType, std::wstring& szName, std::wstring& szDefVal, std::wstring& szVal)
{
	return WriteVariable(szType.c_str(), szName.c_str(), szDefVal.c_str(), szVal.c_str());
}

bool CVSB_CTextFile::WriteVariable(const wchar_t* szType, const wchar_t* szName, const wchar_t* szDefVal, const wchar_t* szVal)
{
	bool bRet = true;
	m_ExportFile << L"\t" << XVSM_MACRO_TYPE << L"=" << szType;
	m_ExportFile << L"\t" << XVSM_MACRO_NAME << L"=" << szName;
	m_ExportFile << L"\t" << XVSM_MACRO_DEFVALUE << L"=" << szDefVal;
	m_ExportFile << L"\t" << XVSM_MACRO_REVALUE << L"=" << szVal <<std::endl;
 	return bRet;
}

bool CVSB_CTextFile::BeginInput(void)
{
	bool bRet = true;
	m_ExportFile << L"[" << XVSM_MACRO_INPUTVAR << L"]" << std::endl;
	return bRet;
}

bool CVSB_CTextFile::EndInput(void)
{
	bool bRet = true;
	m_ExportFile << L"[" << XVSM_MACRO_ENDVAR << L"]" << std::endl;
	return bRet;
}

bool CVSB_CTextFile::BeginGlobal(void)
{
	bool bRet = true;
	m_ExportFile << L"[" << XVSM_MACRO_GLOBALVAR << L"]" << std::endl;
	return bRet;
}

bool CVSB_CTextFile::EndGlobal(void)
{
	bool bRet = true;
	m_ExportFile << L"[" << XVSM_MACRO_ENDVAR << L"]" << std::endl;
	return bRet;
}

bool CVSB_CTextFile::BeginLocal(void)
{
	bool bRet = true;
	m_ExportFile << L"[" << XVSM_MACRO_LOCALVAR << L"]" << std::endl;
	return bRet;
}

bool CVSB_CTextFile::EndLocal(void)
{
	bool bRet = true;
	m_ExportFile << L"[" << XVSM_MACRO_ENDVAR << L"]" << std::endl;
	return bRet;
}

bool CVSB_CTextFile::WritePlainString(std::wstring& szStr)
{
	bool bRet = true;
	m_ExportFile << szStr.c_str() << std::endl;
	return bRet;
}

bool CVSB_CTextFile::WritePlainString(const wchar_t* szStr)
{
	bool bRet = true;
	m_ExportFile << szStr << std::endl;
	return bRet;
}

