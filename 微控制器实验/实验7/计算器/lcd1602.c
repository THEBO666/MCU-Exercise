#include "lcd1602.h"

sbit LCD_RS =  P1^0;
sbit LCD_RW =  P1^1;
sbit LCD_EN =	 P2^5;
sbit LCD_DB0 = P0^0;
sbit LCD_DB1 = P0^1;
sbit LCD_DB2 = P0^2;
sbit LCD_DB3 = P0^3;
sbit LCD_DB4 = P0^4;
sbit LCD_DB5 = P0^5;
sbit LCD_DB6 = P0^6;
sbit LCD_DB7 = P0^7;

/*
	函数内容：在11.0592Mhz下ms延时
	函数参数：unsigned int time --延时时间
	返回值：	无
*/
void delay_ms(unsigned int time)
{
	unsigned char i=0,t=0;
	do
	{
		i=2;
		t=199;
		do
		{
			while(--t);
		}while(--i);
	}while(--time);	
}

/*
	函数内容：Lcd写数据或写指令函数
	函数参数：unsigned char cd---指令或数据
						unsigned char Data-待发送的指令或数据
	返回值：	无
*/
void Lcd_Write(unsigned char cd,unsigned char Data)
{
	if(cd == WriteCommand){
		LCD_RS = 0;
		LCD_RW = 0;
	}
	else{
		LCD_RS = 1;
		LCD_RW = 0;
	}
	
	if(Data & 0x80){
		LCD_DB7 = 1;
	}
	else{
		LCD_DB7 = 0;
	}
	if(Data & 0x40){
		LCD_DB6 = 1;
	}
	else{
		LCD_DB6 = 0;
	}
	if(Data & 0x20){
		LCD_DB5 = 1;
	}
	else{
		LCD_DB5 = 0;
	}
	if(Data & 0x10){
		LCD_DB4 = 1;
	}
	else{
		LCD_DB4 = 0;
	}
	if(Data & 0x08){
		LCD_DB3 = 1;
	}
	else{
		LCD_DB3 = 0;
	}
	if(Data & 0x04){
		LCD_DB2 = 1;
	}
	else{
		LCD_DB2 = 0;
	}
	if(Data & 0x02){
		LCD_DB1 = 1;
	}
	else{
		LCD_DB1 = 0;
	}
	if(Data & 0x01){
		LCD_DB0 = 1;
	}
	else{
		LCD_DB0 = 0;
	}
	
	LCD_EN = 1;
	delay_ms(1);
	LCD_EN = 0;
	delay_ms(1);
}

/*
	函数内容：Lcd设置第几行第几列
	函数参数：unsigned char Line---行
						unsigned char Column-列
	返回值：	无
*/
void Lcd_SetCursor(unsigned char Line,unsigned char Column)
{
	if(Line == 1){
		Lcd_Write(WriteCommand,(0x80|(Column-1)));
	}
	else if(Line == 2){
		Lcd_Write(WriteCommand,(0x80|(Column-1+0x40)));
	}
}

/*
	函数内容：Lcd初始化函数
	函数参数：无
	返回值：	无
*/
void Lcd_Init(void)
{
	Lcd_Write(WriteCommand,0x38);
	Lcd_Write(WriteCommand,0x0c);
	Lcd_Write(WriteCommand,0x06);
	Lcd_Write(WriteCommand,0x01);
}

/*
	函数内容：Lcd指定位置显示单个字符
	函数参数：unsigned char Line---行
						unsigned char Column-列
						char dat ------------字符数据
	返回值：	无
*/
void Lcd_ShowChar(unsigned char Line,unsigned char Column,char dat)
{
	Lcd_SetCursor(Line,Column);
	Lcd_Write(WriteData,dat);
}

/*
	函数内容：Lcd指定位置显示字符串
	函数参数：unsigned char Line---行
						unsigned char Column-列
						char *String --------字符指针
	返回值：	无
*/
void Lcd_ShowString(unsigned char Line,unsigned char Column,char *String)
{
	unsigned char i=0;
	Lcd_SetCursor(Line,Column);
	for(i=0;String[i]!='\0';i++)
	{
		Lcd_Write(WriteData,String[i]);
	}
}

