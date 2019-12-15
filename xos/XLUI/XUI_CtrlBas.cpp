#include "xui_ctrlbas.h"

CXUI_CtrlBase::CXUI_CtrlBase(void)
{
	m_bCreate = false;
}

CXUI_CtrlBase::~CXUI_CtrlBase(void)
{
	m_bCreate = false;
}

bool CXUI_CtrlBase::SetTraits(const CXUI_FormTrait& ctrlTrait)
{
	bool bRet = false;

	if(ctrlTrait.UIType() == UIType())
	{
		m_nCtrlID = ctrlTrait.m_nCtrlID;
		m_nStyle = ctrlTrait.m_nStyle;
		m_nExtStyle = ctrlTrait.m_nExtStyle;
		m_szText = ctrlTrait.m_szText;
		m_nLeft = ctrlTrait.m_nLeft;
		m_nRight = ctrlTrait.m_nRight;
		m_nTop = ctrlTrait.m_nTop;
		m_nBottom = ctrlTrait.m_nBottom;
		m_szResURL = ctrlTrait.m_szResURL;
		m_nResID = ctrlTrait.m_nResID;
		m_szName = ctrlTrait.m_szObjName;
		m_nReserve1 = ctrlTrait.m_nReserve1;
		bRet = true;
	}

	return bRet;
}