#if !defined(AFX_FILENEWDLG_H__77650ABB_BB50_414B_91FC_279B7363C5D9__INCLUDED_)
#define AFX_FILENEWDLG_H__77650ABB_BB50_414B_91FC_279B7363C5D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileNewDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileNewDlg dialog

class CFileNewDlg : public CDialog
{
// Construction
public:
	CFileNewDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileNewDlg)
	enum { IDD = IDD_FILE_CREATE };
	CString	m_strFileName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileNewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileNewDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILENEWDLG_H__77650ABB_BB50_414B_91FC_279B7363C5D9__INCLUDED_)
