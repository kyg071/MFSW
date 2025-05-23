 

#include "stdafx.h"
#include "TestProc.h"
#include <conio.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h>


#include <propkey.h>

 



CTestProc::CTestProc(void)
:m_bTxCmd(0)
, m_bTxData(FALSE)
{
//	m_bServoTXRdy=false;
	int i;
	for(i=0;i<4;i++)
		m_nTotalCnt[i] =m_nGoodCnt[i] = m_nNGCnt[i] =m_nSerial[i]= 0;

	for (i = 0; i < 10; i++)
		m_bHomeDone[i] = false;	// 원점 완료 확인..

	m_strModel[0]=m_strPartNo[0] = "81820-G0100";
 	m_iWidth=100;m_iHeight=100;	// worksheet size
	m_strMobse[0] = "3CN590-1000";
 
//	m_strMobse[0] = buf;
//  HKMC P/N :81820-G0100
//  P/N      :3CN590-1000
//  LOT      :202409250001

	m_strPassWord="1234";
	m_bRun=false;
	bAutoRun = bThreadRdy = false;
	bAutoRunR = bThreadRdy = false;

	bSpecChange = bTestPrint = false;
	InputSignal[0]=0;
 
	for(i=0;i<32;i++)
	  OldInputBit[i]=OutputBit[i]=false;
	m_bManualReq=false;
	m_iServoRxDone=0;
	m_dReadTrq=0;
	m_dReadTrqComp=0;
	m_iMasterPass = 0;
	m_iSelModelPos = -1;	// 선택이 안됨
//	

#ifdef POINTER_TYPE
	mpTroQue = new  double* [4];
	mpCount = new long* [4];
	mpKey = new BYTE * [4];
	for (i = 0; i < 4; i++)
	{
		mpTroQue[i] = new double[MAX_DATA];
		mpCount[i] = new long[MAX_DATA];
		mpKey[i] = new BYTE[MAX_DATA];
	}
#endif
//	mpCount=(double *)malloc(MAX_DATA * sizeof(double));
//	mpKey = (DWORD*)malloc(MAX_DATA * sizeof(DWORD));

 

	m_iServoMode=0;// 운전모드
	m_bServoStatus=0;	// 응답코드
	m_iServoAlarm=0xFF;
	m_iServoPos=0;	// 펄스 위치 값..
	m_dServoAngle=0;	// Max Count 
	m_sStartDir = CSMC_CW;//;CSMC_CW
	m_fKeyClear=false;
	m_bServoRun = false;
	m_bServoOn = false;

	 
	ReadModelFile();
//	printf("\nTestPrc Done");
	int j;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 5; j++)
		{
			m_lDistance[i][j] = 10000;	// Y = 5000 Pulse 5 mm, X,Z=10,000 = 10mm  1회전
 			m_lSpeed[i][j] = 10000;	// pps
		}
// JIG Test 용
		m_lMoveSpeed[i] = 1000;
		m_lMovePulse[i] = 1000;// 1 mm 
	}


}

 

void CTestProc::ValueClearR()
{
 
	 
	int i, j;

	i = 1;
	for (j = 0; j < MAX_DATA; j++)
	{
		mpTroQue[i][j] = 0;
		mpCount[i][j] = 0;
		mpKey[i][j] = 0;
	}
	m_fSMCOK = false;
 
}


void CTestProc::ValueClearL()
{

	int i, j;
 
	i = 0;
	for (j = 0; j < MAX_DATA; j++)
	{
		mpTroQue[i][j] = 0;
		mpCount[i][j] = 0;
		mpKey[i][j] = 0;
	}
	m_fSMCOK = false;

}


 


CTestProc::~CTestProc(void)
{
#ifdef POINTER_TYPE
	int i;
	for (i = 0; i < 4; i++)
	{
		delete [] mpTroQue[i];
		delete [] mpCount[i];
		delete[] mpKey[i];

	}
	delete[] mpTroQue;
	delete[]  mpCount;
	delete mpKey;
#endif
	printf("\n~CTestProc(void)");
}

