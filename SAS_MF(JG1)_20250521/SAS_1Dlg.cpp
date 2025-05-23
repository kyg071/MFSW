
// SAS_1Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "SAS_1.h"
#include "SAS_1Dlg.h"


#include <conio.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h>
 
#define MESSAGE_TYPE_SINGLE_VALUE               0u
#define MESSAGE_TYPE_FIRST_VALUE                1u
#define MESSAGE_TYPE_CONSECUTIVE_VALUE          2u
#define MESSAGE_TYPE_FLOW_VALUE                 3u


#include "TestProc.h"

//#define DIS_TYPE1
CTestProc Test;// Doc  


/* 
#ifdef _M_X64
	#pragma comment(lib, "../../../../AXLNet(Library)/Library/64Bit/AXLNet.lib")		// Library Link
#else
//	#pragma comment(lib, "../../../../AXLNet(Library)/Library/32Bit/AXLNet.lib")		// Library Link
#endif
 */

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define TARGET_RESOLUTION	(int)10	// 10 msec

static void CALLBACK TimeProc(UINT _timerid, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	CSAS_1Dlg* pDlg = (CSAS_1Dlg*)dwUser;
//	CSAS_1Dlg* pView = (CLX3TSWView*)dwUser;
 
	pDlg->DrawG();
	//	if (pView->m_bTestDraw)
	{
		//	pView->DrawG();
	}

}



DWORD TestProcess(LPVOID lpData);




DWORD TestProcess(LPVOID lpData)
{
	//	CSASTesterView *pView = (CSASTesterView *)lpData;
	CSAS_1Dlg* pDlg = (CSAS_1Dlg*)lpData;

	//	while(1)
	while (pDlg->m_RunThread)
	{
		switch (pDlg->m_iRunMode)
		{
		case 1:
			pDlg->TestRun();
			pDlg->m_iRunMode = 0;
			pDlg->p_mSasAuTest->m_iRunMode = 0;
			pDlg->p_mSasAuTest->m_iStopMode = 1;
			break;
		case 2:
		case 3:
		case 4:
			pDlg->Test_SAS_Send(pDlg->m_iRunMode);
			pDlg->m_iRunMode = 0;
			break;
		case 0:
			pDlg->m_iRunMode = 0;
			break;
		default:

			break;
 		}
		Sleep(10);
	}

	return 0;
}

/*
	10msec time delay

*/



 
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
 
//CSAS_1Dlg *pMDlg;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)

END_MESSAGE_MAP()


// CSAS_1Dlg 대화 상자


//CSAS_1App *pApp;


CSAS_1Dlg::CSAS_1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSAS_1Dlg::IDD, pParent)
	, m_CurTabNum(0)
	, m_strModelFileName(_T(""))
	, m_iRunMode(0)
	, m_RunThread(false)
	, m_bRightTurn(false)
	, m_bLeftTurn(false)
	, m_LinMode(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

/*
	GdiplusStartupInput GdiplusStartupInput;
	GdiplusStartup(&g_GdiPlusTokenBoxData,&GdiplusStartupInput,NULL);
*/	
	
	printf("\n (1) SAS_1Dlg::CSAS_1Dlg() 생성 ");
	m_iCindex = 0;

	m_ulCurCnt= m_ulDrawCnt=0;
//	m_ulMesMaxCount=200;

//	count = 20000;	// 200 초 
//	count = 10000;	// 100 초 
	m_ulMesMaxCount = MAX_DATA;	// 7200 이면 된다...

	 
	printf("    SAS_1Dlg::CSAS_1Dlg() 변수  ");
 
	m_pCanData = new CanMsg[m_ulMesMaxCount];
	printf("\n 1");
	m_pdSASAngle = new double[m_ulMesMaxCount];
	printf("\n 2");
	m_pdServoAngle = new double[m_ulMesMaxCount];
	m_pdDifferAngle = new double[m_ulMesMaxCount];
	printf("\n 3");
	m_pdSpeed = new double[m_ulMesMaxCount];
	printf("\n 4 ");
	m_pdTime = new unsigned long[m_ulMesMaxCount];
	
	printf(" new 변수 할당완료!\n");

//	m_pCanData = new CanMsg[m_ulMesMaxCount];
//	m_pCanData = NULL;

	dServoAngle=0;
//
	m_dSASSpeed=0;						// current speed
	m_dSASAngle=0;						// currend angle
	m_dLeftOnAngle = m_dLeftOffAngle = m_dRightOffAngle = m_dRightOnAngle=NOT_READ;

	m_fValidData=FALSE;		// 전류읽기
	m_uiLowHead=m_uiHead=0;	
	m_uiOldHead=0;
// model value initilize
	int i;
	for(i=0;i<2;i++)
		m_iGoodCnt[i]= m_iNGCnt[i]=m_iTestCnt[i]=0;

	m_strReportFile = "D:\\DATA\\DEFAULT.CSV";
	
//	m_strCanMessageArray.SetSize(100);

	m_Model.bfCurrCheck=0;
//	m_Model.
	m_Model.bfOffsetCheck=m_Model.bfConnectTimeCheck=0;

//	memset(m_sLowCanMsg,0,sizeof (m_sLowCanMsg));

//	printf("\n message size %d %d",sizeof(m_sLowCanMsg),sizeof(m_sLowCanMsg[0]));

	for (i = 0; i < 10; i++)
	{
		m_Model.dMesSpeedStart[i] = m_Model.dMesSpeedEnd[i] = 0;
		m_Model.dMesAngleStart[i] = m_Model.dMesAngleEnd[i] = 0;
	}

	m_Model.dMesSpeedEnd[360] = 0;
	m_Model.dMesSpeedStart[0] = 10;


	m_iMultyTransLen = 0;
	m_SelModel.dwMFSWID=GST_MFSW;

	m_fConnectTimeCheck = false;
	printf("\n생성 완료 및 각 DLG (4)할당 시작  Env,-> MOdelset-> autotest-> manual");
	MotionType = CSMC_PTP;


	p_mEnvSet = new CEnvSet;
	p_mModelSet = new CModelSetDlg;
	p_mSasAuTest = new CSASAutoTest;
	p_mManualT = new CManualTest;

	printf("\nCSAS_1Dlg()DLG 할당 종료!!!! ");

}




CSAS_1Dlg::~CSAS_1Dlg()
{

	m_RunThread = FALSE;
	Sleep(100);

	delete p_mEnvSet;
	delete p_mModelSet;
	delete p_mSasAuTest;
	delete p_mManualT;

 
	if(m_pdSASAngle!=NULL)
		delete m_pdSASAngle;
	if(m_pdServoAngle!=NULL)
		delete m_pdServoAngle;
	if(m_pdSpeed!=NULL)
		delete m_pdSpeed;
	if(m_pdDifferAngle!=NULL)
		delete m_pdDifferAngle;
  
 	if(m_pdTime !=NULL)
 		delete m_pdTime;

	if (m_pCanData != NULL)
		delete m_pCanData;

 	Test.DeleteMyObject();
 

//	m_clMC.ServoOn(FALSE);


	SaveIni();



}
 
void CSAS_1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	DDX_Control(pDX, IDC_LISTBOX, m_ctlListBox);
}

BEGIN_MESSAGE_MAP(CSAS_1Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
//	ON_BN_CLICKED(IDOK, &CSAS_1Dlg::OnBnClickedOk)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CSAS_1Dlg::OnTcnSelchangeTab1)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB1, &CSAS_1Dlg::OnTcnSelchangingTab1)

//	ON_MESSAGE(WM_CANTRACEUPDATE,OnTraceUpdateMsg)
//	ON_MESSAGE(WM_CANSTATUSUPDATE,OnTraceStatusMsg)	// 2015.01.06 추가


	ON_MESSAGE(WM__CANLIB, OnCanSASReceive)
//	ON_MESSAGE(WM_COMM_READ, OnReceive)    // Communication Message Handler 강제로 삽입




//ON_BN_CLICKED(IDC_BUTTON1, &CSAS_1Dlg::OnBnClickedButton1)
//ON_BN_CLICKED(IDC_BUTTON2, &CSAS_1Dlg::OnBnClickedButton2)
//ON_BN_CLICKED(IDC_BUTTON3, &CSAS_1Dlg::OnBnClickedButton3)
//ON_BN_CLICKED(IDC_BUTTON4, &CSAS_1Dlg::OnBnClickedButton4)
ON_BN_CLICKED(IDC_BUTTON1, &CSAS_1Dlg::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON2, &CSAS_1Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CSAS_1Dlg 메시지 처리기

BOOL CSAS_1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.
	printf("\nCSAS_1Dlg::OnInitDialog()");

//	ShowWindow(SW_NORMAL);
	this->ModifyStyle(NULL,WS_THICKFRAME);		// size 조절 가능
#ifndef _DEBUG
 	ShowWindow(SW_MAXIMIZE);
#endif


	pMDlg=this;
	Test.CreadtMyObject();

	printf("\nCreadtMyObject()  ");

	CString str;
	str.Format("SAS 자동측정");
	m_Tab.InsertItem(0,str);
	str.Format("SAS 수동 점검");
	m_Tab.InsertItem(1,str);
	str.Format("모델설정");
	m_Tab.InsertItem(2,str);
	str.Format("환경설정");
	m_Tab.InsertItem(3,str);
	

 
	m_Tab.SetFont(&Test.Font3);

	CRect rect;
	int y=30;
	m_Tab.GetClientRect(&rect);
 
//	m_Tab.SetWindowPos(NULL, 5, 5, 1800, 800, SWP_SHOWWINDOW);
	m_Tab.SetWindowPos(NULL, 5, 5, 1500, 800, SWP_SHOWWINDOW);

//	m_Tab.SetWindowPos(&CWnd::, 0, 0, 1800, 900, SWP_SHOWWINDOW);
	//	m_butListClear.SetWindowPos(&CWnd::wndTop, 1220, 190, 90, 30, SWP_SHOWWINDOW);

	m_Tab.GetClientRect(&rect);
 
	p_mSasAuTest->Create(IDD_DLG_AUTO_TEST,&m_Tab);
	p_mSasAuTest->SetWindowPos(NULL,5,y,rect.Width()-10,rect.Height()-20,SWP_SHOWWINDOW | SWP_NOZORDER);

	p_mManualT->Create(IDD_DLG_MANUAL,&m_Tab);
	p_mManualT->SetWindowPos(NULL,5,y, rect.right - 10,rect.bottom-10,SWP_HIDEWINDOW | SWP_NOZORDER);

	p_mEnvSet->Create(IDD_DLG_ENV,&m_Tab);
	p_mEnvSet->SetWindowPos(NULL,5,y,rect.right-10,rect.bottom-10	,SWP_HIDEWINDOW | SWP_NOZORDER);

	p_mModelSet->Create(IDD_MODEL_SPEC_SET_DLG,&m_Tab);
	p_mModelSet->SetWindowPos(NULL,5,y,rect.right-10,rect.Height(),SWP_HIDEWINDOW | SWP_NOZORDER);
 
 
  	 
	m_ctlListBox.SetWindowPos(NULL, 1550, 50, 300,300, SWP_SHOWWINDOW);
	m_ctlListBox.GetWindowRect(&rect);
 
	LoadINI();

	SetWindowTextA(m_strModelFileName);


	m_RunThread=true;
 	AfxBeginThread((AFX_THREADPROC)TestProcess,(LPVOID)this,THREAD_PRIORITY_ABOVE_NORMAL);
//	AfxBeginThread((AFX_THREADPROC)CurrentProc,(LPVOID)this,THREAD_PRIORITY_ABOVE_NORMAL);
 
	printf("\nTestProcess()  ");

	if(m_strModelFileName.IsEmpty()) return TRUE;
 
 	ReadModel(m_strModelFileName);
	
 	p_mModelSet->ModelValueDisplay();

	m_SelModel= m_Model;	// 현재 읽은값
	p_mSasAuTest->SetValueDisplay();
	
	ReadCnt();
	p_mSasAuTest->CountDisplay();


	m_cBCan.InitDriverFD(1, canTRANSCEIVER_TYPE_CANFD, canBITRATE_500K, canFD_BITRATE_1M_80P, this->m_hWnd,true);		// SAS Bit Rate 1M  ,MFSW 500K
	m_cBCan.FlashReadBuffer();


	// SAS
	m_cCCan.InitDriverFD(0, canTRANSCEIVER_TYPE_CANFD, canBITRATE_500K, canFD_BITRATE_2M_80P, this->m_hWnd, true);		// SAS Bit Rate 2M  ,MFSW 500K 
	m_cCCan.FlashReadBuffer();

//	m_cCRCan.InitDriverFD(2, canTRANSCEIVER_TYPE_CANFD, canBITRATE_500K, canFD_BITRATE_2M_80P, this->m_hWnd, true);		// SAS Bit Rate 2M  ,MFSW 500K 

//
//	SMC_Init(1);//

 	SMC_Init(1,false); //초기화 값을 설정 한다..



	TIMECAPS tc;
	if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) == TIMERR_NOERROR)
		m_bTimer = true;

	wTimerRes = min(max(tc.wPeriodMin, TARGET_RESOLUTION), tc.wPeriodMax);
	if (timeBeginPeriod(wTimerRes) != TIMERR_NOERROR)
		m_bTimer = false;


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSAS_1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSAS_1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSAS_1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

 

// 변경되고 난후에
void CSAS_1Dlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nTab=m_Tab.GetCurSel(); // 변경되고나후에 선택된 탭번호.
// 측정 중에는 이동을 안한다...

	if(m_iRunMode)
	{
		*pResult = 0;
		m_Tab.SetCurSel(0);
		return;
	}
//

	switch(nTab)
	{
	case 0:
		p_mSasAuTest->ShowWindow(SW_SHOW);
		break;
	case 1:
		p_mManualT->ShowWindow(SW_SHOW);
 		p_mManualT->SetTimer(TM_MANUAL,300,NULL);
		printf("\nManual Tab On");
		break;
	case 2:
		p_mModelSet->ShowWindow(SW_SHOW);
		break;
	case 3:
		p_mEnvSet->ShowWindow(SW_SHOW);
 		p_mEnvSet->SetTimer(TM_ENV,300,NULL);
		break;
	case 4:
		break;
	}

	m_CurTabNum=nTab;
	*pResult = 0;
}
/*
// 변경되는중에 발생되는 메세지
*/
void CSAS_1Dlg::OnTcnSelchangingTab1(NMHDR *pNMHDR, LRESULT *pResult)
{

	if(m_iRunMode)
	{
		*pResult = 0;
		return;
	}
		
	int nTab=m_Tab.GetCurSel();

	switch(nTab)
	{
	case 0:
		p_mSasAuTest->ShowWindow(SW_HIDE);
		break;
	case 1:
		p_mManualT->ShowWindow(SW_HIDE);
		p_mManualT->KillTimer(TM_MANUAL);	
		printf("\nTab changed");
		break;
		
	case 2:
		p_mModelSet->ShowWindow(SW_HIDE);
		break;
	case 3:
		p_mEnvSet->ShowWindow(SW_HIDE);
		p_mEnvSet->KillTimer(TM_ENV);
//
		break;
	}
	*pResult = 0;
}



void CSAS_1Dlg::ReadModel(CString strFileName)
{
	int fh;
	
	if(_chdir("D:\\Data")==-1)
	{
		_chdir("D:\\");
		_mkdir("\\Data");
		_chdir("D:\\Data");
	}
	

	if( (fh = _open( strFileName, _O_RDWR | _O_CREAT| _O_BINARY ,_S_IREAD | _S_IWRITE )) != -1 )
	{
		_read( fh, &m_Model, sizeof(MODEL));
		_close( fh );	
	}
	else
	{
 
		m_Model.dwMFSWID = GST_MFSW;
		m_Model.dwTBID = 0x125;
		m_Model.iAngleHighByte = 4;
		m_Model.iAngleLowByte = 3;
		m_Model.iSpeedByte = 5;

	}

// FIX 처리 함 향후에 바꿀것...
	m_Model.dwMFSWID=GST_MFSW;
	m_Model.dwTBID=0x125;
	m_Model.iAngleHighByte=4;
	m_Model.iAngleLowByte=3;
	m_Model.iSpeedByte=5;
 
 







}



void CSAS_1Dlg::SaveModel(CString strFileName)
{
	int fh;
	
	if(_chdir("D:\\Data")==-1)
	{
		_chdir("D:\\");
		_mkdir("\\Data");
		_chdir("D:\\Data");
	}
	

	if( (fh = _open( strFileName, _O_RDWR | _O_CREAT| _O_BINARY ,_S_IREAD | _S_IWRITE )) != -1 )
	{
		
		_write( fh, &m_Model, sizeof(MODEL));
		_close( fh );
	
	}

}




