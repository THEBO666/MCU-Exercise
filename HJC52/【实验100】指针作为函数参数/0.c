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
程序功能：	演示指针作为函数的参数。
****************************************************************************/
#include <reg52.h>

void delay(void)  //此延时函数无参数，无返回值。在其后面作了一个有参数的延时函数作为对比
{
  unsigned char m,n;
  for(m=0;m<200;m++)
  	for(n=0;n<200;n++);
}
/***************************************************************
//带参数的延时函数
void delay(unsigned int m)
{
	unsigned int n;
	unsigned char p;
	for(n=m;n>0;n--)
    	for(p=0;p<200;p++);
}
//调用时，可这样调用：delay(200);括弧中的值可自设，但不可大于
//定义时所定的unsigned int的范围。
*****************************************************************/
void led(unsigned char *p) //形参为无符号字符型指针
{
  unsigned char i;
  while(1)
   {
	  i=0;   //将i置为0，指向数组第一个元素
	  while(i!=16) 
	   {
        P1=*(p+i);// 取的指针所指变量（数组元素）的值，送P1口
	     delay();   //调用延时函数
		  i++;    //指向下一个数组元素
	   }
	}
}


void main(void)
{  
  unsigned  char code table[16]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F, 
                              0x7F,0xBF,0xDF,0xEF,0xF7,0xFB,0xFD,0xFE};
										//流水灯控制码 
  unsigned char *p;
  p=table;
  led(p);
  
}