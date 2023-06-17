#include "reg51.h"
#include <stdio.h>
#include "usart.h"
#include "Key.h"
#include "Timer.h"
#include "Led.h"
#include "main.h"
// #include <REGX52.H>
extern uint8_t keyvalue;
extern Key_Info_t Key_Board;
uint8_t TempValue = 0x00;

void delay_us(uint8_t i)
{
	uint8_t a = 0;
	for(a=0;a<i;a++);
}

int main()
{
	interTimer0Init();
	UartInit();
	ScanKeyInit(&Key_Board);
	while (1)
	{
	  runLSD();
	  //TempValue = ReadTemperature();
		//KeyValueProcess(keyvalue,&Key_Board);
		//Key_Board.key_func(&Key_Board);
	}
}
