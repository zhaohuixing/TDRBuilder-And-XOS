#ifndef __XOS_TAGTDATA_H__
#define __XOS_TAGTDATA_H__

#include <string>
#include <vector>
#include "xos_xmldatadef.h"

#pragma warning(disable:4786)

class CXOS_TagTextData  
{
public:
	CXOS_TagTextData();
	CXOS_TagTextData(const std::wstring& wText, XOS_TEXTTYPE tType);
	CXOS_TagTextData(const wchar_t* szText, XOS_TEXTTYPE tType);
	virtual ~CXOS_TagTextData();

public:
	void SetTextData(const std::wstring& wText, XOS_TEXTTYPE tType);
	void SetTextData(const wchar_t* szText, XOS_TEXTTYPE tType);


    inline XOS_TEXTTYPE GetNodeType(void) const {return m_textType;};
	inline const wchar_t* GetNodeText(void) const {return m_strText.c_str();};
	inline void QueryText(std::wstring& sText){sText.assign(m_strText);};
	inline void QueryTypeAndText(XOS_TEXTTYPE& tType, std::wstring& sText)
	{
		tType = m_textType;
		sText.assign(m_strText);
	}

protected:
	std::wstring   m_strText;
	XOS_TEXTTYPE    m_textType;
};

typedef std::vector<CXOS_TagTextData*> CXOS_TagTextDataList;


#endif // __XOS_TAGTDATA_H__
