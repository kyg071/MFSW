// EnvSet.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "EnvSet.h"
#include "SAS_1.h"
// EnvSet.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "SAS_1.h"
#include "EnvSet.h"


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
	DDX_Control(pDX, IDC_COMBO0, m_ctrComSel);
}


BEGIN_MESSAGE_MAP(CEnvSet, CDialog)
	ON_BN_CLICKED(IDOK, &CEnvSet::OnBnClickedOk)
END_MESSAGE_MAP()


// CEnvSet �޽��� ó�����Դϴ�.

void CEnvSet::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnOK();
}

BOOL CEnvSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
