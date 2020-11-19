/************************************************ 
 	 LCD.C  
************************************************/  
#include "MAIN.H" 

uchar code FONT[]=
           {0x04,0x0F,0x12,0x0F,0x0A,0x1F,0x02,0x00,  //年
				0x1F,0x11,0x1F,0x11,0x1F,0x11,0x11,0x00,  //月
		      0x1F,0x11,0x11,0x1F,0x11,0x11,0x1F,0x00}; //日

void CGRAM(void) 
{
	uchar i;
	LCD_Cmd(0x40);           // CGRAM位址設定 
	for (i=0 ; i<24; i++) Send_Data(FONT[i]);
}

void Init_LCD(void)  // LCD的啟始程式  
{
	LCD_CmdI(0x30);   // 8bit傳輸,顯示1列,5*7字型 
	Delay(5000);  
   LCD_CmdI(0x30);       
	Delay(200);
   LCD_CmdI(0x30);    
   LCD_CmdI(0x20);   // 4bit傳輸,顯示1列,5*7字型 

   LCD_Cmd(0x28);    // 4bit傳輸,顯示2列,5*7字型 
   LCD_Cmd(0x01);    // 清除顯示幕   
	Delay(5000);
   LCD_Cmd(0x0C);    // 顯示幕ON,游標不顯示    
   LCD_Cmd(0x06);        
}

void LCD_CmdI(uchar comm)  //傳送命令到LCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(comm&0xF3);
   RS=0; EN=1; DLY(100); EN=0; DLY(100); 
}

void LCD_Cmd(uchar comm)   //傳送命令到LCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(comm&0xF3);
   RS=0; EN=1; DLY(100); EN=0; DLY(100); 
   DATA_BUS=(DATA_BUS&0x0C)|((comm<<4)&0xF3);
   RS=0; EN=1; DLY(100); EN=0; DLY(100); 
}

void Send_Data(uchar Data)  //傳送資料到LCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(Data&0xF3);  
   RS=1; EN=1; DLY(100); EN=0; DLY(100); 
	DATA_BUS=(DATA_BUS&0x0C)|((Data<<4)&0xF3);
   RS=1; EN=1; DLY(100); EN=0; DLY(100);  
}

void Delay(uint del)       // 延時函數  
{
  NEXT:	
  	del--;
	if (del !=0) goto NEXT;
}

void DLY(uchar dly)        // 延時函數 short
{
  WAIT:	
  	dly--;
	if (dly !=0) goto WAIT;
}

void DelayL(uchar CNT)      //延時函數
{
	uchar j;
   for (j=CNT; j>0; j--) 
		Delay(65000);
}