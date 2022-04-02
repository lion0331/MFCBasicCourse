// CBingoDialog.cpp: 实现文件
//

#include "pch.h"
#include "MFCApp.h"
#include "CBingoDialog.h"
#include "afxdialogex.h"


// CBingoDialog 对话框

IMPLEMENT_DYNAMIC(CBingoDialog, CDialog)

CBingoDialog::CBingoDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DLG_EDOYUN, pParent)
	, m_value1(0)
	, m_value2(0)
	, m_value3(0)
{

}

CBingoDialog::~CBingoDialog()
{
}

void CBingoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ONE, m_value1);
	DDV_MinMaxInt(pDX, m_value1, -9999, 9999);
	DDX_Text(pDX, IDC_EDIT_TWO, m_value2);
	DDV_MinMaxInt(pDX, m_value2, -9999, 9999);
	DDX_Text(pDX, IDC_EDIT_THREE, m_value3);
	DDX_Control(pDX, IDC_EDIT_ONE, m_edit1);
	DDX_Control(pDX, IDC_EDIT_TWO, m_edit2);
	DDX_Control(pDX, IDC_EDIT_THREE, m_edit3);
}


BEGIN_MESSAGE_MAP(CBingoDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CBingoDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CBingoDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_LARGE, &CBingoDialog::OnBnClickedBtnLarge)
END_MESSAGE_MAP()


// CBingoDialog 消息处理程序


void CBingoDialog::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	TRACE("%s(%d):%s\n", __FILE__, __LINE__, __FUNCTION__);
	if (m_button.m_hWnd == NULL) {
		m_button.Create(_T("动态"), BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD, CRect(100, 100, 200, 150), this, 9999);
	}
	TCHAR buf[20] = _T("");
	::SendMessage(m_edit1.m_hWnd, WM_GETTEXT, 20, (LPARAM)buf);
	m_edit1.SendMessage(WM_SETTEXT, sizeof(buf), (LPARAM)buf);
	this->SendMessage(WM_GETTEXT, 20, (LPARAM)buf);
}


BOOL CBingoDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CWnd* pEdit01 = GetDlgItem(IDC_EDIT_ONE);
	CWnd* pEdit02 = GetDlgItem(IDC_EDIT_TWO);
	//CWnd* pEdit03 = GetDlgItem(IDC_EDIT_THREE);
	CString strText;
	if (pEdit01 != NULL) {
		pEdit01->SetWindowText(_T("100"));
		pEdit01->GetWindowText(strText);
	}
	if (pEdit02 != NULL) {
		//pEdit02->SetWindowText(_T("200"));
		SetDlgItemText(IDC_EDIT_TWO, _T("200"));
		GetDlgItemText(IDC_EDIT_TWO, strText);
	}
	//if (pEdit03 != NULL)pEdit03->SetWindowText(_T("300"));
	SetDlgItemInt(IDC_EDIT_THREE, 300);
	BOOL isTrans = FALSE;
	UINT ret = GetDlgItemInt(IDC_EDIT_THREE, &isTrans);
	GetWindowRect(m_large);
	m_small = m_large;
	m_small.right = m_small.left + m_small.Width() / 2;
	m_small.bottom = m_small.top + m_small.Height() / 2;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CBingoDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialog::OnOK();
	//UpdateData();
	//m_value3 = m_value2 + m_value1;
	//UpdateData(FALSE);
	CString str1, str2, str3;
	m_edit1.GetWindowText(str1);
	m_edit2.GetWindowText(str2);
	int t = _wtoi(str1) + _wtoi(str2);
	TCHAR buf[32] = _T("");
	_itow_s(t, buf, 10);
	str3 = buf;
	m_edit3.SetWindowText(str3);
}


void CBingoDialog::OnBnClickedBtnLarge()
{
	// TODO: 在此添加控件通知处理程序代码
	CRect curRect;
	GetWindowRect(curRect);//获取窗口的大小
	CWnd* pButton = GetDlgItem(IDC_BTN_LARGE);
	CString strTitle;
	if (pButton) {
		pButton->GetWindowText(strTitle);
		if (strTitle == _T("放大") && (m_large.IsRectEmpty() == FALSE)) {
			pButton->SetWindowText(_T("缩小"));
			//SetWindowPos(&wndTopMost, curRect.left, curRect.top, m_large.Width(), m_large.Height(), SWP_NOMOVE );
			SetWindowPos(NULL, curRect.left, curRect.top, m_large.Width(), m_large.Height(), SWP_NOMOVE | SWP_NOZORDER);
		}
		else if (m_small.IsRectEmpty() == FALSE) {
			pButton->SetWindowText(_T("放大"));
			SetWindowPos(&wndBottom, curRect.left, curRect.top, m_small.Width(), m_small.Height(), SWP_NOMOVE /*| SWP_NOZORDER*/);
			//wndTopMost;
			//SetWindowPos(NULL, curRect.left, curRect.top, m_small.Width(), m_small.Height(), SWP_NOMOVE | SWP_NOZORDER);
		}
	}
}
