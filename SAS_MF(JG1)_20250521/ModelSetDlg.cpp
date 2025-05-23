// ModelSetDlg.cpp : implementation file
//
/*
#include "stdafx.h"
#include "SASTester.h"
#include "SASTesterDoc.h"
#include "ModelSetDlg.h"
#include "FileNewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

*/




#include "stdafx.h"
#include "SAS_1.h"
#include "ModelSetDlg.h"
#include "FileNew.h"
#include "sas_1dlg.h"

#include "TestProc.h"


extern CTestProc Test;// Doc  



// CModelSetDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CModelSetDlg, CDialog)

 

 
/////////////////////////////////////////////////////////////////////////////
// CModelSetDlg dialog


CModelSetDlg::CModelSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModelSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModelSetDlg)
	m_strCheckVersion = _T("Y");
	m_strConnectDelayTime = _T("10.00");
	m_strCurrentConsumtion = _T("0.00");
	m_strMFSWID = _T("000");
	m_strDelayOffsetTime = _T("0.00");
	m_strDifferAngleOffset = _T("0.00");
	m_strHysteresis = _T("0.00");
	m_strNonlinearity = _T("0.00");
	m_strNonlinearityOffset = _T("0.00");
	m_strTBID = _T("000");
	m_strTorque = _T("0.00");
	m_strTorqueOffset = _T("0.00");
	m_strVCID = _T("000");
	m_strVersionHigh = _T("00");
	m_strVersionLow = _T("00");
	m_strAngleHigh = _T("");
	m_strAngleLow = _T("");
	m_strSpeedByte = _T("");
	m_strVersionHighByte = _T("");
	m_strVersionLowByte = _T("");
	//}}AFX_DATA_INIT
	int i;
	for(i=0;i<8;i++)
	{
		this->m_strIniData[i]="00";
		this->m_strOffsetData[i]="00";
		this->m_strResetData[i]="00";
		this->m_strVerCheckData[i]="00";
	}
	for(i=0;i<7;i++)
	{
		this->m_strOffsetAngle[i] = "0.00";
	}
	this->m_strOffsetSpeed = "0.00";

	for(i=0;i<20;i++)
	{
		this->m_strMesAngleStart[i]="0.00";
		this->m_strMesAngleEnd[i]="0.00";
		this->m_strMesSpeedStart[i]="0.00";
		this->m_strMesSpeedEnd[i]="0.00";
	}
	printf("\nCModelSelDlg() 생성 완료!!-------->");

}


CModelSetDlg::~CModelSetDlg()
{
}

 
void CModelSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModelSetDlg)
	DDX_Control(pDX, IDC_LIST1, m_List);
 
	DDX_Text(pDX, IDC_EPS_ID_EDIT, m_strMFSWID);			// MFSW ID
	DDX_Text(pDX, IDC_DELAY_OFFSET_EDIT, m_strDelayOffsetTime);
	DDX_Text(pDX, IDC_CON_DELAY_EDIT, m_strConnectDelayTime);

	DDX_Text(pDX, IDC_DIFFER_ANGLE_OFFSET_EDIT, m_strDifferAngleOffset);
	DDX_Text(pDX, IDC_HYSTERESIS_EDIT, m_strHysteresis);
	DDX_Text(pDX, IDC_NONLINEARITY_EDIT, m_strNonlinearity);
	DDX_Text(pDX, IDC_NONLINEARITY_OFFSET_EDIT, m_strNonlinearityOffset);
	DDX_Text(pDX, IDC_TB_ID_EDIT, m_strTBID);		// SAS ID
//	DDX_Text(pDX, IDC_TORQUE_EDIT, m_strTorque);
//	DDX_Text(pDX, IDC_TORQUE_OFFSET_EDIT, m_strTorqueOffset);
//	DDX_Text(pDX, IDC_VC_ID_EDIT, m_strVCID);
//	DDX_Text(pDX, IDC_VERSION_HIGH_EDIT, m_strVersionHigh);
//	DDX_Text(pDX, IDC_VERSION_LOW_EDIT, m_strVersionLow);
 
	DDX_CBString(pDX, IDC_ANGLE_HIGH_COMBO1, m_strAngleHigh);
 	DDX_CBString(pDX, IDC_ANGLE_LOW_COMBO2, m_strAngleLow);
	DDX_CBString(pDX, IDC_SPEED_COMBO, m_strSpeedByte);
