#include "StdAfx.h"
#include "USBCAN.h"




DWORD WINAPI ReceiveThreadProc(LPVOID lpData);


CUSBCAN::CUSBCAN(void)
: m_bConnect(false)
, m_DevCount(0)
, m_CardIndex(-1)
, m_CardNum(10)
{
		
	m_hDevice=NULL;       // device handle
	m_hCanCtl=NULL;       // controller handle 
	m_hCanChn=NULL;       // channel handle
	m_hTraceWnd=m_hMainWnd=NULL;// 2014.11.25
	m_lMustQuit=0;
	m_fError=TRUE;
 	m_dwNode=0;

//	memset(m_dwIndex,0,sizeof(m_dwIndex));	// not used
}

CUSBCAN::~CUSBCAN(void)
{
	m_fCanUse=FALSE;
	m_bConnect=false;

	this->FinalizeApp();
	if(m_hDevice!=0)
		vciDeviceClose(m_hDevice);

}

/*****************************************************************************
 Function:
  SelectDevice

 Description:
  Selects the first CAN adapter.

 Arguments:
  fUserSelect -> If this parameter is set to TRUE the functions display
                 a dialog box which allows the user to select the device.

 Results:
  none
*****************************************************************************/
long CUSBCAN::SelectDevice( BOOL fUserSelect )
{
  HRESULT hResult; // error code
  
  if (fUserSelect == FALSE)
  {
    HANDLE        hEnum;   // enumerator handle
    VCIDEVICEINFO sInfo;   // device info
    //
    // open the device list
    //
    hResult = vciEnumDeviceOpen(&hEnum);

    //
    // retrieve information about the first
    // device within the device list
    //
//    if (hResult == VCI_OK)
	int cnt=0;
	m_DevCount=0;
	while(hResult == VCI_OK)
    {
	      hResult = vciEnumDeviceNext(hEnum, &sInfo);
		  if(hResult== VCI_OK)
		  {
			  sDevInfo[m_DevCount++]=sInfo;
			  printf("\n[%s] id=(%X) result=%d %s",sDevInfo[cnt].UniqueHardwareId.AsChar
					,sDevInfo[cnt].VciObjectId,hResult,sDevInfo[cnt].Description);
			cnt++;
		  }
	}
//	printf("\n [%d]",hResult);
	DisplayError(hResult);
  

    //
    // close the device list (no longer needed)
    //
    vciEnumDeviceClose(hEnum);

#ifdef USB_TEST
	VCIDEVICECAPS Caps;
	for(  i=0;i<cnt;i++)
	{
			hResult=vciDeviceOpen(sDevInfo[i].VciObjectId, &m_hDevice);
//			vciDeviceGetCaps(hDevice,pCaps);
		vciDeviceGetCaps(m_hDevice,&Caps);
		printf("\n%d %d",i,Caps.BusCtrlCount);
		for(int j=0;j<Caps.BusCtrlCount;j++)
		{
			printf(" [%X BUS_TYPE=%d %d ]",Caps.BusCtrlTypes[j],VCI_BUS_TYPE(Caps.BusCtrlTypes[j])
				,VCI_CTL_TYPE(Caps.BusCtrlTypes[j]));
		}
		vciDeviceClose(m_hDevice);
	}

#endif
    //
    // open the device
    //
	if(m_DevCount >0) hResult=VCI_OK;
/*
    if (hResult == VCI_OK)
    {
      hResult = vciDeviceOpen(sInfo.VciObjectId, &m_hDevice);
    }
*/	
  }
  else
  {
    //
    // open a device selected by the user
    //
    hResult = vciDeviceOpenDlg(NULL, &m_hDevice);

  }

  return hResult;

  
}

