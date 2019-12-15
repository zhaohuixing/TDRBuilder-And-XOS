// Orignated from the code written in July 2003
#ifndef __XDOM_MDOMADAPTOR_H__
#define __XDOM_MDOMADAPTOR_H__
#include "xxml_attribute.h"
#include "xxml_tag.h"
#include "tdom_msdomadptor.h"

class CDOM_MSDOMAdaptor : public TDOM_MSDOMAdaptorBase<CXML_hXML>  
{
public:
	CDOM_MSDOMAdaptor();
	virtual ~CDOM_MSDOMAdaptor();

public:
	virtual bool ExploreXMLTree(CXML_hXML* pXML);
	virtual bool CreateXMLTree(const CXML_hXML& hXML);

private:
	bool FillNode(XDOM_NODE_PTR& ptrNode, CXML_hXML* pXML);
	bool CreateNode(XDOM_NODE_PTR& ptrNode, CXML_hXML hXML);
};

#endif // __XDOM_MDOMADAPTOR_H__
