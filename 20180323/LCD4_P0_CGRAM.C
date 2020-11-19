/********************************************** 
		LCD4_P0_CGRAM.C  2009/11/08

      P0.0=RS,P0.1=EN,P0.4~P0.7=DATA_BUS                              
**********************************************/
#include "MPC82N.H"

#define uchar unsigned char 
#define uint  unsigned int 

uchar code FONT1[] = {1,2,4,0x0C,0x14,4,4,0};			 // �H
uchar code FONT2[] = {0,0x1F,2,0x1A,0X1A,6,2,0};		 // �i
uchar code FONT3[] = {0x0F,0,0x0F,0,1,2,4,0}; 					// ��
uchar code FONT4[] = {0x0C,0x1E,4,0x1F,0,0x0E,0x0A,0x0E};	// �i
uchar code FONT5[] = {0x14,0x1F,4,0x1F,0x0E,0x15,04,0}; 	    // ��	
uchar code Table[] = {0,1,2,3,4,0}; 			 

sbit   RS=P0^0;       // P00 : RS=0���O�Ȧb���ARS=1��ƼȦs��
sbit   EN=P0^1;       // P01 : EN=0�T��LCD�AEN=1�P��LCD
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
   Init_LCD();               //���m�βM��LCD    
	CGRAM();
   LCD_Cmd(0x80);            //��ХѲĤ@��}�l���  
   for(i=0 ; i<6 ; i++)
      Send_Data(Table[i]);   //Ū���C�16�r�e��LCD���   
   while (1) {      
      LCD_Cmd(0x08);for(i=12;i>0;i--) Delay(65000);  // D=0������ܹ�    
      LCD_Cmd(0x0C);for(i=12;i>0;i--) Delay(65000);  // D=1�}�l��ܹ�  
	}
}

void Init_LCD(void)    //LCD���ҩl�{��  
{
	Delay(65000);	
   LCD_CmdI(0x30); //DL=1�G8bit�ǿ�,N=1�G���1��,F=0�G5*7�r�� 
	Delay(50000);  
   LCD_CmdI(0x30); //DL=1�G8bit�ǿ�,N=1�G���1��,F=0�G5*7�r�� 
	Delay(200);
   LCD_CmdI(0x30); //DL=1�G8bit�ǿ�,N=1�G���1��,F=0�G5*7�r�� 
   LCD_CmdI(0x20); //DL=1�G4bit�ǿ�,N=1�G���1��,F=0�G5*7�r�� 

   LCD_Cmd(0x28);  //DL=1�G4bit�ǿ�,N=1�G���2��,F=0�G5*7�r�� 
   LCD_Cmd(0x01);  //�M����ܹ�   
	Delay(5000);
   LCD_Cmd(0x0C);  //D=1�G��ܹ�ON,C=0�G����ܴ��,B=0�G��Ф��{�{     
   LCD_Cmd(0x06);  //I/D=1�G��ܧ���Хk��,S=0�G��в���T��   
}

void CGRAM(void)
{
	uchar i;
   LCD_Cmd(0x40); //���VCGram
	for (i=0; i<40; i++)
		Send_Data(FONT1[i]);		//�N��Ƽg��CGram
}

void Send_Data(uchar Data)  //�ǰe��ƨ�LCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(Data&0xF3);   
   RS=1; 
	EN=1; DLY(100);	 //��ƨ�LCD��   
   EN=0; DLY(100);  //�T��LCD

   DATA_BUS=(DATA_BUS&0x0C)|((Data<<4)&0xF3); 
   RS=1;       	  
	EN=1; DLY(100);	 //��ƨ�LCD��   
   EN=0; DLY(100);  //�T��LCD
}

void LCD_Cmd(uchar comm) //�ǰe�R�O��LCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(comm&0xF3);  
   RS=0;  
	EN=1; DLY(100);	 //��ƨ�LCD��   
   EN=0; DLY(100);  //�T��LCD

   DATA_BUS=(DATA_BUS&0x0C)|((comm<<4)&0xF3);
   RS=0;  
	EN=1; DLY(100);	 //��ƨ�LCD��   
   EN=0; DLY(100);  //�T��LCD
}

void LCD_CmdI(uchar comm) //�ǰe�R�O��LCD
{
   DATA_BUS=(DATA_BUS&0x0C)|(comm&0xF3); 
	RS=0;
	EN=1; DLY(100);	 //��ƨ�LCD��   
   EN=0; DLY(100);  //�T��LCD
}
void Delay(uint del)     //���ɨ��
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
