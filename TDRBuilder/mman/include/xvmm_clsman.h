//2005/02/03
#ifndef __XVMM_CLSMAN_H__
#define __XVMM_CLSMAN_H__

#include "xvsb_defs.h"
#include "xvui_uidefs.h"
#include "xvui_graphman.h"
#include "xvsb_clstype.h"
#include "xvsb_nspace.h"

class CVMM_ClassManager : public CVUI_GraphManager
{
public:
	CVMM_ClassManager(CVUI_GraphCallBack* pHandler = NULL);
	virtual ~CVMM_ClassManager(void);

public:
	void SetDirty(void);
	bool IsDirty(void);
	void Cleanup(void);
	bool Initialize(void);

	bool CanAddComment(void);
	bool AddNewClass(const CPoint& pt);
	bool AddNewClass(const CPoint& pt, std::wstring& szClass);
	bool AddNewClass(const CPoint& pt, const wchar_t* szClass);
	bool AddNewLinker(const CPoint& pt, int nShape = 1);
	bool AddNewGlueLinker(int nHeadID, int nTailID, const CPoint& pt, int nShape = 1);
	bool AddComment(const CPoint& pt);
	int GetNextPUID(void);
	int GetNextLinkID(void);

	void ChangeLinkage(int nOldHeadID, int nOldTailID, int nNewHeadID, int nNewTailID);

	void RemoveBlockLinkage(int nID);
	void DeleteActiveBlock(void);

	void SetNameSpace(std::wstring& szNamespace);
	void SetNameSpace(const wchar_t* szNamespace);
	std::wstring GetNameSpace(void);

	//@cmember: Remove the related linkage attached to the specific graph
	virtual void RemoveRelateLinkage(int nID);

	//@cmember: Remove the related linkage between two classes
	virtual void RemoveHeritageLinkage(int nID);

	//@cmember: Check possibility of set linker head linkage
	virtual bool CanSetHeadLink (int nLinkID, int nHeadID);

	//@cmember: Check possibility of set linker tail linkage
	virtual bool CanSetTailLink (int nLinkID, int nTailID);

	bool CanAddClass(std::wstring& szClass);
	bool CanAddClass(const wchar_t* szClass);
     
	bool IsClassBlock(int nID);
	CVSB_ClassUnit* QueryClassUnit(int nID);
	CVSB_ClassObject* QueryClass(int nID);
	CVSB_ClassType QueryClassType(int nID);
	int QueryClassID(CVSB_ClassType clsType);
	int QueryClassID(std::wstring& szClass);
	int QueryClassID(const wchar_t* szClass);

	bool RemoveHeritage(int nHeadID, int nTailID, bool& bConflict);
	bool AddHeritage(int nHeadID, int nTailID, bool& bConflict);
	void AddConflictList(int nID);

	bool RemoveClass(int nID);

	void UpdateActiveClassLink(void);

	int GetClassInheritanceLink(int nID);

	bool ConnectClassGraphs(int nHeadID, int nTailID);

protected:
	//@cmember: Move the neighbor graphs
	virtual bool AdjustNeighborGraph(int nSrcID, CPoint ptOff, CRect& rect);

private:
	bool _addnewblock(enXVSB_PUTYPE puType, int nID);
	void _removeblock(int nID);
	bool _addcommentblock(int nID);
	bool _addnewclass(std::wstring& szClass, CVSB_ClassType& cType);

public:
	bool					m_bDirty;
	std::wstring			m_szNamespace;
	CVSB_Namespace*			m_hNamespace;
};

#endif
