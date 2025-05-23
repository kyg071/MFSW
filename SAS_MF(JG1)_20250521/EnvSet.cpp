// EnvSet.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SAS_1.h"
#include "EnvSet.h"
#include "math.h"

#include "TestProc.h"

extern CTestProc Test;// Doc  


// CEnvSet 대화 상자입니다.

IMPLEMENT_DYNAMIC(CEnvSet, CDialog)

CEnvSet::CEnvSet(CWnd* pParent /*=NULL*/)
	: CDialog(CEnvSet::IDD, pParent)
{
 
}

CEnvSet::~CEnvSet()
{

 
}

void CEnvSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEnvSet)

 
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CEnvSet, CDialog)
	//{{AFX_MSG_MAP(CEnvSet)

 
	ON_WM_TIMER()
 
	//}}AFX_MSG
	ON_BN_CLICKED(IDC_CHK_SERVO_ON, &CEnvSet::OnBnClickedChkServoOn)
END_MESSAGE_MAP()





// CEnvSet 메시지 처리기입니다.

//void CEnvSet::OnBnClickedOk()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	OnOK();
//
//}

BOOL CEnvSet::OnInitDialog()
{
	CDialog::OnInitDialog();
 
	UpdateData(FALSE);	// varialbe to control

 

	//++ 지정한 축의 서보온 상태를 반환합니다.
//	AxmSignalIsServoOn(0, &dwOnOff);
//
//	SmcWGetCtrlInOutStatus()
	short dwOnOff = 0;
	SmcWGetDigitalOut(Test.m_hSMCID, 1, &dwOnOff);//CSMC_OUT1
 	CheckDlgButton(IDC_CHK_SERVO_ON, dwOnOff & CSMC_OUT1);
//	Test.SerVo(ON);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//void CEnvSet::OnBnClickedCancel()
//{
//	InitData();
//	UpdateData(FALSE);	// varialbe to control 
// 
//}


 
 

void CEnvSet::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int i;	
	DWORD data,dwData=0;
	switch(nIDEvent)
	{
	
	case TM_ENV:
		break;
	}

	KillTimer(nIDEvent);
	CDialog::OnTimer(nIDEvent);
}

BOOL CEnvSet::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_ESCAPE)
			return TRUE;
		if(pMsg->wParam == VK_RETURN )
		{
	 		return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


 
 
void CEnvSet::OnBnClickedChkServoOn()
{
	short dwOnOff = 0;

/* 	
	SmcWGetDigitalOut(Test.m_hSMCID, 1, &dwOnOff);//CSMC_OUT1
	CheckDlgButton(IDC_CHK_SERVO_ON, dwOnOff & CSMC_OUT1);
*/
	
	dwOnOff = IsDlgButtonChecked(IDC_CHK_SERVO_ON);
	Test.SerVo(dwOnOff);
 

	//++ 지정 축의 Servo On/Off 신호를 출력합니다.
//	AxmSignalServoOn(0, dwOnOff);
}