//

//
//

void CTestProc::CreadtMyObject(void)
{
	Font1.CreateFont(12,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
						DEFAULT_QUALITY,FF_DONTCARE,"Arial");
	Font2.CreateFont(15,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
						DEFAULT_QUALITY,DEFAULT_PITCH,"Arial");
	Font3.CreateFont(18,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
						DEFAULT_QUALITY,DEFAULT_PITCH,"Arial");
	Font4.CreateFont(25,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
						DEFAULT_QUALITY,DEFAULT_PITCH,"Arial");
	Font5.CreateFont(45,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
						DEFAULT_QUALITY,DEFAULT_PITCH,"Arial");
	LONG Ret = 0;
	Ret = SmcWInit("SMC000", &m_hSMCID);
	if (Ret)
	{
		AfxMessageBox("SMC Card Not Fount");
		m_fSMCOK = false;
	}
	else
		m_fSMCOK = true;
 
 
}

void CTestProc::DeleteMyObject(void)
{
//	IOClear();
	Font1.DeleteObject();
	Font2.DeleteObject();
	Font3.DeleteObject();
	Font4.DeleteObject();
	Font5.DeleteObject();
	if (m_hSMCID != -1)
	{
		SmcWExit(m_hSMCID);
		printf("\n.....DeleteMyObject()");
	}
 
 
}


 
 

void CTestProc::OutBitSignal(int Pos, bool mode)
{
	BYTE data;
	int port;

	port = Pos % 8;
	data = 1 << port;
	port = Pos / 8;

	OutputBit[Pos]=mode;
// Byte 단위로 Write 하기 위해서
 	if (mode)
		m_bOut[port] |= data;
	else
		m_bOut[port] &= ~data;
//	DioOutBit(m_hDio[0],Pos,mode);
//	DioOutByte(m_hDio[0], port, m_bOut[port]);
 
}

void CTestProc::GetADData()
{
 
}

