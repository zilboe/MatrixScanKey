#include "Timer.h"
#include "Key.h"
#include "Led.h"
uint16_t sysCount;
uint8_t keyvalue;
uint32_t systicks;
uint32_t keyComNumber;
bool isLeftModeFlag = false;
static uint8_t lastKeyValue;
void interTimer0Init(void)
{
    TMOD |= 0x01;
    TH0 = (65536-1000)/256;
    TL0 = (65536-1000)%256;
    TH1 = 
    ET0 = 1;
    TR0 = 1;
    EA = 1;
}

void runAppLamp(void)
{
    if((P2>>7)&1)
    {
        P2 &= ~(1<<7);
    }
    else
    {
        P2 |= (1<<7);
    }
}

void interrupt_timer1(void) interrupt 1
{
    TH0 = (65536-1000)/256;    // 中断后，赋初值；
    TL0 = (65536-1000)%256;		
    if(!isLeftModeFlag)
    {
        keyvalue = getKeyValue();
    }
    else
    {
       keyvalue = getKeyValue2(); 
    }
    if(keyvalue != 0x00)
	    isLeftModeFlag = ~isLeftModeFlag;
    if(lastKeyValue==keyvalue)
    {
       keyComNumber++; 
    }
    else
    {
        keyComNumber = 0;
    }
    sysCount++;       // 每次中断，计数 累加 1；
    systicks++;
    if(sysCount>=1000)
    {
      runAppLamp();     //运行灯
      sysCount = 0; 
    }
		//runLSD();
}

void tick_delay_Ms(uint32_t ms)
{
	uint32_t timetemp;
	timetemp = systicks;
	while((timetemp-systicks) > ms);
}

void interrupt_timer3(void) interrupt 3
{
	
}
