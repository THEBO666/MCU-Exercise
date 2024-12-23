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
#include <sys\sys.h>
#include <lcd\lcd.h> 
/* www.hjmcu.com 慧净电子
代码测试环境:HL-1 HJ-3G HJ-C52开发板板+STC89C52芯片  51单片机显示速度比较慢，
建议到慧净网购买1T指令周期的STC单片机（51内核STC12LE5A60S2)+33M晶振
*/	

main()
{ 

	while(1)
	{
		 Lcd_Init();   //tft初始化
		 LCD_Clear(RED);
		 delayms(3000);
		 LCD_Clear(GREEN);
		 delayms(3000);
		 LCD_Clear(BLUE);
		 delayms(3000);

    }


}
