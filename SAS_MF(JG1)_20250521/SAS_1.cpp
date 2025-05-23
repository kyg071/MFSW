
// SAS_1.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "SAS_1.h"
#include "SAS_1Dlg.h"

// 아래와 같이 모든 cpp 에 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSAS_1App

BEGIN_MESSAGE_MAP(CSAS_1App, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CSAS_1App 생성

CSAS_1App::CSAS_1App()
: m_Connect(true)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CSAS_1App 개체입니다.

CSAS_1App theApp;
CSAS_1Dlg *pMDlg;

// CSAS_1App 초기화

BOOL CSAS_1App::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다.
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));

	printf("\n****************************\n   CSAS_1App:: 중복실행 line#64");

	CreateSemaphore(NULL, TRUE, TRUE, "SAS MFSW");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		AfxMessageBox("Program is already running!");
		return FALSE;
	}

// local ip 설정..	
/* 
	if(system("ping -w 2 -n 1 10.2.1.250") != 0)
	{
		AfxMessageBox("IP를 10.2.1.250 으로 설정후 다시 시작하세요");
		m_Connect = false;
//		return FALSE;
	}

	if(system("ping -w 2 -n 1 10.2.1.2") != 0)
	{
		AfxMessageBox("control 전원및 LAN 연결 확인후 다시 시작 하세요");
		m_Connect= false;	
//		return FALSE;
	}
*/
	CSAS_1Dlg dlg;
	m_pMainWnd = &dlg;
	printf("\n****************************\n   CSAS_1App::    Main DLG 생성");

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 여기에 [확인]을 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
		AfxMessageBox("ID OK");
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 여기에 [취소]를 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
		AfxMessageBox("ID CANCEL");
	}

	// 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고  응용 프로그램을 끝낼 수 있도록 FALSE를
	// 반환합니다.
	return FALSE;
}
