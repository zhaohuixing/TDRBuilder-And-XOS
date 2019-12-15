// 2005/02/17
#include "xvsb_xmlfile.h"
#include "xvsb_filconst.h"
#include "xvsb_strutil.h"
#include <assert.h>
#include <time.h>

//const std::wstring	XMLSetting(L"<?xml version = \"1.0\" encoding=\"UTF-16\"?>");
const std::wstring	XMLSetting(L"<?xml version = \"1.0\" ?>");

CVSB_XMLFile::CVSB_XMLFile(std::wstring& szDir, std::wstring& szName)
	: IVSB_FileExport(szDir, szName)
{
	m_szFile = m_szDirectory;
	m_szFile += L"\\";
	m_szFile += m_szModule;
	_createsignlut();
	m_szExt = L"xml";
}

CVSB_XMLFile::CVSB_XMLFile(const wchar_t* szDir, const wchar_t* szName)
	: IVSB_FileExport(szDir, szName)
{
	m_szFile = m_szDirectory;
	m_szFile += L"\\";
	m_szFile += m_szModule;
	_createsignlut();
	m_szExt = L"xml";
}

CVSB_XMLFile::CVSB_XMLFile(std::wstring& szDir, std::wstring& szName, std::wstring& szModule)
	: IVSB_FileExport(szDir, szModule)
{
	m_szFile = m_szDirectory;
	m_szFile += L"\\";
	m_szFile += szName;
	_createsignlut();
	m_szExt = L"xml";
}

CVSB_XMLFile::CVSB_XMLFile(const wchar_t* szDir, const wchar_t* szName, const wchar_t* szModule)
	: IVSB_FileExport(szDir, szModule)
{
	m_szFile = m_szDirectory;
	m_szFile += L"\\";
	m_szFile += szName;
	_createsignlut();
	m_szExt = L"xml";
}

CVSB_XMLFile::~CVSB_XMLFile(void)
{
}

bool CVSB_XMLFile::Initialize(void)
{
    bool bStatus = false;

	m_szFile += L".";
	m_szFile += m_szExt;

    while(!m_TagStack.empty())
		m_TagStack.pop();
    
    m_AttrQ.clear();
    m_bTagWritten = true;
    
    if (_exinitialize())
    {
		_wirtestring(XMLSetting);
		bStatus = true;
    }

    return bStatus;
}

void CVSB_XMLFile::Shutdown(void)
{
#ifdef _XSVM_DEBUG_
	assert(m_TagStack.empty());
#endif
    while(!m_TagStack.empty())
		m_TagStack.pop();
    
	_exclose();
}

void CVSB_XMLFile::AddFileExt(std::wstring& szExt)
{
	m_szExt = szExt;
}

void CVSB_XMLFile::AddFileExt(const wchar_t* szExt)
{
	m_szExt = szExt;
}

void CVSB_XMLFile::ResetFullPath(std::wstring& szFile)
{
	m_szFile = szFile;
}

void CVSB_XMLFile::ResetFullPath(const wchar_t* szFile)
{
	m_szFile = szFile;
}

bool CVSB_XMLFile::WriteHeader(std::wstring& str)
{
	bool bRet = true;
	AddComment(str);
	return bRet;
}

bool CVSB_XMLFile::WriteHeader(const wchar_t* str)
{
	bool bRet = true;
	std::wstring szText = str;
	
	AddComment(str);

	return bRet;
}

bool CVSB_XMLFile::WriteFooter(std::wstring& str)
{
	bool bRet = true;
	AddComment(str);
	return bRet;
}

bool CVSB_XMLFile::WriteFooter(const wchar_t* str)
{
	bool bRet = true;

	std::wstring szText = str;
	
	AddComment(str);

	return bRet;
}

bool CVSB_XMLFile::BeginExport(void)
{
	bool bRet = true;
	
	std::wstring szTag = m_szExt;

	bRet = BeginTag(szTag);
	if(bRet)
	{
		std::wstring szVer = XVSM_ATTR_VER;
		std::wstring szNum = XVSM_MACRO_CURVER;
		AddAttribute(szVer, szNum);
	}

	return bRet;
}

bool CVSB_XMLFile::EndExport(void)
{
	bool bRet = true;

	bRet = EndTag();

	return bRet;
}

