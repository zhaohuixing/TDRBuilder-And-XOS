// Orignated from the code written in July 2003
#ifndef __XXML_TAG_H__
#define __XXML_TAG_H__

#include <string>
#include <vector>
#include "xxml_attribute.h"
#include "xxml_tagtdata.h"

class CXML_XMLTagNode;

class CXML_XMLTag
{
    friend CXML_XMLTagNode; 
public:
	CXML_XMLTag(void);
	CXML_XMLTag(const std::wstring& sTag);
	CXML_XMLTag(const wchar_t* sTag);
	virtual ~CXML_XMLTag(void);

// XML tag's operation: 
public:
	inline void SetTag(const std::wstring& sTag){m_sTag.assign(sTag);};
	inline void SetTag(const wchar_t* sTag){m_sTag.assign(sTag);};
	inline void QueryTag(std::wstring& sTag){sTag.assign(m_sTag);}
	inline std::wstring GetTag(void){return m_sTag;}

// XML Attributes' operation: 
public:
	inline int GetAttributesNumber(void){return (int)m_AttribList.size();}

	inline void AddAttribute(CXML_Attribute* pAttrib)
	{
		m_AttribList.insert(std::make_pair(pAttrib->GetAttribute(), pAttrib));
	}
	
	CXML_Attribute* GetAttribute(unsigned int index);
	CXML_Attribute* GetAttribute(const std::wstring& szAttr);
	CXML_Attribute* GetAttribute(const wchar_t* szAttr);

	inline int GetTextDataNumber(void){return (int)m_TextList.size();}
	inline void AddTextData(CXML_TagTextData* pTextData){m_TextList.push_back(pTextData);}
	CXML_TagTextData* GetTextData(unsigned int index);
    
private:
	void ClearAttributeList(void);
	void ClearTextList(void);

public:
	std::wstring        	m_sTag;
    //CXML_AttributeList   	m_AttribList;
	CXML_AttributeTable		m_AttribList;
	CXML_TagTextDataList 	m_TextList; 
};

class CXML_XMLTagNode
{
public:
	typedef std::vector<CXML_XMLTagNode*> CXML_TagList;
    typedef CXML_TagList::iterator        CTagIterator;

public:
	CXML_XMLTagNode(void);
	CXML_XMLTagNode(CXML_XMLTag* pTag, CXML_XMLTagNode* pUpperTagNode);
	virtual ~CXML_XMLTagNode(void);

public:
	CXML_XMLTagNode*     	m_pUpperTag;
	CXML_TagList			m_ChildTags;

	inline void SetXMLHeader(const std::wstring& sText){m_sXMLHeader.assign(sText);};
	inline void SetXMLHeader(const wchar_t* sText){m_sXMLHeader.assign(sText);};
	inline void QueryXMLHeader(std::wstring& sText){sText.assign(m_sXMLHeader);};

	inline void SetTag(CXML_XMLTag* pTag){m_pTag = pTag;};
	inline CXML_XMLTag* GetTag(void) const {return m_pTag;};

	inline void AddChildTagNode(CXML_XMLTagNode* pTagNode)
	{
		if(pTagNode)
			m_ChildTags.push_back(pTagNode);
	}	

	bool HasChildNode(void) {return !m_ChildTags.empty();}; 
	CTagIterator ChildNodeBegin(void){return m_ChildTags.begin();};
	CTagIterator ChildNodeEnd(void){return m_ChildTags.end();};

	inline int GetAttributesNumber(void){return (int)m_AttribList.size();}
	
	inline void AddAttribute(CXML_Attribute* pAttrib)
	{
		m_AttribList.insert(std::make_pair(pAttrib->GetAttribute(), pAttrib));
	}

	CXML_Attribute* GetAttribute(unsigned int index);
	CXML_Attribute* GetAttribute(const std::wstring& szAttr);
	CXML_Attribute* GetAttribute(const wchar_t* szAttr);

	bool FindTag(const wchar_t* sText, CXML_XMLTagNode** pTag);	

protected:
	void ClearChildTagNodes(void);
	void ClearAttributeList(void);

public:
	CXML_XMLTag*			m_pTag;
    CXML_AttributeTable		m_AttribList;
	std::wstring			m_sXMLHeader;

public:
	static unsigned int nIdnt;

    void PrintTagNode(void);
};

typedef CXML_XMLTagNode*   CXML_hXML;

extern "C"
{
	CXML_hXML CXML_CreateXMLTree(void);
	bool CXML_DeleteXMLTree(CXML_hXML& hXML);
};

#endif //__XOS_TAG_H__