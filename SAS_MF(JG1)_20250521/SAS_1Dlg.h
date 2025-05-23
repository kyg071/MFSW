
// SAS_1Dlg.h : 헤더 파일
//

#pragma once

#include <afxwin.h>
#include <xlsxwriter.h>


#include "afxcmn.h"		//
#include "envset.h"
#include "modelsetdlg.h"

#include "sasautotest.h"
#include "manualTest.h"
 
#include "KvaserCan.h"

//#include "EzMotion.h"
//#include "commThread.h"
//#include "comm.h"
#include "afxcoll.h"


#include <iostream>
#include <string>
#include <afxconv.h>    // CA2T

//extern CSAS_1Dlg *pMDlg;

// CSAS_1Dlg 대화 상자
class CSAS_1Dlg : public CDialog
{
// 생성입니다.
public:
	CSAS_1Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	~CSAS_1Dlg();	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SAS_1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedOk();

	ULONG_PTR g_GdiPlusTokenBoxData;
	CTabCtrl m_Tab;


	MODEL m_Model;		//
	MODEL m_SelModel;		// 선택된

	CEnvSet *p_mEnvSet;
	CModelSetDlg *p_mModelSet;
 	CManualTest *p_mManualT;
 	CSASAutoTest *p_mSasAuTest;

	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangingTab1(NMHDR *pNMHDR, LRESULT *pResult);
	int m_CurTabNum;

// 측정관련값.

	clock_t m_tStart;
	clock_t m_tCanRev;
	DWORD m_dwStart;
	DWORD m_dwCanRev;
//	double m_dReadCur;
//	double m_dCurServoAngle;
	BOOL m_fValidData;
	BOOL m_fMesCur;
	double *m_pdSASAngle;
	double *m_pdServoAngle;
	double *m_pdSpeed;
	double *m_pdDifferAngle;
 
	CanMsg m_CanData;

	pCanMsg m_pCanData;

//	long mlCurrentPos;

	unsigned long m_lConnTime;




	unsigned long *m_pdTime;
	unsigned long m_ulMesMaxCount;
//	unsigned long m_ulBufferCnt;
	unsigned long m_ulTime;
	unsigned long m_ulCurCnt;
	unsigned long m_ulDrawCnt;
	BOOL m_fMesDataSave;
	BOOL m_fCanEnable;
	CTime m_tStartTest;

	int m_iGoodCnt[2];
	int m_iNGCnt[2];
	int m_iTestCnt[2];

	unsigned int m_iCindex;

 //	CEzMotion m_clMC;



 
//	CCommThread m_pCommT[2];
 
//	CANMSG m_sCanMsg[100];

//	CANMSG m_sLowCanMsg[10];

	unsigned int m_uiHead,m_uiOldHead;
	unsigned int m_uiLowHead;

/* 
	CUSBCAN m_CCan;
	CUSBCAN m_lowCan;
*/

	CKvaserCan m_cCCan, m_cCRCan;
	CKvaserCan m_cBCan;




	CString m_strModelFileName;

	void ReadModel(CString strFileName);
	void SaveModel(CString strFileName);
	void DeleteModel(CString strFileName);
	int m_iRunMode;
	void TestRun(void);
	int Read_Current(double& dData);
	void LoadINI(void);
	void SaveIni(void);
	afx_msg LRESULT OnTraceUpdateMsg(WPARAM wParam, LPARAM lParam);
 	afx_msg LRESULT OnTraceStatusMsg(WPARAM wParam, LPARAM lParam);

	bool m_RunThread;
	void CanSend(DWORD dwID, int dlc, BYTE* pData,bool fLog=true);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void MakeMemory(int count);
	void ReadCnt(void);
	void SaveCnt(void);
	void WriteMesData(CString strFileName, CTime t, unsigned long dTime, double dServoA, double dSASA, double dDiffer, double dSpeed, double dCurrent);
	void WriteMesData1(CString strFileName, CTime t, unsigned long dTime, double dServoA, double dSASA, double dDiffer, double dSpeed, int i);
	void SaveMeaData(void);

	CString m_strReportFile;


	void UserStop(void);

	double m_dSASAngle;

//	CStringArray m_strCanMessageArray;
	bool m_bRightTurn;
	bool m_bLeftTurn;
	double m_dSASSpeed;
	double m_dLeftOnAngle,m_dLeftOffAngle;
	double m_dRightOnAngle,m_dRightOffAngle;
	double dServoAngle;			// 2015.01.08

 

	int m_LinMode;
	BYTE m_LinData[10];

	void LinValueSet(void);
	void SMC_Init(short ch=1, bool fMode=true);
	void DispComment(char* func, char* msg, short ch = 1);

	void PrintStr(CString String);

	LRESULT OnCanSASReceive(WPARAM wParam, LPARAM lParam);

	long dwRet;
	//	long Ret;
	char ErrorString[256];
	short PulseType, DirTimer;
	short EncType;
	short CtrlOut1, CtrlOut2, CtrlOut3;
	short CtrlIn;
	short OrgLog;
	short CtrlInOutLog;
	short ErcMode;
	short ErcTime, ErcOffTimer, AlmTime;
	short LimitTurn, OrgType, EndDir, ZCount;
	short SAccelType;
	short FilterType;
	short SDMode;
	short ClearCntLtc, LtcMode, ClearCntClr, ClrMode;
	short InitParam;

	short MotionType;
	double dblResolveSpeed;
	double dblStartSpeed;
	double dblTargetSpeed;
	double dblAccelTime;
	double dblDecelTime;
	double dblSSpeed;
	long lDistance;
	short bCoordinate;
	short m_sStartDir;




	void AG_MFSW(void);
	void Default_MFSW(void);
	void RJ_MFSW(void);
	CListBox m_ctlListBox;



	BYTE m_cData_SAS[32];

	short int m_iSASAngle;
	double m_dAngle;
	BYTE m_bSAS_Status;
 
	DWORD m_dwTxID;
	CString m_strSASAngle;
	CString m_strSASSpeed;



 
	void Security_Access();
	bool SetMoveParam(short ch);
	void DrawG();
	//int Motionxx(double dTargetSpeed, long distance, short ch, short Dir, short MotionType);

	int MoveCheck();

	 
	int Test_SAS_Send(int Num);

	int Test_Seq();

	int Test_SAS_Cal();




	UINT	wTimerRes;
	DWORD	timerID;
	bool m_bTimer;

	bool	m_fDrawOn;
	//
	BYTE m_CData_DIG[32];
	BYTE m_cData_mDIG[32][8];	// multy byte  
	BYTE m_cMultyTxData[8][8];			// multy byte  
	bool m_fMultyByte;
	bool m_fMultyTrans;
	int m_iMultyTransLen;
	BOOL m_fDiagRev;
	bool m_fDiagRevSing;
	bool m_fMultyRxDone;
	int  m_iMultyRxIndex;
	bool m_fConnectTimeCheck;

	afx_msg void OnBnClickedButton1();


private:
	// CString → UTF-8 std::string 변환 헬퍼
 	std::string Utf8FromCString(const CString& str);

public:
	afx_msg void OnBnClickedButton2();
};
