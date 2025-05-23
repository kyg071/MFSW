// SASAutoTest.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SAS_1.h"
#include "SASAutoTest.h"
#include "math.h"
// 250  560  높이 310 155 center
//#define MAX_Y_DEG  100		// 최대 y 축 Error 값
//#define MIN_Y_DEG -100		// center 값이 
#define MAX_Y_DEG  155		// 최대 y 축 Error 값
#define MIN_Y_DEG -155		// center 값이  unit 값 1.55*100(10도)

// CSASAutoTest 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSASAutoTest, CDialog)




//CSAS_1Dlg *pMDlg;


CSASAutoTest::CSASAutoTest(CWnd* pParent /*=NULL*/)
	: CDialog(CSASAutoTest::IDD, pParent)
 	, m_strTXID(_T("7C0"))
	, m_iDLC(8)
	, m_iDifferScale(DEF_SCALE)
	, m_fCurrentCheck(FALSE)
	, m_fButZeroMove(FALSE)
{
	m_fOffsetSkip = FALSE;
	m_fScroll = TRUE;


//	pMDlg=(CSAS_1Dlg *)AfxGetApp()->GetMainWnd();

	int i;
	int y=10;	//10
	int x=5;	//10
	for(i=0;i<7;i++)
		m_strMInfoD[i] = "";
	printf("\nCSASAutoTest() 생성 !!-------->");


	m_reMInfoBox = CRect(x,y,260,230);
	m_reMInfoTitle = CRect(m_reMInfoBox.left+5,m_reMInfoBox.top+5,m_reMInfoBox.right-5,m_reMInfoBox.top+30);
	for(i=0;i<8;i++)
	{
		m_reMInfoT[i]= CRect(m_reMInfoBox.left+10,m_reMInfoBox.top+35+i*22,m_reMInfoBox.left+180,m_reMInfoBox.top+55+i*22);
		m_reMInfoD[i]= CRect(m_reMInfoBox.left+185,m_reMInfoBox.top+35+i*22,m_reMInfoBox.right-10,m_reMInfoBox.top+55+i*22);
	}
	m_reMesInfoBox = CRect(x,240,260,416);
	m_reMesInfoTitle = CRect(m_reMesInfoBox.left+5,m_reMesInfoBox.top+5,m_reMesInfoBox.right-5,m_reMesInfoBox.top+30);
	for(i=0;i<6;i++)
	{
		m_reMesInfoT[i]= CRect(m_reMesInfoBox.left+10,m_reMesInfoBox.top+35+i*22,m_reMesInfoBox.left+180,m_reMesInfoBox.top+55+i*22);
		m_reMesInfoD[i]= CRect(m_reMesInfoBox.left+185,m_reMesInfoBox.top+35+i*22,m_reMesInfoBox.right-10,m_reMesInfoBox.top+55+i*22);
	}
	m_reResultBox = CRect(x,426,260,602);
	m_reResultTitle = CRect(m_reResultBox.left+5,m_reResultBox.top+5,m_reResultBox.right-5,m_reResultBox.top+30);
	for(i=0;i<6;i++)
	{
		m_reResultT[i]= CRect(m_reResultBox.left+10,m_reResultBox.top+35+i*22,m_reResultBox.left+180,m_reResultBox.top+55+i*22);
		m_reResultD[i]= CRect(m_reResultBox.left+185,m_reResultBox.top+35+i*22,m_reResultBox.right-10,m_reResultBox.top+55+i*22);
	}
/////
	m_rePosInfoBox = CRect(270,y,614,230);
	m_rePosInfoTitle = CRect(m_rePosInfoBox.left+5,m_rePosInfoBox.top+5,m_rePosInfoBox.right-5,m_rePosInfoBox.top+30);

	for(i=0;i<7;i++)
	{
		m_rePosInfoT[i]= CRect(m_rePosInfoBox.left+10,m_rePosInfoBox.top+35+(i+1)*22,m_rePosInfoBox.left+100,m_rePosInfoBox.top+55+(i+1)*22);
	/* 
		m_rePosAS[i]= CRect(m_rePosInfoBox.left+105,m_rePosInfoBox.top+35+(i+1)*22,m_rePosInfoBox.left+180,m_rePosInfoBox.top+55+(i+1)*22);
		m_rePosAE[i]= CRect(m_rePosInfoBox.left+182,m_rePosInfoBox.top+35+(i+1)*22,m_rePosInfoBox.left+257,m_rePosInfoBox.top+55+(i+1)*22);
		m_rePosSP[i]= CRect(m_rePosInfoBox.left+259,m_rePosInfoBox.top+35+(i+1)*22,m_rePosInfoBox.left+334,m_rePosInfoBox.top+55+(i+1)*22);
*/
		m_rePosAS[i] = CRect(m_rePosInfoBox.left + 105, m_rePosInfoBox.top + 35 + (i + 1) * 22, m_rePosInfoBox.left + 220, m_rePosInfoBox.top + 55 + (i + 1) * 22);
		m_rePosAE[i] = CRect(m_rePosInfoBox.left + 182, m_rePosInfoBox.top + 35 + (i + 1) * 22, m_rePosInfoBox.left + 257, m_rePosInfoBox.top + 55 + (i + 1) * 22);
		m_rePosSP[i] = CRect(m_rePosInfoBox.left + 225, m_rePosInfoBox.top + 35 + (i + 1) * 22, m_rePosInfoBox.left + 334, m_rePosInfoBox.top + 55 + (i + 1) * 22);

	}

	for(i=0;i<3;i++)
	{
//		m_rePosPT[i]= CRect(m_rePosInfoBox.left+105+i*77,m_rePosInfoBox.top+35,m_rePosInfoBox.left+180+i*77,m_rePosInfoBox.top+55+2*22);
 		m_rePosPT[i]= CRect(m_rePosInfoBox.left+105+i*77,m_rePosInfoBox.top+35,m_rePosInfoBox.left+180+i*77,m_rePosInfoBox.top+55);

	}
	i = 0;
	m_rePosPT[i] = CRect(m_rePosInfoBox.left + 105 + i * 77, m_rePosInfoBox.top + 35, m_rePosInfoBox.left + 220 + i * 77, m_rePosInfoBox.top + 55);
	i = 2;
	m_rePosPT[i] = CRect(m_rePosInfoBox.left + 225, m_rePosInfoBox.top + 35, m_rePosInfoBox.left + 334, m_rePosInfoBox.top + 55);

	m_rePInfoBox = CRect(624,10,891,230);
	m_rePInfoTitle = CRect(m_rePInfoBox.left+5,m_rePInfoBox.top+5,m_rePInfoBox.right-5,m_rePInfoBox.top+30);
	for(i=0;i<3;i++)
	{
		m_rePInfoT[i]= CRect(m_rePInfoBox.left+10,m_rePInfoBox.top+35+(i+3)*22,m_rePInfoBox.left+100,m_rePInfoBox.top+55+(i+3)*22);
		m_rePToday[i]= CRect(m_rePInfoBox.left+105,m_rePInfoBox.top+35+(i+3)*22,m_rePInfoBox.left+180,m_rePInfoBox.top+55+(i+3)*22);
		m_rePTotal[i]= CRect(m_rePInfoBox.left+182,m_rePInfoBox.top+35+(i+3)*22,m_rePInfoBox.left+257,m_rePInfoBox.top+55+(i+3)*22);
	}
	for(i=0;i<2;i++)
	{
		m_rePPT[i]= CRect(m_rePInfoBox.left+105+i*77,m_rePInfoBox.top+35,m_rePInfoBox.left+180+i*77,m_rePInfoBox.top+55+2*22);
		m_iResetButMode[i]=0;
		m_reResetBut[i]=CRect(m_rePInfoBox.left+105+i*77,m_rePInfoBox.top+35+6*22,m_rePInfoBox.left+180+i*77,m_rePInfoBox.top+55+7*22);
	}
// graph box	
 //	m_reGraphBox = CRect(270,240,1200,600);
 	m_reGraphBox = CRect(270,240,1200,600);	// 전체 영역

//	m_reGraph = CRect(m_reGraphBox.left + 90, m_reGraphBox.top + 10, m_reGraphBox.right - 10, m_reGraphBox.bottom - 30);		// 그래프 영역....
	m_reGraph = CRect(m_reGraphBox.left + 90, m_reGraphBox.top + 10, m_reGraphBox.right - 40, m_reGraphBox.bottom -40);		// 그래프 영역....

//	printf("\nm_reGraphBox= left=%d  top %d right=%d botton %d", m_reGraphBox.left, m_reGraphBox.top, m_reGraphBox.right, m_reGraphBox.bottom);
//	printf("\nm_reGraph= left=%d  top %d right=%d botton %d", m_reGraph.left, m_reGraph.top, m_reGraph.right, m_reGraph.bottom);


	for(i=0;i<4;i++)
	{
		m_reLineColor[i]= CRect(m_reGraphBox.left +10+i*170 ,m_reGraph.bottom +50,m_reGraphBox.left +30+i*170,m_reGraph.bottom +65);
		m_reLineT[i]= CRect(m_reGraphBox.left + 30 + i * 170, m_reGraph.bottom + 40, m_reGraphBox.left + 130 + i * 170, m_reGraph.bottom + 70);
	}


	m_iJudgeMode=3;
	m_reJudgement = CRect(10,612,130,667);
	m_iTestTime = 0;
	m_reTestTime = CRect(140,612,260,667);

//
	m_iReportMode=0;
	y = 100;
	m_reMessageT = CRect(270,602+y,370,637+y);
	m_reMessage = CRect(375,602+y,1200,637+y);

	m_reReport = CRect(375,640+y,1200,670+y);
	m_reReportBut = CRect(270, 640 + y, 370, 670 + y);
	y = 0;


	m_iRunMode=0;
	m_reRunBut = CRect(1210,540,1350,590);
	m_iStopMode=0;
	m_reStopBut = CRect(1210,600,1350,650);
	m_colorL[0] = crCYAN;// CrWHITE;// RGB(255, 0, 0);		// 
	m_colorL[1] = CrGREEN;// RGB(0, 255, 0);
	m_colorL[2] = CrBLUE;// RGB(0, 0, 255);
	m_colorL[3] = CrYELLOW;// RGB(255, 255, 0);


	m_strMInfoT[0]="MFSW ID(Hex)";
	m_strMInfoT[1]="SAS ID(Hex)";
 	m_strMInfoT[2]="Nonlinearity Correction";
 	m_strMInfoT[3]="Hysteresis";
	m_strMInfoT[4]="Connection Delay(ms)";

	m_strMesInfoT[0]="Correction Delay(ms)";
//	m_strMesInfoT[5]="";
	m_strMesInfoT[1]="SAS Speed(˚/sec)";
	m_strMesInfoT[3]="Servo Angle˚";
	m_strMesInfoT[2]="SAS Angle˚";
	m_strMesInfoT[4]="Differ Angle˚";

//	m_strResultT[0]="Current Consumption(mA)";
 	m_strResultT[0]="Correction Delay(ms)";
	m_strResultT[1]="Nonlinearity Correction(˚)";
	m_strResultT[2] = "Hysteresis";
	m_strResultT[5]="";
	m_strResultT[4] = "";// Version(Hex)";
 	m_strReportFile = "D:\\DATA\\DEFAULT.CSV";

	m_fValidData=FALSE;		// 전류읽기

	m_fMesDataSave=FALSE;
	for(i=0;i<8;i++)
	{
		m_strSend[i]="00";
	}

//	for(i=0;i<6;i++)
//		;

	m_strResultD[0]="0.0";
//	m_fCanEnable=TRUE;

//	printf("\nCSASAutoTest::CSASAutoTest()");
	m_ulCurCnt=0;
	m_ulMesMaxCount=200;
//	m_ulBufferCnt=200;		// 아래 에서만 사용
 
 
	iCenterY=300;
	iCenterX = 800;
	dUnit=0.4;
	dXUnit = 10;

	//	dUnit = m_reGraph.Height() / 1800.000;		// 900 총 5 회전.
	dUnit = m_reGraph.Height() / 400.000;	// 최대 값  1800/2 900 도 +- 10도=200,
	dUnit = m_reGraph.Height() / 200.000;	// 최대 값  1800/2 900 도 +- 10도=200,
	m_YStep = 25;	// 50.  
	m_dYRange = m_YStep / 10.;
//	m_YStep = 50;	-> range +- 200/4= ,
//  m_YStep = 25    -> range +- 100/4=25
//m_YRange = m_yStep

	//	dXUnit = m_reGraph.Width() / (double)MAX_DATA;
	dXUnit = m_reGraph.Width() / 16000.;// MAX_DATA; 0.1 도 단위값
	dXUnit1 = dXUnit * 10;	//  소수점 자리 10배 해서 정수로 변환
	m_fDirCW = true;






	iCenterY = m_reGraph.top + m_reGraph.Height() / 2;
	iCenterX = m_reGraph.left + m_reGraph.Width() / 2;


	printf("\n=======**********************=========================================");
	printf("\n ===t= %d b=%d  he=%d", m_reGraph.top, m_reGraph.bottom, m_reGraph.Height());
	printf("\ndUnit= %.1f  ,dXunit=%.1f", dUnit, dXUnit);


	 
}

