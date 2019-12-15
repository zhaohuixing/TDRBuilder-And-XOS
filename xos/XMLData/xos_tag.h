#ifndef __XOS_TAG_H__
#define __XOS_TAG_H__

#include <string>
#include <vector>
#include "xos_attribute.h"
#include "xos_tagtdata.h"

class CXOS_XMLTagNode;

class CXOS_XMLTag
{
    friend CXOS_XMLTagNode; 
public:
	CXOS_XMLTag(void);
	CXOS_XMLTag(const std::wstring& sTag);
	CXOS_XMLTag(const wchar_t* sTag);
	virtual ~CXOS_XMLTag(void);

// XML tag's operation: 
public:
	inline void SetTag(const std::wstring& sTag){m_sTag.assign(sTag);};
	inline void SetTag(const wchar_t* sTag){m_sTag.assign(sTag);};
	inline void QueryTag(std::wstring& sTag){sTag.assign(m_sTag);}
	inline std::wstring GetTag(void){return m_sTag;}

// XML Attributes' operation: 
public:
	inline int GetAttributesNumber(void){return (int)m_AttribList.size();}
	inline void AddAttribute(CXOS_Attribute* pAttrib){m_AttribList.push_back(pAttrib);}
	CXOS_Attribute* GetAttribute(unsigned int index);

	inline int GetTextDataNumber(void){return (int)m_TextList.size();}
	inline void AddTextData(CXOS_TagTextData* pTextData){m_TextList.push_back(pTextData);}
	CXOS_TagTextData* GetTextData(unsigned int index);
    
private:
	void ClearAttributeList(void);
	void ClearTextList(void);

public:
	std::wstring        	m_sTag;
    CXOS_AttributeList   	m_AttribList;
	CXOS_TagTextDataList 	m_TextList; 
};

class CXOS_XMLTagNode
{
public:
	typedef std::vector<CXOS_XMLTagNode*> CXOS_TagList;
    typedef CXOS_TagList::iterator        CTagIterator;

public:
	CXOS_XMLTagNode(void);
	CXOS_XMLTagNode(CXOS_XMLTag* pTag, CXOS_XMLTagNode* pUpperTagNode);
	virtual ~CXOS_XMLTagNode(void);

public:
	CXOS_XMLTagNode*     	m_pUpperTag;
	CXOS_TagList			m_ChildTags;

	inline void SetXMLHeader(const std::wstring& sText){m_sXMLHeader.assign(sText);};
	inline void SetXMLHeader(const wchar_t* sText){m_sXMLHeader.assign(sText);};
	inline void QueryXMLHeader(std::wstring& sText){sText.assign(m_sXMLHeader);};

	inline void SetTag(CXOS_XMLTag* pTag){m_pTag = pTag;};
	inline CXOS_XMLTag* GetTag(void) const {return m_pTag;};

	inline void AddChildTagNode(CXOS_XMLTagNode* pTagNode)
	{
		if(pTagNode)
			m_ChildTags.push_back(pTagNode);
	}	

	bool HasChildNode(void) {return !m_ChildTags.empty();}; 
	CTagIterator ChildNodeBegin(void){return m_ChildTags.begin();};
	CTagIterator ChildNodeEnd(void){return m_ChildTags.end();};

	inline int GetAttributesNumber(void){return (int)m_AttribList.size();}
	inline void AddAttribute(CXOS_Attribute* pAttrib){m_AttribList.push_back(pAttrib);}
	CXOS_Attribute* GetAttribute(unsigned int index);

	bool FindTag(const wchar_t* sText, CXOS_XMLTagNode** pTag);	

protected:
	void ClearChildTagNodes(void);
	void ClearAttributeList(void);

public:
	CXOS_XMLTag*			m_pTag;
    CXOS_AttributeList		m_AttribList;
	std::wstring			m_sXMLHeader;

public:
	static unsigned int nIdnt;

    void PrintTagNode(void);
};

typedef CXOS_XMLTagNode*   CXOS_hXML;

extern "C"
{
	CXOS_hXML CXOS_CreateXMLTree(void);
	bool     CXOS_DeleteXMLTree(CXOS_hXML& hXML);
};

#endif //__XOS_TAG_H__