void CTestProc::ReadModelFile()
{
	CStdioFile spFile;
#ifdef USEMODEL
	SpecFile.RemoveAll();
	CString strTemp;
	if (!spFile.Open(SPECNAME, CFile::shareDenyNone | CFile::modeReadWrite | CFile::typeText))
	{
		strTemp.Format("\"%s\" 을 새로작성 합니다", SPECNAME);	//2018.12. YGKwon
		AfxMessageBox(strTemp);
		if (!spFile.Open(SPECNAME, CFile::shareDenyNone | CFile::modeCreate | CFile::modeReadWrite | CFile::typeText))
		{
			return;
		}
		spFile.WriteString("Model,모베이스 Code,CurstomerCode,Title,ALC,ImageName,TestMode,PrintMode,HW Ver,Force,조작력,거리,EO Code,Speare\n");
	}
	CString strTemp1;
	spFile.SeekToBegin();

	int pos;
	int i = 0;
	CSpecTable caTemp;

	caTemp.Spec.strALC.Empty();
	caTemp.Spec.iVision = 0;
	caTemp.Spec.iPrintMode = 0;
	caTemp.Spec.iTestMode = 0;
	caTemp.Spec.strHW_Ver = "B.0";
	caTemp.Spec.strSW_Ver = "B.0";
	caTemp.Spec.strImageName.Empty();


	if (spFile.ReadString(strTemp))
	{
		while (spFile.ReadString(strTemp))
		{
			pos = strTemp.Find(",");
			if (pos > 0)
			{
				caTemp.Spec.strModelName = strTemp.Left(pos);
				strTemp.Delete(0, pos + 1);
			}
			pos = strTemp.Find(",");
			if (pos > 0)
			{
				caTemp.Spec.strMBCode = strTemp.Left(pos);
				strTemp.Delete(0, pos + 1);
			}
			pos = strTemp.Find(",");
			if (pos > 0)
			{
				caTemp.Spec.strCustomerCode = strTemp.Left(pos);
				strTemp.Delete(0, pos + 1);
			}
			//////////
			pos = strTemp.Find(",");
			if (pos >= 0)
			{
				caTemp.Spec.strTitle = strTemp.Left(pos);
				strTemp.Delete(0, pos + 1);
				//		printf("Title=[%s] %d <%s>\n\r", caTemp.Spec.strTitle, pos,strTemp);	//
			}
			pos = strTemp.Find(",");
			if (pos >= 0)
			{
				caTemp.Spec.strALC = strTemp.Left(pos);
				strTemp.Delete(0, pos + 1);
			}

			pos = strTemp.Find(",");
			if (pos >= 0)
			{
				caTemp.Spec.strImageName = strTemp.Left(pos);
				strTemp.Delete(0, pos + 1);
			}
			//
			pos = strTemp.Find(",");

			if (pos >= 0)
			{
				strTemp1 = strTemp.Left(pos);
				strTemp.Delete(0, pos + 1);
				caTemp.Spec.iTestMode = atoi(strTemp1);
			}
			//
			pos = strTemp.Find(",");

			if (pos >= 0)
			{
				strTemp1 = strTemp.Left(pos);
				strTemp.Delete(0, pos + 1);
				caTemp.Spec.iPrintMode = atoi(strTemp1);
			}
			pos = strTemp.Find(",");
			if (pos >= 0)
			{
				caTemp.Spec.strHW_Ver = strTemp.Left(pos);
				strTemp.Delete(0, pos + 1);
			}
// Force
			pos = strTemp.Find(",");
			if (pos >= 0)
			{
				strTemp1 = strTemp.Left(pos);
				caTemp.Spec.dForce = _ttof(strTemp1);
 				strTemp.Delete(0, pos + 1);
			}
			else
				caTemp.Spec.dForce = 1.2;// N

// 조작력
			pos = strTemp.Find(",");
			if (pos >= 0)
			{
				strTemp1 = strTemp.Left(pos);
				strTemp.Delete(0, pos + 1);
				caTemp.Spec.dJoJak = _ttof(strTemp1);	// click 률
			}
			else
				caTemp.Spec.dJoJak = 60;
// 거리
			pos = strTemp.Find(",");
			if (pos >= 0)
			{
				strTemp1 = strTemp.Left(pos);
				strTemp.Delete(0, pos + 1);
				caTemp.Spec.dDist = _ttof(strTemp1);
			}
			else
				caTemp.Spec.dDist = 1.2;// atoi(strTemp1);
 //
			pos = strTemp.Find(",");
			if (pos >= 0)
			{
				caTemp.Spec.strECo = strTemp.Left(pos);
				strTemp.Delete(0, pos + 1);
				i++;
				SpecFile.Add(caTemp);
			}
			else
			{
				pos = strTemp.Find(0x0d);
				if (pos >= 0)
				{
					caTemp.Spec.strECo = strTemp.Left(pos);
					strTemp.Delete(0, pos + 1);
					i++;
					SpecFile.Add(caTemp);
				}
				else
				{
					printf("Tail Error\n\r");
				}
			}
			printf("\n%d Force=%.2f %.2f %.2f", i, caTemp.Spec.dForce, caTemp.Spec.dJoJak, caTemp.Spec.dDist);
		}
	}

	spFile.Close();
#endif

}