void CSAS_1Dlg::DeleteModel(CString strFileName)
{
	if(strFileName.IsEmpty())
	{
		AfxMessageBox("삭제할 파일일 선택해 주세요");
		return;
	}
	if(_chdir("D:\\Data")==-1)
	{
		_chdir("D:\\");
		_mkdir("\\Data");
		_chdir("D:\\Data");
	}
	CFile::Remove(strFileName);

}

// 자동 측정 routine

void CSAS_1Dlg::TestRun(void)
{
	
	int iResult=-1;
	unsigned int  i;
	double dReadCur=0.0;
	double dTotalCur=0.0;
	CTime tS,tE;
	CTimeSpan tSpan;
	tS = CTime::GetCurrentTime();		// start time
	CString strTemp;
	p_mSasAuTest->m_iTestTime=0;
	m_fMesCur=FALSE;
	p_mSasAuTest->m_iJudgeMode = 2;
//	p_mSasAuTest->m_fMesCur=FALSE;		// 이곳에서만 사용
	p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_reJudgement);
 
	p_mSasAuTest->OutMessage("측정 시작 (제품 power off)");
	Test.BPlus(OFF);
	Test.IGN1(OFF);
	Test.IGN2(OFF);
	//	m_clMC.SASPowerEnable(FALSE);

	Sleep(1000);
	Test.BCanCon(ON, ON);
	Test.CCanCon(ON, ON);
	Test.SerVo(ON);
	
	long iCanRev = 0;
	m_lConnTime = 0;
	Test.BPlus(ON);
	m_tStartTest = p_mSasAuTest->m_tStartTest = CTime::GetCurrentTime();
	m_tCanRev = m_tStart = clock();
	Test.IGN1(ON);
	Test.IGN2(ON);
	p_mSasAuTest->OutMessage("제품 Power On ");
#ifdef _DEBUG
	printf("\nm_tCanRev %d  %d", m_tStart, m_tCanRev);
	printf("\nModel=%f  SelModel=%f ",m_Model.dConnectDelayTime, m_SelModel.dConnectDelayTime);

#endif
	m_fConnectTimeCheck = true;
	for (i = 0; i < 300; i++)
	{

		if ((m_tCanRev > m_tStart)&& !m_fConnectTimeCheck)
		{
			m_lConnTime=iCanRev = m_tCanRev - m_tStart;
			p_mSasAuTest->m_strResultD[0].Format("%d", iCanRev);
			p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_reResultD[0]);
// 현재 측정시간을 기록한다.
			iResult = 1;
			break;
		}
		Sleep(10);
		if (p_mSasAuTest->m_iStopMode == 1) {
			i = 1000; break;
		}	// 강제 종료
	}
	if (i >= 1000)
	{
		UserStop();
		return;
	}
////////////////////
	if (iResult == 1 && p_mSasAuTest->m_iStopMode == 0)
	{
		printf("\nm_tCan수신=%d %d dConnectDelayTime= %f", m_tCanRev, iCanRev, m_SelModel.dConnectDelayTime);
		if (iCanRev > (int)m_SelModel.dConnectDelayTime)
		{
			iResult = -1;
			p_mSasAuTest->OutMessage("Connection Time Fail");
		}
		else
		{
			p_mSasAuTest->OutMessage("Connection Time Pass");
		}
		//		Sleep(200);	// 필요 없다
	}

	m_bSAS_Status = 0xff;

 
	strTemp.Format("m_tCanRev=%d  iCanRev=%d  < dConnectDelayTime= %f", m_tCanRev, iCanRev, m_SelModel.dConnectDelayTime);
	PrintStr(strTemp);
//	if(iResult )

	short StopSts;
	dwRet = SmcWGetStopStatus(Test.m_hSMCID, 1, &StopSts);
 
	if(StopSts != CSMC_STOP_NORMAL)
		SmcWMotionStop(Test.m_hSMCID, 1);


 
	int j;
	double dwTarget, dSpeed;
	long lDistance;
	bool test = false;
	m_dAngle = 2000;
	dwTarget = m_dAngle;



	p_mSasAuTest->m_List.ResetContent();
	 
	if (p_mSasAuTest->m_fOffsetSkip)
	{
		Sleep(100);
		p_mSasAuTest->AddString("Auto Trim");
		if (Test_SAS_Cal() != PASS)
		{
			iResult = 1;
		}
		else
		{
			Test.BPlus(OFF);
			Test.IGN1(OFF);
			Test.IGN2(OFF);
			Sleep(1000);
			m_bSAS_Status = 0xff;

			Test.BPlus(ON);
			Test.IGN1(ON);
			Test.IGN2(ON);
 		}
	}

 

//
	j = 0;
	while (1)
	{
		if ((dwTarget == m_dAngle)&& (m_dAngle !=2000)&& (j > 5))
			break;
 		else
		{
			j++;
			dwTarget = m_dAngle;
		}if (j > 50) break;
		Sleep(50);
	}
	if (j > 50)
	{
		iResult = 0;
		p_mSasAuTest->OutMessage("SAS 각도 Error!");	//  
 	}
	else
		iResult = 1;

	strTemp.Format("%.2f ˚", m_dAngle);
	p_mSasAuTest->AddString(strTemp);

	if ((m_dAngle > 900) || m_dAngle < -900)	//32767 이상인경우 Error
	{
		iResult = 0;
		p_mSasAuTest->OutMessage("SAS 각도 Error 확인이 필요 !");	// 현재 위치를 0 점으로 한다.
		AfxMessageBox("SAS 위치를 읽을수 없습니다.수동으로 제품을 먼저 확인 하세요..");

		Test.BPlus(OFF);
		Test.IGN1(OFF);
		Test.IGN2(OFF);

	}
//	printf("\niResult=%d %d", iResult, p_mSasAuTest->m_fButZeroMove);

// 7FFF
 

	//
	if( p_mSasAuTest->m_iStopMode==1)
	{
		UserStop();
		return;
	}
//	회전 시작
	//double dActPos;

	if(iResult==1 && p_mSasAuTest->m_iStopMode==0)
	{
		Sleep(500);
		lDistance = (long)(pMDlg->m_dAngle * 100.);
		SmcWSetCountPulse(Test.m_hSMCID, 1, lDistance);
		SmcWSetOutPulse(Test.m_hSMCID, 1, lDistance);

	//	printf("\nstep1 Distance= %d", lDistance);

//	server 위치 를 현재 값을 0 으로 할지 선정

	//	AxmStatusGetActPos(0,&dActPos);//;pMDlg->m_clMC.GetFeedBackPos();
		
// SAS 값을 0 로 만든후에 측정을 시작 한다... 원 하는 값을 설정 한다...	
//		printf("\n %.3f  ",dActPos);

//		dActPos= m_clMC.GetFeedBackPos();
	
//		printf(" %.3f  ",dActPos);

 
		DWORD dwRet;
// 현재 값을 가져 온다... SAS angle 값을 가져 온다...
 
//		dSpeed = (m_SelModel.dMesSpeedStart[0] * 2 * 100);	// 36000/360
		dSpeed = (m_SelModel.dMesSpeedStart[0] * 1200);	// 36000/360

		// 1 회전당 72000 Pulse 출력 한다..  1 RPM = 1/60 RPS = 72000/60= 1200 pulse
	//	SmcWSetTargetSpeed(Test.m_hSMCID, 1, 3600);
 

		dblResolveSpeed = 10;
		dblStartSpeed = 10;
		dblAccelTime = 10;
		dblAccelTime = 10;
	 
		dblTargetSpeed = dSpeed;
//		dblSSpeed
		SetMoveParam(1);
 

// CW 방향이 좌측으로 + 값이다..  맨 나중에 한다..

// 현재 값이...
#ifdef FIRST_ORG

	 	if(p_mSasAuTest->m_fButZeroMove)
		{
			dSpeed = (m_SelModel.dMesSpeedStart[0] * 1200);	// 36000/360  RPM to RPS
			dblTargetSpeed = 1200;// 1 RPM
			SetMoveParam(1);

			lDistance =(long) (m_dAngle * 100.);

			if (m_dAngle > 0)
			{
				lDistance = -1 * (lDistance);
				dwRet = SmcWSetStopPosition(Test.m_hSMCID, 1, CSMC_INC, lDistance);
				dwRet = SmcWSetReady(Test.m_hSMCID, 1, CSMC_PTP, CSMC_CCW);
				p_mSasAuTest->OutMessage("원점 이동시작 CW");	// 현재 위치를 0 점으로 한다.
			}
			else if (m_dAngle < 0)
			{
				;
				lDistance = -1 * (lDistance);
				dwRet = SmcWSetStopPosition(Test.m_hSMCID, 1, CSMC_INC, lDistance);
				dwRet = SmcWSetReady(Test.m_hSMCID, 1, CSMC_PTP, CSMC_CW);
				p_mSasAuTest->OutMessage("원점 이동시작 CCW");	// 현재 위치를 0 점으로 한다.
			}
		//	printf("\nZeroMOve %d", lDistance);
			if (m_dAngle != 0)
			{
				SmcWMotionStart(Test.m_hSMCID, 1);
				iResult = MoveCheck();
				p_mSasAuTest->OutMessage("원점 이동 완료");	// 현재 위치를 0 점으로 한다.
				Sleep(500);		// Kwon YoungGi
			}

 		}
//
	//	m_clMC.RdoAbsRelMode(0);		// 0 abs,  1 =rel mode 설정

		Sleep(500);
#endif
		j=0;
		CString strTemp;

		  
	 
	//	
		
//		SmcWSetAccelTime(Test.m_hSMCID, 1, 20);
//		SmcWSetDecelTime(Test.m_hSMCID, 1, 20);
  
//		dSpeed = (m_SelModel.dMesSpeedStart[0] * 2 * 100);	// 36000/360
		dSpeed = (m_SelModel.dMesSpeedStart[0] * 1200);	// RPM to pulse

		strTemp.Format("speed= %.f", dSpeed);

//		SmcWSetTargetSpeed(Test.m_hSMCID, 1, dSpeed);
//		SmcWSetTargetSpeed(Test.m_hSMCID, 1, dSpeed);
//		SmcWSetResolveSpeed(Test.m_hSMCID, 1, 10);

 
		dblTargetSpeed = dSpeed;
		SetMoveParam(1);

 

		dwTarget = m_dAngle;
		Sleep(100);

		j = 0;
		while (1)
		{
			if ((dwTarget == m_dAngle)&& (j > 5))
				break;
			else
			{
				j++;
				dwTarget = m_dAngle;
			}
			if (j > 50) break;
			Sleep(50);
		}

		if (j > 50)
		{
			iResult = 0;
			p_mSasAuTest->OutMessage("SAS 각도 Error!");	// 현재 위치를 0 점으로 한다.
			AfxMessageBox("ERROR");

		}
		else
			iResult = 1;
	
		
		printf("\niResult=%d %d", iResult, p_mSasAuTest->m_fButZeroMove);
 
		PrintStr("이동시작");
		p_mSasAuTest->OutMessage("측정 시작 위치 이동");

		long lCurrentPos;

		long temp;

 
// 현재 값과 차이 가 있는경우....

//	dwRet = SmcWGetStopStatus(Test.m_hSMCID, 1, &StopSts);

 
		lDistance = 0;

 
	
		p_mSasAuTest->OutMessage("측정 시작 ");

//
		m_ulCurCnt= m_ulDrawCnt=0;
		m_iCindex = 0;
	 
	//	p_mSasAuTest->m_iStopMode = 1;	// user stop


	
//		m_fValidData=TRUE;		// current read thread on 전류 읽기및 표시 하기...
//
#ifndef DIS_TYPE1
	 	timerID = timeSetEvent(10, wTimerRes, TimeProc, (DWORD)this, TIME_PERIODIC);// 50ms
#endif

 
		for (i = 1; i < 7; i++)
			m_SelModel.dMesAngleEnd[i - 1] = m_SelModel.dMesAngleStart[i];

		m_SelModel.dMesAngleEnd[6] = m_SelModel.dMesAngleStart[6];


		for(i=0;i< 7;i++)		// 7
		{
	 /* 		printf("\n start [%d] %.3f  %.3f,  %d %f", i, m_SelModel.dMesAngleStart[i], m_SelModel.dMesAngleEnd[i]
			, m_ulMesMaxCount,m_SelModel.dMesSpeedStart);
	*/	
			if(p_mSasAuTest->m_iStopMode==1)	// user stop
			{ 
				iResult=-1;
				break;			// exit for
			}

//			if((m_SelModel.dMesAngleEnd[i] == m_SelModel.dMesAngleStart[i])  || (m_SelModel.dMesSpeedStart[i]  == 0 ))
 			if( (m_SelModel.dMesSpeedStart[i]  == 0 ))
			{
				m_fValidData=FALSE; 
				break;			// exit for
			}
// 
			 
#ifdef NO_CONTROL
			lCurrentPos = 0;
#else
			SmcWGetCountPulse(Test.m_hSMCID, 1, &lCurrentPos);
#endif
			dwTarget = (m_SelModel.dMesAngleStart[i] * 1);// 7200/360);
			
//			dSpeed = (m_SelModel.dMesSpeedStart[i] * 2 * 100);	// 36000/360
			dSpeed = (m_SelModel.dMesSpeedStart[i] * 1200);	//  RPM   = 72000 /60 = 1200 pulse


			lDistance = (long)(dwTarget * 100. * 1.);
			temp = lDistance - lCurrentPos;
			SmcWSetTargetSpeed(Test.m_hSMCID, 1, dSpeed);

			strTemp.Format("Step=%d temp(differ) =%d curr=%d  move=%d (%.f)",i+1, temp, lCurrentPos, lDistance, m_SelModel.dMesAngleStart[i]);
//			AfxMessageBox(strTemp);
			lDistance = temp;		// 일 차 시작위치 값..
			dblTargetSpeed = dSpeed;
			dblTargetSpeed = 18000;// 36000;

			SetMoveParam(1);

			if (i == 0)
			{

				if (lDistance < 0)
				{
					//		lDistance = -1 * (lDistance);
 					dwRet = SmcWSetReady(Test.m_hSMCID, 1, CSMC_PTP, CSMC_CCW);
					//
				}
				else
					dwRet = SmcWSetReady(Test.m_hSMCID, 1, CSMC_PTP, CSMC_CW);
				//
				dwRet = SmcWSetStopPosition(Test.m_hSMCID, 1, CSMC_INC, lDistance);
				strTemp.AppendFormat(" move=%d  speed=%.1f Start Pos ", lDistance, dSpeed);
				//		p_mSasAuTest->AddString(strTemp);
				p_mSasAuTest->OutMessage("Start 위치로 이동중");


#ifndef NO_CONTROL

				if (lDistance != 0)
				{

					strTemp.Format("%d 시작 위치로 이동중!", i + 1);
					p_mSasAuTest->OutMessage(strTemp);
					dwRet = SmcWMotionStart(Test.m_hSMCID, 1);
					iResult = MoveCheck();
					strTemp.Format("%d 시작 위치로 이동완료! =>%d", i + 1,iResult);
					p_mSasAuTest->OutMessage(strTemp);

					Sleep(1000);

				}
				if (iResult == -1)
				{
					UserStop();
					break;
				}
#else
				while (1)
				{
					if (p_mSasAuTest->m_iStopMode == 1)
					{
						iResult = -1;
						UserStop();
						break;
					}

					if (lDistance >= 0)
					{
						if (m_dAngle >= (lDistance / 100.))
							break;
					}
					else
					{
						if (m_dAngle <= (lDistance / 100.))
							break;
					}
					Sleep(100);
				}

#endif
				if (iResult == -1)
					break;
	//			AfxMessageBox("READY");
			}

			dwTarget = (m_SelModel.dMesAngleEnd[i] * 1);//7200.0/360.0);

		//	dSpeed =(m_SelModel.dMesSpeedStart[i]*2*100);//ANG2PULSE

//			dSpeed = (m_SelModel.dMesSpeedStart[i] * 1200);	//  RPM   = 72000 /60 = 1200 pulse

#ifdef NO_CONTROL
			lCurrentPos = 0;
#else
			SmcWGetCountPulse(Test.m_hSMCID, 1, &lCurrentPos);
#endif
			lDistance = (long)(dwTarget * 100. * 1.);
			temp = lDistance - lCurrentPos;
			strTemp.Format("Step=%d temp =%d curr=%d  move=%d  %.2f ",i+1, temp, lCurrentPos, lDistance, m_SelModel.dMesAngleStart[i]);
			//			AfxMessageBox(strTemp);
			lDistance = temp;		// 일 차 시작위치 값..

 			dblTargetSpeed = dSpeed;
			SetMoveParam(1);
	
			if (lDistance < 0)
			{
				//		lDistance = -1 * (lDistance);
				dwRet = SmcWSetReady(Test.m_hSMCID, 1, CSMC_PTP, CSMC_CCW);
				//
			}
			else
				dwRet = SmcWSetReady(Test.m_hSMCID, 1, CSMC_PTP, CSMC_CW);
			//
			dwRet = SmcWSetStopPosition(Test.m_hSMCID, 1, CSMC_INC, lDistance);
			strTemp.AppendFormat(" Measure =%d ", lDistance);
			p_mSasAuTest->AddString(strTemp);

			strTemp.Format("%d 구간 측정중", i + 1);
			p_mSasAuTest->OutMessage(strTemp);
#ifdef NO_CONTROL
			m_fValidData = true;

			while (1)
			{
 				if (m_ulDrawCnt >= m_ulMesMaxCount)
					break; 
				Sleep(5);
/*				if (m_dSASAngle == m_dSASAngle)
				{
					break;
				}
*/
			}

#else
			if (lDistance != 0)
			{
				Sleep(500);
				m_fValidData = TRUE;		// .
				p_mSasAuTest->m_fDirCW = true;
				dwRet = SmcWMotionStart(Test.m_hSMCID, 1);
				iResult = MoveCheck();
			}
			m_fValidData = FALSE;
			if (iResult == -1)
			{
				UserStop();
				break;
			}
			 


			dwTarget = (m_SelModel.dMesAngleStart[i] );//7200.0/360.0); 반대로 측정을 하기 위해서

		//	dSpeed =(m_SelModel.dMesSpeedStart[i]*2*100);//ANG2PULSE
 
	//		AfxMessageBox("YOUNG");
			SmcWGetCountPulse(Test.m_hSMCID, 1, &lCurrentPos);
 
			lDistance = (long)(dwTarget * 100. * 1.);
			temp = lDistance - lCurrentPos;
			strTemp.Format("Reverse Step=%d temp =%d curr=%d  move=%d  %.2f ", i + 1, temp, lCurrentPos, lDistance, m_SelModel.dMesAngleStart[i]);
	//		AfxMessageBox(strTemp);
		//	temp = 1800;
			lDistance = temp;		//  


	 
 			dblTargetSpeed = dSpeed;
		//	dblTargetSpeed = 1200;

			SetMoveParam(1);

			if (lDistance < 0)
			{
				//		lDistance = -1 * (lDistance);
				dwRet = SmcWSetReady(Test.m_hSMCID, 1, CSMC_PTP, CSMC_CCW);
				//
			}
			else
				dwRet = SmcWSetReady(Test.m_hSMCID, 1, CSMC_PTP, CSMC_CW);
			//

			dwRet = SmcWSetStopPosition(Test.m_hSMCID, 1, CSMC_INC, lDistance);
			strTemp.AppendFormat(" Measure =%d ", lDistance);
			p_mSasAuTest->AddString(strTemp);

			if (lDistance != 0)
			{
				Sleep(500);
				m_iCindex = m_ulCurCnt;	// 반대 값
				m_fValidData = TRUE;		// .
				p_mSasAuTest->m_fDirCW = false;
				dwRet = SmcWMotionStart(Test.m_hSMCID, 1);
				iResult = MoveCheck();
			}


			m_fValidData = FALSE;
			
			PrintStr("1 Sec Wait");

			Sleep(1000);
			AfxMessageBox("DDD");

// 반대 방향으로 무조 건 측정 한다..


#endif
 		m_fValidData=FALSE; 
/////////////////////////////////////// here can message clear 하는 방법............/////////
//		
	//	p_mSasAuTest->DrawGraph(m_ulCurCnt);	// 측정 중인경우..   2015.01.08

/*
		Sleep(1000);
		m_clMC.ServoOn(FALSE);
 //		AfxMessageBox("Ready!");
		Sleep(500);
		m_clMC.ServoOn(TRUE);
		Sleep(500);
//	AfxMessageBox("Ready");
*/
//			printf("\n end %d %.3f  %.3f, %d %d",i,m_SelModel.dMesAngleStart[i],m_SelModel.dMesAngleEnd[i],m_ulCurCnt,m_ulMesMaxCount);
		}
//		printf("\n %d %.3f  %.3f, %d %d",i,m_SelModel.dMesAngleStart[i],m_SelModel.dMesAngleEnd[i],m_ulCurCnt,m_ulMesMaxCount);

	}
	timeKillEvent(timerID);
	timerID = NULL;


