/**********************HJ-3G实验开发板例程************************
*  平台：HJ-3G V6.0 + Keil U3 + STC89C52
*  名称：让HJ-3G 实验板的六位数码管轮流显示数字0到5
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
#include <reg51.h>

sbit dula=P2^6;		//段选信号的锁存器控制
sbit wela=P2^7;		//位选信号的锁存器控制

unsigned char code wei[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf};
						//数码管各位的码表
unsigned char code duan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d};
						//0-5的码表
void delay(unsigned int i)
{
	unsigned int m,n;
	for(m=i;m>0;m--)
		for(n=90;n>0;n--);
}

void main()
{
	unsigned char num;
	while(1)
	{
		for(num=0;num<6;num++)
		{
			P0=wei[num];	   
			wela=1;
			wela=0;

			P0=duan[num];	  
			dula=1;
			dula=0;
			delay(1000);
		 }
	}
}

