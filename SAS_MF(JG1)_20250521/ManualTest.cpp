// ManualTest.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SAS_1.h"
#include "TestProc.h"
#include "ManualTest.h"

extern CTestProc Test;
// CManualTest 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualTest, CDialog)

CManualTest::CManualTest(CWnd* pParent /*=NULL*/)
	: CDialog(CManualTest::IDD, pParent)
	, m_bRUN(false)
	, m_dServoAngle(0)
	, m_iSpeed(0)
	, m_bCID(FALSE)
{
	printf("\nCManualTest()-------->");

}

CManualTest::~CManualTest()
{
	m_cFont.DeleteObject();
}

void CManualTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CManualTest)
	DDX_Control(pDX, IDC_BTN_JOG_MOVE_P, m_jogBtnCW);
	DDX_Control(pDX, IDC_BTN_JOG_MOVE_N, m_jogBtnCCW);	// match 되야 event 발생 한다.

 
	int i;
	for (i=0;i<4;i++)
	{
		DDX_Control(pDX, IDC_LED_O1+i, mLed[i]);
	}
/* 
	//
	//
	for (i=4;i<26;i++)
	{
		//		DDX_Control(pDX, IDC_LED_O16+i-4, mLed[i]);
		DDX_Control(pDX, IDC_LED_O16+i-4, mLed[i]);
	}

	DDX_Control(pDX,IDC_LED_O5,mSLed);	// 2014.11.24 추가 servo alarm
	DDX_Control(pDX,IDC_LED_O4,mSAlarm);	// 2014.11.24 추가 servo alarm

	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT1, m_iSpeed);
	DDX_Radio(pDX, IDC_RADIO1, m_bCID);
*/
}


BEGIN_MESSAGE_MAP(CManualTest, CDialog)
	//{{AFX_MSG_MAP(CManualTest)

	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CManualTest::OnBnClickedButton1)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_LED_O1, IDC_LED_O4, On_STN_click)

	ON_BN_CLICKED(IDC_BTNOFFSET, &CManualTest::OnBnClickedBtnoffset)
	ON_BN_CLICKED(IDC_BTNINITIAL, &CManualTest::OnBnClickedBtninitial)
	ON_BN_CLICKED(IDC_BTNRESET, &CManualTest::OnBnClickedBtnreset)
  
ON_BN_CLICKED(IDC_BtnPowerOn, &CManualTest::OnBnClickedBtnpoweron)
ON_BN_CLICKED(IDC_BtnPowerOff, &CManualTest::OnBnClickedBtnpoweroff)

ON_MESSAGE(UM_JOG_BTN_DN, OnJogBtnDn)
ON_MESSAGE(UM_JOG_BTN_UP, OnJogBtnUp)

ON_BN_CLICKED(IDC_BTN_CCW, &CManualTest::OnBnClickedBtnCcw)
ON_BN_CLICKED(IDC_BTN_CW, &CManualTest::OnBnClickedBtnCw)
ON_BN_CLICKED(IDC_BTNSET, &CManualTest::OnBnClickedBtnset)
END_MESSAGE_MAP()
		//}}AFX_MSG


// CManualTest 메시지 처리기입니다.

BOOL CManualTest::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
//		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		if(pMsg->wParam == VK_ESCAPE)
			return TRUE;
		if(pMsg->wParam == VK_RETURN )
		{
	 		return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}



