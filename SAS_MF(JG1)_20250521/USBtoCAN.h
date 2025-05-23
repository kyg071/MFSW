// USBtoCAN.h: interface for the CUSBtoCAN class.
//
//////////////////////////////////////////////////////////////////////
 
#pragma once
 



#define WM_CANTRACEUPDATE WM_USER+100
#define WM_CANSTATUSUPDATE WM_USER+101

class CUSBtoCAN : public CObject 
{
DECLARE_DYNCREATE( CUSBtoCAN )	
public:
	CUSBtoCAN();

public:
	HANDLE m_hDevice;       // device handle
	HANDLE m_hCanCtl;       // controller handle 
	HANDLE m_hCanChn;       // channel handle
	HANDLE m_hScheduler;

	BOOL m_fCanUse;
	DWORD m_dwIndex[16];
	CANMSG m_sCanMsg;
	CANMSG m_sTxCanMsg;
	CANCHANSTATUS m_sChnStatus;
	DWORD m_dwNode;
	unsigned int m_uiHead;
	
	double m_dTick;
	double m_dTimeRes;
	DWORD m_dwTime;
	clock_t m_ctStart;
	clock_t m_ctEnd;
	
	char m_szError[VCI_MAX_ERRSTRLEN];
	int m_fError;

	HWND m_hTraceWnd;
	HWND m_hMainWnd;
public:
	LONG   m_lMustQuit; // quit flag for the receive thread
public:
	void SelectDevice ( BOOL fUserSelect );
	void GetDviceInfo(PVCIDEVICEINFO pInfo);
	void InitSocket   ( UINT32 dwCanNo, HANDLE *hDev, HANDLE *hChn, HANDLE *hCon, UINT8 bMode, UINT8 ubit, UINT8 ubit2 );
	void FinalizeApp  ( void );
	char *DisplayError ( HRESULT hResult );

	void TransmitData ( DWORD dwMsgID,BYTE dlc,UINT8 *abData );
	void CanInitial(UINT8 bMode,UINT8 uBit0,UINT8 uBit1); 
	void ReceiveData(DWORD &dwMsgID,BYTE &dlc,UINT8 *retData);
	void CyclicAdd(DWORD dwID,unsigned char *cData,WORD wCyclicTime);

	void SetTraceWnd(HWND hWnd);
	void SetMainWnd(HWND hWnd);
	void SetNodeNum(DWORD num);

	void TraceSendMsg(BOOL mode);
	void StatusSendMsg();
protected:
  
// Operations
public:
 	virtual ~CUSBtoCAN();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUSBtoCAN)
	//}}AFX_VIRTUAL

// Implementation
protected:

 
};

 