void CTestProc::SaveModelFile()
{
	CStdioFile spFile;
#ifdef USEMODEL
	//	SpecFile.RemoveAll();
	//	if (!spFile.Open("d:\\data\\Hcr BCM spec.txt", CFile::shareDenyNone | CFile::modeCreate | CFile::modeWrite | CFile::typeText))
	if (!spFile.Open(SPECNAME, CFile::shareDenyNone | CFile::modeCreate | CFile::modeWrite | CFile::typeText))
	{
		return;
	}
	spFile.SeekToBegin();
	spFile.WriteString("Model,모베이스 Code,CurstomerCode,Title,ALC,ImageName,TestMode,PrintMode,HW Ver,Force,조작력,거리,EO Code,Speare\n");

	int i;
	int count = SpecFile.GetSize();
	CString strTemp;
	CSpecTable caTemp;
	for (i = 0; i < count; i++)
	{
		caTemp = SpecFile.GetAt(i);
		strTemp.Format("%s,%s,%s,%s,%s,%s,%d,%d,%s,%s,%d,%d,%s,\n", caTemp.Spec.strModelName, caTemp.Spec.strMBCode, caTemp.Spec.strCustomerCode, caTemp.Spec.strTitle
			, caTemp.Spec.strALC, caTemp.Spec.strImageName
			, caTemp.Spec.iTestMode, caTemp.Spec.iPrintMode
			, caTemp.Spec.strHW_Ver, caTemp.Spec.strSW_Ver, caTemp.Spec.iVision, caTemp.Spec.b2DCode, caTemp.Spec.strECo);
		spFile.WriteString(strTemp);
	}
	spFile.Close();
#endif
}

bool CTestProc::Test_Measuer()
{
	return false;
}

void CTestProc::SMC_Init(bool fMode)
{
	CString strTemp;
 
  
}




void CTestProc::BitOut(int drv, short Pos, BOOL mode)
{
//	BYTE data;
//	int port;
 
	short OutData;
	 SmcWGetDigitalOut(m_hSMCID, drv, &OutData);
 
 //	 if ((OutData & CSMC_OUT1) == CSMC_OUT1) {
 	 SmcWSetDigitalOut(m_hSMCID,drv, mode, CSMC_OUT1);

}


void CTestProc::SerVo(BOOL mode)
{
	SmcWSetDigitalOut(m_hSMCID, 1, mode, S_ON);//CSMC_OUT1
}

void CTestProc::SerVoReset(BOOL mode)
{
	short OutData;
	SmcWGetDigitalOut(m_hSMCID, 1, &OutData);

	if(mode)
		SmcWSetDigitalOut(m_hSMCID, 1, CSMC_OUT2, CSMC_OUT2);//CSMC_OUT1
	else
		SmcWSetDigitalOut(m_hSMCID, 1, 0, CSMC_OUT2);//CSMC_OUT1

	SmcWGetDigitalOut(m_hSMCID, 1, &OutData);
}
// servor emergence
void CTestProc::SerVoEmg(BOOL mode)
{
	if (mode)
		SmcWSetDigitalOut(m_hSMCID, 1, CSMC_OUT3, CSMC_OUT3);//CSMC_OUT1
	else
		SmcWSetDigitalOut(m_hSMCID, 1, 0, CSMC_OUT3);//CSMC_OUT1

}


void CTestProc::BPlus(bool mode)
{
	if (mode)
		SmcWSetDigitalOut(m_hSMCID, 4, CSMC_OUT1, CSMC_OUT1);//CSMC_OUT1
	else
		SmcWSetDigitalOut(m_hSMCID, 4, 0, CSMC_OUT1);//CSMC_OUT1
}

void CTestProc::IGN1(bool mode)
{
	if (mode)
		SmcWSetDigitalOut(m_hSMCID, 4, CSMC_OUT2, CSMC_OUT2);//CSMC_OUT1
	else
		SmcWSetDigitalOut(m_hSMCID, 4, 0, CSMC_OUT2);//CSMC_OUT1
}

void CTestProc::IGN2(bool mode)
{
	if (mode)
		SmcWSetDigitalOut(m_hSMCID, 4, CSMC_OUT3, CSMC_OUT3);//CSMC_OUT1
	else
		SmcWSetDigitalOut(m_hSMCID, 4, 0, CSMC_OUT3);//CSMC_OUT1
}


void CTestProc::CCanCon(bool mode, bool reg)
{
	if (mode)
		SmcWSetDigitalOut(m_hSMCID, 3, CSMC_OUT1, CSMC_OUT1);//CSMC_OUT1
	else
		SmcWSetDigitalOut(m_hSMCID, 3, 0, CSMC_OUT1);//CSMC_OUT1
	if (reg)
		SmcWSetDigitalOut(m_hSMCID, 2, CSMC_OUT1, CSMC_OUT1);//CSMC_OUT1
	else
		SmcWSetDigitalOut(m_hSMCID, 2, 0, CSMC_OUT1);//CSMC_OUT1

}