/*************************************************************************
 Function: 
  InitSocket

 Description : 
  Opens the specified socket, creates a message channel, initializes
  and starts the CAN controller.

 Arguments: 
  dwCanNo -> Number of the CAN controller to open.

 Results:
  none

 Remarks:
  If <dwCanNo> is set to 0xFFFFFFFF, the function shows a dialog box
  which allows the user to select the VCI device and CAN controller.


 		m_lowCan.CanInitial(CAN_OPMODE_LOWSPEED,CAN_BT0_100KB,CAN_BT1_100KB,B_CAN);
   void CUSBCAN::CanInitial(UINT8 bMode,UINT8 uBit0,UINT8 uBit1,UINT32 cardNum)
       	         InitSocket(cardNum,&m_hDevice, &m_hCanChn, &m_hCanCtl,bMode,uBit0,uBit1);

*************************************************************************/
void CUSBCAN::InitSocket(UINT32 dwCanNo, HANDLE *hDev, HANDLE *hChn, HANDLE *hCon,UINT8 bMode,UINT8 ubit,UINT8 ubit2)
{
  HRESULT hResult;

  //
  // create a message channel
  //
  hResult = canChannelOpen(*hDev, dwCanNo, FALSE, hChn);

  //
  // initialize the message channel
  //
  if (hResult == VCI_OK)
  {
    UINT16 wRxFifoSize  = 1024;
    UINT16 wRxThreshold = 1;
    UINT16 wTxFifoSize  = 128;
    UINT16 wTxThreshold = 1;

    hResult = canChannelInitialize( *hChn,
                                    wRxFifoSize, wRxThreshold,
                                    wTxFifoSize, wTxThreshold);
  }

  //
  // activate the CAN channel
  //
  if (hResult == VCI_OK)
  {
    hResult = canChannelActivate(*hChn, TRUE);
  }

  //
  // open the CAN controller
  //
  if (hResult == VCI_OK)
  {
    hResult = canControlOpen(*hDev, dwCanNo, hCon);
//	canControlOpen(hDev,dwCanNo,hCon);

    // this function fails if the controller is in use
    // by another application.
  }

  //
  // initialize the CAN controller
  //
  if (hResult == VCI_OK)
  { 
	  CAN_OPMODE_LOWSPEED;
	 hResult = canControlInitialize(*hCon, bMode,
                                   ubit, ubit2);
	printf("\nCUSBCAN::InitSocket()line=%d canControlInitialize()= %d mode=%X  card num=%d =====>>>",__LINE__,hResult,bMode,dwCanNo);

  }
//	canControlReset(*hCon);		//open 상태로
//
//	canControlGetCaps(*hCon,
 // canControlDetectBitrate(*hCon,
  //
  // set the acceptance filter
  //
  if (hResult == VCI_OK)
  { 
     hResult = canControlSetAccFilter( *hCon, FALSE,
                                       CAN_ACC_CODE_ALL, CAN_ACC_MASK_ALL);
  }
///////////////////////////
  //
  // start the CAN controller
  //
  if (hResult == VCI_OK)
  {
    hResult = canControlStart(*hCon, TRUE);
  }
//
  if(hResult == VCI_OK) 
  {
	  m_fCanUse=TRUE;	// VCI_OK == VCI_SUCCESS
	  m_bConnect=true;

  }
  DisplayError(hResult);
}

/*************************************************************************
 Function: 
  TransmitData

 Description: 
  Transmits a CAN message with ID 0x100.

 Arguments: 
  none

 Results:
  none
*************************************************************************/
void CUSBCAN::TransmitData(DWORD dwMsgID,BYTE dlc,UINT8 *abData)
{
  HRESULT hResult;
  
  UINT8   i;
	
  m_sTxCanMsg.dwTime   = 0;
  m_sTxCanMsg.dwMsgId  = dwMsgID;    // CAN message identifier

  m_sTxCanMsg.uMsgInfo.Bytes.bType  = CAN_MSGTYPE_DATA;
  m_sTxCanMsg.uMsgInfo.Bytes.bFlags = CAN_MAKE_MSGFLAGS(dlc,0,0,0,0);

  for (i = 0; i < m_sTxCanMsg.uMsgInfo.Bits.dlc; i++ )
  {
    m_sTxCanMsg.abData[i] = abData[i];
  }
  	
  // write the CAN message into the transmit FIFO
  
  hResult = canChannelPostMessage(m_hCanChn, &m_sTxCanMsg);
  if(hResult==VCI_E_TXQUEUE_FULL)
  {
		canChannelWaitTxEvent(m_hCanChn,INFINITE);
		hResult = canChannelPostMessage(m_hCanChn,  &m_sTxCanMsg);
  }
  
  if(hResult==VCI_OK)
  {
	  CString strTemp;
	  m_ctEnd=clock();
	  m_sTxCanMsg.dwTime=m_dwTime+(DWORD)(((m_ctEnd-m_ctStart)/0.000667));
//		
//   printf("\nCUSBCAN::TransmitData() <%d> %d %d %d",__LINE__,m_dwTime,m_ctEnd,m_ctStart);//
//	  printf("\n %d ",m_sTxCanMsg.dwTime);
	  TraceSendMsg(FALSE);	//TX
  }
  this->DisplayError(hResult);
}



