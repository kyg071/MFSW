

#pragma once




#define MSG_AUTO_RUN		31
#define MSG_AUTO_STOP		32
#define MSG_RESULT_CHANGE	33
#define MSG_MODEL_CHANGE	34
#define MSG_INSIGNAL_CHANGE	35
#define MSG_FORCE_DATA_DRAW 36
#define MSG_STATE_WRITE		37
#define MSG_COUNT_CHANGE	38
#define MSG_MASTER_PASS		39

#define MSG_MANUAL_TEST		40
#define MSG_SERVO_TX		41

#define MSG_SERVO_POSEND	400
#define MSG_SERVO_POSSTART	450
#define MSG_SERVO_RES	200
#define MSG_ROCKVOLT	201

 

#define SV_JOG_CCW		1
#define SV_JOG_CW		2
#define SV_HOME			3
#define SV_POS_ST		4
#define SV_POS_END		5
#define SV_1_CYCLE		6
#define SV_STOP			7


//#include "SpecTable.h"

//#include "comm.h"



class CTestProc
{
public:
	CTestProc(void);
	virtual ~CTestProc(void);
	void CreadtMyObject(void);
	void DeleteMyObject(void);

 

//	CComm m_Load,m_cBarReader,m_cServo;
	
	
	CString m_strBarCode;
	CString m_strLoad;


/*
	int ComPortLoad;
	int ComPortBarCode;
//
	int ComServo;
*/ 

	CFont Font1,Font2,Font3,Font4,Font5;
	
	void BitOut(int drv, short Pos, BOOL mode);
	void SerVo(BOOL mode);
	void SerVoReset(BOOL mode);
	void SerVoEmg(BOOL mode);
	void DioOut(int drv,int port,BYTE data,BOOL mode);
	BYTE DioIn(int drv,int port);


	void IOClear();
	void SetSpecL(int pos=0);
	short m_hDio[3],m_hAio;
	BYTE m_bOut[32];
	 
	double m_dAD[16];

	short m_hSMCID;//
	bool  m_fSMCOK;
	//TEST_ITEM m_sItem[MAX_GROUP][MAX_ITEM];


	CString m_strPartNo[10];
	CString m_strMobse[10];
	CString m_strModel[4];
	CString m_strPassWord;


	int m_nSerial[5];
	int m_nTotalCnt[5];
	int m_nGoodCnt[5];
	int m_nNGCnt[5];
	int m_nTestCnt[5];
	int m_nDate[5];
 
 
	int m_iMaxTestCount;
	int m_iWarnTestCount;
	int m_iCurrTestCount;
	int m_iCurrTestCount2;	// Rigth

	bool m_bRun;

	double m_dMaxL[10][10],m_dMinL[10][10];
	double m_dMaxR[10][10], m_dMinR[10][10];
	CString m_strSpecL[10][10];
	CString m_strSpecR[10][10];
	CString m_strSpec[10][10];

	long m_lDistance[10][5], m_lSpeed[10][5];
	long m_lMovePulse[10], m_lMoveSpeed[10];
	//PRINT_SET m_iPrint;


	void SaveCoordinate();
	void ReadPrintCoordinate();
	void Loadini(TCHAR * filename);
	void Saveini(TCHAR * filename);
	void WriteLogR(CString strData);
	void WriteLogL(CString strData);
	int m_iSaveData;
	int m_iMasterPass;


 
	double m_dGap[4];

	void SaveData(int MaxCnt, int CenterCnt, int pos=0);

	int ReadData(int* MaxCnt, int* CenterCnt, CString FileName);

	void ValueClearR();

	void ValueClearL();

	void SetSpecR(int pos=0);
	void ReadSpec();
	void SaveSpec();

	void SaveCountL();
	void SaveCounrR();
	void ReadCounrL();
	void ReadCounrR();

	void WriteDataR(CString strData);
	void WriteDataL(CString strData);

	/* 
	CArray <CSpecTable, CSpecTable&> SpecFile;
	CSpecTable m_cSpec;
	*/ 
	int m_iComPortBarCode;


	int m_iWidth,m_iHeight;

//
	char StateText[100];

	bool bAutoRun, bThreadRdy;
	bool bAutoRunR ;

	bool bSpecChange, bTestPrint;
	DWORD InputSignal[2];
	bool InputBit[64], OldInputBit[64], OutputBit[64];
	bool IsEmoSw;
	void OutBitSignal(int Pos, bool isset);
//	int m_iTestNum;			// ManualTest
 
	BYTE m_bHomeCheck;
	bool m_bManualReq;
	int	 m_iServoRxDone;	// Error Code
 
	void BarCodePrintLable(void);
	BYTE m_bTxCmd;
	BOOL m_bTxData;
//	double dTorQue[10000];
 
	double mpTroQue[4][MAX_DATA];
	long mpCount[4][MAX_DATA];
	BYTE mpKey[4][MAX_DATA];	// key bit0 Start bit 1 ,APC bit4 LockBar(I_14)
 
	int m_iRedPulse;
	double m_dServoAngle;	// Max Count 
	double m_dReadTrq;
	double m_dReadTrqComp;	// 보상값
	bool m_fKeyClear;

	bool m_bServoOn;
	int m_iServoMode;// 운전모드
	int m_iServoModeR;// 운전모드

	int m_iServoAlarm;
	int m_iServoPos;	// 펄스 위치 값..
	BYTE m_bServoStatus;	// 응답코드
	short m_sStartDir;
	bool m_bServoRun;
	bool m_bServoRunR;

	void GetADData();

	void ReadModelFile();
	void SaveModelFile();
	int m_iSelModelPos;
	bool Test_Measuer();
	bool m_bHomeDone[10];	// 

	void SMC_Init(bool fMode = true);
	
	void BPlus(bool mode);
	void IGN1(bool mode);
	void IGN2(bool mode);
	void CCanCon(bool mode,bool reg=true);
	void BCanCon(bool mode,bool reg=true);
	void RCanCon(bool mode,bool reg=true);
 
};