void CTestProc::BCanCon(bool mode, bool reg)
{
	if (mode)
		SmcWSetDigitalOut(m_hSMCID, 3, CSMC_OUT2, CSMC_OUT2);//CSMC_OUT1
	else
		SmcWSetDigitalOut(m_hSMCID, 3, 0, CSMC_OUT2);//CSMC_OUT1
	if (reg)
		SmcWSetDigitalOut(m_hSMCID, 2, CSMC_OUT2, CSMC_OUT2);//CSMC_OUT1
	else
		SmcWSetDigitalOut(m_hSMCID, 2, 0, CSMC_OUT2);//CSMC_OUT1
}

void CTestProc::RCanCon(bool mode, bool reg)
{
	if (mode)
		SmcWSetDigitalOut(m_hSMCID, 3, CSMC_OUT3, CSMC_OUT3);//CSMC_OUT1
	else
		SmcWSetDigitalOut(m_hSMCID, 3, 0, CSMC_OUT3);//CSMC_OUT1
	if (reg)
		SmcWSetDigitalOut(m_hSMCID, 2, CSMC_OUT2, CSMC_OUT3);//CSMC_OUT1
	else
		SmcWSetDigitalOut(m_hSMCID, 2, 0, CSMC_OUT3);//CSMC_OUT1
}



void CTestProc::DioOut(int drv,int port,BYTE data,BOOL mode)
{
	drv=1;
//
//	DioEchoBackByte(m_hDio[drv],port,&m_bOut[drv*8+port]);// 외부에서 바뀌었을경우..가져오기위해
 	if(mode)
	{
		m_bOut[drv*8+port]|=data;
	}else
	{
		m_bOut[drv*8+port]&=~data;
	}
//	DioOutByte(m_hDio[drv],port,m_bOut[drv*8+port]);
}


BYTE CTestProc::DioIn(int drv,int port)
{
	BYTE data=0;
	drv=0;
//	DioInpByte(m_hDio[drv],port,&data);
	return data;
}


void CTestProc::IOClear()
{
 
}


void CTestProc::SetSpecL(int pos)
{
 

}

void CTestProc::SetSpecR(int pos)
{
 
}

void CTestProc::ReadSpec()
{
	 
}

void CTestProc::SaveSpec()
{
	//int fh1;
	 

}

void CTestProc::SaveCountL()
{
 
}

void CTestProc::SaveCounrR()
{
 
}

void CTestProc::ReadCounrL()
{
 

}

void CTestProc::ReadCounrR()
{
 
}

void CTestProc::WriteDataR(CString strData)
{
	 

}

void CTestProc::WriteDataL(CString strData)
{
 
}



void CTestProc::SaveCoordinate()
{
	 
 
}

void CTestProc::ReadPrintCoordinate()
{
	 
}

