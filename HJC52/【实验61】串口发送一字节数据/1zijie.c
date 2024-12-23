/**********************HJ-3G实验开发板例程************************
*  平台：HJ-3G V6.0 + Keil U3 + STC89C52
*  名称：往串口发送一字节数据（可通过超级终端显示出来，
		  超级终端波特率选为9600）。
		  超级终端设置好后，每按下一次S2键，松开后均会在超级终端
		  上显示一个字母"a"。
		  入口参数：d: 要发送的字节数据。
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

#include <reg52.h>
#define jingzhen     11059200UL			 /*使用22.1184M晶体*/	 //
#define botelv   9600UL		     /*波特率定义为9600*/
unsigned char zifu='a';			//待显示字符。
volatile unsigned char sending;
sbit s2=P3^4;

void delay(unsigned char i)
{
	unsigned char j,k;
	for(j=i;j>0;j--)
		for(k=90;k>0;k--);
}
void init(void)				//串口初始化
{
 EA=0; //暂时关闭中断
 TMOD&=0x0F;  //定时器1模式控制在高4位
 TMOD|=0x20;    //定时器1工作在模式2，自动重装模式
 SCON=0x50;     //串口工作在模式1
 TH1=256-jingzhen/(botelv*12*16);  //计算定时器重装值
 TL1=256-jingzhen/(botelv*12*16);
 PCON|=0x80;    //串口波特率加倍
 ES=1;         //串行中断允许
 TR1=1;        //启动定时器1
 REN=1;        //允许接收 
 EA=1;         //允许中断
}

void send(unsigned char d)		  //发送一个字节的数据，形参d即为待发送数据。
{
 
 SBUF=d; //将数据写入到串口缓冲
 sending=1;	 //设置发送标志
 while(sending); //等待发送完毕
}

void main()
{
	init();
	while(1)
	{
		if(s2==0)
		{
			delay(20);
			if(!s2)
			{
				while(!s2);		   
				send(zifu);
			}
		}
	}
}

void uart(void) interrupt 4		 //串口发送中断
{
 if(RI)    //收到数据
 {
  RI=0;   //清中断请求
 }
 else      //发送完一字节数据
 {
  TI=0;
  sending=0;  //清正在发送标志
 }
}