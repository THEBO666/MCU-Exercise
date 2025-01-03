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
程序功能：		将P2口的状态传递给P1口，给同学对管脚间状态传递
				提供一直感性的认识。
				下载程序后，八个发光二极管会间隔着被点亮。
************************************************************************/

#include<reg52.h>

void main()
{
	P2=0Xaa;  //给P2管脚赋值，0xaa即二进制的1010 1010。
	P1=P2;	  //将P2口状态传给P1，可以发现P1口的灯间隔着被点亮。
	while(1);
}

//P1，P2表面为管脚，但实质上对应的是单片机内部的寄存器。