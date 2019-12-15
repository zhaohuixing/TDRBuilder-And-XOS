// Orignated from the code written in July 2003
#include "xxml_tagtdata.h"

//using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CXML_TagTextData::CXML_TagTextData()
	: m_strText(), m_textType(enXVSB_XML_COMMENT)
{
}

CXML_TagTextData::CXML_TagTextData(const std::wstring& wText, XVSB_TEXTTYPE tType)
	: m_strText(wText), m_textType(tType)
{
}

CXML_TagTextData::CXML_TagTextData(const wchar_t* szText, XVSB_TEXTTYPE tType)
	: m_strText(szText), m_textType(tType)
{
}

CXML_TagTextData::~CXML_TagTextData()
{
#if _MSC_VER >= 1300 
	m_strText.clear();
#else
	if(!m_strText.empty())
		m_strText.erase(m_strText.begin(), m_strText.end());
#endif
}

void CXML_TagTextData::SetTextData(const std::wstring& wText, XVSB_TEXTTYPE tType)
{
	m_textType = tType;

	if(tType == enXVSB_XML_TEXT) // If is text type, append the string
	{
		m_strText.append(wText);
	}
	else
	{
		m_strText.assign(wText);
	}
}

void CXML_TagTextData::SetTextData(const wchar_t* szText, XVSB_TEXTTYPE tType)
{
	m_textType = tType;

	if(tType == enXVSB_XML_TEXT) // If is text type, append the string
	{
		m_strText.append(szText);
	}
	else
	{
		m_strText.assign(szText);
	}
}
