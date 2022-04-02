// PROP02.cpp: 实现文件
//

#include "pch.h"
#include "RunningButton.h"
#include "PROP02.h"
#include "afxdialogex.h"


// PROP_02 对话框

IMPLEMENT_DYNAMIC(PROP_02, CPropertyPage)

PROP_02::PROP_02()
	: CPropertyPage(IDD_PROP_02)
{
	memset(m_skill, 0, sizeof(m_skill));
}

PROP_02::~PROP_02()
{
}

void PROP_02::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, m_skill[0]);//网络编程
	DDX_Check(pDX, IDC_CHECK2, m_skill[1]);//MFC
	DDX_Check(pDX, IDC_CHECK3, m_skill[2]);//操作系统
	DDX_Check(pDX, IDC_CHECK4, m_skill[3]);//数据结构

}


BEGIN_MESSAGE_MAP(PROP_02, CPropertyPage)
END_MESSAGE_MAP()


// PROP_02 消息处理程序


BOOL PROP_02::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	((CPropertySheet*)GetParent())->SetWizardButtons(PSWIZB_NEXT | PSWIZB_BACK);
	return CPropertyPage::OnSetActive();
}


LRESULT PROP_02::OnWizardNext()
{
	// TODO: 在此添加专用代码和/或调用基类
	bool hasChoose = false;
	UpdateData();
	for (int i = 0; i < 4; i++) {
		if (m_skill[i] == TRUE) {
			hasChoose = true;
			break;
		}
	}
	if (!hasChoose) {
		MessageBox(_T("技能未选择！！"), _T("请选择技能"), MB_OK | MB_ICONERROR);
		return -1;
	}
	return CPropertyPage::OnWizardNext();
}
