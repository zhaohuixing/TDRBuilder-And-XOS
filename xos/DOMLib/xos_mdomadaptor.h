#ifndef __XOS_MDOMADAPTOR_H__
#define __XOS_MDOMADAPTOR_H__
#include "xos_attribute.h"
#include "xos_tag.h"
#include "txos_msdomadptor.h"

class CXOS_MSDOMAdaptor : public TXOS_MSDOMAdaptorBase<CXOS_hXML>  
{
public:
	CXOS_MSDOMAdaptor();
	virtual ~CXOS_MSDOMAdaptor();

public:
	virtual bool ExploreXMLTree(CXOS_hXML* pXML);
	virtual bool CreateXMLTree(const CXOS_hXML& hXML);

private:
	bool FillNode(XDOM_NODE_PTR& ptrNode, CXOS_hXML* pXML);
	bool CreateNode(XDOM_NODE_PTR& ptrNode, CXOS_hXML hXML);
};

#endif // __XOS_MDOMADAPTOR_H__
