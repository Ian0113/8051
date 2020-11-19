#include "MAIN.H" 

void CGRAM(uchar num , uchar FONT[]) 
{
	uchar i;
	LCD_Cmd(0x40);           // CGRAM位址設定 
	for (i=0; i<num*8; i++) Send_Data(FONT[i]);
}

void Init_LCD(void) // LCD的啟始程式  
{
	LCD_CmdI(0x30); Delay(5000);  
   LCD_CmdI(0x30); Delay(200);
   LCD_CmdI(0x30);  
   LCD_CmdI(0x20);  

   LCD_Cmd(0x28);    
   LCD_Cmd(1); Delay(5000);
   LCD_Cmd(0x0C);  
   LCD_Cmd(6);         
}

void LCD_CmdI(uchar Comm) //傳送命令到LCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(Comm&0xF3); 
	RS=0; EN=1; DLY(100); EN=0; DLY(100);   
}

void LCD_Cmd(uchar Comm) //傳送命令到LCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(Comm&0xF3);  
   RS=0; EN=1; DLY(100); EN=0; DLY(100); 
   DATA_BUS=(DATA_BUS&0x0C)|((Comm<<4)&0xF3);
	RS=0; EN=1; DLY(100); EN=0; DLY(100);  
}

void Send_Data(uchar Data)  //傳送資料到LCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(Data&0xF3);   
   RS=1; EN=1; DLY(100); EN=0; DLY(100); 
   DATA_BUS=(DATA_BUS&0x0C)|((Data<<4)&0xF3); 
	RS=1; EN=1; DLY(100); EN=0; DLY(100);   
}

void Delay(uint Del)       
{
  WAITD: 	
	Del--;	
	if (Del!=0) goto WAITD;	
}

void DLY(uchar dly)       
{
  WAITS: 	
	dly--;	
	if (dly!=0) goto WAITS;	
}