void CTestProc::Loadini(TCHAR * filename)
{

	TCHAR buf[128] = { NULL, };

  
	GetPrivateProfileString(_T("COM"), _T("ScanPort"), _T("3"), buf, 128, filename);
	m_iComPortBarCode = _ttoi(buf);
/* 
	GetPrivateProfileString(_T("COM"), _T("Load"), _T("2"), buf, 128, filename);
	ComPortLoad = _ttoi(buf);
  
	GetPrivateProfileString(_T("COM"), _T("Servo"), _T("1"), buf, 128, filename);
	ComServo = _ttoi(buf);
*/
	// default password 123
	GetPrivateProfileString("PASSWORD", "Pass", "1234", buf, 123, filename);
	m_strPassWord = buf;

	GetPrivateProfileString("PASSWORD", "SAVE", "0", buf, 123, filename);
 	m_iSaveData = _ttoi(buf);
 
	GetPrivateProfileString("PASSWORD", "MasterP", "0", buf, 123, filename);
	m_iMasterPass = _ttoi(buf);

	GetPrivateProfileString("PASSWORD", "MasterP", "0", buf, 123, filename);
	m_iMasterPass = _ttoi(buf);

	GetPrivateProfileString("PASSWORD", "MasterP", "0", buf, 123, filename);
	m_iMasterPass = _ttoi(buf);

	GetPrivateProfileString("PASSWORD", "GAPLEFT", "30.", buf, 123, filename);
	m_dGap[0] = _ttof(buf);
	
	GetPrivateProfileString("PASSWORD", "GAPRIGHT", "31.", buf, 123, filename);
	m_dGap[1] = _ttof(buf);

 
	GetPrivateProfileString("PASSWORD", "GAPRIGHT", "0", buf, 123, filename);



	GetPrivateProfileString(("TESTCOUNT"), ("MAX"), ("40000"), buf, 128, filename);
	m_iMaxTestCount = _ttoi(buf);

	GetPrivateProfileString(("TESTCOUNT"), ("WARN"), ("39000"), buf, 128, filename);
	m_iWarnTestCount = _ttoi(buf);

	GetPrivateProfileString(_T("MODELNAME"), _T("HKMC"), m_strPartNo[0], buf, 128, filename);
	m_strModel[0] = buf;
	m_strPartNo[0] = buf;

	GetPrivateProfileString(_T("MODELNAME"), _T("MOBASE"), m_strMobse[0], buf, 128, filename);
	m_strMobse[0] = buf;

 
	int pos = 0;
//	int i;
	CString strTemp;
 
	GetPrivateProfileString(("TESTCOUNT"), "CurrentLeft", ("0"), buf, 128, filename);
	m_iCurrTestCount = _ttoi(buf);
	GetPrivateProfileString(("TESTCOUNT"), "CurrentRight", ("0"), buf, 128, filename);
	m_iCurrTestCount2 = _ttoi(buf);
  
}



void CTestProc::Saveini(TCHAR * filename)
{

	TCHAR buf[128] = { NULL, };
	CString str;
	CString strTemp;

	str.Format("%d", m_iCurrTestCount);
	WritePrivateProfileString("TESTCOUNT", "CurrentLeft", str, filename);	// 
	str.Format("%d", m_iCurrTestCount2);
	WritePrivateProfileString("TESTCOUNT", "CurrentRight", str, filename);	// 

	WritePrivateProfileString("MODELNAME", "HKMC", m_strPartNo[0], filename);	// 
	WritePrivateProfileString("MODELNAME", "MOBASE", m_strMobse[0], filename);	// 

	str.Format("%d", m_iMaxTestCount);
  
	WritePrivateProfileString("TESTCOUNT", "MAX",str, filename);	// 

	str.Format("%d", m_iWarnTestCount);
	WritePrivateProfileString("TESTCOUNT", "WARN",str, filename);	// 
 
	WritePrivateProfileString("PASSWORD", "Pass", m_strPassWord, filename);	// 
	str.Format("%d", m_iSaveData);
	WritePrivateProfileString("PASSWORD", "SAVE", str, filename);	// 

}



