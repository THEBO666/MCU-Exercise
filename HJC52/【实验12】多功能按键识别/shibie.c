/*************************HL-1开发板实验例程**********************
*  平台：HL-1 V8.0 + Keil U3 + STC89C52
*  名称：生活中常见一个按键随着按下次数不同对应不同功能，
		   本程序以HL-1 学习板中的k1键为例，模拟其具有2种功能，
		   一是点亮一个发光二极管，二是蜂鸣器发声
*  公司：慧净电子科技有限公司
*  淘宝：http://shop37031453.taobao.com       
*  网站：www.hjmcu.com
*  编写：慧净
*  日期：2008-8-08
*   QQ : 121350852    398115088
*  晶振:11.0592MHZ
*  说明：免费开源，不提供源代码分析，有问题直接到慧净论坛交流
*  论坛：http://hjdz.5d6d.net
******************************************************************/

#include<reg52.h>

#define uchar unsigned char 
uchar num;

sbit beep=P2^3;
sbit led=P1^0;
sbit k1=P3^4;

void delay(uchar i)
{
	uchar j,k;
	for(j=i;j>0;j--)
	for(k=125;k>0;k--);
}


void main()
{
	while(1)
	{
		if(k1==0)
		{
			delay(20);		 //消抖
			if(k1==20)
			{
				while(!k1);	 //等待按键松开
				num++;
			}
			switch(num)
			{
				case 1: led=0;	beep=1; break;
				case 2: beep=0;	led=1;	num=0; break;
			}
		}
	}
}