BOOL CManualTest::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	SetDlgItemDouble(IDC_EDT_JOG_VEL, 10.0);// RPM 1 sec 72000 pulse
	SetDlgItemDouble(IDC_EDT_JOG_ACC, 20.0);
	SetDlgItemDouble(IDC_EDT_JOG_DEC, 20.0);
	SetDlgItemDouble(IDC_EDT_MOVE_DIS, 360.0,1);
 
 	MakeScreen();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CManualTest::MakeScreen(void)
{
	int i;

	m_cFont.CreateFont (20, // 글자높이 45
						0, // 글자너비
						0, // 출력각도
						0, // 기준 선에서의각도
						0,//FW_HEAVY, // 글자굵기
						FALSE, // Italic 적용여부
						FALSE, // 밑줄적용여부
						FALSE, // 취소선적용여부
						DEFAULT_CHARSET, // 문자셋종류
						OUT_DEFAULT_PRECIS, // 출력정밀도
						0,//CLIP_DEFAULT_PRECIS, // 클리핑정밀도
						0,//DEFAULT_QUALITY, // 출력문자품질
						DEFAULT_PITCH, // 글꼴Pitch
						_T("굴림체") // 글꼴
						);
  
	for(i=0;i<3;i++)	//4
	{
		m_stcTitle[i].SubclassDlgItem(IDC_TITLE1+i*2,this);
		m_stcValue[i].SubclassDlgItem(IDC_VALUE1+i*2,this);
		m_stcTitle[i].SetBkColor(RGB(10,80,100));
		m_stcTitle[i].SetTextColor(RGB(255,255,255));
		m_stcValue[i].SetBkColor(RGB(0,0,0));
		m_stcValue[i].SetTextColor(RGB(255,255,255));
		m_stcTitle[i].SetFont(&m_cFont);
		m_stcValue[i].SetFont(&m_cFont);
	}
 

}


