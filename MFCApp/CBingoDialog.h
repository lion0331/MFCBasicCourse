#pragma once


// CBingoDialog 对话框

class CBingoDialog : public CDialog
{
	DECLARE_DYNAMIC(CBingoDialog)

public:
	CBingoDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CBingoDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_EDOYUN };
#endif
protected:
	CButton m_button;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	// 这是编辑框1的文本
	int m_value1;
	int m_value2;
	int m_value3;
	CRect m_large;
	CRect m_small;
	afx_msg void OnBnClickedOk();
	CEdit m_edit1;
	CEdit m_edit2;
	CEdit m_edit3;
	afx_msg void OnBnClickedBtnLarge();
};