DWORD WINAPI ReceiveThreadProc(LPVOID lpData)
{
	CUSBCAN *pCan = (CUSBCAN *)lpData;

	CString strTemp;
	CString strData;
	HRESULT hResult;
	

	while(pCan->m_fCanUse)
	{
		while((hResult=canChannelWaitRxEvent(pCan->m_hCanChn,INFINITE)) == VCI_OK)
		{
			while(canChannelPeekMessage(pCan->m_hCanChn,&pCan->m_sCanMsg) == VCI_OK)
			{
				pCan->m_ctStart=clock();
				pCan->m_dwTime = pCan->m_sCanMsg.dwTime;
				if (pCan->m_sCanMsg.uMsgInfo.Bytes.bType == CAN_MSGTYPE_DATA)
				{
					pCan->TraceSendMsg(TRUE);		// Rx message
					/*
					if (pCan->m_sCanMsg.uMsgInfo.Bits.rtr == 0)
					{


					}else
					{
					strTemp.Format("1.... Time: %10u ID: %3X  DLC: %1u  Remote Frame",
					pCan->m_sCanMsg.dwTime,
					pCan->m_sCanMsg.dwMsgId,
					pCan->m_sCanMsg.uMsgInfo.Bits.dlc);
					}
					*/
				}else if (pCan->m_sCanMsg.uMsgInfo.Bytes.bType == CAN_MSGTYPE_INFO)
				{
					//
					// show informational frames
					//
					switch (pCan->m_sCanMsg.abData[0])
					{
					case CAN_INFO_START: strTemp.Format("\nCAN started..."); break;
					case CAN_INFO_STOP : strTemp.Format("\nCAN stoped...");  break;
					case CAN_INFO_RESET: strTemp.Format("\nCAN reseted..."); break;
					}
					pCan->StatusSendMsg(strTemp);		//

					//	AfxMessageBox(strTemp);
				}else if (pCan->m_sCanMsg.uMsgInfo.Bytes.bType == CAN_MSGTYPE_ERROR)
				{
					//
					// show error frames
					//
					switch (pCan->m_sCanMsg.abData[0])
					{
					case CAN_ERROR_STUFF: strTemp.Format("\nstuff error...");          break; 
					case CAN_ERROR_FORM : strTemp.Format("\nform error...");           break; 
					case CAN_ERROR_ACK  : strTemp.Format("\nacknowledgment error..."); break;
					case CAN_ERROR_BIT  : strTemp.Format("\nbit error...");            break; 
					case CAN_ERROR_CRC  : strTemp.Format("\nCRC error...");            break; 
					case CAN_ERROR_OTHER:
					default             : strTemp.Format("\nother error...");          break;
					}
					pCan->StatusSendMsg(strTemp);		//

				}

			}

		}

	}
	return 0;
}

#ifdef Kwon

