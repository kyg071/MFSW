#if !defined(AFX_LED_H__20C72BAE_748A_4880_8258_CF57D3A8A83E__INCLUDED_)
#define AFX_LED_H__20C72BAE_748A_4880_8258_CF57D3A8A83E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Led.h : header file
//

#define LIMIT_SENSOR	0
#define UNIVERSAL_IO	1
#define EXTERNAL_IO		2

/////////////////////////////////////////////////////////////////////////////
// CLed window

class CLed : public CStatic
{
// Construction
public:
	CLed();

// Attributes
public:

	COLORREF m_bOffColor[3];
	COLORREF m_bOnColor[3];
	COLORREF m_LedColor;

	int m_bSensor;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLed)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetStatus(BOOL bStatus);
	void SetType(int type);
	BOOL GetStatus();
	BOOL bLedStatus;
	void Off();
	void On();
	virtual ~CLed();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLed)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LED_H__20C72BAE_748A_4880_8258_CF57D3A8A83E__INCLUDED_)
