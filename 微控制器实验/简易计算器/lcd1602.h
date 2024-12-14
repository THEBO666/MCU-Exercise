#ifndef __LCD1602_H
#define __LCD1602_H

#include <REGX51.H>
#include <intrins.h>

#define WriteCommand 	0x01
#define WriteData 		0x02

void delay_ms(unsigned int time);
long Lcd_Pow(int x,int y);
void Lcd_Write(unsigned char cd,unsigned char Data);
void Lcd_SetCursor(unsigned char Line,unsigned char Column);
void Lcd_Init(void);
void Lcd_ShowChar(unsigned char Line,unsigned char Column,char dat);
void Lcd_ShowString(unsigned char Line,unsigned char Column,char *String);
void Lcd_ShowNum(unsigned char Line, unsigned char Column, long Number, unsigned char Length);
void Lcd_ShowSignedNum(unsigned char Line,unsigned char Column,long Number,unsigned char Length);
void Lcd_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void Lcd_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void Lcd_Clear(unsigned char Line);
#endif

