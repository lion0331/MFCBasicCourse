#pragma once
#include "PROP01.h"
#include "PROP02.h"
#include "PROP03.h"



// CMyPropSheet

class CMyPropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMyPropSheet)

public:
	CMyPropSheet(UINT nIDCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	CMyPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	virtual ~CMyPropSheet();
public:
	PROP_01 m_prop1;
	PROP_02 m_prop2;
	PROP_03 m_prop3;

protected:
	DECLARE_MESSAGE_MAP()
};


