#ifndef __LED_H__
#define __LED_H__
#include "main.h"
#include "reg51.h"
#include "timer.h"
#define LED_DATA_MAX 8
typedef struct Led_Info
{
    uint8_t LedData[LED_DATA_MAX];
    uint8_t size;
}Led_Info_t;
extern void runLSD(void);

#endif 

