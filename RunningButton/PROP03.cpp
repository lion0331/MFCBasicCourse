// PROP03.cpp: 实现文件
//

#include "pch.h"
#include "RunningButton.h"
#include "PROP03.h"
#include "afxdialogex.h"


// PROP_03 对话框

IMPLEMENT_DYNAMIC(PROP_03, CPropertyPage)

PROP_03::PROP_03()
	: CPropertyPage(IDD_PROP_03)
	, m_money(_T(""))
{

}

PROP_03::~PROP_03()
{
}

void PROP_03::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_MONEY, m_money);
}


BEGIN_MESSAGE_MAP(PROP_03, CPropertyPage)
END_MESSAGE_MAP()


// PROP_03 消息处理程序


BOOL PROP_03::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	((CPropertySheet*)GetParent())->SetWizardButtons(PSWIZB_BACK|PSWIZB_FINISH);
	return CPropertyPage::OnSetActive();
}


BOOL PROP_03::OnWizardFinish()
{
	// TODO: 在此添加专用代码和/或调用基类
	UpdateData();
	if (m_money.GetLength() <= 0) {
		MessageBox(_T("薪资范围未选择！！"), _T("请选择薪资"), MB_OK | MB_ICONERROR);
		return -1;
	}
	return CPropertyPage::OnWizardFinish();
}
