================================================================================
 
2014.10.28 button style 바꾸기

 
============
2015.01.09  turn signal 값 정의 바뀜.
 

2015.01.23 담당자 통화 LIN 관련 전송 속도 19200 BPS  200ms

	자료 검토 결과 break 전송 하기 위해서 Baud 를 바꾸는 기능이 필요 함  
	13 bit 정도의 low Data 가 필요함   1bit = 52 usec   52 * 13 = 677us   677/9(BIT)=75usec  = 13314bps
	

	LIN ID 0x21, break lenght 15bit
	id = P1=1,P2=1   0xe1출력해야된다.
	id5 id4 
	00	Data 2
	01	data 2
	10	data 4
	11	data 8
	
	P0 = id0,id1,id2,id4	Even Parity
	P1 = id1,id3,id4,id5	Odd Parity
	00100001
	id = 0x21  이므로 Data 는 4 byte 
	P1=0,P0=1
	이므로 전송되는 최종 ID 는 0x61 이다.
	
	
//
2015.02.26  차속 관련 추가
	1세대,0x4f0 start bit8 lenght 9 (차속)  0 ~ 1ff(511)  factor = 0.5 하면 km/h 이다
	2세대,0x4f1 
	 2가지 설정
	 
		
2015.03.03 B can message ID  0x110 으로 바뀜.  기존값 0x138

		
  wiper auto message 없어서 
  washer_rear 와 동일 하게 사용
  
  
  debug version 이 실행 된다.
  
  release 버전은 문제 발생 된다.
  
  
  
===============
2025.04.20

JG1 SAS simulator 검사기 관려 작업

===============
	dSpeed = (m_SelModel.dMesSpeedStart[0] * 2 * 100);	// 36000/360
	// 1 회전당 72000 Pulse 출력 한다.. 
	1 RPM = 1/60 RPS = 72000 / 60 = 1200 Pulse( 1 회전당 36000*2=72000 pulse) 

	60 RPM = 1200 * 60 = 72000 pulse  초당 1회전을 의미한다.

		
		
Nonlinearity 계산방법
		
	속도가 30 이상인  (전구간 평균값 - 구간최댓값 ) or (전구간 평균값-구간 최댓값)
	중에 큰값을 사용한다..
 	참조 그림에서 
	
	구간최댓값(구간최솟값) 이란 Differ angle 값을 의미한다.

	1구간 (평균1값-1구간 구간최댓값) or (평균값1-1구간 최솟값)  중 큰값1
	2구간 (평균2값-2구간 구간최댓값) or (평균값2-2구간 최솟값)  중 큰값2
	3구간 (평균3값-3구간 구간최댓값) or (평균값3-3구간 최솟값)  중 큰값3
	
	큰값1,큰값2,큰값3 중 제일 큰값을 Nonlinearity 값으로 한다



	Hysteresis 는  

	평균1,평균2,평균3 중 제일 큰값과 제일 작은값 차리를 말한다.

	Connection Delay Time Reset 이후 Can 응답시간을 말한다.

 
   
  
  
 
		