
// MFCCommonItemDlg.h: 头文件
//

#pragma once


// CMFCCommonItemDlg 对话框
class CMFCCommonItemDlg : public CDialogEx
{
// 构造
public:
	CMFCCommonItemDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCOMMONITEM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnResult();
	// 进度
	int m_progress_pos;
	// 性别
	int m_sex;
	// 爱好
	BOOL m_fav[3];
	CString m_strText;
	afx_msg void OnEnChangeEditText();
	CListBox m_company;
	afx_msg void OnBnClickedBtnTest();
	CComboBox m_simple;
	// 下拉列表
	CComboBox m_droplist;
	afx_msg void OnBnClickedBtnTestDroplist();
	CProgressCtrl m_progress;
	afx_msg void OnBnClickedBtnProgress();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// 图片显示
	CStatic m_picture;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CListCtrl m_list;
	afx_msg void OnBnClickedBtnList();
	CTreeCtrl m_tree;
	CImageList m_icons;
	afx_msg void OnTvnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
};
