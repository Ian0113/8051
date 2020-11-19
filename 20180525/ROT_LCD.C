/***********************************************  
    ROT_LCD.C   2018/05/18

    16X2 LCD, P00=RS ,P01=EN ,P04~P07=DATA_BUS   
    ROTARY, P36, P37, P32 
    MPC82G516 OK
************************************************/  
#include "MAIN.H" 

uchar code MSG[6][16] ={"A: ENTER        ",  
                        "B: HELP         ",  
                        "C: TIME DISPLAY ",
                        "D: TIME ADJUST  ",  
                        "E: PSW INPUT    ",  
                        "F: PSW SET      "}; 

uchar code FONT[] = {0x04,0x0F,0x12,0x0F,0x0A,0x1F,0x02,0x00,  //¦~
					      0x1F,0x11,0x1F,0x11,0x1F,0x11,0x11,0x00,  //¤ë
				         0x1F,0x11,0x11,0x1F,0x11,0x11,0x1F,0x00}; //¤é
uchar bdata f;
sbit  BE_FLAG  = f^0;

uchar OLD,MENUPTR,B_CNT;


void T0_INT(void) interrupt 1 using 2 
{
	if (BE_FLAG==1) {
		B_CNT--;
		if (B_CNT==0) {BE_FLAG=0; TR0=0; BEEP=1;}
	}
}

void MAIN(void)
{
	uchar j,k;
	EN=0;	f=0;   	
 	TMOD=2; TH0=0; TL0=0;
   Init_LCD(); 
	j=ROTA; k=ROTB; OLD=k*2+j; 
	MENUPTR=0; MENU_DISP();
	ET0=1; EA=1;
	while (1) {
		ROT_SCAN(10);
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
	LCD_Cmd(0x80);	
	for (i=0; i<16; i++) Send_Data(MSG[MENUPTR%6][i]); 
	LCD_Cmd(0xC0);	
	for (i=0; i<16; i++) Send_Data(MSG[(MENUPTR+1)%6][i]); 
}





