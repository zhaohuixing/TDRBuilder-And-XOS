#ifndef __XUI_IMG_H__
#define __XUI_IMG_H__

#include "xui_ctrlbas.h"
#include "xui_frmtrait.h"
#include "xui_imgctrl.h"

class CXUI_Image :	public CXUI_CtrlBase
{
public:
	CXUI_Image(void);
	CXUI_Image(std::wstring& szName); // Constructor
	CXUI_Image(const wchar_t* szName); // Constructor
	virtual ~CXUI_Image(void);

public:
	virtual bool CreateCtrl(void);

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXUI_Image");}

	virtual XUI_UITYPE UIType(void) const {return enXUI_IMAGE;}

	virtual void SetResURL(std::wstring& szResURL);

	virtual void SetResURL(const wchar_t* szResURL);

	virtual std::wstring GetResURL(void);

	virtual void Assign(CXOS_ClassObject* pObj);

public:
	CXUI_Image& operator = (const CXUI_FormTrait& ctrlTrait);	// Assignment

public:

	CXUI_ImageCtrl			m_Image;
};

#endif