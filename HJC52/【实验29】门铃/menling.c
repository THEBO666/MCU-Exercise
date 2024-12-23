/**********************HJ-3G实验开发板例程************************
*  平台：HJ-3G V6.0 + Keil U3 + STC89C52
*  名称：模拟简易门铃；且有关闭门铃功能。
		  当按下HJ-3G上的S2键后，蜂鸣器会发出十次短暂的“嘟嘟”声作为呼叫。
		  S3用于关闭或者打开门铃。
		  当门铃处于关闭时，按下S2不会有呼叫效果。
*  公司：慧净电子科技有限公司
*  淘宝：http://shop37031453.taobao.com       
*  网站：www.hlmcu.com
*  编写：
*  日期：2008-8-08
*   QQ : 121350852  398115088
*  晶振:11.0592MHZ
*  说明：免费开源，不提供源代码分析，有问题直接到慧净论坛交流
*  论坛：http://hjdz.5d6d.com
******************************************************************/
#include<reg52.h>

#define uchar unsigned char 
uchar k,ok=1;//默认开机后，门铃开。
unsigned int j;
sbit s2=P3^4;
sbit s3=P3^5;
sbit beep=P2^3;

void delay(unsigned int i)
{
	for(j=i;j>0;j--)
	for(k=125;k>0;k--);
}

void main()
{
	while(1)
	{
		if(ok==1)
		{
			if(s3==0)
			{
				while(s3==0);
				ok=0;
			 }
		}
		else
		{
			if(s3==0)
			{
				while(s3==0);
				ok=1;
			 }
		}
		if((s2==0)&(ok==1))
		{	uchar i=5;
			for(i=5;i>0;i--)
			{
				beep=0;
				delay(800);
				beep=1;
				delay(800);
				beep=0;
				delay(1200);
				beep=1;
				delay(1300);
			}
		}
	}
}


