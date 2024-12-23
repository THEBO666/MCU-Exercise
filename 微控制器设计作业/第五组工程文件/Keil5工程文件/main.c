#include <STC89C5xRC.H>
#include "iic.h"
#include "onewire.h"
#include "key.h"
#include "led.h"
#include "lcd1602.h"

typedef unsigned char u8;
typedef unsigned int u16;

sbit Normal_LED = P1 ^ 2;
sbit Smog_LED = P1 ^ 1;
sbit Tem_LED = P1 ^ 0;

u8 kval, kdown, kold, kslow;
u16 lcdslow;
bit relayflag = 0;
bit t_flag, s_flag;
bit set_flag;

float p_t = 50.0, t; // 初始温度参数
u8 p_s = 40, s;		 // 初始烟雾阈值
u8 tslow;
u8 mode;
bit alarmflag = 0;
u16 l1delay, l2delay;
bit l1flag, l2flag;
bit l1, l2;
void Alarm()
{
	if (alarmflag)
	{
		Normal_LED = 1;
		Smog_LED = 0;
		Tem_LED = 0;
		Beep(1);
		Relay(1);
	}
	else
	{
		Normal_LED = 0;
		Smog_LED = 1;
		Tem_LED = 1;
		Beep(0);
		Relay(0);
	}
}
void Key_Pro()
{
	if (kslow)
		return;
	kslow = 1;
	kval = Key_Read();
	kdown = kval & (kold ^ kval);
	kold = kval;
	switch (kdown)
	{
	case 1:
		if (++mode == 3)
			mode = 0;
		break;
	case 2:
		if (mode == 1)
			p_t += 0.5;
		if (p_t == 100.0)
			p_t = 99.5;
		if (mode == 2)
			p_s += 1;
		if (p_s == 100)
			p_s = 99;
		break;
	case 3:
		if (mode == 1)
			p_t -= 0.5;
		if (p_t < 0)
			p_t = 0.0;
		if (mode == 2)
			p_s -= 1;
		if (p_s == 255)
			p_s = 0;
		break;
	case 4:
		alarmflag = ~alarmflag;
		Alarm();
		break;
	}
}

void LCD_Pro()
{

	if (lcdslow)
		return;
	lcdslow = 1;
	t = Read_T();
	s = (u16)(AD_Read(0x03) * 100) / 255;
	
	LCD_ShowString(1, 1, "S T:");
	LCD_ShowNum(1, 5, (u16)p_t, 2);
	LCD_ShowChar(1, 7, '.');
	LCD_ShowNum(1, 8, (u16)(p_t * 10) % 10, 1);
	LCD_ShowChar(1, 9, 0xdf);
	LCD_ShowString(1, 10, "C S:");
	LCD_ShowNum(1, 14, p_s, 2);
	LCD_ShowChar(1, 16, '%');
	LCD_ShowString(2, 1, "N T:");
	LCD_ShowNum(2, 5, (u16)t, 2);
	LCD_ShowChar(2, 7, '.');
	LCD_ShowNum(2, 8, (u16)(t * 10) % 10, 1);
	LCD_ShowChar(2, 9, 0xdf);
	LCD_ShowString(2, 10, "C S:");
	LCD_ShowNum(2, 14, s, 2);
	LCD_ShowChar(2, 16, '%');
	if (mode == 1)
		LCD_ShowNum(1, 2, 1, 1);
	if (mode == 2)
		LCD_ShowNum(1, 2, 2, 1);
	
}
void Led_Pro()
{
	if (!alarmflag)
	{
		Normal_LED = t >= p_t || s >= p_s;
		if (t >= p_t)
		{
			l1flag = 1;
			if (l1delay >= 100)
			{
				Tem_LED = ~Tem_LED;
				l1delay = 0;
			}
		}
		else
		{
			l1flag = 0;
			Tem_LED = 1;
			l1delay = 0;
		}
		if (s >= p_s)
		{
			l2flag = 1;
			if (l2delay >= 100)
			{
				Smog_LED = ~Smog_LED;
				l2delay = 0;
			}
		}
		else
		{
			l2flag = 0;
			Smog_LED = 1;
			l2delay = 0;
		}
		Relay(t >= p_t || s >= p_s);
		BEEP=(t >= p_t || s >= p_s);
	}
}

void Timer0_Init(void) // 1毫秒@12.000MHz
{
	AUXR |= 0x80; // 定时器时钟1T模式
	TMOD &= 0xF0; // 设置定时器模式
	TL0 = 0x20;	  // 设置定时初始值
	TH0 = 0xD1;	  // 设置定时初始值
	TF0 = 0;	  // 清除TF0标志
	TR0 = 1;	  // 定时器0开始计时
	ET0 = 1;	  // 使能定时器0中断
	EA = 1;
}

void Timer0_Service() interrupt 1
{
	if (++kslow == 10)
		kslow = 0;
	if (++lcdslow == 100)
		lcdslow = 0;
	if (l1flag)
		++l1delay;
	if (l2flag)
		++l2delay;
}

void sysinit()
{
	P1 = 0xD7;
}
void Delay750ms() //@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 6;
	j = 180;
	k = 26;
	do
	{
		do
		{
			while (--k)
				;
		} while (--j);
	} while (--i);
}

int main()
{
	sysinit();
	Read_T();
	Delay750ms();
	LCD_Init();
	Timer0_Init();
	while (1)
	{

		Key_Pro();
		LCD_Pro();
		Led_Pro();
	}
}
