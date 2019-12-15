// Orignated from the code written in July 2003
#pragma warning(disable:4530)

#include <algorithm>
#include <wchar.h>
#include "xxml_tag.h"

template <class Type> class Deletor
{
public:
    void operator () (Type* elem)
    {
		if(elem)
			delete elem;
    }
};

CXML_XMLTag::CXML_XMLTag(void)
	: m_sTag()
{
    m_AttribList.clear();
	m_TextList.clear();
}	

CXML_XMLTag::CXML_XMLTag(const std::wstring& sTag)
{
	m_sTag.assign(sTag); 
    m_AttribList.clear();
	m_TextList.clear();
}

CXML_XMLTag::CXML_XMLTag(const wchar_t* sTag)
{
	m_sTag.assign(sTag);
    m_AttribList.clear();
	m_TextList.clear();
}

CXML_XMLTag::~CXML_XMLTag(void)
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

CXML_Attribute* CXML_XMLTag::GetAttribute(unsigned int index)
{
	if(index < (unsigned int)m_AttribList.size())
	{
		CXML_AttributeTable::iterator iter = m_AttribList.begin();
		for(unsigned int i = 0; i < index; i++)
			++iter;
		return iter->second;
	}
	else
	{
		return NULL;
	}
}

CXML_Attribute* CXML_XMLTag::GetAttribute(const std::wstring& szAttr)
{
	CXML_AttributeTable::iterator iter;
	iter = m_AttribList.find(szAttr);
	if(iter != m_AttribList.end())
	{
		return iter->second;
	}
	else
	{
		return NULL;
	}
}

CXML_Attribute* CXML_XMLTag::GetAttribute(const wchar_t* szAttr)
{
	CXML_AttributeTable::iterator iter;
	iter = m_AttribList.find(szAttr);
	if(iter != m_AttribList.end())
	{
		return iter->second;
	}
	else
	{
		return NULL;
	}
}

CXML_TagTextData* CXML_XMLTag::GetTextData(unsigned int index)
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
    
void CXML_XMLTag::ClearAttributeList(void)
{
	if(!m_AttribList.empty())
	{
		//for_each(m_AttribList.begin(), m_AttribList.end(), Deletor<CXML_Attribute>());
		//m_AttribList.clear();
		CXML_AttrMapRelease		amfree;
		amfree(m_AttribList);
	}
}

void CXML_XMLTag::ClearTextList(void)
{
	if(!m_TextList.empty())
	{
		for_each(m_TextList.begin(), m_TextList.end(), Deletor<CXML_TagTextData>());
		m_TextList.clear();
	}
}


CXML_XMLTagNode::CXML_XMLTagNode(void)
	:m_pUpperTag(NULL), m_pTag(NULL), m_sXMLHeader()
{
	m_ChildTags.clear();
    m_AttribList.clear();
}

CXML_XMLTagNode::CXML_XMLTagNode(CXML_XMLTag* pTag, CXML_XMLTagNode* pUpperTagNode)
	:m_pTag(pTag), m_sXMLHeader()
{
	m_pUpperTag = pUpperTagNode;
	m_ChildTags.clear();
    m_AttribList.clear();
}

CXML_XMLTagNode::~CXML_XMLTagNode(void)
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

void CXML_XMLTagNode::ClearChildTagNodes(void)
{
	if(!m_ChildTags.empty())
	{
		for_each(m_ChildTags.begin(), m_ChildTags.end(), Deletor<CXML_XMLTagNode>());
		m_ChildTags.clear();
	}
}

void CXML_XMLTagNode::ClearAttributeList(void)
{
	if(!m_AttribList.empty())
	{
		//for_each(m_AttribList.begin(), m_AttribList.end(), Deletor<CXML_Attribute>());
		//m_AttribList.clear();
		CXML_AttrMapRelease		amfree;
		amfree(m_AttribList);
	}
}

CXML_Attribute* CXML_XMLTagNode::GetAttribute(unsigned int index)
{
	if(index < (unsigned int)m_AttribList.size())
	{
		//return m_AttribList.at(index);
		CXML_AttributeTable::iterator iter = m_AttribList.begin();
		for(unsigned int i = 0; i < index; i++)
			++iter;
		return iter->second;
	}
	else
	{
		return NULL;
	}
}

CXML_Attribute* CXML_XMLTagNode::GetAttribute(const std::wstring& szAttr)
{
	CXML_AttributeTable::iterator iter;
	iter = m_AttribList.find(szAttr);
	if(iter != m_AttribList.end())
	{
		return iter->second;
	}
	else
	{
		return NULL;
	}
}

CXML_Attribute* CXML_XMLTagNode::GetAttribute(const wchar_t* szAttr)
{
	CXML_AttributeTable::iterator iter;
	iter = m_AttribList.find(szAttr);
	if(iter != m_AttribList.end())
	{
		return iter->second;
	}
	else
	{
		return NULL;
	}
}

bool CXML_XMLTagNode::FindTag(const wchar_t* sText, CXML_XMLTagNode** pTag)
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

unsigned int CXML_XMLTagNode::nIdnt = 0;

class AttributePrint
{
public:
    //void operator()(CXML_Attribute* pAttrib)
	void operator()(CXML_AttributeTable::value_type iter)
    {
		CXML_Attribute* pAttrib = iter.second;
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
    void operator()(CXML_TagTextData* pText)
    {
		if(pText)
		{
			std::wstring		sText;
			XVSB_TEXTTYPE		tType;
			pText->QueryTypeAndText(tType, sText);
			
			switch(tType)
			{
				case enXVSB_XML_COMMENT:
					 PrintComment(sText);
					 break;
				case enXVSB_XML_TEXT:
					 PrintText(sText);
					 break;
				case enXVSB_XML_CDATA:
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
/*
		if(1 < sText.size() ||
		  (1 == sText.size() && !iswspace(sText[0])))
		{
			wprintf(L"%s", sText.c_str());	
		}
*/
	}

	void PrintCDATA(const std::wstring& sText)
	{
		wprintf(L"<![CDATA[%s]]>", sText.c_str());
	}

};

class TagPrint
{
public:
    void operator()(CXML_XMLTagNode* pTag)
    {
		if(pTag)
		{
			pTag->PrintTagNode();
		}
    }
};

void CXML_XMLTagNode::PrintTagNode(void)
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
		wprintf(L"\n%*s",3 * ++CXML_XMLTagNode::nIdnt,L"");
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
		wprintf(L"\n%*s",3 * CXML_XMLTagNode::nIdnt--, L"");
		wprintf(L"</%s>",m_pTag->m_sTag.c_str());
	}

	return;
}

CXML_hXML CXML_CreateXMLTree(void)
{
	CXML_XMLTagNode* pXML = new CXML_XMLTagNode();
	return pXML;
}

bool CXML_DeleteXMLTree(CXML_hXML& hXML)
{
	bool bRet = false;
	if(hXML)
	{
		delete ((CXML_XMLTagNode*)hXML);
		hXML = NULL;
		bRet = true;
	}
	return bRet; 
}


