#ifndef __DS18B20_H__
#define __DS18B20_H__
#include "main.h"
extern char buf[64];
extern uint8_t TempValue;
extern void send_Temp(uint8_t temp);
#endif