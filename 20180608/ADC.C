/*******************************************
      ADC.C 
*******************************************/
#include "MAIN.H" 

extern uint  ADC16;

void Init_ADC(void)
{
	P1M0=0x21;  P1M1=0;	     // P1.0, P1.5 Input Only
	AUXR=0x00;	ADCTL=0x60;   // High Speed, ADRJ=0  
}

void V_ADC0(void)
{	
	float temp ;

	ADCTL = ADCTL+ADCON+ADCS; // ADC CH0 Start Convert 
	while (!(ADCTL & ADCI));  // Wait ADC Complete
	ADCTL = 0x60;             // ADC Convert OK, Stop ADC
	ADC16 = (ADCH<<2) + ADCL;
	ADCTL =ADCTL+ADCON+ADCS;  // ADC CH0 Start Convert 
	while (!(ADCTL & ADCI));  // Wait ADC Complete
	ADCTL = 0x60;             // ADC Convert OK, Stop ADC
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

void ADC_HEX_DISPLAY(void) {			
	uint i,HEX;

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
	

