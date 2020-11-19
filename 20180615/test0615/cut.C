/***********************************************  
		techer's exp
************************************************/  
#include "MAIN.H" 
#include <math.h> 

uchar code SPACE[] = "                ";
uchar code STUDENT_ID[] = "9A417018";

uchar code MSG[9][16] ={"A ADC5 Decimal  ",  
                        "B ADC5 Binary   ",  
                        "C ADC5 Voltage 4",
                        "D ADC5 Voltage 3",  
                        "E ADC5 Voltage 2",  
                        "F ADC5 Voltage 1",
							   "G ABCD CW Rotate",
							   "H UP   Counter 4",								
							   "I DOWN Counter 4"};

uchar code MSGA[] = "C: TIME D: ADC0 ";  
uchar code MSGB[] = "E: CNT  F: U/D  "; 

uchar code MSGC[] = "TIME";
uchar code MSGD[]={'2','0','1','8',0,' ','6',1,' ','8',2};

uchar code MSGE[] = " MPC82G516 ADC0 ";

uchar code FONT[] = {0x04,0x0F,0x12,0x0F,0x0A,0x1F,0x02,0x00,  //年
					      0x1F,0x11,0x1F,0x11,0x1F,0x11,0x11,0x00,  //月
				         0x1F,0x11,0x11,0x1F,0x11,0x11,0x1F,0x00}; //日
uchar KEY_NO,K_TEMP;
uchar OLD,MENUPTR,B_CNT,LCD_CNT;


sbit	COLUMN4	= P2^0;
sbit	COLUMN3  = P2^1;
sbit	COLUMN2  = P2^2;
sbit	COLUMN1  = P2^3;	
sbit	ROW4		= P2^4;
sbit	ROW3		= P2^5;
sbit	ROW2		= P2^6;
sbit	ROW1		= P2^7;

uchar	bdata  f; 
sbit	T_FLAG		= f^0;
sbit	T_ABLE		= f^1;
sbit	Stu_FLAG		= f^2;

uchar	bdata  g; 
sbit	ADC_FLAG = g^0;
sbit	ADC_ABLE = g^1;
//sbit	ADC_HEX  = g^2;
sbit  ADC_DEC  = g^2;
sbit  ADC_BIN  = g^3;
sbit  ADC_VOL1 = g^4;
sbit  ADC_VOL2 = g^5;
sbit  ADC_VOL3 = g^6;
sbit  ADC_VOL4 = g^7;

uchar	bdata  h; 
sbit	BE_FLAG  = h^0;

uchar bdata  q;
sbit	UP_FLAG		= q^0;
sbit	UP_ABLE		= q^1;
sbit	DOWN_FLAG 	= q^2;
sbit	DOWN_ABLE	= q^3;

sbit	KUP_FLAG	= q^4;
sbit	KUP_ABLE	= q^5;
sbit	KDOWN_FLAG	= q^6;
sbit	KDOWN_ABLE	= q^7;


uchar SECOND,HOUR,MIN,SEC,ONESEC;

uint RotCount = 0;
uint KeyCount = 0;
uint KeySwitch = 0;

