
// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

// MFC�� ���� �κа� ���� ������ ��� �޽����� ���� ����⸦ �����մϴ�.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#include <afxext.h>         // MFC Ȯ���Դϴ�.


#include <afxdisp.h>        // MFC �ڵ�ȭ Ŭ�����Դϴ�.



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC�� ���� �� ��Ʈ�� ���� ����


 
#include <GdiPlus.h>

using namespace Gdiplus;//
 

#include "vcinpl.h"
#include "iodefine_.h"

#include "CSmc.h"
#include "CSmcdef.h"
#pragma comment(lib,"CSMC.lib") 
//#pragma comment(lib,"vcisdk.lib") 

#pragma comment(lib,"canlib32.lib")	// YGK
#pragma comment(lib,"xlsxwriter.lib")	// YGK 25.03,03 minizip.lib,zlib.lib

#pragma comment(lib,"minizip.lib")	// YGK 25.03,03 minizip.lib,zlib.lib
#pragma comment(lib,"zlib.lib")	// YGK 25.03,03 minizip.lib,zlib.lib


#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")


unsigned short CRC16_0(unsigned char *nData, int wLength);
//unsigned short CRC16(unsigned char *nData, int wLength);
unsigned int HexaStringConvert(CString strData);






#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64f
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

 

// xp style button �����

#pragma comment(linker,"/manifestdependency:\" type='win32'  name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"") 




//#define ZERO_CHECK 1
#define PRINTF 1

#ifdef PRINTF


#ifdef _DEBUG


#ifdef _UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup  /subsystem:console")
#endif
#endif


#endif

//#define NO_CONTROL




#define MESSAGE_TYPE_SINGLE_VALUE               0u
#define MESSAGE_TYPE_FIRST_VALUE                1u
#define MESSAGE_TYPE_CONSECUTIVE_VALUE          2u
#define MESSAGE_TYPE_FLOW_VALUE                 3u






typedef struct _MODEL
{
	DWORD dwMFSWID;
	DWORD dwTBID;
	DWORD dwVCID;
	BOOL fVerCheck;
	BYTE bReset[8];
	BYTE bInit[8];
	BYTE bOffset[8];
	BYTE bVer[8];
	double dCurrentConsumtion;
	double dConnectDelayTime;
	double dNonlinearity;
	double dTorque;
	double dHysteress;
	BYTE bVerS[2];
	double dOffConnectDelay;
	double dOffNonlinearity;
	double dOffTorque;
	double dOffDifferAngle;
	double dOffsetAngle[10];
	double dOffsetSpeed;
	
	double dMesAngleStart[10];
	double dMesSpeedStart[10];
	double dMesAngleEnd[10];
	double dMesSpeedEnd[10];

	int iAngleHighByte;
	int iAngleLowByte;
	int iVersionHighByte;
	int iVersionLowByte;
	int iSpeedByte;

	bool bfCurrCheck;
	bool bfOffsetCheck;
	bool bfConnectTimeCheck;
}MODEL;

typedef struct {
	unsigned	b0 : 1, b1 : 1, b2 : 1, b3 : 1, b4 : 1, b5 : 1, b6 : 1, b7 : 1;
} byte_bits;

typedef union {
	BYTE bByte;
	byte_bits bit;
} lsByte;


#define	ANG2PULSE		11.111		// ������ 
#define PULSE2ANG		- 0.09		//  - �� �ϸ� CD101 ��

//CSAS_1App *pApp;

//////////////////////////////////////////////////


/////////////////////////////////////////////////