/* 
	DDX_Text(pDX, IDC_RESET_COM_1,m_strResetData[0]);
	DDX_Text(pDX, IDC_RESET_COM_2,m_strResetData[1]);
	DDX_Text(pDX, IDC_RESET_COM_3,m_strResetData[2]);
	DDX_Text(pDX, IDC_RESET_COM_4,m_strResetData[3]);
	DDX_Text(pDX, IDC_RESET_COM_5,m_strResetData[4]);
	DDX_Text(pDX, IDC_RESET_COM_6,m_strResetData[5]);
	DDX_Text(pDX, IDC_RESET_COM_7,m_strResetData[6]);
	DDX_Text(pDX, IDC_RESET_COM_8,m_strResetData[7]);
	DDX_Text(pDX, IDC_INIT_COM_1,m_strIniData[0]);
	DDX_Text(pDX, IDC_INIT_COM_2,m_strIniData[1]);
	DDX_Text(pDX, IDC_INIT_COM_3,m_strIniData[2]);
	DDX_Text(pDX, IDC_INIT_COM_4,m_strIniData[3]);
	DDX_Text(pDX, IDC_INIT_COM_5,m_strIniData[4]);
	DDX_Text(pDX, IDC_INIT_COM_6,m_strIniData[5]);
	DDX_Text(pDX, IDC_INIT_COM_7,m_strIniData[6]);
	DDX_Text(pDX, IDC_INIT_COM_8,m_strIniData[7]);	
	DDX_Text(pDX, IDC_OFFSET_COM_1,m_strOffsetData[0]);
	DDX_Text(pDX, IDC_OFFSET_COM_2,m_strOffsetData[1]);
	DDX_Text(pDX, IDC_OFFSET_COM_3,m_strOffsetData[2]);
	DDX_Text(pDX, IDC_OFFSET_COM_4,m_strOffsetData[3]);
	DDX_Text(pDX, IDC_OFFSET_COM_5,m_strOffsetData[4]);
	DDX_Text(pDX, IDC_OFFSET_COM_6,m_strOffsetData[5]);
	DDX_Text(pDX, IDC_OFFSET_COM_7,m_strOffsetData[6]);
	DDX_Text(pDX, IDC_OFFSET_COM_8,m_strOffsetData[7]);
*/
 /* 
	DDX_Text(pDX, IDC_VERSION_COM_1,m_strVerCheckData[0]);
	DDX_Text(pDX, IDC_VERSION_COM_2,m_strVerCheckData[1]);
	DDX_Text(pDX, IDC_VERSION_COM_3,m_strVerCheckData[2]);
	DDX_Text(pDX, IDC_VERSION_COM_4,m_strVerCheckData[3]);
	DDX_Text(pDX, IDC_VERSION_COM_5,m_strVerCheckData[4]);
	DDX_Text(pDX, IDC_VERSION_COM_6,m_strVerCheckData[5]);
	DDX_Text(pDX, IDC_VERSION_COM_7,m_strVerCheckData[6]);
	DDX_Text(pDX, IDC_VERSION_COM_8,m_strVerCheckData[7]);
 */
	DDX_Text(pDX, IDC_OFFSET_POSITION_1,m_strOffsetAngle[0]);
	DDX_Text(pDX, IDC_OFFSET_POSITION_2,m_strOffsetAngle[1]);
	DDX_Text(pDX, IDC_OFFSET_POSITION_3,m_strOffsetAngle[2]);
	DDX_Text(pDX, IDC_OFFSET_POSITION_4,m_strOffsetAngle[3]);
	DDX_Text(pDX, IDC_OFFSET_POSITION_5,m_strOffsetAngle[4]);
	DDX_Text(pDX, IDC_OFFSET_POSITION_6,m_strOffsetAngle[5]);
	DDX_Text(pDX, IDC_OFFSET_POSITION_7,m_strOffsetAngle[6]);

	DDX_Text(pDX, IDC_MES_POS_ANGLE_1,m_strMesAngleStart[0]);
	DDX_Text(pDX, IDC_MES_POS_ANGLE_2,m_strMesAngleStart[1]);
	DDX_Text(pDX, IDC_MES_POS_ANGLE_3,m_strMesAngleStart[2]);
	DDX_Text(pDX, IDC_MES_POS_ANGLE_4, m_strMesAngleStart[3]);
	DDX_Text(pDX, IDC_MES_POS_ANGLE_5, m_strMesAngleStart[4]);
	DDX_Text(pDX, IDC_MES_POS_ANGLE_6, m_strMesAngleStart[5]);
	DDX_Text(pDX, IDC_MES_POS_ANGLE_7, m_strMesAngleStart[6]);

	DDX_Text(pDX, IDC_MES_POS_ANGLE_END_1,m_strMesAngleEnd[0]);
	DDX_Text(pDX, IDC_MES_POS_ANGLE_END_2,m_strMesAngleEnd[1]);
	DDX_Text(pDX, IDC_MES_POS_ANGLE_END_3,m_strMesAngleEnd[2]);
	DDX_Text(pDX, IDC_MES_POS_ANGLE_END_4,m_strMesAngleEnd[3]);
	DDX_Text(pDX, IDC_MES_POS_ANGLE_END_5,m_strMesAngleEnd[4]);
	DDX_Text(pDX, IDC_MES_POS_SPEED_1,m_strMesSpeedStart[0]);
	DDX_Text(pDX, IDC_MES_POS_SPEED_2,m_strMesSpeedStart[1]);
	DDX_Text(pDX, IDC_MES_POS_SPEED_3,m_strMesSpeedStart[2]);
	DDX_Text(pDX, IDC_MES_POS_SPEED_4, m_strMesSpeedStart[3]);
	DDX_Text(pDX, IDC_MES_POS_SPEED_5, m_strMesSpeedStart[4]);
	DDX_Text(pDX, IDC_MES_POS_SPEED_6, m_strMesSpeedStart[5]);
	DDX_Text(pDX, IDC_MES_POS_SPEED_7, m_strMesSpeedStart[6]);

	DDX_Text(pDX, IDC_MES_POS_SPEED_END_1,m_strMesSpeedEnd[0]);
	DDX_Text(pDX, IDC_MES_POS_SPEED_END_2,m_strMesSpeedEnd[1]);
	DDX_Text(pDX, IDC_MES_POS_SPEED_END_3,m_strMesSpeedEnd[2]);
	DDX_Text(pDX, IDC_MES_POS_SPEED_END_4, m_strMesSpeedEnd[3]);
	DDX_Text(pDX, IDC_MES_POS_SPEED_END_5, m_strMesSpeedEnd[4]);
 
	DDX_Text(pDX, IDC_OFFSET_POSITION_SPEED_1,m_strOffsetSpeed);
 
