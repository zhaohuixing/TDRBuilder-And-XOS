// Orignated from the code written in July 2003
#pragma warning(disable:4530)
#pragma warning(disable:4786)
#ifndef __XXML_ATTRIBUTE_H__
#define __XXML_ATTRIBUTE_H__

#include <string>
#include <vector>
#include <map>
#include "xxml_xmldatadef.h"
#include "tvsb_cpputil.h"

class CXML_Attribute  
{
public:
	CXML_Attribute();
	CXML_Attribute(const CXML_Attribute& src);
	CXML_Attribute(const std::wstring& wAttrib, XVSB_XMLNUMERICDATA numData, XVSB_XMLATTRIBUTETYPE enType);
	CXML_Attribute(const std::wstring& wAttrib, const std::wstring& wString);
	CXML_Attribute(const wchar_t* wAttrib, const wchar_t* wString);
	virtual ~CXML_Attribute();

// Assign attribute member data 
public:
	CXML_Attribute& operator = (const CXML_Attribute& src);

public:
	inline void SetAttribute(const std::wstring& wAttrib){m_Attribute.assign(wAttrib);};
	
	inline void SetNumeric(XVSB_XMLNUMERICDATA numData, XVSB_XMLATTRIBUTETYPE enType)
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
		m_Type = enXVSB_XML_STRING;
		m_String.assign(wString);
	}

// Query attribute member data
public:
    inline XVSB_XMLATTRIBUTETYPE GetDataType(void){return m_Type;};
	inline void QueryAttribute(std::wstring& sAttribute){sAttribute.assign(m_Attribute);};

public:
	bool QueryNumeric(XVSB_XMLNUMERICDATA& numData, XVSB_XMLATTRIBUTETYPE& enType);
    bool QueryString(std::wstring& wString);
	std::wstring GetAttribute(void){return m_Attribute;}
	std::wstring GetValue(void){return m_String;}

private:
    std::wstring			m_Attribute;

private:
	XVSB_XMLATTRIBUTETYPE	m_Type;
	XVSB_XMLNUMERICDATA		m_Numeric;
	std::wstring			m_String;

};

//typedef std::vector<CXML_Attribute*> CXML_AttributeList;
typedef std::map<std::wstring, CXML_Attribute*>					CXML_AttributeTable;
typedef TVSB_PairDeletor<CXML_AttributeTable::value_type>		CXML_AttrMapDelete;
typedef TVSB_Dealloc<CXML_AttributeTable, CXML_AttrMapDelete>	CXML_AttrMapRelease;


#endif // __XOS_ATTRIBUTE_H__
