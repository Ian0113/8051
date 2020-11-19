/************************************************ 
 	 LCD.C  
************************************************/  
#include "MAIN.H" 

uchar code FONT[]=
           {0x04,0x0F,0x12,0x0F,0x0A,0x1F,0x02,0x00,  //�~
				0x1F,0x11,0x1F,0x11,0x1F,0x11,0x11,0x00,  //��
		      0x1F,0x11,0x11,0x1F,0x11,0x11,0x1F,0x00}; //��

void CGRAM(void) 
{
	uchar i;
	LCD_Cmd(0x40);           // CGRAM��}�]�w 
	for (i=0 ; i<24; i++) Send_Data(FONT[i]);
}

void Init_LCD(void)  // LCD���ҩl�{��  
{
	LCD_CmdI(0x30);   // 8bit�ǿ�,���1�C,5*7�r�� 
	Delay(5000);  
   LCD_CmdI(0x30);       
	Delay(200);
   LCD_CmdI(0x30);    
   LCD_CmdI(0x20);   // 4bit�ǿ�,���1�C,5*7�r�� 

   LCD_Cmd(0x28);    // 4bit�ǿ�,���2�C,5*7�r�� 
   LCD_Cmd(0x01);    // �M����ܹ�   
	Delay(5000);
   LCD_Cmd(0x0C);    // ��ܹ�ON,��Ф����    
   LCD_Cmd(0x06);        
}

void LCD_CmdI(uchar comm)  //�ǰe�R�O��LCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(comm&0xF3);
   RS=0; EN=1; DLY(100); EN=0; DLY(100); 
}

void LCD_Cmd(uchar comm)   //�ǰe�R�O��LCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(comm&0xF3);
   RS=0; EN=1; DLY(100); EN=0; DLY(100); 
   DATA_BUS=(DATA_BUS&0x0C)|((comm<<4)&0xF3);
   RS=0; EN=1; DLY(100); EN=0; DLY(100); 
}

void Send_Data(uchar Data)  //�ǰe��ƨ�LCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(Data&0xF3);  
   RS=1; EN=1; DLY(100); EN=0; DLY(100); 
	DATA_BUS=(DATA_BUS&0x0C)|((Data<<4)&0xF3);
   RS=1; EN=1; DLY(100); EN=0; DLY(100);  
}

void Delay(uint del)       // ���ɨ��  
{
  NEXT:	
  	del--;
	if (del !=0) goto NEXT;
}

void DLY(uchar dly)        // ���ɨ�� short
{
  WAIT:	
  	dly--;
	if (dly !=0) goto WAIT;
}

void DelayL(uchar CNT)      //���ɨ��
{
	uchar j;
   for (j=CNT; j>0; j--) 
		Delay(65000);
}