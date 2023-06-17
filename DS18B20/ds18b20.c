#include "ds18b20.h"
#include "reg51.h"
#include "main.h"
sbit DQ = P3 ^ 7;
void Ddelay(uint8_t t)
{
	uint8_t n;
	n = 0;
	while (n < t)
	{
		n++;
	}
}

void Reset(void)
{
	DQ = 1;
	Ddelay(8);
	DQ = 0;
	Ddelay(85);
	DQ = 1;
	Ddelay(14);
}

void WriteChar(uint8_t dat)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		DQ = 0;
		DQ = dat & 0x01;
		Ddelay(5);
		DQ = 1;
		dat >>= 1;
	}
	Ddelay(4);
}

uint8_t ReadChar(void)
{
	uint8_t i, dat = 0;
	for (i = 0; i < 8; i++)
	{
		DQ = 1;
		dat >> 1;
		DQ = 1;
		if (DQ)
		{
			dat = dat | 0x80;
			Ddelay(4);
		}
	}
	return dat;
}

uint8_t ReadTemperature(void)
{
	uint8_t tempH=0x00;
	uint8_t tempL=0x00;
	uint8_t temperature;
	Reset();
	WriteChar(0xcc);
	WriteChar(0x44);
	Ddelay(125);
	Reset();
	WriteChar(0xcc);
	WriteChar(0xbe);
	tempL = ReadChar();
	tempH = ReadChar();
	temperature = ((tempH * 256) + tempL) * 0.0625 * 10;
	Ddelay(200);
	return (temperature); // 返回的是0123格式
}
