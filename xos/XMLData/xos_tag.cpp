#include <algorithm>
#include "xos_tag.h"

template <class Type> class Deletor
{
public:
    void operator () (Type* elem)
    {
		if(elem)
			delete elem;
    }
};

CXOS_XMLTag::CXOS_XMLTag(void)
	: m_sTag()
{
    m_AttribList.clear();
	m_TextList.clear();
}	

CXOS_XMLTag::CXOS_XMLTag(const std::wstring& sTag)
{
	m_sTag.assign(sTag); 
    m_AttribList.clear();
	m_TextList.clear();
}

CXOS_XMLTag::CXOS_XMLTag(const wchar_t* sTag)
{
	m_sTag.assign(sTag);
    m_AttribList.clear();
	m_TextList.clear();
}

CXOS_XMLTag::~CXOS_XMLTag(void)
{
#if _MSC_VER >= 1300 
	m_sTag.clear();
#else
	if(!m_sTag.empty())
		m_sTag.erase(m_sTag.begin(), m_sTag.end());
#endif
    ClearAttributeList();
	ClearTextList();
}

CXOS_Attribute* CXOS_XMLTag::GetAttribute(unsigned int index)
{
	if(index < m_AttribList.size())
	{
		return m_AttribList.at(index);
	}
	else
	{
		return NULL;
	}
}

CXOS_TagTextData* CXOS_XMLTag::GetTextData(unsigned int index)
{
	if(index < m_TextList.size())
	{
		return m_TextList.at(index);
	}
	else
	{
		return NULL;
	}
}
    
void CXOS_XMLTag::ClearAttributeList(void)
{
	if(!m_AttribList.empty())
	{
		for_each(m_AttribList.begin(), m_AttribList.end(), Deletor<CXOS_Attribute>());
		m_AttribList.clear();
	}
}

void CXOS_XMLTag::ClearTextList(void)
{
	if(!m_TextList.empty())
	{
		for_each(m_TextList.begin(), m_TextList.end(), Deletor<CXOS_TagTextData>());
		m_TextList.clear();
	}
}


CXOS_XMLTagNode::CXOS_XMLTagNode(void)
	:m_pUpperTag(NULL), m_pTag(NULL), m_sXMLHeader()
{
	m_ChildTags.clear();
    m_AttribList.clear();
}

CXOS_XMLTagNode::CXOS_XMLTagNode(CXOS_XMLTag* pTag, CXOS_XMLTagNode* pUpperTagNode)
	:m_pTag(pTag), m_sXMLHeader()
{
	m_pUpperTag = pUpperTagNode;
	m_ChildTags.clear();
    m_AttribList.clear();
}

CXOS_XMLTagNode::~CXOS_XMLTagNode(void)
{
	ClearChildTagNodes();

	m_pUpperTag = NULL;
	if(m_pTag)
	{
		delete m_pTag;
		m_pTag = NULL;
	}

	ClearAttributeList();
}

void CXOS_XMLTagNode::ClearChildTagNodes(void)
{
	if(!m_ChildTags.empty())
	{
		for_each(m_ChildTags.begin(), m_ChildTags.end(), Deletor<CXOS_XMLTagNode>());
		m_ChildTags.clear();
	}
}

void CXOS_XMLTagNode::ClearAttributeList(void)
{
	if(!m_AttribList.empty())
	{
		for_each(m_AttribList.begin(), m_AttribList.end(), Deletor<CXOS_Attribute>());
		m_AttribList.clear();
	}
}

CXOS_Attribute* CXOS_XMLTagNode::GetAttribute(unsigned int index)
{
	if(index < m_AttribList.size())
	{
		return m_AttribList.at(index);
	}
	else
	{
		return NULL;
	}
}

bool CXOS_XMLTagNode::FindTag(const wchar_t* sText, CXOS_XMLTagNode** pTag)
{
	bool bRet = false;

	if(m_pTag && pTag)
	{
		if(wcscmp(_wcslwr(_wcsdup(m_pTag->GetTag().c_str())), _wcslwr(_wcsdup(sText))) == 0)
		{
			*pTag = this;
			bRet = true;
			return bRet;
		}
	}

	CTagIterator	iter;
	for(iter = m_ChildTags.begin(); iter != m_ChildTags.end(); ++iter)
	{
		bRet = (*iter)->FindTag(sText, pTag);
		if(bRet == true)
			return bRet;
	}

	return bRet;
}

