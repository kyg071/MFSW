//Comm.h
//Rs232c�� �ϱ����� Ŭ���� ���1
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
   HANDLE idComDev ;//����Ʈ ����̽� ���� �ڵ�
   BOOL fConnected;//����Ʈ�� ����Ǹ� 1�� ����
   BYTE abIn[ MAXBLOCK + 1] ;//����Ʈ���� ������ ����Ÿ
   BYTE m_cData[10000] ;
   BYTE m_cBuf[MAXBLOCK +1];
   int m_iDataLen;
   HWND m_hwnd;//�޼����� ������ ������ �÷���
   HWND m_hBasic;

// Construction
public:
   CComm();
   void SetXonOff(BOOL chk);//XonOff ����
   //����Ʈ�� ������
   void SetComPort(int port,DWORD rate,BYTE bytesize,BYTE stop,BYTE parity);
   //Dtr Rts����
   void SetDtrRts(BYTE chk);
   //comm ��Ʈ�� �����.
   BOOL CreateCommInfo();
   //comm ��Ʈ�� �����Ѵ�.
   BOOL DestroyComm();
   //����Ʈ���� ����Ÿ�� �޴´�.
   int  ReadCommBlock( LPSTR, int ) ;
   //����Ʈ�� ����Ÿ�� �ִ´�.
   BOOL WriteCommBlock( LPSTR, int);
   BOOL OpenComPort( ) ;//����Ʈ�� ���� ������ �õ��Ѵ�.
   //��Ʈ�� �����Ѵ�.
   BOOL SetupConnection( ) ;
   //������ �����Ѵ�.
   BOOL CloseConnection( ) ;
   //���� ����Ÿ�� ���ۿ� �����Ѵ�.
   void SetReadData(unsigned char* data, int);
   //�޼��縦 ���� ������ �÷��� �����Ѵ�.
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