void CTestProc::WriteLogR(CString strData)
{
	int fh;

	CString temp;
	CString temp2;

	char filename[100];
	char fold[200];
	char fold1[200];
	char timedata[100];
	char worker[100];

	CTime t = CTime::GetCurrentTime();
	if (_chdir("c:\\Data") == -1)
	{
		_chdir("C:\\");
		_mkdir("\\Data");
	}

	sprintf(fold1, "c:\\Data\\Log_DataR");
	if (_chdir(fold1) == -1)
	{
		_chdir("C:\\");
		_mkdir(fold1);
	}

	printf("\nWriteLogR..");
	sprintf(fold1, "c:\\Data\\Log_DataR\\%s", (LPSTR)(LPCSTR)m_strPartNo[0]);

	if (_chdir(fold1) == -1)
	{
		_mkdir(fold1);

	}
	sprintf(fold, "%s\\%04d%02d%02d", fold1, t.GetYear(), t.GetMonth(), t.GetDay());
	if (_chdir(fold) == -1)
	{
		_mkdir(fold);
		m_nSerial[1] =0001;
 	}
	sprintf(timedata, "%02d:%02d:%02d  ", t.GetHour(), t.GetMinute(), t.GetSecond());
	sprintf(filename, "%s\\%04d_%04d.log", fold, this->m_nTestCnt[1], this->m_nGoodCnt[1]);
	if ((fh = _open(filename, _O_RDWR)) != -1)
	{
		_lseek(fh, 0, SEEK_END);
		strData += "\n";
		_write(fh, timedata, 10);
		_write(fh, strData.GetBuffer(1024), strData.GetLength());
		_close(fh);
	}
	else
	{
		if ((fh = _creat(filename, _S_IREAD | _S_IWRITE)) != -1)
		{
			sprintf(worker, "모델 : %s\n", (LPSTR)(LPCSTR)m_strPartNo[0]);
			_write(fh, worker, strlen(worker));
			strData += "\n";
			_write(fh, timedata, 10);
			_write(fh, strData.GetBuffer(1024), strData.GetLength());
			_close(fh);
		}
	}

}




void CTestProc::WriteLogL(CString strData)
{
	int fh;

	CString temp;
	CString temp2;

	char filename[100];
	char fold[200];
	char fold1[200];
	char timedata[100];
	char worker[100];

	CTime t = CTime::GetCurrentTime();
	if (_chdir("c:\\Data") == -1)
	{
		_chdir("C:\\");
		_mkdir("\\Data");
	}
	sprintf(fold1, "c:\\Data\\Log_DataL");
	if (_chdir(fold1) == -1)
	{
		_chdir("C:\\");
		_mkdir(fold1);
//		_mkdir(fold1);

	}

	sprintf(fold1, "c:\\Data\\Log_DataL\\%s", (LPSTR)(LPCSTR)m_strPartNo[0]);

	if (_chdir(fold1) == -1)
	{
		_mkdir(fold1);

	}
	sprintf(fold, "%s\\%04d%02d%02d", fold1, t.GetYear(), t.GetMonth(), t.GetDay());
	if (_chdir(fold) == -1)
	{
		_mkdir(fold);
		m_nSerial[1] = 1;
	}
	sprintf(timedata, "%02d:%02d:%02d  ", t.GetHour(), t.GetMinute(), t.GetSecond());
	sprintf(filename, "%s\\%04d_%04d.log", fold, this->m_nTestCnt[1], this->m_nGoodCnt[1]);
	if ((fh = _open(filename, _O_RDWR)) != -1)
	{
		_lseek(fh, 0, SEEK_END);
		strData += "\n";
		_write(fh, timedata, 10);
		_write(fh, strData.GetBuffer(1024), strData.GetLength());
		_close(fh);
	}
	else
	{
		if ((fh = _creat(filename, _S_IREAD | _S_IWRITE)) != -1)
		{
			sprintf(worker, "모델 : %s\n", (LPSTR)(LPCSTR)m_strPartNo[0]);
			_write(fh, worker, strlen(worker));
			strData += "\n";
			_write(fh, timedata, 10);
			_write(fh, strData.GetBuffer(1024), strData.GetLength());
			_close(fh);
		}
	}
}




void CTestProc::SaveData(int MaxCnt, int CenterCnt, int pos)
{
	CStdioFile spFile;
	CString strTemp;
	static int Number = 0;
//	char fold[200];
//	char filename[1024];
	int p = pos;


	if (m_iSaveData == 0)
		return;
	 

}
 