CSASAutoTest::~CSASAutoTest()
{

}


void CSASAutoTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);



	DDX_Control(pDX, IDC_SCROLL_CHECK, m_butScroll);
	DDX_Control(pDX, IDC_SENDID_EDIT, m_editTXID);
	DDX_Control(pDX, IDC_SENDDLC_EDIT, m_editDLC);
	DDX_Control(pDX, IDC_SEND_BUT, m_butSend);
	DDX_Control(pDX, IDC_SENDDATA8, m_editSend8);
	DDX_Control(pDX, IDC_SENDDATA7, m_editSend7);
	DDX_Control(pDX, IDC_SENDDATA6, m_editSend6);
	DDX_Control(pDX, IDC_SENDDATA5, m_editSend5);
	DDX_Control(pDX, IDC_SENDDATA4, m_editSend4);
	DDX_Control(pDX, IDC_SENDDATA3, m_editSend3);
	DDX_Control(pDX, IDC_SENDDATA2, m_editSend2);
	DDX_Control(pDX, IDC_SENDDATA1, m_editSend1);
	DDX_Control(pDX, IDC_SCALE_EDIT, m_editScale);
	DDX_Control(pDX, IDC_REPORT_BUT, m_butReport);
	DDX_Control(pDX, IDC_LIST_CLEAR_BUT, m_butListClear);
	DDX_Control(pDX, IDC_OFFSET_SKIP_CHECK, m_butOffsetCheck);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Check(pDX, IDC_OFFSET_SKIP_CHECK, m_fOffsetSkip);
	DDX_Text(pDX, IDC_SCALE_EDIT, m_iDifferScale);
	DDX_Text(pDX, IDC_SENDDLC_EDIT, m_iDLC);
	DDX_Text(pDX, IDC_SENDID_EDIT, m_strTXID);
	DDX_Check(pDX, IDC_SCROLL_CHECK, m_fScroll);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_SENDDATA1, m_strSend[0]);
	DDX_Text(pDX, IDC_SENDDATA2, m_strSend[1]);
	DDX_Text(pDX, IDC_SENDDATA3, m_strSend[2]);
	DDX_Text(pDX, IDC_SENDDATA4, m_strSend[3]);
	DDX_Text(pDX, IDC_SENDDATA5, m_strSend[4]);
	DDX_Text(pDX, IDC_SENDDATA6, m_strSend[5]);
	DDX_Text(pDX, IDC_SENDDATA7, m_strSend[6]);
	DDX_Text(pDX, IDC_SENDDATA8, m_strSend[7]);
	//	DDX_Control(pDX, IDC_CURRENT_SKIP_CHECK1, m_butCurrentCheck);
	//	DDX_Check(pDX, IDC_CURRENT_SKIP_CHECK1, m_fCurrentCheck);
	DDX_Control(pDX, IDC_ZERO_CHECK, m_cButZerrMove);
	DDX_Check(pDX, IDC_ZERO_CHECK, m_fButZeroMove);
//	DDX_Control(pDX, IDC_CHARTCTRL, m_ChartCtrl);
}


BEGIN_MESSAGE_MAP(CSASAutoTest, CDialog)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_LIST_CLEAR_BUT, &CSASAutoTest::OnBnClickedListClearBut)
	ON_BN_CLICKED(IDC_SEND_BUT, &CSASAutoTest::OnBnClickedSendBut)
	ON_BN_CLICKED(IDC_REPORT_BUT, &CSASAutoTest::OnBnClickedReportBut)
//	ON_BN_CLICKED(IDC_TODAY_RESET, &CSASAutoTest::OnBnClickedTodayReset)
//	ON_BN_CLICKED(IDC_TOTAL_RESET, &CSASAutoTest::OnBnClickedTotalReset)
ON_WM_TIMER()
END_MESSAGE_MAP()


// CSASAutoTest 메시지 처리기입니다.


 


