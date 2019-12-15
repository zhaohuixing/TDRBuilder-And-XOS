//2005/02/03
#ifndef __XVMM_MMAN_H__
#define __XVMM_MMAN_H__

#include "xvsb_defs.h"
#include "xvui_uidefs.h"
#include "xvui_graphman.h"
#include "xvsb_module.h"
#include "ivui_mcbbas.h"

class CVMM_ModuleManager : public CVUI_GraphManager
{
public:
	CVMM_ModuleManager(CVUI_GraphCallBack* pHandler = NULL);
	virtual ~CVMM_ModuleManager(void);

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

protected:
	//@cmember: Move the neighbor graphs
	virtual bool AdjustNeighborGraph(int nSrcID, CPoint ptOff, CRect& rect);

private:
	bool _addnewblock(enXVSB_PUTYPE puType, int nID);
	void _removeblock(int nID);
	bool _addcommentblock(int nID);

public:
	CVSB_Module					m_Module;
	IVUI_MMCallBackBase*		m_ICallBack; 
	bool						m_bDirty;
};

#endif
