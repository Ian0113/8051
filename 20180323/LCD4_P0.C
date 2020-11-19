/******************************************************** 
      LCD4_P0.C  2013/07/30
 
      P0.0=RS,P0.1=EN,P0.4~P0.7=DATA_BUS                              
*********************************************************/
#include "MPC82N.H"

#define uchar unsigned char 
#define uint  unsigned int 

uchar code Table1[] = "Hi! How are you."; //²Ä¤@¦æ¦Cªí¦r¤¸
uchar code Table2[] = "I'm fine. Thanks"; //²Ä¤G¦æ¦Cªí¦r¤

sbit  RS=P0^0;       // P00:RS=0«ü¥O¼È¦b¾¹¡ARS=1¸ê®Æ¼È¦s¾¹
sbit  EN=P0^1;       // P01:EN=0¸T¯àLCD¡AEN=1­P¯àLCD
sfr   DATA_BUS=0x80; // DATA bus=P0.4~P0.7

void Init_LCD(void); 
void LCD_CmdI(uchar comm);
void LCD_Cmd(uchar comm);
void Send_Data(uchar Data);
void Delay(uint del);
void DLY(uchar dly);

void main(void)
{
	uchar i; EN=0;  
   Init_LCD();               //­«¸m¤Î²M°£LCD    
   LCD_Cmd(0x80);            //´å¼Ð¥Ñ²Ä¤@¦æ¶}©lÅã¥Ü  
   for(i=0; i< 16; i++) Send_Data(Table1[i]);    
    
   LCD_Cmd(0xC0);            //´å¼Ð¥Ñ²Ä¤G¦æ¶}©lÅã¥Ü   
   for(i=0; i< 16; i++) Send_Data(Table2[i]);      
   while (1) {      
      LCD_Cmd(0x0C); 
		for (i=12; i>0; i--) Delay(65000);       
      LCD_Cmd(0x08); 
		for (i=12; i>0; i--) Delay(65000);       
	}
}

void Init_LCD(void)//LCDªº±Ò©lµ{¦¡  
{
	LCD_CmdI(0x30); //DL=1¡G8bit¶Ç¿é 
	Delay(5000);  
   LCD_CmdI(0x30);  
	Delay(200);
   LCD_CmdI(0x30);  
   LCD_CmdI(0x20); //DL=0¡G4bit¶Ç¿é  

   LCD_Cmd(0x28);  //DL=0¡G4bit¶Ç¿é 
   LCD_Cmd(0x01);  //²M°£Åã¥Ü¹õ   
	Delay(5000);
   LCD_Cmd(0x0C);  //D=1¡GÅã¥Ü¹õON,C=0¡G¤£Åã¥Ü´å¼Ð    
   LCD_Cmd(0x06);  //I/D=1¡GÅã¥Ü§¹´å¼Ð¥k²¾,S=0¡G´å¼Ð²¾¦ì¸T¯à   
}

void LCD_CmdI(uchar comm)  //¶Ç°e©R¥O¨ìLCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(comm&0xF3);
   RS=0; 
	EN=1; DLY(100); EN=0; DLY(100); //±N¸ê®Æ±qdatabus°e¤W
}

void LCD_Cmd(uchar comm)   //¶Ç°e©R¥O¨ìLCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(comm&0xF3);
   RS=0; EN=1; DLY(100); EN=0; DLY(100); //±N¸ê®Æ±qdatabus°e¤W
   DATA_BUS=(DATA_BUS&0x0C)|((comm<<4)&0xF3);
   RS=0; 
	EN=1; DLY(100); EN=0; DLY(100); //±N¸ê®Æ±qdatabus°e¤W
}

void Send_Data(uchar Data)  //¶Ç°e¸ê®Æ¨ìLCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(Data&0xF3);  
   RS=1; EN=1; DLY(100); EN=0; DLY(100); 
	DATA_BUS=(DATA_BUS&0x0C)|((Data<<4)&0xF3);
   RS=1; 
	EN=1; DLY(100); EN=0; DLY(100);  //±N¸ê®Æ±qdatabus°e¤W
}

void Delay(uint del)      //©µ®É¨ç¼Æ
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