//}}AFX_DATA_MAP
	
}




// CModelSetDlg 메시지 처리기입니다.


BEGIN_MESSAGE_MAP(CModelSetDlg, CDialog)
	//{{AFX_MSG_MAP(CModelSetDlg)
	ON_BN_CLICKED(IDC_NEW_BUT, OnNewBut)
	ON_BN_CLICKED(IDC_SAVE_BUT, OnSaveBut)
	ON_BN_CLICKED(IDC_DELETE_BUT, OnDeleteBut)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SET_BTN, &CModelSetDlg::OnBnClickedSetBtn)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModelSetDlg message handlers

void CModelSetDlg::OnNewBut() 
{
 
	CFileNew *pDlg = new CFileNew;
	CString str;	
	if(pDlg->DoModal()==IDOK)
	{
 		pMDlg->m_strModelFileName = pDlg->m_strFileName+".SAS";
		str=pDlg->m_strFileName+".SAS";
		m_List.SetCurSel(m_List.AddString(pMDlg->m_strModelFileName));
	}
	OnSaveBut();	// 자동으로 만들기
	
}

void CModelSetDlg::OnSaveBut() 
{


//	CSAS_1Dlg *pDoc=(CSAS_1Dlg*) AfxGetApp()->GetMainWnd();
	int i= m_List.GetCurSel();
	if(i<0)
	{
		AfxMessageBox("저장할 spec 을 선택해 주세요.");
		return;
	}


///////
	m_List.GetText(m_List.GetCurSel(),pMDlg->m_strModelFileName);

  
	GetValue();
	pMDlg->SaveModel(pMDlg->m_strModelFileName);
//	UpdateData(FALSE);

}


