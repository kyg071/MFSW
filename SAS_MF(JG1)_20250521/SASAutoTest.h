

#ifndef _SASAUTOTEST_H_

#define _SASAUTOTEST_H_

#pragma once

#include "afxwin.h"
#define GraphControl

#ifdef GraphControl 
//#include "csGraph.h"
#include "graphctrl.h"
#endif
 
#ifdef GTEST
#include "ChartCtrl_source/ChartCtrl.h"
#include "ChartCtrl_source/ChartLineSerie.h"
#include "ChartCtrl_source/ChartCandlestickSerie.h"
#endif
// CSASAutoTest 대화 상자입니다.

class CSASAutoTest : public CDialog
{
	DECLARE_DYNAMIC(CSASAutoTest)

public:
	CSASAutoTest(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSASAutoTest();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_AUTO_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
 
public:


//
 

	CButton	m_butScroll;
	CEdit	m_editTXID;
	CEdit	m_editDLC;
	CButton	m_butSend;
	CEdit	m_editSend8;
	CEdit	m_editSend7;
	CEdit	m_editSend6;
	CEdit	m_editSend5;
	CEdit	m_editSend4;
	CEdit	m_editSend3;
	CEdit	m_editSend2;
	CEdit	m_editSend1;
	CEdit	m_editScale;
	
	CButton	m_butReport;

	CButton	m_butTotalReset;
	CButton	m_butTodayReset;
	CButton	m_butListClear;
	CButton	m_butOffsetCheck;

	CListBox	m_List;

	BOOL	m_fOffsetSkip;
	UINT	m_iDifferScale;
//	int m_iDifferScale;
	UINT	m_iDLC;
	CString	m_strTXID;
	BOOL	m_fScroll;
	//}}AFX_DATA
	CString m_strSend[8];









	CRect m_reMInfoBox;
	CRect m_reMInfoTitle;
	CRect m_reMInfoT[9];
	CRect m_reMInfoD[9];
	CString m_strMInfoT[9];
	CString m_strMInfoD[9];

	CRect m_rePosInfoBox;
	CRect m_rePosInfoTitle;
	CRect m_rePosInfoT[10];
	CRect m_rePosAS[10];
	CRect m_rePosAE[10];
	CRect m_rePosSP[10];
	CRect m_rePosPT[10];
	CString m_strPosAS[10];
	CString m_strPosAE[10];
	CString m_strPosSP[10];
	

	CRect m_rePInfoBox;
	CRect m_rePInfoTitle;
	CRect m_rePInfoT[3];
	CRect m_rePPT[2];
	CRect m_rePToday[3];
	CRect m_rePTotal[3];
	CString m_strPInfoT[3];
	CString m_strPToday[3];
	CString m_strPTotal[3];

	CRect m_reResetBut[2];
	int m_iResetButMode[2];

	CRect m_reMesInfoBox;
	CRect m_reMesInfoTitle;
	CRect m_reMesInfoT[8];
	CRect m_reMesInfoD[8];
	CString m_strMesInfoT[8];
	CString m_strMesInfoD[8];

	CRect m_reResultBox;
	CRect m_reResultTitle;
	CRect m_reResultT[8];
	CRect m_reResultD[8];
	CString m_strResultT[8];
	CString m_strResultD[8];
	
	CRect m_reJudgement;
	int m_iJudgeMode;
	CRect m_reTestTime;
	int m_iTestTime;
	
	int m_iReportMode;
	CRect m_reReportBut;
	CRect m_reReport;

 	CString m_strReportFile;

	CRect m_reMessageT;
	CRect m_reMessage;
	CString m_strMessage;		// 동일 message 표시 하지 않기 위하여서 ..

	
	int m_iRunMode;
	CRect m_reRunBut;
	int m_iStopMode;
	CRect m_reStopBut;

	CRect m_reList;
	CRect m_reListResetBut;

	CRect m_reGraphBox;
	CRect m_reGraph;
	CRect m_reLineColor[4];
	CRect m_reLineT[4];
	COLORREF m_colorL[4];

	clock_t m_tStart;
	clock_t m_tCanRev;
	DWORD m_dwStart;
	DWORD m_dwCanRev;
	double m_dReadCur;
//	double m_dCurServoAngle;
	BOOL m_fValidData;
//	BOOL m_fMesCur;
 
	unsigned long m_ulMesMaxCount;
//	unsigned long m_ulBufferCnt;
	unsigned long m_ulTime;
	unsigned long m_ulCurCnt;

	BOOL m_fMesDataSave;
	BOOL m_fCanEnable;
	CTime m_tStartTest;

	 

	void DrawButton(CDC *pDC, COLORREF bcolor, COLORREF fcolor, CRect rect, CString strTitle1, CString strTitle2,UINT txtAlign,int mode,int iHeight,int iWidth,int iRow);





	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnBnClickedListClearBut();
	afx_msg void OnBnClickedSendBut();
	afx_msg void OnBnClickedReportBut();
//	afx_msg void OnBnClickedTodayReset();
//	afx_msg void OnBnClickedTotalReset();

	void OutMessage(CString strData);
	void SetValueDisplay(void);
	void AddString(CString strData);
	void DrawGraph(int iPo);


	int iCenterY;
	int iCenterX;
	double dUnit;
	double dXUnit;
	double dXUnit1;

	int m_YStep;
	double m_dYRange;


	bool m_fDirCW;


	void CountDisplay(void);
	void GraphMake(void);

//	CCSGraph m_XYGraph;
 
#ifdef GraphControl
	CGraphCtrl m_Graph;
#endif

	CButton m_butCurrentCheck;
	BOOL m_fCurrentCheck;
	CButton m_cButZerrMove;
	BOOL m_fButZeroMove;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	CChartCtrl m_ChartCtrl;
};


#endif
