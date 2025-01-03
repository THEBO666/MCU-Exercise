/**********************HJ-3G实验开发板例程************************
*  平台：HJ-3G V6.0 + Keil U3 + STC89C52
*  名称：与上个软件延时的计时相比，此采用定时器的方法，不但节省了单片机的
			资源，而且定时精度高。故做精确定时或者单片机资源有限时，提倡用定时器
			的方法。
			这里采用的是定时器0工作于模式1。
			用的是中断法。
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

//注意晶振需为11.0592M。
//若为其他数值晶振，请改变TH0与TL0参数值，否则计时会有很大误差 。

#include<reg51.h>

#define uchar unsigned char

sbit dula=P2^6;
sbit wela=P2^7;
unsigned char j,k,c1,c0,m,n=255;
unsigned char pp;
unsigned char code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
                        0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

void delay(unsigned char i)
{
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
}

void display(uchar a,uchar b)
{
   P0=table[a];
   dula=1;
   dula=0;
   
   P0=0xef;
   wela=1;
   wela=0;
   delay(5);
   
   P0=table[b];
   dula=1;
   dula=0;
   
   P0=0xdf;
   wela=1;
   wela=0;
   delay(5);
}

void main()
{
	TMOD=0x01;		 //模式设置，00000001，可见采用的是定时器0，工作与模式1（M1=0，M0=1）。
	TR0=1;			 //打开定时器
	TH0=(65536-46080)/256;// 由于晶振为11.0592,故所记次数应为46080，计时器每隔50000微秒发起一次中断。
	TL0=(65536-46080)%256;//46080的来历，为50000*11.0592/12
	ET0=1;			 //开定时器0中断
	EA=1;			 //开总中断
	while(1)
	{
		if(pp==20)
		{	pp=0;
			m++;
			n--;
			P1=n;//闪烁灯
			if(m==60)
			{
				m=0;	   //若到了60s，则归零
			}
		}
		c0=m%10;		  //取出当前描述的个位与十位
		c1=m/10;
		display(c1,c0);	   //显示
	}
}

void time0() interrupt 1
{TH0=(65536-46080)/256;
	TL0=(65536-46080)%256;
	pp++;
}