#ifndef FIRST_ORG

	if (p_mSasAuTest->m_fButZeroMove)
	{
	//	dSpeed = (m_SelModel.dMesSpeedStart[0] * 1200);	// 36000/360  RPM to RPS
		dblTargetSpeed = 1200;// 1 RPM
		SetMoveParam(1);

		lDistance = (long)(m_dAngle * 100.);

		if (m_dAngle > 0)
		{
			lDistance = -1 * (lDistance);
			dwRet = SmcWSetStopPosition(Test.m_hSMCID, 1, CSMC_INC, lDistance);
			dwRet = SmcWSetReady(Test.m_hSMCID, 1, CSMC_PTP, CSMC_CCW);
			p_mSasAuTest->OutMessage("원점 이동시작 CW");	// 현재 위치를 0 점으로 한다.
		}
		else if (m_dAngle < 0)
		{
			;
			lDistance = -1 * (lDistance);
			dwRet = SmcWSetStopPosition(Test.m_hSMCID, 1, CSMC_INC, lDistance);
			dwRet = SmcWSetReady(Test.m_hSMCID, 1, CSMC_PTP, CSMC_CW);
			p_mSasAuTest->OutMessage("원점 이동시작 CCW");	// 현재 위치를 0 점으로 한다.
		}
		//	printf("\nZeroMOve %d", lDistance);
		if (m_dAngle != 0)
		{
			SmcWMotionStart(Test.m_hSMCID, 1);
			iResult = MoveCheck();
			p_mSasAuTest->OutMessage("원점 이동 완료");	// 현재 위치를 0 점으로 한다.
			Sleep(500);		// Kwon YoungGi
		}

	}
	//
		//	m_clMC.RdoAbsRelMode(0);		// 0 abs,  1 =rel mode 설정

	Sleep(500);
#endif

 
//
	if(iResult==1)
	{
		p_mSasAuTest->OutMessage("측정 완료");
	}

	else
		p_mSasAuTest->OutMessage("측정 정지");

//	p_mSasAuTest->OnPaint();
//	m_ulMesMaxCount = 0;
	if(iResult==1)
	{
		double dMax =0.0;
		double dMin =900;
		int m_iDataCnt=0;
		double dSum=0;
		int iPos=0;
		double dAvr[10]={0,0,0,0,0,0,0,0,0,0 };
		double dLMax[10]={ 0,0,0,0,0,0,0,0,0,0 };
		double dLMin[10]={900,900,900,900,900,900,900,900,900,900};
		p_mSasAuTest->AddString("Nonlinearity,Hysteresis 계산 시작");
	 
		BOOL fData=FALSE;
		 

		double dNonL=0;
		for(i=1;i< m_ulMesMaxCount;i++)
		{
	 		if(this->m_pdSpeed[i] > CAL_START_SPEED )	// 최소 속도가..
			{
				fData = TRUE;
				if(this->m_pdDifferAngle[i]>dMax)
					dMax = this->m_pdDifferAngle[i];
				if(this->m_pdDifferAngle[i]<dMin)
					dMin = this->m_pdDifferAngle[i];
				dSum+=this->m_pdDifferAngle[i];
				m_iDataCnt++;
			}else
			{// speed 값이 cal_start_speed 보다 작은경우(한구간 끝난경우..)
				if(fData && iPos < 10)		// 5 -> 10
				{
					fData=FALSE;
					dLMax[iPos]=dMax;
					dLMin[iPos]=dMin;
				//	if(dNonL<(dMax-dMin))
				//		dNonL = dMax-dMin;
					dMax =0.0;
					dMin =900;
					if(iPos<10)
						dAvr[iPos++]=dSum/m_iDataCnt;	
					//if(iPos>4) iPos=4;
				}
			}
	 
		}
//	 
		dMax=0;
		double dTemp=0;
		for( i=0;i<(unsigned int)iPos;i++)
		{
			dTemp = dAvr[i]-dLMin[i];		// 한구간 평균값 - 최솟값
			if(dMax<dTemp)
				dMax=dTemp;
			dTemp = dLMax[i]-dAvr[i];	// 한구간 평균값 - 최댓값
			if(dMax<dTemp)
				dMax=dTemp;
		}

		dNonL = dMax;// dTemp;		// dMax 값이 아닌지 ??
		p_mSasAuTest->m_strResultD[2].Format("%.2f",dNonL);
		p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_reResultD[2]);
		if(m_SelModel.dNonlinearity < dNonL)
		{
			iResult=-1;
			p_mSasAuTest->OutMessage("Nonlinearity Fail");
		}else
		{
			iResult=1;
			p_mSasAuTest->OutMessage("Nonlinearity Pass");
		}

		dMax=0;
		dMin=0;
//
		for(i=0;i<(unsigned int)iPos;i++)
		{
			if(dMax<dAvr[i])
				dMax = dAvr[i];
			if(dMin>dAvr[i])
				dMin = dAvr[i];
		}
//
		p_mSasAuTest->m_strResultD[3].Format("%.2f",dMax-dMin);
		p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_reResultD[3]);
		if(iResult==1)
		{
			if(m_SelModel.dHysteress<(dMax-dMin))
			{
				p_mSasAuTest->OutMessage("Hysteresis Fail");
				iResult=-1;
			}else
			{
				p_mSasAuTest->OutMessage("Hysteresis Pass");
				iResult=1;
			}
		}
	}

	m_fValidData=FALSE;

	Sleep(200);
//	Sleep(1000);
/////////// 화면 갱신한다..
	p_mSasAuTest->m_ulCurCnt = m_ulCurCnt;
	p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_reGraph);


	if(iResult==1)
	{
		p_mSasAuTest->m_iJudgeMode=1;	// GOOD
		m_iGoodCnt[0]++;
		m_iGoodCnt[1]++;
		m_iTestCnt[0]++;
		m_iTestCnt[1]++;
		p_mSasAuTest->m_strPToday[0].Format("%d",m_iGoodCnt[0]);
		p_mSasAuTest->m_strPToday[2].Format("%d",m_iTestCnt[0]);
		p_mSasAuTest->m_strPTotal[0].Format("%d",m_iGoodCnt[1]);	
		p_mSasAuTest->m_strPTotal[2].Format("%d",m_iTestCnt[1]);	
	}else
	{
		p_mSasAuTest->m_iJudgeMode=0;	// NG
		m_iNGCnt[0]++;
		m_iNGCnt[1]++;
		m_iTestCnt[0]++;
		m_iTestCnt[1]++;
		p_mSasAuTest->m_strPToday[1].Format("%d",m_iNGCnt[0]);
		p_mSasAuTest->m_strPToday[2].Format("%d",m_iTestCnt[0]);
		p_mSasAuTest->m_strPTotal[1].Format("%d",m_iNGCnt[1]);
		p_mSasAuTest->m_strPTotal[2].Format("%d",m_iTestCnt[1]);
	}

//	SaveCnt();
	p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_rePInfoBox);

 	SaveMeaData();		// 측정 결과를 저장 한다...
	p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_reJudgement);
	tE = CTime::GetCurrentTime();
	tSpan  = tE-tS;
	p_mSasAuTest->m_iTestTime =(int) tSpan.GetTotalSeconds();	// Test Tine
	p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_reTestTime);
	SmcWMotionStop(Test.m_hSMCID, 1);



	Test.BPlus(OFF);
	Test.IGN1(OFF);
	Test.IGN2(OFF);
	//	m_clMC.SASPowerEnable(FALSE);
 	Test.SerVo(OFF);
	 
	printf("\n....TestRun() ");

}

int CSAS_1Dlg::Read_Current(double& dData)
{
 
	int retVal=-1;
 
	return retVal;
}

void CSAS_1Dlg::LoadINI(void)
{
	char *filename;//="d:\\data\\SAS_MFSW.INI";

	TCHAR path[MAX_PATH];
	GetModuleFileName(NULL,path,sizeof path);
	CString strPath;
	strPath=path;

	int i=strPath.ReverseFind('\\');// 파일 이름 찾기
	strPath=strPath.Left(i);// 뒤에 있는 현재 실행 파일 이름을 지운다.
	strPath.AppendFormat("\\SAS_MFSW.INI");


	strPath.Format("d:\\Data\\SAS_MFSW.INI");

//	char filename1[MAX_PATH];

	filename = strPath.GetBuffer(strPath.GetLength());

 // 	AfxMessageBox(strPath);

	TCHAR buf[128]={NULL,};

	bool flag;
 /* 
	flag=GetPrivateProfileString(("COM"), ("curr"), ("COM3"),buf,128,filename );
	printf("\nLoadini[%s]=%d",filename,flag);
	GetPrivateProfileString(("COM"), ("LIN"), ("COM4"),buf,128,filename );
//  
	GetPrivateProfileString(("CAR"), ("maxModel"), ("10"),buf,128,filename );
*/	
	GetPrivateProfileString(("ETC"), "model_FileName", ("default.spe"),buf,128,filename );
	m_strModelFileName = buf;
}


void CSAS_1Dlg::SaveIni(void)
{

	char *filename;//="d:\\data\\SAS_MFSW.INI";

	TCHAR path[MAX_PATH];
	GetModuleFileName(NULL,path,sizeof path);
	CString strPath;
	strPath=path;

	int i=strPath.ReverseFind('\\');// 파일 이름 찾기
	strPath=strPath.Left(i);// 뒤에 있는 현재 실행 파일 이름을 지운다.
	strPath.AppendFormat("\\SAS_MFSW.INI");
	strPath.Format("d:\\Data\\SAS_MFSW.INI");

	filename = strPath.GetBuffer(strPath.GetLength());
	AfxMessageBox(strPath);

//	printf("\n<%s>",filename);
 
	WritePrivateProfileString(_T("ETC"),_T("model_FileName"),m_strModelFileName,filename);	// 
 
}

LRESULT CSAS_1Dlg::OnTraceStatusMsg(WPARAM wParam, LPARAM lParam)
{
#ifdef USE_IXXAT
	p_mSasAuTest->AddString(m_BCan.m_CanStatusMsg);	// list box 추가 처리 한다.
#endif
	return 0;
}
// can message 처리




