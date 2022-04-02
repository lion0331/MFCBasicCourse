// PROP01.cpp: 实现文件
//

#include "pch.h"
#include "RunningButton.h"
#include "PROP01.h"
#include "afxdialogex.h"


// PROP_01 对话框

IMPLEMENT_DYNAMIC(PROP_01, CPropertyPage)

PROP_01::PROP_01()
	: CPropertyPage(IDD_PROP_01)
	,m_lang(-1)
	, m_company(_T(""))
{
}

PROP_01::~PROP_01()
{
}

void PROP_01::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_CPP, m_lang);
	DDX_LBString(pDX, IDC_LIST_COMPANY, m_company);
}


BEGIN_MESSAGE_MAP(PROP_01, CPropertyPage)
END_MESSAGE_MAP()


// PROP_01 消息处理程序


BOOL PROP_01::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST_COMPANY);
	if (pListBox) {
		pListBox->AddString(_T("阿里巴巴"));
		pListBox->AddString(_T("华为"));
		pListBox->AddString(_T("腾讯"));
		pListBox->AddString(_T("京东"));
		pListBox->AddString(_T("百度"));
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


BOOL PROP_01::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	((CPropertySheet*)GetParent())->SetWizardButtons(PSWIZB_NEXT);
	((CPropertySheet*)GetParent())->GetDlgItem(IDHELP)->ShowWindow(SW_HIDE);
	return CPropertyPage::OnSetActive();
}


LRESULT PROP_01::OnWizardNext()
{
	// TODO: 在此添加专用代码和/或调用基类
	UpdateData();
	if (m_lang == -1) {
		MessageBox(_T("请选择开发语言！"), _T("开发语言未选择"), MB_OK | MB_ICONERROR);
		return -1;
	}
	if (m_company.GetLength() == 0) {
		MessageBox(_T("请选公司！"), _T("公司未选择"), MB_OK | MB_ICONERROR);
		return -1;
	}
	return CPropertyPage::OnWizardNext();
}