// iRow 값이 1줄 ,2 줄 표시 한다..
void CSASAutoTest::DrawButton(CDC *pDC, COLORREF bcolor, COLORREF fcolor, CRect rect, CString strTitle1, CString strTitle2,UINT txtAlign,int mode,int iHeight,int iWidth,int iRow)
{

	CBrush br;
	
	CBrush *pOldBr;
	CPen Pen1,Pen2,Pen3,Pen4;
	CPen *pOldPen;
	CFont font;
	CFont *pOldfont;
	COLORREF pOldTextColor,pOldBkColor;

	UINT oldAlign=pDC->GetTextAlign();

	pOldTextColor=pDC->GetTextColor();
	pOldBkColor=pDC->GetBkColor();
	pOldfont = pDC->GetCurrentFont();

	br.CreateSolidBrush(bcolor);
	Pen1.CreatePen(PS_SOLID,1,RGB(255,255,255));
	Pen2.CreatePen(PS_SOLID,1,RGB(228,228,228));
	Pen3.CreatePen(PS_SOLID,1,RGB(192,192,192));
	Pen4.CreatePen(PS_SOLID,1,RGB(96,96,96));
	
	
//	font.CreateFont(iHeight,iWidth,0,0,FW_BOLD,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"HT견고딕");
	font.CreateFont(iHeight,iWidth-1,0,0,FW_BOLD,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"굴림");
	
	
	pOldBr=(CBrush *)pDC->SelectObject(&br);
	
	if((mode%100)==0)
	{
		pDC->Rectangle(rect);
		pOldPen=(CPen *)pDC->SelectObject(&Pen2);
		pDC->MoveTo(rect.left,rect.top);
		pDC->LineTo(rect.right-1,rect.top);
		pDC->MoveTo(rect.left,rect.top);
		pDC->LineTo(rect.left,rect.bottom-1);
		pDC->SelectObject(&Pen1);
		pDC->MoveTo(rect.left+1,rect.top+1);
		pDC->LineTo(rect.right-2,rect.top+1);
		pDC->MoveTo(rect.left+1,rect.top+1);
		pDC->LineTo(rect.left+1,rect.bottom-2);
		pDC->SelectObject(&Pen4);
		pDC->MoveTo(rect.left,rect.bottom-1);
		pDC->LineTo(rect.right,rect.bottom-1);
		pDC->MoveTo(rect.right-1,rect.top);
		pDC->LineTo(rect.right-1,rect.bottom-1);
		pDC->SelectObject(&Pen3);
		pDC->MoveTo(rect.left+1,rect.bottom-2);
		pDC->LineTo(rect.right-1,rect.bottom-2);
		pDC->MoveTo(rect.right-2,rect.top+1);
		pDC->LineTo(rect.right-2,rect.bottom-2);
	}else if((mode%100)==1)
	{
		pDC->Rectangle(rect);
		pOldPen=(CPen *)pDC->SelectObject(&Pen4);
		pDC->MoveTo(rect.left,rect.top);
		pDC->LineTo(rect.right-1,rect.top);
		pDC->MoveTo(rect.left,rect.top);
		pDC->LineTo(rect.left,rect.bottom-1);
		pDC->SelectObject(&Pen3);
		pDC->MoveTo(rect.left+1,rect.top+1);
		pDC->LineTo(rect.right-2,rect.top+1);
		pDC->MoveTo(rect.left+1,rect.top+1);
		pDC->LineTo(rect.left+1,rect.bottom-2);
		pDC->SelectObject(&Pen2);
		pDC->MoveTo(rect.left,rect.bottom-1);
		pDC->LineTo(rect.right,rect.bottom-1);
		pDC->MoveTo(rect.right-1,rect.top);
		pDC->LineTo(rect.right-1,rect.bottom-1);
		
		pDC->SelectObject(&Pen1);
		pDC->MoveTo(rect.left+1,rect.bottom-2);
		pDC->LineTo(rect.right-1,rect.bottom-2);
		pDC->MoveTo(rect.right-2,rect.top+1);
		pDC->LineTo(rect.right-2,rect.bottom-2);
	}else if((mode%100)==2)
	{
		pOldPen=(CPen *)pDC->SelectObject(&Pen3);
		pDC->Rectangle(rect);
	}else if((mode%100)==3)
	{
		pOldPen=(CPen *)pDC->SelectObject(&Pen3);
		pDC->RoundRect(rect,CPoint(5,5));
	}
	
  	else
	{
		pOldPen = (CPen*)pDC->SelectObject(&Pen3);
	//	pDC->RoundRect(rect, CPoint(5, 5));
	}
 

	pDC->SelectObject(&font);
	pDC->SetTextColor(fcolor);
	pDC->SetBkColor(bcolor);
	pDC->SetTextAlign(txtAlign);
	
	switch(txtAlign)
	{
	case TA_LEFT:
		if(iRow==1)
			pDC->TextOut(rect.left+5,rect.top+(rect.Height()-iHeight)/2,strTitle1);
		else if(iRow==2)
		{
			pDC->TextOut(rect.left+5,rect.top+rect.Height()/2-iHeight-2,strTitle1);
			pDC->TextOut(rect.left+5,rect.top+rect.Height()/2+2,strTitle2);
		}

		break;
	case TA_CENTER:
		if(iRow==1)
			pDC->TextOut(rect.left+rect.Width()/2,rect.top+(rect.Height()-iHeight)/2,strTitle1);
		else if(iRow==2)
		{
			pDC->TextOut(rect.left+rect.Width()/2,rect.top+rect.Height()/2-iHeight-2,strTitle1);
			pDC->TextOut(rect.left+rect.Width()/2,rect.top+rect.Height()/2+2,strTitle2);
		}
		break;
	case TA_RIGHT:
		if(iRow==1)
			pDC->TextOut(rect.right-5,rect.top+(rect.Height()-iHeight)/2,strTitle1);
		else if(iRow==2)
		{
			pDC->TextOut(rect.right-5,rect.top+rect.Height()/2-iHeight-2,strTitle1);
			pDC->TextOut(rect.right-5,rect.top+rect.Height()/2+2,strTitle1);
		}
		break;
	}
	
	
	pDC->SelectObject(pOldfont);
	pDC->SetTextAlign(oldAlign);	
	pDC->SetBkColor(pOldBkColor);                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
	pDC->SetTextColor(pOldTextColor);
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBr);
	br.DeleteObject();
	Pen1.DeleteObject();
	Pen2.DeleteObject();
	Pen3.DeleteObject();
	Pen4.DeleteObject();
	font.DeleteObject();

}




void CSASAutoTest::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
	static int j;
 //	printf("\nCSASAutoTest::OnPaint()%d",j++);

	unsigned int i;
	CString strTemp;
	
	COLORREF bkColor = dc.GetBkColor();
/* 
	dc.TextOut(910,220,"dlc");
	dc.TextOut(910,190,"Data");
	dc.TextOut(1000,220,"Tx ID");
*/
	DrawButton(&dc, RGB(192,192,192),RGB(0,0,0), m_reMInfoBox, "", "",TA_CENTER,0,16,8,1);
	DrawButton(&dc, RGB(192,192,192),RGB(0,0,255),m_reMInfoTitle,"Model 정보","",TA_CENTER,2,24,10,1);
	for(i=0;i<5;i++)
	{
		DrawButton(&dc, RGB(255,255,255),RGB(0,0,0), m_reMInfoT[i], m_strMInfoT[i], "",TA_LEFT,2,12,6,1);
		DrawButton(&dc, RGB(192,255,192),RGB(0,0,0), m_reMInfoD[i], m_strMInfoD[i], "",TA_LEFT,2,12,6,1);
	}
	
	DrawButton(&dc, RGB(192,192,192),RGB(0,0,0), m_reMesInfoBox, "", "",TA_CENTER,0,16,8,1);
	DrawButton(&dc, RGB(192,192,192),RGB(0,0,255),m_reMesInfoTitle,"Measurement 정보","",TA_CENTER,2,24,10,1);
	for(i=0;i<4;i++)
	{
		DrawButton(&dc, RGB(255,255,255),RGB(0,0,0), m_reMesInfoT[i], m_strMesInfoT[i], "",TA_LEFT,2,12,6,1);
	//	DrawButton(&dc, RGB(0,0,0),RGB(0,255,0), m_reMesInfoD[i], m_strMesInfoD[i], "",TA_RIGHT,2,12,6,1);// black Green
		DrawButton(&dc, RGB(192, 255, 192), RGB(0, 0, 0), m_reMesInfoD[i], m_strMesInfoD[i], "", TA_LEFT, 2, 12, 6, 1);
	}


	DrawButton(&dc, RGB(192,192,192),RGB(0,0,0), m_reResultBox, "", "",TA_CENTER,0,16,8,1);

	DrawButton(&dc, RGB(192,192,192),RGB(0,0,255),m_reResultTitle,"측정결과","",TA_CENTER,2,24,10,1);
	for(i=0;i<6;i++)
	{
		DrawButton(&dc, RGB(255,255,255),RGB(0,0,0), m_reResultT[i], m_strResultT[i], "",TA_LEFT,2,12,6,1);
		DrawButton(&dc, RGB(192,255,192),RGB(0,0,0), m_reResultD[i], m_strResultD[i], "",TA_LEFT,2,12,6,1);
	}


	DrawButton(&dc, RGB(192,192,192),RGB(0,0,0), m_rePosInfoBox, "", "",TA_CENTER,0,16,8,1);
	DrawButton(&dc, RGB(192,192,192),RGB(0,0,255),m_rePosInfoTitle,"Position Infomation","",TA_CENTER,2,24,10,1);
	for(i=0;i<7;i++)
	{
		strTemp.Format("Position %d",i+1);
		DrawButton(&dc, RGB(255,255,255),RGB(0,0,0), m_rePosInfoT[i], strTemp, "",TA_LEFT,2,12,6,1);
		DrawButton(&dc, RGB(192,255,192),RGB(0,0,0), m_rePosAS[i], m_strPosAS[i], "",TA_RIGHT,2,12,6,1);
	//	DrawButton(&dc, RGB(192,255,192),RGB(0,0,0), m_rePosAE[i], m_strPosAE[i], "",TA_LEFT,2,12,6,1);
		DrawButton(&dc, RGB(192,255,192),RGB(0,0,0), m_rePosSP[i], m_strPosSP[i], "", TA_RIGHT,2,12,6,1);
	}
