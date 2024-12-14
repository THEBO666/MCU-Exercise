#include <STC89C5xRC.H>
#include "lcd1602.h"
#include "iic.h"
#include <STDIO.H>
#include <INTRINS.H>
float u1,u2,u3,u4;
char str1[5],str2[5],str3[5],str4[5];
void Delay10ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 20;
	j = 113;
	do
	{
		while (--j);
	} while (--i);
}

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"1.   V 2.   V");
	LCD_ShowString(2,1,"3.   V 4.   V");
	while(1)
	{
		AD_Read(0x00);
		sprintf(str1,"%.2f",ad[0]);
		LCD_ShowString(1,3,str1);
		u2=AD_Read(0x01)/51.0;
		sprintf(str2,"%.2f",ad[1]);
		LCD_ShowString(1,10,str2);

		u3=AD_Read(0x02)/51.0;
		sprintf(str3,"%.2f",ad[2]);
		LCD_ShowString(2,3,str3);
		u4=AD_Read(0x03)/51.0;
		sprintf(str4,"%.2f",ad[3]);
		LCD_ShowString(2,10,str4);
		Delay10ms();
	}
}