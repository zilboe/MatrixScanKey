#include "reg51.h"
#include <stdio.h>
#include "usart.h"
#include "Key.h"
#include "Timer.h"
// #include <REGX52.H>
extern uint8_t keyvalue;
extern Key_Info_t Key_Board;
int main()
{
	interTimer0Init();
	UartInit();
	ScanKeyInit(&Key_Board);
	while (1)
	{
		KeyValueProcess(keyvalue,&Key_Board);
		Key_Board.key_func(&Key_Board);
	}
}
