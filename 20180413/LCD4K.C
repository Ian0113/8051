/***********************************************
    LCD4K.C  2013/07/30   
    16X2 LCD
    P00=RS ,P01=EN ,P0=DATA_BUS   
    4X4 KEYBOARD, P2, NO INTERRUPT                 
************************************************/  
#include "MPC82N.H" 
#define  uchar  unsigned char
#define	uint   unsigned int

//uchar code MSGA[] = "    LCD TEST    "; // ²Ä¤@¦C¦r¤¸
//uchar code MSGB[] = " KEYBOARD TEST  "; // ²Ä¤G¦C¦r¤¸
uchar code MSGC[] = {'2','0','1','8',0,'1','1',1,'2','0',2};

int a=0;
uchar code FONT1[]={0,0,7,4,7,4,7,0};
uchar code FONT2[]={0,0,0x1C,4,0x1C,4,0x1C,0};



uchar code FONT3[]={0x1F,0x11,0x1F,0x14,0x1F,0x14,0x1B,0};//¥Á
uchar code FONT4[]={0x1F,0x13,0x1F,0x1B,0x17,0x1B,0x1F,0};//°ê

uchar code FONT5[] = {0x04,0x0F,0x12,0x0F,0x0A,0x1F,0x02,0x00,  //¦~
					      0x1F,0x11,0x1F,0x11,0x1F,0x11,0x11,0x00,  //¤ë
				         0x1F,0x11,0x11,0x1F,0x11,0x11,0x1F,0x00,  //¤é
							};
uchar code FONT6[] = {0x1F,4,4,0x0F,5,5,0x1F,0,//¤­
							8,4,0x1F,0x0A,0x0A,0x11,0,0,//¤»
							0,8,8,0x1F,8,8,0x0F,0,//¤C
							
							};
uchar code FONT7[] = {0,8,0x1F,8,8,0x0F,0,0};
//uchar code FONT5[]={};


//uchar code FONT1[] = {1,2,4,0x0A,2,2,2,0};			 							// ¤H
//uchar code FONT2[] = {0,0x1F,2,0x1A,0x1A,6,2,0};		 						// ¥i
//uchar code FONT3[] = {8,6,8,6,1,2,0x0C,0}; 										// ¤ô
//uchar code FONT4[] = {0x0A,0x1F,2,0x1F,0,0x0E,0x0A,0x0E};				 	// §i
//uchar code FONT5[] = {1,0x1F,0x17,0x0F,0x0F,0x0A,0x0B,0x12}; 	    		// ®f¥ª	
//uchar code FONT6[] = {0,0x1F,0x1D,0x1C,0x1E,0x0A,4,2};						//	®f¥k
//uchar code Table[] = {3,4,5,6,7,8};

sbit RS=P0^0;         // P00: RS=0«ü¥O¼È¦s¾¹¡ARS=1¸ê®Æ¼È¦s¾¹
sbit EN=P0^1;         // P01: EN=0¸T¯àLCD¡AEN=1­P¯àLCD
sfr  DATA_BUS = 0x80; // DATA BUS=P0.4 -- P0.7

sbit COLUMN4 = P2^0;
sbit COLUMN3 = P2^1;
sbit COLUMN2 = P2^2;
sbit COLUMN1 = P2^3;	
sbit ROW4	 = P2^4;
sbit ROW3	 = P2^5;
sbit ROW2	 = P2^6;
sbit ROW1	 = P2^7;
 
uchar bdata  f; 
sbit L_FLAG	 = f^0;
sbit K_FLAG  = f^1;
sbit B_FLAG  = f^2;
sbit C_FLAG  = f^3;

uchar KEY_NO,K_TEMP,LCD_CNT;
	
void Init_DISP(void);
void Init_LCD(void); 
void CGRAM(uchar inp);
void LCD_CmdI(uchar comm);
void LCD_Cmd(uchar comm);
void Send_Data(uchar Data);
void Delay(uint del);
void DLY(uchar dly);
void Kdelay(void);
void SCAN(void);
void SCAN_ON(void);
void SCAN_OFF(void);
void K_DISP(void);
void KEY_PRO(void);
void CGRAM2(void);
void CGRAM3(void);
//uchar TE2018[] = "2018";
uchar code STUDENT_ID[] = "        9A417018"; //²Ä¤@¦æ¦Cªí¦r¤¸
uchar code TEST[] = "R=470K";
void main(void)
{
	EN=0;	Delay(5000);
	f=0; LCD_CNT=16;	
   Init_LCD();
	Init_DISP();
   while (1) Kdelay();      
}

