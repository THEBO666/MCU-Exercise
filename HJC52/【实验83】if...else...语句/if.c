/**********************HJ-3G实验开发板例程************************
*  平台：HJ-3G V6.0 + Keil U3 + STC89C52
*  名称：C语言学习实验
*  公司：慧净电子科技有限公司
*  淘宝：http://shop37031453.taobao.com       
*  网站：www.hlmcu.com
*  编写：
*  日期：2008-8-08
*   QQ : 121350852  398115088
*  晶振:11.0592MHZ
*  说明：免费开源，不提供源代码分析，有问题直接到慧净论坛交流
*  论坛：http://hjdz.5d6d.com
******************************************************************
程序功能：	 通过实例，让同学们了解if…else…语句的作用。
			 当if后面括弧里面的条件表达式为真，则执行if后面大括弧里的指令
			 否则将执行else语句后面大括弧里的指令
****************************************************************************/
#include <reg52.h>

sbit s2=P3^4;		  //本程序中，P3^4用作输入。 P1口用作输出

void main()
{
	while(1) //永远无条件的执行这个循环。
	{
		if(s2==0)	  //当s2键被按下时，P3^4管脚为低电平。也即，若s2为0，即代表s2按键被按下
			P1=0x55;  //此时，P1口电平分布为01010101
		else		  //否则，s2未被按下
			P1=0xaa;  //此时，P1口电平分布为10101010
	}
}