void CModelSetDlg::GetValue()
{
	int i;
	UpdateData(TRUE);	// default true  control to value
	pMDlg->m_Model.dwMFSWID = HexaStringConvert(this->m_strMFSWID);
	pMDlg->m_Model.dwTBID = HexaStringConvert(this->m_strTBID);
	pMDlg->m_Model.dwVCID = ::HexaStringConvert(this->m_strVCID);
	pMDlg->m_Model.iAngleHighByte = atoi(m_strAngleHigh);
	pMDlg->m_Model.iAngleLowByte = atoi(m_strAngleLow);
	pMDlg->m_Model.iSpeedByte = atoi(m_strSpeedByte);
	pMDlg->m_Model.iVersionHighByte = atoi(m_strVersionHighByte);
	pMDlg->m_Model.iVersionLowByte = atoi(m_strVersionLowByte);

/* 	if (this->m_strCheckVersion == "Y")
		pMDlg->m_Model.fVerCheck = TRUE;
	else
		pMDlg->m_Model.fVerCheck = FALSE;
*/
	for(i=0;i<8;i++)
	{
		pMDlg->m_Model.bReset[i]=(BYTE)HexaStringConvert(this->m_strResetData[i]);
		pMDlg->m_Model.bInit[i]=(BYTE)HexaStringConvert(this->m_strIniData[i]);
		pMDlg->m_Model.bOffset[i]=(BYTE)HexaStringConvert(this->m_strOffsetData[i]);
		pMDlg->m_Model.bVer[i]=(BYTE)HexaStringConvert(this->m_strVerCheckData[i]);
	}
	pMDlg->m_Model.dCurrentConsumtion = atof(this->m_strCurrentConsumtion);
	pMDlg->m_Model.dConnectDelayTime = atof(this->m_strConnectDelayTime);
	pMDlg->m_Model.dNonlinearity = atof(this->m_strNonlinearity);
	pMDlg->m_Model.dTorque = atof(this->m_strTorque);
	pMDlg->m_Model.dHysteress = atof(this->m_strHysteresis);
	pMDlg->m_Model.bVerS[0]=(BYTE)HexaStringConvert(this->m_strVersionHigh);
	pMDlg->m_Model.bVerS[1]=(BYTE)HexaStringConvert(this->m_strVersionLow);
	pMDlg->m_Model.dOffConnectDelay = atof(this->m_strDelayOffsetTime);
	pMDlg->m_Model.dOffNonlinearity = atof(this->m_strNonlinearityOffset);
//	pMDlg->m_Model.dOffTorque = atof(this->m_strTorqueOffset);
	pMDlg->m_Model.dOffDifferAngle = atof(this->m_strDifferAngleOffset);

	for(i=0;i<7;i++)
	{
		pMDlg->m_Model.dOffsetAngle[i]=atof(this->m_strOffsetAngle[i]);
	}
	pMDlg->m_Model.dOffsetSpeed = atof(this->m_strOffsetSpeed);

	for(i=0;i<7;i++)		// 5 -> 7
	{
		pMDlg->m_Model.dMesAngleStart[i] = atof(this->m_strMesAngleStart[i]);
		pMDlg->m_Model.dMesAngleEnd[i] = atof(this->m_strMesAngleEnd[i]);
		pMDlg->m_Model.dMesSpeedStart[i]= atof(this->m_strMesSpeedStart[i]);
		pMDlg->m_Model.dMesSpeedEnd[i] = atof(this->m_strMesSpeedEnd[i]);
	}
	
}


void CModelSetDlg::OnDeleteBut() 
{

	int i= m_List.GetCurSel();
 
	if(i<0)
	{
		AfxMessageBox("삭제할 spce 을 선택해 주세요");
		return;
	}
	m_List.GetText(m_List.GetCurSel(),pMDlg->m_strModelFileName);
	pMDlg->DeleteModel(pMDlg->m_strModelFileName);
	m_List.DeleteString(m_List.GetCurSel());
}

 