bool CVSB_XMLFile::BeginModule(void)
{
	bool bRet = true;
	
	std::wstring szAttr;
	std::wstring szValue;
	std::wstring szTag;

	szTag = XVSM_TAG_MODULE;

	bRet = BeginTag(szTag);

	if(bRet)
	{
		szAttr = XVSM_ATTR_NAME;
		szValue = m_szModule;
		AddAttribute(szAttr, szValue);

		szAttr = XVSM_ATTR_DATE;

		time_t		stTime;
		time(&stTime);

		szValue = _wctime(&stTime);

		AddAttribute(szAttr, szValue);
	}
	
	return bRet;
}

bool CVSB_XMLFile::BeginModule(std::wstring& szModule)
{
	m_szModule = szModule;
	return BeginModule();
}


bool CVSB_XMLFile::EndModule(void)
{
	bool bRet = true;

	bRet = EndTag();

	return bRet;
}

bool CVSB_XMLFile::BeginEntry(void)
{
	bool bRet = true;

	std::wstring szTag;

	szTag = XVSM_TAG_ENTRY;
	bRet = BeginTag(szTag);

	BeginInput();

	return bRet;
}

bool CVSB_XMLFile::EndEntry(void)
{
	bool bRet = true;

	EndInput();
	bRet = EndTag();

	return bRet;
}

bool CVSB_XMLFile::BeginXVSEntry(void)
{
	bool bRet = true;

	std::wstring szTag;

	szTag = XVSM_TAG_ENTRY;
	bRet = BeginTag(szTag);

	return bRet;
}

bool CVSB_XMLFile::EndXVSEntry(void)
{
	bool bRet = true;
	bRet = EndTag();
	return bRet;
}

bool CVSB_XMLFile::BeginInitialize(void)
{
	bool bRet = false;

	std::wstring szTag;

	szTag = XVSM_TAG_INITIALIZE;

	bRet = BeginTag(szTag);

	return bRet;
}

bool CVSB_XMLFile::EndInitialize(void)
{
	bool bRet = false;

	bRet = EndTag();

	return bRet;
}

bool CVSB_XMLFile::BeginPU(std::wstring& szPU, long nID, long nType)
{
	bool bRet = true;
	
	std::wstring szAttr;
	std::wstring szValue;
	std::wstring szTag;

	szTag = XVSM_TAG_PROCESSOR;

	bRet = BeginTag(szTag);

	if(bRet)
	{
		szAttr = XVSM_ATTR_NAME;
		szValue = szPU;
		AddAttribute(szAttr, szValue);

		szAttr = XVSM_ATTR_ID;
        wchar_t szVal[256];
		memset(szVal, 0, 256*sizeof(wchar_t));
		_itow(nID, szVal, 10);
		szValue = szVal;
		AddAttribute(szAttr, szValue);

		szAttr = XVSM_ATTR_TYPE;
		memset(szVal, 0, 256*sizeof(wchar_t));
		_itow(nType, szVal, 10);
		szValue = szVal;
		AddAttribute(szAttr, szValue);
	}
	
	return bRet;
}

bool CVSB_XMLFile::EndPU(void)
{
	bool bRet = false;

	bRet = EndTag();

	return bRet;
}

bool CVSB_XMLFile::BeginInput(void)
{
	bool bRet = true;

	std::wstring szTag = XVSM_TAG_INPUT;
	bRet = BeginTag(szTag);

	return bRet;
}

bool CVSB_XMLFile::EndInput(void)
{
	bool bRet = true;
	bRet = EndTag();
	return bRet;
}

bool CVSB_XMLFile::BeginGlobal(void)
{
	bool bRet = false;

	std::wstring szTag;

	szTag = XVSM_TAG_GLOBAL;

	bRet = BeginTag(szTag);

	return bRet;
}

bool CVSB_XMLFile::EndGlobal(void)
{
	bool bRet = false;

	bRet = EndTag();

	return bRet;
}

bool CVSB_XMLFile::BeginLocal(void)
{
	bool bRet = false;

	std::wstring szTag;

	szTag = XVSM_TAG_LOCAL;

	bRet = BeginTag(szTag);

	return bRet;
}

bool CVSB_XMLFile::EndLocal(void)
{
	bool bRet = false;

	bRet = EndTag();

	return bRet;
}

bool CVSB_XMLFile::BeginExit(void)
{
	bool bRet = false;

	std::wstring szTag;

	szTag = XVSM_TAG_EXIT;

	bRet = BeginTag(szTag);

	return bRet;
}

bool CVSB_XMLFile::EndExit(void)
{
	bool bRet = false;

	bRet = EndTag();

	return bRet;
}

