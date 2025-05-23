


#ifndef _IODEFINE

#define _IODEFINE

#define NOT_READ	-9999				// 초기값 left,right turn angle

#define CAL_START_SPEED	20		// 비선형을 측정 하기위한 측정 data 시작 speed 값  30 -> 20 으로 141209

#define MAX_DATA	15000

#define PASS	0
#define FAIL	-1

#define S_ON		CSMC_OUT1
#define S_RES		CSMC_OUT2

#define ON			1
#define OFF			0

#define MFSW_GST		0x7ae
#define GST_MFSW		0x7A6
#define GST_SAS			0x742
#define GST_ALL			0x7DF
#define SAS_GST			0x74A



#define CrBLACK      RGB(0,0,0)
#define CrGRAY       RGB(224,224,224)
#define CrRED        RGB(255,0,0)
#define CrGREEN      RGB(0,255,0)
#define CrBLUE       RGB(0,0,255)
#define CrYELLOW     RGB(255,255,0)
#define CrWHITE      RGB(255,255,255)

#define crCYAN	RGB(0,240,255)


 
#define TM_SERVO	52

#define MAX_DATA	15000	//최대 수집 data 10 ms 단위 


 

typedef struct _CanMsg
{
//	UINT32     dwTime;    // time stamp for receive message
	UINT8      abData[8]; // message data
} CanMsg, * pCanMsg;     // size is 20 bytes






 
#define Do_0	0
#define Do_1	2
#define Do_2	3
/*
#define obPower	0
#define obIGN2	1
#define obMETER	2
*/
#define obMFPower	0
#define obMFIGN		1
#define obSASPower  2


#define B_CAN	0
#define C_CAN	1

#define TM_MANUAL		10
#define TM_ENV			11
#define DIR		-1


#define DEF_SCALE	10		// 초기 scale value


// B can input deinfe message 1
#define C_F_FOG_SW		0x80	
#define C_HL_HIGH_SW	0x40	
#define C_T_SIGRH_SW	0x1
#define C_T_SIGLH_SW	0x2
#define C_R_FOG_SW		0x4
#define C_PASS_SW		0x8
#define C_WIPPER_WASHER_SW_AG	0x1
#define C_F_FOG_SW_AG	0x2
#define C_PASS_SW_AG	0x4
#define C_HL_HIGH_SW_AG 0x8

 // MESSAGE 2 BIT1~3 WIPPER INT SW
#define C_WIPPER_LO_SW		1
#define C_WIPPER_HI_SW		0x20
#define C_WIPPER_INT_SW		0x10
#define C_WIPPER_AUTO_SW	0x40
#define C_WIPPER_WASHER_SW	0x80	// FRONT
#define C_WIPPER_LO_SW_AG	0x4
#define C_WIPPER_HI_SW_AG	0x2
#define C_WIPPER_INT_SW_AG	0x10
#define C_WIPPER_MIST_SW_AG 0x8
#define C_WIPPER_AUTO_SW_AG	0x1	// 출력 어디에 할당할지

// MESSAGE 3 BIT 2,3,4,5,6 할당안됨
#define C_R_FOG_SW_AG		0x80
#define C_LC_SIGRH_SW		0x1
#define C_LC_SIGLH_SW		0x2		// FULL TURN LEFT

#define C_LC_SIGRH_SW_AG	0x10
#define C_LC_SIGLH_SW_AG	0x20	// full turn left


#define C_WIPPER_MIST_SW	0x80	// FRONT
//  
#define C_WIPPER_RWASHER_SW	0x40	// REAR 할당안됨



 #define C_F_FOG_SW_RJ	0x2
//#define	C_R_FOG_SW_RJ		0x00
//#define C_F_FOG_SW_RJ		0x04//struct 
 // 
#define C_HIGH_SW_RJ	0x40
#define C_PASS_SW_RJ	0x8
//
#define C_SIGRH_SW_RJ 1
#define C_SIGLH_SW_RJ 2

// 1
#define C_WIPPER_WASHER_SW_RJ	0x80
#define C_WIPPER_LO_SW_RJ	0x1
#define C_WIPPER_HI_SW_RJ	0x20
//#define C_WIPPER_INT_SW_RJ	0x10
#define C_WIPPER_AUTO_SW_RJ	0x40	// 출력 어디에 할당할지
//2
#define C_WIPPER_MIST_SW_RJ 0x80


/////////////
#define PASSING_LED	1
#define DIMMER_LED	2
#define HL_HIGH_LED		2
#define CHANG_LH_LED	4
#define FULL_TR_L_LED	8
#define CHANG_RH_LED	0x10
#define FULL_TR_R_LED	0x20
#define MIST_LED	0x40
#define INT_LED		0x80


//
#define WIPER_LO_LED	1
#define WIPER_HI_LED	2
#define WASHER_F__LED	4
#define WASHER_R_LED	8
#define WIPTE_AUTO_LED	8
#define HLAMP_LO_LED	0x10
#define TAIL_LED	0x20
#define AUTO_LED	0x40
#define RR_FOG_LED		0x80

#define FR_FOG_LED	0x1


#endif