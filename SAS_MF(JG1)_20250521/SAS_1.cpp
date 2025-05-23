
// SAS_1.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "SAS_1.h"
#include "SAS_1Dlg.h"

// �Ʒ��� ���� ��� cpp �� 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSAS_1App

BEGIN_MESSAGE_MAP(CSAS_1App, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CSAS_1App ����

CSAS_1App::CSAS_1App()
: m_Connect(true)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CSAS_1App ��ü�Դϴ�.

CSAS_1App theApp;
CSAS_1Dlg *pMDlg;

// CSAS_1App �ʱ�ȭ

BOOL CSAS_1App::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�.
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));

	printf("\n****************************\n   CSAS_1App:: �ߺ����� line#64");

	CreateSemaphore(NULL, TRUE, TRUE, "SAS MFSW");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		AfxMessageBox("Program is already running!");
		return FALSE;
	}

// local ip ����..	
/* 
	if(system("ping -w 2 -n 1 10.2.1.250") != 0)
	{
		AfxMessageBox("IP�� 10.2.1.250 ���� ������ �ٽ� �����ϼ���");
		m_Connect = false;
//		return FALSE;
	}

	if(system("ping -w 2 -n 1 10.2.1.2") != 0)
	{
		AfxMessageBox("control ������ LAN ���� Ȯ���� �ٽ� ���� �ϼ���");
		m_Connect= false;	
//		return FALSE;
	}
*/
	CSAS_1Dlg dlg;
	m_pMainWnd = &dlg;
	printf("\n****************************\n   CSAS_1App::    Main DLG ����");

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ���⿡ [Ȯ��]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
		AfxMessageBox("ID OK");
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ���⿡ [���]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
		AfxMessageBox("ID CANCEL");
	}

	// ��ȭ ���ڰ� �������Ƿ� ���� ���α׷��� �޽��� ������ �������� �ʰ�  ���� ���α׷��� ���� �� �ֵ��� FALSE��
	// ��ȯ�մϴ�.
	return FALSE;
}
