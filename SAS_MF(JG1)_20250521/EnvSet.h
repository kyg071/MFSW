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
	// Generated message map functions
	//{{AFX_MSG(CEnvSet)

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
//	CIPAddressCtrl m_ipAddr;
 
	virtual BOOL OnInitDialog();
 
 
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
 
	afx_msg void OnBnClickedChkServoOn();




	long lOutPulse, lCountPulse, dwRet;
	short m_LimitSts, MotStatus;







};
