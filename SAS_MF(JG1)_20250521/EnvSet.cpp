// EnvSet.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "SAS_1.h"
#include "EnvSet.h"
#include "math.h"

#include "TestProc.h"

extern CTestProc Test;// Doc  


// CEnvSet ��ȭ �����Դϴ�.

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





// CEnvSet �޽��� ó�����Դϴ�.

//void CEnvSet::OnBnClickedOk()
//{
//	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
//	OnOK();
//
//}

BOOL CEnvSet::OnInitDialog()
{
	CDialog::OnInitDialog();
 
	UpdateData(FALSE);	// varialbe to control

 

	//++ ������ ���� ������ ���¸� ��ȯ�մϴ�.
//	AxmSignalIsServoOn(0, &dwOnOff);
//
//	SmcWGetCtrlInOutStatus()
	short dwOnOff = 0;
	SmcWGetDigitalOut(Test.m_hSMCID, 1, &dwOnOff);//CSMC_OUT1
 	CheckDlgButton(IDC_CHK_SERVO_ON, dwOnOff & CSMC_OUT1);
//	Test.SerVo(ON);


	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

//void CEnvSet::OnBnClickedCancel()
//{
//	InitData();
//	UpdateData(FALSE);	// varialbe to control 
// 
//}


 
 

void CEnvSet::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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
 

	//++ ���� ���� Servo On/Off ��ȣ�� ����մϴ�.
//	AxmSignalServoOn(0, dwOnOff);
}
