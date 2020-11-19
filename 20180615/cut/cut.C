/***********************************************  
    ROT_LCD.C   2018/05/18

    16X2 LCD, P00=RS ,P01=EN ,P04~P07=DATA_BUS   
    ROTARY, P36, P37, P32 
    MPC82G516 OK
************************************************/  
#include "MAIN.H" 

uchar code MSG[6][16] ={"A: HELP         ",  
                        "B: TIME DISPLAY ",  
                        "C: UP COUNTER   ",
                        "D: DOWN COUNTER ",  
                        "E: ADC0 HEX DISP",  
                        "F: ADC0 Voltage "};

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


sbit COLUMN4  = P2^0;
sbit COLUMN3  = P2^1;
sbit COLUMN2  = P2^2;
sbit COLUMN1  = P2^3;	
sbit ROW4	  = P2^4;
sbit ROW3	  = P2^5;
sbit ROW2	  = P2^6;
sbit ROW1	  = P2^7;

uchar bdata  f; 
sbit T_FLAG   = f^0;
sbit T_ABLE   = f^1;

uchar bdata  g; 
sbit ADC_FLAG = g^0;
sbit ADC_ABLE = g^1;
sbit ADC_HEX  = g^2;

uchar bdata  h; 
sbit BE_FLAG  = h^0;




uchar SECOND,HOUR,MIN,SEC,ONESEC;


void ROTP_INT(void) interrupt 0 using 1
{
	uchar i;
	BEEP_PRO();	
  	switch (MENUPTR) {
		case 0:
			HELP();
		   break;
		case 1:
 			LCD_Cmd(0x01); Delay(5000);  
			LCD_Cmd(0x0C); LCD_Cmd(0x86);
  			for (i=0; i<4; i++) Send_Data(MSGC[i]);  
			LCD_Cmd(0xC4); 	 
         TIME_DISP(); T_ABLE=1;				
			break;
		case 2:		 
			break;
		case 3:
			break;
		case 4:
		   LCD_Cmd(1); Delay(5000); LCD_Cmd(0x0C);
			for (i=0; i<16; i++) Send_Data(MSGE[i]);
			f=0; g=0; ADC_ABLE=1; ADC_FLAG=1;	ADC_HEX=1;		 		 
			break;
		case 5:
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
	if (ADC_ABLE==1) ADC_FLAG=1;	    // 0.1 sec 
	ONESEC--;
	if (ONESEC>0) return;
	ONESEC=10; TIME_INC();		 	 
	if (T_ABLE==1) T_FLAG=1;       // 1 sec 
} 

void MAIN(void)
{
	uchar j,k;
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
		if (T_FLAG==1) {TIME_DISP(); T_FLAG=0;}
		else if (ADC_FLAG==1) {
			if (ADC_HEX==1) {
				V_ADC0(); LCD_Cmd(0xC6); ADC_HEX_DISPLAY(); ADC_FLAG=0;
			}
		}
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
	f=0; g=0;
	LCD_Cmd(0x80);	
	for (i=0; i<16; i++) Send_Data(MSG[MENUPTR%6][i]); 
	LCD_Cmd(0xC0);	
	for (i=0; i<16; i++) Send_Data(MSG[(MENUPTR+1)%6][i]); 
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

void TIME_DISP(void)
{
	uchar i,j;
	LCD_Cmd(0xC4); LCD_Cmd(0x0C);

	j=HOUR; i=j/10; 
	if (i==0) i=0x20;
	else i+=0x30;
	Send_Data(i);
	j%=10; j+=0x30;
	Send_Data(j); Send_Data(':');

	j=MIN; i=j/10; 
	if (i==0) i=0x20;
	else i+=0x30;
	Send_Data(i);
	j%=10; j+=0x30;
	Send_Data(j); Send_Data(':');

	j=SEC; i=j/10; 
	if (i==0) i=0x20;
	else i+=0x30;
	Send_Data(i);
	j%=10; j+=0x30;
	Send_Data(j);
}

void KEY_PRO(void)
{
	uchar i;
	P2=0x0F0;
	switch (KEY_NO)
	{
		case 0x0A: 

			break;	
		case 0x0B: 

			break;
		case 0x0C: 
			BEEP_PRO();
 			LCD_Cmd(0x01); Delay(5000);  
			LCD_Cmd(0x0C); LCD_Cmd(0x86);
  			for (i=0; i<4; i++) Send_Data(MSGC[i]);  
			LCD_Cmd(0xC4); 	 
         TIME_DISP(); T_ABLE=1;
			break;						 
		case 0x0D: 

			break;
		case 0x0E: 

			break;
		case 0x0F: 

			break;
		default:
			break;						
	}
}

