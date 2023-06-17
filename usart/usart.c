#include "usart.h"
char buf[64];
void delay_Ms(unsigned short i)
{
	unsigned short x,y;
	for(x=i;x>0;x--)
	for(y=1000;y>0;y--);
}

void UartInit()		//9600bps@11.0592MHz
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x40;		//8λ����,�ɱ䲨����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xFD;			//�趨��ʱ��ֵ
	TH1 = 0xFD;			//�趨��ʱ����װֵ		
	TR1 = 1;			//������ʱ��1
	ET1 = 0;        	//��ֹ��ʱ��1�ж�  
}

void sendByte(unsigned char ch)
{
	SBUF = ch;
	while(!TI);	TI=0;
}
void sendString(char *str)
{
	while(*str != '\0')
	{
		sendByte(*str++);
	}
}


