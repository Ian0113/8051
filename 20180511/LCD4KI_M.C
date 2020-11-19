/*******************************************************  
      LCD4KI_M.C   2018/04/20
      16X2 LCD
      P00=RS ,P01=EN ,P0=DATA_BUS   
      4X4 KEYBOARD, P2, NO INTERRUPT  
      0 - F KEY AND DISPLAY                      
*******************************************************/ 
#include "MAIN.H" 

uchar code MSGA[] = "  >_<      O_o  "; // 第一列字元
uchar code MSGB[] = "  Hello world!  "; // 第二列字元
uchar code MSGC[] = {'2','0','1','8',0,' ','5',1,'1','1',2};
uchar code SPACE[] = "                "; //第一行列表字元
uchar code STUDENT_ID[] = "9A417018"; 

uchar bdata  f; 
sbit L_FLAG	 = f^0;
sbit K_FLAG  = f^1;

uchar bdata  g; 
sbit B_FLAG  = g^0;
sbit D_FLAG  = g^1;
sbit E_FLAG  = g^2;
sbit F_FLAG  = g^3;

uchar KEY_NO,K_TEMP,LCD_CNT;	

void KEY_INT(void) interrupt 2 using 3
{
	uchar COD_TMP;
	SCAN_ON();
	if (K_TEMP==0xFF) {KEY_NO=0xFF; P2=0XF0; return;}
	COD_TMP=K_TEMP;
	Delay(5000);
	SCAN_ON();
	if (K_TEMP==0xFF) {KEY_NO=0xFF; P2=0XF0; return;}
	if (COD_TMP!=K_TEMP) {KEY_NO=0xFF; P2=0XF0; return;}
	SCAN_OFF();
	KEY_PRO();
}

void main(void)
{
	uchar i,j;
	EN=0;	Delay(5000);
	f=0; g=0; LCD_CNT=16;
   Init_LCD(); CGRAM();  
	Init_DISP();

	/*imp*/
	EA=1; EX1=1; P2=0XF0;
 	loop:	
		if (B_FLAG==0 && D_FLAG==0 && E_FLAG==0 && F_FLAG==0) {
			DLY(100);
			if (B_FLAG==1) goto loop;
			if (D_FLAG==1) goto loop;
			if (E_FLAG==1) goto loop;
			if (F_FLAG==1) goto loop;
		}


		else if (B_FLAG==1) {
			LCD_Cmd(0x80); DelayL(6);
			if (B_FLAG==0) goto loop;    
   		for(i=0; i< 15; i++) {
				LCD_Cmd(0x14); DelayL(6);
				if (B_FLAG==0) goto loop; 
			}
			LCD_Cmd(0xCF); DelayL(6);
			if (B_FLAG==0) goto loop; 
   		for(i=0; i< 15; i++) {
				LCD_Cmd(0x10); DelayL(12);
				if (B_FLAG==0) goto loop; 
			} 
      }


		else if (D_FLAG==1) {
   		LCD_Cmd(0x84);            //游標由第一行開始顯示  
   		for (i=0; i<8; i++) Send_Data(STUDENT_ID[i]);
  			DelayL(6); 
			if (D_FLAG==0) goto loop; 
  			for (i=0; i< 4; i++) {
				LCD_Cmd(0x18); DelayL(6);
 				if (D_FLAG==0) goto loop;
			}    
   		while (1) {      
   			for (i=0; i< 8; i++) {
					LCD_Cmd(0x1C); DelayL(6);
					if (D_FLAG==0) goto loop; 
				} 
   			for (i=0; i< 8; i++) {
					LCD_Cmd(0x18); DelayL(6);
					if (D_FLAG==0) goto loop; 
				}                   
			}
      }


		else if (E_FLAG==1) {
			LCD_Cmd(0xC0); DelayL(6);
			if (E_FLAG==0) goto loop;    
   		for(i=0; i< 15; i++) {
				LCD_Cmd(0x14); DelayL(6);
				if (E_FLAG==0) goto loop; 
			}
			LCD_Cmd(0x8F); DelayL(6);
			if (E_FLAG==0) goto loop; 
   		for(i=0; i< 15; i++) {
				LCD_Cmd(0x10); DelayL(12);
				if (E_FLAG==0) goto loop; 
			} 
      }


		else if(F_FLAG==1){
			LCD_Cmd(0x84);            //游標由第一行開始顯示  
			if(F_FLAG==0)goto loop;
   		for (i=0; i<8; i++){
				Send_Data(STUDENT_ID[i]);
				if(F_FLAG==0)goto loop;
			}
			for(i=0;i<4;i++){
					if(F_FLAG==0)goto loop;
					LCD_Cmd(0xC0);
					if(F_FLAG==0)goto loop;
					for(j=i;j<4;j++){
						if(F_FLAG==0)goto loop;
						Send_Data(SPACE[j]);
						if(F_FLAG==0)goto loop;
					}
					for(j=0;j<8;j++){
						if(F_FLAG==0)goto loop;
						Send_Data(STUDENT_ID[j]);
						if(F_FLAG==0)goto loop;
					}
					for(j=0;j<i;j++){
						if(F_FLAG==0)goto loop;
						Send_Data(SPACE[j]);
						if(F_FLAG==0)goto loop;
					}
					if(F_FLAG==0)goto loop;
					DelayL(6);
					if(F_FLAG==0)goto loop;
				}
			while(1){
				if(F_FLAG==0)goto loop;
				LCD_Cmd(0xC0);
				if(F_FLAG==0)goto loop;
				for(i=0;i<8;i++){
					if(F_FLAG==0)goto loop;
					LCD_Cmd(0xC0);
					if(F_FLAG==0)goto loop;
					for(j=0;j<i;j++){
						if(F_FLAG==0)goto loop;
						Send_Data(SPACE[j]);
						if(F_FLAG==0)goto loop;
					}
					for(j=0;j<8;j++){
						if(F_FLAG==0)goto loop;
						Send_Data(STUDENT_ID[j]);
						if(F_FLAG==0)goto loop;
					}
					for(j=i;j<8;j++){
						if(F_FLAG==0)goto loop;
						Send_Data(SPACE[j]);
						if(F_FLAG==0)goto loop;
					}
					if(F_FLAG==0)goto loop;
					DelayL(6);
					if(F_FLAG==0)goto loop;
				}
				if(F_FLAG==0)goto loop;
				LCD_Cmd(0xC0);
				if(F_FLAG==0)goto loop;
				for(i=0;i<16;i++){
					if(F_FLAG==0)goto loop;
					Send_Data(SPACE[i]);
					if(F_FLAG==0)goto loop;
				}
				for(i=0;i<8;i++){
					if(F_FLAG==0)goto loop;
					LCD_Cmd(0xC0);
					if(F_FLAG==0)goto loop;
					for(j=i;j<8;j++){
						if(F_FLAG==0)goto loop;
						Send_Data(SPACE[j]);
						if(F_FLAG==0)goto loop;
					}
					for(j=0;j<8;j++){
						if(F_FLAG==0)goto loop;
						Send_Data(STUDENT_ID[j]);
						if(F_FLAG==0)goto loop;
					}
					for(j=0;j<i;j++){
						if(F_FLAG==0)goto loop;
						Send_Data(SPACE[j]);
						if(F_FLAG==0)goto loop;
					}
					if(F_FLAG==0)goto loop;
					DelayL(6);
					if(F_FLAG==0)goto loop;
				}
			}
		}
		goto loop;            
}

