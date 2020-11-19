/******************************************************** 
      LCD4_P0.C  2013/07/30
 
      P0.0=RS,P0.1=EN,P0.4~P0.7=DATA_BUS                              
*********************************************************/
#include "MPC82N.H"

#define uchar unsigned char 
#define uint  unsigned int 

uchar code STUDENT_ID[] = "9A417018"; //�Ĥ@��C���r��

sbit  RS=P0^0;       // P00:RS=0���O�Ȧb���ARS=1��ƼȦs��
sbit  EN=P0^1;       // P01:EN=0�T��LCD�AEN=1�P��LCD
sfr   DATA_BUS=0x80; // DATA bus=P0.4~P0.7

void Init_LCD(void); 
void LCD_CmdI(uchar comm);
void LCD_Cmd(uchar comm);
void Send_Data(uchar Data);
void Delay(uint del);
void DLY(uchar dly);
void DelayL(uchar CNT);

void main(void)
{
	uchar i; EN=0;  
   Init_LCD();               //���m�βM��LCD
	//0x80~0x8F
   LCD_Cmd(0x84);            //��ХѲĤ@��}�l���  
   for(i=0; i< 8; i++) Send_Data(STUDENT_ID[i]);    
   //LCD_Cmd(0xC0);            //��ХѲĤG��}�l���   
   for(i=0;i<4;i++)
	{
		LCD_Cmd(0x18);
		DelayL(12);
	}
   while (1) {      
      for(i=0;i<8;i++)
		{
			LCD_Cmd(0x1C);		//�k��
			DelayL(12);
		}
		for(i=0;i<8;i++)
		{
			LCD_Cmd(0x18);		//����
			DelayL(12);
		}
	}
}

void Init_LCD(void)//LCD���ҩl�{��  
{
	LCD_CmdI(0x30); //DL=1�G8bit�ǿ� 
	Delay(5000);  
   LCD_CmdI(0x30);  
	Delay(200);
   LCD_CmdI(0x30);  
   LCD_CmdI(0x20); //DL=0�G4bit�ǿ�  

   LCD_Cmd(0x28);  //DL=0�G4bit�ǿ� 
   LCD_Cmd(0x01);  //�M����ܹ�   
	Delay(5000);
   LCD_Cmd(0x0C);  //D=1�G��ܹ�ON,C=0�G����ܴ��    
   LCD_Cmd(0x06);  //I/D=1�G��ܧ���Хk��,S=0�G��в���T��   
}

void LCD_CmdI(uchar comm)  //�ǰe�R�O��LCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(comm&0xF3);
   RS=0; 
	EN=1; DLY(100); EN=0; DLY(100); //�N��Ʊqdatabus�e�W
}

void LCD_Cmd(uchar comm)   //�ǰe�R�O��LCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(comm&0xF3);
   RS=0; EN=1; DLY(100); EN=0; DLY(100); //�N��Ʊqdatabus�e�W
   DATA_BUS=(DATA_BUS&0x0C)|((comm<<4)&0xF3);
   RS=0; 
	EN=1; DLY(100); EN=0; DLY(100); //�N��Ʊqdatabus�e�W
}

void Send_Data(uchar Data)  //�ǰe��ƨ�LCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(Data&0xF3);  
   RS=1; EN=1; DLY(100); EN=0; DLY(100); 
	DATA_BUS=(DATA_BUS&0x0C)|((Data<<4)&0xF3);
   RS=1; 
	EN=1; DLY(100); EN=0; DLY(100);  //�N��Ʊqdatabus�e�W
}

void Delay(uint del)      //���ɨ��
{
 wait:
	del--;
	if (del!=0) goto wait;
}

void DLY(uchar dly)      //���ɨ��short
{
 next:
   dly--;
	if (dly!=0) goto next;
}

void DelayL(uchar CNT)      //���ɨ��
{
	uchar o;
	for (o=CNT; o>0; o--) Delay(65000);
}
