﻿
// RunningButtonDlg.h: 头文件
//

#pragma once
#include "CMyButton.h"


// CRunningButtonDlg 对话框
class CRunningButtonDlg : public CDialogEx
{
// 构造
public:
	CRunningButtonDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RUNNINGBUTTON_DIALOG };
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
	CMyButton m_btn_right;
	CMyButton m_btn_left;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedBtnQuery();
};
