// FileNew.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "SAS_1.h"
#include "FileNew.h"


// CFileNew ��ȭ �����Դϴ�.

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


// CFileNew �޽��� ó�����Դϴ�.

void CFileNew::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);		// control to value 
	OnOK();
}
