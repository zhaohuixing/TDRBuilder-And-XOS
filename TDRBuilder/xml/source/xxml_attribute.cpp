// Orignated from the code written in July 2003
#include "xxml_attribute.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//using namespace std;

CXML_Attribute::CXML_Attribute()
{
	m_Type = enXVSB_XML_BOOL;
	m_Numeric.m_Bool = false;
#if _MSC_VER >= 1300 
#pragma message("VisuaStudio.NET support basic_string::clear")
	m_String.clear();
	m_Attribute.clear();
#else
#pragma message("Old version of VC++ don't support basic_string::clear")
		if(!m_String.empty())
			m_String.erase(m_String.begin(), m_String.end());
		if(!m_Attribute.empty())
			m_Attribute.erase(m_Attribute.begin(), m_Attribute.end());
#endif
}


CXML_Attribute::CXML_Attribute(const CXML_Attribute& src)
{
	m_Attribute.assign(src.m_Attribute);
	m_Type = src.m_Type;
	if(m_Type != enXVSB_XML_STRING)
	{
		m_Numeric = src.m_Numeric;
#if _MSC_VER >= 1300 
#pragma message("VisuaStudio.NET support basic_string::clear")
		m_String.clear();	
#else
#pragma message("Old version of VC++ don't support basic_string::clear")
		if(!m_String.empty())
			m_String.erase(m_String.begin(), m_String.end());
#endif
	}
    else
	{
		m_String.assign(src.m_String);
	}
}

CXML_Attribute::CXML_Attribute(const std::wstring& wAttrib, 
							 XVSB_XMLNUMERICDATA numData, 
							 XVSB_XMLATTRIBUTETYPE enType)
	: m_Numeric(numData), m_Type(enType)
{
	m_Attribute.assign(wAttrib);
#if _MSC_VER >= 1300 
#pragma message("VisuaStudio.NET support basic_string::clear")
	m_String.clear();
#else
#pragma message("Old version of VC++ don't support basic_string::clear")
		if(!m_String.empty())
			m_String.erase(m_String.begin(), m_String.end());
#endif
}

CXML_Attribute::CXML_Attribute(const std::wstring& wAttrib, const std::wstring& wString)
{
    m_Type = enXVSB_XML_STRING;
	m_Attribute.assign(wAttrib);
	m_String.assign(wString);
}

CXML_Attribute::CXML_Attribute(const wchar_t* wAttrib, const wchar_t* wString)
{
    m_Type = enXVSB_XML_STRING;
	m_Attribute.assign(wAttrib);
	m_String.assign(wString);
}

CXML_Attribute::~CXML_Attribute()
{
#if _MSC_VER >= 1300 
#pragma message("VisuaStudio.NET support basic_string::clear")
	m_String.clear();
	m_Attribute.clear();
#else
#pragma message("Old version of VC++ don't support basic_string::clear")
		if(!m_String.empty())
			m_String.erase(m_String.begin(), m_String.end());
		if(!m_Attribute.empty())
			m_Attribute.erase(m_Attribute.begin(), m_Attribute.end());
#endif
}

CXML_Attribute& CXML_Attribute::operator = (const CXML_Attribute& src)
{
	m_Attribute.assign(src.m_Attribute);
	m_Type = src.m_Type;
	if(m_Type != enXVSB_XML_STRING)
	{
		m_Numeric = src.m_Numeric;
#if _MSC_VER >= 1300 
#pragma message("VisuaStudio.NET support basic_string::clear")
		m_String.clear();	
#else
#pragma message("Old version of VC++ don't support basic_string::clear")
		if(!m_String.empty())
			m_String.erase(m_String.begin(), m_String.end());
#endif
	}
    else
	{
		m_String.assign(src.m_String);
	}

	return *this;
}

bool CXML_Attribute::QueryNumeric(XVSB_XMLNUMERICDATA& numData, XVSB_XMLATTRIBUTETYPE& enType)
{
	if(m_Type == enXVSB_XML_STRING)
		return false;

	numData = m_Numeric;
	enType = m_Type;

	return true;
}

bool CXML_Attribute::QueryString(std::wstring& wString)
{
	if(m_Type != enXVSB_XML_STRING)
		return false;

	wString.assign(m_String);

	return true;
}


