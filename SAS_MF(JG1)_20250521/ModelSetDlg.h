#if !defined(AFX_MODELSETDLG_H__601639F6_9C85_4CE6_9461_4E49AC10C24D__INCLUDED_)
#define AFX_MODELSETDLG_H__601639F6_9C85_4CE6_9461_4E49AC10C24D__INCLUDED_
 
#pragma once
 
// ModelSetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////

// CModelSetDlg 대화 상자입니다.




class CModelSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CModelSetDlg)
// Construction
public:
	CModelSetDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CModelSetDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MODEL_SPEC_SET_DLG };


 
	CListBox	m_List;
	CString	m_strCheckVersion;
	CString	m_strConnectDelayTime;
	CString	m_strCurrentConsumtion;
	CString	m_strMFSWID;
	CString	m_strDelayOffsetTime;
	CString	m_strDifferAngleOffset;
	CString	m_strHysteresis;
	CString	m_strNonlinearity;
	CString	m_strNonlinearityOffset;
	CString	m_strTBID;
	CString	m_strTorque;
	CString	m_strTorqueOffset;
	CString	m_strVCID;
	CString	m_strVersionHigh;
	CString	m_strVersionLow;
	CString	m_strAngleHigh;
	CString	m_strAngleLow;
	CString	m_strSpeedByte;
	CString	m_strVersionHighByte;
	CString	m_strVersionLowByte;
	//}}AFX_DATA

	CString m_strResetData[8];
	CString m_strIniData[8];
	CString m_strOffsetData[8];
	CString m_strVerCheckData[8];
	CString m_strOffsetAngle[7];
	CString m_strMesAngleStart[20];
	CString m_strMesAngleEnd[20];
	CString m_strMesSpeedStart[20];
	CString m_strMesSpeedEnd[20];
	CString m_strOffsetSpeed;
public:
	void GetModelDataFile();
// Overrides
 
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModelSetDlg)
	afx_msg void OnNewBut();
	afx_msg void OnSaveBut();
	afx_msg void OnDeleteBut();
//	virtual void OnOK();
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()







public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedSetBtn();
	void GetValue();
	void ModelValueDisplay(void);
};


#endif // !defined(AFX_MODELSETDLG_H__601639F6_9C85_4CE6_9461_4E49AC10C24D__INCLUDED_)

