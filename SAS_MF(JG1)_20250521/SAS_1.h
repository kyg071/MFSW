
// SAS_1.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.
#include "sas_1dlg.h"

// CSAS_1App:
// 이 클래스의 구현에 대해서는 SAS_1.cpp을 참조하십시오.
//


class CSAS_1App : public CWinAppEx
{
public:
	CSAS_1App();

 
// 재정의입니다.
	
public:
	virtual BOOL InitInstance();

// 구현입니다.
	


	DECLARE_MESSAGE_MAP()
public:
	bool m_Connect;
};

extern CSAS_1App theApp;
extern CSAS_1Dlg *pMDlg;