void Init_DISP(void)
{
	uchar i; 
   LCD_Cmd(0x80);           // 游標由第一列開始顯示  
   for (i=0; i<16; i++) Send_Data(MSGA[i]);   
   LCD_Cmd(0xC0);           // 游標由第二列開始顯示   
   for (i=0; i<16; i++) Send_Data(MSGB[i]);  
}

void K_DISP(void)
{
	uchar TEMP;
	if (K_FLAG==0) {
  		LCD_Cmd(0x01); Delay(5000);
	   LCD_Cmd(0x0E); 
	   LCD_Cmd(0x6); 
		L_FLAG=0; K_FLAG=1;
		LCD_CNT=16;					
	}
	g=0;
 	KEY_NO |= 0x30; 
	TEMP=KEY_NO;
	Send_Data(TEMP); LCD_CNT--;
	if (LCD_CNT!=0) return;
	L_FLAG=!L_FLAG;
	if (L_FLAG==1) {LCD_Cmd(0xC0); LCD_CNT=16;}	
	else {
   	LCD_Cmd(0x01); Delay(5000); LCD_CNT=16;				
	}			
}

void KEY_PRO(void)
{
	uchar i;
	/*imp*/
	P2=0XF0;
	switch (KEY_NO) {
		case 0: 
		case 1: 
		case 2: 
		case 3: 
		case 4: 
		case 5: 
		case 6: 
		case 7: 
		case 8: 
		case 9: 
			K_DISP();
			break;
		case 0x0A: 
			g=0; K_FLAG=0;
    		LCD_Cmd(0x01);  // 清除顯示幕   
			Delay(5000);
    		LCD_Cmd(0x0C);
    		LCD_Cmd(0x83);
    		for (i=0 ; i<11 ; i++)
        		Send_Data(MSGC[i]);
			break;
		case 0x0B:
			if (B_FLAG==1) break; 
			g=0; B_FLAG=1; K_FLAG=0;
    		LCD_Cmd(0x01); Delay(5000);
    		LCD_Cmd(0x0E);
			break;
		case 0x0C: 
    		LCD_Cmd(0x01); Delay(5000);
    		LCD_Cmd(0x0F);  // D=1：顯示幕ON,C=1：游標顯示,B=1：游標閃爍     
			LCD_CNT=16;
			L_FLAG=0; K_FLAG=1; g=0;
			break;
		case 0x0D:
			if (D_FLAG==1) break; 
			g=0; D_FLAG=1; K_FLAG=0;
    		LCD_Cmd(0x01); Delay(5000);
    		LCD_Cmd(0x0C);
			break;
		case 0x0E:
			if (E_FLAG==1) break; 
			g=0; E_FLAG=1; K_FLAG=0;
    		LCD_Cmd(0x01); Delay(5000);
    		LCD_Cmd(0x0E);
			break;
		case 0x0F:
			if (F_FLAG==1) break; 
			g=0; F_FLAG=1; K_FLAG=0;
    		LCD_Cmd(0x01); Delay(5000);
    		LCD_Cmd(0x0C);
			break;
		default:		 
			break;	
	}
}
