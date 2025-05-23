// EnvSet.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "EnvSet.h"
#include "SAS_1.h"
// EnvSet.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SAS_1.h"
#include "EnvSet.h"


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
	DDX_Control(pDX, IDC_COMBO0, m_ctrComSel);
}


BEGIN_MESSAGE_MAP(CEnvSet, CDialog)
	ON_BN_CLICKED(IDOK, &CEnvSet::OnBnClickedOk)
END_MESSAGE_MAP()


// CEnvSet 메시지 처리기입니다.

void CEnvSet::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}

BOOL CEnvSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
