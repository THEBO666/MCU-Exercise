	 /**********************HL-1实验开发板例程************************
*  平台：HL-1 V8.0 + Keil U3 + STC89C52
*  名称：TFT彩屏测试程序
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
#include <intrins.h>
#include "sys.h"
void delayms(int count)  // /* X1ms */
{
        int i,j;
        for(i=0;i<count;i++)
                for(j=0;j<1000;j++);
}