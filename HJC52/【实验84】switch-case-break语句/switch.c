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
程序功能：	通过实例说明switch语句的功能。特别注意switch语句的格式，在此很容易犯错。	
****************************************************************************/
#include <reg51.h>

sbit s2=P3^4;
sbit s3=P3^5;
sbit s4=P3^6;
sbit s5=P3^7;

void main()
{
	char anjian;
	while(1)   //无条件永远执行大循环
	{
		if(!s2)			  //这些按键按下，就会使anjian变量赋以相应的值。
			anjian=1;
		if(!s3)
			anjian=2;
		if(!s4)
			anjian=3;
		if(!s5)
			anjian=4;

		switch(anjian)	//当按键的值为几，程序就跳转到case几执行指令，让然后跳出
		{//这个大括弧一定不可少
			case 1: P1=0X0F; break;//这个break也不可少
			case 2: P1=0Xf0; break;
			case 3: P1=0X55; break;
			case 4: P1=0Xaa; break;
			default:P1=0X00; break;//这个为当anjian取值为其他值时的结果（注意关键字为default）。
		}						   //又由于在刚定义变量anjian时，变量的值为初始值0，而0不属于上面的数值，
								   //故此时default项即被选中，故刚开机时，为8个LED均亮。
	}
}