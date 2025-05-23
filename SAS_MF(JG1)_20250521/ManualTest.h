#pragma once

#include "ColorStaticST.h"
#include "led.h"
#include "JogButton.h"




// CManualTest 대화 상자입니다.

class CManualTest : public CDialog
{
	DECLARE_DYNAMIC(CManualTest)

public:
	CManualTest(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualTest();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_MANUAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	bool m_bRUN;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);


	CColorStaticST m_stcTitle[8];
	CColorStaticST m_stcValue[8];
//	CFont m_CFont;

	CFont m_cFont;
	virtual BOOL OnInitDialog();
	void MakeScreen(void);
	afx_msg void OnBnClickedButton1();

	CLed mLed[26];
	CLed mSLed;
	CLed mSAlarm;

 
	afx_msg void OnBnClickedBtnoffset();
	afx_msg void OnBnClickedBtninitial();
	afx_msg void OnBnClickedBtnreset();
	void C_CAN_out(DWORD dwID,BYTE data);
	void TurnAngleDisplay(void);
//	afx_msg void OnBnClickedButton2();
//	afx_msg void OnStnClickedTurnvalue5();
	afx_msg void OnBnClickedBtnspeed();
	int m_iSpeed;
 
	BOOL m_bCID;
	afx_msg void OnBnClickedBtnpoweron();
	afx_msg void OnBnClickedBtnpoweroff();





	CJogButton m_jogBtnCW;
	CJogButton m_jogBtnCCW;
	afx_msg LRESULT OnJogBtnDn(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnJogBtnUp(WPARAM wParam, LPARAM lParam);


	long lOutPulse, lCountPulse, dwRet;
	short m_LimitSts, MotStatus;

	void SetDlgItemDouble(int nID, double value, int nPoint = 2);
	int GetDlgItemint(int nID);
	void SetDlgItemint(int nID, double value, int nPoint=2);
	double GetDlgItemDouble(int nID);


	afx_msg void OnBnClickedBtnCcw();
	afx_msg void OnBnClickedBtnCw();

	long m_lCountPulse;
	double m_dServoAngle;
	void On_STN_click(UINT nID);

	afx_msg void OnBnClickedBtnset();
};
