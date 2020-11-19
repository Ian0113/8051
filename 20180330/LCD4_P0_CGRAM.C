/********************************************** 
		LCD4_P0_CGRAM.C  2009/11/08

      P0.0=RS,P0.1=EN,P0.4~P0.7=DATA_BUS                              
**********************************************/
#include "MPC82N.H"

#define uchar unsigned char 
#define uint  unsigned int 

uchar code FONT1[] = {1,2,4,0x0A,2,2,2,0};			 							// ¤H
uchar code FONT2[] = {0,0x1F,2,0x1A,0x1A,6,2,0};		 						// ¥i
uchar code FONT3[] = {8,6,8,6,1,2,0x0C,0}; 										// ¤ô
uchar code FONT4[] = {0x0A,0x1F,2,0x1F,0,0x0E,0x0A,0x0E};				 	// §i
uchar code FONT5[] = {1,0x1F,0x17,0x0F,0x0F,0x0A,0x0B,0x12}; 	    		// ®f¥ª	
uchar code FONT6[] = {0,0x1F,0x1D,0x1C,0x1E,0x0A,4,2};						//	®f¥k
uchar code Table[] = {0,1,2,3,4,5};
sbit   RS=P0^0;       // P00 : RS=0«ü¥O¼È¦b¾¹¡ARS=1¸ê®Æ¼È¦s¾¹
sbit   EN=P0^1;       // P01 : EN=0¸T¯àLCD¡AEN=1­P¯àLCD
sfr    DATA_BUS=0x80; // DATA BUS=P0.4~P0.7

void Init_LCD(void); 
void CGRAM(void);
void LCD_CmdI(uchar comm);
void LCD_Cmd(uchar comm);
void Send_Data(uchar Data);
void Delay(uint del);
void DLY(uchar dly);

void main(void)
{
	uchar i; EN=0;  
   Init_LCD();               //­«¸m¤Î²M°£LCD    
	CGRAM();
   LCD_Cmd(0x80);            //´å¼Ð¥Ñ²Ä¤@¦æ¶}©lÅã¥Ü  
   for(i=0 ; i<6 ; i++)
      Send_Data(Table[i]);   //Åª¨ú¦Cª16¦r°e¨ìLCDÅã¥Ü   
   while (1) {      
      LCD_Cmd(0x08); 
      for(i=0;i<12;i++)Delay(65000);  // D=0Ãö³¬Åã¥Ü¹õ    
      LCD_Cmd(0x0C);
      for(i=0;i<12;i++)Delay(65000);  // D=1¶}©lÅã¥Ü¹õ  
	}
}

void Init_LCD(void)    //LCDªº±Ò©lµ{¦¡  
{
	Delay(65000);	
   LCD_CmdI(0x30); //DL=1¡G8bit¶Ç¿é,N=1¡GÅã¥Ü1¦æ,F=0¡G5*7¦r«¬ 
	Delay(50000);  
   LCD_CmdI(0x30); //DL=1¡G8bit¶Ç¿é,N=1¡GÅã¥Ü1¦æ,F=0¡G5*7¦r«¬ 
	Delay(200);
   LCD_CmdI(0x30); //DL=1¡G8bit¶Ç¿é,N=1¡GÅã¥Ü1¦æ,F=0¡G5*7¦r«¬ 
   LCD_CmdI(0x20); //DL=1¡G4bit¶Ç¿é,N=1¡GÅã¥Ü1¦æ,F=0¡G5*7¦r«¬ 

   LCD_Cmd(0x28);  //DL=1¡G4bit¶Ç¿é,N=1¡GÅã¥Ü2¦æ,F=0¡G5*7¦r«¬ 
   LCD_Cmd(0x01);  //²M°£Åã¥Ü¹õ   
	Delay(5000);
   LCD_Cmd(0x0C);  //D=1¡GÅã¥Ü¹õON,C=0¡G¤£Åã¥Ü´å¼Ð,B=0¡G´å¼Ð¤£°{Ã{     
   LCD_Cmd(0x06);  //I/D=1¡GÅã¥Ü§¹´å¼Ð¥k²¾,S=0¡G´å¼Ð²¾¦ì¸T¯à   
}

void CGRAM(void)
{
	uchar i;
   LCD_Cmd(0x40); 
	for (i=0; i<40; i++)
		Send_Data(FONT1[i]);
}

void Send_Data(uchar Data)  //¶Ç°e¸ê®Æ¨ìLCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(Data&0xF3);   
   RS=1; 
	EN=1; DLY(100);	 //¸ê®Æ¨ìLCD¤º   
   EN=0; DLY(100);  //¸T¯àLCD

   DATA_BUS=(DATA_BUS&0x0C)|((Data<<4)&0xF3); 
   RS=1;       	  
	EN=1; DLY(100);	 //¸ê®Æ¨ìLCD¤º   
   EN=0; DLY(100);  //¸T¯àLCD
}

void LCD_Cmd(uchar comm) //¶Ç°e©R¥O¨ìLCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(comm&0xF3);  
   RS=0;  
	EN=1; DLY(100);	 //¸ê®Æ¨ìLCD¤º   
   EN=0; DLY(100);  //¸T¯àLCD

   DATA_BUS=(DATA_BUS&0x0C)|((comm<<4)&0xF3);
   RS=0;  
	EN=1; DLY(100);	 //¸ê®Æ¨ìLCD¤º   
   EN=0; DLY(100);  //¸T¯àLCD
}

void LCD_CmdI(uchar comm) //¶Ç°e©R¥O¨ìLCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(comm&0xF3); 
	RS=0;
	EN=1; DLY(100);	 //¸ê®Æ¨ìLCD¤º   
   EN=0; DLY(100);  //¸T¯àLCD
}
void Delay(uint del)     //©µ®É¨ç¼Æ
{
 wait:
	del--;
	if (del!=0) goto wait;
}

void DLY(uchar dly)      //©µ®É¨ç¼Æshort
{
 next:
   dly--;
	if (dly!=0) goto next;
}

