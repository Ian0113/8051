/******************************************************** 
      LCD4_P0.C  2013/07/30
 
      P0.0=RS,P0.1=EN,P0.4~P0.7=DATA_BUS                              
*********************************************************/
#include "MPC82N.H"

#define uchar unsigned char 
#define uint  unsigned int 

sbit  RS=P0^0;       // P00:RS=0指令暫在器，RS=1資料暫存器
sbit  EN=P0^1;       // P01:EN=0禁能LCD，EN=1致能LCD
sfr   DATA_BUS=0x80; // DATA bus=P0.4~P0.7

void Init_LCD(void); 
void LCD_CmdI(uchar comm);
void LCD_Cmd(uchar comm);
void Send_Data(uchar Data);
void Delay(uint del);
void DLY(uchar dly);
void DelayL(uchar CNT);
uchar code SPACE[] = "                 "; //第一行列表字元
uchar code STUDENT_ID[] = "9A417018"; //第一行列表字元

void main(void)
{
	uchar i,j; EN=0;  
   Init_LCD();               //重置及清除LCD
	//0x80~0x8F
	//LCD_Cmd(0x80);            //游標由第一行開始顯示 
	LCD_Cmd(0x0E);				//顯示油標

   while (1) {   
		
      for(i=0;i<9;i++)
		{
			LCD_Cmd(0x80);
			LCD_Cmd(0x06);
			DelayL(12);
			for(j=0; j<i; j++) Send_Data(SPACE[j]);
			for(j=0; j<8; j++) Send_Data(STUDENT_ID[j]);
		}
		LCD_Cmd(0x88);
		for(i=0;i<8;i++)
		{
			
			
			for(j=0; j<8; j++)
			{
				LCD_Cmd(0x14);
				DelayL(12);
				Send_Data(STUDENT_ID[j]);
			}
			//for(j=0; j<i; j++) Send_Data(SPACE[j]);
		}
	}
}

void Init_LCD(void)//LCD的啟始程式  
{
	LCD_CmdI(0x30); //DL=1：8bit傳輸 
	Delay(5000);  
   LCD_CmdI(0x30);  
	Delay(200);
   LCD_CmdI(0x30);  
   LCD_CmdI(0x20); //DL=0：4bit傳輸  

   LCD_Cmd(0x28);  //DL=0：4bit傳輸 
   LCD_Cmd(0x01);  //清除顯示幕   
	Delay(5000);
   LCD_Cmd(0x0C);  //D=1：顯示幕ON,C=0：不顯示游標    
   LCD_Cmd(0x06);  //I/D=1：顯示完游標右移,S=0：游標移位禁能   
}

void LCD_CmdI(uchar comm)  //傳送命令到LCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(comm&0xF3);
   RS=0; 
	EN=1; DLY(100); EN=0; DLY(100); //將資料從databus送上
}

void LCD_Cmd(uchar comm)   //傳送命令到LCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(comm&0xF3);
   RS=0; EN=1; DLY(100); EN=0; DLY(100); //將資料從databus送上
   DATA_BUS=(DATA_BUS&0x0C)|((comm<<4)&0xF3);
   RS=0; 
	EN=1; DLY(100); EN=0; DLY(100); //將資料從databus送上
}

void Send_Data(uchar Data)  //傳送資料到LCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(Data&0xF3);  
   RS=1; EN=1; DLY(100); EN=0; DLY(100); 
	DATA_BUS=(DATA_BUS&0x0C)|((Data<<4)&0xF3);
   RS=1; 
	EN=1; DLY(100); EN=0; DLY(100);  //將資料從databus送上
}

void Delay(uint del)      //延時函數
{
 wait:
	del--;
	if (del!=0) goto wait;
}

void DLY(uchar dly)      //延時函數short
{
 next:
   dly--;
	if (dly!=0) goto next;
}

void DelayL(uchar CNT)      //延時函數
{
	uchar o;
	for (o=CNT; o>0; o--) Delay(65000);
}

