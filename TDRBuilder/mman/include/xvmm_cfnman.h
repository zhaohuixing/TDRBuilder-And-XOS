//2005/06/14
#ifndef __XVMM_CFNMAN_H__
#define __XVMM_CFNMAN_H__

#include "xvsb_defs.h"
#include "xvui_uidefs.h"
#include "xvui_graphman.h"
#include "xvsb_clsfn.h"
#include "ivui_mcbbas.h"

class CVMM_ClsFnManager : public CVUI_GraphManager
{
public:
	CVMM_ClsFnManager(CVSB_Method* pCFn, CVUI_GraphCallBack* pHandler = NULL);
	virtual ~CVMM_ClsFnManager(void);

public:
	void SetDirty(void);

	bool IsDirty(void);

	void Cleanup(void);

	bool Initialize(void);

	bool CreateRootNodes(void);

	bool CanAddComment(void);

	bool AddNewPU(const CPoint& pt, enXVSB_PUTYPE puType);
	
	bool AddNewLinker(const CPoint& pt, int nShape = 1);
	
	bool AddComment(const CPoint& pt);
	
	int GetNextPUID(void);
	
	int GetNextLinkID(void);

	void ChangeLinkage(int nOldHeadID, int nOldTailID, int nNewHeadID, int nNewTailID);

	void ChangeLogicYesLinkage(int nOldHeadID, int nOldTailID, int nNewHeadID, int nNewTailID);

	void ChangeLogicNoLinkage(int nOldHeadID, int nOldTailID, int nNewHeadID, int nNewTailID);

	void RemoveBlockLinkage(int nID);

	void DeleteActiveBlock(void);

	//@cmember: Remove the related linkage attached to the specific graph
	virtual void RemoveRelateLinkage(int nID);

	//@cmember: Query specific graph object ahead linked graph object ID
	virtual int GetGraphHeadLinkID(int nID);

	CVSB_FnPattern GetFuncPattern(void);

	CVSB_FnParamPattern GeParamPattern(void);

	CVSB_Method* GetClassFn(void);

	CVSB_ClassObject* GetCFnOwnerClass(void);

public:
	virtual COLORREF GetPaperColor(void){return m_clrPaperTemp;}
	virtual void SetPaperColor(COLORREF clr){m_clrPaperTemp = clr;}
	virtual bool IsGridOn(void){return m_bBKGrid;}
	virtual bool IsShadow(void){return m_bShadow;}
	virtual COLORREF GetGridColor(void){return m_clrGrid;}
	virtual void SetGridColor(COLORREF clr){m_clrGrid = clr;}
	virtual void SetGrid(bool bGrid){m_bBKGrid = bGrid;}
	virtual void SetShadow(bool bShadow)
	{
		m_bShadow = bShadow; 
		CVUI_GraphManager::SetShadow(m_bShadow);
	}

protected:
	//@cmember: Move the neighbor graphs
	virtual bool AdjustNeighborGraph(int nSrcID, CPoint ptOff, CRect& rect);

private:
	bool _addnewblock(enXVSB_PUTYPE puType, int nID);
	void _removeblock(int nID);
	bool _addcommentblock(int nID);

public:
	CVSB_Method*				m_hClassFn;
//	CVSB_Module					m_Module;
//	IVUI_MMCallBackBase*		m_ICallBack; 
	bool						m_bDirty;

protected:
	COLORREF					m_clrPaperTemp;
	bool						m_bBKGrid;			//Build-in parameter
	COLORREF					m_clrGrid;
	bool						m_bShadow;			//Build-in parameter
};


typedef std::map<CVSB_FnParamPattern, CVMM_ClsFnManager*> CVMM_CFnManTable;  //Key: Function object prototype pattern
typedef TVSB_PairDeletor<CVMM_CFnManTable::value_type> CVMM_CFnManTableDelete;
typedef TVSB_Dealloc<CVMM_CFnManTable, CVMM_CFnManTableDelete> CVMM_CFnManTableFree;

#endif