int CTestProc::ReadData(int* MaxCnt, int* CenterCnt, CString FileName)
{
	int ch = 0;

	CStdioFile spFile;
	CString strTemp1;
	static int Number = 0;
	*MaxCnt = 0;
	//	strTemp(%s\\spec\\%s.TXT",DATAPATH

	char filename[1024];
	sprintf(filename, "%s", (LPSTR)(LPCSTR)FileName);

	strTemp1 = FileName;
	if (!spFile.Open(strTemp1, CFile::shareDenyNone | CFile::modeReadWrite | CFile::typeText))
	{
		AfxMessageBox(strTemp1 + " Not Fount");
		*MaxCnt = -2;
		*CenterCnt = 1;
		Number = 0;
		return -1;
	}
	CString strTemp;

	spFile.SeekToBegin();

	int pos;
	int i = 0;
	int index = 0;
	int st = 0;
	//
	*CenterCnt = 33;
	double dTrqOff = 1.;
	int p = 0;
	printf("\n==================================");
	if (spFile.ReadString(strTemp))
	{

		strTemp1.Format("%s,2,3,4,", strTemp);
		strTemp = strTemp1;
		pos = strTemp.Find(',');
		if (pos > 0)
		{
			strTemp1 = strTemp.Left(pos);
			p = atoi(strTemp1);
			strTemp.Delete(0, pos + 1);
			if (p > 3)
				p = 0;
			else if (p < 0)
				p = 0;
			ch = p;
		}

		printf("\npos=%d     Position %d ",pos, ch);

			//	Test.ValueClear();
		i = 0;
		while (spFile.ReadString(strTemp))
		{
			//if(strTemp.IsEmpty()) break;
			strTemp1.Format("%s,2,3,4,", strTemp);
			strTemp = strTemp1;
			//			printf("\n%3d [%s]",i,strTemp1);

			if (i > MAX_DATA) break;
			pos = strTemp.Find(',');


			if (pos >= 0)
			{
				strTemp1 = strTemp.Left(pos);
				index = atoi(strTemp1);
				strTemp.Delete(0, pos + 1);
				//			printf(" index = %d ",index);
			}
			else
				strTemp1 = "xxxxxx ";

			if (index > MAX_DATA) break;

			pos = strTemp.Find(',');
			//(strTemp1);


			if (pos >= 0)
			{
				strTemp1 = strTemp.Left(pos);

				//		AfxMessageBox(strTemp1);
				if (i > 0)
				{
					//	st = atoi(strTemp1);
					mpCount[p][index] = atoi(strTemp1);	// index 값이 0 이상인경우..
			// 		Test.mpCount[p][index] = st;	// index 값이 0 이상인경우..
//					printf("\ni=%4d(%04d)[%s][%d]%d", i, index, (LPSTR)(LPCSTR)strTemp1, p, st);//, Test.mpCount[p][index]);
				}
				strTemp.Delete(0, pos + 1);
			}


			pos = strTemp.Find(',');
			if (pos >= 0)
			{
				strTemp1 = strTemp.Left(pos);
				if (i > 0)
				{
					mpTroQue[p][index] = atof(strTemp1) *1.96;// * m_dTrqOffset /dTrqOff;//  100*1.96

				}

				strTemp.Delete(0, pos + 1);
			}

			pos = strTemp.Find(',');
			if (pos > 0)
				strTemp.Delete(0, pos + 1);

			pos = strTemp.Find(',');
			if (pos >= 0)
			{
				strTemp1 = strTemp.Left(pos);
				if (i > 0)
					mpKey[p][index] = atoi(strTemp1);
				strTemp.Delete(0, pos + 1);


				i++;


			}
			else
			{
				pos = strTemp.Find(0x0d);
				if (pos >= 0)
				{
					strTemp1 = strTemp.Left(pos);
					if (i > 0)
						mpKey[p][index] = atoi(strTemp1);
					i++;
				}
				else
				{
					printf("Tail Error %d(pos=%d)\n\r", i, pos);
				}
			}

		}

	}
	else
	{
		printf(" data<%s> read error ", (LPSTR)(LPCSTR)strTemp1);
	}
	*MaxCnt = i;// index 값
//	Test.mpTroQue[0] = Test.mpTroQue[1];
//	Test.mpKey[0] = Test.mpKey[1];
	spFile.Close();

	printf("\nRead data channel=%d count=%d", p, i);

	return ch;
}

