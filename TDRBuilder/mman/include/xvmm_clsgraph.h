#ifndef __XVMM_CLSGRAPH_H__
#define __XVMM_CLSGRAPH_H__
#include "xvsb_clstype.h"
#include "xvui_graph.h"
#include <map>
#include <string>
#include "xvmm_cfnman.h"

/////////////////////////////////////////////////////////////////////////////
// CVMM_ClassGraph

class CVMM_ClassGraph : public CVUI_GraphBase
{
//@Access: Constructors
protected:
// Constructors
public:
	//@cmember: Constructor
	CVMM_ClassGraph(long nID, CVUI_GraphManager* pManager = NULL);

	//@cmember: Constructor
	CVMM_ClassGraph(long nID, const CVSB_ClassType& clsType, CVUI_GraphManager* pManager);

	//@cmember: Constructor
	CVMM_ClassGraph(long nID, std::wstring& szNS, std::wstring& szCls, CVUI_GraphManager* pManager);

	//@cmember: Constructor
	CVMM_ClassGraph(long nID, const wchar_t* szNS, const wchar_t* szCls, CVUI_GraphManager* pManager);

	//@cmember: Destructor
	virtual ~CVMM_ClassGraph();

//@Access: Attributes
public:
	CVSB_ClassType		m_ClassType;
	CVMM_CFnManTable	m_ClsFnMap;


//@Access: Attributes
protected:

//@Access: Operations
public:
	//@cmember: Check the head link access
	virtual bool GetHeadLinkAccess(int nLink);

	//@cmember: Check the tail link access
	virtual bool GetTailLinkAccess(int nLink);

	CVSB_ClassType	GetClassType(void){return m_ClassType;}
	void SetClassType(CVSB_ClassType clstype);
	void SetClassName(std::wstring& szName);
	void SetClassName(const wchar_t* szName);

	void CleanMap();

	bool AddClsFnMan(CVSB_Method* pCFn); 
	bool UpdateClsFnMan(const CVSB_FnParamPattern& fnPP); 
	void RemoveClsFnMan(const CVSB_FnParamPattern& fnPP); 
	CVMM_ClsFnManager* QueryClsFnMan(const CVSB_FnParamPattern& fnPP); 
	CVMM_ClsFnManager* QueryClsFnMan(CVSB_Method* pCFn); 
	CVMM_ClsFnManager* QueryClsFnMan(CVSB_Method& pCFn); 


};

#endif // __XVUI_GRAPH_H__