void CModelSetDlg::ModelValueDisplay(void)
{
	int i;

 
	this->m_strMFSWID.Format("%X",pMDlg->m_Model.dwMFSWID);
	this->m_strTBID.Format("%X",pMDlg->m_Model.dwTBID);
	this->m_strAngleHigh.Format("%d",pMDlg->m_Model.iAngleHighByte);
	this->m_strAngleLow.Format("%d",pMDlg->m_Model.iAngleLowByte);
	this->m_strSpeedByte.Format("%d",pMDlg->m_Model.iSpeedByte);
	this->m_strVCID.Format("%X",pMDlg->m_Model.dwVCID);

	if(pMDlg->m_Model.fVerCheck)
		this->m_strCheckVersion = "Y";
	else
		this->m_strCheckVersion = "N";
 
	this->m_strVersionHighByte.Format("%d",pMDlg->m_Model.iVersionHighByte);
	this->m_strVersionLowByte.Format("%d",pMDlg->m_Model.iVersionLowByte);
	this->m_strNonlinearity.Format("%.2f",pMDlg->m_Model.dNonlinearity);
	for(i=0;i<8;i++)
	{
		this->m_strResetData[i].Format("%02X",pMDlg->m_Model.bReset[i]);
		this->m_strIniData[i].Format("%02X",pMDlg->m_Model.bInit[i]);
		this->m_strOffsetData[i].Format("%02X",pMDlg->m_Model.bOffset[i]);
		this->m_strVerCheckData[i].Format("%02X",pMDlg->m_Model.bVer[i]);
	}
	this->m_strCurrentConsumtion.Format("%.2f",pMDlg->m_Model.dCurrentConsumtion);
	this->m_strConnectDelayTime.Format("%.2f",pMDlg->m_Model.dConnectDelayTime);
	this->m_strTorque.Format("%.2f",pMDlg->m_Model.dTorque);
	this->m_strHysteresis.Format("%.2f",pMDlg->m_Model.dHysteress);
	this->m_strVersionHigh.Format("%02X",pMDlg->m_Model.bVerS[0]);
	this->m_strVersionLow.Format("%02X",pMDlg->m_Model.bVerS[1]);
	this->m_strDelayOffsetTime.Format("%.2f",pMDlg->m_Model.dOffConnectDelay);
	this->m_strNonlinearityOffset.Format("%.2f",pMDlg->m_Model.dOffNonlinearity);
	this->m_strTorqueOffset.Format("%.2f",pMDlg->m_Model.dOffTorque);
	this->m_strDifferAngleOffset.Format("%.2f",pMDlg->m_Model.dOffDifferAngle);
	
	for(i=0;i<7;i++)
	{
		this->m_strOffsetAngle[i].Format("%.2f",pMDlg->m_Model.dOffsetAngle[i]);		
	}
	this->m_strOffsetSpeed.Format("%.2f",pMDlg->m_Model.dOffsetSpeed);


	for(i=0;i<7;i++)		// 5 -> 7
	{
		this->m_strMesAngleStart[i].Format("%.2f",pMDlg->m_Model.dMesAngleStart[i]);
		this->m_strMesAngleEnd[i].Format("%.2f",pMDlg->m_Model.dMesAngleEnd[i]);
		this->m_strMesSpeedStart[i].Format("%.2f",pMDlg->m_Model.dMesSpeedStart[i]);
		this->m_strMesSpeedEnd[i].Format("%.2f",pMDlg->m_Model.dMesSpeedEnd[i]);
	}
 
 
	UpdateData(FALSE);

}


void CModelSetDlg::OnDblclkList1() 
{
 
	CString strData;

	m_List.GetText(m_List.GetCurSel(),strData);

	pMDlg->m_strModelFileName = strData;
	pMDlg->ReadModel(strData);
	ModelValueDisplay();
 


}


