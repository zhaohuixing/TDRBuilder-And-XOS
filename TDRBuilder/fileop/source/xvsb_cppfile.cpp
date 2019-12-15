// 2005/02/17
#include "xvsb_cppfile.h"
#include "xvsb_filconst.h"
#include "xvsb_strutil.h"

CVSB_CPPFile::CVSB_CPPFile(std::wstring& szDir, std::wstring& szName)
	: IVSB_FileExport(szDir, szName)
{
	m_szFile = m_szDirectory;
	m_szFile += L"\\";
	m_szFile += m_szModule;
	m_szFile += XVSM_MACRO_CPPEXT;
}

CVSB_CPPFile::CVSB_CPPFile(const wchar_t* szDir, const wchar_t* szName)
	: IVSB_FileExport(szDir, szName)
{
	m_szFile = m_szDirectory;
	m_szFile += L"\\";
	m_szFile += m_szModule;
	m_szFile += XVSM_MACRO_CPPEXT;
}

CVSB_CPPFile::~CVSB_CPPFile(void)
{
}

bool CVSB_CPPFile::WriteHeader(std::wstring& str)
{
	bool bRet = true;
	m_ExportFile << L"/*" << str.c_str() << L"*/" << std::endl;
	return bRet;
}

bool CVSB_CPPFile::WriteHeader(const wchar_t* str)
{
	bool bRet = true;
	m_ExportFile << L"/*" << str << L"*/" << std::endl;
	return bRet;
}

bool CVSB_CPPFile::WriteFooter(std::wstring& str)
{
	bool bRet = true;
	m_ExportFile << L"/*" << str.c_str() << L"*/" << std::endl;
	return bRet;
}

bool CVSB_CPPFile::WriteFooter(const wchar_t* str)
{
	bool bRet = true;
	m_ExportFile << L"/*" << str << L"*/" << std::endl;
	return bRet;
}

bool CVSB_CPPFile::BeginExport(void)
{
	bool bRet = true;

	// Write #include "module.h"
	std::wstring szInc;
	szInc = XVSM_MACRO_INCLUDE;
	szInc += L" \"";
	szInc += m_szModule;
	szInc += L".h";
	szInc += L"\"";

	m_ExportFile << szInc.c_str() << std::endl;

	// Write #include "xvsmath.h"
	szInc = XVSM_MACRO_INCXMATH;

	m_ExportFile << szInc.c_str() << L"\n\n" << std::endl;

	// Write #include <math.h>
	szInc = XVSM_MACRO_INCMATHH;
	m_ExportFile << szInc.c_str() << L"\n\n" << std::endl;

	return bRet;
}

bool CVSB_CPPFile::EndExport(void)
{
	bool bRet = true;
	
	// Nothing here......

	return bRet;
}

bool CVSB_CPPFile::BeginModule(void)
{
	bool bRet = true;

	std::wstring szText;

	// Write constructor
	szText = m_szModule;
	szText += XVSM_MACRO_DCOLON;
	szText += m_szModule;
	szText += XVSM_MACRO_VOIDPARA;
	m_ExportFile << szText.c_str() << std::endl;

	// Write {
	szText = XVSM_MACRO_LB;
	m_ExportFile << szText.c_str() << std::endl;
	
	// Write the startup function
	szText = L"\t";
	szText += XVSM_MACRO_SETENTRY;
	szText += XVSM_MACRO_VOIDFNSIGN;
	szText += XVSM_MACRO_SEMICOLON;
	m_ExportFile << szText.c_str() << std::endl;

	// Write the m_nID = -1;
	szText = L"\t";
	szText += XVSM_MACRO_COUNTERVAR;
	szText += L" ";
	szText += XVSM_MACRO_ASSIGN;
	szText += L" ";
	szText += XVSM_MACRO_MINUSONE;
	szText += XVSM_MACRO_SEMICOLON;
	m_ExportFile << szText.c_str() << std::endl;

	// Write }
	szText = XVSM_MACRO_RB;
	m_ExportFile << szText.c_str() << L"\n" << std::endl;

	// Write Destructor
	szText = m_szModule;
	szText += XVSM_MACRO_DCOLON;
	szText += XVSM_MACRO_NOTSIGN;
	szText += m_szModule;
	szText += XVSM_MACRO_VOIDPARA;
	m_ExportFile << szText.c_str() << std::endl;

	// Write {
	szText = XVSM_MACRO_LB;
	m_ExportFile << szText.c_str() << std::endl;
		
	// Write }
	szText = XVSM_MACRO_RB;
	m_ExportFile << szText.c_str() << L"\n" << std::endl;

	return bRet;
}

