/*************************HL-1开发板实验例程**********************
*  平台：HL-1 V8.0 + Keil U3 + STC89C52
*  实验：流水灯3
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
#include<reg51.h>

void delay(unsigned char i)
{
	unsigned char m,n;
	for(m=i;m>0;m--)
	for(n=125;n>0;n--);
}

void main()
{
	unsigned char m=255;
	while(1)
	{
		P1=m;
		delay(2000);
		m--;
	}
}