/*
	函数内容：计算指数值
	函数参数：int x--底数
						int y--指数
	返回值：	实际指数值
*/
long Lcd_Pow(int x,int y)
{
	unsigned char i = 0;
	long Result = 1;
	for(i=0;i<y;i++)
	{
		Result = Result *x;
	}
	return Result;
}

/*
	函数内容：Lcd指定位置显示数字
	函数参数：unsigned char Line---行
						unsigned char Column-列
						unsigned int Number--数字
						unsigned char Length-数字长度
	返回值：	无
*/
void Lcd_ShowNum(unsigned char Line, unsigned char Column, long Number, unsigned char Length)
{
	unsigned char i = 0;
	Lcd_SetCursor(Line, Column);
	for(i=Length;i>0;i--)
	{
		Lcd_Write(WriteData,(Number/Lcd_Pow(10,i-1)%10+'0'));
	}
}

/*
	函数内容：Lcd指定位置显示有符号数字
	函数参数：unsigned char Line---行
						unsigned char Column-列
						unsigned int Number--数字
						unsigned char Length-数字长度
	返回值：	无
*/
void Lcd_ShowSignedNum(unsigned char Line,unsigned char Column,long Number,unsigned char Length)
{
	unsigned char zeroFlag = 0;
	unsigned char i = 0;
	unsigned char dat = 0;
	long Number1 = 1;
	Lcd_SetCursor(Line, Column);
	if(Number >= 0){
		//Lcd_Write(WriteData,'+');
		Number1 = Number;
	}else
	{
		Lcd_Write(WriteData,'-');
		Number1 = ~(Number-1);
	}
	for(i=Length;i>0;i--)
	{
		dat = (Number1/Lcd_Pow(10,i-1)%10+'0');
		if((dat > '0') && (dat <= '9'))
		{
			zeroFlag = 1;
		}
		if(zeroFlag == 1){
			Lcd_Write(WriteData,dat);
		}
	}
}

/*
	函数内容：Lcd指定位置显示十六进制数字
	函数参数：unsigned char Line---行
						unsigned char Column-列
						unsigned int Number--数字
						unsigned char Length-数字长度
	返回值：	无
*/
void Lcd_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i = 0,SigleNumber = 0;
	Lcd_SetCursor(Line, Column);
	for(i=Length;i>0;i--)
	{
		SigleNumber = Number/Lcd_Pow(16,i-1)%16;
		if(SigleNumber < 10){
			Lcd_Write(WriteData,(SigleNumber+'0'));
		}
		else{
			Lcd_Write(WriteData,(SigleNumber-10+'A'));
		}
	}
}

/*
	函数内容：Lcd指定位置显示二进制数字
	函数参数：unsigned char Line---行
						unsigned char Column-列
						unsigned int Number--数字
						unsigned char Length-数字长度
	返回值：	无
*/
void Lcd_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i = 0;
	Lcd_SetCursor(Line, Column);
	for(i=Length;i>0;i--)
	{
		Lcd_Write(WriteData,(Number/Lcd_Pow(2,i-1)%2+'0'));
	}
}

/*
	函数内容：Lcd指定位置显示二进制数字
	函数参数：unsigned char Line---行
						unsigned char Column-列
						unsigned int Number--数字
						unsigned char Length-数字长度
	返回值：	无
*/
void Lcd_Clear(unsigned char Line)
{
	unsigned char i = 0;
	if(Line == 1)
	{
		Lcd_Write(WriteCommand,0x80);
		for(i=0;i<16;i++)
		{
			Lcd_Write(WriteData,0x20);
		}
	}
	else
	{
		Lcd_Write(WriteCommand,(0x80+0x40));
		for(i=0;i<16;i++)
		{
			Lcd_Write(WriteData,0x20);
		}
	}
}

