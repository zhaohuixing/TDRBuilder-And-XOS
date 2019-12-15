#include "xos_tagtdata.h"

//using namespace std;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CXOS_TagTextData::CXOS_TagTextData()
	: m_strText(), m_textType(enXOS_XML_COMMENT)
{
}

CXOS_TagTextData::CXOS_TagTextData(const std::wstring& wText, XOS_TEXTTYPE tType)
	: m_strText(wText), m_textType(tType)
{
}

CXOS_TagTextData::CXOS_TagTextData(const wchar_t* szText, XOS_TEXTTYPE tType)
	: m_strText(szText), m_textType(tType)
{
}

CXOS_TagTextData::~CXOS_TagTextData()
{
#if _MSC_VER >= 1300 
	m_strText.clear();
#else
	if(!m_strText.empty())
		m_strText.erase(m_strText.begin(), m_strText.end());
#endif
}

void CXOS_TagTextData::SetTextData(const std::wstring& wText, XOS_TEXTTYPE tType)
{
	m_textType = tType;

	if(tType == enXOS_XML_TEXT) // If is text type, append the string
	{
		m_strText.append(wText);
	}
	else
	{
		m_strText.assign(wText);
	}
}

void CXOS_TagTextData::SetTextData(const wchar_t* szText, XOS_TEXTTYPE tType)
{
	m_textType = tType;

	if(tType == enXOS_XML_TEXT) // If is text type, append the string
	{
		m_strText.append(szText);
	}
	else
	{
		m_strText.assign(szText);
	}
}
