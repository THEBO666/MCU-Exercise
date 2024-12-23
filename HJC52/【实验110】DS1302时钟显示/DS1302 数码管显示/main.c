/**********************HL-1ʵ�鿪��������************************
*  ƽ̨��HL-1 V6.2 + Keil U3 + STC89C52RD
*  ���ƣ�DS1302 �������ʾ�����ա�ʱ��
*  ��˾���۾����ӿƼ����޹�˾
*  �Ա���http://shop37031453.taobao.com       
*  ��վ��www.hlmcu.com
*  ��д���۾�
*  ���ڣ�2008-8-08
*   QQ : 121350852 398115088
*  ����:11.0592MHZ
*  ˵������ѿ�Դ�����ṩԴ���������������ֱ�ӵ��۾���̳����
*  ��̳��http://hjdz.5d6d.com
******************************************************************/
#include <reg52.h>
#include "ds1302.h"
#include "display.h"
#define uchar unsigned char
unsigned char code table[]={
0x3f  , 0x06 , 0x5b , 0x4f ,
0x66 , 0x6d ,0x7d , 0x07 , 
0x7f  , 0x6f , 0x77 , 0x7c ,
0x39 , 0x5e , 0x79 , 0x71 ,0xbf
};
void main()
{
	uchar t0,t1,t2,t3,t4,t5;
	SYSTEMTIME CurrentTime;
	Initial_DS1302();
	DS1302_SetTime(DS1302_HOUR,10);	//���õ�ʱ����10��54��30
	DS1302_SetTime(DS1302_MINUTE,54);
	DS1302_SetTime(DS1302_SECOND,30);   
	while(1)
	{
		DS1302_GetTime(&CurrentTime);
		DateToStr(&CurrentTime);
		TimeToStr(&CurrentTime);
		t0=CurrentTime.TimeString[0];
		t1=CurrentTime.TimeString[1];
		t2=CurrentTime.TimeString[3];
		t3=CurrentTime.TimeString[4];
		t4=CurrentTime.TimeString[6];
		t5=CurrentTime.TimeString[7];
		display(table[t0],table[t1],table[t2],table[t3],table[t4],table[t5]);
	}
}