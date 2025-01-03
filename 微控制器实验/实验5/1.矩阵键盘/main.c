#include <STC89C5xRC.H>
#include "seg.h"
#include "key.h"
#include "led.h"

typedef unsigned char u8;
typedef unsigned int u16;

u8 kval,kslow,kdown,kold;
u8 pos;
u16 segslow;
u8 seg[8]={10,10,10,10,10,10,10,10};
u8 led[8]={0,0,0,0,0,0,0,0};
u8 pot[8]={0,0,0,0,0,0,0,0};
u8 kdis;
u16 delay;
bit flag=0;
void Key_Pro()
{
	if(kslow) return ;
	kslow=1;
	kval=Key_Read();
	kdown=kval&(kold^kval);
	kold=kval;
	kdis=kold;
}

void Seg_Pro()
{
	if(segslow) return ;
	segslow=1;
	seg[7]=kdis%10;
	seg[6]=kdis/10;
}

void Led_Pro()
{
	led[0]=(flag==1);
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
	if(++kslow==10) kslow=0;
	if(++segslow==500) segslow=0;
	if(++pos==8) pos=0;
	if(++delay==1000)
	{
		delay=0;
		flag=~flag;
	}
	Seg_Display(pos,seg[pos],pot[pos]);
	Led_Display(pos,led[pos]);

}

void sysInit()
{
	
}
void main()
{
	sysInit();
	Timer0_Init();
	while(1)
	{
		Key_Pro();
		Seg_Pro();
		Led_Pro();
	}
}