
// MFCCommonItemDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCCommonItem.h"
#include "MFCCommonItemDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCCommonItemDlg 对话框



CMFCCommonItemDlg::CMFCCommonItemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCOMMONITEM_DIALOG, pParent)
	, m_sex(-1)

	, m_strText(_T(""))
{
	memset(m_fav, 0, sizeof(m_fav));
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCCommonItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RAD_MALE, m_sex);
	DDX_Check(pDX, IDC_CK_FOOTBALL, m_fav[0]);
	DDX_Check(pDX, IDC_CK_BKBALL, m_fav[1]);
	DDX_Check(pDX, IDC_CK_YOGA, m_fav[2]);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_strText);
	DDX_Control(pDX, IDC_LIST_COMPANY, m_company);
	DDX_Control(pDX, IDC_COMBO1, m_simple);
	DDX_Control(pDX, IDC_COMBO2, m_droplist);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Control(pDX, IDC_YIDOYUN, m_picture);
	DDX_Control(pDX, IDC_LIST_DATA, m_list);
	DDX_Control(pDX, IDC_TREE, m_tree);
}

BEGIN_MESSAGE_MAP(CMFCCommonItemDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_RESULT, &CMFCCommonItemDlg::OnBnClickedBtnResult)
	ON_EN_CHANGE(IDC_EDIT_TEXT, &CMFCCommonItemDlg::OnEnChangeEditText)
	ON_BN_CLICKED(IDC_BTN_TEST, &CMFCCommonItemDlg::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_BTN_TEST_DROPLIST, &CMFCCommonItemDlg::OnBnClickedBtnTestDroplist)
	ON_BN_CLICKED(IDC_BTN_PROGRESS, &CMFCCommonItemDlg::OnBnClickedBtnProgress)
	ON_WM_TIMER()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BTN_LIST, &CMFCCommonItemDlg::OnBnClickedBtnList)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, &CMFCCommonItemDlg::OnTvnSelchangedTree)
END_MESSAGE_MAP()


// CMFCCommonItemDlg 消息处理程序

