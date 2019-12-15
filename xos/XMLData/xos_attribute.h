#ifndef __XOS_ATTRIBUTE_H__
#define __XOS_ATTRIBUTE_H__

#include <string>
#include <vector>
#include "xos_xmldatadef.h"

#pragma warning(disable:4786)

class CXOS_Attribute  
{
public:
	CXOS_Attribute();
	CXOS_Attribute(const CXOS_Attribute& src);
	CXOS_Attribute(const std::wstring& wAttrib, XOS_XMLNUMERICDATA numData, XOS_XMLATTRIBUTETYPE enType);
	CXOS_Attribute(const std::wstring& wAttrib, const std::wstring& wString);
	CXOS_Attribute(const wchar_t* wAttrib, const wchar_t* wString);
	virtual ~CXOS_Attribute();

// Assign attribute member data 
public:
	CXOS_Attribute& operator = (const CXOS_Attribute& src);

public:
	inline void SetAttribute(const std::wstring& wAttrib){m_Attribute.assign(wAttrib);};
	
	inline void SetNumeric(XOS_XMLNUMERICDATA numData, XOS_XMLATTRIBUTETYPE enType)
	{
		m_Type = enType;
		m_Numeric = numData;
#if _MSC_VER >= 1300 
#pragma message("VisuaStudio.NET support basic_string::clear")
		m_String.clear();
#else
#pragma message("Old version of VC++ don't support basic_string::clear")
		if(!m_String.empty())
			m_String.erase(m_String.begin(), m_String.end());
#endif
	}

	inline void SetString(const std::wstring& wString)
	{
		m_Type = enXOS_XML_STRING;
		m_String.assign(wString);
	}

// Query attribute member data
public:
    inline XOS_XMLATTRIBUTETYPE GetNodeType(void){return m_Type;};
	inline void QueryAttribute(std::wstring& sAttribute){sAttribute.assign(m_Attribute);};

public:
	bool QueryNumeric(XOS_XMLNUMERICDATA& numData, XOS_XMLATTRIBUTETYPE& enType);
    bool QueryString(std::wstring& wString);
	std::wstring GetAttribute(void){return m_Attribute;}
	std::wstring GetValue(void){return m_String;}

private:
    std::wstring        m_Attribute;

private:
	XOS_XMLATTRIBUTETYPE m_Type;
	XOS_XMLNUMERICDATA   m_Numeric;
	std::wstring        m_String;

};

typedef std::vector<CXOS_Attribute*> CXOS_AttributeList;

#endif // __XOS_ATTRIBUTE_H__
