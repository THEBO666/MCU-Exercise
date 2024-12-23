#include <STC15F2K60S2.H>

#include "iic.h"
#include "onewire.h"
#include "key.h"
#include "led.h"
typedef unsigned char u8;
typedef unsigned int u16;

u8 kval,kdown,kold,kslow;
u8 led[8]={0,0,0,0,0,0,0,0};

u8 relayflag=0;
void Key_Pro()
{
	if(kslow) return ;
	kslow=1;
	kval=Key_Read();
	kdown=kval&(kold^kval);
	kold=kval;
	switch(kval)
	{
		case 1:
			relayflag=1;
		break;
	}
	
}


void Led_Pro()
{
	Relay(relayflag);
	
}
void Timer0_Init(void)		//1毫秒@12.000MHz
{
	AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0x18;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0=1;
	EA=1;
}

void Timer0_Service() interrupt 1
{
	if(++kslow==50) kslow=0;
	
}
void sysinit()
{
	P0=0xff;
	P2=P2&0x1f|0x80;
	P2=P2&0x1f;
	
	P0=0x00;
	P2=P2&0x1f|0xa0;
	P2=P2&0x1f;
}
void Delay750ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 32;
	j = 133;
	k = 87;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

int main()
{
	sysinit();
	while(1)
	{
		
		Key_Pro();
		Led_Pro();
	}
}
