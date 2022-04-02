
// RunningButtonDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "RunningButton.h"
#include "RunningButtonDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "MyPropSheet.h"


// CRunningButtonDlg 对话框



CRunningButtonDlg::CRunningButtonDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RUNNINGBUTTON_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRunningButtonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON2, m_btn_right);
	DDX_Control(pDX, IDC_BUTTON1, m_btn_left);
}

BEGIN_MESSAGE_MAP(CRunningButtonDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON2, &CRunningButtonDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CRunningButtonDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BTN_QUERY, &CRunningButtonDlg::OnBnClickedBtnQuery)
END_MESSAGE_MAP()


// CRunningButtonDlg 消息处理程序

BOOL CRunningButtonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_btn_left.m_pButton = &m_btn_right;
	m_btn_right.m_pButton = &m_btn_left;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRunningButtonDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRunningButtonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRunningButtonDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//CRect left, right;
	//m_btn_right.GetWindowRect(right);
	//if (right.PtInRect(point) == TRUE) {
	//	m_btn_right.ShowWindow(SW_HIDE);
	//	m_btn_left.ShowWindow(SW_SHOW);
	//}
	//TRACE("%s(%d):%s %d %d\n", 
	//	__FILE__, __LINE__, __FUNCTION__, point.x, point.y);
	CDialogEx::OnMouseMove(nFlags, point);
}


void CRunningButtonDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("恭喜你，点到我了！"), _T("成功！"));
}


void CRunningButtonDlg::OnBnClickedBtnQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	// 创建职业调查的对话框
	CMyPropSheet dlg(_T("职业调查"));
	dlg.SetWizardMode();
	if (ID_WIZFINISH == dlg.DoModal()) {
		CString strMsg = _T("您的选择是：");
		switch (dlg.m_prop1.m_lang) {
		case 0:
			strMsg += _T("开发语言：C++");
			break;
		case 1:
			strMsg += _T("开发语言：Java");
			break;
		case 2:
			strMsg += _T("开发语言：Python");
			break;
		}
		strMsg += _T(" 您的公司是：") + dlg.m_prop1.m_company;
		strMsg += _T(" 您的技能有：");
		CString strSkill[4] = {
			_T("网络编程"),_T("MFC"),_T("操作系统"),_T("数据结构")
		};
		for (int i = 0; i < 4; i++) {
			if (dlg.m_prop2.m_skill[i]) {
				strMsg += strSkill[i] + _T(",");
			}
		}
		strMsg += _T(" 您的薪资范围是：") + dlg.m_prop3.m_money;
		MessageBox(strMsg, _T("最终信息"));
	}
}
