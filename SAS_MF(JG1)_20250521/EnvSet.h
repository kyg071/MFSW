#pragma once
#include "afxwin.h"
  
 
// CEnvSet 대화 상자입니다.

class CEnvSet : public CDialog
{
	DECLARE_DYNAMIC(CEnvSet)

public:
	CEnvSet(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CEnvSet();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_ENV };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
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
