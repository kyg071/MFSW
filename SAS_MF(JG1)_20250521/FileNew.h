#pragma once


// CFileNew ��ȭ �����Դϴ�.

class CFileNew : public CDialog
{
	DECLARE_DYNAMIC(CFileNew)

public:
	CFileNew(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CFileNew();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_FILE_CREATE };
		
	CString	m_strFileName;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
