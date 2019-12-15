// Orignated from the code written in July 2003
#ifndef __TDOM_MSDOMADPTOR_H__
#define __TDOM_MSDOMADPTOR_H__

#include "xxml_msxmlinc.h"
#include <string>
#include <list>
#include <atlbase.h>

#pragma warning( disable: 4251 )

#define XDOM_DOC_PTR				CComPtr<MSXML2::IXMLDOMDocument2> 
#define XDOM_NODE_PTR				CComPtr<MSXML2::IXMLDOMNode>
#define XDOM_NODEMAP_PTR			CComPtr<MSXML2::IXMLDOMNamedNodeMap>
#define XDOM_ATTR_PTR				CComPtr<MSXML2::IXMLDOMAttribute>

template<typename TXMLData> class TDOM_MSDOMAdaptorBase
{  
public:
	TDOM_MSDOMAdaptorBase();
	~TDOM_MSDOMAdaptorBase();

public:
	virtual bool ExploreXMLTree(TXMLData* pXML){return true;};
	virtual bool CreateXMLTree(const TXMLData& hXML){return true;};

public:
	virtual bool Initialize(void);
	virtual void UnInitialize(void);
	virtual bool Load(const wchar_t* szURL);
	virtual bool Save(const wchar_t* szURL);
	virtual bool Reset(void);

	// Get/Set name, text, or value of node
	bool SetNodeName(XDOM_NODE_PTR& ptrParent, XDOM_NODE_PTR& ptrNode, const wchar_t* lpszText);
	bool GetNodeName(XDOM_NODE_PTR& ptrNode, std::wstring& strName);
	bool SetNodeText(XDOM_NODE_PTR& ptrNode, const wchar_t* lpszText);
	bool GetNodeText(XDOM_NODE_PTR& ptrNode, std::wstring& strText);
	bool SetNodeValue(XDOM_NODE_PTR& ptrNode, const wchar_t* lpszValue);
	bool GetNodeValue(XDOM_NODE_PTR& ptrNode, std::wstring& strValue);

	bool GetNodeType(XDOM_NODE_PTR& ptrNode, MSXML2::DOMNodeType& nodeType);
	
	//Child node
	XDOM_NODE_PTR	CreateDOMChildNode(XDOM_NODE_PTR& ptrNode, const wchar_t* lpszName, int nType = MSXML2::NODE_ELEMENT);
	
	// Create attribute
	XDOM_ATTR_PTR	CreateDOMNodeAttribute(XDOM_NODE_PTR& ptrNode, const wchar_t* lpszName, const wchar_t* lpszValue);
	
	// Get document
	XDOM_DOC_PTR&	GetDOMDocument(void);
	XDOM_NODE_PTR&	GetDOMNode(void);
	
	bool			IsInitialized(void);
	bool			IsLoaded(void);
	
protected:
	void Clear(void);
	void PackNode(XDOM_NODE_PTR & ptrNode, XDOM_ATTR_PTR & ptrAttr);

protected:
	bool			m_bInitialized;
	bool			m_bLoaded;

	XDOM_DOC_PTR	m_ptrDoc;
	XDOM_NODE_PTR	m_ptrDocNode;
};

#include "tdom_msdomadptor.inl"
#endif // __TDOM_MSDOMADPTOR_H__