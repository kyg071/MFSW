// FileNew.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SAS_1.h"
#include "FileNew.h"


// CFileNew 대화 상자입니다.

IMPLEMENT_DYNAMIC(CFileNew, CDialog)

CFileNew::CFileNew(CWnd* pParent /*=NULL*/)
	: CDialog(CFileNew::IDD, pParent)
{
	m_strFileName = _T("");

}

CFileNew::~CFileNew()
{
}

void CFileNew::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILENAME_EDIT, m_strFileName);

}


BEGIN_MESSAGE_MAP(CFileNew, CDialog)
	ON_BN_CLICKED(IDOK, &CFileNew::OnBnClickedOk)
END_MESSAGE_MAP()


// CFileNew 메시지 처리기입니다.

void CFileNew::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);		// control to value 
	OnOK();
}
