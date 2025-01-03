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
程序功能：	比较循环移位与非循环移位。程序中，P1=m<<2;为非循环移位。
			P1=_crol_(m,2);为循环移位。注意观察P1口相连的各发光led的亮灭变化，
			进而比较两者间的差异。
			当按键S2没有被按下时，执行的为循环移位；当按下时，执行非循环移位。
****************************************************************************/
#include <reg52.h>
#include <intrins.h>

sbit s2=P3^4;

void main()
{
	
	unsigned char m=0xf3;
	while(1)
	{
		if(s2==0)
			P1=m<<2;//将左移运算结果送P1口,此运算符为不循环移动，即移出的数据将丢失，而后面的将补零
		else
			P1=_crol_(m,2);//这个为循环移位，即移出的那些位将被送入到低位。
				   //但是注意，调用这个_crol_(,)之前，要在头文件中包含intrins.h。
	 }
}
/*另外，>>为非循环右移运算符。而_cror_（，）为循环右移函数。
  其包含于intrins.h头文件中，该文件还包含有其他移位函数，
  有兴趣的同学可以查阅相关资料。*/