bool CVSB_CPPFile::BeginModule(std::wstring& szModule)
{
	m_szModule = szModule;
	return BeginModule();
}

bool CVSB_CPPFile::EndModule(void)
{
	bool bRet = true;

	// Nothing here......

	return bRet;
}

bool CVSB_CPPFile::BeginEntry(void)
{
	bool bRet = true;
	std::wstring szText;

	// Write Startup
	szText = XVSM_MACRO_PREVOID;
	szText += L" ";
	szText += m_szModule;
	szText += XVSM_MACRO_DCOLON;
	szText += XVSM_MACRO_SETENTRY;
	szText += XVSM_MACRO_VOIDPARA;
	m_ExportFile << szText.c_str() << std::endl;

	// Write {
	szText = XVSM_MACRO_LB;
	m_ExportFile << szText.c_str() << std::endl;

	return bRet;
}

bool CVSB_CPPFile::EndEntry(void)
{
	bool bRet = true;
	std::wstring szText;

	// Write }
	szText = XVSM_MACRO_RB;
	m_ExportFile << szText.c_str()  << L"\n" << std::endl;
	return bRet;
}

bool CVSB_CPPFile::BeginInitialize(void)
{
	bool bRet = true;

	std::wstring szText;

	//Write Initialize declaration
	szText = XVSM_MACRO_PRELONG;
	szText += L" ";
	szText += m_szModule;
	szText += XVSM_MACRO_DCOLON;
	szText += XVSM_MACRO_INITIALIZE;
	szText += XVSM_MACRO_VOIDPARA;
	m_ExportFile << szText.c_str() << std::endl;

	// Write {
	szText = XVSM_MACRO_LB;
	m_ExportFile << szText.c_str() << std::endl;

	return bRet;
}

bool CVSB_CPPFile::EndInitialize(void)
{
	bool bRet = true;
	std::wstring szText;

	// Write }
	szText = XVSM_MACRO_RB;
	m_ExportFile << szText.c_str()  << L"\n" << std::endl;
	return bRet;
}

bool CVSB_CPPFile::WriteVariable(std::wstring& szType, std::wstring& szName, std::wstring& szVal)
{
	return WriteVariable(szType.c_str(), szName.c_str(), szVal.c_str());
}

bool CVSB_CPPFile::WriteVariable(const wchar_t* szType, const wchar_t* szName, const wchar_t* szVal)
{
	bool bRet = true;

	m_ExportFile << L"\t" << szName << L" = " << szVal << L";" << std::endl;

	return bRet;
}

bool CVSB_CPPFile::WriteNextLine(void)
{
	bool bRet = true;

	m_ExportFile << L"\n" << std::endl;

	return bRet;
}

bool CVSB_CPPFile::WriteCounterReturn(bool bIsXML)
{
	bool bRet = true;

	m_ExportFile << XVSM_MACRO_RETURNCUNTER << std::endl;

	return bRet;
}

bool CVSB_CPPFile::WriteSetCounter(long nID, bool bIsXML)
{
	bool bRet = true;
	
	// Write 
	wchar_t szID[256];
	memset(szID, 0, 256*sizeof(wchar_t));
	_itow(nID, szID, 10);

	m_ExportFile << L"\t" << XVSM_MACRO_SETCOUNTER << szID << L";"<< std::endl;

	return bRet;
}