unsigned int CXOS_XMLTagNode::nIdnt = 0;

class AttributePrint
{
public:
    void operator()(CXOS_Attribute* pAttrib)
    {
		if(pAttrib)
		{
			std::wstring sAttrib, sValue;
			pAttrib->QueryAttribute(sAttrib);
			pAttrib->QueryString(sValue);
			wprintf(L" %s=", sAttrib.c_str());
			wprintf(L"\"%s\"", sValue.c_str());
		}
    }
};

class TextDataPrint
{
public:
    void operator()(CXOS_TagTextData* pText)
    {
		if(pText)
		{
			std::wstring     sText;
			XOS_TEXTTYPE tType;
			pText->QueryTypeAndText(tType, sText);
			
			switch(tType)
			{
				case enXOS_XML_COMMENT:
					 PrintComment(sText);
					 break;
				case enXOS_XML_TEXT:
					 PrintText(sText);
					 break;
				case enXOS_XML_CDATA:
					 PrintCDATA(sText); 
					 break;	
			}
		}
    }
private:
	void PrintComment(const std::wstring& sText)
	{
		wprintf(L"<!--%s-->", sText.c_str());
	}

	void PrintText(const std::wstring& sText)
	{
		if(1 < sText.size() ||
		  (1 == sText.size() && !iswspace(sText[0])))
		{
			wprintf(L"%s", sText.c_str());	
		}
	}

	void PrintCDATA(const std::wstring& sText)
	{
		wprintf(L"<![CDATA[%s]]>", sText.c_str());
	}

};

class TagPrint
{
public:
    void operator()(CXOS_XMLTagNode* pTag)
    {
		if(pTag)
		{
			pTag->PrintTagNode();
		}
    }
};

void CXOS_XMLTagNode::PrintTagNode(void)
{
	if(!m_sXMLHeader.empty() && !m_AttribList.empty())
	{
		wprintf(L"<?%s ", m_sXMLHeader.c_str());
		for_each(m_AttribList.begin(), m_AttribList.end(), AttributePrint());
		wprintf(L"?>");
	}

	if(!m_pTag)
	{
		if(!m_ChildTags.empty())
		{
			for_each(m_ChildTags.begin(), m_ChildTags.end(), TagPrint());
		}
		return;

	}

	if(!m_pTag->m_sTag.empty())
	{
		wprintf(L"\n%*s",3 * ++CXOS_XMLTagNode::nIdnt,L"");
		wprintf(L"<%s", m_pTag->m_sTag.c_str());
	}
   
	if(!m_pTag->m_AttribList.empty())
	{
		for_each(m_pTag->m_AttribList.begin(), m_pTag->m_AttribList.end(), AttributePrint());
	}
	if(!m_pTag->m_sTag.empty())
		wprintf(L">");
    
	if(!m_pTag->m_TextList.empty())
	{
		for_each(m_pTag->m_TextList.begin(), m_pTag->m_TextList.end(), TextDataPrint());
	}
   
	if(!m_ChildTags.empty())
	{
		for_each(m_ChildTags.begin(), m_ChildTags.end(), TagPrint());
	}

	if(!m_pTag->m_sTag.empty())
	{
		wprintf(L"\n%*s",3 * CXOS_XMLTagNode::nIdnt--, L"");
		wprintf(L"</%s>",m_pTag->m_sTag.c_str());
	}

	return;
}

CXOS_hXML CXOS_CreateXMLTree(void)
{
	CXOS_XMLTagNode* pXML = new CXOS_XMLTagNode();
	return pXML;
}

bool CXOS_DeleteXMLTree(CXOS_hXML& hXML)
{
	bool bRet = false;
	if(hXML)
	{
		delete ((CXOS_XMLTagNode*)hXML);
		hXML = NULL;
		bRet = true;
	}
	return bRet; 
}