bool CVSB_XMLFile::WriteVariable(std::wstring& szType, std::wstring& szName, std::wstring& szVal)
{
	bool bRet = false;
	std::wstring szAttr;
	std::wstring szValue;
	std::wstring szTag;

	szTag = XVSM_TAG_VARIABLE;
	bRet = BeginTag(szTag);

	if(bRet)
	{
		CVSB_CPPType2XMLType   cpp2xml;
		szAttr = XVSM_ATTR_TYPE;
		szValue = cpp2xml(szType);
		if(szValue.empty())
			return false;
		AddAttribute(szAttr, szValue);

		szAttr = XVSM_ATTR_NAME;
		szValue = szName;
		AddAttribute(szAttr, szValue);

		szAttr = XVSM_ATTR_DEFVALUE;
		szValue = szVal;
		AddAttribute(szAttr, szValue);
	}

	bRet = EndTag();
	return bRet;
}

bool CVSB_XMLFile::WriteVariable(const wchar_t* szType, const wchar_t* szName, const wchar_t* szVal)
{
	std::wstring szT = szType;
	std::wstring szN = szName;
	std::wstring szV = szVal;

	return WriteVariable(szT, szN, szV);
}

bool CVSB_XMLFile::WriteArrayDeclaration(std::wstring& szElemType, std::wstring& szName, long nSize)
{
	bool bRet = false;
	std::wstring szAttr;
	std::wstring szValue;
	std::wstring szTag;

	szTag = XVSM_TAG_ARRAY;
	bRet = BeginTag(szTag);

	if(bRet)
	{
		szAttr = XVSM_ATTR_NAME;
		szValue = szName;
		AddAttribute(szAttr, szValue);

		CVSB_CPPType2XMLType   cpp2xml;

		szAttr = XVSM_ATTR_ARRAYTYPE;
		szValue = cpp2xml(szElemType);
		if(szValue.empty())
			return false;
		AddAttribute(szAttr, szValue);

		szAttr = XVSM_ATTR_ARRAYSIZE;
		wchar_t szVal[256];
		memset(szVal, 0, 256*sizeof(wchar_t));
		_itow(nSize, szVal, 10);
		szValue = szVal;
		AddAttribute(szAttr, szValue);
	}

	return bRet;
}

bool CVSB_XMLFile::EndArrayDeclaration(void)
{
	bool bRet = true;

	bRet = EndTag();

	return bRet;
}

bool CVSB_XMLFile::WriteArrayElement(std::wstring& szAryName, long nIndx, std::wstring& szVal)
{
	bool bRet = true;
	std::wstring szAttr;
	std::wstring szValue;
	std::wstring szTag;

	szTag = XVSM_TAG_ARRAYELEMENT;
	bRet = BeginTag(szTag);

	if(bRet)
	{
		szAttr = XVSM_ATTR_INDEX;
		wchar_t szIndx[256];
		memset(szIndx, 0, 256*sizeof(wchar_t));
		_itow(nIndx, szIndx, 10);
		szValue = szIndx;
		AddAttribute(szAttr, szValue);

		szAttr = XVSM_ATTR_DEFVALUE;
		szValue = szVal;
		AddAttribute(szAttr, szValue);
	}

	bRet = EndTag();
	return bRet;
}

bool CVSB_XMLFile::WriteArrayElement(const wchar_t* szAryName, long nIndx, const wchar_t* szVal)
{
	std::wstring szN = szAryName;
	std::wstring szV = szVal;

	return WriteArrayElement(szN, nIndx, szV);
}

bool CVSB_XMLFile::WriteArrayElement(std::wstring& szAryName, long nIndx, std::wstring& szDefVal, std::wstring& szVal)
{
	bool bRet = true;
	std::wstring szAttr;
	std::wstring szValue;
	std::wstring szTag;

	szTag = XVSM_TAG_ARRAYELEMENT;
	bRet = BeginTag(szTag);

	if(bRet)
	{
		szAttr = XVSM_ATTR_INDEX;
		wchar_t szIndx[256];
		memset(szIndx, 0, 256*sizeof(wchar_t));
		_itow(nIndx, szIndx, 10);
		szValue = szIndx;
		AddAttribute(szAttr, szValue);

		szAttr = XVSM_ATTR_INITVALUE;
		AddAttribute(szAttr, szDefVal);

		szAttr = XVSM_ATTR_FINALVALUE;
		AddAttribute(szAttr, szVal);
	}

	bRet = EndTag();
	return bRet;
}