void CSAS_1Dlg::AG_MFSW(void)
{
	DWORD dwData=0;
	BYTE	temp;
	int i;
#ifdef USE_AG		
 
	for(i=0;i<5;i++)
	{
			if(m_BCan.m_sCanMsg.abData[i] != m_sLowCanMsg[0].abData[i])
				break;
	}
//
	if(i>4)
			return ;	// 이전 message 와 같은경우
//
//		if(m_CurTabNum ==0) return 0;
		m_sLowCanMsg[0]=m_BCan.m_sCanMsg;



//////////////////////////
// wipper-lo,hi,whsher-f,r, headlamp low, tail ,auto,rear for
		if(	m_sLowCanMsg[0].abData[2] & C_R_FOG_SW_AG)
				dwData =RR_FOG_LED;

		if(	m_sLowCanMsg[0].abData[1] & C_WIPPER_LO_SW_AG)
				dwData |= WIPER_LO_LED;

		if(	m_sLowCanMsg[0].abData[1] & C_WIPPER_HI_SW_AG)
				dwData |= WIPER_HI_LED;

		if(	m_sLowCanMsg[0].abData[0] & C_WIPPER_WASHER_SW_AG)
				dwData |= WASHER_F__LED;
//
		switch (m_sLowCanMsg[0].abData[0] & 0xc0)
		{
// light off
		case 0x40:
				dwData |= TAIL_LED;
				break;
		case 0x80:
				dwData |= HLAMP_LO_LED;
				break;
		case 0xc0:
				dwData |= AUTO_LED;
				break;
		}
//  		
//
		if(	m_sLowCanMsg[0].abData[1] & C_WIPPER_AUTO_SW_AG)
				dwData |= WIPTE_AUTO_LED;
//
	//	AxdoNWriteOutportByte(0,Do_1,1,dwData);		// LED out
//
// WASHER Rear 현재 할 당 안됨. lamp 출력도 없다.
/*
		if(	m_sLowCanMsg[0].abData[1] & C_WIPPER_AUTO_SW)
				dwData |= AUTO_LED;
*/
		temp=(m_sLowCanMsg[0].abData[1] & 0xe0) >> (1+4);
		dwData = 2 << temp;	//
		if(	m_sLowCanMsg[0].abData[0] & C_F_FOG_SW_AG)
			dwData |=1; 
//
	//	AxdoNWriteOutportByte(0,Do_1,2,dwData);		// LED out
 //////////////////////////////////==============

		if(m_sLowCanMsg[0].abData[0] & C_PASS_SW_AG)
			dwData = PASSING_LED;
		else 
			dwData = 0;

		if(m_sLowCanMsg[0].abData[0] & C_HL_HIGH_SW_AG)	//dimmer 기능
			dwData |= HL_HIGH_LED;
// 2015.01.09 ag 차종은 없다
/*
		if(m_sLowCanMsg[0].abData[2] & C_T_SIGLH_SW)
			dwData |= CHANG_LH_LED;
		if(m_sLowCanMsg[0].abData[2] & C_T_SIGRH_SW)
			dwData |= CHANG_RH_LED;
*/
		if(m_sLowCanMsg[0].abData[1] & C_WIPPER_INT_SW_AG)
			dwData |= INT_LED;
		if(m_sLowCanMsg[0].abData[1] & C_WIPPER_MIST_SW_AG)
			dwData |= MIST_LED;

////// 2014.12.09 부분 변경 각도 표기 기능  full turn
/////////////////////////////////////////////////////
		if(m_sLowCanMsg[0].abData[0] & C_LC_SIGRH_SW_AG)
		{
			dwData |= FULL_TR_R_LED;
			if(!m_bRightTurn)
			{
				m_bRightTurn=true;	// current angle display
				m_dRightOnAngle=m_dSASAngle;		//NOT_READ
				m_dRightOffAngle=NOT_READ;
				p_mManualT->TurnAngleDisplay();
			}
		}
		else
		{
			if(m_bRightTurn)
			{
				m_bRightTurn=false;
				m_dRightOffAngle=m_dSASAngle;
				p_mManualT->TurnAngleDisplay();
			}
		}

		if(m_sLowCanMsg[0].abData[0] & C_LC_SIGLH_SW_AG)
		{
			dwData |= FULL_TR_L_LED;
			if(!m_bLeftTurn)
			{
				m_bLeftTurn=true;
				m_dLeftOnAngle=m_dSASAngle;
				m_dLeftOffAngle=NOT_READ;
				p_mManualT->TurnAngleDisplay();
			}
		}
		else
		{
			if(m_bLeftTurn)
			{
				m_bLeftTurn=false;
				m_dLeftOffAngle=m_dSASAngle;	// off
				p_mManualT->TurnAngleDisplay();
			}
		}
#endif
	//	AxdoNWriteOutportByte(0,Do_1,0,dwData);
}

void CSAS_1Dlg::RJ_MFSW(void)
{
#ifdef USE_RJ
	DWORD dwData=0;
	BYTE	temp;
	int i;

 	for(i=0;i<5;i++)
	{
		 
			if(m_clCan.m_sCanMsg.abData[i] != m_sLowCanMsg[0].abData[i])
				break;
	}
//
	if(i>4)
			return ;	// 이전 message 와 같은경우
//
//		if(m_CurTabNum ==0) return 0;
//		m_sLowCanMsg[0]=m_sCanMsg.m_sCanMsg;
 	for(i=0;i<8;i++)
		m_sLowCanMsg[0].abData[i]=m_clCan.m_sCanMsg.abData[i];

//////////////////////////
// wipper-lo,hi,whsher-f,r, headlamp low, tail ,auto,rear for
//		if(	m_sLowCanMsg[0].abData[2] & C_R_FOG_SW_RJ)
//				dwData =RR_FOG_LED;

		if(	m_sLowCanMsg[0].abData[1] & C_WIPPER_LO_SW_RJ)
				dwData |= WIPER_LO_LED;

		if(	m_sLowCanMsg[0].abData[1] & C_WIPPER_HI_SW_RJ)
				dwData |= WIPER_HI_LED;

 		if(	m_sLowCanMsg[0].abData[1] & C_WIPPER_WASHER_SW_RJ)
 				dwData |= WASHER_F__LED;
//
//		if(	m_sLowCanMsg[0].abData[1] & C_WIPPER_AUTO_SW_RJ)
//				dwData |= WIPTE_AUTO_LED;

		switch (m_sLowCanMsg[0].abData[0] & 0x30)
		{
// light off
		
		case 0x10:
				dwData |= TAIL_LED;
				break;
		case 0x20:
				dwData |= HLAMP_LO_LED;
				break;
		case 0x30:
				dwData |= AUTO_LED;
				break;
		}
//  		
//
//
	//	AxdoNWriteOutportByte(0,Do_1,1,dwData);		// LED out
//
// WASHER Rear 현재 할 당 안됨. lamp 출력도 없다.
/*
		if(	m_sLowCanMsg[0].abData[1] & C_WIPPER_AUTO_SW)
				dwData |= AUTO_LED;
*/
		temp=(m_sLowCanMsg[0].abData[1] & 0xe) >> (1);
		dwData = 2 << temp;	//
 		if(	m_sLowCanMsg[0].abData[0] & C_F_FOG_SW_RJ)
 			dwData |=1; 
//
//		AxdoNWriteOutportByte(0,Do_1,2,dwData);		// LED out
 //////////////////////////////////==============

		if(m_sLowCanMsg[0].abData[0] & C_PASS_SW_RJ)
			dwData = PASSING_LED;
		else 
			dwData = 0;

		if(m_sLowCanMsg[0].abData[0] & C_HIGH_SW_RJ)	//dimmer 기능
			dwData |= HL_HIGH_LED;
// 2015.01.09 ag 차종은 없다
/*
		if(m_sLowCanMsg[0].abData[2] & C_T_SIGLH_SW)
			dwData |= CHANG_LH_LED;
		if(m_sLowCanMsg[0].abData[2] & C_T_SIGRH_SW)
			dwData |= CHANG_RH_LED;
*/
 		if(m_sLowCanMsg[0].abData[1] & C_WIPPER_AUTO_SW_RJ)
 			dwData |= INT_LED;
		if(m_sLowCanMsg[0].abData[2] & C_WIPPER_MIST_SW_RJ)
			dwData |= MIST_LED;

////// 2014.12.09 부분 변경 각도 표기 기능  full turn
/////////////////////////////////////////////////////
		if(m_sLowCanMsg[0].abData[0] & C_SIGRH_SW_RJ)
		{
//			dwData |= FULL_TR_R_LED;
			dwData |= FULL_TR_L_LED;
			if(!m_bRightTurn)
			{
				m_bRightTurn=true;	// current angle display
				m_dRightOnAngle=m_dSASAngle;		//NOT_READ
				m_dRightOffAngle=NOT_READ;
				p_mManualT->TurnAngleDisplay();
			}
		}
		else
		{
			if(m_bRightTurn)
			{
				m_bRightTurn=false;
				m_dRightOffAngle=m_dSASAngle;
				p_mManualT->TurnAngleDisplay();
			}
		}

		if(m_sLowCanMsg[0].abData[0] & C_SIGLH_SW_RJ)
		{
// 			dwData |= FULL_TR_L_LED;
 			dwData |= FULL_TR_R_LED;	// pannel 이름이 바뀌어서
 			if(!m_bLeftTurn)
			{
				m_bLeftTurn=true;
				m_dLeftOnAngle=m_dSASAngle;
				m_dLeftOffAngle=NOT_READ;
				p_mManualT->TurnAngleDisplay();
			}
		}
		else
		{
			if(m_bLeftTurn)
			{
				m_bLeftTurn=false;
				m_dLeftOffAngle=m_dSASAngle;	// off
				p_mManualT->TurnAngleDisplay();
			}
		}
#endif
	//	AxdoNWriteOutportByte(0,Do_1,0,dwData);
}



void CSAS_1Dlg::Default_MFSW(void)
{
#ifdef USE_MFSW
	DWORD dwData = 0;
	int i;
	BYTE	temp;
	for(i=0;i<5;i++)
	{
			if(m_BCan.m_sCanMsg.abData[i] != m_sLowCanMsg[0].abData[i])
				break;
	}
//
	if(i>4)
			return ;	// 이전 message 와 같은경우
//
//		if(m_CurTabNum ==0) return 0;
		m_sLowCanMsg[0]=m_BCan.m_sCanMsg;
 
//////////////////////////
// wipper-lo,hi,whsher-f,r, headlamp low, tail ,auto,rear for
//		if(	m_sLowCanMsg[0].abData[0] & C_R_FOG_SW)
//				dwData =RR_FOG_LED;

		if(	m_sLowCanMsg[0].abData[1] & C_WIPPER_LO_SW)
				dwData |= WIPER_LO_LED;

		if(	m_sLowCanMsg[0].abData[1] & C_WIPPER_HI_SW)
				dwData |= WIPER_HI_LED;

		if(	m_sLowCanMsg[0].abData[1] & C_WIPPER_WASHER_SW)
				dwData |= WASHER_F__LED;
// 아직 할당 되지 않음..
/*
		if(	m_sLowCanMsg[0].abData[1] & C_WIPPER_RWASHER_SW)
				dwData |= WASHER_R__LED;
*/
		//		DWORD dwData1=0;

		switch (m_sLowCanMsg[0].abData[0] & 0x30)
		{
// light off
		
		case 0x10:
				dwData |= TAIL_LED;
				break;
		case 0x20:
				dwData |= HLAMP_LO_LED;
				break;
		case 0x30:
				dwData |= AUTO_LED;
				break;
		}
//		
	//	AxdoNWriteOutportByte(0,Do_1,1,dwData);

//
// WASHER Rear 현재 할 당 안됨. lamp 출력도 없다.
/*
		if(	m_sLowCanMsg[0].abData[1] & C_WIPPER_AUTO_SW)
				dwData |= AUTO_LED;
*/
		temp=(m_sLowCanMsg[0].abData[1] & 0xe) >> 1;
		dwData = 2 << temp;	//
		if(	m_sLowCanMsg[0].abData[0] & C_F_FOG_SW)
			dwData |=1; 
	//	AxdoNWriteOutportByte(0,Do_1,2,dwData);
//		printf("\n----------------- %02X %02X %02X",m_sLowCanMsg[0].abData[0],m_sLowCanMsg[0].abData[1],m_sLowCanMsg[0].abData[2]);	
////------------------
		if(m_sLowCanMsg[0].abData[0] & C_PASS_SW)
			dwData = PASSING_LED;
		else 
			dwData = 0;

		if(m_sLowCanMsg[0].abData[0] & C_HL_HIGH_SW)
			dwData |= HL_HIGH_LED;
// 2015.01.09
		if(m_sLowCanMsg[0].abData[2] & C_T_SIGLH_SW)
			dwData |= CHANG_LH_LED;
		if(m_sLowCanMsg[0].abData[2] & C_T_SIGRH_SW)
			dwData |= CHANG_RH_LED;
		if(m_sLowCanMsg[0].abData[1] & C_WIPPER_INT_SW)
			dwData |= INT_LED;
		if(m_sLowCanMsg[0].abData[2] & C_WIPPER_MIST_SW)
			dwData |= MIST_LED;
////// 2014.12.09 부분 변경 각도 표기 기능
/////////////////////////////////////////////////////
		if(m_sLowCanMsg[0].abData[0] & C_LC_SIGRH_SW)
		{
			dwData |= FULL_TR_R_LED;
			if(!m_bRightTurn)
			{
				m_bRightTurn=true;	// current angle display
				m_dRightOnAngle=m_dSASAngle;		//NOT_READ
				m_dRightOffAngle=NOT_READ;


				p_mManualT->TurnAngleDisplay();
			}
		}
		else
		{
			if(m_bRightTurn)
			{
				m_bRightTurn=false;
				m_dRightOffAngle=m_dSASAngle;
				p_mManualT->TurnAngleDisplay();
			}
		}
		if(m_sLowCanMsg[0].abData[0] & C_LC_SIGLH_SW)
		{
			dwData |= FULL_TR_L_LED;
			if(!m_bLeftTurn)
			{
				m_bLeftTurn=true;
				m_dLeftOnAngle=m_dSASAngle;
				m_dLeftOffAngle=NOT_READ;
				p_mManualT->TurnAngleDisplay();
			}
		}
		else
		{
			if(m_bLeftTurn)
			{
				m_bLeftTurn=false;
				m_dLeftOffAngle=m_dSASAngle;	// off
				p_mManualT->TurnAngleDisplay();
			}
		}
#endif
//		AxdoNWriteOutportByte(0,Do_1,0,dwData);

}


LRESULT CSAS_1Dlg::OnTraceUpdateMsg(WPARAM wParam, LPARAM lParam)
{
	if(!p_mSasAuTest->m_fCanEnable)
		return 0;

	CString strData;
		
	DWORD dwData=0;
		
	BYTE	temp;

//

// wParam = 0 B-CAN, 3=C-CAN
// lParam = 0 Txdata,1 RXdata
//	AfxMessageBox("CAN message On");

// 	printf("%d ",wParam);
// 	strData.Format("%d",wParam);
//	AfxMessageBox(strData);
//	p_mSasAuTest->AddString(strData);	// list box 추가 처리 한다.
#ifdef USE_IXXAT
	switch(wParam)
	{ 
	case B_CAN:

//		strData.Format("B_CAN RX %04X ", m_BCan.m_sCanMsg.dwMsgId); 
//		0x110 == AG model  0x138 == ??

		if(m_CurTabNum ==0) return 0;
// 현재 tab number =1 인 경우만..또는 0 아닌경우 만..
		switch(m_BCan.m_sCanMsg.dwMsgId)
		{
		case 0x138:
			Default_MFSW();
			break;
		case 0x110:
			AG_MFSW();
			break;
		default:
//
			return 0;
			break;
		}
// 
	 
		return 0;	// 변경
		break;
//
	case C_CAN:


		if(lParam)
			strData.Format("RX %04X ", m_clCan.m_sCanMsg.dwMsgId);
		else
			strData.Format("TX %04X ", m_clCan.m_sCanMsg.dwMsgId);

		if(m_CurTabNum ==0)
		{
			for(int i=0;i<8;i++)
				strData.AppendFormat("%02X ",m_clCan.m_sCanMsg.abData[i]);
		}
///////////////// 2015.01.6 추가 

		if(!m_fValidData)
			p_mSasAuTest->AddString(strData);	// list box 추가 처리 한다.
////////////////
 		if(m_clCan.m_sCanMsg.dwMsgId==0x138)
		{
			RJ_MFSW();
			return 0;
		}


		if((m_clCan.m_sCanMsg.dwMsgId!=m_SelModel.dwTBID) && (m_clCan.m_sCanMsg.dwMsgId!=m_SelModel.dwVCID))
			return 0;	// 변경
		m_tCanRev=clock();
// 각도 message
		if(m_clCan.m_sCanMsg.dwMsgId == m_SelModel.dwVCID)
		{
			p_mSasAuTest->m_strResultD[4].Format("%02X,%02X",m_clCan.m_sCanMsg.abData[m_SelModel.iVersionHighByte],m_clCan.m_sCanMsg.abData[m_SelModel.iVersionLowByte]);		
			p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_reResultD[4]);
			return 0;	//추가
		}

		// 수신 인경우
		if(lParam)
			m_sCanMsg[m_uiHead] = m_clCan.m_sCanMsg;	// Rx message
		else
			m_sCanMsg[m_uiHead] = m_clCan.m_sTxCanMsg;	// TX message
//			
		if(lParam)
		{
//			m_sCanMsg[m_uiHead] = m_clCan.m_sCanMsg;	// Rx message
 			if(m_clCan.m_sCanMsg.dwMsgId== m_SelModel.dwTBID)
			{
	//			static double dServoAngle=0;
//				if(m_fValidData)
		//		dServoAngle = m_clMC.GetFeedBackPos();
//				m_dSASAngle = m_clMC.GetFeedBackPos();

				double dSASAngle;
				double dSpeed;

		// 		int siSASAngle;
					
	//			siSASAngle = (m_sCanMsg[m_uiHead].abData[m_SelModel.iAngleHighByte])<<8 | m_sCanMsg[ m_uiHead].abData[ m_SelModel.iAngleLowByte];
 /*
				if(m_SelModel.dwTBID==0x00C4)//M16 angle calc
				{
 					int siSASAngle;
		 			siSASAngle = (m_sCanMsg[m_uiHead].abData[m_SelModel.iAngleHighByte])<<8 | m_sCanMsg[m_uiHead].abData[m_SelModel.iAngleLowByte];
					siSASAngle = (m_sCanMsg[m_uiHead].abData[m_SelModel.iAngleHighByte])<<8 | m_sCanMsg[ m_uiHead].abData[ m_SelModel.iAngleLowByte];
					siSASAngle /=16;
					siSASAngle -=2048;
					dSASAngle = (double)(siSASAngle);
				}else
 */
				{
 					short int siSASAngle;		// 16 bit sigend value
		 			siSASAngle = m_sCanMsg[m_uiHead].abData[m_SelModel.iAngleHighByte]<<8 | m_sCanMsg[ m_uiHead].abData[ m_SelModel.iAngleLowByte];
					dSASAngle = (double)(siSASAngle) * 0.1;// /10.0;	// *0.1
//					printf("\n %.4f %d ",dSASAngle,siSASAngle);
				}
// 각도값도 3276.7 이면 error 이다.
//		0xFF 는 error 1020		

 				m_dSASSpeed=dSpeed;	// current speed
				if(dSASAngle < 3276)
				{
					p_mSasAuTest->m_strMesInfoD[3].Format("%.2f",dSASAngle);
					p_mSasAuTest->m_strMesInfoD[1].Format("%.2f",dSpeed);
					p_mSasAuTest->m_strMesInfoD[2].Format("%.2f",dServoAngle);
					p_mSasAuTest->m_strMesInfoD[4].Format("%.2f",dServoAngle-dSASAngle);
 					p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_reMesInfoD[4],FALSE);
 					p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_reMesInfoD[3],FALSE);
					p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_reMesInfoD[1],FALSE);
					p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_reMesInfoD[2],FALSE);
					m_dSASAngle=dSASAngle;
				}
				else
					m_dSASAngle=3276.7;		// 2014.11.21 무조건 7fff
				// error display ?? 