void ROTP_INT(void) interrupt 0 using 1 //旋轉變碼器 按下
{
	uchar i;
	BEEP_PRO();
	f=0;g=0;q=0;
  	switch (MENUPTR) {
		case 0:
			LCD_Cmd(1); Delay(5000); LCD_Cmd(0x0C);
			for (i=0; i<16; i++) Send_Data(MSGE[i]);
			ADC_ABLE=1;ADC_DEC=1;
			break;
		case 1:
			LCD_Cmd(1); Delay(5000); LCD_Cmd(0x0C);
			for (i=0; i<16; i++) Send_Data(MSGE[i]);
			ADC_ABLE=1;ADC_BIN=1;
			break;
		case 2:
			LCD_Cmd(1); Delay(5000); LCD_Cmd(0x0C);
			for (i=0; i<16; i++) Send_Data(MSGE[i]);
			ADC_ABLE=1;ADC_VOL4=1;
			break;
		case 3:
			LCD_Cmd(1); Delay(5000); LCD_Cmd(0x0C);
			for (i=0; i<16; i++) Send_Data(MSGE[i]);
			ADC_ABLE=1;ADC_VOL3=1;
			break;
		case 4:
			LCD_Cmd(1); Delay(5000); LCD_Cmd(0x0C);
			for (i=0; i<16; i++) Send_Data(MSGE[i]);
			ADC_ABLE=1;ADC_VOL2=1;
			break;
		case 5:
			LCD_Cmd(1); Delay(5000); LCD_Cmd(0x0C);
			for (i=0; i<16; i++) Send_Data(MSGE[i]);
			ADC_ABLE=1;ADC_VOL1=1;
			break;
		case 6:
/*---------------------------------------------------------------------------------------------*/
			break;
		case 7:
			LCD_Cmd(0x01); Delay(5000);  
			LCD_Cmd(0x0C);
			UP_ABLE = 1;
			break;
		case 8:
			LCD_Cmd(0x01); Delay(5000);  
			LCD_Cmd(0x0C);
			DOWN_ABLE = 1;
			break;
		default:
			break;
	}
	while (ROTP==0);
}

void T0_INT(void) interrupt 1 using 2 
{
	if (BE_FLAG==1) {
		B_CNT--;
		if (B_CNT==0) {BE_FLAG=0; TR0=0; BEEP=1;}
	}
}

void KEY_INT(void) interrupt 2 using 1
{
	uchar COD_TMP;
	SCAN_ON();
	if (K_TEMP==0xFF) {P2=0xF0; return;}
	COD_TMP=K_TEMP;
	Delay(5000);
	SCAN_ON();
	if (K_TEMP==0xFF) {P2=0xF0; return;}
	if (COD_TMP!=K_TEMP)	{KEY_NO=0xFF; P2=0xF0; return;}
	SCAN_OFF();
	KEY_PRO();
}

void T2_INT(void) interrupt 5 using 3
{
	TF2=0;
	SECOND--;
	if (SECOND>0) return;
	SECOND=10; 	
/*--------------------------------------------------------------------------------------------------------------*/
	//利用計時器定時判斷ABLE  若成立更改FLAG  (0.1 sec)
	if(UP_ABLE == 1) 
	{
		UP_FLAG =1;
		UP_COUNTER(&RotCount,0,9999);
	}
	else if(DOWN_ABLE == 1) 
	{
		DOWN_FLAG =1;
		DOWN_COUNTER(&RotCount,9999,0);
	}
	else if(KUP_ABLE == 1) 
	{
		KUP_FLAG =1;
		UP_COUNTER(&KeyCount,0,123);
	}
	else if(KDOWN_ABLE == 1) 
	{
		KDOWN_FLAG =1;
		DOWN_COUNTER(&KeyCount,123,0);
	}
	else if (ADC_ABLE==1)
	{
		ADC_FLAG=1;
	}
/*--------------------------------------------------------------------------------------------------------------*/
	//利用計時器定時判斷ABLE  若成立更改FLAG  (1 sec)
	ONESEC--;
	if (ONESEC>0) return;
	ONESEC=10; TIME_INC();		 	 
	if (T_ABLE==1) T_FLAG=1;
} 