BOOL CMFCCommonItemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetDlgItemText(IDC_EDIT_TEXT, _T("aaaaaaaaaa\nbbbbbbbbbbbbbbbbbbbb\n"));
	m_company.AddString(_T("浏阳拖拉机厂"));
	m_company.AddString(_T("汨罗帽子厂"));
	m_company.AddString(_T("四川飞机厂"));
	m_company.AddString(_T("湖北造船厂"));
	m_progress.SetRange(0, 10000);
	//m_progress_pos = 0;
	//m_progress.SetMarquee(TRUE, -100);
	m_progress_pos = 10000;
	SetTimer(99, 3000, NULL);//定时器的精度，不要低于30ms
	SetTimer(10, 100, NULL);//10ms一次
	m_list.SetBkColor(RGB(128, 255, 64));
	m_list.SetTextBkColor(RGB(128, 255, 64));
	m_list.InsertColumn(0, _T("CHECK"), LVCFMT_LEFT, 200);
	m_list.InsertColumn(1, _T("IP"), LVCFMT_LEFT, 140);
	m_list.InsertColumn(2, _T("ID"), LVCFMT_LEFT, 240);
	m_list.InsertColumn(3, _T("序号"), LVCFMT_LEFT, 50);
	DWORD extStyle = m_list.GetExtendedStyle();
	//extStyle |= LVS_EX_FULLROWSELECT;
	//extStyle |= LVS_EX_GRIDLINES;
	extStyle |= LVS_EX_CHECKBOXES;
	//extStyle |= LVS_EX_BORDERSELECT;//图标模式下才有的
	m_list.SetExtendedStyle(extStyle);

	m_list.InsertItem(0, CString("FALSE"));//序号
	m_list.SetItemText(0, 1, _T("192.168.0.1"));//IP
	m_list.SetItemText(0, 2, _T("430999198101014415"));//ID
	m_list.SetItemText(0, 3, _T("0"));//CHECK
	m_list.InsertItem(1, CString("TRUE"));//序号
	m_list.SetItemText(1, 1, _T("192.168.0.1"));//IP
	m_list.SetItemText(1, 2, _T("430999198101014415"));//ID
	m_list.SetItemText(1, 3, _T("1"));//CHECK

	m_icons.Create(IDB_TREE, 32, 3, 0);
	m_tree.SetImageList(&m_icons, TVSIL_NORMAL);
	// TREE
	HTREEITEM hRoot = m_tree.InsertItem(_T("root"), 0, 1);
	HTREEITEM hLeaf1 = m_tree.InsertItem(_T("leaf"), 2, 1, hRoot);
	m_tree.InsertItem(_T("sub"), 2, 1, hLeaf1);
	HTREEITEM hLeaf2 = m_tree.InsertItem(_T("leaf"), 2, 1, hRoot);
	m_tree.InsertItem(_T("sub"), 2, 1, hLeaf2);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCCommonItemDlg::OnPaint()
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
HCURSOR CMFCCommonItemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCCommonItemDlg::OnBnClickedBtnResult()
{
	UpdateData();
	if (m_sex == -1) {
		MessageBox(_T("请选择性别！"), _T("性别缺失"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	CString strMsg = CString(_T("您的性别是：")) + ((m_sex == 0) ? _T("男") : _T("女")) + _T("\n");
	CString strFav = _T("");
	//CString Favs[3] = { _T("足球"),_T("篮球"),_T("瑜伽") };
	UINT nID = IDC_CK_FOOTBALL;
	//UINT nIDs[3] = { IDC_CK_FOOTBALL,1004,IDC_CK_YOGA };
	for (int i = 0; i < 3; i++) {
		if (m_fav[i]) {
			CString strName;
			GetDlgItemText(nID + i, strName);
			//GetDlgItemText(nIDs[i], strName);
			strFav += strName + _T(" ");
		}
	}
	if (strFav.GetLength() > 0) {
		strMsg += _T("您的爱好是：") + strFav;
	}
	else {
		strMsg += _T("您没有任何爱好！");
	}
	MessageBox(strMsg, _T("结果展示"));
	CWnd* pTestBtn = GetDlgItem(IDC_BTN_TEST);
	if (pTestBtn->IsWindowEnabled() == FALSE)
		pTestBtn->EnableWindow(TRUE);
	else
		pTestBtn->EnableWindow(FALSE);
	CWnd* pText = GetDlgItem(IDC_EDIT_TEXT);
	if (pText->IsWindowEnabled() == FALSE) {
		pText->EnableWindow(TRUE);
	}

}


void CMFCCommonItemDlg::OnEnChangeEditText()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	m_strText = m_strText.MakeUpper();
	UpdateData(FALSE);
}


void CMFCCommonItemDlg::OnBnClickedBtnTest()
{
	CString strText;
	if (m_company.GetSelCount() == 0) {
		MessageBox(_T("没有选中任何公司"));
		return;
	}
	else {
		int total = m_company.GetSelCount();
		int* index = new int[total];
		strText += _T("你选中了");
		TCHAR buf[32] = _T("");
		_itow_s(total, buf, 32, 10);
		strText += buf;
		strText += _T("个公司\n");
		m_company.GetSelItems(total, index);
		CString strTemp;
		for (int i = 0; i < total; i++)
		{
			m_company.GetText(index[i], strTemp);
			strText += strTemp + _T(" ");
		}
		delete[] index;
		MessageBox(strText);
		m_company.GetText(m_company.GetCurSel(), strTemp);
	}
}


void CMFCCommonItemDlg::OnBnClickedBtnTestDroplist()
{
	// TODO: 在此添加控件通知处理程序代码
	int cur = m_simple.GetCurSel();
	if (cur == -1) {
		TRACE("%s(%d):当前没有选中任何列\n", __FILE__, __LINE__);
	}
	else {
		TRACE("%s(%d):当前选中了第%d列\n", __FILE__, __LINE__, cur + 1);
		CString tmp;
		m_simple.GetLBText(cur, tmp);
		MessageBox(tmp);
	}
	cur = m_droplist.GetCurSel();
	CString tmp;
	if (cur == -1) {
		TRACE("%s(%d):当前没有选中任何列\n", __FILE__, __LINE__);
		m_droplist.GetWindowText(tmp);
		MessageBox(tmp);
	}
	else {
		TRACE("%s(%d):当前选中了第%d列\n", __FILE__, __LINE__, cur + 1);
		m_droplist.GetLBText(cur, tmp);
		m_droplist.GetEditSel();//获取编辑框选中的字符数量
		m_droplist.GetWindowText(tmp);
		MessageBox(tmp);
	}
}


void CMFCCommonItemDlg::OnBnClickedBtnProgress()
{
	int pos = m_progress.GetPos();
	m_progress.SetPos(pos + 500);
}


void CMFCCommonItemDlg::OnTimer(UINT_PTR nIDEvent)
{
	static int count = 0;
	TRACE("%08X", GetTickCount64());
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 99) {//进度条的更新器
		//m_progress.SetMarquee(FALSE, 5);
		m_progress.SetPos(m_progress_pos);
		//TRACE("%s(%d):%s %d\n", __FILE__, __LINE__, __FUNCTION__, m_progress_pos);
	}
	else if (nIDEvent == 10) {
		//TRACE("%s(%d):%s %d\n", __FILE__, __LINE__, __FUNCTION__, GetTickCount());
		//if (count > 5)KillTimer(10);
		//count++;
		int low, upper;
		m_progress.GetRange(low, upper);
		//if (m_progress_pos >= upper) {
		//	KillTimer(10);
		//}
		//else {
		//	m_progress_pos += 10;
		//}
		if (m_progress_pos <= low) {
			KillTimer(10);
		}
		else {
			m_progress_pos -= 20;
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}





void CMFCCommonItemDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int count = DragQueryFile(hDropInfo, -1, NULL, 0);
	//count >1  MessageBox....
	TCHAR sPath[MAX_PATH];
	char mbsPath[MAX_PATH * 2];
	for (int i = 0; i < count; i++) {
		memset(sPath, 0, sizeof(sPath));
		memset(mbsPath, 0, sizeof(mbsPath));
		DragQueryFile(hDropInfo, i, sPath, MAX_PATH);
		size_t total = 0;
		wcstombs_s(&total, mbsPath, sizeof(mbsPath), sPath, MAX_PATH);
		TRACE("%s(%d):%s %s\n", __FILE__, __LINE__, __FUNCTION__, mbsPath);
		if (CString(sPath).Find(_T(".ico"))) {
			HICON hIcon = (HICON)LoadImage(AfxGetInstanceHandle(), sPath, IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
			m_picture.SetIcon(hIcon);
		}
	}
	InvalidateRect(NULL);
	CDialogEx::OnDropFiles(hDropInfo);
}


void CMFCCommonItemDlg::OnBnClickedBtnList()
{
	int lineCount = m_list.GetItemCount();
	CHeaderCtrl* pHeader = m_list.GetHeaderCtrl();
	int coloumnCount = pHeader->GetItemCount();
	for (int i = 0; i < lineCount; i++)
	{
		if (m_list.GetCheck(i)) {
			TRACE("%s(%d):%s %s\n", __FILE__, __LINE__, __FUNCTION__, "选中");
		}
		else {
			TRACE("%s(%d):%s %s\n", __FILE__, __LINE__, __FUNCTION__, "没中");
		}
		for (int j = 0; j < coloumnCount; j++)
		{
			CString temp = m_list.GetItemText(i, j);
			char text[256];
			memset(text, 0, sizeof(text));
			size_t total;
			wcstombs_s(&total, text, sizeof(text), temp, temp.GetLength());
			TRACE("%s(%d):%s %s\n", __FILE__, __LINE__, __FUNCTION__, text);
		}
	}
}


void CMFCCommonItemDlg::OnTvnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UINT nCount = m_tree.GetSelectedCount();
	if (nCount > 0) {
		HTREEITEM hSelect = m_tree.GetSelectedItem();
		CString strText = m_tree.GetItemText(hSelect);
		char sText[256] = "";
		size_t total;
		wcstombs_s(&total, sText, sizeof(sText), strText, strText.GetLength());
		TRACE("%s(%d):%s %s\n", __FILE__, __LINE__, __FUNCTION__, sText);
	}
	*pResult = 0;
}