// 측정 결과를 저장 한다.
				if(m_fValidData)
				{
//					printf("[m_ulMesMaxCount %d %d]",m_ulMesMaxCount,m_ulCurCnt);
					m_dwCanRev =m_sCanMsg[m_uiHead].dwTime;
					m_pdServoAngle[m_ulCurCnt] = dServoAngle;
					m_pdSASAngle[m_ulCurCnt]= dSASAngle;
					m_pdCurrent[m_ulCurCnt]=m_dReadCur;
					m_pdTime[m_ulCurCnt]=m_dwCanRev-m_dwStart;
//
					if(m_ulCurCnt < (m_ulMesMaxCount-1))
						m_ulCurCnt++;
 //					else
 //						printf("m_ulCurCnt Max %d %d",m_ulCurCnt,m_ulMesMaxCount);
 			 		p_mSasAuTest->DrawGraph(m_ulCurCnt);	// 측정 중인경우..   2015.01.08
					p_mSasAuTest->m_ulCurCnt=m_ulCurCnt;
					m_strCanMessageArray.Add(strData);
				//	strData;// can message 저장 한다.
				}
		
			}
		
		}
	//	else
//			m_sCanMsg[m_uiHead] = m_clCan.m_sTxCanMsg;	// TX message
		m_uiOldHead = m_uiHead++;
		if(m_uiHead >= 100) m_uiHead=0;

		break;
	}
#endif;
	return 0;

}

void CSAS_1Dlg::CanSend(DWORD dwID, int dlc, BYTE* pData,bool fLog)
{
	CString strData;
	strData.Format("TX [%04X] : ",dwID);
	for(int i=0;i<dlc;i++)
		strData.AppendFormat("%02X ",pData[i]);
	if (fLog)
		PrintStr(strData);
 	m_cBCan.WriteData(dwID, dlc, pData);

}

