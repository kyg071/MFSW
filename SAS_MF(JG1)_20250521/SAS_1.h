
// SAS_1.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.
#include "sas_1dlg.h"

// CSAS_1App:
// �� Ŭ������ ������ ���ؼ��� SAS_1.cpp�� �����Ͻʽÿ�.
//


class CSAS_1App : public CWinAppEx
{
public:
	CSAS_1App();

 
// �������Դϴ�.
	
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	


	DECLARE_MESSAGE_MAP()
public:
	bool m_Connect;
};

extern CSAS_1App theApp;
extern CSAS_1Dlg *pMDlg;
