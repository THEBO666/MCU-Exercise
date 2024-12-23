/**********************HL-1实验开发板例程************************
*  平台：HL-1 V8.0 + Keil U3 + STC89C52
*  名称：使八位LED逐位移动并不断循环
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
#include <intrins.h>  //这个头文件是这个方法的核心，它包含了逐步移位函数功能
					  //即程序中的_crol_(P1,y)

sbit led=P1^0;

void delay(unsigned int i)
{
	unsigned int j;
	unsigned char k;
	for(j=i;j>0;j--)
		for(k=125;k>0;k--);
}

void main()
{	P1=0xfe;
	delay(1000);
	while(1)
	{
	//	unsigned char m;
		//P1=0xfe;
	//	delay(1000);
	//	for(m=7;m>0;m--)
		{
			P1=_crol_(P1,1);   //P1逐步左移一位。
			delay(1000);
		}
	}
}