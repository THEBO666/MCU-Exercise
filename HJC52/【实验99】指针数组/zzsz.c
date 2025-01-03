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
程序功能：	演示指针数组的应用方法。
****************************************************************************/
#include <reg52.h>

void delay(void)	  //一段小延时
{
  unsigned char m,n;
  for(m=0;m<200;m++)
    for(n=0;n<200;n++);
}

void main(void)
{  
	unsigned char code table[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
	unsigned char *p[ ]={&table[0],&table[1],&table[2],&table[3],&table[4],
						&table[5],&table[6],&table[7]}; 
						//使指针数组中的每一个变量均指向数组table[]中的相应地址。
						//指针变量存放的是地址。
	unsigned char i;     
	while(1)
    {
	   for(i=0;i<8;i++)
		 {
		   P1=*p[i];	//i的变化，导致指针内容的变化，然后导致向P1传送的数值的变化。
			delay();
		 }
	 }
}