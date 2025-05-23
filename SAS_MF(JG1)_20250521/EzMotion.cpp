// EzMotion.cpp: implementation of the CEzMotion class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SAS_1.h"
#include "EzMotion.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEzMotion::CEzMotion()
{
	m_lModuleCount=0;m_lAxisCount=0;
}

CEzMotion::~CEzMotion()
{
 
	if(AxlIsOpened())
	{
		DoOutAllOFF();
		AxlClose();
	}
}


// io card initilize

BOOL CEzMotion::Initialize_Motion()
{
	int retVal=TRUE;
	DWORD Code,dwStatus;
	if(AxlOpen()!=AXT_RT_SUCCESS)
	{
		AfxMessageBox("AxlOpen Fail...");
		return FALSE;
	}
	//++ ��ȿ�� ��ü �������� ��ȯ�մϴ�.
	Code=AxmInfoGetAxisCount(&m_lAxisCount);
	if(Code!=AXT_RT_SUCCESS)
		return FALSE;
	if(m_lAxisCount < 1)	
		return FALSE;
	m_lAxisNo = 0;
//	TRACE("Library initialized Ok ��=%d\n",m_lAxisCount);
	//++ ������ ���� ������ ��ȯ�մϴ�.
	// [INFO] �������� ������ �д� �Լ� ���� ���ʿ��� ������ NULL(0)�� �Է��ϸ� �˴ϴ�.
	Code=AxmInfoGetAxis(m_lAxisNo, NULL, NULL, &m_dwModuleID);

	if(Code==AXT_RT_SUCCESS)
	{
		AxmSignalGetServoAlarm(0,&dwStatus);
		printf("\nAxmSignalGetServoAlarm()<%d>",dwStatus);
		AxmSignalSetServoAlarm(0,LOW);		// B���� normal close �� ��� �Ѵ�. HIGH
		Position_Reset();

		AxmMotGetEncInputMethod(0,&dwStatus);
		printf("\nAxmMotGetEncInputMethod()<%d>",dwStatus);	// 3 ���� ���� 
	//	TwoCcwCwLow;OneLowLowHigh
 		AxmMotSetEncInputMethod(0,OneLowHighLow);

	}

 
	long lincnt,loutcnt;
 
	Code = AxdInfoIsDIOModule(&dwStatus);	// dio module Ȯ�� axd.h
	if(dwStatus== STATUS_EXIST)
	{
		Code=AxdInfoGetModuleCount(&m_lModuleCount);
		if(Code == AXT_RT_SUCCESS)	
		{
			printf("\n Number of DIO module %d",m_lModuleCount);
			for(int ModuleNo=0;ModuleNo < m_lModuleCount;ModuleNo++)
			{
				AxdInfoGetInputCount(ModuleNo,&lincnt);
				AxdInfoGetOutputCount(ModuleNo,&loutcnt);
				printf("\n %d %d %d ",ModuleNo,lincnt,loutcnt);
			}
		}
	}


	return retVal;
}


void CEzMotion::Position_Reset()
{
	AxmStatusSetCmdPos(m_lAxisNo, 0.0);
	AxmStatusSetActPos(m_lAxisNo, 0.0);		// ������ġ�� �������� ���� �Ѵ�.

}


void CEzMotion::ServoOn(BOOL mode)
{
	AxmSignalServoOn(m_lAxisNo, mode);
}

// SAS Power & ig On
void CEzMotion::SASPowerEnable(BOOL mode)
{
	long IModuleCounts;
	AxdInfoGetModuleCount(&IModuleCounts);
	
	if(IModuleCounts > 0)
	{	
		long	lNodeNo;
		long	lModulePos;
		DWORD	dwModuleID;
	
		short	nIndex;
		nIndex	= obSASPower;
		if(AxdInfoGetModule(0, &lNodeNo, &lModulePos, &dwModuleID) == AXT_RT_SUCCESS)
		{
			AxdoNWriteOutportBit(lNodeNo, lModulePos, nIndex, mode);
			AxdoNWriteOutportBit(lNodeNo, lModulePos, obMFIGN, mode);
			AxdoNWriteOutportBit(lNodeNo, lModulePos, 3, mode);//
		}
	}
}


int CEzMotion::MoveServo(double dMovePos,double dMoveVel,double dMoveAcc,double dMoveDec)
{

	DWORD	dwRetCode;
	dMovePos = dMovePos * DIR;

	//++ ������ ���� ������ �Ÿ�(�Ǵ� ��ġ)/�ӵ�/���ӵ�/���ӵ��� ��Ǳ����ϰ� ��� ���Ῡ�ο� ������� �Լ��� �������ɴϴ�.
	dwRetCode = AxmMoveStartPos(m_lAxisNo, dMovePos, dMoveVel, dMoveAcc, dMoveDec);
	if(dwRetCode != AXT_RT_SUCCESS)
	{
 		return -1;
	}else
	{
		return 1;
	}
}
int CEzMotion::RdoAbsRelMode(int mode) 
{
	DWORD	dwRetCode;
	

	//++ ���� ���� ���� ��ǥ�踦 �����մϴ�. 
	// dwAbsRelMode : (0)POS_ABS_MODE - ���� ��ġ�� ������� ������ ��ġ�� ������ǥ �̵��մϴ�.
	//                (1)POS_REL_MODE - ���� ��ġ���� ������ �縸ŭ �����ǥ �̵��մϴ�.
	dwRetCode = AxmMotSetAbsRelMode(m_lAxisNo, mode);
	if(dwRetCode != AXT_RT_SUCCESS)
	{
		return -1;
	}else
	{
		return 1;
	}

}
double CEzMotion::GetFeedBackPos()
{
	double dActPos;
	AxmStatusGetActPos(m_lAxisNo, &dActPos);
// DIR
	dActPos = -PULSE2ANG * dActPos ;// *    0.01       *360/7200.00000;

	return dActPos;
}
BOOL CEzMotion::GetBusyCheck()
{
	DWORD dwBusyStatus;
	AxmStatusReadInMotion(m_lAxisNo, &dwBusyStatus);
	return dwBusyStatus;
}


void CEzMotion::MoveServoStop()
{
	AxmMoveSStop(m_lAxisNo);
}


void CEzMotion::DoOutBit(long ModulePos,long BitPos,DWORD flag)
{
	AxdoNWriteOutportBit(0,ModulePos,BitPos,flag);
}



void CEzMotion::DoOutAllOFF(void)
{
	AxdoNWriteOutportWord(0,Do_0,0,0);
	AxdoNWriteOutportDword(0,Do_1,0,0);
	AxdoNWriteOutportDword(0,Do_2,0,0);
}
