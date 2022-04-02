// MyPropSheet.cpp: 实现文件
//

#include "pch.h"
#include "RunningButton.h"
#include "MyPropSheet.h"


// CMyPropSheet

IMPLEMENT_DYNAMIC(CMyPropSheet, CPropertySheet)

CMyPropSheet::CMyPropSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_prop1);
	AddPage(&m_prop2);
	AddPage(&m_prop3);
}

CMyPropSheet::CMyPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_prop1);
	AddPage(&m_prop2);
	AddPage(&m_prop3);
}

CMyPropSheet::~CMyPropSheet()
{
}


BEGIN_MESSAGE_MAP(CMyPropSheet, CPropertySheet)
END_MESSAGE_MAP()


// CMyPropSheet 消息处理程序