bool CVSB_XMLFile::WriteArrayElement(const wchar_t* szAryName, long nIndx, const wchar_t* szDefVal, const wchar_t* szVal)
{
	std::wstring szN = szAryName;
	std::wstring szDV = szDefVal;
	std::wstring szV = szVal;

	return WriteArrayElement(szN, nIndx, szDV, szV);
}

bool CVSB_XMLFile::WriteVariable(std::wstring& szType, std::wstring& szName, std::wstring& szDefVal, std::wstring& szVal)
{
	bool bRet = false;
	std::wstring szAttr;

	std::wstring szTag;

	szTag = XVSM_TAG_VARIABLE;
	bRet = BeginTag(szTag);

	if(bRet)
	{
		szAttr = XVSM_ATTR_TYPE;
		AddAttribute(szAttr, szType);

		szAttr = XVSM_ATTR_NAME;
		AddAttribute(szAttr, szName);

		szAttr = XVSM_ATTR_INITVALUE;
		AddAttribute(szAttr, szDefVal);

		szAttr = XVSM_ATTR_FINALVALUE;
		AddAttribute(szAttr, szVal);
	}

	bRet = EndTag();
	return bRet;
}

bool CVSB_XMLFile::WriteVariable(const wchar_t* szType, const wchar_t* szName, const wchar_t* szDefVal, const wchar_t* szVal)
{
	std::wstring szT = szType;
	std::wstring szN = szName;
	std::wstring szDV = szDefVal;
	std::wstring szV = szVal;

	return WriteVariable(szT, szN, szDV, szV);
}

bool CVSB_XMLFile::WritePlainFunction(std::wstring& szFunc, std::wstring& szReturn)
{
	return WritePlainFunction(szFunc.c_str(), szReturn.c_str());
}

bool CVSB_XMLFile::WritePlainFunction(const wchar_t* szFunc, const wchar_t* szReturn)
{
	bool bRet = true;
	std::wstring strText;

	strText = XVSM_TAG_METHOD;
	BeginTag(strText);
    _writetag();

	strText = XVSM_XML_CDATALEFT;
	strText += L"\n";
	strText += szReturn;
	strText += L" ";
	strText += szFunc;
	strText += XVSM_MACRO_VOIDPARA;

	m_ExportFile << strText.c_str() << std::endl;

	return bRet;
}

bool CVSB_XMLFile::WriteFuncBegin(void)
{
	bool bRet = true;
	
	m_ExportFile << XVSM_MACRO_LB << std::endl;

	return bRet;
}

bool CVSB_XMLFile::WriteFuncEnd(void)
{
	bool bRet = true;
	std::wstring strText;

	strText = XVSM_MACRO_RB;
	strText += XVSM_XML_CDATARIGHT;

	m_ExportFile << strText.c_str() << std::endl;

	EndTag();

	return bRet;
}

bool CVSB_XMLFile::WriteFormula(std::wstring& szFn)
{
	return WriteFormula(szFn.c_str());
}

bool CVSB_XMLFile::WriteFormula(const wchar_t* szFn)
{
	bool bRet = true;

	m_ExportFile << L"\t" << szFn << L";" << std::endl;

	return bRet;
}

bool CVSB_XMLFile::WriteVariableDeclare(std::wstring& szType, std::wstring& szVar)
{
	return WriteVariableDeclare(szType.c_str(), szVar.c_str());
}

bool CVSB_XMLFile::WriteVariableDeclare(const wchar_t* szType, const wchar_t* szVar)
{
	bool bRet = true;
	CVSB_CPPType2XMLType   cpp2xml;
	std::wstring szTemp = szType;
	std::wstring szXMLType = cpp2xml(szTemp);

	m_ExportFile << L"\t" << szXMLType.c_str() << L"  " << szVar << L";" << std::endl;
	return bRet;
}

bool CVSB_XMLFile::WriteIFstatement(std::wstring& szCndit)
{
	bool bRet = true;

	m_ExportFile << L"\t" << L"if (" << szCndit << L")" << std::endl;

	return bRet;
}

bool CVSB_XMLFile::WriteIFstatement(const wchar_t* szCndit)
{
	bool bRet = true;

	return bRet;
}

bool CVSB_XMLFile::WriteELSEstatement(void)
{
	bool bRet = true;

	m_ExportFile << L"\t" << L"else" << std::endl;

	return bRet;
}

bool CVSB_XMLFile::WriteInnerLB(void)
{
	bool bRet = true;

	m_ExportFile << L"\t{\n\t";

	return bRet;
}

