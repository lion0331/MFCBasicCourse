#pragma once


// PROP_02 对话框

class PROP_02 : public CPropertyPage
{
	DECLARE_DYNAMIC(PROP_02)

public:
	PROP_02();
	virtual ~PROP_02();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROP_02 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 工作技能
	BOOL m_skill[4];
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
};
