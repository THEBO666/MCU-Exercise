#ifndef __DS1302_H__
#define __DS1302_H__
#include <STC89C5xRC.H>


sbit DS1302_SCLK=P1^7;
sbit DS1302_IO=P2^7;
sbit DS1302_CE=P1^2;
//寄存器写入地址/指令定义
#define DS1302_SECOND		0x80
#define DS1302_MINUTE		0x82
#define DS1302_HOUR			0x84
#define DS1302_DATE			0x86
#define DS1302_MONTH		0x88
#define DS1302_DAY			0x8A
#define DS1302_YEAR			0x8C
#define DS1302_WP			0x8E
extern unsigned char DS1302_Time[];
void DS1302_Init();
void DS1302_WriteByte(unsigned char Command,Data);
unsigned char DS1302_ReadByte(unsigned char Command);
void DS1302_SetTime();
void DS1302_ReadTime();

#endif