BOOL CSAS_1Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if(pMsg->message == WM_KEYDOWN)
	{
//		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		if(pMsg->wParam == VK_ESCAPE)
			return TRUE;
		if(pMsg->wParam == VK_RETURN )
		{
					// 이곳에 사용될 함수나 처리 구문을 작성하면됨
	 		return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CSAS_1Dlg::MakeMemory(int count)
{

	return;
	if( m_pdSASAngle!=NULL)
	{	delete  m_pdSASAngle;m_pdSASAngle=NULL;}
	if( m_pdServoAngle!=NULL)
	{	delete  m_pdServoAngle;m_pdServoAngle=NULL;}
	if( m_pdSpeed!=NULL)
	{	delete  m_pdSpeed;m_pdSpeed = NULL;	}
	
	if( m_pdDifferAngle!=NULL)
	{	delete  m_pdDifferAngle;m_pdDifferAngle=NULL;}
	
 
 	if( m_pdTime!=NULL)
 	{	delete  m_pdTime; m_pdTime=NULL;	}
			
	if (m_pCanData != NULL)
	{
		delete m_pCanData;
		m_pCanData = NULL;
 	}
// 10 ms  단위 1분 60초= 60 * 100 ms   초당 100 *60
// 1 RPM = 1/60 RPS ,  360 / 60 = 6 초 (1회전)    1도당 = 1000ms/6도= 167ms 필요  1회전 sample 갯수 6초*100=600 [ 초당(1000/10 = 100 개 필요]
	// 6회전 필요 Data Full turn(약6회전)3600개 * 2번 반복 = 7200개면 된다...1 RPS 인경우...

	count = 20000;	// 200 초 
	count = 10000;	// 200 초 
	m_ulMesMaxCount = count;

	m_pdSASAngle = new double[count];
	m_pdServoAngle = new double[count];
	m_pdSpeed = new double[count];
	m_pdDifferAngle = new double[count];
 
	m_pdTime = new unsigned long[count];

	m_pCanData = new CanMsg[m_ulMesMaxCount];

 

}

void CSAS_1Dlg::ReadCnt(void)
{
	int fh;
	
	if(_chdir("D:\\Data")==-1)
	{
		_chdir("D:\\");
		_mkdir("\\Data");
		_chdir("D:\\Data");
	}
	

	if( (fh = _open( "D:\\DATA\\Count.cfg", _O_RDWR | _O_CREAT| _O_BINARY ,_S_IREAD | _S_IWRITE )) != -1 )
	{
		
		_read( fh, m_iGoodCnt, sizeof(m_iGoodCnt));
		_read( fh, m_iNGCnt, sizeof(m_iNGCnt));
		_read( fh, m_iTestCnt, sizeof(m_iTestCnt));
		
		_close( fh );	
	}
}

void CSAS_1Dlg::SaveCnt(void)
{
	int fh;
	

	if(_chdir("D:\\Data")==-1)
	{
		_chdir("D:\\");
		_mkdir("\\Data");
		_chdir("D:\\Data");
	}
	

	if( (fh = _open( "D:\\DATA\\Count.cfg", _O_RDWR | _O_CREAT| _O_BINARY ,_S_IREAD | _S_IWRITE )) != -1 )
	{
		
		_write( fh, m_iGoodCnt, sizeof(m_iGoodCnt));
		_write( fh, m_iNGCnt, sizeof(m_iNGCnt));
		_write( fh, m_iTestCnt, sizeof(m_iTestCnt));
		
		_close( fh );	
	}
}


#ifdef USE_SAVE
void CSAS_1Dlg::WriteMesData(CString strFileName, CTime t, unsigned long dTime, double dServoA, double dSASA, double dDiffer, double dSpeed, double dCurrent)
{
	int fh;
	CString strTemp;
	unsigned long iTime=dTime;
 	CTimeSpan tSpan = CTimeSpan(0,iTime/3600,(iTime%3600)/60,iTime%60);
	t = t+tSpan;
	if( (fh = _open( strFileName, _O_RDWR )) != -1)
	{
		_lseek(fh,0,SEEK_END);
		strTemp.Format("%04d-%02d-%02d %02d:%02d:%02d,",t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
		_write( fh, strTemp.GetBuffer(0), strTemp.GetLength());
		strTemp.Format("%02d:%02d:%02d.%03d,",iTime/3600,(iTime%3600)/60,iTime%60,(int)((dTime-iTime)*1000));
		_write( fh, strTemp.GetBuffer(0), strTemp.GetLength());
		strTemp.Format("%.2f,%.2f,%.2f,%.2f,%d\n",dServoA,dSASA,dSpeed,dDiffer,m_ulCurCnt);
		_write( fh, strTemp.GetBuffer(0), strTemp.GetLength());
		_close( fh );	
	}else
	{
		
		if( (fh = _creat( strFileName, _S_IREAD | _S_IWRITE )) != -1 )
		{
			strTemp.Format("Current Time,SAS Time,Data,Servo Angle,SAS Angle,SAS Speed,Differ Angle,count=%d\n",m_ulMesMaxCount);
			_write(fh, strTemp.GetBuffer(0),strTemp.GetLength());
			strTemp.Format("%04d-%02d-%02d %02d:%02d:%02d,",t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
			_write( fh, strTemp.GetBuffer(0), strTemp.GetLength());
			strTemp.Format("%02d:%02d:%02d.%03d,",iTime/3600,(iTime%3600)/60,iTime%60,(int)((dTime-iTime)*1000));
			_write( fh, strTemp.GetBuffer(0), strTemp.GetLength());
			strTemp.Format("%.2f,%.2f,%.2f,%.2f,%.2f\n",dServoA,dSASA,dSpeed,dDiffer,dCurrent);
			_write( fh, strTemp.GetBuffer(0), strTemp.GetLength());
			_close( fh );
		}


	}

}
#endif

// 2014.11.21 can message 
void CSAS_1Dlg::WriteMesData1(CString strFileName, CTime t, unsigned long dTime, double dServoA, double dSASA, double dDiffer, double dSpeed,int i)
{
 

	int fh;
	CString strTemp;
	CString strTemp1;

	unsigned long iTime=dTime;
	int j;
	CTimeSpan tSpan = CTimeSpan(0,iTime/3600,(iTime%3600)/60,iTime%60);
	t = t+tSpan;
//	printf("\n%d <%s>",m_strCanMessageArray[i]);
//	printf("\n total message count %d %d .%s.",i,m_ulCurCnt,m_strCanMessageArray[i]);
	strTemp1 = "";
	return;
	for (j = 0; j < 8; j++)
		strTemp1.AppendFormat("%02X ", m_pCanData[i].abData[j]);
 
	if( (fh = _open( strFileName, _O_RDWR )) != -1)
	{
		_lseek(fh,0,SEEK_END);
		strTemp.Format("%04d-%02d-%02d %02d:%02d:%02d,",t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
		_write( fh, strTemp.GetBuffer(0), strTemp.GetLength());
//		strTemp.Format("%02d:%02d:%02d.%ld,",iTime/3600,(iTime%3600)/60,iTime%60, dTime);
		strTemp.Format("%ld,", dTime);
		_write( fh, strTemp.GetBuffer(0), strTemp.GetLength());
//		strTemp.Format("%.2f,%.2f,%.2f,%.2f,%d,%s\n",dServoA,dSASA,dSpeed,dDiffer,m_ulCurCnt,strTemp);
		strTemp.Format("%s,%.1f,%.1f,%.1f\n", strTemp1,dServoA, dSASA, dSpeed);
		_write( fh, strTemp.GetBuffer(0), strTemp.GetLength());
		_close( fh );	
	}else
	{
		
		if( (fh = _creat( strFileName, _S_IREAD | _S_IWRITE )) != -1 )
		{
			strTemp.Format("Current Time,SAS Time,Message,Servo Angle,SAS Angle,SAS Speed,Differ Angle,count=%d,message\n",m_ulMesMaxCount);
			_write(fh, strTemp.GetBuffer(0),strTemp.GetLength());
			strTemp.Format("%04d-%02d-%02d %02d:%02d:%02d,",t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
			_write( fh, strTemp.GetBuffer(0), strTemp.GetLength());
//			strTemp.Format("%02d:%02d:%02d.%ld,",iTime/3600,(iTime%3600)/60,iTime%60,(iTime - dTime));
			strTemp.Format("%ld,", dTime);
			_write( fh, strTemp.GetBuffer(0), strTemp.GetLength());
		//	strTemp.Format("%.2f,%.2f,%.2f,%.2f,%d,%s\n",dServoA,dSASA,dSpeed, dDiffer, m_ulCurCnt,strTemp);
			strTemp.Format("%s,%.1f,%.1f,%.1f\n", strTemp1, dServoA, dSASA, dSpeed);

			_write( fh, strTemp.GetBuffer(0), strTemp.GetLength());
			
			_close( fh );
		}
//		WriteMesData1(strFile, m_tStartTest, m_pdTime[i], m_pdServoAngle[i], m_pdSASAngle[i], m_pdDifferAngle[i], m_pdSpeed[i], i);


	}
//	printf("\n%d %.1f   %.1f  %.1f", i, dServoA, dSASA, dSpeed);

}

void CSAS_1Dlg::SaveMeaData(void)
{
	CTime t = CTime::GetCurrentTime();
	CString strTemp;
	CString strFile;
	strFile = m_strReportFile;
	strTemp.Format("%04d%02d%02d%02d%02d%02d",t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
	strFile.Insert(m_strReportFile.GetLength()-4,strTemp);


	CString cMessage;
	unsigned long str_count=0;
 	printf("\nSaveMeaData() total message count %d %d ..%d.",str_count,m_ulMesMaxCount,m_ulCurCnt);
	strTemp.Format("SaveMeaData() total message count % d % d .. % d.",str_count,m_ulMesMaxCount,m_ulCurCnt);
	PrintStr(strTemp);
	p_mSasAuTest->OutMessage("Save Data");
	int i;
	int end = m_ulCurCnt;
	for(i=1;i< end ;i++)
	{	
		WriteMesData1(strFile,m_tStartTest,m_pdTime[i],m_pdServoAngle[i],m_pdSASAngle[i],m_pdDifferAngle[i],m_pdSpeed[i],i);
	}
	p_mSasAuTest->OutMessage("Save End");

	 
}

void CSAS_1Dlg::UserStop(void)
{

	p_mSasAuTest->OutMessage("사용자 중지");
	p_mSasAuTest->m_iJudgeMode=5;
	p_mSasAuTest->Invalidate();

}
 

 
void CSAS_1Dlg::LinValueSet(void)
{

		if(m_CurTabNum ==0) return ;
// 현재 tab number =1 인 경우만..
	DWORD dwData=0;
	BYTE	temp;

//////////////////////////
// wipper-lo,hi,whsher-f,r, headlamp low, tail ,auto,rear for
		if(	m_LinData[1] & C_R_FOG_SW)
				dwData =RR_FOG_LED;

		if(	m_LinData[2] & C_WIPPER_LO_SW)
				dwData |= WIPER_LO_LED;

		if(	m_LinData[2] & C_WIPPER_HI_SW)
				dwData |= WIPER_HI_LED;

		if(	m_LinData[2] & C_WIPPER_WASHER_SW)
				dwData |= WASHER_F__LED;
// 아직 할당 되지 않음..
/*
		if(	m_sLowCanMsg[0].abData[1] & C_WIPPER_RWASHER_SW)
				dwData |= WASHER_R__LED;
*/
		//		DWORD dwData1=0;

		switch (m_LinData[1] & 0x30)
		{
// light off
		
		case 0x10:
				dwData |= TAIL_LED;
				break;
		case 0x20:
				dwData |= HLAMP_LO_LED;
				break;
		case 0x30:
				dwData |= AUTO_LED;
				break;
		}
		

//		AxdoNWriteOutportByte(0,Do_1,1,dwData);
//
// WASHER Rear 현재 할 당 안됨. lamp 출력도 없다.
/*
		if(	m_sLowCanMsg[0].abData[1] & C_WIPPER_AUTO_SW)
				dwData |= AUTO_LED;
*/
		temp=(m_LinData[2] & 0xe) >> 1;
		dwData = 2 << temp;	//
		if(	m_LinData[1] & C_F_FOG_SW)
			dwData |=1; 
	//	AxdoNWriteOutportByte(0,Do_1,2,dwData);
////------------------
		if(m_LinData[1] & C_PASS_SW)
			dwData = PASSING_LED;
		else 
			dwData = 0;

		if(m_LinData[1] & C_HL_HIGH_SW)		// Dimmer
			dwData |= HL_HIGH_LED;
// 2015.01.09
		if(m_LinData[3] & C_T_SIGLH_SW)
			dwData |= CHANG_LH_LED;
		if(m_LinData[3] & C_T_SIGRH_SW)
			dwData |= CHANG_RH_LED;
		if(m_LinData[2] & C_WIPPER_INT_SW)
			dwData |= INT_LED;
		if(m_LinData[3] & C_WIPPER_MIST_SW)
			dwData |= MIST_LED;
////// 2014.12.09 부분 변경 각도 표기 기능
/////////////////////////////////////////////////////
		if(m_LinData[1] & C_LC_SIGRH_SW)
		{
			dwData |= FULL_TR_R_LED;
			if(!m_bRightTurn)
			{
				m_bRightTurn=true;	// current angle display
				m_dRightOnAngle=m_dSASAngle;		//NOT_READ
				m_dRightOffAngle=NOT_READ;


				p_mManualT->TurnAngleDisplay();
			}
		}
		else
		{
			if(m_bRightTurn)
			{
				m_bRightTurn=false;
				m_dRightOffAngle=m_dSASAngle;
				p_mManualT->TurnAngleDisplay();
			}
		}
		if(m_LinData[1] & C_LC_SIGLH_SW)
		{
			dwData |= FULL_TR_L_LED;
			if(!m_bLeftTurn)
			{
				m_bLeftTurn=true;
				m_dLeftOnAngle=m_dSASAngle;
				m_dLeftOffAngle=NOT_READ;
				p_mManualT->TurnAngleDisplay();
			}
		}
		else
		{
			if(m_bLeftTurn)
			{
				m_bLeftTurn=false;
				m_dLeftOffAngle=m_dSASAngle;	// off
				p_mManualT->TurnAngleDisplay();
			}
		}

	//	AxdoNWriteOutportByte(0,Do_1,0,dwData);

		printf("\n");

		for(int i=0;i<5;i++)
			printf("%02x ",m_LinData[i]);

}

 
void CSAS_1Dlg::SMC_Init(short ch, bool fMode)
{
	CString strTemp;
	short mOutData, mLimitSts;
	int i;
//	if (fMode)
	{
		dwRet = SmcWGetPulseType(Test.m_hSMCID, ch, &PulseType, &DirTimer);
		dwRet = SmcWGetEncType(Test.m_hSMCID, ch, &EncType);
		dwRet = SmcWGetCtrlTypeOut(Test.m_hSMCID, ch, &CtrlOut1, &CtrlOut2, &CtrlOut3);
		dwRet = SmcWGetCtrlTypeIn(Test.m_hSMCID, ch, &CtrlIn);
		dwRet = SmcWGetOrgLog(Test.m_hSMCID, ch, &OrgLog);
		dwRet = SmcWGetCtrlInOutLog(Test.m_hSMCID, ch, &CtrlInOutLog);
		dwRet = SmcWGetErcMode(Test.m_hSMCID, ch, &ErcMode);
		dwRet = SmcWGetErcAlmClearTime(Test.m_hSMCID, ch, &ErcTime, &ErcOffTimer, &AlmTime);
		dwRet = SmcWGetOrgMode(Test.m_hSMCID, ch, &LimitTurn, &OrgType, &EndDir, &ZCount);
		dwRet = SmcWGetSAccelType(Test.m_hSMCID, ch, &SAccelType);
		dwRet = SmcWGetInFilterType(Test.m_hSMCID, ch, &FilterType);
		dwRet = SmcWGetSDMode(Test.m_hSMCID, ch, &SDMode);
		dwRet = SmcWGetCounterMode(Test.m_hSMCID, ch, &ClearCntLtc, &LtcMode, &ClearCntClr, &ClrMode);
		dwRet = SmcWGetInitParam(Test.m_hSMCID, ch, &InitParam);


		strTemp.Format("PulseType=%d DirtTimer=%d  Enctype=%d", PulseType, DirTimer, EncType);//4,1,0 pulset type 5 필요,(CW/CCW High Enctype= 4phase
		PrintStr(strTemp);
		strTemp.Format("CtrlType out1=%d out2=%d out3=%d ", CtrlOut1, CtrlOut2, CtrlOut3);	//0,0,0
		PrintStr(strTemp);
		strTemp.Format("CtrlTypein 1=%d  Orglog=%d ", CtrlIn, OrgLog);			//1,0
		PrintStr(strTemp);
		strTemp.Format("CtrlInoutLog=%03X ErcMode=%d", CtrlInOutLog, ErcMode);	//0,0
		PrintStr(strTemp);
		strTemp.Format("ErcAlmClearTime %d  %d  %d ", ErcTime, ErcOffTimer, AlmTime);
		PrintStr(strTemp);
		strTemp.Format("LimitTurn %d  =OrgType%d  %d zCount=%d", LimitTurn, OrgType, EndDir, ZCount);//1,0,0,1
		PrintStr(strTemp);
		strTemp.Format("SAfceltype =%d ", SAccelType);				//0 
		PrintStr(strTemp);
		strTemp.Format("inFilterType =%d  SDMode=%d", FilterType, SDMode);	// 0,0
		PrintStr(strTemp);
		strTemp.Format("tCounterMode ClearCntLtc=%d &LtcMode=%d ClearCntClr=%d ClrMode=%d", ClearCntLtc, LtcMode, ClearCntClr, ClrMode);//0,0,0,0
		PrintStr(strTemp);
	//	SmcWSetDigitalOut(Test.m_hSMCID,0,)
		
		PulseType = 5;
		DirTimer = 1;
		LimitTurn = 1;
		ZCount = 1;
		SAccelType = 1;
		CtrlIn = 1;

		dwRet = SmcWGetLimitStatus(Test.m_hSMCID, ch, &mLimitSts);
		if (dwRet) {
			SmcWGetErrorString(dwRet, ErrorString);
			DispComment(_T("SmcWGetLimitStatus"), ErrorString);
			//		return;
		}
		dwRet = SmcWGetDigitalOut(Test.m_hSMCID, ch, &mOutData);
		//	if ((OutData & CSMC_OUT1) == CSMC_OUT1)	// 0x1
 //	dwRet = SmcWSetDigitalOut(Test.m_hSMCID,1, CSMC_OUT2, CSMC_OUT2);

	}
//	else
	{
		PulseType = 5;
		DirTimer = 1;
		LimitTurn = 1;
		ZCount = 1;
		SAccelType = 1;
		CtrlIn = 1;
		EncType = 2;	// 0->1,2  2 로 해야 된다.... A/B two-phase input
		CtrlInOutLog = 0x01;	//1~7 input , limit is bit7 low active 로 한다.. bit0 = alarm 상태 값         bit9,10,11 outlogic (0,1,2)    bit7 is limit 0= low 1 = high
 
		for (i = 0; i < 4; i++)
		{
			ch = i + 1;
			dwRet = SmcWSetPulseType(Test.m_hSMCID, ch, PulseType, DirTimer);	// CW CCW High
			dwRet = SmcWSetEncType(Test.m_hSMCID, ch, EncType);
			dwRet = SmcWSetCtrlTypeOut(Test.m_hSMCID, ch, CtrlOut1, CtrlOut2, CtrlOut3);
			dwRet = SmcWSetCtrlTypeIn(Test.m_hSMCID, ch, CtrlIn);
			dwRet = SmcWSetOrgLog(Test.m_hSMCID, ch, OrgLog);
////1~7 input , limit is bit7 low active 로 한다.. bit0 = alarm 상태 값         bit9,10,11 outlogic (0,1,2)    bit7 is limit
			if (i > 0) CtrlInOutLog = 0;
			else CtrlInOutLog = 1;
			dwRet = SmcWSetCtrlInOutLog(Test.m_hSMCID, ch, CtrlInOutLog);

			if (dwRet) {
				SmcWGetErrorString(dwRet, ErrorString);
				DispComment(_T("SmcWSetCtrlInOutLog"), ErrorString, ch);
				strTemp.Format("ch= %d %04X", ch, CtrlInOutLog);
				PrintStr(strTemp);

			}
			else
			{
				strTemp.Format("ch= %d %04X", ch, CtrlInOutLog);
				PrintStr(strTemp);
			}

			dwRet = SmcWSetErcMode(Test.m_hSMCID, ch, ErcMode);

			dwRet = SmcWSetErcAlmClearTime(Test.m_hSMCID, ch, ErcTime, ErcOffTimer, AlmTime);
			dwRet = SmcWSetOrgMode(Test.m_hSMCID, ch, LimitTurn, OrgType, EndDir, ZCount);
			dwRet = SmcWSetSAccelType(Test.m_hSMCID, ch, SAccelType);
			dwRet = SmcWSetInFilterType(Test.m_hSMCID, ch, FilterType);
			dwRet = SmcWSetSDMode(Test.m_hSMCID, ch, SDMode);
			dwRet = SmcWSetCounterMode(Test.m_hSMCID, ch, ClearCntLtc, LtcMode, ClearCntClr, ClrMode);
			dwRet = SmcWSetInitParam(Test.m_hSMCID, ch);
			//		Test.DioOut(JIG_CARD_NUM,1,SERVO_ON|SERVO_CWLIM| SERVO_CCWLIM,ON);SERVO_ENABLE
		//	Test.DioOut(JIG_CARD_NUM, 1, SERVO_ENABLE, ON);//SERVO_ENABLE

			dblTargetSpeed = 50000;		// 1638300		16383
 
			dblResolveSpeed = 10;
			dblTargetSpeed = 50000;
			SmcWSetResolveSpeed(Test.m_hSMCID, ch, dblResolveSpeed);
 			SmcWSetTargetSpeed(Test.m_hSMCID, ch, dblTargetSpeed);

		}

		short OutVal;



		Test.SerVoReset(ON);
		Test.SerVo(OFF);
		Sleep(50);
		SmcWGetDigitalOut(Test.m_hSMCID, 1, &OutVal);
		strTemp.Format("Server Out = %d", OutVal);
		PrintStr(strTemp);

		Test.SerVo(OFF);
		Test.SerVoReset(OFF);
		Sleep(50);
		SmcWGetDigitalOut(Test.m_hSMCID, 1, &OutVal);
		strTemp.Format("Server Out = %d", OutVal);		// 결과 값이 0 아니면 restart 해야 된다...
		PrintStr(strTemp);

		SmcWGetDigitalOut(Test.m_hSMCID, 1, &OutVal);



		//	Test.DioOut(DO_32, 0, X1SERVO_ON | Y1SERVO_ON | Z1SERVO_ON, ON);
		//	Test.DioOut(DO_32, 1, X2SERVO_ON | Y2SERVO_ON | Z2SERVO_ON | Z1_BREAK | Z2_BREAK, ON);

		dwRet = SmcWGetLimitStatus(Test.m_hSMCID, ch, &mLimitSts);
		if (dwRet) {
			SmcWGetErrorString(dwRet, ErrorString);
			DispComment(_T("SmcWGetLimitStatus"), ErrorString);

		}
	}

}

void CSAS_1Dlg::DispComment(char* func, char* msg, short ch)
{
	CString wStr;
	wStr.Format("(%d)%s: %s", ch, func, msg);
	PrintStr(wStr);
}

void CSAS_1Dlg::PrintStr(CString String)
{
//	CString temp;
	int i;
	i = m_ctlListBox.AddString(String);		// 항상맨뒤에 한다.. 속성중sort 가 true 인경우문제있다/
	if (m_ctlListBox.GetCount() > 30) m_ctlListBox.DeleteString(0);
	m_ctlListBox.SetCurSel(m_ctlListBox.GetCount() - 1);		// 초기값이 -1

}



static int rxLen = 0;
static int index = 0;
BYTE TxFData[8] = { 0x30, 8, 0x0a, 0, 0, 0 };	// Flow control frame


LRESULT CSAS_1Dlg::OnCanSASReceive(WPARAM wParam, LPARAM lParam)
{
//	CKEYBOARDDoc* pDoc = GetDocument();

	int i;
	CString strTemp;
	CString strData;


	BYTE cData[64];
	long id = 0;
	bool fLog = true;
	bool fChange;
	unsigned int dlc = 0;
//	double dSpeed;
	unsigned long timestamp=0;
		
	if (wParam == m_cCCan.m_hCan)
	{
 		i = m_cCCan.ReadDataFD(id, dlc, cData, timestamp);
	//	i = m_cCCan.ReadDataFD(id, dlc, cData);

		//	printf("\n%d id=%X  dlg=%d ", i, id, dlc);
		if (i != canOK) return 0;
		switch (id)
		{
		case SAS_GST:
			break;


		case 0x125:
			if (dlc > 32) dlc = 32;
			// 3,4,5,7 값중 하나라도 바뀌면....
			fChange = false;
		//	printf("\n%d", timestamp);
			dlc = 8;
			for (i = 0; i < dlc; i++)
			{
				m_cData_SAS[i] = cData[i];// m_CData_M02
/* 				if (m_fValidData)
				{
					m_pCanData[m_ulCurCnt].abData[i] = cData[i];
				}
*/										  //		printf("%02X ", cData[i]);
			}
			m_iSASAngle = m_cData_SAS[4];
			m_iSASAngle = m_iSASAngle << 8;
			m_iSASAngle |= m_cData_SAS[3];
			m_dAngle = (m_iSASAngle / 10.);
			m_bSAS_Status = cData[6];


			if (m_fConnectTimeCheck)
			{
				m_tCanRev = clock();
				m_fConnectTimeCheck = false;
			}
 


			m_iSASAngle = m_cData_SAS[4];
			m_iSASAngle = m_iSASAngle << 8;
			m_iSASAngle |= m_cData_SAS[3];
			m_dAngle = (m_iSASAngle / 10.);
			m_bSAS_Status = cData[6];
 
			//			m_dSASSpeed = (double)(m_cData_SAS[m_SelModel.iSpeedByte]) * 4;	//항상 4로(분해능)
			m_dSASSpeed = (double)(m_cData_SAS[5]) * 4;	//항상 4로(분해능)

#ifdef DIS_TYPE1

			p_mSasAuTest->m_strMesInfoD[2].Format("%.2f", m_dAngle);
			p_mSasAuTest->m_strMesInfoD[1].Format("%.2f", m_dSASSpeed);
			p_mSasAuTest->m_strMesInfoD[3].Format("%.2f", m_pdServoAngle[0]);
		//	p_mSasAuTest->m_strMesInfoD[4].Format("%.2f", m_pdServoAngle[0] - m_dAngle);

			p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_reMesInfoD[3], FALSE);
		//	p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_reMesInfoD[0], FALSE);
			p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_reMesInfoD[1], FALSE);
			p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_reMesInfoD[2], FALSE);


//			m_dSASSpeed;
//			dSpeed = (double)(m_sCanMsg[m_uiHead].abData[m_SelModel.iSpeedByte]) * 4;	//항상 4로(분해능)
//			m_dSASSpeed = dSpeed;	// current speed


//			m_dSASAngle
			m_strSASAngle.Format("%.1f", m_dAngle);
			m_strSASSpeed.Format("%02d %02X", m_cData_SAS[5], m_cData_SAS[6]);// status


			if ((m_fValidData)&& (m_ulCurCnt < (m_ulMesMaxCount-1)))
			{
				m_pdTime[m_ulCurCnt]=  timestamp;

				m_pdSASAngle[m_ulCurCnt] = m_dAngle;
#ifdef NO_CONTROL
				m_pdServoAngle[m_ulCurCnt] = m_dAngle;
				m_pdServoAngle[0] = m_dAngle;
#else
				SmcWGetCountPulse(Test.m_hSMCID, 1, &mlCurrentPos);
				m_pdServoAngle[0] = mlCurrentPos / 100.;			// 이곳에서만 사용


//				SmcWGetCountPulse(Test.m_hSMCID, 1, &m_lCountPulse);
//				m_pdServoAngle[0] = m_lCountPulse / 100.;

#endif
 				m_pdDifferAngle[m_ulCurCnt] = m_dAngle - m_pdServoAngle[0];
				m_pdServoAngle[m_ulCurCnt] = m_pdServoAngle[0];
				m_pdSpeed[m_ulCurCnt] = m_dSASSpeed;
 
		 		p_mSasAuTest->DrawGraph(m_ulCurCnt);	// 측정 중인경우..   2015.01.08
				m_ulCurCnt++;
 	 
	  			
 
			}
#endif
			//GetDlgCtrlID(IDC_SAS_ANGLE);
 
			break;
		default:
			break;
		}

	}
	else if (wParam == m_cBCan.m_hCan)
	{

		i = m_cBCan.ReadDataFD(id, dlc, cData);
		if (i != canOK) return 0;
		switch (id)
		{
		case MFSW_GST:

 			strData.Format("RX [%03X (%d)] :", id,dlc);
			for (i = 0; i < 8; i++)
			{
				m_CData_DIG[i] = cData[i];
				strData.AppendFormat(" %02X", cData[i]);
			}
 			PrintStr(strData);
			switch (cData[0] >> 4)
			{
			case MESSAGE_TYPE_FIRST_VALUE:
				CanSend(m_SelModel.dwMFSWID, 8, TxFData);
				i = cData[1] - 6;
				rxLen = i / 7;
				if (i % 7) rxLen++;
				m_iMultyRxIndex = 1;
				for (i = 0; i < 8; i++)
					m_cData_mDIG[0][i] = cData[i];
 				break;
			case MESSAGE_TYPE_CONSECUTIVE_VALUE:
				index = cData[0] - 0x20;// cData[0] & 0x1f;
				for (i = 0; i < dlc; i++)
					m_cData_mDIG[index][i] = cData[i];		// max 32 byte
 
				rxLen--;
				m_iMultyRxIndex++;
				if (rxLen == 0)
				{
					m_fMultyRxDone = true;
 				}
				break;
			case MESSAGE_TYPE_FLOW_VALUE:
				i = 0;
				while (m_iMultyTransLen > 0)
				{
					CanSend(m_SelModel.dwMFSWID, 8,m_cMultyTxData[i++]);
					Sleep(30);
					m_iMultyTransLen--;

				}
				m_fMultyTrans = true;
				m_fDiagRev = m_fDiagRevSing = false;
				break;

 			case MESSAGE_TYPE_SINGLE_VALUE:
				if (!m_fDiagRev)
				{
					if ((cData[1] == 0x7f) && (cData[3] == 0x78))
						break;
					else
						m_fDiagRev = m_fDiagRevSing = true;
 				}
				break;
			default:
				break;
			}

			//			GST_MFSW;

			break;

		default:
			break;
		}

	}
 
 
	return 0;

}




//void CSAS_1Dlg::OnBnClickedButton1()
//{
//	PrintStr("++++++++++");
//	SMC_Init(1, true);
//	Test.BitOut(1, S_ON, ON);
//	Test.SerVo(ON);
// }


//void CSAS_1Dlg::OnBnClickedButton2()
//{
//	Test.BitOut(1, S_ON, OFF);
//	Test.SerVo(OFF);
//}


//void CSAS_1Dlg::OnBnClickedButton3()
//{
//	Test.SerVoReset(ON);
//	p_mManualT->m_stcValue[1].SetWindowTextA("ServoReset");
// }


//void CSAS_1Dlg::OnBnClickedButton4()
//{
//	Test.SerVoReset(OFF);
//	p_mManualT->m_stcValue[1].SetWindowTextA("ServoReset Off");
//	 
//
//}


void CSAS_1Dlg::Security_Access()
{

}

bool CSAS_1Dlg::SetMoveParam(short ch)
{

	dwRet = SmcWSetResolveSpeed(Test.m_hSMCID, ch, dblResolveSpeed); // Set Resolution to Driver
	if (dwRet) {
		SmcWGetErrorString(dwRet, ErrorString);
		DispComment("SmcWSetResolveSpeed", ErrorString, ch);
		return FALSE;
	}
	dwRet = SmcWSetStartSpeed(Test.m_hSMCID, ch, dblStartSpeed);// Set StartSpeed to Driver
	dwRet = SmcWSetTargetSpeed(Test.m_hSMCID, ch, dblTargetSpeed); // Set TargetSpeed to Driver

	dwRet = SmcWSetAccelTime(Test.m_hSMCID, ch, dblAccelTime);// Set AccelTime to Driver
	dwRet = SmcWSetDecelTime(Test.m_hSMCID, ch, dblDecelTime);// Set AccelTime to Driver
//	
	dwRet = SmcWSetSSpeed(Test.m_hSMCID, ch, dblSSpeed);     // Set SSpeed to Driver 설정값은
//	m_sStartDir = CSMC_CW;//;CSMC_CW
	Test.m_sStartDir = m_sStartDir;
	//	
	bCoordinate = CSMC_INC;	//CSMC_ABS
	MotionType = CSMC_PTP;	// YGK 25.05.20 강제로
	if (MotionType == CSMC_PTP && bCoordinate == CSMC_INC)
	{
		lDistance = abs(lDistance);
		if (m_sStartDir == CSMC_CCW)
		{
			lDistance = -1 * (lDistance);
		}
	}
//
	dwRet = SmcWSetStopPosition(Test.m_hSMCID, ch, bCoordinate, lDistance);
	if (dwRet) {
		SmcWGetErrorString(dwRet, ErrorString);
		DispComment("SmcWSetStopPosition", ErrorString);
		return FALSE;
	}

	return true;
}

void CSAS_1Dlg::DrawG()
{
	long m_lCountPulse;
 
 
//	m_dAngle;

#ifdef DIS_TYPE1

	if (m_fValidData)
	{
		if ( (m_ulDrawCnt < m_ulCurCnt))
		{
		//	m_ulDrawCnt++;
		//	p_mSasAuTest->DrawGraph(m_ulDrawCnt);	// 측정 중인경우..   2015.01.08
		}
	}
	else
	{
		p_mSasAuTest->m_strMesInfoD[1].Format("%.2f", m_dAngle);
		p_mSasAuTest->m_strMesInfoD[2].Format("%.2f", m_dSASSpeed);
		p_mSasAuTest->m_strMesInfoD[3].Format("%.2f", m_pdServoAngle[0]);
		p_mSasAuTest->m_strMesInfoD[4].Format("%.2f", m_pdServoAngle[0] - m_dAngle);

		p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_reMesInfoD[3], FALSE);
		p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_reMesInfoD[0], FALSE);
		p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_reMesInfoD[1], FALSE);
		p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_reMesInfoD[2], FALSE);
	}
#else
#ifdef NO_CONTROL
	m_pdServoAngle[0] = m_dAngle;
#else

	DWORD tick = timeGetTime();
	dwRet = SmcWGetCountPulse(Test.m_hSMCID, 1, &m_lCountPulse);
	m_pdServoAngle[0] = m_lCountPulse / 100.;
	
#endif 
	//	m_dAngle;
	int i;
	p_mSasAuTest->m_strMesInfoD[1].Format("%.2f", m_dAngle);
	p_mSasAuTest->m_strMesInfoD[2].Format("%.2f", m_dSASSpeed);
	p_mSasAuTest->m_strMesInfoD[3].Format("%.2f", m_pdServoAngle[0]);
	p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_reMesInfoD[3], FALSE);
	p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_reMesInfoD[1], FALSE);
	p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_reMesInfoD[2], FALSE);
	//	p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_reMesInfoD[0], FALSE);
	//	p_mSasAuTest->m_strMesInfoD[4].Format("%.2f", m_pdServoAngle[0] - m_dAngle);

	if ((m_fValidData) && (m_ulCurCnt < (m_ulMesMaxCount - 1)))
	{
		m_ulCurCnt++;
		m_pdServoAngle[m_ulCurCnt] = m_pdServoAngle[0];
		m_pdSASAngle[m_ulCurCnt] = m_dAngle;
		m_pdDifferAngle[m_ulCurCnt] = m_dAngle - m_pdServoAngle[0];
		m_pdSpeed[m_ulCurCnt] = m_dSASSpeed;
  	 	for(i=0;i<8;i++)
			m_pCanData[m_ulCurCnt].abData[i] = m_cData_SAS[i]; 

	 	m_pdTime[m_ulCurCnt] = tick;

		p_mSasAuTest->DrawGraph(m_ulCurCnt);	// 측정 중인경우..   2015.01.08	}
	}
