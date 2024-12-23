/**********************HL-1实验开发板例程************************
*  平台：HL-1 V8.0 + Keil U3 + STC89C52
*  名称：使八位LED逐位移动并不断循环，该方法采用逐个查表赋值的方法
*  公司：慧净电子科技有限公司
*  淘宝：http://shop37031453.taobao.com       
*  网站：www.hjmcu.com
*  编写：慧净
*  日期：2008-8-08
*   QQ : 121350852 398115088
*  晶振:11.0592MHZ
*  说明：免费开源，不提供源代码分析，有问题直接到慧净论坛交流
*  论坛：http://hjdz.5d6d.net
******************************************************************/

#include <reg51.h>



unsigned char table[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};

void delay(unsigned int i)
{
	unsigned int j;
	unsigned char k;
	for(j=i;j>0;j--)
		for(k=125;k>0;k--);
}

void main()
{
	while(1)
	{
		unsigned char m;
		for(m=0;m<8;m++)
		{
			P1=table[m];
			delay(2000);
		}
	}
}