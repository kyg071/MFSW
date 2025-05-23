// EzMotion.h: interface for the CEzMotion class.
//
//////////////////////////////////////////////////////////////////////
 
#pragma once
 
#include "../../AXLNet(Library)/C, C++/AXL.h"
#include "../../AXLNet(Library)/C, C++/AXM.h"
#include "../../AXLNet(Library)/C, C++/AXD.h"


/*
#ifdef  _M_X64
#pragma comment(lib, "../../../../AXLNet(Library)/Library/64Bit/AXLNet.lib")
#else
#pragma comment(lib, "../../../../../AXLNet(Library)/Library/32Bit/AXLNet.lib")
#endif
*/

class CEzMotion  
{
public:
	CEzMotion();
	virtual ~CEzMotion();
	
	long		m_lAxisNo;					// 제어할 축 번호
	long		m_lAxisCount;				// 유효한 전체 모션축수
	DWORD		m_dwModuleID;				// 선택한 축의 모델ID
	
	BOOL Initialize_Motion(void);
	void Position_Reset(void);
	void ServoOn(BOOL mode);
	void SASPowerEnable(BOOL mode);
	int MoveServo(double dMovePos,double dMoveVel,double dMoveAcc,double dMoveDec);
	int RdoAbsRelMode(int mode);
	double GetFeedBackPos();
	BOOL GetBusyCheck();
	void MoveServoStop();
	void DoOutBit(long ModulePos,long BitPos,DWORD flag);
	void DoOutAllOFF(void);
	long	m_lModuleCount;

};

 