/* 	DrawButton(&dc, RGB(255, 255, 255), RGB(0, 0, 0), m_rePosPT[0], "Start", "Angle(˚)", TA_CENTER, 2, 12, 6, 2);
//	DrawButton(&dc, RGB(255,255,255),RGB(0,0,0), m_rePosPT[1], "Stop", "Angle(˚)",TA_CENTER,2,12,6,2);
	DrawButton(&dc, RGB(255,255,255),RGB(0,0,0), m_rePosPT[2], "Move", "Speed(˚/s)",TA_CENTER,2,12,6,2);
*/	
	DrawButton(&dc, RGB(255, 255, 255), RGB(0, 0, 0), m_rePosPT[0], "Angle(˚)","", TA_CENTER, 2, 12, 6, 1);
	DrawButton(&dc, RGB(255, 255, 255), RGB(0, 0, 0), m_rePosPT[2], "Speed(RPM)","", TA_CENTER, 2, 12, 6, 1);

/* 
	DrawButton(&dc, RGB(192,192,192),RGB(0,0,0), m_rePInfoBox, "", "",TA_CENTER,0,16,8,1);
	DrawButton(&dc, RGB(192, 192, 192), RGB(0, 0, 255), m_rePInfoTitle, "Product Infomation", "", TA_CENTER, 2, 24, 10, 1);
	
	for(i=0;i<3;i++)
	{
		switch(i)
		{
		case 0: 
			strTemp.Format("OK Count");
			break;
		case 1:
			strTemp.Format("NG Count");
			break;
		case 2:
			strTemp.Format("Total Count");
			break;
		default:
			break;
		}
		DrawButton(&dc, RGB(255,255,255),RGB(0,0,0), m_rePInfoT[i], strTemp, "",TA_LEFT,2,12,6,1);
		DrawButton(&dc, RGB(192,255,192),RGB(0,0,0), m_rePToday[i], m_strPToday[i], "",TA_RIGHT,2,12,6,1);
		DrawButton(&dc, RGB(192,255,192),RGB(0,0,0), m_rePTotal[i], m_strPTotal[i], "",TA_RIGHT,2,12,6,1);		
	}
	DrawButton(&dc, RGB(255,255,255),RGB(0,0,0), m_rePPT[0], "Today", "Count",TA_CENTER,2,12,6,2);
	DrawButton(&dc, RGB(255,255,255),RGB(0,0,0), m_rePPT[1], "Total", "Count",TA_CENTER,2,12,6,2);
*/

	DrawButton(&dc, RGB(0,0,32),RGB(0,0,0), m_reGraphBox, "", "",TA_CENTER,0,12,6,2);
	DrawButton(&dc, RGB(0,0,32),RGB(0,0,0), m_reGraph, "", "",TA_CENTER,0,12,6,2);

	for(i=0;i<4;i++)
	{
		DrawButton(&dc, m_colorL[i],m_colorL[i], m_reLineColor[i], "", "",TA_CENTER,1,12,6,1);
	}

	
	DrawButton(&dc, bkColor,RGB(0,0,0), m_reLineT[0], "CW", "",TA_LEFT,6,12,6,1);	// left to right turn CW 값증분한다.
	DrawButton(&dc, bkColor,RGB(0,0,0), m_reLineT[1], "CCW", "",TA_LEFT,6,12,6,1);	// Right to left -에서 +값으로  
 	DrawButton(&dc, bkColor,RGB(0,0,0), m_reLineT[2], "Error ", "",TA_LEFT,6,12,6,1);// mode 값이 4 이상이면 안그린다..
//	DrawButton(&dc, bkColor, RGB(0, 0, 0), m_reLineT[3], "SAS Speed", "", TA_LEFT, 2, 12, 6, 1);
/* 	DrawButton(&dc, bkColor, RGB(0, 0, 0), m_reLineT[0], "Servo Angle", "", TA_LEFT, 2, 12, 6, 1);
	DrawButton(&dc, bkColor, RGB(0, 0, 0), m_reLineT[1], "SAS Angle", "", TA_LEFT, 2, 12, 6, 1);
	DrawButton(&dc, bkColor, RGB(0, 0, 0), m_reLineT[2], "Differ Angle", "", TA_LEFT, 2, 12, 6, 1);
	DrawButton(&dc, bkColor, RGB(0, 0, 0), m_reLineT[3], "SAS Speed", "", TA_LEFT, 2, 12, 6, 1);
*/
	dc.TextOut(m_reLineT[2].right + 2, m_reLineT[2].bottom - 15, "X");
//	dc.TextOut(m_reLineT[2].right + 2, m_reLineT[2].bottom - 18, "X");

