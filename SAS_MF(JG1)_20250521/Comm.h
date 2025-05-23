//Comm.h
//Rs232c를 하기위한 클래스 헤더1
#define MAXBLOCK       2500


#define MAXPORTS        128


// Flow control flags

#define FC_DTRDSR       0x01
#define FC_RTSCTS       0x02
#define FC_XONXOFF      0x04

// ascii definitions

#define ASCII_BEL       0x07
#define ASCII_BS        0x08
#define ASCII_LF        0x0A
#define ASCII_CR        0x0D
#define ASCII_XON       0x11
#define ASCII_XOFF      0x13

#define STX     0x02
#define ETX     0x03
#define ENQ     0x05
#define ACK     0x06
#define NAK     0x15
#define SYN     0x16
#define EM      0x19
#define SUB     0x1A  


#define WM_RECEIVEDATA   WM_USER+9




// function prototypes (private)

/////////////////////////////////////////////////////////////////////////////
// CComm window

class CComm : public CObject
{

   DECLARE_DYNCREATE( CComm )
public:
   HANDLE idComDev ;//컴포트 디바이스 연결 핸들
   BOOL fConnected;//컴포트가 연결되면 1로 설정
   BYTE abIn[ MAXBLOCK + 1] ;//컴포트에서 들어오는 데이타
   BYTE m_cData[10000] ;
   BYTE m_cBuf[MAXBLOCK +1];
   int m_iDataLen;
   HWND m_hwnd;//메세지를 전달할 윈도우 플러그
   HWND m_hBasic;

// Construction
public:
   CComm();
   void SetXonOff(BOOL chk);//XonOff 설정
   //컴포트를 설정함
   void SetComPort(int port,DWORD rate,BYTE bytesize,BYTE stop,BYTE parity);
   //Dtr Rts설정
   void SetDtrRts(BYTE chk);
   //comm 포트를 만든다.
   BOOL CreateCommInfo();
   //comm 포트를 해제한다.
   BOOL DestroyComm();
   //컴포트에서 데이타를 받는다.
   int  ReadCommBlock( LPSTR, int ) ;
   //컴포트에 데이타를 넣는다.
   BOOL WriteCommBlock( LPSTR, int);
   BOOL OpenComPort( ) ;//컴포트를 열고 연결을 시도한다.
   //포트를 연결한다.
   BOOL SetupConnection( ) ;
   //연결을 해제한다.
   BOOL CloseConnection( ) ;
   //읽은 데이타를 버퍼에 저장한다.
   void SetReadData(unsigned char* data, int);
   //메세재를 보낼 윈도우 플래를 설정한다.
   void SetHwnd(HWND hwnd);

	
   
   void ReceiveData(int iLen);
   
   
   
   
// Attributes
public:
   BYTE        bPort;
   BOOL        fXonXoff;
   BYTE        bByteSize, bFlowCtrl, bParity, bStopBits ;
   DWORD       dwBaudRate ;
   HANDLE hWatchThread;
   HWND        hTermWnd ;
   DWORD       dwThreadID ;
   OVERLAPPED  osWrite, osRead ;
   int         nMinTimeOut; 
   int         nWaitTimeOut;
   int		nMaxRepeatCount;
	int nRepeat;

	BOOL m_fPacket;

	int m_iReadCount;
	DWORD m_nRTS;
	DWORD m_nDTR;


protected:
  
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComm)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CComm();

	// Generated message map functions
//	DECLARE_MESSAGE_MAP()
protected:
};


/////////////////////////////////////////////////////////////////////////////
