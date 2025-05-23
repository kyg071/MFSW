#pragma once


// CFileNew 대화 상자입니다.

class CFileNew : public CDialog
{
	DECLARE_DYNAMIC(CFileNew)

public:
	CFileNew(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CFileNew();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_FILE_CREATE };
		
	CString	m_strFileName;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