void CManualTest::OnTimer(UINT_PTR nIDEvent)
{
/* 
		dwRetCode = AxmMoveVel(0, -dJogVel, dJogAcc, dJogDec);
		if(dwRetCode != AXT_RT_SUCCESS){
			strData.Format("AxmMoveVel return error[Code:%04d]", dwRetCode);
			MessageBox(strData, "Error", MB_OK | MB_ICONERROR);
		}
*/		
					
//	double dServoAngle = m_clMC.GetFeedBackPos(); //	AxmStatusGetActPos(m_lAxisNo, &dActPos);
//	dActPos = -0.01 * dActPos ;// *           *360/7200.00000;
	CString str;
	DOUBLE dActPos;
	DWORD data=0,dwData=0;
	short OutVal;
	int i;
	switch(nIDEvent)
	{
	case 5:
		Test.SerVoReset(OFF);
		KillTimer(nIDEvent);
		break;
	case TM_MANUAL:
		;
		SmcWGetCountPulse(Test.m_hSMCID, 1, &m_lCountPulse);
		dActPos = m_lCountPulse;
		m_dServoAngle = dActPos/100.;

	 
//		dwRecCode= AxmStatusGetActPos(0,&dActPos);//;pMDlg->m_clMC.GetFeedBackPos(); 2014.12.09 추가변경
/* 		if (AxmStatusGetActPos(0, &dActPos) == AXT_RT_SUCCESS)//;pMDlg->m_clMC.GetFeedBackPos();
		{
			m_dServoAngle=-PULSE2ANG * dActPos;	// 반대로 표시  
			str.Format("%.2lf",m_dServoAngle);
//			printf("\n%.2lf  %.1f",dActPos * 0.9,dActPos);
//
		}
		else
			str="---";
*/
		str.Format("%.1lf", m_dServoAngle);
		m_stcValue[0].SetWindowTextA(str);
		if (pMDlg->m_dAngle >= 3276.7)
			str = "ERROR";
		else
			str.Format("%.1lf", pMDlg->m_dAngle);

		m_stcValue[1].SetWindowTextA(str);

		str.Format("%d", pMDlg->m_bSAS_Status);
		m_stcValue[2].SetWindowTextA(str);
 
		SmcWGetDigitalOut(Test.m_hSMCID, 1, &OutVal);
 		//	mLed[0].SetStatus(OutVal & S_ON);
  	// 	mLed[1].SetStatus(OutVal & 1);	// servo Error flag

		for (i = 0; i < 2; i++)
			mLed[i].SetStatus(OutVal & (1 << i));
 		SmcWGetDigitalOut(Test.m_hSMCID, 4, &OutVal);//CSMC_OUT1
		mLed[2].SetStatus(OutVal & 1);	// B PLUS
		mLed[3].SetStatus(OutVal & 2);	// ign1,2

	//	mLed[2].SetStatus(1);


 //
//		AxmSignalIsServoOn(0,&dwData);
//		mLed[3].SetStatus(dwData);
// servo alarm 신호의 상태를 확인. 2014.11.24
/* 		if (AxmSignalReadServoAlarm(0, &data) == AXT_RT_SUCCESS)
		{
			mSLed.SetStatus(data);
		}
		//
		if(AxmSignalReadOutputBit(0,1,&dwData)==AXT_RT_SUCCESS)
		{
			mSAlarm.SetStatus(dwData);
			if(dwData)
			{
				if(data==0)
				{
					AxmSignalWriteOutputBit(0,1,data);		// auto clear
				}
			}
		}
		AxdoNReadOutportWord(0, Do_0, 0, &dwData);				
		AxdoNReadOutportWord(0, Do_1, 0, &dwData);
		AxdoNReadOutportWord(0, Do_1, 1, &data);
*/		 
 
		break;
	default:
		KillTimer(nIDEvent);
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

/*

		m_clMC.RdoAbsRelMode(0);		// 0 abs,  1 =rel mode 설정
	AxmStatusSetCmdPos(m_lAxisNo, 0.0);
	AxmStatusSetActPos(m_lAxisNo, 0.0);		


	*/
void CManualTest::OnBnClickedButton1()
{
	SmcWSetCountPulse(Test.m_hSMCID, 1, 0);

//	pMDlg->m_clMC.RdoAbsRelMode(0);
//	pMDlg->m_clMC.Position_Reset();
//	AxmStatusSetCmdPos(0, 0.0);
//	AxmStatusSetActPos(0, 0.0);		

}


void CManualTest::OnBnClickedBtninitial()
{
	if (pMDlg->m_iRunMode == 0)
		pMDlg->m_iRunMode = 2;
}


void CManualTest::OnBnClickedBtnoffset()
{
	//	BYTE send[8] = { 0x04,0x2E,0xF3,0x53,0x00,0x00,0x00,0x00 };// caribration

	if (pMDlg->m_iRunMode == 0)
		pMDlg->m_iRunMode = 3;

}


void CManualTest::OnBnClickedBtnreset()
{
	if (pMDlg->m_iRunMode == 0)
		pMDlg->m_iRunMode = 4;
}

// 사용 하는 곳 없다.

void CManualTest::C_CAN_out(DWORD dwID,BYTE data)
{
	BYTE send[8];
	unsigned int i;
	for(i=0;i<8;i++)
	{
		send[i]=0;
	}
	send[0]=data;
	pMDlg->CanSend(dwID,8,send);
}

// left right angle display
void CManualTest::TurnAngleDisplay(void)
{
//
	CString str;
	if(pMDlg->m_dLeftOnAngle==NOT_READ)
		str="----";
	else
		str.Format("%.1f",pMDlg->m_dLeftOnAngle);
	m_stcValue[4].SetWindowTextA(str);

	if(pMDlg->m_dLeftOffAngle==NOT_READ)
		str="----";
	else
		str.Format("%.1f",pMDlg->m_dLeftOffAngle);
	m_stcValue[5].SetWindowTextA(str);

	if(pMDlg->m_dRightOnAngle==NOT_READ)
		str="----";
	else
		str.Format("%.1f",pMDlg->m_dRightOnAngle);
	m_stcValue[6].SetWindowTextA(str);
//
	if(pMDlg->m_dRightOffAngle==NOT_READ)
		str="----";
	else
		str.Format("%.1f",pMDlg->m_dRightOffAngle);

	m_stcValue[7].SetWindowTextA(str);

}
 

void CManualTest::OnBnClickedBtnspeed()
{
	UpdateData(true);		// control to value
 
}

 

void CManualTest::On_STN_click(UINT nID)
{
	UINT num = nID - IDC_LED_O1;
	short OutSta;
 
	switch (nID)
	{
	case IDC_LED_O1:
		SmcWGetDigitalOut(Test.m_hSMCID, 1, &OutSta);//CSMC_OUT1
		if (OutSta & CSMC_OUT1)
 			Test.SerVo(OFF);
  		else 
			Test.SerVo(ON);
 		break;

	case IDC_LED_O2:
		SmcWGetDigitalOut(Test.m_hSMCID, 1, &OutSta);//CSMC_OUT1
		if (OutSta & CSMC_OUT2)
			Test.SerVoReset(OFF);
		else
		{
			Test.SerVoReset(ON);
			SetTimer(5, 500, NULL);
 		}
		break;

	case IDC_LED_O3:
		SmcWGetDigitalOut(Test.m_hSMCID, 4,&OutSta);//CSMC_OUT1
		if (OutSta & CSMC_OUT1)
		{
			Test.BPlus(OFF);
			Test.IGN1(OFF);
			Test.IGN2(OFF);
 		}
		else
		{
			Test.BPlus(ON);
			Test.BCanCon(ON, ON);
			Test.CCanCon(ON, ON);
 		}
		break;

	case IDC_LED_O4:
		SmcWGetDigitalOut(Test.m_hSMCID, 4, &OutSta);//CSMC_OUT1
		if (OutSta & CSMC_OUT2)
		{
			Test.IGN1(OFF);
			Test.IGN2(OFF);
 		}
		else
		{
			Test.IGN1(ON);
			Test.IGN2(ON);

		}
	}
 
}




void CManualTest::OnBnClickedBtnpoweron()
{
	Test.BCanCon(ON, ON);
	Test.CCanCon(ON, ON);
	Test.BPlus(ON);
	Test.IGN1(ON);
	Test.IGN2(ON);
	Sleep(100);
	pMDlg->m_cCCan.FlashReadBuffer();


}


void CManualTest::OnBnClickedBtnpoweroff()
{
	Test.BPlus(OFF);
	Test.IGN1(OFF);
	Test.IGN2(OFF);

}

// ++ =======================================================================
// >> GetDlgItemDouble(...) : 지정한 콘트롤에 설정되어 있는 텍스트를 
//    double값으로 변환하여 반환하는 함수.
//  - Edit, Static 콘트롤에 설정된 텍스트를 double값으로 읽어들여 코드를 간결
//    하게 구현할 수 있습니다.
// --------------------------------------------------------------------------
double CManualTest::GetDlgItemDouble(int nID)
{
	double dRet;
	CString sTemp;
	GetDlgItem(nID)->GetWindowText(sTemp);
	dRet = atof((LPCTSTR)sTemp);
	return dRet;
}

// ++ =======================================================================
// >> SetDlgItemDouble(...) : double값을 지정한 콘트롤에 설정하는 함수.
//  - 설정한 콘트롤의 ID와 double값을 입력합니다. 이때 표현 할 소숫점 자릿수를
//    지정할 수 있습니다. (기본은 소숫점 3자리로 지정됨)
//  - Edit, Static 콘트롤에 사용할 수 있으며 double값을 입력하면되므로 코드를
//    간결하게 구현할 수 있습니다.
// --------------------------------------------------------------------------

void CManualTest::SetDlgItemDouble(int nID, double value, int nPoint)
{
	CString sTemp, sTemp2;
	sTemp2.Format("%%.%df", nPoint);
	sTemp.Format(sTemp2, value);
	GetDlgItem(nID)->SetWindowText(sTemp);

}


int CManualTest::GetDlgItemint(int nID)
{
	int iRet;
	CString sTemp;
	GetDlgItem(nID)->GetWindowText(sTemp);
	iRet = atoi((LPCTSTR)sTemp);

	return iRet;
}

void CManualTest::SetDlgItemint(int nID, double value, int nPoint)
{
	CString sTemp, sTemp2;
	sTemp2.Format("%d", nPoint);
	sTemp.Format(sTemp2, value);
	GetDlgItem(nID)->SetWindowText(sTemp);

}

// ++ =======================================================================
// >> OnJogBtnDn(...) : "Jog Move(+/-)"버튼 Down시 호출되는 핸들러 함수.
//  - "CJogButton" 버튼 클래스에서 버튼 클릭시 호출되는 WM_LBUTTONDOWN 이벤트를 
//    받아 사용자 이벤트로 이 함수를 호출해 줍니다. 이 때 wParam을 통해 전달되는
//    콘트롤 ID로 Jog(+/-)버튼을 구분하게 됩니다.
//  - Jog버튼 Down시 연속구동 함수를 호출하여 Jog 구동을 시작합니다.
// --------------------------------------------------------------------------
LRESULT CManualTest::OnJogBtnDn(WPARAM wParam, LPARAM lParam)
{
	CString strData;
	DWORD	dwRetCode;
	double	dJogVel, dJogAcc, dJogDec;



	dJogVel = fabs(GetDlgItemDouble(IDC_EDT_JOG_VEL));
	dJogAcc = fabs(GetDlgItemDouble(IDC_EDT_JOG_ACC));
	dJogDec = fabs(GetDlgItemDouble(IDC_EDT_JOG_DEC));

	dJogVel = dJogVel * 1200;
 
	SmcWSetTargetSpeed(Test.m_hSMCID, 1, dJogVel);
	SmcWSetAccelTime(Test.m_hSMCID, 1, dJogAcc);
	SmcWSetDecelTime(Test.m_hSMCID, 1, dJogDec);
	SmcWSetResolveSpeed(Test.m_hSMCID, 1, 10);


	switch (wParam)
	{
	case IDC_BTN_JOG_MOVE_P:
		//++ 지정한 축을 (+)방향으로 지정한 속도/가속도/감속도로 모션구동합니다.
	/* 	dwRetCode = AxmMoveVel(0, -dJogVel, dJogAcc, dJogDec);
		if(dwRetCode != AXT_RT_SUCCESS){
			strData.Format("AxmMoveVel return error[Code:%04d]", dwRetCode);
			MessageBox(strData, "Error", MB_OK | MB_ICONERROR);
		}
	*/
	//	printf("\nJOG MOVE P");
		dwRet = SmcWSetReady(Test.m_hSMCID, 1, CSMC_JOG, CSMC_CCW);
		dwRet = SmcWMotionStart(Test.m_hSMCID, 1);
		break;

	case IDC_BTN_JOG_MOVE_N:
		//++ 지정한 축을 (-)방향으로 지정한 속도/가속도/감속도로 모션구동합니다.
	/* 	dwRetCode = AxmMoveVel(0, dJogVel, dJogAcc, dJogDec);
		if(dwRetCode != AXT_RT_SUCCESS){
			strData.Format("AxmMoveVel return error[Code:%04d]", dwRetCode);
			MessageBox(strData, "Error", MB_OK | MB_ICONERROR);
		}
	*/
		dwRet = SmcWSetReady(Test.m_hSMCID, 1, CSMC_JOG, CSMC_CW);
		dwRet = SmcWMotionStart(Test.m_hSMCID, 1);
	//	printf("\nJOG MOVE N");

		break;
	}

	return 0;
}

// ++ =======================================================================
// >> OnJogBtnUp(...) : "Jog Move(+/-)"버튼 Up시 호출되는 핸들러 함수.
//  - "CJogButton" 버튼 클래스에서 버튼 클릭시 호출되는 WM_LBUTTONUP이벤트를 
//    받아 사용자 이벤트로 이 함수를 호출해 줍니다. 이 때 wParam을 통해 전달되는
//    콘트롤 ID로 Jog(+/-)버튼을 구분하게 됩니다.
//  - Jog버튼 Up시 구동정지 함수를 호출하여 Jog 구동을 종료합니다.
// --------------------------------------------------------------------------
LRESULT CManualTest::OnJogBtnUp(WPARAM wParam, LPARAM lParam)
{
	//++ 지정한 축의 Jog구동(모션구동/원점검색구동)을 감속정지합니다.
//	AxmMoveSStop(0);	
// resul 10
// Speed 72000 하면 1초에 한바퀴.


//	SmcWMotionDecStop(Test.m_hSMCID, 1);
	SmcWMotionStop(Test.m_hSMCID, 1);
	switch (wParam)
	{
	case IDC_BTN_JOG_MOVE_P:
//		printf("    IDC_BTN_JOG_MOVE_P");

		break;
	case IDC_BTN_JOG_MOVE_N:
//		printf("    IDC_BTN_JOG_MOVE_N");
		break;
	}
	return 0;
}







void CManualTest::OnBnClickedBtnCcw()
{
	double	dJogVel, dJogAcc, dJogDec;
	double dtemp;

	dJogVel = fabs(GetDlgItemDouble(IDC_EDT_JOG_VEL));
	dJogAcc = fabs(GetDlgItemDouble(IDC_EDT_JOG_ACC));
	dJogDec = fabs(GetDlgItemDouble(IDC_EDT_JOG_DEC));
	dtemp = fabs(GetDlgItemDouble(IDC_EDT_MOVE_DIS));

	dJogVel = dJogVel * 1200;
	SmcWMotionStop(Test.m_hSMCID, 1);
	SmcWSetTargetSpeed(Test.m_hSMCID, 1, dJogVel);
	SmcWSetAccelTime(Test.m_hSMCID, 1, dJogAcc);
	SmcWSetDecelTime(Test.m_hSMCID, 1, dJogDec);
	SmcWSetResolveSpeed(Test.m_hSMCID, 1, 10);
	
	long lDistance;

	lDistance = (long)(dtemp * 100. * 1.);
	lDistance = -1 * (lDistance);
	dwRet = SmcWSetStopPosition(Test.m_hSMCID, 1, CSMC_INC, lDistance);

	dwRet = SmcWSetReady(Test.m_hSMCID, 1, CSMC_PTP, CSMC_CCW);// turn right
	dwRet = SmcWMotionStart(Test.m_hSMCID, 1);

}

// 오른쪽
void CManualTest::OnBnClickedBtnCw()
{
	double	dJogVel, dJogAcc, dJogDec;
	double dtemp;
	long lDistance;
	short StopSts;
	dwRet = SmcWGetStopStatus(Test.m_hSMCID, 1, &StopSts);

 
	if (StopSts != CSMC_STOP_NORMAL)
		SmcWMotionStop(Test.m_hSMCID, 1);

	dJogVel = fabs(GetDlgItemDouble(IDC_EDT_JOG_VEL));
	dJogAcc = fabs(GetDlgItemDouble(IDC_EDT_JOG_ACC));
	dJogDec = fabs(GetDlgItemDouble(IDC_EDT_JOG_DEC));
	dtemp = fabs(GetDlgItemDouble(IDC_EDT_MOVE_DIS));
	
	SmcWMotionStop(Test.m_hSMCID, 1);


	dJogVel = dJogVel  * 1200;// dJogVel * 2 * 100;

	SmcWSetTargetSpeed(Test.m_hSMCID, 1, dJogVel);
	SmcWSetAccelTime(Test.m_hSMCID, 1, dJogAcc);
	SmcWSetDecelTime(Test.m_hSMCID, 1, dJogDec);
	SmcWSetResolveSpeed(Test.m_hSMCID, 1, 10);
	lDistance = (long)(dtemp * 100. * 1.);
//	lDistance = -1 * (lDistance);

	dwRet = SmcWSetStopPosition(Test.m_hSMCID, 1, CSMC_INC, lDistance);


	dwRet = SmcWSetReady(Test.m_hSMCID, 1, CSMC_PTP, CSMC_CW);
	dwRet = SmcWMotionStart(Test.m_hSMCID, 1);


}


void CManualTest::OnBnClickedBtnset()
{
	long CountPulse;
	CountPulse= (long)(pMDlg->m_dAngle *100.);
  	SmcWSetCountPulse(Test.m_hSMCID, 1, CountPulse);

}