void CUSBCAN::ReceiveData(DWORD &dwMsgID,BYTE &dlc,UINT8 *retData)
{
	HRESULT hResult;
	CANMSG  sCanMsg;

//	char cLog[100];

	hResult = canChannelWaitRxEvent(m_hCanChn, 100);
	
    hResult = canChannelReadMessage(m_hCanChn, 100, &sCanMsg);

	if (hResult == VCI_OK)
	{
		m_fError=FALSE;
		if (sCanMsg.uMsgInfo.Bytes.bType == CAN_MSGTYPE_DATA)
		{
    
			if (sCanMsg.uMsgInfo.Bits.rtr == 0)
			{
				UINT8 j;
/*
				sprintf(cLog,"\n1.... Time: %10u  ID: %3X  DLC: %1u  Data:",
							sCanMsg.dwTime,
							sCanMsg.dwMsgId,
							sCanMsg.uMsgInfo.Bits.dlc);
*/
				dwMsgID = sCanMsg.dwMsgId;
				dlc = sCanMsg.uMsgInfo.Bits.dlc;
				for (j = 0; j < sCanMsg.uMsgInfo.Bits.dlc; j++)
				{
//					sprintf(cLog," %.2X", sCanMsg.abData[j]);
					retData[j]=sCanMsg.abData[j];
				}


			}else
			{
/*				sprintf(cLog,"\n1.... Time: %10u ID: %3X  DLC: %1u  Remote Frame",
				 sCanMsg.dwTime,
				 sCanMsg.dwMsgId,
				 sCanMsg.uMsgInfo.Bits.dlc);
*/			}
		}
/*		else if (sCanMsg.uMsgInfo.Bytes.bType == CAN_MSGTYPE_INFO)
		{
    		switch (sCanMsg.abData[0])
			{
			  case CAN_INFO_START: sprintf(cLog,"\nCAN started..."); break;
			  case CAN_INFO_STOP : sprintf(cLog,"\nCAN stoped...");  break;
			  case CAN_INFO_RESET: sprintf(cLog,"\nCAN reseted..."); break;
			}
		
		}else if (sCanMsg.uMsgInfo.Bytes.bType == CAN_MSGTYPE_ERROR)
		{
			switch (sCanMsg.abData[0])
			{
			  case CAN_ERROR_STUFF: sprintf(cLog,"\nstuff error...");          break; 
			  case CAN_ERROR_FORM : sprintf(cLog,"\nform error...");           break; 
			  case CAN_ERROR_ACK  : sprintf(cLog,"\nacknowledgment error..."); break;
			  case CAN_ERROR_BIT  : sprintf(cLog,"\nbit error...");            break; 
			  case CAN_ERROR_CRC  : sprintf(cLog,"\nCRC error...");            break; 
			  case CAN_ERROR_OTHER:
			  default             : sprintf(cLog,"\nother error...");          break;
			}
		}
*/
	}
}
#endif

void CUSBCAN::CanInitial(UINT8 bMode,UINT8 uBit0,UINT8 uBit1,UINT32 cardNum)
{
	this->FinalizeApp();
	int i;
	HRESULT hResult; 			
	VCIDEVICECAPS Caps;
	if(m_DevCount == 0)
	{
		AfxMessageBox("Connect CAN card !(CAN을 찾을수 없습니다.)");
		return;
	}

	for(i=0;i<m_DevCount;i++)
	{
		hResult=vciDeviceOpen(sDevInfo[i].VciObjectId, &m_hDevice);

		vciDeviceGetCaps(m_hDevice,&Caps);
/*	
		printf("\ndevnum=%d busctrlcount=%d [%s] %d",i,Caps.BusCtrlCount,	// 해당 card 가 없습니다.
		sDevInfo[i].UniqueHardwareId.AsChar,sDevInfo[i].UniqueHardwareId.AsGuid);;
*/
		if(Caps.BusCtrlCount>2)
		{
			m_CardIndex=i;	// -1 이면 error
			break;
		}
//		
		for(int j=0;j<Caps.BusCtrlCount;j++)
		{
				printf(" [%X BUS_TYPE=%d %d ]",Caps.BusCtrlTypes[j],VCI_BUS_TYPE(Caps.BusCtrlTypes[j])
					,VCI_CTL_TYPE(Caps.BusCtrlTypes[j]));
			m_CardIndex=-7;	// for test routine
		}
//
		vciDeviceClose(m_hDevice);
	}

//	printf("\nCanInitilized %d %d",m_CardIndex,i);
 
	CANCAPABILITIES cap;
	InitSocket(cardNum,&m_hDevice, &m_hCanChn, &m_hCanCtl,bMode,uBit0,uBit1);
//	canSchedulerOpen(m_hDevice,0,&m_hScheduler);
//	canSchedulerGetCaps(m_hScheduler,&cap);
//* 여기서	사용하는곳 없다.
	canControlGetCaps(m_hCanCtl,&cap);	// for test
//	cap.dwClockFreq;

//	printf("\ncap.dwClockFreq=%d %d %d",cap.dwClockFreq,cap.dwCmsDivisor,cap.dwTscDivisor);
//
	cap.dwClockFreq=10;cap.dwCmsDivisor=10;
	cap.dwTscDivisor=10;
	m_dTick=(cap.dwClockFreq/cap.dwCmsDivisor)/1000;
	m_dTimeRes=(double)cap.dwTscDivisor/cap.dwClockFreq;

//	CString strTemp;
//	strTemp.Format("%d %d %.8f",cap.dwTscDivisor,cap.dwClockFreq,m_dTimeRes);
/////// 여기 까지 

//	canSchedulerActivate(m_hScheduler,TRUE);
//	m_fCanUse=TRUE;
	if(m_fCanUse)
	{
	 	SetCardNum(cardNum);
		AfxBeginThread((AFX_THREADPROC)ReceiveThreadProc,(LPVOID)this,THREAD_PRIORITY_ABOVE_NORMAL);
	}
}