#endif
//m_ulDrawCnt
//
 
}


#ifdef USE_Motion
int CSAS_1Dlg::Motion(double dTargetSpeed, long distance, short ch, short Dir, short MotionType)
{
	CString strTemp;
	dblTargetSpeed = dTargetSpeed;
	lDistance = distance;
	//long countpulse;
	int i;
	dblResolveSpeed = 10;
	dblResolveSpeed = 10;
	dwRet = SmcWSetResolveSpeed(Test.m_hSMCID, ch, dblResolveSpeed); // Set Resolution to Driver
	if (dwRet) {
		SmcWGetErrorString(dwRet, ErrorString);
		DispComment("SmcWSetResolveSpeed", ErrorString, ch);
		return FALSE;
	}
	dwRet = SmcWSetStartSpeed(Test.m_hSMCID, ch, dblStartSpeed);// Set StartSpeed to Driver
	dwRet = SmcWSetTargetSpeed(Test.m_hSMCID, ch, dTargetSpeed); // Set TargetSpeed to Driver

	dwRet = SmcWSetAccelTime(Test.m_hSMCID, ch, dblAccelTime);// Set AccelTime to Driver
	dwRet = SmcWSetDecelTime(Test.m_hSMCID, ch, dblDecelTime);// Set AccelTime to Driver

//	
	dwRet = SmcWSetSSpeed(Test.m_hSMCID, ch, dblSSpeed);     // Set SSpeed to Driver
	if (MotionType == CSMC_PTP && bCoordinate == CSMC_INC)
	{
		distance = abs(distance);
		if (Dir == CSMC_CCW)
		{
			distance = -1 * (distance);
		}
	}

	dwRet = SmcWSetStopPosition(Test.m_hSMCID, ch, bCoordinate, distance);
	if (dwRet) {
		SmcWGetErrorString(dwRet, ErrorString);
		DispComment("SmcWSetStopPosition", ErrorString, ch);
		return FALSE;
	}
	dwRet = SmcWSetReady(Test.m_hSMCID, ch, MotionType, m_sStartDir);// Ready motion
	if (dwRet != 0)
	{
		SmcWGetErrorString(dwRet, ErrorString);
		DispComment("SmcWSetReady", ErrorString, ch);
	}
	//	SmcWGetReady(Test.m_hSMCIDD,1, &MotionType,&StartDir);
	//	CString strTemp;
	//	strTemp.Format("%d %d",MotionType,StartDir);
	//	AfxMessageBox(strTemp);
//	dwRet = SmcWSetStopPosition(Test.m_hSMCIDD, 1, bCoordinate, lDistance);

	strTemp.Format("Motion Start %.f %d %d", dTargetSpeed, distance, bCoordinate);
	PrintStr(strTemp);
	
	dwRet = SmcWMotionStart(Test.m_hSMCID, ch);
	if (dwRet != 0)
	{
		SmcWGetErrorString(dwRet, ErrorString);
		DispComment("SmcWMotionStart", ErrorString, ch);
	}

 
	return 0;
}

#endif


int CSAS_1Dlg::MoveCheck()
{
	bool test = false;
	short StopSts;
	int retVal = 1;
	while (1)
	{
		if (p_mSasAuTest->m_iStopMode == 1)
		{
 			return -1;
 		}
#ifdef NO_CONTROL
		
		StopSts = CSMC_STOP_NORMAL;

#else
		Sleep(0);
		dwRet = SmcWGetStopStatus(Test.m_hSMCID, 1, &StopSts);
#endif
		switch (StopSts)
		{
		case CSMC_MOVE:
			test = false;
			break;
		case CSMC_STOP_COMMAND:
			test = false;
			break;
		case CSMC_SD_COMMAND:
			test = false;
			break;
		case CSMC_STOP_NORMAL:
			test = true;
			retVal = 1;
			return retVal;
 			break;
		default:
			test = true;
			retVal = -1;
	 
			PrintStr("Alarm Stop");
			// Error 에 의하 stop
			/* 			case CSMC_STOP_MLIM:
					   case CSMC_STOP_ALARM:
					   case CSMC_STOP_PLIM:
		   */
			break;
		}
		if (test)
			break;
	}
	return retVal;
}



int CSAS_1Dlg::Test_SAS_Send(int Num)
{
	int iResult = PASS;
	int i;
	CString strTemp;
	BYTE send[8] = { 0x04,0x2E,0xF3,0x53,0x00,0x00,0x00,0x00 };// caribration

	if (Test_Seq() == PASS)
	{
		switch (Num)
		{
		case 2:
			send[3] = 0x53;// cal initial
			break;
		case 3:
			send[3] = 0x55;// decal offset
			break;
		case 4:
			send[3] = 0x57;// reset (trim)

			break;
		default:
			break;
		}

		m_SelModel.dwMFSWID = GST_MFSW;
		m_fDiagRev = m_fDiagRevSing = false;

		CanSend(m_SelModel.dwMFSWID, 8, send);
		i = 0;
		iResult = FAIL;
		while (1)
		{
			i++;
			Sleep(50);
			if (m_fDiagRev) break;
			if (i > 199)break;

		}
		if (i < 200)
		{
			if ((m_CData_DIG[1] == 0x6e) && (m_CData_DIG[2] == send[2])
				&& (m_CData_DIG[3] == send[3]))
			{
				iResult = PASS;
				strTemp.Format("Pass =%02X", m_bSAS_Status);
			}
			else
			{
				strTemp.Format("Err %02X %02X %02X", m_CData_DIG[1], m_CData_DIG[2], m_CData_DIG[3]);
			}
			PrintStr(strTemp);
 		}
		//
		   //	Test.IGN1(OFF);
		   //	Test.IGN2(OFF);




	}
	return iResult;

}


int CSAS_1Dlg::Test_Seq()
{
	int iResult = PASS;
	BYTE send[8] = { 0x02,0x10,0x03,0x00,0x00,0x00,0x00,0x00 };

	m_fDiagRev = m_fDiagRevSing = false;
	m_fMultyByte = false;
	m_iMultyTransLen = 0;
	CString strTemp;
	m_SelModel.dwMFSWID = GST_MFSW;
	CanSend(m_SelModel.dwMFSWID, 8, send);
	int i = 0;
	i = 0;
	iResult = FAIL;
	while (1)
	{
		i++;
		Sleep(50);
		if (m_fDiagRev) break;
		if (i > 199)break;

	}
	if (i < 200)
	{
		if (m_CData_DIG[1] == 0x50 && m_CData_DIG[2] == 0x03)
		{
			iResult = PASS;
		}
		else
			return FAIL;

	}
	else
	{
		return FAIL;
	}
	BYTE m_CData3;
	BYTE m_CData4;
	BYTE m_CData5;
	BYTE m_CData6;
	m_CData3 = 'J';	//4b
	m_CData4 = 'G';	// 59
	m_CData5 = 0x31;
	m_CData6 = 0x6;// 0x12;	// CCP 08  06 MFSW
	BYTE send1[8] = { 0x10,0x0A,0x27,0x12,0,0,0,0 };

	if (iResult == PASS)
	{
		send[0] = 0x02;
		send[1] = 0x27;
		send[2] = 0x11;
		m_fDiagRev = m_fDiagRevSing = false;
		m_fMultyByte = false;
		m_iMultyTransLen = 0;
		m_fMultyRxDone = false;
		CanSend(m_SelModel.dwMFSWID, 8, send);
		int i = 0;
		i = 0;
		iResult = FAIL;
		while (1)
		{
			i++;
			Sleep(50);
			if (m_fDiagRev) break;
			if (m_fMultyRxDone) break;
			if (i > 199)break;

		}
		if (i < 200)
		{
			if (m_fMultyRxDone)
			{
				if (m_cData_mDIG[0][2] == 0x67 && m_cData_mDIG[0][3] == 0x11)
				{
					iResult = PASS;
					strTemp.Format("security_Aceese  PASS (%d)", m_iMultyRxIndex);
					PrintStr(strTemp);
				}
			}
		}
		//

	}
	m_bSAS_Status = 0xff;
	if (iResult == PASS)
	{

		m_fDiagRev = m_fDiagRevSing = false;
		m_fMultyByte = false;
		m_iMultyTransLen = 0;
		m_iMultyTransLen = 1;
		m_cMultyTxData[0][0] = 0x21;
		m_cMultyTxData[0][1] = send1[4]=m_CData3;
		m_cMultyTxData[0][2] = send1[5] = m_CData4;
		m_cMultyTxData[0][3] = send1[6] = m_CData5;
		m_cMultyTxData[0][4] = send1[7] = m_CData6;
		m_cMultyTxData[0][5] = 0;
		m_cMultyTxData[0][6] = 0;
		m_cMultyTxData[0][7] = 0;
		m_iMultyTransLen = 1;
		m_fMultyTrans = false;
		m_fDiagRevSing = false;
		CanSend(m_SelModel.dwMFSWID, 8, send1);
		i = 0;
		iResult = FAIL;

		while (1)
		{
			i++;
			Sleep(50);
			if (m_fMultyTrans && m_fDiagRevSing) break;
			if (i > 199)break;

		}
		if (i < 200)
		{
			if (m_CData_DIG[1] == 0x67 && m_CData_DIG[2] == 0x12)
			{
				PrintStr("Security_Aceese Final PASS");
				iResult = PASS;
			}
		}
		//

	}

	return iResult;
}