void Init_DISP(void)
{
	uchar i;
	CGRAM(0);
	Delay(5000);
	
   LCD_Cmd(0x80);           // ´å¼Ð¥Ñ²Ä¤@¦C¶}©lÅã¥Ü  
   Send_Data(0);
	Delay(5000);
	LCD_Cmd(0x81);
	Send_Data(1);
	Delay(5000);
   LCD_Cmd(0xC0);           // ´å¼Ð¥Ñ²Ä¤G¦C¶}©lÅã¥Ü   
   Send_Data(6);
	Delay(5000);
	LCD_Cmd(0xC1);
	Delay(5000);
	Send_Data(6);
	for(i=0;i<120;i++)Delay(50000);
	LCD_Cmd(0x01);
	



	Delay(5000);
	LCD_Cmd(0x80);
	Delay(5000);
	
	for(i=0;i<16;i++)Send_Data(STUDENT_ID[i]);
	

	Delay(5000);
	LCD_Cmd(0xC0);
	Delay(5000);

	for(i=0;i<6;i++)Send_Data(TEST[i]);
	Send_Data(0xF4);
	
}

void Init_LCD(void)  // LCDªº±Ò©lµ{¦¡  
{
	LCD_CmdI(0x30);   // DL=1¡G8bit¶Ç¿é,N=0¡GÅã¥Ü1¦C,F=0¡G5*7¦r«¬ 
	Delay(5000);  
   LCD_CmdI(0x30);      
	Delay(200);
   LCD_CmdI(0x30);       
   LCD_CmdI(0x20);   // DL=0¡G4bit¶Ç¿é,N=0¡GÅã¥Ü1¦C,F=0¡G5*7¦r«¬ 

   LCD_Cmd(0x28);    // DL=0¡G4bit¶Ç¿é,N=1¡GÅã¥Ü2¦C,F=0¡G5*7¦r«¬ 
   LCD_Cmd(0x01);    // ²M°£Åã¥Ü¹õ   
	Delay(5000);
   LCD_Cmd(0x0C);    // D=1¡GÅã¥Ü¹õON,C=0¡G´å¼Ð¤£Åã¥Ü,B=0¡G´å¼Ð¤£°{Ã{     
   LCD_Cmd(0x06);    // I/D=1¡GÅã¥Ü§¹´å¼Ð¥k²¾,S=0¡GÅã¥Ü²¾¦ì¸T¯à   
}

void CGRAM(uchar inp) 
{
	uchar i;
	LCD_Cmd(0x40);        // CGRAM¦ì§}³]©w 	
	for (i=inp; i<64; i++) Send_Data(FONT1[i]);	
}
void CGRAM2(){
	uchar i;
	LCD_Cmd(0x40);        // CGRAM¦ì§}³]©w 	
	for (i=0; i<64; i++) Send_Data(FONT3[i]);	
	}
void CGRAM3(){
	uchar i;
	LCD_Cmd(0x40);        // CGRAM¦ì§}³]©w 	
	for (i=0; i<8; i++) Send_Data(FONT7[i]);	
}

void LCD_CmdI(uchar comm)  //¶Ç°e©R¥O¨ìLCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(comm&0xF3);
   RS=0; EN=1; DLY(100); EN=0; DLY(100); 
}

void LCD_Cmd(uchar comm)   //¶Ç°e©R¥O¨ìLCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(comm&0xF3);
   RS=0; EN=1; DLY(100); EN=0; DLY(100); 
   DATA_BUS=(DATA_BUS&0x0C)|((comm<<4)&0xF3);
   RS=0; EN=1; DLY(100); EN=0; DLY(100); 
}

void Send_Data(uchar Data)  //¶Ç°e¸ê®Æ¨ìLCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(Data&0xF3);  
   RS=1; EN=1; DLY(100); EN=0; DLY(100); 
	DATA_BUS=(DATA_BUS&0x0C)|((Data<<4)&0xF3);
   RS=1; EN=1; DLY(100); EN=0; DLY(100);  
}

void Delay(uint del)       // ©µ®É¨ç¼Æ  
{
  next:
	del--;
	if (del!=0) goto next;
}

void DLY(uchar dly)       // ©µ®É¨ç¼Æ  SHORT
{
  wait:
	dly--;
	if (dly!=0) goto wait;
}

void Kdelay(void)          // ©µ®É¨ç¼Æ
{
	uint KDCNT2;
	uchar KDCNT;
	KDCNT=10;
   while (KDCNT>0) {
		KDCNT2=30000;
		while (KDCNT2>0) KDCNT2--;
		SCAN();
		if (KEY_NO==0xFF) KDCNT--;
	}
	if (B_FLAG==0 && C_FLAG==1) {
		SP-=6; C_FLAG=0;
	}
}