BOOL CModelSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetModelDataFile();
	GetDlgItem(IDC_LIST1)->SetFont(&Test.Font4);
	GetDlgItem(IDC_NEW_BUT)->SetFont(&Test.Font3);
	GetDlgItem(IDC_SAVE_BUT)->SetFont(&Test.Font3);
	GetDlgItem(IDC_DELETE_BUT)->SetFont(&Test.Font3);
	GetDlgItem(IDC_SET_BTN)->SetFont(&Test.Font3);

	GetDlgItem(IDC_STATIC1)->SetFont(&Test.Font2);
	GetDlgItem(IDC_STATIC2)->SetFont(&Test.Font2);
	GetDlgItem(IDC_STATIC3)->SetFont(&Test.Font2);
	GetDlgItem(IDC_STATIC4)->SetFont(&Test.Font2);
	GetDlgItem(IDC_STATIC5)->SetFont(&Test.Font2);
	GetDlgItem(IDC_STATIC6)->SetFont(&Test.Font2);
	GetDlgItem(IDC_STATIC7)->SetFont(&Test.Font2);
	GetDlgItem(IDC_STATIC8)->SetFont(&Test.Font2);
	GetDlgItem(IDC_STATIC9)->SetFont(&Test.Font2);

	GetDlgItem(IDC_STATIC10)->SetFont(&Test.Font2);
	GetDlgItem(IDC_STATIC11)->SetFont(&Test.Font2);
	GetDlgItem(IDC_STATIC12)->SetFont(&Test.Font2);
	GetDlgItem(IDC_STATIC13)->SetFont(&Test.Font2);
	GetDlgItem(IDC_STATIC14)->SetFont(&Test.Font2);
	GetDlgItem(IDC_STATIC15)->SetFont(&Test.Font2);
	GetDlgItem(IDC_STATIC16)->SetFont(&Test.Font2);
	GetDlgItem(IDC_STATIC17)->SetFont(&Test.Font2);
	GetDlgItem(IDC_STATIC18)->SetFont(&Test.Font2);
	GetDlgItem(IDC_STATIC19)->SetFont(&Test.Font2);
	GetDlgItem(IDC_STATIC20)->SetFont(&Test.Font2);
	GetDlgItem(IDC_STATIC21)->SetFont(&Test.Font2);

	GetDlgItem(IDC_MES_POS_ANGLE_1)->SetFont(&Test.Font2);
	GetDlgItem(IDC_MES_POS_ANGLE_2)->SetFont(&Test.Font2);
	GetDlgItem(IDC_MES_POS_ANGLE_3)->SetFont(&Test.Font2);
	GetDlgItem(IDC_MES_POS_ANGLE_4)->SetFont(&Test.Font2);
	GetDlgItem(IDC_MES_POS_ANGLE_5)->SetFont(&Test.Font2);
	GetDlgItem(IDC_MES_POS_ANGLE_6)->SetFont(&Test.Font2);
	GetDlgItem(IDC_MES_POS_ANGLE_7)->SetFont(&Test.Font2);

	GetDlgItem(IDC_MES_POS_ANGLE_END_1)->SetFont(&Test.Font2);
	GetDlgItem(IDC_MES_POS_ANGLE_END_2)->SetFont(&Test.Font2);
	GetDlgItem(IDC_MES_POS_ANGLE_END_3)->SetFont(&Test.Font2);
	GetDlgItem(IDC_MES_POS_ANGLE_END_4)->SetFont(&Test.Font2);
	GetDlgItem(IDC_MES_POS_ANGLE_END_5)->SetFont(&Test.Font2);
	GetDlgItem(IDC_MES_POS_SPEED_1)->SetFont(&Test.Font2);
	GetDlgItem(IDC_MES_POS_SPEED_2)->SetFont(&Test.Font2);
	GetDlgItem(IDC_MES_POS_SPEED_3)->SetFont(&Test.Font2);
	GetDlgItem(IDC_MES_POS_SPEED_4)->SetFont(&Test.Font2);
	GetDlgItem(IDC_MES_POS_SPEED_5)->SetFont(&Test.Font2);
	GetDlgItem(IDC_MES_POS_SPEED_6)->SetFont(&Test.Font2);
	GetDlgItem(IDC_MES_POS_SPEED_7)->SetFont(&Test.Font2);

 
	
//	ON_BN_CLICKED(IDC_NEW_BUT, OnNewBut)
//		ON_BN_CLICKED(IDC_SAVE_BUT, OnSaveBut)
//		ON_BN_CLICKED(IDC_DELETE_BUT, OnDeleteBut)
//		ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
		//}}AFX_MSG_MAP
//		ON_BN_CLICKED(IDC_SET_BTN, &CModelSetDlg::OnBnClickedSetBtn)

		





	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CModelSetDlg::GetModelDataFile()
{
	CString strPath;
	strPath="D:\\Data\\*.sas";
	CFileFind fd;
	CString strFile;
	BOOL fCon;
 
	if(fd.FindFile(strPath))
	{
		do
		{
			fCon=fd.FindNextFile();
			strFile=fd.GetFileName();
			m_List.AddString(strFile);
		}while(fCon);
	}
}
// ModelSetDlg.cpp : 구현 파일입니다.
//

BOOL CModelSetDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if(pMsg->message == WM_KEYDOWN)
	{
//		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		if(pMsg->wParam == VK_ESCAPE)
			return TRUE;
		if(pMsg->wParam == VK_RETURN )
		{
					// 이곳에 사용될 함수나 처리 구문을 작성하면됨
	 		return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void CModelSetDlg::OnBnClickedSetBtn()
{

	int i= m_List.GetCurSel();
	if(i<0)
	{
		AfxMessageBox("적용할 spec 을 선택해 주세요.");
 		return;
	}
//
	GetValue();

	pMDlg->m_SelModel = pMDlg->m_Model;	// 현재 설정값을 적용한다.
	pMDlg->p_mSasAuTest->SetValueDisplay();
 
}

