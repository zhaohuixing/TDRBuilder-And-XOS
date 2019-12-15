#include "xos_attribute.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//using namespace std;

CXOS_Attribute::CXOS_Attribute()
{
	m_Type = enXOS_XML_BOOL;
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


CXOS_Attribute::CXOS_Attribute(const CXOS_Attribute& src)
{
	m_Attribute.assign(src.m_Attribute);
	m_Type = src.m_Type;
	if(m_Type != enXOS_XML_STRING)
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

CXOS_Attribute::CXOS_Attribute(const std::wstring& wAttrib, 
							 XOS_XMLNUMERICDATA numData, 
							 XOS_XMLATTRIBUTETYPE enType)
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

CXOS_Attribute::CXOS_Attribute(const std::wstring& wAttrib, const std::wstring& wString)
{
    m_Type = enXOS_XML_STRING;
	m_Attribute.assign(wAttrib);
	m_String.assign(wString);
}

CXOS_Attribute::CXOS_Attribute(const wchar_t* wAttrib, const wchar_t* wString)
{
    m_Type = enXOS_XML_STRING;
	m_Attribute.assign(wAttrib);
	m_String.assign(wString);
}

CXOS_Attribute::~CXOS_Attribute()
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

CXOS_Attribute& CXOS_Attribute::operator = (const CXOS_Attribute& src)
{
	m_Attribute.assign(src.m_Attribute);
	m_Type = src.m_Type;
	if(m_Type != enXOS_XML_STRING)
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

bool CXOS_Attribute::QueryNumeric(XOS_XMLNUMERICDATA& numData, XOS_XMLATTRIBUTETYPE& enType)
{
	if(m_Type == enXOS_XML_STRING)
		return false;

	numData = m_Numeric;
	enType = m_Type;

	return true;
}

bool CXOS_Attribute::QueryString(std::wstring& wString)
{
	if(m_Type != enXOS_XML_STRING)
		return false;

	wString.assign(m_String);

	return true;
}