void SCAN(void)
{
	uchar TEMP, COD_TMP;
	P2=0xF0;
	TEMP=P2&0xF0;
	KEY_NO=0xFF;
	if (TEMP==0xF0) return;
	SCAN_ON();
	if (K_TEMP==0xFF) {KEY_NO=0xFF; return;}
	COD_TMP=K_TEMP;
	Delay(5000);
	SCAN_ON();
	if (K_TEMP==0xFF) {KEY_NO=0xFF; return;}
	if (COD_TMP!=K_TEMP) {KEY_NO=0xFF; return;}
	SCAN_OFF();
	KEY_PRO();
}

void SCAN_ON(void)
{
	KEY_NO=0xFF; K_TEMP=0xFF;
	P2=0xFE;       //P20=0±½´y²Ä4¦æ
   if (P2==0xEE) {K_TEMP=P2; KEY_NO=0x0F; return;} 
   if (P2==0xDE) {K_TEMP=P2; KEY_NO=0x0E; return;}  
   if (P2==0xBE) {K_TEMP=P2; KEY_NO=0x0D; return;}   
   if (P2==0x7E) {K_TEMP=P2; KEY_NO=0x0C; return;}  
       
   P2=0xFD;       //P21=0±½´y²Ä3¦æ
   if (P2==0xED) {K_TEMP=P2; KEY_NO=0x0B; return;}   
   if (P2==0xDD) {K_TEMP=P2; KEY_NO=0x0A; return;} 
   if (P2==0xBD) {K_TEMP=P2; KEY_NO=9; return;} 
   if (P2==0x7D) {K_TEMP=P2; KEY_NO=8; return;}  
       
   P2=0xFB;       //P22=0±½´y²Ä2¦æ
   if (P2==0xEB) {K_TEMP=P2; KEY_NO=7; return;}   
   if (P2==0xDB) {K_TEMP=P2; KEY_NO=6; return;}   
   if (P2==0xBB) {K_TEMP=P2; KEY_NO=5; return;}  
   if (P2==0x7B) {K_TEMP=P2; KEY_NO=4; return;}  
      
   P2=0xF7;       //P23=0±½´y²Ä1¦æ
   if (P2==0xE7) {K_TEMP=P2; KEY_NO=3; return;}  
   if (P2==0xD7) {K_TEMP=P2; KEY_NO=2; return;}  
   if (P2==0xB7) {K_TEMP=P2; KEY_NO=1; return;}  
   if (P2==0x77) {K_TEMP=P2; KEY_NO=0; return;} 
}

void SCAN_OFF(void)
{
LOOP:	
	P2=0xF0;
	while (P2!=0xF0);
	Delay(5000);
	if (P2!=0xF0) goto LOOP;
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
	B_FLAG=0;
 	KEY_NO |= 0x30; 
	TEMP=KEY_NO;
	Send_Data(TEMP); LCD_CNT--;
	if (LCD_CNT!=0) return;
	L_FLAG=!L_FLAG;
	if (L_FLAG==1) { 
		LCD_Cmd(0xC0); LCD_CNT=16;
	}	
	else {
   	LCD_Cmd(0x01); Delay(5000); LCD_CNT=16;				
	}			
}