void MAIN(void)
{
	uchar i,j,k;
	EN=0;	f=0; g=0; h=0; 	
 	TMOD=2; TH0=0; TL0=0;
	SECOND=10; // SECOND=100, 1秒
	ONESEC=10;
	T2CON=0;   // T2 16 BIT Timer 
              // Fosc=22.1184MHz，Timer時脈=Fosc/12=1.8432MHz
              // Timer延時時間=(1/1.8432MHz)*18432=10000uS=10ms  
   TH2=(65536-18432)>>8; TL2=(65536-18432); TR2=1; // 10ms 
	RCAP2H=(65536-18432)>>8; RCAP2L=(65536-18432); 

   Init_LCD(); 
	j=ROTA; k=ROTB; OLD=k*2+j; 
	MENUPTR=0; MENU_DISP();
   HOUR=0; MIN=0; SEC=0;
	P2=0xF0;
	EX0=1; IT0=1;      // ROTARY PUSH BUTTON
	EX1=1;
   ET0=1; PT0=1;  
	ET2=1; PT2=1;
   EA=1;
	while (1) {
		ROT_SCAN(10);
/*--------------------------------------------------------------------------------------------------------------*/
		//利用FLAG判斷做什麼事 
		if(UP_FLAG==1)
		{
			COUNTER_DISP(4,RotCount);
			UP_FLAG=0;
		}
		else if(DOWN_FLAG==1)
		{
			COUNTER_DISP(4,RotCount);
			DOWN_FLAG=0;
		}
		else if(KUP_FLAG==1)
		{
			COUNTER_DISP(3,KeyCount);
			KUP_FLAG=0;
		}
		else if(KDOWN_FLAG==1)
		{
			COUNTER_DISP(3,KeyCount);
			KDOWN_FLAG=0;
		}
		else if(ADC_FLAG==1)
		{
			/*
			if (ADC_HEX==1)
			{
				V_ADC0(); LCD_Cmd(0xC6); ADC_HEX_DISPLAY(); ADC_FLAG=0;
			}
			*/
			if(ADC_DEC==1)
			{
				/*
				V_ADC0();
				*/
				V_ADC5();
				LCD_Cmd(0xC0);
				ADC_DEC_DISPLAY();
				ADC_FLAG=0;
			}
			else if(ADC_BIN==1)
			{
				/*
				V_ADC0();
				*/
				V_ADC5();
				LCD_Cmd(0xC0);
				ADC_BIN_DISPLAY();
				ADC_FLAG=0;
			}
			else if(ADC_VOL4==1)
			{
				/*
				V_ADC0();
				*/
				V_ADC5();
				LCD_Cmd(0xC0);
				ADC_VOL_DISPLAY(4);
				ADC_FLAG=0;
			}
			else if(ADC_VOL3==1)
			{
				/*
				V_ADC0();
				*/
				V_ADC5();
				LCD_Cmd(0xC0);
				ADC_VOL_DISPLAY(3);
				ADC_FLAG=0;
			}
			else if(ADC_VOL2==1)
			{
				/*
				V_ADC0();
				*/
				V_ADC5();
				LCD_Cmd(0xC0);
				ADC_VOL_DISPLAY(2);
				ADC_FLAG=0;
			}
			else if(ADC_VOL1==1)
			{
				/*
				V_ADC0();
				*/
				V_ADC5();
				LCD_Cmd(0xC0);
				ADC_VOL_DISPLAY(1);
				ADC_FLAG=0;
			}
		}
/*--------------------------------------------------------------------------------------------------------------*/
	}
}

void BEEP_PRO(void)
{
	B_CNT=0; BE_FLAG=1; 
	BEEP=0; TR0=1;
}

void MENU_DISP(void)
{
	uchar i;
	f=0; g=0;q=0;
	LCD_Cmd(0x80);	
	for (i=0; i<16; i++) Send_Data(MSG[MENUPTR%9][i]);
	LCD_Cmd(0xC0);	
	for (i=0; i<16; i++) Send_Data(MSG[(MENUPTR+1)%9][i]);
}

void HELP(void)
{
	uchar i;
	f=0; g=0;
	LCD_Cmd(1); Delay(5000);
	LCD_Cmd(0x0C); LCD_Cmd(0x80);            
   for (i=0; i<16; i++) Send_Data(MSGA[i]);    
   LCD_Cmd(0xC0);                
   for (i=0; i<16; i++) Send_Data(MSGB[i]);  
}

void TIME_INC(void)
{
	SEC+=1; 
	if (SEC < 60) return; 
	SEC=0; MIN+=1;
	if (MIN < 60) return;
	MIN=0; HOUR+=1;
	if (HOUR < 24) return;
	HOUR=0;	
}



