#ifndef __USART_H__
#define __USART_H__

#include "reg51.h"
#include "stdio.h"
#include "main.h"
void delay_Ms(unsigned short i);
void UartInit(void);
void timer_init(void);
void sendByte(unsigned char ch);
void sendString(char *str);

#endif