/*************************************************************************
 Function: 
  FinalizeApp

 Description: 
  Finalizes the application

 Arguments: 
  none
  
 Results:
  none
*************************************************************************/
void CUSBCAN::FinalizeApp()
{
 	if(m_hScheduler!=NULL)
	{
		canSchedulerActivate(m_hScheduler,FALSE);
		canSchedulerReset(m_hScheduler);
		canSchedulerClose(m_hScheduler);
	}
	if(m_hCanChn!=NULL)
		canChannelClose(m_hCanChn);
	if(m_hCanCtl!=NULL)
		canControlClose(m_hCanCtl);

	m_bConnect=false;
	m_CardIndex=-1;
	
	
}

/*************************************************************************
 Function: 
  DisplayError

 Description : 
  This function displays a message box for the specified error code.

 Arguments : 
  hResult -> Error code or -1 to display the error code returned
             by GetLastError().

 Results:
  none
*************************************************************************/
char *CUSBCAN::DisplayError(HRESULT hResult)
{
  
  if (hResult != NO_ERROR)
  {
    if (hResult == -1)
      hResult = GetLastError();

    m_szError[0] = 0;
    vciFormatError(hResult, m_szError, sizeof(m_szError));
//	printf("\n<%s>",m_szError);
    return m_szError;
  }
  return NULL;
}


#ifdef Kwon
void CUSBCAN::CyclicAdd(DWORD dwID,unsigned char *cData,WORD wCycleTime)
{
	CANCYCLICTXMSG msg;
	unsigned int iIndex;
	int i;

	
	msg.wCycleTime=(WORD)(wCycleTime*m_dTick);
	msg.bIncrMode=CAN_CTXMSG_INC_NO;
	msg.bByteIndex=1;
	msg.dwMsgId=dwID;
	msg.uMsgInfo.Bytes.bType  = CAN_MSGTYPE_DATA;
    msg.uMsgInfo.Bytes.bFlags = CAN_MAKE_MSGFLAGS(8,0,0,0,1);
	for( i=0;i<8;i++)
	{
		msg.abData[i]=cData[i];
	}
	canSchedulerAddMessage(m_hScheduler,&msg,&iIndex);

	
	canSchedulerStartMessage(m_hScheduler,iIndex,0);
	
}

#endif


void CUSBCAN::GetDviceInfo(PVCIDEVICEINFO pInfo)
{
	HRESULT hResult;
	hResult=vciDeviceGetInfo(m_hDevice,pInfo);
}

void CUSBCAN::SetNodeNum(DWORD num)
{
	m_dwNode=num;
}

void CUSBCAN::SetCardNum(UINT32 cardNum)
{
	m_CardNum=cardNum;
}


void CUSBCAN::SetMainWnd(HWND hWnd)
{
	m_hMainWnd=hWnd;
}

void CUSBCAN::SetTraceWnd(HWND hWnd)
{
	m_hTraceWnd=hWnd;		// 미사용
}

void CUSBCAN::TraceSendMsg(BOOL mode)
{
	if(m_hMainWnd!=NULL)
	{
		::PostMessage(m_hMainWnd,WM_CANTRACEUPDATE,m_CardNum,mode);	// Message Q 사용
//		SendMessage(m_hMainWnd,WM_CANTRACEUPDATE,m_CardNum,mode);	// 바로 전송
//		if(m_CardNum==1) AfxMessageBox("Rdy");
	}
}


// 사용 안함.
 
void CUSBCAN::StatusSendMsg(CString strData)
{
	m_CanStatusMsg=strData;
	if(m_hMainWnd!=NULL)
	{
		SendMessage(m_hMainWnd,WM_CANSTATUSUPDATE,m_CardNum,m_dwNode);	// 바로 전송
	}
}

 

