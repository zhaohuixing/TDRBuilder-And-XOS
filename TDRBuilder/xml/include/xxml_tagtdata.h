// Orignated from the code written in July 2003
#pragma warning(disable:4530)
#ifndef __XXML_TAGTDATA_H__
#define __XXML_TAGTDATA_H__

#include <string>
#include <vector>
#include "xxml_xmldatadef.h"

#pragma warning(disable:4786)

class CXML_TagTextData  
{
public:
	CXML_TagTextData();
	CXML_TagTextData(const std::wstring& wText, XVSB_TEXTTYPE tType);
	CXML_TagTextData(const wchar_t* szText, XVSB_TEXTTYPE tType);
	virtual ~CXML_TagTextData();

public:
	void SetTextData(const std::wstring& wText, XVSB_TEXTTYPE tType);
	void SetTextData(const wchar_t* szText, XVSB_TEXTTYPE tType);


    inline XVSB_TEXTTYPE GetDataType(void) const {return m_textType;};
	inline const wchar_t* GetDataText(void) const {return m_strText.c_str();};
	inline void QueryText(std::wstring& sText){sText.assign(m_strText);};
	inline void QueryTypeAndText(XVSB_TEXTTYPE& tType, std::wstring& sText)
	{
		tType = m_textType;
		sText.assign(m_strText);
	}

protected:
	std::wstring		m_strText;
	XVSB_TEXTTYPE		m_textType;
};

typedef std::vector<CXML_TagTextData*> CXML_TagTextDataList;


#endif // __XVSB_TAGTDATA_H__