int CSAS_1Dlg::Test_SAS_Cal()
{
	int iResult = PASS;
	BYTE send[8] = { 0x02,0x10,0x03,0x00,0x00,0x00,0x00,0x00 };
	BYTE send1[8] = { 0x04,0x2E,0xF3,0x55,0x00,0x00,0x00,0x00 };	// decal
	CString strTemp;
	int i;

	iResult = Test_Seq();

	if (iResult == PASS)
	{
 //		Test.BPlus(OFF);
		m_SelModel.dwMFSWID = GST_MFSW;
		m_fDiagRev = m_fDiagRevSing = false;

		if (m_bSAS_Status != 0)	// Decal 진행중인 경우는 실행 안한다.(status==0)
		{
			CanSend(m_SelModel.dwMFSWID, 8, send1);
			i = 0;
			iResult = FAIL;
			while (1)
			{
				i++;
				Sleep(50);
				if (m_fDiagRev) break;
				if (i > 199)break;

			}
			if (i < 200)
			{
				if ((m_CData_DIG[1] == 0x6e) && (m_CData_DIG[2] == send1[2])
					&& (m_CData_DIG[3] == send1[3]))
				{
					iResult = PASS;
					strTemp.Format("Decal Pass =%02X", m_bSAS_Status);
				}
				else
				{
					strTemp.Format("Decal Err %02X %02X %02X", m_CData_DIG[1], m_CData_DIG[2], m_CData_DIG[3]);
				}
				p_mSasAuTest->AddString(strTemp);
			}
			//
			   //	Test.IGN1(OFF);
			   //	Test.IGN2(OFF);
			Sleep(100);
		}
 
		if ((iResult == PASS)&& (m_bSAS_Status == 0))
		{
			send1[3] = 0x57;
			m_fDiagRev = m_fDiagRevSing = false;
			CanSend(m_SelModel.dwMFSWID, 8, send1);
			i = 0;
			iResult = FAIL;
			while (1)
			{
				i++;
				Sleep(50);
				if (m_fDiagRev) break;
				if (i > 199)break;

			}
			if (i < 200)
			{
				if ((m_CData_DIG[1] == 0x6e) && (m_CData_DIG[2] == send1[2])
					&& (m_CData_DIG[3] == send1[3]))
				{
					iResult = PASS;
					strTemp.Format("Trim Pass =%02X", m_bSAS_Status);
				}
				else
				{
					strTemp.Format("Trim Err %02X %02X %02X", m_CData_DIG[1], m_CData_DIG[2], m_CData_DIG[3]);
				}
				PrintStr(strTemp);
			}

		}

		if ((iResult == PASS)&& (m_bSAS_Status == 4))
		{
			send1[3] = 0x53;
			m_fDiagRev = m_fDiagRevSing = false;
			CanSend(m_SelModel.dwMFSWID, 8, send1);
			i = 0;
			iResult = FAIL;
			while (1)
			{
				i++;
				Sleep(50);
				if (m_fDiagRev) break;
				if (i > 199)break;

			}
			if (i < 200)
			{
				if ((m_CData_DIG[1] == 0x6e) && (m_CData_DIG[2] == send1[2])
					&& (m_CData_DIG[3] == send1[3]))
				{
					iResult = PASS;
					strTemp.Format("Calibration Pass =%02X", m_bSAS_Status);
				}
				else
				{
					strTemp.Format("Cal Err %02X %02X %02X", m_CData_DIG[1], m_CData_DIG[2], m_CData_DIG[3]);
				}
				PrintStr(strTemp);

			}
 		}
 
	}
//
	if (iResult == PASS)
	{
		Test.IGN1(OFF);
		Test.IGN2(OFF);
		Sleep(500);
		Test.IGN1(ON);
		Test.IGN2(ON);
 
	}
//

	return 	iResult;
 
}

//#include <xlsxwriter.h>

/*

libxlsxwriter는 UTF-8 전용입니다.
MFC/Windows 기본은 UTF-16(CString) 또는 ANSI(char*)이므로,
→ 반드시 UTF-8으로 변환 후 worksheet_write_string()에 넘겨야 정상 표시됩니다

*/

#ifdef USEXXX
// CStringA (ANSI) → UTF-8
std::string CStringA_To_UTF8(const CStringA& ansi)
{
	// 1) ANSI(CStringA) → UTF-16(CStringW)
//	CW2 wide((LPCSTR)ansi, CP_ACP);
//	CW2W wide((LPCSTR)ansi, CP_ACP);

	// 2) UTF-16 → UTF-8
 	CW2A utf8((LPCWSTR)wide, CP_UTF8);
	return std::string((char*)utf8);
}
#endif

// CStringW (UTF-16) → UTF-8
std::string CStringW_To_UTF8(const CStringW& wide)
{
	CW2A utf8((LPCWSTR)wide, CP_UTF8);
	return std::string((char*)utf8);
}


// ANSI(CP_ACP) 멀티바이트 문자열 → UTF-8
std::string MBCSToUtf8(const std::string& mbstr) {
	if (mbstr.empty()) return {};

	// 1) 멀티바이트 → UTF-16
	int wlen = ::MultiByteToWideChar(
		CP_ACP,             // 원본 코드페이지 (ANSI)
		0,
		mbstr.data(),
		(int)mbstr.size(),
		nullptr, 0
	);
	if (wlen == 0) return {};

	std::wstring wbuf(wlen, L'\0');
	::MultiByteToWideChar(
		CP_ACP, 0,
		mbstr.data(), (int)mbstr.size(),
		&wbuf[0], wlen
	);

	// 2) UTF-16 → UTF-8
	int u8len = ::WideCharToMultiByte(
		CP_UTF8,
		0,
		wbuf.data(), wlen,
		nullptr, 0,
		nullptr, nullptr
	);
	if (u8len == 0) return {};

	std::string u8buf(u8len, '\0');
	::WideCharToMultiByte(
		CP_UTF8, 0,
		wbuf.data(), wlen,
		&u8buf[0], u8len,
		nullptr, nullptr
	);

	return u8buf;
}

void CSAS_1Dlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

//	CFile::Remove(strFileName);


 	CString csPath = _T("d:\\data1\\chart.xlsx");

//	CString csPath = "d:\\data\\chart.xlsx";


	std::string filePath = "D:\\data1\\report.xlsx";

//	sprintf((char*)&filePath, "%s", "FFF");

//	printf("\n[%s]", filePath);

	filePath = "D:\\data\\report.xlsx";

//	filePath = MBCSToUtf8(&csPath);

// 	std::string path = Utf8FromWide(_T("C:\\temp\\report.xlsx"));
//	CString path= "d:\\data\\report.xlsl";
//	char path[200];
//	sprintf(path, "d:\\data\\report.xlsx");// , (LPSTR)(LPCSTR)m_plList[m_iProductNum].strShinChangProduct);

	lxw_workbook* wb = workbook_new(filePath.c_str());
	lxw_worksheet* worksheet = workbook_add_worksheet(wb, nullptr);

 
	// 3) std::string으로 셀 데이터 준비
	
	std::string col1 = "기능평가항목";
	std::string col2 = "상세항목";
	std::string col3 = "SPEC";
	std::string col32 = "MIN";
	std::string col42 = "MAX";
	std::string col5 = "단위";
	std::string col6 = "MEASURE";
	std::string col7 = "RESULT";

	std::string row3 = "연결지연시간";
	double      num = 123.0;
//	CStringA test = _T("이름");
     // ANSI 빌드 시 CP_ACP 텍스트
	lxw_format* fmt = workbook_add_format(wb);
//	lxw_format* fmt1 = workbook_add_format(wb);
//	format_set_border(fmt, LXW_BORDER_THIN);
//	format_set_align(fmt1, LXW_ALIGN_CENTER);

	format_set_align(fmt, LXW_ALIGN_CENTER);
	format_set_align(fmt, LXW_ALIGN_VERTICAL_CENTER);//LXW_ALIGN_NONE
//	format_set_bold(fmt);
	//format_set_bg_color(fmt, LXW_COLOR_YELLOW);

	std::string utf8 = MBCSToUtf8(col1);
	worksheet_set_column(worksheet, 0, 0, 20, NULL);
	worksheet_set_column(worksheet, 1, 1, 20, NULL);
//  	worksheet_set_column(worksheet, 2, 2, 8, NULL);
 // 	worksheet_set_column(worksheet, 2, 3, 8, NULL);

 	worksheet_set_column(worksheet, 5, 5, 20, fmt);	// 측정
//	worksheet_set_column(worksheet, 6, 6, 20, NULL);	// 결과

//	worksheet_write_string(worksheet, 0, 0, utf8.c_str(), fmt);
//	worksheet_merge_range(worksheet, 0, 0, 1, 0, utf8.c_str(), fmt);

	utf8 = MBCSToUtf8(col2);
  	worksheet_write_string(worksheet, 0, 1, utf8.c_str(), fmt);
 //	worksheet_merge_range(worksheet, 0, 1, 1, 1, "상세항목", fmt);
// 	worksheet_merge_range(worksheet, 0, 1, 1, 1, utf8.c_str(), fmt);

 
	utf8 = MBCSToUtf8(col3);
	worksheet_merge_range(worksheet, 0, 2, 0, 3, utf8.c_str(), fmt);
	//worksheet_merge_range(worksheet, 0, 2, 0, 3, utf8.c_str(), fmt);
//	worksheet_write_string(worksheet, 0, 2, utf8.c_str(), nullptr);//3,4(C,D)

	utf8 = MBCSToUtf8(col32);
	worksheet_write_string(worksheet, 1, 2, utf8.c_str(), fmt);//3,4(C,D)
	utf8 = MBCSToUtf8(col42);
	worksheet_write_string(worksheet, 1, 3, utf8.c_str(), fmt);//3,4(C,D)

	utf8 = MBCSToUtf8(col5);
//	worksheet_write_string(worksheet, 0, 4, utf8.c_str(), nullptr);	//  단위 표시
	worksheet_merge_range(worksheet, 0, 4, 1, 4, utf8.c_str(), fmt);
  
	utf8 = MBCSToUtf8(col6);
 	worksheet_write_string(worksheet, 0, 5, utf8.c_str(), nullptr);
// 	worksheet_merge_range(worksheet, 0, 5, 1, 5, utf8.c_str(), fmt);
/*
	utf8 = MBCSToUtf8(col7);
//	worksheet_write_string(worksheet, 0, 6, utf8.c_str(), nullptr);
	worksheet_merge_range(worksheet, 0, 6, 1, 6, utf8.c_str(), fmt);


//	worksheet_write_number(worksheet, 1, 1, 1, nullptr);
	//	worksheet_write_string(worksheet, 0, 0, "이름", nullptr);
//	worksheet_write_number(worksheet, 1, 0, 42, nullptr);
/* 		// 4) 서식 & 수식 예시
//	lxw_format* fmt_bold = workbook_add_format(wb);
//	format_set_bold(fmt_bold);
//	worksheet_write_string(worksheet, 3, 0, "합계", fmt_bold);



//	worksheet_write_number(worksheet, 2, 5, num, fmt);
//	worksheet_write_number(worksheet, 3, 5, 13.3, fmt);


//libxlsxwriter 자체는 수식을 평가(계산)해 주지 않고 “수식만” 파일에 써 준다는 데 있습니다.
//	worksheet_write_formula(worksheet, 4, 1, "=SUM(F3:F4)", nullptr);
// 
//	double result = 100;
//	worksheet_write_formula_num(worksheet, 3, 1, "=SUM(F3:F4)", nullptr,result);	// 예상값을 미리 아는경우 강제로 결과를 써준다.

//	lxw_format* format = workbook_add_format(wb);
//	format_set_num_format(format, "$#,##0.00");

//	worksheet_write_number(worksheet, 4, 0, 141234.567, format);
//	worksheet_write_string(worksheet, 5, 0, "range", nullptr);// 이렇게 하면 안됨
//	worksheet_write_string(worksheet,6, 0, "이름", nullptr);	//이렇게 해도 안됨
    lxw_format* border_fmt = workbook_add_format(workbook);
    format_set_top(border_fmt, LXW_BORDER_THICK);
    format_set_bottom(border_fmt, LXW_BORDER_THICK);
    format_set_left(border_fmt, LXW_BORDER_THICK);
    format_set_right(border_fmt, LXW_BORDER_THICK);


	// 워크북을 생성한 직후에 자동 계산 모드를 켭니다.
/* 
	workbook_set_calc_mode(wb, LXW_CALC_MODE_AUTOMATIC);
	// 또는 열 때 전체 수식을 다시 계산하도록 설정
	workbook_set_calc_on_load(wb, 1);
*/
//	worksheet_insert_chart(worksheet,10,10,)
	
#ifdef TEST_XL

#include <xlsxwriter.h>

	int main() {
		lxw_workbook* workbook = workbook_new("outline_box.xlsx");
		lxw_worksheet* worksheet = workbook_add_worksheet(workbook, NULL);

		// 위에서 서식 정의 + for문으로 전체 적용

		lxw_format* fmt_inner = workbook_add_format(workbook);
		format_set_border(fmt_inner, LXW_BORDER_THIN);

		lxw_format* fmt_top = workbook_add_format(workbook);
		lxw_format* fmt_bottom = workbook_add_format(workbook);
		lxw_format* fmt_left = workbook_add_format(workbook);
		lxw_format* fmt_right = workbook_add_format(workbook);

		format_set_border(fmt_top, LXW_BORDER_THIN);    format_set_top(fmt_top, LXW_BORDER_THICK);
		format_set_border(fmt_bottom, LXW_BORDER_THIN);    format_set_bottom(fmt_bottom, LXW_BORDER_THICK);
		format_set_border(fmt_left, LXW_BORDER_THIN);    format_set_left(fmt_left, LXW_BORDER_THICK);
		format_set_border(fmt_right, LXW_BORDER_THIN);    format_set_right(fmt_right, LXW_BORDER_THICK);

		for (int r = 1; r <= 3; ++r) {
			for (int c = 1; c <= 3; ++c) {
				lxw_format* fmt = fmt_inner;

				if (r == 1 && c == 1) { // Left-Top
					lxw_format* corner = workbook_add_format(workbook);
					format_set_top(corner, LXW_BORDER_THICK);
					format_set_left(corner, LXW_BORDER_THICK);
					format_set_border(corner, LXW_BORDER_THIN);
					fmt = corner;
				}
				else if (r == 1 && c == 3) { // Right-Top
					lxw_format* corner = workbook_add_format(workbook);
					format_set_top(corner, LXW_BORDER_THICK);
					format_set_right(corner, LXW_BORDER_THICK);
					format_set_border(corner, LXW_BORDER_THIN);
					fmt = corner;
				}
				else if (r == 3 && c == 1) { // Left-Bottom
					lxw_format* corner = workbook_add_format(workbook);
					format_set_bottom(corner, LXW_BORDER_THICK);
					format_set_left(corner, LXW_BORDER_THICK);
					format_set_border(corner, LXW_BORDER_THIN);
					fmt = corner;
				}
				else if (r == 3 && c == 3) { // Right-Bottom
					lxw_format* corner = workbook_add_format(workbook);
					format_set_bottom(corner, LXW_BORDER_THICK);
					format_set_right(corner, LXW_BORDER_THICK);
					format_set_border(corner, LXW_BORDER_THIN);
					fmt = corner;
				}
				else if (r == 1) fmt = fmt_top;
				else if (r == 3) fmt = fmt_bottom;
				else if (c == 1) fmt = fmt_left;
				else if (c == 3) fmt = fmt_right;

				char buf[8];
				sprintf(buf, "%c%d", 'A' + c, r + 1);
				worksheet_write_string(worksheet, r, c, buf, fmt);
			}
		}
		workbook_close(workbook);
		return 0;


#endif
		

	lxw_error err;
	err =workbook_close(wb);		// memory 해제
	if(err != LXW_NO_ERROR)
 		AfxMessageBox(_T("Win32 Excel 파일 문제 발생.."));



 
}


/* 
std::string Utf8FromCString(const CString& wstr) {
	// CP_UTF8 옵션으로 UTF-16 → UTF-8 변환
//	CW2A utf8(wstr, CP_UTF8);
	return std::string((char*)utf8);
}

 
//-----------------------------------------------------------------------------
//  CString → UTF-8 std::string 변환
//-----------------------------------------------------------------------------
std::string CSAS_1Dlg::Utf8FromCString(const CString& str)
{
 //	CW2A utf8(str, CP_UTF8);
	return std::string((char*)utf8);
}
*/


void CSAS_1Dlg::OnBnClickedButton2()
{
	CString strTemp;
	strTemp.Format("%d", m_ulCurCnt);
	int i;

	p_mSasAuTest->m_fDirCW = false;
	
	p_mSasAuTest->InvalidateRect(p_mSasAuTest->m_reGraph);

	for (i = 1; i < m_ulCurCnt; i++)
	{
		p_mSasAuTest->DrawGraph(i);
	}
	
	p_mSasAuTest->m_fDirCW = true;


}
