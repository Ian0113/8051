/*******************************************
      9A417018
*******************************************/

#include "MAIN.H" 

uint ADC16;

void Init_ADC(void)
{
	P1M0=0x21;  P1M1=0;	// P1.0, P1.5 Input Only
	AUXR=0x00;			   // Low Speed, ADRJ=0  
}

void V_ADC0(void)
{	
	float temp ;

	ADCTL = ADCON + ADCS;    // ADC CH0 Start Convert 
	while (!(ADCTL & ADCI));  // Wait ADC Complete
	ADCTL = 0;                // ADC Convert OK, Stop ADC
	ADC16 = (ADCH<<2) + ADCL;

	ADCTL = ADCON + ADCS;    // ADC CH0 Start Convert 
	while (!(ADCTL & ADCI));  // Wait ADC Complete
	ADCTL = 0;                // ADC Convert OK, Stop ADC
	temp = ADC16 + (ADCH<<2) + ADCL;

   ADC16 = temp; ADC16>>=1;
}

void V_ADC5(void)
{	
	float temp ;

	ADCTL = ADCON + ADCS + 5; // ADC CH5 Start Convert 
	while (!(ADCTL & ADCI));  // Wait ADC Complete
	ADCTL = 0;                // ADC Convert OK, Stop ADC
	ADC16 = (ADCH<<2) + ADCL;

	ADCTL = ADCON + ADCS + 5; // ADC CH5 Start Convert 
	while (!(ADCTL & ADCI));  // Wait ADC Complete
	ADCTL = 0;                // ADC Convert OK, Stop ADC
	temp = ADC16 + (ADCH<<2) + ADCL;

   ADC16 = temp; ADC16>>=1;
}

void ADC_HEX_DISPLAY(void) 	
{
	uchar i;
	uint HEX;

	HEX=ADC16;
	i=HEX>>8;
	if (i>=0x0A) i+=7;
	i+=0x30; Send_Data(i);

	i=(HEX>>4)&0x0F;
	if (i>=0x0A) i+=7;
	i+=0x30; Send_Data(i);
	i=HEX&0x0F;
	if (i>=0x0A) i+=7;
	i+=0x30; Send_Data(i);	
	Send_Data(' ');
}

void ADC_DEC_DISPLAY(void)
{
	uchar i;
	uint HEX;

	HEX=ADC16;

	HEX_to_DEC( HEX>>8 , (HEX>>4)&0x0F , HEX&0x0F);
	
	Send_Data(' ');

}

void ADC_BIN_DISPLAY(void)
{
	uchar i;
	uint HEX;

	HEX=ADC16;
	i=HEX>>8;
	HEX_to_BIN(i);

	i=(HEX>>4)&0x0F;
	HEX_to_BIN(i);

	i=HEX&0x0F;
	HEX_to_BIN(i);
	
	LCD_Cmd(0xC0);
	Send_Data(' ');
	Send_Data(' ');
}