bool CVSB_XMLFile::WriteInnerRB(void)
{
	bool bRet = true;

	m_ExportFile << L"\t}" << std::endl;

	return bRet;
}

bool CVSB_XMLFile::WriteNextLine(void)
{
	bool bRet = true;

	m_ExportFile << L"\n" << std::endl;

	return bRet;
}

bool CVSB_XMLFile::WriteCounterReturn(bool bIsXML)
{
	bool bRet = true;

	if(bIsXML)
		return bRet;

	m_ExportFile << XVSM_MACRO_RETURNCUNTER << std::endl;

	return bRet;
}

bool CVSB_XMLFile::WriteSetCounter(long nID, bool bIsXML)
{
	bool bRet = true;
	
	if(bIsXML == false)
	{
		// Write 
		wchar_t szID[256];
		memset(szID, 0, 256*sizeof(wchar_t));
		_itow(nID, szID, 10);

		m_ExportFile << L"\t" << XVSM_MACRO_SETCOUNTER << szID << L";"<< std::endl;
	}
	else
	{
		//WriteGoLink(nID);
		return true;
	}

	return bRet;
}

bool CVSB_XMLFile::WritePlainString(std::wstring& szStr)
{
	_wirtestring(szStr);
	return true;
}

bool CVSB_XMLFile::WritePlainString(const wchar_t* szStr)
{
	std::wstring szS = szStr;
	return WritePlainString(szS);
}

bool CVSB_XMLFile::WriteComeLink(long nID)
{
	bool bRet = true;
	std::wstring szAttr;
	std::wstring szValue;
	std::wstring szTag;

	szTag = XVSM_TAG_COME;
	bRet = BeginTag(szTag);

	if(bRet)
	{
		szAttr = XVSM_ATTR_ID;
		wchar_t szVal[256];
		memset(szVal, 0, 256*sizeof(wchar_t));
		_itow(nID, szVal, 10);
		szValue = szVal;
		AddAttribute(szAttr, szValue);

	}

	bRet = EndTag();
	return bRet;
}

bool CVSB_XMLFile::WriteGoLink(long nID)
{
	bool bRet = true;
	std::wstring szAttr;
	std::wstring szValue;
	std::wstring szTag;

	szTag = XVSM_TAG_GO;
	bRet = BeginTag(szTag);

	if(bRet)
	{
		szAttr = XVSM_ATTR_ID;
		wchar_t szVal[256];
		memset(szVal, 0, 256*sizeof(wchar_t));
		_itow(nID, szVal, 10);
		szValue = szVal;
		AddAttribute(szAttr, szValue);

	}

	bRet = EndTag();
	return bRet;
}

bool CVSB_XMLFile::WriteYesLink(long nID)
{
	bool bRet = true;
	std::wstring szAttr;
	std::wstring szValue;
	std::wstring szTag;

	szTag = XVSM_TAG_YESGO;
	bRet = BeginTag(szTag);

	if(bRet)
	{
		szAttr = XVSM_ATTR_ID;
		wchar_t szVal[256];
		memset(szVal, 0, 256*sizeof(wchar_t));
		_itow(nID, szVal, 10);
		szValue = szVal;
		AddAttribute(szAttr, szValue);

	}

	bRet = EndTag();
	return bRet;
}

bool CVSB_XMLFile::WriteNoLink(long nID)
{
	bool bRet = true;
	std::wstring szAttr;
	std::wstring szValue;
	std::wstring szTag;

	szTag = XVSM_TAG_NOTGO;
	bRet = BeginTag(szTag);

	if(bRet)
	{
		szAttr = XVSM_ATTR_ID;
		wchar_t szVal[256];
		memset(szVal, 0, 256*sizeof(wchar_t));
		_itow(nID, szVal, 10);
		szValue = szVal;
		AddAttribute(szAttr, szValue);

	}

	bRet = EndTag();
	return bRet;
}

bool CVSB_XMLFile::WriteXYAttributs(long nX, long nY)
{
	std::wstring szAttr;
	std::wstring szValue;
	wchar_t	szTemp[256];
	memset(szTemp, 0, 256*sizeof(wchar_t));
	_itow(nX, szTemp, 10);
	szAttr = XVSM_ATTR_X;
	szValue = szTemp;
	AddAttribute(szAttr, szValue);

	memset(szTemp, 0, 256*sizeof(wchar_t));
	_itow(nY, szTemp, 10);
	szAttr = XVSM_ATTR_Y;
	szValue = szTemp;
	AddAttribute(szAttr, szValue);

	return true;
}

