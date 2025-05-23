// KvaserCan.cpp: implementation of the CKvaserCan class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "JK1_KEYBOARD.h"
//#include "PW_MainFinal.h"
//#include "jw1_Wheel.h"

#include "KvaserCan.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKvaserCan::CKvaserCan()
{
	m_hCan=-1;
}

CKvaserCan::~CKvaserCan()
{
	if(m_hCan>-1)
	{
		canBusOff(m_hCan);
		canClose(m_hCan);
	}
}

void CKvaserCan::InitDriver(int channel, int iCanHardType, int iBaud, HWND hWnd)
{
//  int  i;
 // int  stat;
//  int iChannelCnt;
  int iChannelType;
//  CString strT;

  m_hWnd=hWnd;
  canInitializeLibrary();

  //get number of present channels
 // stat = canGetNumberOfChannels(&iChannelCnt);

  //for (i = 0; i < iChannelCnt; i++) 
  //{
		//obtain some hardware info from CANlib

		canGetChannelData(channel, canCHANNELDATA_TRANS_TYPE,
						&iChannelType, sizeof(DWORD));

		m_hCan = canOpenChannel(channel, canOPEN_REQUIRE_EXTENDED);
		
		if(m_hCan <0) 
		{
			char msg[64];
			canGetErrorText((canStatus)m_hCan, msg, sizeof(msg));
			AfxMessageBox(msg);
		}
		canSetBusParams(m_hCan, iBaud, 0, 0, 0, 0, 0);
		canSetBusOutputControl(m_hCan, canDRIVER_NORMAL);
		canBusOn(m_hCan);

	//	canSetNotify(m_hCan, m_hWnd, canNOTIFY_RX);
	//	break;

//	}
}

void CKvaserCan::InitDriverFD(int channel, int iCanHardType, int iBaud, int iBitrate, HWND hWnd,bool flag)
{
	//  int  i;
	 // int  stat;
	//  int iChannelCnt;
	int iChannelType;
	//  CString strT;

	m_hWnd = hWnd;
	canInitializeLibrary();

	//get number of present channels
   // stat = canGetNumberOfChannels(&iChannelCnt);

	//for (i = 0; i < iChannelCnt; i++) 
	//{
		  //obtain some hardware info from CANlib

	canGetChannelData(channel, canCHANNELDATA_TRANS_TYPE,
		&iChannelType, sizeof(DWORD));

	m_hCan = canOpenChannel(channel, canOPEN_CAN_FD | canOPEN_ACCEPT_LARGE_DLC);
	 
	if (m_hCan < 0)
	{
		char msg[64];
		canGetErrorText((canStatus)m_hCan, msg, sizeof(msg));
		AfxMessageBox(msg);
	}
	canSetBusParams(m_hCan, iBaud, 0, 0, 0, 0, 0);
	canSetBusParamsFd(m_hCan, iBitrate, 0, 0, 0);
	canSetBusOutputControl(m_hCan, canDRIVER_NORMAL);
	canBusOn(m_hCan);
	if(flag)
 		canSetNotify(m_hCan, m_hWnd, canNOTIFY_RX);
	//	break;

//	}
}


int CKvaserCan::ReadData(long &dwMsgID,unsigned int &dlc,BYTE *cData)
{
    
    unsigned int flags;
    unsigned long timestamp;

    return canRead(m_hCan, &dwMsgID, cData, &dlc, &flags, &timestamp);
}

int CKvaserCan::WriteData(long lMsgID,unsigned int dlc,BYTE *cData, bool flag)
{ 
 
	if(dlc > 8)
	{
//		if(flag)
		if (lMsgID > 0x7ff)
			return canWriteWait(m_hCan, lMsgID, cData, dlc, canMSG_EXT | canFDMSG_FDF | canFDMSG_BRS, 1000);//canMSG_EXT
		else
			return canWriteWait(m_hCan, lMsgID, cData, dlc, canMSG_STD | canFDMSG_FDF | canFDMSG_BRS, 1000);

	}
// lMsgID > 0xfff 이면으로 바꿈
//	if(flag)
	if (lMsgID > 0x7ff)
	{
		return canWriteWait(m_hCan, lMsgID, cData, dlc, canMSG_EXT, 1000);//
	}
	return canWriteWait(m_hCan, lMsgID, cData, dlc, canMSG_STD , 1000);//canMSG_EXT

//		return canWriteWait(m_hCan, lMsgID, cData, dlc, canMSG_STD | canFDMSG_FDF| canFDMSG_BRS, 1000);

}



int CKvaserCan::ReadDataFD(long& dwMsgID, unsigned int& dlc, BYTE* cData)
{

	unsigned int flags;
	unsigned long timestamp;

	return canRead(m_hCan, &dwMsgID, cData, &dlc, &flags, &timestamp);
}


int CKvaserCan::ReadDataFD(long& dwMsgID, unsigned int& dlc, BYTE* cData,unsigned long& timestamp)
{

	unsigned int flags;
 //	unsigned long timestamp1;
	 
	return canRead(m_hCan, &dwMsgID, cData, &dlc, &flags, &timestamp);
}

int CKvaserCan::WriteDataFD(long lMsgID, unsigned int dlc, BYTE* cData)
{
	if(lMsgID > 0xfff)
		return canWriteWait(m_hCan, lMsgID, cData, dlc, canMSG_EXT | canFDMSG_FDF| canFDMSG_BRS, 1000);

	return canWriteWait(m_hCan, lMsgID, cData, dlc, canMSG_STD | canFDMSG_FDF| canFDMSG_BRS, 1000);
}


void CKvaserCan::FlashReadBuffer()
{
	canBusOff(m_hCan);
	canFlushReceiveQueue(m_hCan);
	canFlushTransmitQueue(m_hCan);
	canBusOn(m_hCan);
}