void HEX_to_BIN(uint num)
{
	uint i;
	switch(num)
	{
		case 0:
			Send_Data('0');
			Send_Data('0');
			Send_Data('0');
			Send_Data('0');
		break;
		case 1:
			Send_Data('0');
			Send_Data('0');
			Send_Data('0');
			Send_Data('1');
		break;
		case 2:
			Send_Data('0');
			Send_Data('0');
			Send_Data('1');
			Send_Data('0');
		break;
		case 3:
			Send_Data('0');
			Send_Data('0');
			Send_Data('1');
			Send_Data('1');
		break;
		case 4:
			Send_Data('0');
			Send_Data('1');
			Send_Data('0');
			Send_Data('0');
		break;
		case 5:
			Send_Data('0');
			Send_Data('1');
			Send_Data('0');
			Send_Data('1');
		break;
		case 6:
			Send_Data('0');
			Send_Data('1');
			Send_Data('1');
			Send_Data('0');
		break;
		case 7:
			Send_Data('0');
			Send_Data('1');
			Send_Data('1');
			Send_Data('1');
		break;
		case 8:
			Send_Data('1');
			Send_Data('0');
			Send_Data('0');
			Send_Data('0');
		break;
		case 9:
			Send_Data('1');
			Send_Data('0');
			Send_Data('0');
			Send_Data('1');
		break;
		case 10:
			Send_Data('1');
			Send_Data('0');
			Send_Data('1');
			Send_Data('0');
		break;
		case 11:
			Send_Data('1');
			Send_Data('0');
			Send_Data('1');
			Send_Data('1');
		break;
		case 12:
			Send_Data('1');
			Send_Data('1');
			Send_Data('0');
			Send_Data('0');
		break;
		case 13:
			Send_Data('1');
			Send_Data('1');
			Send_Data('0');
			Send_Data('1');
		break;
		case 14:
			Send_Data('1');
			Send_Data('1');
			Send_Data('1');
			Send_Data('0');
		break;
		case 15:
			Send_Data('1');
			Send_Data('1');
			Send_Data('1');
			Send_Data('1');
		break;
	}
}

void HEX_to_DEC(uint fir , uint sec , uint thi)
{
	uchar len,i;
   uint k;
	uint v1 = fir * 16 * 16;
	uint v2 = sec * 16;
	uint v3 = thi;
	uint tal = v1 + v2 + v3;
	if(tal>999)
	{
		len = 4;
		for(i=0; i<len; i++)
		{
			k = tal / pow(10, len-i-1);
			k = k % 10;
			k = 0x30 + k;
			Send_Data(k);
		}
	}
	else if(tal>99)
	{
		Send_Data(' ');
		len = 3;
		for(i=0; i<len; i++)
		{
			k = tal / pow(10, len-i-1);
			k = k % 10;
			k = 0x30 + k;
			Send_Data(k);
		}
	}
	else if(tal>9)
	{
		Send_Data(' ');
		Send_Data(' ');
		len = 2;
		for(i=0; i<len; i++)
		{
			k = tal / pow(10, len-i-1);
			k = k % 10;
			k = 0x30 + k;
			Send_Data(k);
		}
	}
	else
	{
		Send_Data(' ');
		Send_Data(' ');
		Send_Data(' ');
		Send_Data('0' + tal );
	}
}

void HEX_to_VOL(uint fir , uint sec , uint thi,int sw)
{
	uchar len,i;
   uint k;
	uint v1 = fir * 16 * 16;
	uint v2 = sec * 16;
	uint v3 = thi;
	long kk = v1 + v2 + v3;
	if(sw==4)
	{
		kk = kk * 5 * 10000;
		kk = kk / 1023;
		Send_Data('0' + kk/10000 );
		Send_Data('.');
		Send_Data('0' + (kk%10000)/1000 );
		Send_Data('0' + (kk%1000)/100 );
		Send_Data('0' + (kk%100)/10 );
		Send_Data('0' + kk%10 );
	}
	
	else if(sw==3)
	{
		k = k * 5 * 1000;
		k = k / 1023;
		Send_Data('0' + k/1000 );
		Send_Data('.');
		Send_Data('0' + (k%1000)/100 );
		Send_Data('0' + (k%100)/10 );
		Send_Data('0' + k%10 );
	}
	else if(sw==2)
	{
		k = k * 5 * 100;
		k = k / 1023;
		Send_Data('0' + k/100 );
		Send_Data('.');
		Send_Data('0' + (k%100)/10 );
		Send_Data('0' + k%10 );
	}
	else if(sw==1)
	{
		k = k * 5 * 10;
		k = k / 1023;
		Send_Data('0' + k/10 );
		Send_Data('.');
		Send_Data('0' + k%10 );
	}
}

void ADC_VOL_DISPLAY(int sw)
{
	uint HEX;
	HEX=ADC16;

   HEX_to_VOL( HEX>>8 , (HEX>>4)&0x0F , HEX&0x0F ,sw);
	
}