bool CVSB_CPPFile::WriteArrayElement(std::wstring szAryName, long nIndx, std::wstring szVal)
{
	return WriteArrayElement(szAryName.c_str(), nIndx, szVal.c_str());
}

bool CVSB_CPPFile::WriteArrayElement(const wchar_t* szAryName, long nIndx, const wchar_t* szVal)
{
	bool bRet = true;

	wchar_t szIdx[256];
	memset(szIdx, 0, 256*sizeof(wchar_t));
	_itow(nIndx, szIdx, 10);

	m_ExportFile << L"\t" << szAryName << L"[" << szIdx << L"]" L" = " << szVal << L";" << std::endl;

	return bRet;
}

bool CVSB_CPPFile::WritePlainFunction(std::wstring& szFunc, std::wstring& szReturn)
{
	return WritePlainFunction(szFunc.c_str(), szReturn.c_str());
}

bool CVSB_CPPFile::WritePlainFunction(const wchar_t* szFunc, const wchar_t* szReturn)
{
	bool bRet = true;

	m_ExportFile << szReturn << L" " << m_szModule.c_str() << XVSM_MACRO_DCOLON << szFunc << XVSM_MACRO_VOIDPARA << std::endl;

	return bRet;
}

bool CVSB_CPPFile::WritePlainString(std::wstring& szStr)
{
	return WritePlainString(szStr.c_str());
}

bool CVSB_CPPFile::WritePlainString(const wchar_t* szStr)
{
	bool bRet = true;

	m_ExportFile << szStr;

	return bRet;
}

bool CVSB_CPPFile::WriteFuncBegin(void)
{
	m_ExportFile << XVSM_MACRO_LB << std::endl;
	return true;
}

bool CVSB_CPPFile::WriteFuncEnd(void)
{
	m_ExportFile << XVSM_MACRO_RB << std::endl;
	return true;
}

bool CVSB_CPPFile::WriteFormula(std::wstring& szFn)
{
	bool bRet = true;
	
	CVSB_StrMarker2Fact m2fact;
	std::wstring szFunc;
	szFunc = m2fact(szFn);
	m_ExportFile << L"\t" << szFunc.c_str() << L";" << std::endl;

	return bRet;
}

bool CVSB_CPPFile::WriteFormula(const wchar_t* szFn)
{
	std::wstring szFunc = szFn;
	return WriteFormula(szFunc);
}

bool CVSB_CPPFile::WriteVariableDeclare(std::wstring& szType, std::wstring& szVar)
{
	return WriteVariableDeclare(szType.c_str(), szVar.c_str());
}

bool CVSB_CPPFile::WriteVariableDeclare(const wchar_t* szType, const wchar_t* szVar)
{
	bool bRet = true;
	m_ExportFile << L"\t" << szType << L"  " << szVar << L";" << std::endl;
	return bRet;
}

bool CVSB_CPPFile::WriteIFstatement(std::wstring& szCndit)
{
	return WriteIFstatement(szCndit.c_str());
}

bool CVSB_CPPFile::WriteIFstatement(const wchar_t* szCndit)
{
	bool bRet = true;

	m_ExportFile << L"\t" << L"if (" << szCndit << L")" << std::endl;

	return bRet;
}

bool CVSB_CPPFile::WriteELSEstatement(void)
{
	bool bRet = true;

	m_ExportFile << L"\t" << L"else" << std::endl;

	return bRet;
}

bool CVSB_CPPFile::WriteInnerLB(void)
{
	bool bRet = true;

	m_ExportFile << L"\t{\n\t";

	return bRet;
}

bool CVSB_CPPFile::WriteInnerRB(void)
{
	bool bRet = true;

	m_ExportFile << L"\t}" << std::endl;

	return bRet;
}
