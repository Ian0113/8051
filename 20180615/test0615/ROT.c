/*******************************************
      9A417018
*******************************************/

#include "MAIN.H" 

extern uchar OLD,MENUPTR,B_CNT,LCD_CNT;
uchar CW_CNT,CCW_CNT;

void ROT_SCAN(uint DelN)       
{
	uchar j,k,NEW,ABTEMP;
WAITN: 	
	DelN--;  
	j=ROTA; k=ROTB; NEW=k*2+j;
	ABTEMP=NEW^OLD;
	if (ABTEMP!=0) {
		OLD=NEW;
		if (ABTEMP==2) {
			if ((NEW==1)|(NEW==2)) ROT_RIGHT();    
			if ((NEW==0)|(NEW==3)) ROT_LEFT();  
		}	
		else {
			if ((NEW==0)|(NEW==3)) ROT_RIGHT();  
			if ((NEW==1)|(NEW==2)) ROT_LEFT();    
		}		
	}
	if (DelN != 0) goto WAITN;	
}

void ROT_LEFT(void) 
{
	CW_CNT=0; CCW_CNT+=1;
	if (CCW_CNT==4) {
		CCW_CNT=0;  
		if (MENUPTR==0) MENUPTR=8;
		else MENUPTR-=1;
		BEEP_PRO(); MENU_DISP();  
	}
}

void ROT_RIGHT(void) 
{
	CCW_CNT=0; CW_CNT+=1;
	if (CW_CNT==4) {
		CW_CNT=0; 
		if (MENUPTR==8) MENUPTR=0;
		else MENUPTR+=1;
		BEEP_PRO(); MENU_DISP();  
	}
}
