#pragma once
#include "afxwin.h"


// CEnvSet ��ȭ �����Դϴ�.

class CEnvSet : public CDialog
{
	DECLARE_DYNAMIC(CEnvSet)

public:
	CEnvSet(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CEnvSet();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_ENV };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CComboBox m_ctrComSel[2];
	virtual BOOL OnInitDialog();
};