//	DrawButton(&dc, bkColor,RGB(0,0,0), m_reResetBut[0], "Today", "Reset",TA_CENTER,m_iResetButMode[0],16,8,2);
//	DrawButton(&dc, bkColor,RGB(0,0,0), m_reResetBut[1], "Total", "Reset",TA_CENTER,m_iResetButMode[1],16,8,2);
	
	if(m_iJudgeMode==0)
	{
		DrawButton(&dc, RGB(255,0,0),RGB(255,255,0), m_reJudgement, "NG", "",TA_CENTER,1,24,12,1);
	}else if(m_iJudgeMode==1)
	{
		DrawButton(&dc, RGB(0,0,255),RGB(255,255,0), m_reJudgement, "GOOD", "",TA_CENTER,1,24,12,1);
	}else if(m_iJudgeMode==2)
	{
		DrawButton(&dc, RGB(0,255,0),RGB(0,0,0), m_reJudgement, "RUN", "",TA_CENTER,1,24,12,1);
	}else if(m_iJudgeMode==3)
	{
		DrawButton(&dc, RGB(255,255,0),RGB(0,0,0), m_reJudgement, "READY", "",TA_CENTER,1,24,12,1);
	}
	else
	{
		DrawButton(&dc, RGB(255,255,0),RGB(0,0,0), m_reJudgement, "중지", "",TA_CENTER,1,24,12,1);
	}

	strTemp.Format("%d",m_iTestTime);
	DrawButton(&dc, RGB(0,255,0),RGB(0,0,0), m_reTestTime, strTemp, "",TA_RIGHT,1,24,12,1);
 
	DrawButton(&dc, bkColor,RGB(0,0,0), m_reReportBut, "Report", "",TA_CENTER,m_iReportMode,16,8,1);
	DrawButton(&dc, RGB(0,0,0),RGB(255,255,255), m_reReport, m_strReportFile, "",TA_LEFT,1,16,8,1);


	DrawButton(&dc, RGB(255,255,255),RGB(0,0,0), m_reMessageT, "Message", "",TA_CENTER,2,16,8,1);
	DrawButton(&dc, RGB(0,0,0),RGB(255,255,255), m_reMessage, m_strMessage, "",TA_LEFT,1,16,8,1);

 //	if(theApp.m_Connect)		// 선언에서 한번만 사용 한다...
	{
 		DrawButton(&dc, RGB(0,0,192),RGB(255,255,255), m_reRunBut, "RUN", "",TA_CENTER,m_iRunMode,32,16,1);
		DrawButton(&dc, RGB(0,0,192),RGB(255,255,255), m_reStopBut, "STOP", "",TA_CENTER,m_iStopMode,32,16,1);

	}

	 

	CPen penBackLine;
	CPen penLine[4];
	CFont font90,font;
 //
	if (!(pMDlg->m_fValidData))
	{

		font90.CreateFont(12, 6, 900, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "HT견고딕");
		font.CreateFont(12, 6, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "HT견고딕");

		 
		/////////////////////////////////////

		penBackLine.CreatePen(PS_DOT, 1, RGB(64, 64, 212));
		for (i = 0; i < 4; i++)
		{
			penLine[i].CreatePen(PS_SOLID, 1, m_colorL[i]);
		}

		dc.SetBkColor(RGB(0, 0, 32));

		dc.SelectObject(&penBackLine);

		dc.MoveTo(m_reGraph.left, iCenterY);
		dc.LineTo(m_reGraph.right, iCenterY);
// +-20 도사이, +- 10  Grid
		for (i = 1; i < 5; i++)
		{
			dc.MoveTo(m_reGraph.left, iCenterY - (int)(dUnit * m_YStep*i));
			dc.LineTo(m_reGraph.right, iCenterY - (int)(dUnit * m_YStep *i));
			dc.MoveTo(m_reGraph.left, iCenterY + (int)(dUnit * m_YStep *i));
			dc.LineTo(m_reGraph.right, iCenterY + (int)(dUnit * m_YStep *i));
		}
/* 
		dUnit = m_reGraph.Height() / 400.000;	// 최대 값  1800/2 900 도
	//	dXUnit = m_reGraph.Width() / (double)MAX_DATA;
		dXUnit = m_reGraph.Width() / 16000.;// MAX_DATA; 0.1 도 단위값
*/

//		dXUnit = m_reGraph.Width() / MAX_DATA;
// 100 도 간격으로 -800 ~ +800
		for(i=1;i<16;i++)//1// 10 초 16 개  1개=10ms 500 개 = 5000ms=5sec   50 단위 눈금=32 100 도 단위 16
		{ 
			dc.MoveTo(m_reGraph.left+(int)( dXUnit*i* 1000), m_reGraph.top);	// 100 도 1000 , 50도 500
			dc.LineTo(m_reGraph.left+ (int)(dXUnit * i*1000), m_reGraph.bottom);
 		}


/* 
		dc.MoveTo(m_reGraph.left, iCenterY - (int)(dUnit * 780));
		dc.LineTo(m_reGraph.right, iCenterY - (int)(dUnit * 780));

		dc.MoveTo(m_reGraph.left, iCenterY + (int)(dUnit * 780));
		dc.LineTo(m_reGraph.right, iCenterY + (int)(dUnit * 780));
*/

		dc.SelectObject(&font90);
//		dc.SetTextColor(RGB(64, 64, 212));
		dc.SetTextColor(RGB(212, 212, 212));

		dc.SetTextAlign(TA_CENTER);
//		dc.TextOut(m_reGraph.left - 30, iCenterY, "Angle(˚)");
		dc.TextOut(m_reGraph.left - 30, iCenterY, "Error(˚)");	// +- 5 표시 한다.

		dc.SelectObject(&font);
		//	dc.TextOut(m_reGraph.left + m_reGraph.Width() / 2, m_reGraph.bottom + 4, "Time(ms)");
	 	dc.TextOut(m_reGraph.left + m_reGraph.Width() / 2, m_reGraph.bottom + 15, "Encoder(˚)");	//  
		CString strTemp;

//		x 눈금
		for (i = 1; i < 16; i++)//1// 10 초 16 개  1개=10ms 500 개 = 5000ms=5sec   50 단위 눈금=32 100 도 단위 16
		{
			dc.MoveTo(m_reGraph.left + dXUnit * i * 1000, m_reGraph.top);	// 100 도 1000 , 50도 500
			dc.LineTo(m_reGraph.left + dXUnit * i * 1000, m_reGraph.bottom);
		}

 		for (i = 1; i < 9; i++)
		{
			strTemp.Format("-%3d", 100 * i);
			dc.TextOut(iCenterX - (int)(dXUnit * i * 1000), m_reGraph.bottom + 4, strTemp);
			strTemp.Format("%3d", 100 * i);
			dc.TextOut(iCenterX + (int)(dXUnit * i * 1000), m_reGraph.bottom + 4, strTemp);
	//		printf("\n=%d %d", i, iCenterX + (int)(dXUnit * i * 1000));
		}

		dc.TextOut(iCenterX, m_reGraph.bottom + 4, "0");



		dc.SetTextAlign(TA_RIGHT);
// 
//	dUnit = m_reGraph.Height() / 200.000;	// 최대 값  1800/2 900 도 +- 10도=200,
//	m_YStep = 50;	-> range +- 200/4= ,
//  m_YStep = 25    -> range +- 100/4=25
//m_YRange = m_yStep
		for (i = 1; i < 5; i++ )
		{
			strTemp.Format("-%3.1f", m_dYRange * i);
			dc.TextOut(m_reGraph.left - 4, iCenterY + (int)(dUnit * m_YStep *i) - 6, strTemp);
			strTemp.Format("%3.1f", m_dYRange * i);
			dc.TextOut(m_reGraph.left - 4, iCenterY - (int)(dUnit * m_YStep *i) - 6, strTemp);
		}

		dc.TextOut(m_reGraph.left - 4, iCenterY - 0, "0");





//		dc.TextOut(m_reGraph.left - 4, iCenterY + (int)(dUnit * 780) - 6, "-780");
//		dc.TextOut(m_reGraph.left - 4, iCenterY - (int)(dUnit * 780) - 6, "780");

		dc.SelectObject(&penLine[0]);
		// servor 
		int y,x;

		////////////////////////////////////////////////////////////////////

		//

		//if(!(pMDlg->m_fValidData))
		//{
		x = iCenterX+(int)(dXUnit1 * pMDlg->m_pdServoAngle[1]);	// before
		y = (int)(dUnit * pMDlg->m_pdDifferAngle[i] * 10);// m_iDifferScale);

		if (y > MAX_Y_DEG) y = MAX_Y_DEG;
		else if (y < MIN_Y_DEG) y = MIN_Y_DEG;
		
		dc.MoveTo(x, iCenterY-y);		// 처음값으로 하고 아래는 2번 부터 

	//	dc.MoveTo(m_reGraph.left, iCenterY);		// 처음값으로 하고 아래는 2번 부터 
		//  redraw
 
		dc.SelectObject(&penLine[0]);		// CW 각도 +
		for (i = 2; i < m_ulCurCnt; i++)
		{

			y = (int)(dUnit * pMDlg->m_pdDifferAngle[i] * 10);// m_iDifferScale);

			if (y > MAX_Y_DEG) y = MAX_Y_DEG;
			else if (y < MIN_Y_DEG) y = MIN_Y_DEG;
			//
	//		x = (int)(dXUnit1 * pMDlg->m_pdServoAngle[i]);
			x = (int)(dXUnit1 * pMDlg->m_pdServoAngle[i]);	// before

		//	printf("\npos=%d  x=%d %.2f %.2f", i, x, pMDlg->m_pdServoAngle[i], pMDlg->m_pdDifferAngle[i]);

			x = iCenterX + x;
//			printf("\n=%d %d", i, iCenterX + (int)(dXUnit * i * 1000));
 			dc.LineTo(x , iCenterY - y);
			if (i == pMDlg->m_iCindex)
			{
				dc.SelectObject(&penLine[1]);
				printf("\nReverse Draw m_ulCurCnt=%d  center=%d", m_ulCurCnt, pMDlg->m_iCindex);
			}
//			dc.LineTo(m_reGraph.left + (int)(i * m_reGraph.Width() * 1.000 / m_ulMesMaxCount), iCenterY - y);
// 
// 
//			dc.TextOut(iCenterX + (int)(dXUnit * i * 1000), m_reGraph.bottom + 4, strTemp);

		}
		//
 
/* 
		dc.MoveTo(m_reGraph.left, iCenterY);
//
		for (i = 0; i < m_ulCurCnt; i++)
		{
			y = (int)(dUnit * pMDlg->m_pdSASAngle[i]);
			if (y > MAX_Y_DEG) y = MAX_Y_DEG;
			else if (y < MIN_Y_DEG) y = MIN_Y_DEG;
			dc.LineTo(m_reGraph.left + (int)(i * m_reGraph.Width() * 1.000 / m_ulMesMaxCount),
				iCenterY - y);
		}
 
		dc.SelectObject(&penLine[2]);

		dc.MoveTo(m_reGraph.left, iCenterY);

		for (i = 0; i < m_ulCurCnt; i++)
		{
			y = (int)(dUnit * pMDlg->m_pdDifferAngle[i] * 1);// m_iDifferScale);
			if (y > MAX_Y_DEG) y = MAX_Y_DEG;
			else if (y < MIN_Y_DEG) y = MIN_Y_DEG;

			dc.LineTo(m_reGraph.left + (int)(i * m_reGraph.Width() * 1.000 / m_ulMesMaxCount),
				iCenterY - y);
		}

			dc.SelectObject(&penLine[3]);
		dc.MoveTo(m_reGraph.left, iCenterY);
		//
		for (i = 0; i < m_ulCurCnt; i++)
		{
			y = (int)(dUnit * pMDlg->m_pdSpeed[i]);
			if (y > MAX_Y_DEG) y = MAX_Y_DEG;
			else if (y < MIN_Y_DEG) y = MIN_Y_DEG;

			dc.LineTo(m_reGraph.left + (int)(i * m_reGraph.Width() * 1.000 / m_ulMesMaxCount)
				, iCenterY - y);
		}
	
		*/

		penBackLine.DeleteObject();
		for (i = 0; i < 4; i++)
		{
			penLine[i].DeleteObject();
		}
		 
		font.DeleteObject();
		font90.DeleteObject();

	}
