#ifndef __TIMER_H__
#define __TIMER_H__
#include "reg51.H"
#include "main.h"

void interTimer0Init(void);

void tick_delay_Ms(uint32_t ms);
#endif
