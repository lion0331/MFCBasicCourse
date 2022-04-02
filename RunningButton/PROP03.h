#pragma once


// PROP_03 对话框

class PROP_03 : public CPropertyPage
{
	DECLARE_DYNAMIC(PROP_03)

public:
	PROP_03();
	virtual ~PROP_03();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROP_03 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 薪资范围
	CString m_money;
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
};
