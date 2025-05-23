// FileNewDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "SASTester.h"
#include "FileNewDlg.h"
/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/
/////////////////////////////////////////////////////////////////////////////
// CFileNewDlg dialog


CFileNewDlg::CFileNewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileNewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileNewDlg)
	m_strFileName = _T("");
	//}}AFX_DATA_INIT
}


void CFileNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileNewDlg)
	DDX_Text(pDX, IDC_FILENAME_EDIT, m_strFileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileNewDlg, CDialog)
	//{{AFX_MSG_MAP(CFileNewDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileNewDlg message handlers

void CFileNewDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	CDialog::OnOK();
}
