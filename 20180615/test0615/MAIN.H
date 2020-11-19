/***********************************************************************
*****************************By H.H.C 9A417018**************************
************************************************************************
*****************************2018/06/16*********************************
***********************************************************************/


/*******************************************
      MAIN.H 
*******************************************/
#include "MPC82N.H" 
#include <math.h>
#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long
sbit BEEP   = P3^4;

void BEEP_PRO(void);
void MENU_DISP(void);
void KEY_PRO(void);
void TIME_DISP(void);
void TIME_INC(void);
void HELP(void);
void MAIN(void);
void ROTP_INT(void);
void T0_INT(void);
void T2_INT(void);
void KEY_INT(void);
void ID_Shift(void);
void COUNTER_DISP(int len , int count);

/*******************************************
      ROTARY.H 
*******************************************/
sbit ROTA	= P3^6;  // Rotary Switch
sbit ROTB   = P3^7;
sbit ROTP   = P3^2;

void ROT_SCAN(uint DelN); 
void ROT_LEFT(void);
void ROT_RIGHT(void); 

/*******************************************
      LCD.H 
*******************************************/
sbit RS       = P0^0; // P00:RS=0指令暫存器，RS=1資料暫存器
sbit EN       = P0^1; // P01:EN=0禁能LCD，EN=1致能LCD
sfr  DATA_BUS = 0x80; // DATA BUS=P04~P07


void CGRAM(uchar num , uchar FONT[]);
void Init_LCD(void);
void LCD_CmdI(uchar Comm);
void LCD_Cmd(uchar Comm);
void Send_Data(uchar Data);
void Delay(uint Del);
void DLY(uchar dly);
void DelayL(uchar CNT);

/*******************************************
      ADC.H 
*******************************************/

void Init_ADC(void);
void V_ADC0(void);
void V_ADC5(void);
void ADC_HEX_DISPLAY(void);

void HEX_to_BIN(uint num);
void HEX_to_DEC(uint fir , uint sec , uint thi);
void ADC_BIN_DISPLAY(void);
void ADC_DEC_DISPLAY(void);
void HEX_to_VOL(uint fir , uint sec , uint thi,int sw);
void ADC_VOL_DISPLAY(int sw);

/*******************************************
      KEY.H 
*******************************************/

void SCAN_ON(void);
void SCAN_OFF(void);

/*******************************************
      COUNTER.H 
*******************************************/


void UP_COUNTER(int *count,int min,int max);
void DOWN_COUNTER(int *count,int max,int min);