/////////////////////////////////////////

 //	CPaintDC *pDC=&dc;
 
}

BOOL CSASAutoTest::OnInitDialog()
{
	CDialog::OnInitDialog();

 
//	m_List.SetWindowPos(&CWnd::wndTop,901,10,450,170,SWP_SHOWWINDOW);
//	m_List.SetWindowPos(&CWnd::wndTop,901,10,550,170,SWP_SHOWWINDOW);
	m_List.SetWindowPos(&CWnd::wndTop, 650, 10, 550, 170, SWP_SHOWWINDOW);

//	m_butOffsetCheck.SetWindowPos(&CWnd::wndTop, 1210, 482, 120, 20, SWP_HIDEWINDOW);
//	m_butCurrentCheck.SetWindowPos(&CWnd::wndTop,1210,482+20,120,20, SWP_HIDEWINDOW);



#ifdef ZERO_CHECK
	m_cButZerrMove.SetWindowPos(&CWnd::wndTop,1210,482+40,120,20,SWP_SHOWWINDOW);	// 감추기
#else
//	m_cButZerrMove.SetWindowPos(&CWnd::wndTop,1210,482+40,120,20,SWP_HIDEWINDOW);	// 감추기
#endif

	m_cButZerrMove.SetWindowPos(&CWnd::wndTop, 1000, 482 + 140, 100, 20, SWP_SHOWWINDOW);	// 보이기
	m_butOffsetCheck.SetWindowPos(&CWnd::wndTop, 1100, 482+140, 100, 20, SWP_SHOWWINDOW);

	m_butListClear.SetWindowPos(&CWnd::wndTop,1220-120,185,90,40,SWP_SHOWWINDOW);
//	m_butTodayReset.SetWindowPos(&CWnd::wndTop,m_reResetBut[0].left,m_reResetBut[0].top,m_reResetBut[0].Width(),m_reResetBut[0].Height(),SWP_SHOWWINDOW);
//	m_butTotalReset.SetWindowPos(&CWnd::wndTop,m_reResetBut[1].left,m_reResetBut[1].top,m_reResetBut[1].Width(),m_reResetBut[1].Height(),SWP_SHOWWINDOW);
	

	int x = -150;

	m_editSend1.SetWindowPos(&CWnd::wndTop, 940 + x, 190, 25, 20, SWP_HIDEWINDOW);
	m_editSend2.SetWindowPos(&CWnd::wndTop, 970 + x, 190, 25, 20, SWP_HIDEWINDOW);
	m_editSend3.SetWindowPos(&CWnd::wndTop, 1000 + x, 190, 25, 20, SWP_HIDEWINDOW);
	m_editSend4.SetWindowPos(&CWnd::wndTop, 1030 + x, 190, 25, 20, SWP_HIDEWINDOW);
	m_editSend5.SetWindowPos(&CWnd::wndTop, 1060 + x, 190, 25, 20, SWP_HIDEWINDOW);
	m_editSend6.SetWindowPos(&CWnd::wndTop, 1090 + x, 190, 25, 20, SWP_HIDEWINDOW);
	m_editSend7.SetWindowPos(&CWnd::wndTop, 1120 + x, 190, 25, 20, SWP_HIDEWINDOW);
	m_editSend8.SetWindowPos(&CWnd::wndTop, 1150 + x, 190, 25, 20, SWP_HIDEWINDOW);
	m_butSend.SetWindowPos(&CWnd::wndTop, 1120 + x, 215, 55, 20, SWP_HIDEWINDOW);
	m_editDLC.SetWindowPos(&CWnd::wndTop, 940 + x, 215, 40, 20, SWP_HIDEWINDOW);
	m_editTXID.SetWindowPos(&CWnd::wndTop, 1050 + x, 215, 60, 20, SWP_HIDEWINDOW);
	
	m_butReport.SetWindowPos(&CWnd::wndTop, 1050 + x, 215, 60, 20, SWP_HIDEWINDOW);

	m_butScroll.SetWindowPos(&CWnd::wndTop, 1180 + x, 190, 60, 20, SWP_SHOWWINDOW);
	x = -300;
	m_editScale.SetWindowPos(&CWnd::wndTop, 740, 640, 40, 20, SWP_SHOWWINDOW);


	iCenterY = m_reGraph.top+m_reGraph.Height()/2;
	iCenterX = m_reGraph.left + m_reGraph.Width() / 2;



	printf("\n================================================");
	printf("\n ===t= %d b=%d  he=%d",m_reGraph.top	,m_reGraph.bottom, m_reGraph.Height());


	printf("\ndUnit= %.1f  ,dXunit=%.1f", dUnit, dXUnit);
 

//	GraphMake();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSASAutoTest::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString strTemp;
	if(point.x > m_reRunBut.left && point.x < m_reRunBut.right && point.y > m_reRunBut.top && point.y < m_reRunBut.bottom)
	{
		if(m_iRunMode==0)
		{
			pMDlg->m_iRunMode=m_iRunMode=1;
			m_iStopMode=0;
			unsigned int  i;
			m_ulMesMaxCount = pMDlg->m_ulMesMaxCount;	// Buffer 최대 값..

	//		pMDlg->m_clMC.ServoOn(TRUE);

			for(i=0;i< m_ulMesMaxCount;i++)
			{
				pMDlg->m_pdSASAngle[i]=0;
				pMDlg->m_pdServoAngle[i]=0;
				pMDlg->m_pdDifferAngle[i]=0;
				pMDlg->m_pdSpeed[i]=0;
				pMDlg->m_pdTime[i]=0;
			}
			strTemp.Format(" Total Data %d", m_ulMesMaxCount);
			AddString(strTemp);

//
			m_ulCurCnt=0;
	//		pMDlg->m_strCanMessageArray.RemoveAll();

			UpdateData(TRUE);				// control to value
//			
			InvalidateRect(m_reRunBut);
			InvalidateRect(m_reStopBut);
			InvalidateRect(m_reGraph);
//			AxdoNWriteOutportBit(0,0,0,obSASPower);
	//		pMDlg->m_clMC.SASPowerEnable(TRUE);
		}
	}

	else if(point.x > m_reStopBut.left && point.x < m_reStopBut.right && point.y > m_reStopBut.top && point.y < m_reStopBut.bottom)
	{
		if(m_iStopMode==0)
		{
			m_iStopMode=1;
			pMDlg->m_iRunMode=m_iRunMode=0;
//			m_clMC.MoveServoStop();
	//		pMDlg->m_clMC.MoveServoStop();

			InvalidateRect(m_reStopBut);
			InvalidateRect(m_reRunBut);
//			AxdoNWriteOutportBit(0,0,0,obSASPower);
	//		pMDlg->m_clMC.SASPowerEnable(FALSE);
	//		pMDlg->m_clMC.ServoOn(FALSE);
			OutMessage("사용자 중지.");
//
		}
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CSASAutoTest::OutMessage(CString strData)
{
	if(m_strMessage==strData)
		return;
	m_strMessage=strData;
	InvalidateRect(m_reMessage);

}


// 설정치 표시하기 
void CSASAutoTest::SetValueDisplay(void)
{
	unsigned int i;

		m_strMInfoD[0].Format("%X",pMDlg->m_SelModel.dwMFSWID);
		m_strMInfoD[1].Format("%X",pMDlg->m_SelModel.dwTBID);
 		m_strMInfoD[2].Format("± %.2f",pMDlg->m_SelModel.dNonlinearity);
 		m_strMInfoD[3].Format("%.2f",pMDlg->m_SelModel.dHysteress);
		m_strMInfoD[4].Format("%.2f", pMDlg->m_SelModel.dConnectDelayTime);
//		m_strMInfoD[6].Format("%02X,%02X",pMDlg->m_SelModel.bVerS[0],pMDlg->m_SelModel.bVerS[1]);
// 종료 각과 시작각 차이 / 이동속도..

		double dTime=0;//,dTemp;
		int temp=0;
		double t1,pulse;
		for(i=0;i< 6;i++)
		{
			m_strPosAS[i].Format("%.2f",pMDlg->m_SelModel.dMesAngleStart[i]);
			m_strPosAE[i].Format("%.2f",pMDlg->m_SelModel.dMesAngleEnd[i]);
			m_strPosSP[i].Format("%.2f",pMDlg->m_SelModel.dMesSpeedStart[i]);
//
			if(pMDlg->m_SelModel.dMesSpeedStart[i] == 0) break;
//			if(pMDlg->m_SelModel.dMesAngleStart[i] != pMDlg->m_SelModel.dMesAngleEnd[i])
			if (pMDlg->m_SelModel.dMesAngleStart[i] != pMDlg->m_SelModel.dMesAngleStart[i+1])
			{
				pulse = (pMDlg->m_SelModel.dMesSpeedStart[i]) * 1200;//  1 회전 속도 이다...(1초당 출력 펄스값)
//				temp= (int)(abs((int)(pMDlg->m_SelModel.dMesAngleStart[i]-pMDlg->m_SelModel.dMesAngleEnd[i])) / pMDlg->m_SelModel.dMesSpeedStart[i]);
				t1= fabs((pMDlg->m_SelModel.dMesAngleStart[i] - pMDlg->m_SelModel.dMesAngleStart[i+1])*200. / pulse);// 총필요 시간..
 // 				
				t1=t1*100 + 5;		// 10 ms 단위 200 은 여유 갯수.
				printf("\n%d %.1f pulse=%f  %f", i, t1,pulse, fabs((pMDlg->m_SelModel.dMesAngleStart[i] - pMDlg->m_SelModel.dMesAngleStart[i+1])));
				temp= (int)t1;
				dTime +=temp;		
// 속도 계산 방법은 
			}else 
			{
				break;
			}
	//		printf("\n%d %d  %.3f",i,temp,pMDlg->m_SelModel.dMesSpeedStart[i]);
		}


////////////////////
//		printf("\n %d 필요메모리 %.1f -> * 2 = %.1f",i,dTime,dTime *2);
		
//		AfxMessageBox("Can memory Ready");

/////////////////////
//		dTime*=100;		// 10ms 단위로 만든다.
	
	//	int 
			
	//	temp = (int)dTime *2;
 
//		m_ulMesMaxCount = dTime+i*100;			// 200 이상이면 ???


		// 10 ms  단위 1분 60초= 60 * 100 ms   초당 100 *60
		// 1 RPM = 1/60 RPS ,  360 / 60 = 6 초 (1회전)    1도당 = 1000ms/6도= 167ms 필요  1회전 sample 갯수 6초*100=600 [ 초당(1000/10 = 100 개 필요]
			// 6회전 필요 Data Full turn(약6회전)3600개 * 2번 반복 = 7200개면 된다...1 RPS 인경우...

//	 	m_ulMesMaxCount = temp;		//  
/* 
		pMDlg->MakeMemory(temp);
		if( pMDlg->m_pdSASAngle == NULL ||  pMDlg->m_pdServoAngle == NULL ||  pMDlg->m_pdSpeed ==NULL
			||  pMDlg->m_pdDifferAngle == NULL ||  pMDlg->m_pCanData == NULL ||  pMDlg->m_pdTime == NULL)
		{
			AfxMessageBox("메모리 부족 측정 값을 재설정 하세요!");
			return ;
		}
*/

 
 
		m_ulCurCnt=0;
		Invalidate();

		OutMessage(pMDlg->m_strModelFileName + " File Select");
	

}

void CSASAutoTest::AddString(CString strData)
{

		
	CString strTemp;
	CTime t = CTime::GetCurrentTime();

	strTemp.Format("%04d/%02d/%02d %02d:%02d:%02d ",t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
	strTemp += strData;
	if(m_fScroll)
		m_List.SetTopIndex(m_List.AddString(strTemp));
	else
		m_List.AddString(strTemp);

}


void CSASAutoTest::OnBnClickedListClearBut()
{
	 m_List.ResetContent();
}

void CSASAutoTest::OnBnClickedSendBut()
{
	UpdateData(TRUE);
	BYTE send[8];
	DWORD dwID= HexaStringConvert(m_strTXID);
	unsigned int i;
	for(i=0;i<m_iDLC;i++)
	{
		send[i]=HexaStringConvert(m_strSend[i]);
	}
	pMDlg->CanSend(dwID,m_iDLC,send);

}



//  SAS_Dlg 에서 호출 한다..
void CSASAutoTest::DrawGraph(int iPo)
{
#ifdef LINE_X_TIME
	int i;
	if(iPo<2)
		return;
//
	iPo=iPo-1;		// 이미 증분함.

	CDC *pDC = (CDC *)GetDC();
//
//
	CPen penLine[4];

	for(i=0;i<4;i++)
		penLine[i].CreatePen(PS_SOLID,1,m_colorL[i]);

	int y;

	pDC->SelectObject(&penLine[0]);
	y=(int)(dUnit *  pMDlg->m_pdServoAngle[iPo-1]);
//

	if(y > MAX_Y_DEG) y=MAX_Y_DEG;
	else if(y < MIN_Y_DEG) y= MIN_Y_DEG;

	pDC->MoveTo(m_reGraph.left+(int)((iPo-1)*m_reGraph.Width() *1.000 / m_ulMesMaxCount),
		iCenterY-y);
	pDC->LineTo(m_reGraph.left+(int)(iPo*m_reGraph.Width() * 1.000 / m_ulMesMaxCount),
		iCenterY-y);
//	
	pDC->SelectObject(&penLine[1]);

	y=(int)(dUnit *  pMDlg->m_pdSASAngle[iPo-1]);

	if(y> MAX_Y_DEG) y=MAX_Y_DEG;
	else if(y< MIN_Y_DEG) y= MIN_Y_DEG;

	pDC->MoveTo(m_reGraph.left+(int)((iPo-1)*m_reGraph.Width()*1.000/m_ulMesMaxCount),iCenterY-y);

	y=(int)(dUnit *  pMDlg->m_pdSASAngle[iPo]);

	if(y> MAX_Y_DEG) y=MAX_Y_DEG;
	else if(y < MIN_Y_DEG) y=MIN_Y_DEG;
	
	pDC->LineTo(m_reGraph.left+(int)(iPo*m_reGraph.Width()*1.000/m_ulMesMaxCount),iCenterY-y);
//	
	pDC->SelectObject(&penLine[2]);

	y=(int)(dUnit*  pMDlg->m_pdDifferAngle[iPo-1]*m_iDifferScale);
	if(y> MAX_Y_DEG) y=MAX_Y_DEG;
	else if(y<  MIN_Y_DEG) y= MIN_Y_DEG;
	pDC->MoveTo(m_reGraph.left+(int)((iPo-1)*m_reGraph.Width()*1.000/m_ulMesMaxCount),
		iCenterY-y);

	y=(int)(dUnit*  pMDlg->m_pdDifferAngle[iPo]*m_iDifferScale);
	if(y> MAX_Y_DEG) y=MAX_Y_DEG;
	else if(y<  MIN_Y_DEG) y= MIN_Y_DEG;
	pDC->LineTo(m_reGraph.left+(int)(iPo*m_reGraph.Width()*1.000/m_ulMesMaxCount),
		iCenterY-y);
//
	pDC->SelectObject(&penLine[3]);

	y=(int)(dUnit*  pMDlg->m_pdSpeed[iPo-1]);
	if(y> MAX_Y_DEG) y=MAX_Y_DEG;
	else if(y<  MIN_Y_DEG) y= MIN_Y_DEG;

	pDC->MoveTo(m_reGraph.left+(int)((iPo-1)*m_reGraph.Width()*1.000/m_ulMesMaxCount),
		iCenterY-y);
	y=(int)(dUnit*  pMDlg->m_pdSpeed[iPo]);
	if(y> MAX_Y_DEG) y=MAX_Y_DEG;
	else if(y<  MIN_Y_DEG) y= MIN_Y_DEG;

	pDC->LineTo(m_reGraph.left+(int)(iPo*m_reGraph.Width()*1.000/m_ulMesMaxCount),
		iCenterY-y);
	
	for(i=0;i<4;i++)
		penLine[i].DeleteObject();
	ReleaseDC(pDC);
#else

	int i;
	if (iPo < 3)		// 2
		return;
	//
	iPo = iPo - 1;		// 이미 증분함.

	CDC* pDC = (CDC*)GetDC();
	//
	//
	CPen penLine[4];

	for (i = 0; i < 4; i++)
		penLine[i].CreatePen(PS_SOLID, 1, m_colorL[i]);

	int y,y1,x;

	if(m_fDirCW)
		pDC->SelectObject(&penLine[0]);		// CCW,CW 에 따라서 다르게 표현한다..
	else
		pDC->SelectObject(&penLine[1]);		// CCW,CW 에 따라서 다르게 표현한다..


	// (m_reGraph.left, iCenterY);
	// (m_reGraph.right, iCenterY);

//	 printf("\npos=%d   %.2f %.2f ", iPo - 1, pMDlg->m_pdServoAngle[iPo - 1], pMDlg->m_pdDifferAngle[iPo - 1]);
//	 printf("\npos=%d   %.2f %.2f ", iPo - 1, pMDlg->m_pdServoAngle[iPo - 1], pMDlg->m_pdDifferAngle[iPo - 1]);


//	y = (int)(dUnit * (pMDlg->m_pdServoAngle[iPo - 1]- pMDlg->m_pdSASAngle[iPo - 1])*10.);
	y = (int)(dUnit * pMDlg->m_pdDifferAngle[iPo -1] * 10.);

	if (y > MAX_Y_DEG) y = MAX_Y_DEG;
	else if (y < MIN_Y_DEG) y = MIN_Y_DEG;

	x = (int)(dXUnit1 * pMDlg->m_pdServoAngle[iPo - 1]);	// before
//	printf(" new y=%d [x=%d] ",y, x);


	x = iCenterX + x;
	//			printf("\n=%d %d", i, iCenterX + (int)(dXUnit * i * 1000));
//	dc.LineTo(x, iCenterY - y);
 	pDC->MoveTo(x,iCenterY - y);
	x = (int)(dXUnit1 * pMDlg->m_pdServoAngle[iPo]);	// before
	x = iCenterX + x;

//	y = (int)(dUnit * (pMDlg->m_pdServoAngle[iPo] - pMDlg->m_pdSASAngle[iPo]) * 10.);
	y = (int)(dUnit * pMDlg->m_pdDifferAngle[iPo] * 10.);

	if (y > MAX_Y_DEG) y = MAX_Y_DEG;
	else if (y < MIN_Y_DEG) y = MIN_Y_DEG;

//	printf("==>x= %d y=%d", x,y );
	
//	y = dc.MoveTo(m_reGraph.left, iCenterY - (int)(dUnit * m_YStep * i));

 	pDC->LineTo(x,iCenterY -y);
//	printf("iCenterY=%d m_YStep=%d", iCenterY, m_YStep);

//	pDC->MoveTo(m_reGraph.left + (int)((iPo - 1) * m_reGraph.Width() * 1.000 / 16000),iCenterY - y);
//	pDC->LineTo(m_reGraph.left + (int)(iPo * m_reGraph.Width() * 1.000 / 16000),iCenterY - y);

	//	

#ifdef USE_NEXT
	pDC->SelectObject(&penLine[1]);

	y = (int)(dUnit * pMDlg->m_pdSASAngle[iPo - 1]);

	if (y > MAX_Y_DEG) y = MAX_Y_DEG;
	else if (y < MIN_Y_DEG) y = MIN_Y_DEG;

	pDC->MoveTo(m_reGraph.left + (int)((iPo - 1) * m_reGraph.Width() * 1.000 / m_ulMesMaxCount), iCenterY - y);

	y = (int)(dUnit * pMDlg->m_pdSASAngle[iPo]);

	if (y > MAX_Y_DEG) y = MAX_Y_DEG;
	else if (y < MIN_Y_DEG) y = MIN_Y_DEG;

	pDC->LineTo(m_reGraph.left + (int)(iPo * m_reGraph.Width() * 1.000 / m_ulMesMaxCount), iCenterY - y);
	//	
	pDC->SelectObject(&penLine[2]);

	y = (int)(dUnit * pMDlg->m_pdDifferAngle[iPo - 1] * m_iDifferScale);
	if (y > MAX_Y_DEG) y = MAX_Y_DEG;
	else if (y < MIN_Y_DEG) y = MIN_Y_DEG;
	pDC->MoveTo(m_reGraph.left + (int)((iPo - 1) * m_reGraph.Width() * 1.000 / m_ulMesMaxCount),
		iCenterY - y);

	y = (int)(dUnit * pMDlg->m_pdDifferAngle[iPo] * m_iDifferScale);
	if (y > MAX_Y_DEG) y = MAX_Y_DEG;
	else if (y < MIN_Y_DEG) y = MIN_Y_DEG;
	pDC->LineTo(m_reGraph.left + (int)(iPo * m_reGraph.Width() * 1.000 / m_ulMesMaxCount),
		iCenterY - y);
	//

	pDC->SelectObject(&penLine[3]);

	y = (int)(dUnit * pMDlg->m_pdSpeed[iPo - 1]);
	if (y > MAX_Y_DEG) y = MAX_Y_DEG;
	else if (y < MIN_Y_DEG) y = MIN_Y_DEG;

	pDC->MoveTo(m_reGraph.left + (int)((iPo - 1) * m_reGraph.Width() * 1.000 / m_ulMesMaxCount),
		iCenterY - y);
	y = (int)(dUnit * pMDlg->m_pdSpeed[iPo]);
	if (y > MAX_Y_DEG) y = MAX_Y_DEG;
	else if (y < MIN_Y_DEG) y = MIN_Y_DEG;

	pDC->LineTo(m_reGraph.left + (int)(iPo * m_reGraph.Width() * 1.000 / m_ulMesMaxCount),
		iCenterY - y);

#endif

	for (i = 0; i < 4; i++)
		penLine[i].DeleteObject();
	ReleaseDC(pDC);

#endif

}

void CSASAutoTest::OnBnClickedReportBut()
{
	// TODO: Add your control notification handler code here
	CFileDialog pDlg(FALSE,"CSV","*.CSV",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"EXCEL FILE(*.CSV)|*.CSV|*.*|*.*|");
	if(pDlg.DoModal()==IDOK)
	{
		m_strReportFile = pDlg.GetPathName();
		InvalidateRect(m_reReport);
	}	 
}

//void CSASAutoTest::OnBnClickedTodayReset()
//{
//	 pMDlg->m_iGoodCnt[0]=pMDlg->m_iNGCnt[0]=pMDlg->m_iTestCnt[0]=0;
//	 pMDlg->SaveCnt();
//	m_strPToday[0].Format("%d",pMDlg->m_iGoodCnt[0]);
//	m_strPToday[1].Format("%d",pMDlg->m_iNGCnt[0]);
//	m_strPToday[2].Format("%d",pMDlg->m_iTestCnt[0]);
//	 InvalidateRect(m_rePInfoBox);
//	
//}	

//void CSASAutoTest::OnBnClickedTotalReset()
//{
//	 pMDlg->m_iGoodCnt[1]=pMDlg->m_iNGCnt[1]=pMDlg->m_iTestCnt[1]=0;
//	 pMDlg->SaveCnt();
//	m_strPTotal[0].Format("%d",pMDlg->m_iGoodCnt[1]);
//	m_strPTotal[1].Format("%d",pMDlg->m_iNGCnt[1]);
//	m_strPTotal[2].Format("%d",pMDlg->m_iTestCnt[1]);
//	InvalidateRect(m_rePInfoBox);
// 
//}



void CSASAutoTest::CountDisplay(void)
{
	m_strPToday[0].Format("%d",pMDlg->m_iGoodCnt[0]);
	m_strPToday[1].Format("%d",pMDlg->m_iNGCnt[0]);
	m_strPToday[2].Format("%d",pMDlg->m_iTestCnt[0]);
	m_strPTotal[0].Format("%d",pMDlg->m_iGoodCnt[1]);
	m_strPTotal[1].Format("%d",pMDlg->m_iNGCnt[1]);
	m_strPTotal[2].Format("%d",pMDlg->m_iTestCnt[1]);
	InvalidateRect(m_rePInfoBox);

}

void CSASAutoTest::GraphMake(void)
{
	CRect rtGraph;
//	GetDlgItem(IDC_pGraph1)->GetWindowRect(rtGraph);

//	printf("\n%s %d",__FILE__,__LINE__);
 
	ScreenToClient(rtGraph);
/*
	m_XYGraph.Create(WS_VISIBLE | WS_CHILD,rtGraph,this);
	//	m_XYGraph.m_nYDecimals=5;
	//	m_XYGraph.m_nYDecimals=9;
	m_XYGraph.SetGridXY(7,5);
	m_XYGraph.SetRange(0,100,-900,900,1);	// xlow,xupp,ylow ,yhigh,decimal place
//	m_XYGraph.SetRange(-4,4,0,1200,1);	// xlow,xupp,ylow ,yhigh
	m_XYGraph.SetYUnits("Angle");
	m_XYGraph.SetXUnits("Time");
	m_XYGraph.SetBackgroundColor(RGB(0,0,0));
	m_XYGraph.SetGridColor(RGB(192,192,255));
	m_XYGraph.SetPlotColor(RGB(0,255,0));
*/
#ifdef GraphControl
	m_Graph.Create(WS_VISIBLE | WS_CHILD,rtGraph,this);
	m_Graph.SetYUnits("Angle");
	m_Graph.SetXUnits("Time");
	m_Graph.SetBackgroundColor(RGB(0,0,0));
	m_Graph.SetGridColor(RGB(192,192,255));
	m_Graph.SetPlotColor(RGB(255,0,0),0);
	m_Graph.SetPlotColor(RGB(255,255,0),1);
#endif
//
}


void CSASAutoTest::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	long m_lCountPulse;
	switch (nIDEvent)
	{
	case 10:
		 
		m_strMesInfoD[1].Format("%.2f", pMDlg->m_dAngle);
//		long m_lCountPulse;
	//	SmcWGetCountPulse(Test.m_hSMCID, 1, &m_lCountPulse);

		break;
	}
	CDialog::OnTimer(nIDEvent);
}