void KEY_PRO(void)
{
	uchar i;
	P2=0x0F0;
	f=0;g=0;q=0;
	BEEP_PRO();
	switch (KEY_NO)
	{
		case 0x0A: 

			break;	
		case 0x0B: 

			break;
		case 0x0C:
			LCD_Cmd(0x01); Delay(5000);  
			LCD_Cmd(0x0C);
			if(KeySwitch==1)
			{
				KUP_ABLE = 1;
			}
			else
			{
				KDOWN_ABLE = 1;
			}
			break;
						 
		case 0x0D: 
			LCD_Cmd(0x01); Delay(5000);  
			LCD_Cmd(0x0C);
			if(KeySwitch==1)
			{
				KeySwitch=0;
				KDOWN_ABLE = 1;
			}
			else
			{
				KeySwitch=1;
				KUP_ABLE = 1;
			}
			break;
		case 0x0E: 

			break;
		case 0x0F: 

			break;
		default:
			break;						
	}
}


void COUNTER_DISP(int len , int count)
{
	int i;
	LCD_Cmd(0xC1);
	for(i=0; i<len; i++)
	{
		Send_Data(0x30 + (count / (int)pow(10, len-i-1))% 10);
	}
}

void ID_Shift(void)
{
	uchar i,j;
	LCD_Cmd(0x84);
	for (i=0; i<8; i++){
		ROT_SCAN(10);
		if(Stu_FLAG==0)return;
		Send_Data(STUDENT_ID[i]);
	}
	for(i=0;i<4;i++){
		ROT_SCAN(10);
		if(Stu_FLAG==0)return;
		LCD_Cmd(0xC0);
		for(j=i;j<4;j++){
			ROT_SCAN(10);
			if(Stu_FLAG==0)return;
			Send_Data(SPACE[j]);
		}
		for(j=0;j<8;j++){
			ROT_SCAN(10);
			if(Stu_FLAG==0)return;
			Send_Data(STUDENT_ID[j]);
		}
		for(j=0;j<i;j++){
			ROT_SCAN(10);
			if(Stu_FLAG==0)return;
			Send_Data(SPACE[j]);
		}
		ROT_SCAN(50000);
	}
	while(1){
		ROT_SCAN(10);
		if(Stu_FLAG==0)return;
		LCD_Cmd(0xC0);
		for(i=0;i<8;i++){
			ROT_SCAN(10);
			if(Stu_FLAG==0)return;
			LCD_Cmd(0xC0);
			for(j=0;j<i;j++){
				ROT_SCAN(10);
				if(Stu_FLAG==0)return;
				Send_Data(SPACE[j]);
			}
			for(j=0;j<8;j++){
				ROT_SCAN(10);
				if(Stu_FLAG==0)return;
				Send_Data(STUDENT_ID[j]);
			}
			for(j=i;j<8;j++){
				ROT_SCAN(10);
				if(Stu_FLAG==0)return;
				Send_Data(SPACE[j]);
			}
			ROT_SCAN(50000);
			if(Stu_FLAG==0)return;
		}
		ROT_SCAN(10);
		LCD_Cmd(0xC0);
		for(i=0;i<16;i++){
			ROT_SCAN(10);
			if(Stu_FLAG==0)return;
			Send_Data(SPACE[i]);
		}
		for(i=0;i<8;i++){
			ROT_SCAN(10);
			if(Stu_FLAG==0)return;
			LCD_Cmd(0xC0);
			for(j=i;j<8;j++){
				ROT_SCAN(10);
				if(Stu_FLAG==0)return;
				Send_Data(SPACE[j]);
			}
			for(j=0;j<8;j++){
				ROT_SCAN(10);
				if(Stu_FLAG==0)return;
				Send_Data(STUDENT_ID[j]);
			}
			for(j=0;j<i;j++){
				ROT_SCAN(10);
				if(Stu_FLAG==0)return;
				Send_Data(SPACE[j]);
			}
			ROT_SCAN(50000);
			if(Stu_FLAG==0)return;
		}
	}
}




