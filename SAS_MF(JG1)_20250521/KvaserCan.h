// KvaserCan.h: interface for the CKvaserCan class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KVASERCAN_H__4297EE54_D037_40F5_AD61_886D031B06D4__INCLUDED_)
#define AFX_KVASERCAN_H__4297EE54_D037_40F5_AD61_886D031B06D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <canlib.h>

class CKvaserCan  
{
public:
	CKvaserCan();
	virtual ~CKvaserCan();
	canHandle  m_hCan;	
	HWND m_hWnd;
	void InitDriver(int channel,int iCanHardType, int iBaud, HWND hWnd);
	void InitDriverFD(int channel, int iCanHardType, int iBaud, int iBitrate, HWND hWnd, bool flag = false);

	int ReadData(long &dwMsgID,unsigned int &dlc,BYTE *cData);
	int WriteData(long dwMsgID,unsigned int dlc,BYTE *cData,bool flag=true);
 	int ReadDataFD(long& dwMsgID, unsigned int& dlc, BYTE* cData);
	int ReadDataFD(long& dwMsgID, unsigned int& dlc, BYTE* cData, unsigned long& timestamp);
	int WriteDataFD(long dwMsgID, unsigned int dlc, BYTE* cData);

	void FlashReadBuffer();
};

#endif // !defined(AFX_KVASERCAN_H__4297EE54_D037_40F5_AD61_886D031B06D4__INCLUDED_)
