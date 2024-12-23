/**********************HL-1实验开发板例程************************
*  平台：HL-1 V8.0 + Keil U3 + STC89C52
*  名称：用四个led指示HJ-3G实验板键盘最下面一排的四个按键状态。
			当按键按下时，对应led亮；松开后，对应led灭
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

sbit s2=P3^4;
sbit s3=P3^5;
sbit s4=P3^6;
sbit s5=P3^7;
sbit led1=P1^0;
sbit led2=P1^1;
sbit led3=P1^2;
sbit led4=P1^3;

void main()
{
	while(1)
	{
		if(s2==0)
			led1=0;
		else
			led1=1;

		if(s3==0)
			led2=0;
		else
			led2=1;

		if(s4==0)
			led3=0;
		else
			led3=1;

		if(s5==0)
			led4=0;
		else
			led4=1;
	}
}