void KEY_PRO(void)
{
	uchar i,j;
	int count;
	int var;
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
			B_FLAG=0;K_FLAG=1;
			Delay(5000);
			B_FLAG=0;K_FLAG=1;
			Delay(5000);
			B_FLAG=0;K_FLAG=1;
			Delay(5000);
			CGRAM2();
			Delay(5000);
			Delay(5000);
    		LCD_Cmd(0x01); Delay(5000);
    		LCD_Cmd(0x80);Delay(5000);
			
    		Send_Data(0);
			Send_Data(1);
			Delay(5000);

			Send_Data(0xB0);//¤@
			Send_Data('O');
			Send_Data(5);//¤­
			Send_Data(2);//¦~
			Send_Data(6);//¤»
			Send_Data(3);//¤ë
			Send_Data('+');		
			Send_Data(7);//¤C

			Delay(5000);			
			Send_Data(4);//¤é
			

			LCD_Cmd(0xC0);
			Delay(5000);
	
			for(i=0;i<16;i++)Send_Data(STUDENT_ID[i]);
			

			break;	
		case 0x0B:
			B_FLAG=0;K_FLAG=1;
			Delay(5000);
			B_FLAG=1; C_FLAG=1; K_FLAG=0;
    		LCD_Cmd(0x01); Delay(5000);
    		//LCD_Cmd(0x0E);Delay(5000);
			LCD_Cmd(0x80);Delay(5000);
			for(i=0;i<16;i++)Send_Data(STUDENT_ID[i]);
			while(B_FLAG==1&&K_FLAG==0){
				for(count=0;count<1000;count++)
				{
					if(B_FLAG!=1&&K_FLAG!=0)break;
					LCD_Cmd(0xC1);
					if(count<10)
					{
						LCD_Cmd(0xC3);Delay(5000);
						Send_Data((char)0x30+count);
					}
					
					else if(count<100)
					{
						LCD_Cmd(0xC2);Delay(5000);
						var = count/10;
						Send_Data((char)0x30+var);
						var = count%10;
						Send_Data((char)0x30+var);
					}
					else if(count<1000)
					{
						LCD_Cmd(0xC1);Delay(5000);
						var = count/100;
						Send_Data((char)0x30+var);
						var = (count-var*100)/10;
						Send_Data((char)0x30+var);
						var = count%10;
						Send_Data((char)0x30+var);
					}
					if(B_FLAG!=1&&K_FLAG!=0)break;
					Kdelay();
				}
			}
			break;
				
		case 0x0C: 
			B_FLAG=0;K_FLAG=1;
			Delay(5000);
			B_FLAG=1; C_FLAG=1; K_FLAG=0;
    		LCD_Cmd(0x01); Delay(5000);
    		//LCD_Cmd(0x0E);Delay(5000);
			LCD_Cmd(0x80);Delay(5000);
			for(i=0;i<16;i++)Send_Data(STUDENT_ID[i]);
			while(B_FLAG==1&&K_FLAG==0){
				for(count=789;count>=123;count--)
				{
					if(B_FLAG!=1&&K_FLAG!=0)break;
					LCD_Cmd(0xC1);
					if(count<10)
					{
						LCD_Cmd(0xC3);Delay(5000);
						Send_Data((char)0x30+count);
					}
					else if(count<100)
					{
						LCD_Cmd(0xC2);Delay(5000);
						var = count/10;
						Send_Data((char)0x30+var);
						var = count%10;
						Send_Data((char)0x30+var);
					}
					else if(count<1000)
					{
						LCD_Cmd(0xC1);Delay(5000);
						var = count/100;
						Send_Data((char)0x30+var);
						var = (count-var*100)/10;
						Send_Data((char)0x30+var);
						var = count%10;
						Send_Data((char)0x30+var);
					}
					if(B_FLAG!=1&&K_FLAG!=0)break;
					Kdelay();
				}
			}
			break;
		case 0x0D:
				B_FLAG=0;K_FLAG=1;
				Delay(5000);
				B_FLAG=1; C_FLAG=1; K_FLAG=0;
	    		LCD_Cmd(0x01); Kdelay();
			   LCD_Cmd(0x84);            //´å¼Ð¥Ñ²Ä¤@¦æ¶}©lÅã¥Ü 
				LCD_Cmd(0x0C);					//Ãö³¬´å¼Ð
			   for(i=0; i< 8; i++) Send_Data(STUDENT_ID[i]);    
			   for(i=0;i<4;i++)
				{
					LCD_Cmd(0x18);
					for(j=0;j<4;j++)Kdelay();
				}
			   while (B_FLAG==1&&K_FLAG==0) {      
			      for(i=0;i<8;i++)
					{
						LCD_Cmd(0x1C);		//¥k²¾
						for(j=0;j<4;j++)Kdelay();
					}
					for(i=0;i<8;i++)
					{
						LCD_Cmd(0x18);		//¥ª²¾
						for(j=0;j<4;j++)Kdelay();
					}
				}
			break;
		case 0x0E:
				B_FLAG=0;K_FLAG=1;
				Delay(5000);
				B_FLAG=1; C_FLAG=1; K_FLAG=0;
	    		LCD_Cmd(0x01); Delay(5000);
	    		LCD_Cmd(0x0E);
				while (B_FLAG==1&&K_FLAG==0) {
					LCD_Cmd(0x8F);	Kdelay();
					for (i=15; i>0; i--) {LCD_Cmd(0x10); Kdelay();} 	 
	   			LCD_Cmd(0xC0);	
					Kdelay();
					for (i=15; i>0; i--) {LCD_Cmd(0x14); Kdelay();}					
				}	
			break;
		case 0x0F:
				L_FLAG=0; K_FLAG=1; B_FLAG=0;
				Delay(5000);
				LCD_Cmd(0x01); Delay(5000);
				LCD_Cmd(0x80);            //´å¼Ð¥Ñ²Ä¤@¦æ¶}©lÅã¥Ü  
				LCD_Cmd(0x0C);					//Ãö³¬´å¼Ð
			   for(i=0 ; i<6 ; i++)
			      //Send_Data(Table[i]);   //Åª¨ú¦Cª16¦r°e¨ìLCDÅã¥Ü   
			break;	
		default: 
			break;		
	}
}
