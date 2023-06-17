#include "Led.h"
#include "main.h"
sbit P22 = P2 ^ 2;
sbit P23 = P2 ^ 3;
sbit P24 = P2 ^ 4;

void runLSD(void)
{
	
	uint8_t i=0;
	for(i=0;i<8;i++)
	{
		P22 = 0;
		P23 = 0;
		P24 = 0;
		delay_us(1);
		P22 = 1;
		P23 = 0;
		P24 = 0;
		delay_us(1);
		P22 = 0;
		P23 = 1;
		P24 = 0;
		delay_us(1);
		P22 = 1;
		P23 = 1;
		P24 = 0;
		delay_us(1);
		P22 = 0;
		P23 = 0;
		P24 = 1;
		delay_us(1);
		P22 = 1;
		P23 = 0;
		P24 = 1;
		delay_us(1);
		P22 = 0;
		P23 = 1;
		P24 = 1;
		delay_us(1);
		P22 = 1;
		P23 = 1;
		P24 = 1;
		delay_us(1);
		
	}
//	P22 = 1;
//	P23 = 0;
//	P24 = 0;
//	delay_Ms(1);
//	P22 = 0;
//	P23 = 1;
//	P24 = 0;
//	delay_Ms(1);
//	P22 = 0;
//	P23 = 0;
//	P24 = 0;
//	delay_Ms(1);
}

