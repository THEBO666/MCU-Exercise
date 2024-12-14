#include <STC89C5xRC.H>
#include "ds1302.h"
#include "lcd1602.h"

void TimeShow(void)//时间显示功能
{
	DS1302_ReadTime();//读取时间
	LCD_ShowNum(1,1,DS1302_Time[0],2);//显示年
	LCD_ShowNum(1,4,DS1302_Time[1],2);//显示月
	LCD_ShowNum(1,7,DS1302_Time[2],2);//显示日
	LCD_ShowNum(2,1,DS1302_Time[3],2);//显示时
	LCD_ShowNum(2,4,DS1302_Time[4],2);//显示分
	LCD_ShowNum(2,7,DS1302_Time[5],2);//显示秒
}
void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"  -  -  ");
	LCD_ShowString(2,1,"  :  :  ");
	DS1302_SetTime();
	while(1)
	{
		TimeShow();
	}
}