bool CVSB_XMLFile::BeginTag(const std::wstring& tag)
{
	bool bRet = false;

    _writetag();

#ifdef _XSVM_DEBUG_
	assert(!tag.empty());
#endif
	if(tag.empty())
		return bRet;

#ifdef _XSVM_DEBUG_
	assert(tag.find(L' ') == tag.npos);
#endif
	if(tag.find(L' ') != tag.npos)
		return bRet;

    m_TagStack.push(tag);
    m_bTagWritten = false;
	bRet = true;

	return bRet;
}

bool CVSB_XMLFile::EndTag(void)
{
	bool bRet = false;

#ifdef _XSVM_DEBUG_
	assert(!m_TagStack.empty());
#endif

	if(m_TagStack.empty())
		return bRet;

    std::wstring tag;
    std::wstring str;
    
	tag = m_TagStack.top();
    m_TagStack.pop();    

    if(!m_bTagWritten)
    {	
		_makexmltag(str, tag, true);
    }
    else
    {
		str = L"</";
		str += tag;
		str += L">";
    }
	_wirtestring(str);
    
    m_bTagWritten = true;
	bRet = true;
	return bRet;
}

void CVSB_XMLFile::AddAttribute(const std::wstring& strName, const std::wstring& strValue)
{
	m_AttrQ.push_back(std::make_pair(strName, strValue));
}

void CVSB_XMLFile::AddText(const std::wstring& strOutText)
{
    std::wstring strText = strOutText;

    _writetag();
    _encoding(strText);
    _wirtestring(strText);
}

void CVSB_XMLFile::AddCDATA(const std::wstring& strCDATA)
{
    std::wstring strText;
	strText = XVSM_XML_CDATALEFT;
	strText += strCDATA;
	strText += XVSM_XML_CDATARIGHT;

    _writetag();
    _wirtestring(strText);
}

void CVSB_XMLFile::AddComment(const std::wstring& strComment)
{
    std::wstring strText;
	strText = XVSM_XML_COMMENTLEFT;
	strText += strComment;
	strText += XVSM_XML_COMMENTRIGHT;
    _writetag();
    _wirtestring(strText);
}

//consume
void CVSB_XMLFile::_wirtestring(const std::wstring& str)
{
    m_ExportFile << str.c_str();
}

void CVSB_XMLFile::_encoding(std::wstring& out)
{
	const std::wstring		signs(L"\'\"&<>");
    std::wstring			szNew;
	wchar_t					szchar;
	_ex_signmap::iterator	iter;
    
	int signpos = (int)out.find_first_of(signs);

    while(signpos != out.npos)
    {
		szchar = out[signpos];
		iter = m_signLUT.find(szchar);
		if(iter != m_signLUT.end())
		{
			szNew = iter->second;
			out.replace(signpos, 1, szNew);
			signpos += (int)szNew.size();
		}	

		signpos = (int)out.find_first_of(signs, signpos);
    }
}

void CVSB_XMLFile::_makexmltag(std::wstring& output, const std::wstring& tag, bool empty) //construct
{
    _ex_attrqueue::iterator iter;
	std::wstring			szVal;
	std::wstring			szAttr;
    
    output = L"<";
	output += tag;

    for(iter = m_AttrQ.begin(); iter != m_AttrQ.end(); ++iter)
    {
		szAttr = iter->first;
		szVal = iter->second;
	
		output += L" ";
		output += szAttr;	
		output += L" = \"";

		_encoding(szVal);
		output += szVal;
		
		output += L"\"";
    }
    
    output += (empty ? L"/>\n" : L">\n");

	m_AttrQ.clear();
}

void CVSB_XMLFile::_writetag(void)  //flush
{
    if(!m_TagStack.empty() && !m_bTagWritten)
    {
		std::wstring tag = m_TagStack.top();
		std::wstring str;
		_makexmltag(str, tag);
		_wirtestring(str);
    }
	else
	{
		m_AttrQ.clear();
	}

    m_bTagWritten = true;
}

void CVSB_XMLFile::_createsignlut(void)
{
	m_signLUT.clear();

	m_signLUT.insert(std::make_pair(L'\'', L"&apos;"));
	m_signLUT.insert(std::make_pair(L'\"', L"&quot;"));
	m_signLUT.insert(std::make_pair(L'&', L"&amp;"));
	m_signLUT.insert(std::make_pair(L'<', L"&lt;"));
	m_signLUT.insert(std::make_pair(L'>', L"&gt;"));
}